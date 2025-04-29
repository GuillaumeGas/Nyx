#pragma once

#include <iostream>
#include <map>
#include <functional>
#include <vector>

#include "ast/Expression.hpp"

using namespace std;

namespace nyx
{
    class SyscallsInterface
    {
    public:
        ast::ExpressionPtr execute(string, vector<ast::ExpressionPtr>* params);

    protected:
        map<string, function<ast::ExpressionPtr(vector<ast::ExpressionPtr>*)>> _syscalls;
    };
};