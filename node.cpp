#include "node.h"

std::string Node::type(){
  return "Node";
}

bool Node::is_dir(){
  return false;
}


Node* Node::resolve(){
  return this;
}

//returns true if should be deleted and replaced
bool Node::assign(Node* n){
  return true;
}
