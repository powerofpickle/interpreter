#pragma once
#include <string>
#include "node.h"

namespace FileUtil{

  const int NOT_FOUND = 0;
  const int FILE = 1;
  const int DIRECTORY = 2;

  int path_status(std::string path);
  std::string& read_file(std::string path, std::string& dest);
  int write_file(std::string path, std::string& data);
  Node* node_at(std::string path);
}
