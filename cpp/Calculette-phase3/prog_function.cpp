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
    auto fct = p.getFunction(_name);
    if((fct.first != -1) && ((uint)fct.first != argsValue.size())){
        throw ProgFunction::Error("Arguments error");
    }
    double res = fct.second(argsValue);
    return res;
}
