#include <iostream>
#include <sstream>

#include "program.hpp"

int main(/*int argc, char const *argv[]*/)
{
    std::istringstream iss1("(4*2+3*6)/13;\n 8*9-1 \n 3+1");
    Program p1(iss1);
    double res = p1.eval(std::cout);
    std::cout << "--------" << std::endl;
    std::cout << "Program result : " << res << std::endl;

    std::istringstream iss2("a = 3;\n 8*9-1 \n a+1");
    Program p2(iss2);
    res = p2.eval(std::cout);
    std::cout << "--------" << std::endl;
    std::cout << "Program result : " << res << std::endl;
    return 0;
}
