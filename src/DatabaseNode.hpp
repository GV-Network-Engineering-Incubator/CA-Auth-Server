#include <time.h>
#include <string>

class DatabaseNode {
public:
  time_t nTime; // Time of database creation
  std::string name; // Database name
  time_t failTime; // The time of failure
  int port; // Running port
  std::string host; // The running host
}
