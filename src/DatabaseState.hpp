#pragma once

#include <string>
#include "DatabaseNode.hpp"

class DatabaseState {
public:
  DatabaseNode* me; // This node's status
  int state;
  int size; // How much data it takes up on the harddrive
  std::string dataLocation; // Where this database stores its goods
  int getState();
  void setState(int);

  int getSize();

  std::string getDataLocation();
  void setDataLocation(std::string);
};
