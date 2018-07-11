#pragma once
#include <vector>
#include "file.h"
#include "node.h"
#include <string>
#include <map>
#include <stack>

class Directory : public Node{
public:
  virtual std::vector<std::string> list_children_names()=0;
  void print_children_names();
  void print_tree(int spaces, int max_levels, bool values);
  void set_child_string(std::string name, std::string value);
  virtual Node* set_child(std::string name, Node* node)=0;
  virtual Node* get_child(std::string name)=0;

  virtual Node* add_to_vdir(VirtualDirectory* dir, std::string name)=0;
  virtual Node* add_to_dir(RealDirectory* dir, std::string name)=0;

  virtual Node* get_node(std::vector<std::string> path);
  virtual Node* set_node(std::vector<std::string> path, Node* node);

  virtual void fill_stack(std::stack<Node*> &stack);
  bool is_dir();
};

class VirtualDirectory : public Directory{
private:
public:
  std::map<std::string, Node*> children;
  std::vector<std::string> list_children_names();
  Node* set_child(std::string name, Node* node);
  Node* get_child(std::string name);
  Node* add_to_vdir(VirtualDirectory* dir, std::string name);
  Node* add_to_dir(RealDirectory* dir, std::string name);

};

class RealDirectory : public Directory{
private:
public:
  RealDirectory(std::string path);
  std::string type();
  std::string path;
  std::vector<std::string> list_children_names();
  Node* set_child(std::string name, Node* node);
  Node* get_child(std::string name);
  Node* add_to_vdir(VirtualDirectory* dir, std::string name);
  Node* add_to_dir(RealDirectory* dir, std::string name);
  void fill_stack(std::stack<Node*> &stack);

  //Node* get_node(std::vector<std::string> path);
};
