#include <vector>
#include <string>

class Expr {
    public:
    enum Kind {num, op};
    struct ExprToken{
        Kind kind;
        double num;
        std::string value;
        int priority;
    };
    // Construit une expression a partir du texte
    Expr ( const char * str );
    Expr ( const std::string& str );
    // Retourne la valeur de l'expression
    double eval();
    // Affiche la représentation interne
    void print();

    public: //to private after debug
    std::vector<Expr::ExprToken> expr;

    std::vector<std::string> split ( const std::string& s, char delim );
    Expr::ExprToken toToken( const std::string& s, int levelParenthesis, bool isNegative = false );
    Expr::ExprToken toToken( double x );
    std::vector<Expr::ExprToken> toTokenVector( const std::vector<std::string> vs );
    std::vector<std::string> splitExpr (const std::string& s);
    bool isPriority (Expr::ExprToken tokA, Expr::ExprToken tokB);
    double evaluate (Expr::ExprToken op, Expr::ExprToken valA, Expr::ExprToken valB);
    std::vector<Expr::ExprToken> rpn( const std::vector<Expr::ExprToken>& toks );
    void printTok(Expr::ExprToken tok);
};
