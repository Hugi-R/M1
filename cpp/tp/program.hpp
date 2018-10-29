#ifndef PROGRAM_HPP
#define PROGRAM_HPP 1
#include <istream>
#include <vector>

#include "expr.hpp"

class Program {
    public:
    Program(std::istream& in);
    void eval();

    private:
    std::vector<Expr> printed;
    std::vector<Expr> hidden;

    std::vector<std::string> splitProg (const std::string& s);
    void parse(std::string in);
};
#endif
