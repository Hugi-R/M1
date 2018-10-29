#include <string>
#include <iostream>

#include "program.hpp"
#include "tools.hpp"

Program::Program(std::istream& in){
    std::string tmp;
    while(!in.eof()){
        std::getline(in, tmp);
        parse(tmp);
    }
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
            std::vector<std::string> tmpsplit(Tools::split(tok, delim));
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
                if(Tools::contain(expr, '=')){
                    addVariable(expr);
                    hidden.push_back(expr);
                    expr = "";
                } else {
                    Expr e(expr);
                    hidden.push_back(e);
                    expr = "";
                }
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

void Program::addVariable(const std::string s){
    auto toks = Tools::split(s, '=');
    if(toks.size() != 3) throw std::exception();
    if(std::isdigit(toks[0][0])) throw std::exception();
    if(variables.count(toks[0])>0) throw std::exception();
    Expr expr(toks[2]);
    variables.insert(std::pair<std::string,double>(toks[0], expr.eval(variables)));
    std::cout << "new variable : " << toks[0] << " as " << expr.toString() << std::endl;
}

double Program::eval(std::ostream& os){
    print(os);
    os << "--------" << std::endl;
    double res;
    for(auto e : hidden)
        e.eval(variables);
    for(auto e : printed){
        res = e.eval(variables);
        os << res << "\n";
    }
    return res;
}

void Program::print(std::ostream& os){
    for(auto e : hidden){
        os << e.toString() << ";\n";
    }
    for(auto e : printed){
        os << e.toString() << "\n";
    }
}
