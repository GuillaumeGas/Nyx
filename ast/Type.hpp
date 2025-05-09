
#pragma once

#include <iostream>

#define DllExport __declspec(dllexport)

namespace nyx {
    namespace ast {
        enum TYPE {
            INT,
            CHAR,
            BOOL,
            FLOAT,
            STRING,
            ARRAY,
            RANGE,
            PTR,
            _VOID,
            STRUCT,
            UNDEF,
            ERR
        };

        class DllExport Type {
        public:
            Type(const Type& type);
            Type(std::string name);
            Type(std::string name, bool is_basic);
            ~Type();

            void setType(std::string name, bool is_basic = true);
            void setBasic(bool val);
            std::string toString() const;
            bool isBasic() const;

            TYPE value;
            std::string name;
            bool is_basic;

        private:
            TYPE getValue() const;
        };

    };
};
