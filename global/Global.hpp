#pragma once

#include <iostream>
#include <vector>

namespace nyx {
    class Global {
    public:
        static Global* getInstance();

        void release();

        void setFile(std::string& file_name);
        void addLine(std::string& line);
        std::string getLine(unsigned int num);

        std::string file_name;
        std::vector<std::string> file_content;
        std::ostream * ostream;

    private:
        Global();
        static Global* instance;
    };
};
