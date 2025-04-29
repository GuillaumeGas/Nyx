#pragma once

#include <iostream>
#include <map>
#include <functional>
#include <vector>

#include "../ast/Expression.hpp"

#define DllExport __declspec(dllexport)

using namespace std;

namespace nyx
{
    class DllExport SyscallsInterface
    {
    public:
        ast::ExpressionPtr execute(string, vector<ast::ExpressionPtr>* params);

    protected:
        map<string, function<ast::ExpressionPtr(vector<ast::ExpressionPtr>*)>> _syscalls;

        void addSyscall(string name, function<ast::ExpressionPtr(vector<ast::ExpressionPtr>*)> fun);
    };
};