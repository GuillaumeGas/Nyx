#include "SyscallsInterface.hpp"

#include "../ast/Expression.hpp"
#include "../ast/exceptions/SemanticException.hpp"

using namespace std;
using namespace nyx;
using namespace ast;

void SyscallsInterface::addSyscall(string name, function<ExpressionPtr(vector<ExpressionPtr>*)> fun)
{
    _syscalls[name] = fun;
}

ExpressionPtr SyscallsInterface::execute(string syscallName, vector<ExpressionPtr> * params)
{
    if (_syscalls.find(syscallName) != _syscalls.end())
        return _syscalls[syscallName](params);
    
    throw SemanticErrorException("Unknown syscall !");
}