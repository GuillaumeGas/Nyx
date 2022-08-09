#pragma once

#include <iostream>
#include <vector>

namespace nyx {
    class FileInfo {
    public:
        FileInfo(std::string fileName);

        std::string getFileName() const;
        void addLine(std::string& line);
        std::string getLine(unsigned int num) const;

    private:
        std::string _fileName;
        std::vector<std::string> _fileContent;
    };
};
