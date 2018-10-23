#include <iostream>

#include "expr.hpp"

int main(/*int argc, char const *argv[]*/)
{
    /*std::cout << "eval 17-24 / 4 *3 +2 = ";
    Expr expr1("17-24 / 4 *3 +2");
    std::cout << expr1.eval() << std::endl;

    std::cout << "\neval 17+24 * 4 /3 -2 = ";
    Expr expr2("17+24 * 4 /3 -2");
    std::cout << expr2.eval() << std::endl;

    std::cout << "\neval 17+((24 * 4) /3) -2 = ";
    Expr expr3("17+(24 * 4) /3 -2");
    std::cout << expr3.eval() << std::endl;*/
    Expr expr("(3)");
    for(auto s : expr.split("(3)", '('))
        std::cout << s << std::endl;
    return 0;
}
