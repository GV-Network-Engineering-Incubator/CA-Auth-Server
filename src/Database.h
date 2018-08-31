#pragma once

#include <map>
#include <string>
#include <vector>

namespace database {
class Database {
  public:
    std::string path;

    Database(std::string path);
    int init();
    bool write_to_file(std::map<std::string, std::string> client_data);
  private:
    std::string encrypt_credentials(std::vector<std::map<std::string, std::string>> client_credentials);
};
} // namespace database
