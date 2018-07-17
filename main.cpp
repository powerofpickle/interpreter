#include <iostream>
#include "directory.h"
#include "file.h"
#include "vfs.h"
#include "file_util.h"
#include "program.h"
#include <string>
#include <vector>
#include "platform.h"
#include "http.h"

class Main : public Program{
public:
  void run(){
    vfs->out(vfs->get_string("args/0"));
  }
};


int main(int argc, char** argv){

  RealDirectory root(ROOT_PATH);
  VirtualVirtualLink root_link(&root, std::vector<std::string>());
  VFS::global.set_child("/", &root_link);

  HTTPNode http_node;
  VFS::global.set_child("http:", &http_node);

  std::vector<Node*> args;
  for(int i = 1; i < argc; i++){
    args.push_back(new VirtualFile(argv[i]));
  }

  RealDirectory pwd("/home/coleman/language");
  RealDirectory parent_dir("/home/coleman/language");

  std::stack<Node*> stack;
  stack.push(&parent_dir);

  Main main;
  main.init_vfs(&pwd, stack, args);
  main.run();
}
