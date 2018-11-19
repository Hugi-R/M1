/*
 * Master Informatique - Programmation C++
 * Phase 2
 *
 */

#include "tokenstream.h"
#include "program.h"

#include <sstream>


int main(int argc, char *argv[]) {

    std::string test_expr[]{
            "17-24/4*3+2;",
            "(4*2+3*6)/13;\n8*9-1\n3+1",
            "deuxpi = 2 * 3.1415926536;\nrayon = 3*8;\ncirconference = deuxpi * rayon;\ncirconference",
            "pi = 3.1415926536;\ncos(pi)\ncos(2*pi)\nsin(pi)\ntan(pi)\nlerp(0,1,1)\nhypot(1,1)",
            "sqrt(pow(2,2))\nlog(exp(3))",
            "x = 1;\npolynome(3,1,2,3,x)",
            "x = 2;\npolynome(4,0,0,0,1,x)",
            "x = 2;\nsqrt(y=2;pow(x,y))" // si si ça marche
    };
    constexpr auto num_test = std::extent<decltype(test_expr)>::value;

    // Input token stream
    TokenStream ts{std::cin};


    switch (argc) {
        case 1:
            std::cout << "Enter your expression (<Ctrl-D> to terminate) : " << std::endl;
            break;
        case 2: {
                auto nt = decltype(num_test)(std::atoi(argv[1]));
                if (nt < num_test) {
                    std::cout << "----------------" << std::endl << "Executing test " << nt << " : " << std::endl
                              << test_expr[nt]
                              << std::endl << "----------------" << std::endl;
                    ts.setInput(new std::istringstream{test_expr[nt]});
                } else {
                    std::cout << "Test " << nt << " unavailable !" << std::endl;
                    return 1;
                }
            }
            break;
        default:
            std::cerr << "Too many arguments !" << std::endl;
            return 1;
    }

    try {
        Program prog{ts};

        std::cout <<  "----------------" << std::endl;

        // Evaluate the program
        double result = prog.eval();

        std::cout <<  "----------------" << std::endl << "Program result is " << result << std::endl;

        std::cout << "----------------" << std::endl;
        prog.dump_memory();

    } catch (const TokenStream::Error &e) {
        std::cerr << e.what() << std::endl;
    } catch (const Program::Error &e) {
        std::cerr << e.what() << std::endl;
    } catch (const ProgFunction::Error &e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
