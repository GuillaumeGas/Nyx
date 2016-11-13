#include "Global.hpp"

using namespace std;
using namespace nyx;

Global * Global::instance = NULL;

Global::Global() {}

Global * Global::get_instance() {
  if (instance == NULL) 
    instance = new Global;
  return instance;
}

void Global::set_file(string& file_name) {
  this->file_name = file_name;
}

void Global::add_line(string& line) {
  file_content.push_back(line);
}

string Global::get_line(unsigned int num) {
  if (num > file_content.size()) {
    cout << "[Error] Line not found !" << endl;
    exit(-1);
  }
  return file_content[num-1];
}

