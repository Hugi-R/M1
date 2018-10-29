#ifndef EXPR_CPP
#define EXPR_CPP 1
#include <vector>
#include <string>
#include <map>

class Expr {
    public:
    enum Kind {num, op};
    class ExprToken{
        public:
        Kind kind;
        double num;
        std::string value;
        int priority;
        ExprToken(Kind k, double n, std::string s, int p) : kind{k}, num{n}, value{s}, priority{p} {};
        virtual double eval(std::map<std::string, Expr>& variables);
        void print(){ std::cout << kind << "; " << num << "; " << value << std::endl;}
    };
    class ExprTokenVar : public ExprToken {
        public:
        ExprTokenVar(Kind k, double n, std::string s, int p) : ExprToken(k,n,s,p) {};
        virtual double eval(std::map<std::string, Expr>& variables);
    };
    // Construit une expression a partir du texte
    Expr ( const char * str );
    Expr ( const std::string& str = ""); //compilator is grumpy if no default, apparently need it for map ?
    // Retourne la valeur de l'expression
    double eval(std::map<std::string, Expr>& variables);
    // Affiche la représentation interne
    std::string toString();

    public: //to private after debug
    std::string str;
    std::vector<Expr::ExprToken> expr;

    Expr::ExprToken toToken( const std::string& s, int levelParenthesis, bool isNegative = false );
    Expr::ExprToken toToken( double x );
    std::vector<Expr::ExprToken> toTokenVector( const std::vector<std::string> vs );
    std::vector<std::string> splitExpr (const std::string& s);
    bool isPriority (Expr::ExprToken tokA, Expr::ExprToken tokB);
    double evaluate (Expr::ExprToken op, Expr::ExprToken valA, Expr::ExprToken valB, std::map<std::string, Expr>& variables);
    std::vector<Expr::ExprToken> rpn( const std::vector<Expr::ExprToken>& toks );
};
#endif
