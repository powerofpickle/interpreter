#pragma once
#include <string>
#include "node.h"

class Directory;

class File: public Node{
public:
  virtual std::string get()=0;
  virtual void set(std::string val)=0;

  virtual Node* add_to_vdir(VirtualDirectory* dir, std::string name)=0;
  virtual Node* add_to_dir(RealDirectory* dir, std::string name)=0;
  bool is_dir();
};

class VirtualFile : public File{
private:
  std::string value;

public:
  VirtualFile();
  VirtualFile(std::string value);
  std::string get();
  void set(std::string val);

  Node* add_to_vdir(VirtualDirectory* dir, std::string name);
  Node* add_to_dir(RealDirectory* dir, std::string name);
};

class RealFile : public File{
private:
  std::string path;
public:
  RealFile(std::string path);
  std::string get();
  void set(std::string val);

  Node* add_to_vdir(VirtualDirectory* dir, std::string name);
  Node* add_to_dir(RealDirectory* dir, std::string name);
};
