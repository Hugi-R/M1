//
// Created by Mathias Paulin on 17/10/2017.
//
#ifndef POACPP_PROGRAM_HEADER__
#define POACPP_PROGRAM_HEADER__

#include <list>
#include<map>

#include "tokenstream.h"

class Program {
public:

    class Error {
    public :
        explicit Error(const std::string &error) : message("Program error : " + error) {}

        const char *what() const { return message.c_str(); }

    private :
        std::string message;
    };

    /// Construct an expression from a TokenStream.
    explicit Program(TokenStream &ts);

    ///  Prints the internal representation of the expression.
    void print() const;

    /// Returns the value of the expression.
    double eval(bool donotprint=false);

    void dump_memory();

    void setTokenStream(TokenStream &ts);
private:

    void tokenize(TokenStream &ts);

    void parse();

private:

    // Calculator memory - may be pre-filled
    std::map<std::string, double> _memory {
//            {"pi",    3.1415926535897932385},
//            {"e",     2.7182818284590452354},
//            {"sqrt2", 1.414213562373095}
    };

    // Program representations.
    std::list<Token> _infix;
    std::list<Token> _rpn;
};

#endif // POACPP_PROGRAM_HEADER__
