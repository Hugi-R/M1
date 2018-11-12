//
// Created by Mathias Paulin on 17/10/2017.
// Modified by Hugo Roussel.
//
#ifndef POACPP_TOKENSTREAM_HEADER__
#define POACPP_TOKENSTREAM_HEADER__
#include <iostream> // I/O


// The token system
// This demonstrate the use of enum class
// enum class (a scoped enumeration) is an enum where the enumerators are within the scope of the enumeration and
// no implicit conversions to other types are provided.
// by inherinting from char, we are able to cast a char to a Kind ...
enum class Kind : char {
    fct, name, number, end, next, print = ';',
    plus = '+', minus = '-', mul = '*', div = '/',
    assign = '=', lp = '(', rp = ')'
};

// Token of our calculator
struct Token {
    Kind kind;
    std::string string_value;
    double number_value;

    Token(const Kind &k, const std::string &s="", double v=0) : kind(k), string_value{s}, number_value(v) {};

    friend std::ostream &operator<<(std::ostream &os, const Token &t);

    /// Returns true if the token is a litteral.
    bool isLiteral() const;

    /// Returns true if the token is a litteral.
    bool isIdentifier() const;

    /// Returns true if the token is an operator.
    bool isOperator() const;

    /// Returns true if the token is a separator (\n, ;, next or end).
    bool isSeparator() const;

    /// Returns true if the token is a function.
    bool isFunction() const;

    /// Returns -1 if the given token has a higher priority, 1 if lower
    /// and 0 if they are the same.
    int compare(const Token &other) const;

    /// Evaluate the operator with given operands a1 and a2.
    /// (can only be used if it is an operator).
    double operate(double a1, double a2) const;

    /// Parse string_value into a function
    void parseFunction();
};


// Transform an input stream into a Token stream
class TokenStream {
public :

    class Error {
    public :
        explicit Error(const std::string &error) : message("TokenStream error : " + error) {}

        const char *what() const { return message.c_str(); }

    private :
        std::string message;
    };


    TokenStream(std::istream &s) : ip{&s}, owns{false} {}

    TokenStream(std::istream *p) : ip{p}, owns{true} {}

    ~TokenStream() {
        close();
    }

    Token get(); // read and return next token

    const Token &current() const { // most recently read token
        return ct;
    }

    void setInput(std::istream &s) {
        close();
        ip = &s;
        owns = false;
    }

    void setInput(std::istream *p) {
        close();
        ip = p;
        owns = true;
    }

private:
    void close() {
        if (owns)
            delete ip;
    }

    // pointer to an input stream
    std::istream *ip;
    // does the Token_stream own the istream?
    bool owns;
    // current token
    Token ct{Kind::end};
};

#endif // POACPP_TOKENSTREAM_HEADER__
