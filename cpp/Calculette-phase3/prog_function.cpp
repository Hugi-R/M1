// Hugo Roussel

#include <vector>
#include <iostream>
#include <sstream>
#include <cmath>

#include <iostream>

#include "tokenstream.h"
#include "program.h"

ProgFunction::ProgFunction(Token &myToken) : _myToken{myToken} {
    parse();
}


void ProgFunction::parse(){
    auto it = _myToken.string_value.begin();
    auto end = _myToken.string_value.end();
    while(it != end && *it != '('){
        _name += *it;
        ++it;
    }
    ++it;
    std::string arg;
    int parenthesisLevel = 0;
    while((it+1) != end ){
        if(*it == '(') parenthesisLevel += 1;
        if(*it == ')') parenthesisLevel -= 1;
        if(parenthesisLevel == 0 && *it == ','){
            _args.push_back(arg);
            arg = "";
        } else {
            arg += *it;
        }
        ++it;
    }
    _args.push_back(arg);
    /*std::cout << _name << " : ";
    for(auto s : _args)
        std::cout << s << " ";
    std::cout << std::endl;*/
}

double ProgFunction::eval(Program &p){
    Program parser(p);
    std::vector<double> argsValue;
    for(auto s : _args){
        std::istringstream is(s);
        TokenStream ts(is);
        parser.setTokenStream(ts);
        argsValue.push_back(parser.eval(true));
    }
    auto fct = getFunctionLambda();
    return fct(argsValue);
}

std::function<double (std::vector<double>)> ProgFunction::getFunctionLambda(){
    if(_name == "cos")
        return [](std::vector<double> x){if(x.size() > 1) throw ProgFunction::Error("Arguments error"); else return std::cos(x[0]);};
    if(_name == "sin")
        return [](std::vector<double> x){if(x.size() > 1) throw ProgFunction::Error("Arguments error" ); else return std::sin(x[0]);};
    if(_name == "tan")
        return [](std::vector<double> x){if(x.size() > 1) throw ProgFunction::Error("Arguments error"); else return std::tan(x[0]);};
    if(_name == "sqrt")
        return [](std::vector<double> x){if(x.size() > 1) throw ProgFunction::Error("Arguments error"); else return std::sqrt(x[0]);};
    if(_name == "log")
        return [](std::vector<double> x){if(x.size() > 1) throw ProgFunction::Error("Arguments error"); else return std::log(x[0]);};
    if(_name == "exp")
        return [](std::vector<double> x){if(x.size() > 1) throw ProgFunction::Error("Arguments error"); else return std::exp(x[0]);};
    if(_name == "pow")
        return [](std::vector<double> x){if(x.size() > 2) throw ProgFunction::Error("Arguments error"); else return std::pow(x[0],x[1]);};
    if(_name == "hypot")
        return [](std::vector<double> x){if(x.size() > 2) throw ProgFunction::Error("Arguments error"); else return std::sqrt(x[0]*x[0]+x[1]*x[1]);};
    if(_name == "lerp")
        return [](std::vector<double> x){if(x.size() > 3 /*|| x[2]<0 || x[2]>1*/) throw ProgFunction::Error("Arguments error"); else return (1 - x[2]) * x[0] + x[2] * x[1];};
    if(_name == "polynome"){
        return [](std::vector<double> x){
            if(x.size() < 3 || (x.size()-2) != x[0]){
                throw ProgFunction::Error("Arguments error");
            } else {
                double res = 0;
                for(int i = 1; i <= x[0]; ++i){
                    res += std::pow(x[x.size()-1],i)*x[i];
                }
                return res;
            }
        };
    }

    throw ProgFunction::Error("Unknow function : "+_name);
}
