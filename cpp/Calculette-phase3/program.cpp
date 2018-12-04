//
// Created by Mathias Paulin on 17/10/2017.
// Modified by Hugo Roussel.
//
#include "program.h"

#include <stack>
#include <sstream>

Program::Program(TokenStream &ts) {
    build_function_table();
    tokenize(ts);
    parse();
}

void Program::print() const {

    std::cout << "Program  : ";
    for (const auto &t : _infix) {
        std::cout << t << " ";
    }
    std::cout << std::endl;

    std::cout << "RPN  : ";
    for (const auto &t : _rpn) {
        std::cout << t << " ";
    }
    std::cout << std::endl;
}

double Program::eval(bool donotprint) {
    double value;
    std::stack<double> res_stack;

    for (const auto &t : _rpn) {
        // use memory here if token == name
        if (t.isLiteral()) {
            res_stack.push(t.number_value);
        } else if (t.isSeparator()) {
            if (!res_stack.empty()) {
                value = res_stack.top();
                res_stack.pop();
            }
            if (t.kind == Kind::next)
                donotprint = true;
            else if (!donotprint) {
                std::cout << value << std::endl;
            } else {
                donotprint = false;
            }
        } else if (t.isOperator()) {
            auto op2 = res_stack.top();
            res_stack.pop();
            auto op1 = res_stack.top();
            res_stack.pop();
            value = t.operate(op1, op2);
            res_stack.push(value);
        } else if (t.isIdentifier()) {
            // fetch identifier value from memory
            auto variable = _memory.find(t.string_value);
            if (variable == _memory.end()) {
                throw Program::Error("Identifier not found : " + t.string_value);
            } else {
                value = variable->second;
                res_stack.push(value);
            }
        } else if (t.isFunction()) {
            if(!donotprint)
                std::cout << t << "= ";
            res_stack.push(t.fct->eval(*this));
        } else {
            // store value in memory
            value = res_stack.top();
            _memory[t.string_value] = value;
        }
    }
    return value;
}


void Program::tokenize(TokenStream &ts) {
    do {
        _infix.push_back(ts.get());
    } while ((ts.current().kind != Kind::end));
}

void Program::parse() {
    // operator stack
    std::stack<Token> op_stack;
    for (const auto &tok : _infix) {
        if (tok.isLiteral() || tok.isIdentifier() || tok.isFunction()) {
            //  Litteral or identifier value. Just put to the output queue.
            _rpn.push_back(tok);
        } else if (tok.isOperator()) {
            // An operator is read
            // pop until top of the stack has an element of lower precedence
            while (!op_stack.empty() && op_stack.top().isOperator() && op_stack.top().compare(tok) > 0) {
                _rpn.push_back(op_stack.top());
                op_stack.pop();
            }
            op_stack.push(tok);
        } else if (tok.kind == Kind::lp) {
            op_stack.push(tok);
        } else if (tok.kind == Kind::rp) {
            // A right parenthesis is read
            // pop until top of the stack is a left parenthesis
            while (!op_stack.empty() && op_stack.top().kind != Kind::lp) {
                _rpn.push_back(op_stack.top());
                op_stack.pop();
            }
            if (op_stack.empty()) {
                throw Program::Error("Bad () match.");
            }
            op_stack.pop();
        } else if (tok.isSeparator()) {
            // A separator is read -- end of sub-expression
            // pop until the stack is empty
            while (!op_stack.empty()) {
                _rpn.push_back(op_stack.top());
                op_stack.pop();
            }
            _rpn.push_back(tok);
        } else if (tok.kind == Kind::assign) {
            // todo : check for lvalue (_rpn.back())
            auto assign = Token {Kind::assign, _rpn.back().string_value};
            _rpn.pop_back();
            op_stack.push(assign);
        } else {
            std::stringstream error;
            error << "Error -- unknown token" << tok;
            throw Program::Error(error.str());
        }
    }
    while (!op_stack.empty()) {
        _rpn.push_back(op_stack.top());
        op_stack.pop();
    }
}

void Program::dump_memory() {
    std::cout << std::endl << "Calculator memory : " << std::endl;
    for (const auto &e: _memory)
        std::cout << e.first << "=" << e.second << std::endl;
}

void Program::setTokenStream(TokenStream &ts){
    _infix.clear();
    _rpn.clear();
    tokenize(ts);
    parse();
}

void Program::build_function_table() {
    _functions[std::string("sin")]=std::make_pair(1, [](const DoubleParams& x)->double{return std::sin(x[0]);});
    _functions[std::string("cos")]=std::make_pair(1, [](const DoubleParams& x)->double{return std::cos(x[0]);});
    _functions[std::string("tan")]=std::make_pair(1, [](const DoubleParams& x)->double{return std::tan(x[0]);});
    _functions[std::string("sqrt")]=std::make_pair(1, [](const DoubleParams& x)->double{return std::sqrt(x[0]);});
    _functions[std::string("log")]=std::make_pair(1, [](const DoubleParams& x)->double{return std::log(x[0]);});
    _functions[std::string("exp")]=std::make_pair(1, [](const DoubleParams& x)->double{return std::exp(x[0]);});
    _functions[std::string("pow")]=std::make_pair(2, [](const DoubleParams& p)->double{return std::pow(p[0], p[1]);});
    _functions[std::string("hypot")]=std::make_pair(2, [](const DoubleParams& p)->double{return std::hypot(p[0], p[1]);});
    _functions[std::string("lerp")]=std::make_pair(3, [](const DoubleParams& p)->double{return (1-p[2])*p[0] + p[2]*p[1];});

    _functions[std::string("polynome")]=std::make_pair
            (	-1,
                 [](const DoubleParams& x)->double {
                    if (x.size() != x[0]+2)
                        throw Program::Error("polynome() - wrong number of arguments.");
                    double res = 0;
                    for(int i = 1; i <= x[0]; ++i){
                        res += std::pow(x[x.size()-1],i)*x[i];
                    }
                    return res;
                 }
            );
}

InternalFunction Program::getFunction(std::string name){
    return _functions[name];
}
