#include "vfs.h"
#include "link.h"
#include <iostream>

std::vector<Node*> dynamic_nodes;
std::stack<Node*> temp_directory_stack;

VirtualDirectory VFS::global;

void VFS::inc_ref(VFS* vfs) {
  vfs->ref_count++;
}

void VFS::dec_ref(VFS* vfs) {
  vfs->ref_count--;
  if (vfs->ref_count == 0) {
    std::cout << "Deallocating VFS" << std::endl;
  }
}


VFS::VFS(std::string real_parent_dir){
  real_link = new VirtualRealLink(real_parent_dir);
  this->directory_stack.push(real_link);
}

VFS::VFS(std::stack<Node*> directory_stack){
  this->directory_stack = directory_stack;
}

/*
Updates directory history
Tries to get node from self
If it fails, tries global directory
*/

Node* VFS::get_child(std::string name){
  Node* n = VirtualDirectory::get_child(name);

  if(n == nullptr){
    n = global.get_child(name);
  }

  return n;
}


void VFS::fill_stack(std::stack<Node*> &stack){
  stack = directory_stack;
}

void VFS::move(std::string to, std::string from){
  set_node(split_path(to), get_node(split_path(from)));
}

void VFS::set_string(std::string path, std::string value){
  VirtualFile vf(value);
  set_node(split_path(path), &vf);
}

std::string VFS::get_string(std::string path){
  Node* n = get_node(split_path(path));
  if(n == nullptr){
    return "";
  }
  return ((File*)n)->get();
}

void VFS::set(std::string path, Node* n){
  set_node(split_path(path), n);
}

void VFS::link(std::string path, std::string link){
  VirtualVirtualLink vvl(this, split_path(link));
  set_node(split_path(path), &vvl);
}

void VFS::out(std::string path){
  Node* n = get_node(split_path(path));

  if(n == nullptr){
    std::cout << "Doesn't exist!" << std::endl;
    return;
  }
  n = n->resolve();
  if(n->is_dir()){
    ((Directory*)n)->print_tree(0, 1, false);
  }else{
    std::cout << (((File*)n)->get()) << std::endl;
  }
}

std::vector<std::string> VFS::split_path(std::string path){
  std::vector<std::string> r;
  if(path[0] == '/')
    r.push_back("/");

  int i;
  for(i = 0; i < path.size(); i++){
    if(path[i] == '/'){
      if(i != 0)
        r.push_back(path.substr(0,i));
      path = path.substr(i+1, path.size());
      i = -1;
    }
  }
  if(i != 0)
    r.push_back(path);

  return r;
}
