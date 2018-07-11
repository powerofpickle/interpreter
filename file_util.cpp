#include "file_util.h"
#include "directory.h"
#include "file.h"

#include <iostream>
#include <filesystem>
#include <fstream>

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

int FileUtil::path_status(std::string path){
  struct stat stat_info;
  if(stat(path.c_str(), &stat_info) == 0){
    if(stat_info.st_mode & S_IFDIR){
      return DIRECTORY;
    }else if(stat_info.st_mode & S_IFREG){
      //std::cout << "File Found!" << std::endl;
      return FILE;
    }else{
      std::cout << "Something other than a file or directory was found!" << std::endl;
      return NOT_FOUND;
    }
  }
  std::cout << "NOT FOUND" << std::endl;
  return NOT_FOUND;
}

std::string& FileUtil::read_file(std::string path, std::string& dest){
  std::ifstream infile { path };
  dest = std::string { std::istreambuf_iterator<char>(infile), std::istreambuf_iterator<char>() };
  return dest;
}

int FileUtil::write_file(std::string path, std::string& data){
  std::ofstream out(path);
  out << data;
  return 1;
}

Node* FileUtil::node_at(std::string path){
  Node* r = nullptr;

  int file_stat = FileUtil::path_status(path);
  switch(file_stat){
    case FileUtil::NOT_FOUND:
      //std::cout << new_path << " does not exist!" << std::endl;
      break;
    case FileUtil::FILE:
      //std::cout << new_path << " is a file!" << std::endl;
      r = new RealFile(path);
      break;
    case FileUtil::DIRECTORY:
      //std::cout << new_path << " is a directory!" << std::endl;
      r = new RealDirectory(path);
      break;
  }

  return r;
}
