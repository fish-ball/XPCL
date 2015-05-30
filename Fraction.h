//////////////////////////////////////////////////////////
//                      ·ÖÊýÄ£°å v1.0                   //
//////////////////////////////////////////////////////////

#ifndef FRACTION_XPER
#define FRACTION_XPER

#include <iostream>

typedef long long i64;

i64 gcd(i64 m, i64 n) { return n ? gcd(n, m%n) : m; }
i64 lcm(i64 m, i64 n) { return m / gcd(m, n) * n; }
i64 sign(i64 x) { return x > 0 ? 1 : -1; }
i64 abs(i64 x) { return x > 0 ? x : -x; }

struct Fraction {
    i64 a,  b;
    Fraction(i64 x = 0, i64 y = 1) {
        i64 m = gcd(abs(x), abs(y));
        a = x / m * sign(y);
        b = a ? abs(y / m) : 1;
    }
    double toDouble() const { return double(a)/double(b); }
};

Fraction abs(const Fraction& x) { return Fraction(x.a < 0 ? -x.a : x.a, x.b); }

const Fraction operator+(const Fraction& x, const Fraction& y) {
    i64 m = gcd(x.b, y.b);
    return  Fraction( y.b/m*x.a + x.b/m*y.a, x.b/m*y.b );
}

const Fraction operator-(const Fraction& x, const Fraction& y) {
    i64 m = gcd(x.b, y.b);
    return  Fraction( y.b/m*x.a - x.b/m*y.a, x.b/m*y.b );
}

const Fraction operator*(const Fraction& x, const Fraction& y) {
    i64 m1 = gcd(abs(x.a), y.b),
        m2 = gcd(abs(y.a), x.b);
    return  Fraction(x.a/m1 * y.a/m2, x.b/m2 * y.b/m1);
}

const Fraction operator/(const Fraction& x, const Fraction& y) {
    return  x * Fraction(y.b, y.a);
}

bool operator<(const Fraction& x, const Fraction& y) {
    return x.a*y.b - x.b*y.a < 0;
}    

std::ostream& operator<<(std::ostream& out, const Fraction& x) {
    if(x.a == 0)        return out << 0;
    else if(x.b == 1)   return out << x.a;
    else                return out << x.a << '/' << x.b;
}

#endif // FRACTION_XPER
