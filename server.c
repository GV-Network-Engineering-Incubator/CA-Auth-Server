#include <stdio.h>
#include <signal.h> // SA_RESTART
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <signal.h>
#include <time.h>
#include "auth_lib.c"

#define PORT "8080"
#define BACKLOG 15 // Number of pending connections for queue

struct stat st = {0};

void cleanup_client_data() {
  system("rm -f ca.key ca.pem");
}

void init_request_logger() {
  /* Current working directory */
  char cwd[1024];
  if (getcwd(cwd, sizeof(cwd)) != NULL) {
    char* logging_dir = strcat(cwd, "/logs");
    if (stat(logging_dir, &st) == -1) {
      puts("Building logging directory");
      mkdir(logging_dir, 0700);
    } else {
      puts("Logging directory exists, moving on");
    }
  } else {
    perror("Error establishing logging directory!");
  }
}

void log_to_file(char* message) {
  FILE* logfile = fopen("logs/request.log", "ab+");
  fprintf(logfile, message);
}

void logger(char* message, char* error) {
  time_t rawtime;
  struct tm* timeinfo;

  time(&rawtime);
  timeinfo = localtime(&rawtime);
  char* now = asctime(timeinfo);

  if (error != NULL) {
    char* error = strcat(now, error);
    log_to_file(error);
    return;
  }

  char* request = strcat(now, message);
  log_to_file(request);
  return;
}

void sigchld_handler(int s) {
  int saved_errno = errno;
  while(waitpid(-1, NULL, WNOHANG) > 0);
  errno = saved_errno;
}

void* get_in_adddr(struct sockaddr *sa) {
  if (sa->sa_family == AF_INET) {
    return &(((struct sockaddr_in*)sa)->sin_addr);
  }
  return &(((struct sockaddr_in6*)sa)->sin6_addr);
}

int main(void) {
  int sockfd, new_fd, pid;
  static int counter = 0;
  struct addrinfo hints, *servinfo, *p;
  struct sockaddr_storage connecting_addr;
  socklen_t sin_size;
  struct sigaction sa;
  int yes = 1;
  char s[INET6_ADDRSTRLEN];
  int rv;
  char* message, client_reply[6000];

  memset(&hints, 0, sizeof hints);
  hints.ai_family = AF_UNSPEC;
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_flags = AI_PASSIVE; // Use the system this is running on's IP

  init_request_logger();

  if ((rv = getaddrinfo(NULL, PORT, &hints, &servinfo)) != 0) {
    fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
    return 1;
  }

  // Bind to the first open connection
  for (p = servinfo; p != NULL; p = p->ai_next) {
    if ((sockfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) == -1) {
      perror("server: socket");
      return 1;
    }

    if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1) {
      perror("setsockopt");
      exit(1);
    }

    if (bind(sockfd, p->ai_addr, p->ai_addrlen) == -1) {
      perror("server: bind");
      continue;
    }
    break;
  }
  freeaddrinfo(servinfo);

  if (p == NULL) {
    fprintf(stderr, "server: Failed to bind\n");
    exit(1);
  }

  if (listen(sockfd, BACKLOG) == -1) {
    perror("listen");
    exit(1);
  }

  sa.sa_handler = sigchld_handler; // Reap dead processes
  sigemptyset(&sa.sa_mask);
  sa.sa_flags = SA_RESTART;
  if (sigaction(SIGCHLD, &sa, NULL) == -1) {
    perror("sigaction");
    exit(1);
  }

  printf("server: waiting for connections...");

  // Server loop
  while(1) {
    sin_size = sizeof connecting_addr;
    new_fd = accept(sockfd, (struct sockaddr *)&connecting_addr, &sin_size);

    if (new_fd == -1) {
      perror("accept");
      continue;
    }

    // Give s our IP address of the connecting server
    inet_ntop(connecting_addr.ss_family, get_in_adddr((struct sockaddr *)&connecting_addr), s, sizeof s);
    printf("server: got a connection from %s\n", s);


    if ((pid = fork()) == -1) {
      close(new_fd);
      printf("error fork failed for %s", s);
      continue;
    } else if (pid > 0) {
      close(new_fd);
      printf("Connection received");
      counter++;
      continue;
    } else if (pid == 0) {
      counter++;
      send(new_fd, message, strlen(message), 0);
      if (recv(new_fd, client_reply, sizeof client_reply, 0) < 0) {
        puts("Receiving client data failed!");
      }
      puts("Received client CA request, validating");
      system("openssl req -config openssl.conf -x509 -sha256 -nodes -extensions v3_ca -days 3650 -subj '/CN=OpenSSL CA/O=Example Company/C=SE' -newkey rsa:4096 -keyout ca.key -out ca.pem");

      close(new_fd);
      counter--;
      cleanup_client_data();
      break;
    }
  }
  counter = 0;
  return 0;
}

/* openssl req -in mycsr.csr -noout -text */
