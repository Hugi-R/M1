// Hugo Roussel

#include <regex>
#include <vector>
#include <iostream>
#include <sstream>
#include <cmath>

#include <iostream>

//#include "prog_function.h"
#include "tokenstream.h"

double ProgFunction::parse(std::string s){
    std::regex cos("cos\\((-?\\d+\\.?\\d*)\\)");
    std::regex sin("sin\\((-?\\d\\.?\\d*)\\)");
    std::regex tan("tan\\((-?\\d\\.?\\d*)\\)");
    std::regex sqrt("sqrt\\((-?\\d\\.?\\d*)\\)");
    std::regex log("log\\((-?\\d\\.?\\d*)\\)");
    std::regex exp("exp\\((-?\\d\\.?\\d*)\\)");

    std::vector<std::regex> base_fct{cos, sin, tan, sqrt, log, exp};
    uint i = 0;
    std::smatch num_match;
    while(!std::regex_match(s, num_match, base_fct[i]) && ++i < base_fct.size());
    if(i >= base_fct.size()){
        std::stringstream error;
        error << "Not a valid function (" << s << ")";
        throw ProgFunction::Error(error.str());
    }
    double num = stod(num_match[1].str());
    
    double ret;
    switch (i)
    {
        case 0:
            ret = std::cos(num);
            break;
        case 1:
            ret = std::sin(num);
            break;
        case 2:
            ret = std::tan(num);
            break;
        case 3:
            ret = std::sqrt(num);
            break;
        case 4:
            ret = std::log(num);
            break;
        case 5:
            ret = std::exp(num);
            break;
        default:
            std::cerr << "Incomplete switch in ProgFunction::parse" << std::endl;
            break;
    }
    return ret;
}

ProgFunction::ProgFunction(Token &myToken) : _myToken{myToken} {
    //_myToken.number_value = parse(_myToken.string_value);
    parse();
    std::cout << _name << " : ";
    for(auto s : _args){
        std::cout << s << " ";
    }
    std::cout << std::endl;
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
    while((it+1) != end ){
        if(*it != ','){
            arg += *it;
        } else {
            _args.push_back(arg);
            arg = "";
        }
        ++it;
    }
    _args.push_back(arg);
}

double ProgFunction::eval(Program &p){
    //TODO
    return 0;
}
