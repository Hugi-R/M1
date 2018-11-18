//
// Created by Mathias Paulin on 17/10/2017.
//
#include "program.h"

#include <stack>
#include <sstream>

Program::Program(TokenStream &ts) {
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

double Program::eval() {
    bool donotprint = false;
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
        if (tok.isLiteral() || tok.isIdentifier()) {
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
