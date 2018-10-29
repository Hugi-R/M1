#include <iostream>
#include <string>
#include <sstream>

#include "program.hpp"
#include "tools.hpp"

Program::Program(std::istream& in){
    std::string tmp;
    while(!std::getline(in, tmp).eof())
        parse(tmp);
}

std::vector<std::string> Program::splitProg (const std::string& s){
    //remove space
    std::string buff;
    for(char c : s){
        if(c != ' ')
            buff.push_back(c);
    }
    constexpr static char delims[] = {';', '\n'};
    std::vector<std::string> res;
    res.push_back(buff);
    for(char delim : delims){
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

void Program::parse(std::string in){
    std::vector<std::string> toks = splitProg(in);
    std::string expr = "";
    for(auto s : toks){
        if(s == ";"){
            if(expr != ""){
                Expr e(expr);
                hidden.push_back(e);
                expr = "";
            }
        } else if(s == "\n"){
            if(expr != ""){
                Expr e(expr);
                printed.push_back(e);
                expr = "";
            }
        } else {
            expr = s;
        }
    }
    if(expr != ""){ //treating if last is eof
        Expr e(expr);
        printed.push_back(e);
        expr = "";
    }
}

void Program::eval(){

}

int main(/*int argc, char const *argv[]*/)
{
    std::istringstream iss("1;2 \n 3; 4");
    Program p(iss);
    return 0;
}
