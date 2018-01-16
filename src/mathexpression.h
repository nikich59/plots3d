#include <qoperation.h>
#include <qmath.h>
#include <cmath>

#pragma once

namespace
{

class Complex
{
    friend Complex fabs(const Complex &c);
    friend Complex argument(const Complex &c);
    friend Complex exp(const Complex &c);
    friend Complex operator-(const Complex &c);
    friend Complex sinh(const Complex &c);
    friend Complex log(const Complex &c);
    friend Complex cos(const Complex &c);
    friend void getValueFromQString(const QString &s, int &pos, Complex &c);
    friend QString convertValueToQString(const Complex &c);
    friend int getValuePriority(const Complex &c);
    friend bool operator==(double, const Complex &);
public:
    Complex() : m_re(0.0), m_im(0.0) {}
    Complex(double re) : m_re(re), m_im(0.0) {}
    Complex(double re, double im) : m_re(re), m_im(im) {}
    operator double() const {return sqrt(m_re*m_re+m_im*m_im); }
    double re() const {return m_re; }
    double im() const {return m_im; }
    void operator=(const Complex &other) {m_re = other.m_re; m_im = other.m_im; }
    bool operator==(double d) {return m_im == 0.0 && d == m_re; }
    bool operator==(const Complex &other) {return m_im == other.m_im && m_re == other.m_re; }
    Complex operator+(const Complex &other) const {return Complex
                (m_re + other.m_re, m_im + other.m_im); }
    Complex operator-(const Complex &other) const {return Complex
                (m_re - other.m_re, m_im - other.m_im); }
    Complex operator*(const Complex &other) const {return Complex
                (m_re * other.m_re - m_im * other.m_im,
                 m_re * other.m_im + m_im * other.m_re); }
    Complex operator/(const Complex &other) const {return Complex
                ((m_re * other.m_re + m_im * other.m_im) /
                 (other.m_re * other.m_re + other.m_im * other.m_im),
                 (m_im * other.m_re - m_re * other.m_im) /
                 (other.m_re * other.m_re + other.m_im * other.m_im)); }
    Complex operator/(double d) const {return Complex(m_re / d, m_im / d); }
    QString toQString() const;
    double *pRe() {return &m_re; }
    double *pIm() {return &m_im; }

private:
    double m_re, m_im;

};

bool operator==(double d, const Complex &c)
{
    return c.m_im == 0.0 && d == c.m_re;
}

template <>
Complex QOperationCompiler<Complex>::getValueFromString(const QString &s, int &pos, int &ok) const
{
    int i = pos;
    if (s[i] != QChar('{')) {
        if (!s[i].isDigit()) {
            ok = -1;
            return 0.0;
        }
        if (s[i] == QChar('-'))
            i++;
        QString use;
        while (i < s.length() && (s[i].isDigit() || s[i] == QChar('.'))) {
            use += s[i];
            i++;
        }
        if (use == QString("-")) {
            ok = -1;
            return 0.0;
        }
        ok = 0;
        pos = i;
        return Complex(use.toDouble(), 0.0);
    }
    i++;
    if (i >= s.length()) {
        ok = -1;
        return 0.0;
    }
    QString use;
    while (i < s.length() && (s[i].isDigit() || s[i] == QChar('.'))) {
        use += s[i];
        i++;
    }
    if (i >= s.length()) {
        ok = -1;
        return 0.0;
    }
    double re = use.toDouble();
    while (i < s.length() && s[i] == QChar(' '))
        i++;
    if (i >= s.length() || s[i] != QChar(';')) {
        ok = -1;
        return 0.0;
    }
    i++;
    while (i < s.length() && s[i] == QChar(' '))
        i++;
    if (i >= s.length()) {
        ok = -1;
        return 0.0;
    }
    use.clear();
    while (i < s.length() && (s[i].isDigit() || s[i] == QChar('-') || s[i] == QChar('.'))) {
        use += s[i];
        i++;
    }
    while (i < s.length() && s[i] == QChar(' '))
        i++;
    if (i >= s.length() || s[i] != QChar('}')) {
        ok = -1;
        return 0.0;
    }
    i++;
    double im = use.toDouble();
    ok = 0;
    pos = i;
    return Complex(re, im);
}

template <>
QString QConstOperation<Complex>::toQString(const QOperationCompiler<Complex> &) const
{
    return _value.toQString();
}

QString Complex::toQString() const
{
    const int DOUBLE_ACCURACY = 10;
    if (!doubleCmp(m_re, 0.0)) {
        if (doubleCmp(m_im, 1.0))
            return "(" + QString::number(m_re, 'g', DOUBLE_ACCURACY) + " + " + "i)";
        if (!doubleCmp(m_im, 0.0))
            return "(" + QString::number(m_re, 'g', DOUBLE_ACCURACY) + (m_im < 0.0 ? " - " : " + ")+
                    QString::number(fabs(m_im), 'g', DOUBLE_ACCURACY) + "i)";
        else
            return QString::number(m_re, 'g', DOUBLE_ACCURACY);
    } else {
        if (doubleCmp(m_im, 1.0))
            return "i";
        if (!doubleCmp(m_im, 0.0))
            return QString::number(m_im, 'g', DOUBLE_ACCURACY) + "i";
        else
            return "0";
    }

    return "";
}

Complex operator-(const Complex &c)
{
    return Complex(-c.m_re, -c.m_im);
}

Complex operator/(double d, const Complex &c)
{
    return Complex(d) / c;
}

Complex fabs(const Complex &c)
{
    return Complex(sqrt(c.m_re * c.m_re + c.m_im * c.m_im), 0.0);
}

double flog(double r)
{
    return log(r);
}

double fexp(double r)
{
    return exp(r);
}

Complex argument(const Complex &c)
{
    return Complex(atan2(c.m_im, c.m_re), 0.0);
}

Complex log(const Complex &c)
{
    double r = fabs(c);
    return Complex(flog((double)r), atan2(c.m_im, c.m_re));
}

Complex exp(const Complex &c)
{
    return Complex(fexp(c.m_re) * cos(c.m_im), fexp(c.m_re) * sin(c.m_im));
}

Complex pow(const Complex &c1, const Complex &c2)
{
    return exp(Complex(log(fabs(c1)), argument(c1)) * c2);
}

Complex sqrt(const Complex &c)
{
    return pow(c, Complex(0.5));
}

Complex sinh(const Complex &c)
{
    return (exp(c) - exp(-c)) / 2.0;
}

Complex cosh(const Complex &c)
{
    return (exp(c) + exp(-c)) / 2.0;
}

Complex sin(const Complex &c)
{
    return sinh(Complex(0.0, 1.0) * c) / Complex(0.0, 1.0);
}

Complex cos(const Complex &c)
{
    return cosh(Complex(-c.m_im, c.m_re));
}

typedef QFunction<Complex>          QComplexFunction;

typedef QOperationCompiler<Complex> QComplexCompiler;

} // end of namespace
