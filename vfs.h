#pragma once
#include "directory.h"
#include "link.h"
#include <stack>
#include <vector>

extern std::vector<Node*> dynamic_nodes;
extern std::stack<Node*> temp_directory_stack;

class VFS : public VirtualDirectory{
private:
  std::stack<Node*> directory_stack;
  VirtualRealLink* real_link = nullptr;
  int ref_count = 0;
public:
  static VirtualDirectory global;
  static void inc_ref(VFS* vfs);
  static void dec_ref(VFS* vfs);
  VFS(std::string real_parent_dir);
  VFS(std::stack<Node*> directory_stack);
  Node* get_child(std::string name);
  void fill_stack(std::stack<Node*> &stack);

  void move(std::string to, std::string from);
  void set_string(std::string path, std::string val);
  std::string get_string(std::string path);
  void set(std::string, Node* n);
  void link(std::string path, std::string link);
  void out(std::string path);

  static std::vector<std::string> split_path(std::string path);

};
