#include "link.h"
#include "node.h"
#include "directory.h"
#include "file_util.h"
#include "vfs.h"
#include <string>
#include <iostream>

//VirtualVirtualLink

VirtualVirtualLink::VirtualVirtualLink(Directory* vfs, std::vector<std::string> path){
  this->vfs = vfs;
  this->path = path;
}

Node* VirtualVirtualLink::add_to_vdir(VirtualDirectory* dir, std::string name){
  VirtualVirtualLink* copy = new VirtualVirtualLink(this->vfs, this->path);
  dir->children[name] = copy;
  return copy;
}

Node* VirtualVirtualLink::add_to_dir(RealDirectory* dir, std::string name){
  return nullptr;
}

Node* VirtualVirtualLink::resolve(){
  Node* r = vfs->get_node(path);
  return r;
}

bool VirtualVirtualLink::assign(Node* n){
  vfs->set_node(path, n);
  return false;
}

//VirtualRealLink
VirtualRealLink::VirtualRealLink(std::string path){
  this->path = path;
}


Node* VirtualRealLink::add_to_vdir(VirtualDirectory* dir, std::string name){
  VirtualRealLink* copy = new VirtualRealLink(path);
  dir->children[name] = copy;
  return copy;
}

Node* VirtualRealLink::add_to_dir(RealDirectory* dir, std::string name){
  return nullptr;
}

Node* VirtualRealLink::resolve(){
  Node* r = nullptr;

  int file_stat = FileUtil::path_status(path);
  switch(file_stat){
    case FileUtil::NOT_FOUND:
      std::cout << "ERROR: Could not resolve link to " << path << std::endl;
      break;
    case FileUtil::FILE:
      r = new RealFile(path);
      break;
    case FileUtil::DIRECTORY:
      r = new RealDirectory(path);
      break;
  }
  return r;
}
