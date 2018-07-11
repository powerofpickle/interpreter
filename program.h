#pragma once
#include "vfs.h"
#include <stack>
#include <vector>

class Program{
public:
  VFS* vfs;
  void set_vfs(VFS* vfs);
  void init_vfs(Directory* caller, std::stack<Node*> stack, std::vector<Node*> args);
  virtual void run()=0;
};
