class Complex{
    public:
    Complex(double, double);
    Complex(const Complex&);
    Complex(Complex&&);

    //friend Complex operator+(const Complex& a, const Complex& b);
    //void print();

    private:
    double _real;
    double _imaginary;
};

int main(int argc, char const *argv[])
{
    /* code */
    return 0;
}
