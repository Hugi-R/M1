#include <iostream>

#include "program.hpp"

int main(/*int argc, char const *argv[]*/)
{
    Program p(std::cin);
    double res = p.eval(std::cout);
    std::cout << "--------" << std::endl;
    std::cout << "Program result : " << res << std::endl;
    std::cout << "--------" << std::endl;
    std::cout << "Memory :" << std::endl;
    for(auto pair : p.variables){
        std::cout << std::get<0>(pair) << " = " << std::get<1>(pair) << std::endl;
    }
    return 0;
}
