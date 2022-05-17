#include <iostream>
#include "matrix.h"

using namespace std;

void show(Complex a)
{
    printf("%.4lf + %.4lfi\n", a.GetReal(), a.GetImage());
}

void ComplexConstructor()
{
    Complex a = Complex();
    show(a);
}

void ComplexConstructor(db a, db b)
{
    Complex c = Complex(a, b);
    show(c);
}

void ComplexSet(db a, db b)
{
    Complex c = Complex();
    c.SetReal(a);
    c.SetImage(b);
    show(c);
}

void ComplexAdd()
{
    Complex a = Complex(1, 2);
    Complex b = Complex(3, 4);
    Complex c = a + b;
    show(c); // (4, 6)
}

void ComplexMin()
{
    Complex a = Complex(1, 2);
    Complex b = Complex(3, 4);
    Complex c = a - b;
    show(c); // (-2, -2)
}

void ComplexMul()
{
    Complex a = Complex(1, 2);
    Complex b = Complex(3, 4);
    Complex c = a * b;
    show(c); // (-5, 10)
}

void ComplexDiv()
{
    Complex a = Complex(1, 2);
    Complex b = Complex(3, 4);
    Complex c = a / b;
    show(c); // (11 / 25, 2 / 25)
}

void show(ValueType a)
{
    cout << a.GetType() << ' ';
    if (a.GetType() == 1)
        cout << a.GetLongLongValue() << endl;
    else if (a.GetType() == 2)
        printf("%.4lf\n", a.GetDoubleValue());
    else
        show(a.GetComplexValue());
}

void ValueTypeSet()
{
    ValueType a;
    show(a);
}

void ValueTypeSet(int type)
{
    ValueType a = ValueType(type);
    show(a);
}

void SetLL()
{
    int type = 1;
    ll value = 123123123;
    ValueType a = ValueType();
    a.SetType(type);
    a.SetLongLongValue(value);
    show(a);
}

void SetDB()
{
    int type = 2;
    db value = 123123.623;
    ValueType a = ValueType();
    a.SetType(type);
    a.SetDoubleValue(value);
    show(a);
}

void SetCP()
{
    int type = 3;
    Complex value = Complex(2, 3);
    ValueType a = ValueType();
    a.SetType(type);
    a.SetComplexValue(value);
    show(a);
}

void TestUpGrade()
{
    int type = 2;
    db value = 123123.123;
    ValueType a = ValueType();
    a.SetType(type);
    a.SetDoubleValue(value);
    show(a);
    a.UpGrade();
    show(a);
}

void NumberAndComplex()
{
    Complex a = Complex(2.5, 4);
    ll b = 3;
    show(b * a);
    db c = 2.5;
    show(c * a);
}

void NumberAndValueType1()
{
    ValueType a = ValueType(1);
    a.SetLongLongValue(2);
    ll b = 3;
    show(b * a);
    show(a / b);
    db c = 3.0;
    show(c * a);
    show(a / c);
    Complex d = Complex(1, 2);
    show(d * a);
    show(a / d);
}

void NumberAndValueType2()
{
    ValueType a = ValueType(2);
    a.SetDoubleValue(2);
    ll b = 3;
    show(b * a);
    show(a / b);
    db c = 3.0;
    show(c * a);
    show(a / c);
    Complex d = Complex(1, 2);
    show(d * a);
    show(a / d);
}

void NumberAndValueType3()
{
    ValueType a = ValueType(3);
    a.SetComplexValue(Complex(2, 4));
    ll b = 3;
    show(b * a);
    show(a / b);
    db c = 3.0;
    show(c * a);
    show(a / c);
    Complex d = Complex(1, 2);
    show(d * a);
    show(a / d);
}

void ValueTypeAndValueType()
{
    ValueType a = ValueType(1);
    a.SetLongLongValue(2);
    ValueType b = ValueType(2);
    b.SetDoubleValue(2.5);
    ValueType c = ValueType(3);
    c.SetComplexValue(Complex(2, 3));

    show(a + b);
    show(a - b);
    show(a * b);
    show(a / b);

    show(a + c);
    show(a - c);
    show(a * c);
    show(a / c);

    show(b + c);
    show(b - c);
    show(b * c);
    show(b / c);
}
