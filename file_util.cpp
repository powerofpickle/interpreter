#include "file_util.h"
#include "directory.h"
#include "file.h"

#include <iostream>
#include <filesystem>
#include <fstream>

#include <sys/types.h>
#include <sys/stat.h>


namespace fs = std::filesystem;

int FileUtil::path_status(std::string path){
  //std::cout << path << " is being checked!" << std::endl;
  fs::file_status status;
  try {
    status = fs::status(path);
  }
  catch (std::exception e) {
    //std::cout << "Exception when checking status of " << path << std::endl;
    return NOT_FOUND;
  }
  if (fs::is_regular_file(status))
      return FILE;
  if (fs::is_directory(status))
      return DIRECTORY;
  if (fs::exists(status)) {
      //std::cout << path << " exists but isn't a directory or a file!" << std::endl;
      return NOT_FOUND;
  }

  //std::cout << path << " does not exist!" << std::endl;
  return NOT_FOUND;
  /*
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
  */
}

std::vector<std::string> FileUtil::list_directory(std::string path) {
	std::vector<std::string> r;
	for (auto& p : fs::directory_iterator(path)) {
		r.push_back(p.path().filename().string());
	}

	return r;
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
      std::cout << path << " does not exist!" << std::endl;
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
