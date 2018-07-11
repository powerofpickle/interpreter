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
