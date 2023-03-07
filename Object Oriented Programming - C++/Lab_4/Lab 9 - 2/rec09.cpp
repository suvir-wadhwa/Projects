#include <string>
#include <vector>
#include <iostream>
using namespace std;

class Rational {
    friend ostream& operator<<(ostream& os, const Rational& rat);
    friend istream& operator>>(istream& input, Rational& rat);
    friend bool operator==(const Rational& lhs, const Rational& rhs);
    friend bool operator<(const Rational& lhs, const Rational& rhs);
public:
    Rational(int num = 1, int den = 1);
    static int greatestCommonDivisor(int x, int y);
    Rational& operator+=(const Rational& rat);
    Rational& operator++();
    const Rational operator++(int dummy);
    explicit operator bool() const;

private:
    int numerator;
    int denominator;
    void normalize();
};

ostream& operator<<(ostream& os, const Rational& rat) {
    os << rat.numerator << " / " << rat.denominator;
    return os;
}

istream& operator>>(istream& input, Rational &rat) {
    input >> rat.numerator;
    char slash;
    input >> slash;
    if (slash == '/') {
        input >> rat.denominator;
    }
    else {
        rat.denominator = 1;
    }
    rat.normalize();
    return input;
}

Rational::Rational(int num, int den) : numerator(num), denominator(den) {}

void Rational::normalize() {
    int gcd;
    if (denominator < 0 && numerator >= 0) {
        numerator = -1 * numerator;
        denominator = -1 * denominator;
    }
    if (denominator < 0 && numerator < 0) {
        denominator = -1 * denominator;
        numerator = -1 * numerator;
    }
    gcd = greatestCommonDivisor(numerator, denominator);
    numerator = numerator / gcd;
    denominator = denominator / gcd;
}

int Rational::greatestCommonDivisor(int x, int y) {
    while (y != 0) {
        int temp = x % y;
        x = y;
        y = temp;
    }
    return x;
}

Rational& Rational::operator+=(const Rational& rat) {
    numerator *= rat.denominator;
    int rat_num = rat.numerator * denominator;
    denominator *= rat.denominator;
    numerator = numerator + rat_num;
    normalize();
    return *this;
}

Rational& Rational::operator++() {
    numerator += denominator;
    normalize();
    return *this;
}

const Rational Rational::operator++(int dummy) {
    Rational original(*this);
    numerator += denominator;
    normalize();
    return original;
}

Rational::operator bool() const {
    return numerator != 0;
}



Rational operator+(const Rational& lhs, const Rational& rhs) {
    Rational temp(lhs);
    temp += rhs;
    return temp;
}

bool operator==(const Rational& lhs, const Rational& rhs) {
    return (lhs.denominator == rhs.denominator && lhs.numerator == rhs.numerator);
}

bool operator<(const Rational& lhs, const Rational& rhs) {
    return (lhs.numerator/lhs.denominator < rhs.numerator/rhs.denominator);
}

bool operator!=(const Rational& lhs, const Rational& rhs) {
    return !(lhs == rhs);
}

bool operator<=(const Rational& lhs, const Rational& rhs) {
    return (lhs < rhs || lhs == rhs);
}

bool operator>(const Rational& lhs, const Rational& rhs) {
    return !(lhs == rhs || lhs < rhs);
}

bool operator>=(const Rational& lhs, const Rational& rhs) {
    return (lhs > rhs || lhs == rhs);
}


Rational& operator--(Rational& rat) {
    Rational sub(-1, 1);
    rat += sub;
    return rat;
}

Rational operator--(Rational& rat, int dummy) {
    Rational output(rat);
    Rational sub(-1, 1);
    rat += sub;
    return output;
}

int main() {
    Rational a, b;
    cout << "Input a rational number, e.g. 6/9.\n";
    cout << "a: ";
    cin >> a;
    cout << "Input a rational number, e.g. 6/9.\n";
    cout << "b: ";
    cin >> b;
    const Rational one = 1;

    cout << "a = " << a << endl;
    cout << "b = " << b << endl;
    cout << "one = " << one << endl;
    cout << "a += b: " << (a += b) << endl;	// Implement as member
    cout << "a = " << a << endl;

    // Implement + as non-member, but not a friend
    cout << "a + one: " << (a + one) << endl;
    cout << "a == one: " << boolalpha << (a == one) << endl;

    // How does this manage to work?
    // It does NOT require writing another == operator.
    cout << "1 == one: " << boolalpha << (1 == one) << endl;

    // Do not implement as friend.
    cout << "a != one: " << boolalpha << (a != one) << endl;

    cout << "a = " << a << endl;
    cout << "++a = " << (++a) << endl;
    cout << "a = " << a << endl;
    cout << "a++ = " << (a++) << endl;
    cout << "a = " << a << endl;
    cout << "--a = " << (--a) << endl;
    cout << "a = " << a << endl;
    cout << "a-- = " << (a--) << endl;
    cout << "a = " << a << endl;

    cout << "++ ++a = " << (++ ++a) << endl;
    cout << "a = " << a << endl;
    cout << "-- --a = " << (-- --a) << endl;
    cout << "a = " << a << endl;

    cout << "a++ ++ = " << (a++ ++) << endl;
    cout << "a = " << a << endl;

    // Even though the above example, (a++ ++), compiled, the
    // following shouldn't.
    // But some compiler vendors might let it...  Is your compiler
    // doing the right thing?
    //cout << "a-- -- = " << (a-- --) << endl;
    cout << "a = " << a << endl;


    // Should report that 1 is true
    if (Rational(1)) {
        cout << "1 is true" << endl;
    } else {
        cout << "1 is false" << endl;
    }

    // Should report that 0 is false
    if (Rational(0)) {
        cout << "0 is true" << endl;
    } else {
        cout << "0 is false" << endl;
    }

    cout << "Comparisons\n";
    Rational twoFifths(2, 5);
    Rational threeHalves(3, 2);
    Rational minusFive(-5);
    cout << twoFifths << " < " << threeHalves << " : "
         << (twoFifths < threeHalves) << endl;
    cout << twoFifths << " <= " << 1 << " : " << (twoFifths <= 1) << endl;
    cout << threeHalves << " < " << twoFifths << " : "
         << (threeHalves < twoFifths) << endl;
    cout << threeHalves << " > " << threeHalves << " : "
         << (threeHalves > threeHalves) << endl;
    cout << threeHalves << " >= " << threeHalves << " : "
         << (threeHalves >= threeHalves) << endl;
    cout << minusFive << " >= " << threeHalves << " : "
         << (minusFive >= threeHalves) << endl;
}


