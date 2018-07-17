#pragma once
#include <string>

class VirtualDirectory;
class RealDirectory;
class File;
class Directory;

class Node{

public:
  virtual std::string type();
  virtual bool is_dir();
  virtual Node* add_to_vdir(VirtualDirectory* dir, std::string name);
  virtual Node* add_to_dir(RealDirectory* dir, std::string name);
  virtual Node* resolve();
  virtual Directory* resolve_dir();
  virtual File* resolve_file();
  virtual bool assign(Node* n);
};
