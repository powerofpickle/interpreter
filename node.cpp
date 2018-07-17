#include "node.h"
#include <iostream>

Node* Node::add_to_vdir(VirtualDirectory* dir, std::string name){
	std::cout << "This should not be called! [node.cpp]" << std::endl;
	return this;
}

Node* Node::add_to_dir(RealDirectory* dir, std::string name){
	std::cout << "This should not be called! [node.cpp]" << std::endl;
	return this;
}

std::string Node::type(){
  return "Node";
}

bool Node::is_dir(){
  return false;
}


Node* Node::resolve(){
  return this;
}

Directory* Node::resolve_dir(){
  std::cout << "Error: Could not be resolved as directory!" << std::endl;
  return nullptr;
}

File* Node::resolve_file(){
  std::cout << "Error: Could not be resolved as file!" << std::endl;
  return nullptr;
}

//returns true if should be deleted and replaced
bool Node::assign(Node* n){
  return true;
}
