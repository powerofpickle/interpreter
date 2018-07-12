#include "directory.h"
#include "file.h"
#include "file_util.h"
#include "vfs.h"
#include <iostream>
#include <filesystem>
#include <fstream>

#include <sys/types.h>
#include <sys/stat.h>

namespace fs = std::filesystem;

void Directory::print_children_names(){
  std::vector<std::string> names = list_children_names();
  for(std::string name : names){
    std::cout << name << std::endl;
  }
}

void Directory::print_tree(int spaces, int max_levels, bool values){
  std::vector<std::string> names = list_children_names();
  for(std::string name : names){
    Node* n = get_child(name);
    if(n == nullptr)
      continue;
    n = n->resolve();
    for(int i = 0; i < spaces*2; i++){
      std::cout << " ";
    }
    std::cout << "- " << name;
    if(max_levels > 1 && n->is_dir()){
      std::cout << std::endl;
      ((Directory*)n)->print_tree(spaces+1, max_levels-1, values);
    }else if(values){
      std::cout << " : " << ((File*)n)->get() << std::endl;
    }else{
      std::cout << std::endl;
    }
  }
}

void Directory::set_child_string(std::string name, std::string value){
  VirtualFile* vf = new VirtualFile(value);
  this->set_child(name, vf);
  delete vf;
}

bool Directory::is_dir(){
  return true;
}

int Directory::num_children(){
  return -1;
}

Node* Directory::get_node(std::vector<std::string> path){

  std::stack<Node*> stack;
  Node* n = this;
  int i;
  for(i = 0; i < path.size(); i++){
    if(path[i] == ".."){
      if(stack.empty()){
        ((Directory*)n)->fill_stack(stack);
      }
      n = stack.top();
      stack.pop();
    }else if(path[i] == "."){
      n = this;
    }else{
      stack.push(n);

      n = ((Directory*)n)->get_child(path[i]);
    }

    if(n == nullptr){
      std::cout << "Error: " << path[i] << " not found!" << std::endl;
      break;
    }
    if(i < (path.size() - 1)){
      n = n->resolve();
      if(n->is_dir() == false){
        std::cout << "Error: " << path[i] << " is not a directory!" << std::endl;
      }
    }
  }

  return n;

/*
  if(path == ".."){
    if()
  }else if(path == "."){

  }
  Node* n = get_child(path[0]);
  if(n == nullptr){
    std::cout << "Node " << path[0] << " does not exist!" << std::endl;
    return nullptr;
  }

  if(path.size() == 1){
    return n;
  }

  n = n->resolve();

  if(n->is_dir()){
    return ((Directory*)n)->get_node(std::vector<std::string>(path.begin()+1, path.end()));
  }else{
    std::cout << "Node " << path[0] << " is not a directory!" << std::endl;
    return nullptr;
  }
*/
}

void Directory::fill_stack(std::stack<Node*> &stack){
  std::cout << "Error: fill_stack() called from Directory base class!" << std::endl;
}

Node* Directory::set_node(std::vector<std::string> path, Node* node){

  std::stack<Node*> stack;
  Node* n = this;
  int i;
  for(i = 0; i < path.size() - 1; i++){
    Node* prev = n;
    if(path[i] == ".."){
      if(stack.empty()){
        ((Directory*)n)->fill_stack(stack);
      }
      n = stack.top();
      stack.pop();
    }else if(path[i] == "."){
      n = this;
    }else{
      stack.push(n);
      n = ((Directory*)n)->get_child(path[i]);
    }
    if(n == nullptr){
      VirtualDirectory vd;
      n = ((Directory*)prev)->set_child(path[i], &vd);
    }
    n = n->resolve();
    if(n->is_dir() == false){
      std::cout << "Error: " << path[i] << " is not a directory!" << std::endl;
    }
  }
  Node* existing = ((Directory*)n)->get_child(path[i]);
  if(existing != nullptr && (existing->assign(node) == false)){
    return existing->resolve();
  }
  return ((Directory*)n)->set_child(path[i], node);

/*
  if(path.size() == 1){
    return set_child(path[0], node);
  }

  temp_directory_stack.push(this);

  Node* n = get_child(path[0]);
  if(n == nullptr){
    VirtualDirectory vd;
    return ((Directory*)set_child(path[0], &vd))->set_node(std::vector<std::string>(path.begin()+1, path.end()), node);
  }

  n = n->resolve();

  if(n->is_dir()){
    return ((Directory*)n)->set_node(std::vector<std::string>(path.begin()+1, path.end()), node);
  }else{
    std::cout << "Node " << path[0] << " is not a directory!" << std::endl;
    return nullptr;
  }
*/
}

//VirtualDirectory
int VirtualDirectory::num_children(){
  return children.size();
}

std::vector<std::string> VirtualDirectory::list_children_names(){
  std::vector<std::string> r;
  for( const auto& pair : children ){
    r.push_back(pair.first);
  }
  return r;
}


Node* VirtualDirectory::set_child(std::string name, Node* node){
  Node* n = get_child(name);
  if(n != nullptr){
    delete n;
  }
  return node->add_to_vdir(this, name);
}

Node* VirtualDirectory::get_child(std::string name){
  if(children.find(name) == children.end())
    return nullptr;
  return children[name];
}



Node* VirtualDirectory::add_to_vdir(VirtualDirectory* dir, std::string name){
  VirtualDirectory* copy = new VirtualDirectory();
  for( const auto& pair : children ){
    copy->set_child(pair.first, pair.second);
  }
  dir->children[name] = copy;
  return copy;
}

Node* VirtualDirectory::add_to_dir(RealDirectory* dir, std::string name){
  return nullptr;
}

//RealDirectory
RealDirectory::RealDirectory(std::string path){
  this->path = path;

}

std::string RealDirectory::type(){
  return "RealDirectory";
}

std::vector<std::string> RealDirectory::list_children_names(){
  std::vector<std::string> r;
  for (auto& p : fs::directory_iterator(this->path)){
    r.push_back(p.path().filename().string());
  }

  return r;
}


Node* RealDirectory::set_child(std::string name, Node* node){
  return node->add_to_dir(this, name);
}

Node* RealDirectory::get_child(std::string name){
  std::string new_path = path + "/" + name;

  return FileUtil::node_at(new_path);
}

Node* RealDirectory::add_to_vdir(VirtualDirectory* dir, std::string name){
  return nullptr;
}


Node* RealDirectory::add_to_dir(RealDirectory* dir, std::string name){
  return nullptr;
}

void RealDirectory::fill_stack(std::stack<Node*> &stack){
  std::cout << "RealDirectory filling stack!" << std::endl;
  stack.push(FileUtil::node_at(path + "/.."));
}

/*
Node* RealDirectory::get_node(std::vector<std::string> path){
  std::cout << "GOT CALLED!" << std::endl;

  if(path.size() == 0){
    return this;
  }
  std::string joined_path = path[0];
  for(int i = 1; i < path.size(); i++){
    joined_path += "/" + path[i];
  }
  std::cout << joined_path << std::endl;
  return get_child(joined_path);
}
*/
