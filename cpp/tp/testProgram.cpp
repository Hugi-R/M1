#include <iostream>
#include <sstream>

#include "program.hpp"

int main(/*int argc, char const *argv[]*/)
{
    std::cout << "\nTest 1" << std::endl;
    std::istringstream iss1("(4*2+3*6)/13;\n 8*9-1 \n 3+1");
    Program p1(iss1);
    double res = p1.eval(std::cout);
    std::cout << "--------" << std::endl;
    std::cout << "Program result : " << res << std::endl;
    std::cout << "--------" << std::endl;
    std::cout << "Memory :" << std::endl;
    for(auto pair : p1.variables){
        std::cout << std::get<0>(pair) << " = " << std::get<1>(pair) << std::endl;
    }

    std::cout << "\nTest 2" << std::endl;
    std::istringstream iss2("deuxpi = 2 * 3.1415926536;\nrayon = 3*8;\ncirconference = deuxpi * rayon;\ncirconference\n");
    Program p2(iss2);
    res = p2.eval(std::cout);
    std::cout << "--------" << std::endl;
    std::cout << "Program result : " << res << std::endl;
    std::cout << "--------" << std::endl;
    std::cout << "Memory :" << std::endl;
    for(auto pair : p2.variables){
        std::cout << std::get<0>(pair) << " = " << std::get<1>(pair) << std::endl;
    }
    return 0;
}
