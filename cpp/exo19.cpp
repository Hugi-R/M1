#include <iostream>
#include <cmath>


class Expr{
    public:
    virtual ~Expr() {}
    virtual float eval(float x) = 0;
    virtual void print(std::ostream& out) = 0;
};

class Const : public Expr {
    public:
    Const(float c): _c(c) { }
    virtual float eval(float x) { return _c; }
    virtual void print(std::ostream& out) { out << _c; }

    private:
    float _c;
};

class Var : public Expr {
    public:
    Var(std::string x): _x{x} {}
    virtual float eval(float x) {return x;}
    virtual void print(std::ostream& out) { out << _x; }

    private:
    std::string _x;
};

class Neg : public Expr {
    public:
    Neg(Expr& expr) : _expr{expr} {}
    virtual float eval(float x) {return - _expr.eval(x);}
    virtual void print(std::ostream& out) { out << "-"; _expr.print(out);}

    private:
    Expr& _expr;
};

class BinOp : public Expr {
    public:
    BinOp(Expr& lhs, Expr& rhs) : _lhs{lhs}, _rhs{rhs} {}
    ~BinOp() {}

    protected:
    Expr& _lhs;
    Expr& _rhs;
};

class Add : public BinOp {
    public:
    Add(Expr& a, Expr& b) : BinOp(a,b) {}
    virtual float eval(float x) {return _lhs.eval(x) + _rhs.eval(x);}
    virtual void print(std::ostream& out) {_lhs.print(out); out << "+"; _rhs.print(out);}
};

class Sub : public BinOp {
    public:
    Sub(Expr& a, Expr& b) : BinOp(a,b) {}
    virtual float eval(float x) {return _lhs.eval(x) - _rhs.eval(x);}
    virtual void print(std::ostream& out) {_lhs.print(out); out << "-"; _rhs.print(out);}
};

class Mul : public BinOp {
    public:
    Mul(Expr& a, Expr& b) : BinOp(a,b) {}
    virtual float eval(float x) {return _lhs.eval(x) * _rhs.eval(x);}
    virtual void print(std::ostream& out) {_lhs.print(out); out << "*"; _rhs.print(out);}
};

class Div : public BinOp {
    public:
    Div(Expr& a, Expr& b) : BinOp(a,b) {}
    virtual float eval(float x) {return _lhs.eval(x) / _rhs.eval(x);}
    virtual void print(std::ostream& out) {_lhs.print(out); out << "/"; _rhs.print(out);}
};

class Pow : public BinOp {
    public:
    Pow(Expr& a, Expr& b) : BinOp(a,b) {}
    virtual float eval(float x) {return std::pow(_lhs.eval(x), _rhs.eval(x));}
    virtual void print(std::ostream& out) {out << "pow("; _lhs.print(out); out << ","; _rhs.print(out); out << ")";}
};

int main(){
    //Expr *e = new Add(Const(3), Const(4));
    Const c(3);
    Var v("x");
    Neg n(c);
    Add a(n,v);
    Mul m(a,c);
    //Expr *f = new Sub( Pow(Var("x"),Const(2)), Mul(Const(3), Var("x")) );
    std::cout << m.eval(0) << std::endl;
    m.print(std::cout);
    std::cout << std::endl;
    return 0;
}
