// Hugo Roussel

#ifndef PROG_FUNCTION_H
#define PROG_FUNCTION_H
#include <string>

class ProgFunction {
public:
    class Error {
    public:
        explicit Error(const std::string &error) : message("ProgramFunction error : " + error) {}

        const char *what() const { return message.c_str(); }

    private:
        std::string message;
    };

    /// check wether s as the form of a function
    static double parse(std::string s);
};

#endif //PROG_FUNCTION_H
