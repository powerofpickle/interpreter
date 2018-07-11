#pragma once
#include <string>

class VirtualDirectory;
class RealDirectory;

class Node{

public:
  virtual std::string type();
  virtual bool is_dir();
  virtual Node* add_to_vdir(VirtualDirectory* dir, std::string name)=0;
  virtual Node* add_to_dir(RealDirectory* dir, std::string name)=0;
  virtual Node* resolve();
};
