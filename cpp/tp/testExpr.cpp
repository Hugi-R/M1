#include <iostream>

#include "expr.hpp"

int main(/*int argc, char const *argv[]*/)
{
    std::vector<std::string> exprs = {
        "0",
        "(1)",
        "((1) - (2))",
        "-2",
        "(-3)",
        "1.2",
        "1.2-1",
        "-2.2",
        "(-3.2)",
        "17-24 / 4 *3 +2",
        "17+24 * 4 /3 -2",
        "17+((24 * 4)- 3) -2"
    };
    std::vector<double> results = {
        0,
        1,
        -1,
        -2,
        -3,
        1.2,
        1.2-1,
        -2.2,
        -3.2,
        13,
        47,
        108
    };

    for(uint i = 0; i < exprs.size(); ++i){
        Expr expr1(exprs[i]);
        double res = expr1.eval();
        std::cout << ((res == results[i] && expr1.toString() == exprs[i]) ? "OK" : "KO") << "   " << exprs[i] << " = " << res
        << " and \"" << exprs[i] << "\" = \"" << expr1.toString() << "\"" << std::endl;
    }
    return 0;
}
