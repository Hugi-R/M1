#include <iostream>
#include <string>
#include <functional>

template <typename T>
class Option{
    public:
    Option(const T& t):_valid{true},_value{t}{}
    Option():_valid{false}{}
    bool valid() const {return _valid;}
    operator bool() const {return _valid;}
    T& operator*(){return value();}
    T value(){
        if(!_valid)
            throw std::exception();
        else
            return _value;
    }
    template <typename F>
    void do_if(const F& f){if(_valid) f(_value);}

    private:
    bool _valid;
    T _value;
};

int main(/*int argc, char const *argv[]*/)
{
    Option<std::string> s("Test");
    Option<int> i;
    s.do_if([](std::string s){std::cout << s << std::endl;});
    /*Option<int, 999> i;
    Option<int, 0> j(5);
    std::cout << i.valid() << std::endl;
    std::cout << i.value() << std::endl;
    if(j)
        std::cout << j.value() << std::endl;
    std::cout << *j << std::endl;*/
    return 0;
}
