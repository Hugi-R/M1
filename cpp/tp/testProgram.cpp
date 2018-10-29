#include <iostream>
#include <sstream>

#include "program.hpp"

int main(/*int argc, char const *argv[]*/)
{
    std::istringstream iss("(4*2+3*6)/13;\n 8*9-1 \n 3+1");
    Program p(iss);
    double res = p.eval(std::cout);
    std::cout << "--------" << std::endl;
    std::cout << "Program result : " << res << std::endl;
    return 0;
}
