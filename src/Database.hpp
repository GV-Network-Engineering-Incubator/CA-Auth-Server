#pragma once

#include <string>
#include "DatabaseNode.hpp"

#define failedToStart(s) ((s)->message & DATABASE_FAIL)

class Database {
public:
  // Database status constants
  const int DATABASE_OK = 0;
  const int DATABASE_FAIL = 2;

  static Database* Instance();

private:
  Database() {};
  int initialize();
  int loadConfig(std::string filename);
};
