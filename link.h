#pragma once
#include <string>
#include <vector>
#include "directory.h"
#include "node.h"

class VFS;

class VirtualVirtualLink : public Node{
  Directory* vfs;
  std::vector<std::string> path;
public:
  VirtualVirtualLink(Directory* vfs, std::vector<std::string> path);
  Node* add_to_vdir(VirtualDirectory* dir, std::string name);
  Node* add_to_dir(RealDirectory* dir, std::string name);
  Node* resolve();
  File* resolve_file();
  Directory* resolve_dir();
  bool assign(Node* n);
};

class VirtualRealLink : public Node{
  std::string path;
public:
  VirtualRealLink(std::string path);
  Node* add_to_vdir(VirtualDirectory* dir, std::string name);
  Node* add_to_dir(RealDirectory* dir, std::string name);
  Node* resolve();
};
