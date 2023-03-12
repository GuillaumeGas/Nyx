#include "Global.hpp"

using namespace std;
using namespace nyx;

Global* Global::instance = NULL;

Global::Global()
{
    instance = nullptr;
}

Global* Global::getInstance() {
    if (instance == NULL)
        instance = new Global;
    return instance;
}

void Global::release()
{
    if (instance)
        delete instance;
    instance = nullptr;
}

void Global::setFile(string& file_name) {
    this->file_name = file_name;
}

void Global::addLine(string& line) {
    file_content.push_back(line);
}

string Global::getLine(unsigned int num) {
    if (num > file_content.size()) {
        cout << "[Error] Line not found !" << endl;
        exit(-1);
    }
    return file_content[num - 1];
}

