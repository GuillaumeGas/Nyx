
#pragma once

#include <iostream>

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
            UNDEF,
            ERR
        };

        class Type {
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
