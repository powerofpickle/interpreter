#include "program.h"
#include <stack>
#include <string>
#include <vector>
#include "file.h"

// ^, .., and args
void Program::init_vfs(Directory* caller, std::stack<Node*> stack, std::vector<Node*> args){
  vfs = new VFS(stack);
  VirtualVirtualLink vvl(caller, std::vector<std::string>());
  vfs->set_child("^", &vvl);
  vfs->set_string("args/return", "");
  for(int i = 0; i < args.size(); i++){
    vfs->set("args/" + std::to_string(i), args[i]);
  }

  VirtualVirtualLink global_link(&VFS::global, std::vector<std::string>());
  vfs->set("global", &global_link);
}
