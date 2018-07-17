#pragma once
#include "directory.h"

class HTTPNode : public Directory{
private:
	std::string path;
public:
	HTTPNode();
	HTTPNode(std::string path);
	File* resolve_file();
	Node* resolve();
	Node* add_to_vdir(VirtualDirectory* dir, std::string name);
	Node* get_child(std::string name);

};


