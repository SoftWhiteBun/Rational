// Rational.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "pch.h"
#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
#include <sstream>
using namespace std;

int gcd(int A, int B)
{
	while (A != B)
		if (A > B) A -= B;
		else B -= A;
	return A;
}

class Rational {
public:
	Rational();
	Rational(int numerator, int denominator);
	int Numerator() const;
	void NewNumerator(int& new_num);
	int Denominator() const;
	void NewDenominator(int& new_den);
	void Reduction();
private:
	int p; // numerator
	int q; // denominator
};

Rational::Rational() {
	p = 0;
	q = 1;
}

Rational::Rational(int numerator, int denominator) {
	p = numerator;
	q = denominator;
	if (denominator == 0) throw 1;
	else {
		if (q < 0) {
			q = -q;
			p = -p;
		}
		Reduction();
		if (p == 0) q = 1;
	}
}

int Rational::Numerator() const {
	return p;
}

void Rational::NewNumerator(int& new_num) {
	p = new_num;
}

int Rational::Denominator() const {
	return q;
}

void Rational::NewDenominator(int& new_den) {
	q = new_den;
}

void Rational::Reduction() {
	int tmp;
	if (p != 0) tmp = gcd(abs(p), abs(q));
	if (p != 0 && tmp != 1) {
		p /= tmp;
		q /= tmp;
	};
}

bool operator==(const Rational &lhs, const Rational &rhs) {
	return lhs.Numerator() == rhs.Numerator() && lhs.Denominator() == rhs.Denominator();
}

Rational operator+(const Rational &lhs, const Rational &rhs) {
	if (lhs.Denominator() == rhs.Denominator()) return Rational({ lhs.Numerator() + rhs.Numerator(), lhs.Denominator() });
	else {
		Rational result{ lhs.Numerator() * rhs.Denominator() + rhs.Numerator() * lhs.Denominator(), lhs.Denominator() * rhs.Denominator() };
		result.Reduction();
		return result;
	}
}

Rational operator-(const Rational &lhs, const Rational &rhs) {
	if (lhs.Denominator() == rhs.Denominator()) return Rational({ lhs.Numerator() - rhs.Numerator(), lhs.Denominator() });
	else {
		Rational result{ lhs.Numerator() * rhs.Denominator() - rhs.Numerator() * lhs.Denominator(), lhs.Denominator() * rhs.Denominator() };
		result.Reduction();
		return result;
	}
}

Rational operator*(const Rational &lhs, const Rational &rhs) {
	Rational result{ lhs.Numerator() * rhs.Numerator(), lhs.Denominator() * rhs.Denominator() };
	result.Reduction();
	return result;
}

Rational operator/(const Rational &lhs, const Rational &rhs) {
	if (rhs.Numerator() == 0) throw domain_error("domain error");
	else {
		Rational result{ lhs.Numerator() * rhs.Denominator(), lhs.Denominator() * rhs.Numerator() };
		result.Reduction();
		return result;
	}
}

istream& operator >> (istream& stream, Rational& r) { 
	int p, q;
	if (stream >> p && stream.ignore(1) && stream >> q) {
		r = { p, q };
	}
	return stream;
}

ostream& operator<<(ostream& stream, const Rational &r) {
	stream << r.Numerator() << '/' << r.Denominator();
	return stream;
}

bool operator > (Rational a, Rational b) {
	return (a.Numerator() / (double)a.Denominator()) > double(b.Numerator() / (double)b.Denominator());
}

bool operator < (Rational a, Rational b) { //обязательно нужно это дело перегрузить, для использования в map и set
	return (a.Numerator() / (double)a.Denominator()) < (b.Numerator() / (double)b.Denominator());
}


int main() {
	Rational r1, r2;
	char operation;
	cout << "Введите данные. Пример: 11/4+3/4" << endl;
	cin >> r1 >> operation >> r2;
    
	try {
		if (operation == '+') cout << r1 + r2 << endl;
		if (operation == '-') cout << r1 - r2 << endl;
		if (operation == '*') cout << r1 * r2 << endl;
		if (operation == '/') {
			if (r2.Numerator() == 0) cout << "Division by zero" << endl;
			else cout << r1 / r2 << endl;
		}
	} catch (int e) {
	    if (e == 1) cout << "Invalid argument" << endl;
	}
	return 0;
}

