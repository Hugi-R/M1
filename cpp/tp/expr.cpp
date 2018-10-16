#include <iostream>
#include <stack>

#include "expr.hpp"


std::vector<std::string> split ( const std::string& s, char delim ){
    std::vector<std::string> res;
    std::string buff{""};
    for(char c : s){
        if(c == delim){
            res.push_back(buff);
            buff = "";
        } else {
            buff.push_back(c);
        }
    }
    res.push_back(buff);
    return res;
}

Expr::ExprToken toToken( const std::string& s ){
    double num = 0;
    Expr::Kind kind;
    if( s == "+" || s == "-" || s == "*" || s == "/"){
        kind = Expr::Kind::op;
    } else {
        num = std::stod(s);
        kind = Expr::Kind::num;
    }
    Expr::ExprToken res{kind, num, s};
    return res;
}

std::stack<Expr::ExprToken> rpn( const std::vector<std::string>& toks ){
    std::stack<Expr::ExprToken> res;
    Expr::Kind expected{Expr::Kind::num};
    for(std::string s : toks){
        auto tok = toToken(s);
        //TODO try catch ?
        if(tok.kind == expected){
            //TODO
        } else {
            //TODO throw
        }
    }
}

void printTok(Expr::ExprToken tok){
    std::cout << tok.kind << "; " << tok.num << "; " << tok.value << std::endl;
}

int main(){
    for(std::string s: split("1 + 2 * 3 / 4", '+'))
        std::cout << s << std::endl;
    printTok( toToken("+"));
    printTok( toToken("-"));
    printTok( toToken("*"));
    printTok( toToken("/"));
    printTok( toToken("0"));
    printTok( toToken("100"));
    printTok( toToken("v"));
    return 0;
}
