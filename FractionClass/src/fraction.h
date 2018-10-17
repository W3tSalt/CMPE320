/*
 * fraction.h
 *
 *  Created on: Oct. 17, 2018
 *      Author: Ryan
 */

#pragma once

#include <string>
#include <vector>
using namespace std;

class FractionException {
public:
	FractionException(const string& message);
	string& what();

private:
	string message;
};

////////////////////////////////////////////////////////////////////////////////////////////////////////

class Fraction {
public:
	Fraction();
	Fraction(const int& num);
	Fraction(const int& num,const int& denom);
	explicit operator float() const;
	Fraction& operator++();						// pre-increment
	Fraction operator++(int unused);			// post-increment

private:
	int numerator;
	int denominator;
};


// Friend Function Overloads
friend Fraction operator-(const Fraction& left, Fraction& right);
friend Fraction operator+(const Fraction& left, Fraction& right);
friend Fraction operator*(const Fraction& left, Fraction& right);
friend Fraction operator/(const Fraction& left, Fraction& right);
friend Fraction operator<(const Fraction& left, Fraction& right);
friend Fraction operator<=(const Fraction& left, Fraction& right);
friend Fraction operator==(const Fraction& left, Fraction& right);
friend Fraction operator!=(const Fraction& left, Fraction& right);
friend Fraction operator>=(const Fraction& left, Fraction& right);
friend Fraction operator>(const Fraction& left, Fraction& right);

friend ostream& operator<<(ostream& out, const Fraction& value);
