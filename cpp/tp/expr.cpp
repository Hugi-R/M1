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
            std::string d;
            d.push_back(delim);
            res.push_back(d);
            buff = "";
        } else {
            buff.push_back(c);
        }
    }
    res.push_back(buff);
    //remove "" from vector
    std::vector<std::string> tmp;
    for(auto s : res){
        if
        tmp.push_back(s);
    }
    return res;
}

Expr::ExprToken Expr::toToken( const std::string& s , int levelParenthesis ){
    double num = 0;
    Expr::Kind kind;
    int priority = 0;
    std::cout << "toToken( " << s << ", " << levelParenthesis << " )" << std::endl;
    if( s == "+" || s == "-"){
        kind = Expr::Kind::op;
        priority = levelParenthesis + 1;
    } else if (s == "*" || s == "/"){
        kind = Expr::Kind::op;
        priority = levelParenthesis + 2;
    } else {
        num = std::stod(s);
        kind = Expr::Kind::num;
    }
    Expr::ExprToken res{kind, num, s, priority};
    return res;
}

Expr::ExprToken Expr::toToken( double x ){
    return Expr::ExprToken{Expr::Kind::num, x, std::string(), 0};
}

/* return vector of token that is a valid expression */
std::vector<Expr::ExprToken> Expr::toTokenVector( const std::vector<std::string> vs ){
    std::vector<Expr::ExprToken> res;
    Expr::Kind expected{Expr::Kind::num};
    int levelParenthesis = 0;
    for(std::string s : vs)
        std::cout << s << std::endl;
    for(std::string s : vs){
        std::cout << s << std::endl;
        if(s == "("){
            if(expected != Expr::Kind::num) // avoid a(-c)
                throw std::exception();
            levelParenthesis += 1;
        } else if (s == ")"){
            if(expected == Expr::Kind::num) // avoid (a-)c
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
    std::cout << std::endl << buff << std::endl;
    constexpr static char delims[] = {'(', '+', '-', '*', '/', ')'};
    std::vector<std::string> res;
    res.push_back(buff);
    for(char delim : delims){
        std::vector<std::string> tmp;
        tmp.clear();
        for(std::string tok : res){
            std::vector<std::string> tmpsplit(split(tok, delim));
            tmp.insert(tmp.end(), tmpsplit.begin(), tmpsplit.end());
        }
        for(auto st : tmp)
            std::cout << st << std::endl;
        res = tmp;
    }
    return res;
}

bool Expr::isPriority (Expr::ExprToken tokA, Expr::ExprToken tokB){
    assert(tokA.kind == Expr::Kind::op && tokB.kind == Expr::Kind::op);
        return tokA.priority > tokB.priority;
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

/*int main(){
    std::vector<std::string> vs(splitExpr("17-24 / 4 *3 +2"));
    for(auto s: vs )
        std::cout << s << std::endl;
    std::vector<Expr::ExprToken> toks(toTokenVector(vs));
    for(auto tok : toks)
        printTok(tok);

    std::cout << "rpn\n";
    std::vector<Expr::ExprToken> toksRpn(rpn(toks));
    for(auto tok : toksRpn)
        printTok(tok);

    std::cout << "eval 17-24 / 4 *3 +2 = ";
    Expr expr1("17-24 / 4 *3 +2");
    std::cout << expr1.eval() << std::endl;
    std::cout << "\neval 17+24 * 4 /3 -2 = ";
    Expr expr2("17+24 * 4 /3 -2");
    std::cout << expr2.eval() << std::endl;
    return 0;
}*/
