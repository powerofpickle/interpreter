#include <iostream>
#include <string>
#include "node.h"
#include "http.h"
#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>


HTTPNode::HTTPNode(){
	this->path = "";
}

HTTPNode::HTTPNode(std::string path){
	this->path = path;
}

File* HTTPNode::resolve_file(){
	return new VirtualFile("This will be the page for " + this->path); 
}

Node* HTTPNode::resolve(){
	return resolve_file();
}

Node* HTTPNode::add_to_vdir(VirtualDirectory* dir, std::string name){
	HTTPNode* copy = new HTTPNode(this->path);
	dir->children[name] = copy;
	return copy;
}

Node* HTTPNode::get_child(std::string name){
	std::string new_path = this->path + name + "/";
	return new HTTPNode(new_path);
}
