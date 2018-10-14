#include <iostream>
#include <ostream>
#include<vector>


class Complex{
    public:
    class DivisionByZero{};

    constexpr Complex(double a = 0, double b = 0);
    Complex(const Complex&);
    Complex(Complex&&);

    Complex& operator=(const Complex& c){
        return Complex{c};
    }
    friend Complex operator+(const Complex& a, const Complex& b);
    friend Complex operator/(const Complex& a, const Complex& b);
    friend std::ostream& operator<<(std::ostream& os, const Complex c){
        return os;
    }
    double real() const;
    double imaginary() const;
    double& real();
    double& imaginary();
    void print();

    static const Complex one;

    private:
    double _real;
    double _imaginary;
};

class CVector{
    public:
    CVector(int c = 10) : m_C{c}, m_N{0}{
        m_data = new Complex[c];
    }
    ~CVector(){
        delete[] m_data;
    }
    Complex operator[](int i) const;
    Complex& operator[](int i);
    void push_back(Complex& c);

    class iterator {
        public:
        iterator(CVector& vec);
        bool operator!=(iterator& it);


        private:
        int pos;
        CVector& vec;

    };

    iterator begin();
    iterator end();

    private:
    int m_C;
    int m_N;
    Complex *m_data;
};

Complex operator+(const Complex& a, const Complex& b){
    return Complex(a._real + b._real, a._imaginary + b._imaginary);
}
Complex operator/(const Complex& a, const Complex& b){
    double num1 = a._real*b._real + a._imaginary*b._imaginary;
    double num2 = a._imaginary*b._real + a._real*b._imaginary;
    double denom = b._real*b._real + b._imaginary*b._imaginary;
    if(denom == 0) throw Complex::DivisionByZero();
    return Complex(num1/denom, num2/denom);
}

constexpr Complex::Complex(double a, double b) : _real{a}, _imaginary{b} {}

Complex::Complex(const Complex& other) : _real{other._real}, _imaginary{other._imaginary} {}

Complex::Complex(Complex&& c) : _real{c._real}, _imaginary{c._imaginary} {}

double Complex::real() const {return _real;}
double Complex::imaginary() const {return _imaginary;}
double& Complex::real() {return _real;}
double& Complex::imaginary() {return _imaginary;}
const Complex Complex::one {1, 1};

void Complex::print(){
    std::cout << _real << "+" << _imaginary << "i" << std::endl;
}

std::istream& operator>>(std::istream& is, Complex& c){
    float a, b;
    char t;
    is >> a;
    is >> t;
    if(t != '+'){
        is.putback(t);
        b = 0.f;
    }
    is >> b;
    is >> t;
    if(t != 'i'){
        is.putback(t);
        is.setstate(std::ios::failbit);
    }
    c.real()=a;
    c.imaginary()=b;
    return is;
}

inline Complex CVector::operator[](int i) const {
    if(i >= m_N)
        throw std::exception();
    return m_data[i];
}
inline Complex& CVector::operator[](int i) {
    if(i >= m_N)
        throw std::exception();
    return m_data[i];
}
void CVector::push_back(Complex& c){
    if(m_N == m_C){
        Complex* newData = new Complex[2*m_C];
        //check
        for(int i = 0; i < m_C; ++i){
            newData[i] = m_data[i];
        }
        delete[] m_data;
        m_data = newData;
        m_C *= 2;
    }
    m_data[m_N++];
}

int main(int argc, char const *argv[])
{
    Complex i(1, 2);
    i.print();
    Complex d(i);
    d.print();
    Complex z;
    z.print();
    std::cin >> z;
    z.print();
    CVector cv(5);
    cv.push_back(i);
    cv.push_back(d);
    cv.push_back(z);
    return 0;
}
