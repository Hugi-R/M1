// Hugo Roussel

#ifndef PROG_FUNCTION_H
#define PROG_FUNCTION_H
#include <string>
#include <vector>

//#include "tokenstream.h"//cyclic dependency
//forward declaration :
class Token;


class ProgFunction {
public:
    class Error {
    public:
        explicit Error(const std::string &error) : message("ProgramFunction error : " + error) {}

        const char *what() const { return message.c_str(); }

    private:
        std::string message;
    };

    ProgFunction(std::string args);

    
    static double parse(std::string s);
    //static double parse(TokenStream ts);

    private:
    std::vector<Token> _args;
};

#endif //PROG_FUNCTION_H
