#include "file.h"
#include "directory.h"
#include "file_util.h"

bool File::is_dir(){
  return false;
}

//VirtualFile

VirtualFile::VirtualFile(){

}
VirtualFile::VirtualFile(std::string value){
  this->value = value;
}

std::string VirtualFile::get(){
  return this->value;

}

void VirtualFile::set(std::string val){
  this->value = val;
}

Node* VirtualFile::add_to_vdir(VirtualDirectory* vdir, std::string name){
  VirtualFile* vf = new VirtualFile(this->value);
  vdir->children[name] = vf;
  return vf;
}
Node* VirtualFile::add_to_dir(RealDirectory* vdir, std::string name){
  std::string path = vdir->path + "/" + name;
  FileUtil::write_file(path, this->value);
  return FileUtil::node_at(path);
}

//RealFile

RealFile::RealFile(std::string path){
  this->path = path;
}

std::string RealFile::get(){
  std::string r;
  FileUtil::read_file(this->path, r);
  return r;
}

void RealFile::set(std::string val){
  FileUtil::write_file(this->path, val);
}

Node* RealFile::add_to_vdir(VirtualDirectory* vdir, std::string name){
  VirtualFile* vf = new VirtualFile(this->get());
  vdir->children[name] = vf;
  return vf;
}
Node* RealFile::add_to_dir(RealDirectory* dir, std::string name){
  std::string get_val = this->get();
  std::string path = dir->path + "/" + name;
  FileUtil::write_file(path, get_val);
  return FileUtil::node_at(path);
}
