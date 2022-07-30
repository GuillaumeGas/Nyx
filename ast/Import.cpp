#include "Import.hpp"

using namespace std;
using namespace nyx;
using namespace ast;

Import::Import(vector<string>* path, Position* pos) : Declaration(pos) {
    this->path = path;
}

Import::~Import() {
    if (path)
        delete path;
}

void Import::interpret() {}

void Import::print(ostream& out, int offset) const {
    shift(out, offset);
    out << "<import ";
    for (int i = 0; i < path->size(); i++) {
        out << (*path)[i];
        if (i < path->size() - 1)
            out << ".";
    }
    out << ">";
}
