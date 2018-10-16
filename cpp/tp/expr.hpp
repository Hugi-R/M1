#include <vector>
#include <string>

class Expr {
    public:
    enum Kind {num, op, eof};
    struct ExprToken{
        Kind kind;
        double num;
        std::string value;
    };
    // Construit une expression a partir du texte
    Expr ( const char * str );
    // Retourne la valeur de l'expression
    int eval();
    // Affiche la représentation interne
    void print();
};
