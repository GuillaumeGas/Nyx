#pragma once

#include <iostream>
#include <vector>

namespace nyx {
  class Global {
  public:
    static Global * get_instance();

    void set_file(std::string& file_name);
    void add_line(std::string& line);
    std::string get_line(unsigned int num);

    std::string file_name;
    std::vector<std::string> file_content;

  private:
    Global();
    static Global * instance;
  };
};
