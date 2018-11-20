//
// Created by Mathias Paulin on 17/10/2017.
// Modified by Hugo Roussel.
//
#include "tokenstream.h"
#include <sstream>  // String stream


/// Returns true if the token is a litteral.
bool Token::isLiteral() const {
    return kind == Kind::number;
}

bool Token::isIdentifier() const {
    return kind == Kind::name;
}

/// Returns true if the token is a litteral.
bool Token::isOperator() const {
    return (kind == Kind::plus) || (kind == Kind::minus) || (kind == Kind::mul) || (kind == Kind::div);
}

/// Returns true if the token is a separator (\n, ;, next or end).
bool Token::isSeparator() const {
    return (kind == Kind::end) || (kind == Kind::print) || (kind == Kind::next);
}

bool Token::isFunction() const {
    return kind == Kind::fct;
}

bool Token::isAssign() const {
    return kind == Kind::assign;
}

double Token::eval(Program &p) const{
    if(isAssign())
        return fct->eval(p);
    return number_value;
}


int Token::compare(const Token &other) const {
    if (kind == Kind::minus || kind == Kind::plus)
        if (other.kind == Kind::mul || other.kind == Kind::div)
            return -1;
        else
            return 0;
    else if (other.kind == Kind::minus || other.kind == Kind::plus)
        return 1;
    else
        return 0;
}


std::ostream &operator<<(std::ostream &os, const Token &t) {
    switch (t.kind) {
        case Kind::name :
            os << t.string_value << ' ';
            break;
        case Kind::number :
            os << t.number_value << ' ';
            break;
        case Kind::end :
        case Kind::print :
            os << std::endl;
            break;
        case Kind::next :
            os << static_cast<char>(t.kind);
            break;
        case Kind::assign:
            os << t.string_value << '=' << ' ';
            break;
        case Kind::plus:
        case Kind::minus:
        case Kind::mul:
        case Kind::div:
        case Kind::lp:
        case Kind::rp:
            os << static_cast<char>(t.kind) << ' ';
            break;
        case Kind::fct:
            os << t.string_value << ' ';
            break;
        default:
            throw TokenStream::Error("Undefined Token ");
    }
    return os;
}

double Token::operate(double a1, double a2) const {
    switch (kind) {
        case Kind::plus:
            return a1 + a2;
        case Kind::minus:
            return a1 - a2;
        case Kind::mul:
            return a1 * a2;
        case Kind::div:
            return a1 / a2;
        default:
            throw TokenStream::Error("Bad operator  -- " + string_value);
    }
}

Token TokenStream::get() {
    char ch{0};

    do {
        if (!ip->get(ch))
            return ct = {Kind::end};
    } while (ch != '\n' && std::isspace(ch));

    switch (ch) {
        case ';':
            return ct = {Kind::next};
        case '\n':
            return ct = {Kind::print};
        case '*': case '/':
        case '+': case '-':
        case '(': case ')':
        case '=':
            return ct = {static_cast<Kind>(ch)};
        case '0': case '1': case '2': case '3': case '4': case '5': case '6': case '7': case '8': case '9':
        case '.':
            // put the first digit (or .) back into the input stream
            ip->putback(ch);
            // read the number into ct
            *ip >> ct.number_value;
            ct.kind = Kind::number;
            return ct;
        default:
            // name, name =, or error
            // name can be a function : name(a[,b,...])
            if (std::isalpha(ch)) {
                ct.string_value = {ch};
                ct.kind = Kind::name;
                while (ip->get(ch) && std::isalnum(ch)){
                    ct.string_value += ch;
                }
                while(std::isspace(ch)) ip->get(ch);
                //token is function :
                if(ch == '('){
                    ct.kind = Kind::fct;
                    ct.string_value += ch;
                    int parenthesisLevel = 0;
                    bool good = false;
                    while(ip->get(ch) && !good){
                        ct.string_value += ch;
                        if(ch == ')'){
                            if(parenthesisLevel == 0)
                                good = true;
                            else
                                parenthesisLevel -= 1;
                        } else if(ch == '(') {
                            parenthesisLevel += 1;
                        }
                    }
                    if(!good)
                        throw TokenStream::Error("Missing ')' in "+ct.string_value);
                    ct.fct = std::make_shared<ProgFunction>(ct);
                }
                if(ch != ')') ip->putback(ch);
                return ct;
            } else {
                ip->putback(ch);
                std::stringstream error;
                error << "Bad Token (" << ch << ")";
                throw TokenStream::Error(error.str());
            }
    }
}
