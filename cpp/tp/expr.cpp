#include <iostream>
#include <stack>
#include <sstream>

// uncomment to disable assert()
// #define NDEBUG
#include <cassert>

#include "expr.hpp"

Expr::Expr( const std::string& str ){
    expr = rpn(toTokenVector(splitExpr(str)));
}
Expr::Expr( const char * str ){
    expr = rpn(toTokenVector(splitExpr(std::string(str))));
}

/* split a string by a delimiter, the delimiter is not removed and is added as a string */
std::vector<std::string> Expr::split ( const std::string& s, char delim ){
    std::vector<std::string> res;
    std::string buff{""};
    for(char c : s){
        if(c == delim){
            res.push_back(buff);
            res.push_back(std::string()+delim);
            buff = "";
        } else {
            buff.push_back(c);
        }
    }
    res.push_back(buff);
    return res;
}

Expr::ExprToken Expr::toToken( const std::string& s ){
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

Expr::ExprToken Expr::toToken( double x ){
    return Expr::ExprToken{Expr::Kind::num, x, std::string()};
}

/* return a valid vector of token */
std::vector<Expr::ExprToken> Expr::toTokenVector( const std::vector<std::string> vs ){
    std::vector<Expr::ExprToken> res;
    Expr::Kind expected{Expr::Kind::num};
    for(std::string s : vs){
        auto tok = toToken(s);
        if(tok.kind == expected){
            res.push_back(tok);
            if(expected == Expr::Kind::num)
                expected = Expr::Kind::op;
            else
                expected = Expr::Kind::num;
        } else {
            throw std::exception();
        }
    }

    if(expected != Expr::Kind::op){
        throw std::exception();
    }
    return res;
}

std::vector<std::string> Expr::splitExpr (const std::string& s){
    //remove space 
    std::string buff;
    for(char c : s){
        if(c != ' ')
            buff.push_back(c);
    }

    constexpr static char operators[4] = {'+', '-', '*', '/'};
    std::vector<std::string> res;
    res.push_back(buff);
    for(char delim : operators){
        std::vector<std::string> tmp;
        tmp.clear();
        for(std::string tok : res){
            std::vector<std::string> tmpsplit(split(tok, delim));
            tmp.insert(tmp.end(), tmpsplit.begin(), tmpsplit.end());
        }
        res = tmp;
    }
    return res;
}

bool Expr::isPriority (Expr::ExprToken tokA, Expr::ExprToken tokB){
    assert(tokA.kind == Expr::Kind::op && tokB.kind == Expr::Kind::op);
        if((tokA.value == "*" || tokA.value == "/" ) && (tokB.value == "+" || tokB.value == "-"))
            return true;
        return false;
}

double Expr::evaluate (Expr::ExprToken op, Expr::ExprToken valA, Expr::ExprToken valB){
    assert((op.kind == Expr::Kind::op) && (valA.kind == Expr::Kind::num) && (valB.kind == Expr::Kind::num));
    if(op.value == "*"){
        return valA.num * valB.num;
    } else if (op.value == "/"){
        return valA.num / valB.num;
    } else if (op.value == "+"){
        return valA.num + valB.num;
    } else if (op.value == "-"){
        return valA.num - valB.num;
    }
    throw std::exception();
}

std::vector<Expr::ExprToken> Expr::rpn( const std::vector<Expr::ExprToken>& toks ){
    std::vector<Expr::ExprToken> expr;
    std::stack<Expr::ExprToken> tmp;
    for(Expr::ExprToken tok : toks){
        if(tok.kind == Expr::Kind::num){
            expr.push_back(tok);
        } else {
            while(!tmp.empty() && isPriority(tmp.top(), tok)){
                expr.push_back(tmp.top());
                tmp.pop();
            }
            tmp.push(tok);
        }
    }
    while(!tmp.empty()){
        expr.push_back(tmp.top());
        tmp.pop();
    }
    return expr;
}

double Expr::eval(){
    /*for(auto tok : expr)
        printTok(tok);
    std::cout << std::endl;*/
    std::stack<Expr::ExprToken> res;
    for(auto it = expr.rbegin(); it != expr.rend(); ++it){
        auto tokA = *it;
        //printTok(tokA);
        if(tokA.kind == Expr::Kind::num){
            while(!res.empty() && res.top().kind == Expr::Kind::num){
                auto tokB = res.top();
                res.pop();
                auto op = res.top();
                res.pop();
                auto tok = toToken(evaluate(op, tokA, tokB));
                /*std::cout << "\nevaluate" << std::endl;
                printTok(tok);
                std::cout << std::endl;*/
                tokA = tok;
            }
            res.push(tokA);
        } else {
            res.push(tokA);
        }
    }
    /*std::cout << std::endl;
    printTok(res.top());*/
    assert(res.top().kind == Expr::Kind::num);
    return res.top().num;
}

void Expr::printTok(Expr::ExprToken tok){
    std::cout << tok.kind << "; " << tok.num << "; " << tok.value << std::endl;
}

int main(){
    /*std::vector<std::string> vs(splitExpr("17-24 / 4 *3 +2"));
    for(auto s: vs )
        std::cout << s << std::endl;
    std::vector<Expr::ExprToken> toks(toTokenVector(vs));
    for(auto tok : toks)
        printTok(tok);
    
    std::cout << "rpn\n";
    std::vector<Expr::ExprToken> toksRpn(rpn(toks));
    for(auto tok : toksRpn)
        printTok(tok);
*/
    std::cout << "eval 17-24 / 4 *3 +2 = ";
    Expr expr1("17-24 / 4 *3 +2");
    std::cout << expr1.eval() << std::endl;
    std::cout << "\neval 17+24 * 4 /3 -2 = ";
    Expr expr2("17+24 * 4 /3 -2");
    std::cout << expr2.eval() << std::endl;
    return 0;
}
