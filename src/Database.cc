#include "Database.h"
#include <boost/filesystem.h>
#include <iostream>

namespace database {

  int Database::init(std::string path) {
    const std::string dir = _filePath.c_str();
    path = dir + path;
    boost::filesystem::path dir(path);

    if (boost::filesystem::create_directory(path)) {
      std::cerr << "Directory created: " << _filePath << std::endl;
    }
  }

  Database::Database(std::string path="db/db.txt") {
    this->path = path;
    this->init(std::string path);
  }
} // namespace database
