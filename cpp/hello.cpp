#include <iostream>
#include <functional>
using namespace std;

int main()
{
    auto fct = [](double a, double b, double c) {return a+b+c;};
    //auto fct2 = fct();
    return 0;
}