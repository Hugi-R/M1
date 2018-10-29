#include <iostream>
#include <stack>
#include <sstream>

// uncomment to disable assert()
// #define NDEBUG
#include <cassert>

#include "expr.hpp"
#include "tools.hpp"

Expr::Expr( const std::string& str ) : str{str} {
    expr = rpn(toTokenVector(splitExpr(str)));
}
Expr::Expr( const char * cstr ): str{cstr} {
    expr = rpn(toTokenVector(splitExpr(str)));
}

std::string Expr::toString(){return str;}

Expr::ExprToken& Expr::toToken( const std::string& s , int levelParenthesis, bool isNegative ){
    double num = 0;
    Expr::Kind kind;
    int priority = 0;
    Expr::ExprToken *res;
    if( s == "+" || s == "-"){
        kind = Expr::Kind::op;
        priority = levelParenthesis + 1;
        res = new Expr::ExprToken(kind, num, s, priority);
    } else if (s == "*" || s == "/"){
        kind = Expr::Kind::op;
        priority = levelParenthesis + 2;
        res = new Expr::ExprToken(kind, num, s, priority);
    } else {
        if(std::isdigit(s[0])){
            num = std::stod(s);
            if(isNegative) num = -num;
            kind = Expr::Kind::num;
            res = new Expr::ExprToken(kind, num, s, priority);
        } else {
            kind = Expr::Kind::num;
            res = new Expr::ExprToken(kind, num, s, priority, true);
        }
    }
    return *res;
}

Expr::ExprToken Expr::toToken( double x ){
    return Expr::ExprToken(Expr::Kind::num, x, std::string(), 0);
}

/* return vector of token that is a valid expression */
std::vector<Expr::ExprToken> Expr::toTokenVector( const std::vector<std::string> vs ){
    std::vector<Expr::ExprToken> res;
    Expr::Kind expected{Expr::Kind::num};
    int levelParenthesis = 0;
    for(uint i = 0; i < vs.size(); ++i ){
        std::string s = vs[i];
        if(s == "("){
            if(expected != Expr::Kind::num) // avoid : a(+c)
                throw std::exception();
            levelParenthesis += 1;
        } else if (s == ")"){
            if(expected != Expr::Kind::op) // avoid : (a+)c
                throw std::exception();
            levelParenthesis -= 1;
        } else {
            auto tok = toToken(s, levelParenthesis*10);
            if(tok.kind == expected){
                res.push_back(tok);
                if(expected == Expr::Kind::num)
                    expected = Expr::Kind::op;
                else
                    expected = Expr::Kind::num;
            } else if( s == "-" ) { //special case : -a
                auto tok = toToken(vs[i+1], levelParenthesis*10, true);
                if(tok.kind == Expr::Kind::num){
                    res.push_back(tok);
                    expected = Expr::Kind::op;
                    i += 1; //sorry to the for loop :(
                } else {
                    throw std::exception();
                }
            } else {
                throw std::exception();
            }
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
    constexpr static char delims[] = {'(', '+', '-', '*', '/', ')'};
    std::vector<std::string> res;
    res.push_back(buff);
    for(char delim : delims){
        std::vector<std::string> tmp;
        tmp.clear();
        for(std::string tok : res){
            std::vector<std::string> tmpsplit(Tools::split(tok, delim));
            tmp.insert(tmp.end(), tmpsplit.begin(), tmpsplit.end());
        }
        res = tmp;
    }
    return res;
}

bool Expr::isPriority (const Expr::ExprToken& tokA, const Expr::ExprToken& tokB){
    assert(tokA.kind == Expr::Kind::op && tokB.kind == Expr::Kind::op);
        return tokA.priority > tokB.priority;
}

double Expr::evaluate (const Expr::ExprToken& op, const Expr::ExprToken& valA, const Expr::ExprToken& valB, std::map<std::string, double>& variables){
    assert((op.kind == Expr::Kind::op) && (valA.kind == Expr::Kind::num) && (valB.kind == Expr::Kind::num));
    if(op.value == "*"){
        return valA.eval(variables) * valB.eval(variables);
    } else if (op.value == "/"){
        return valA.eval(variables) / valB.eval(variables);
    } else if (op.value == "+"){
        return valA.eval(variables) + valB.eval(variables);
    } else if (op.value == "-"){
        return valA.eval(variables) - valB.eval(variables);
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

double Expr::eval(std::map<std::string, double>& variables){
    std::stack<Expr::ExprToken> res;
    for(auto it = expr.rbegin(); it != expr.rend(); ++it){
        auto tokA = *it;
        if(tokA.kind == Expr::Kind::num){
            while(!res.empty() && res.top().kind == Expr::Kind::num){
                auto tokB = res.top();
                res.pop();
                auto op = res.top();
                res.pop();
                auto tok = toToken(evaluate(op, tokA, tokB, variables));
                tokA = tok;
            }
            res.push(tokA);
        } else {
            res.push(tokA);
        }
    }
    assert(res.top().kind == Expr::Kind::num);
    return res.top().eval(variables);
}

double Expr::ExprToken::eval(std::map<std::string, double>& variables) const{
    if(isVar){
        return variables[value];
    }else{
        return num;
    }
}
