#include "database.h"

#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/stat.h>

/* Global reference to the me node. The databaseNode
 * will always point to this one*/
databaseNode *me = NULL;

databaseNode *createDatabaseNode(char* nodename);
int databaseAddNode(databaseNode *node);
int databasePing();
int loadConfig(char* filename);

/*----------------------------------------------
 * Initializers
 * -------------------------------------------*/
