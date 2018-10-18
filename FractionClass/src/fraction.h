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
	Fraction& operator++();						// pre-increment
	Fraction operator++(int unused);			// post-increment
	Fraction& operator-();
	Fraction& operator+=(const Fraction right);
	int numerator();
	int denominator();
	void normalize();

private:
	void fractionSign();
	int gcd(int,int);
	int mNumerator;
	int mDenominator;

// Friend Function Overloads
friend Fraction operator+(const Fraction& left, const Fraction& right);
friend Fraction operator-(const Fraction& left, const Fraction& right);
friend Fraction operator*(const Fraction& left, const Fraction& right);
friend Fraction operator/(const Fraction& left, const Fraction& right);
friend Fraction operator+=(const Fraction& left, const Fraction& right);
friend bool operator<(const Fraction& left, const Fraction& right);
friend bool operator<=(const Fraction& left, const Fraction& right);
friend bool operator==(const Fraction& left, const Fraction& right);
friend bool operator!=(const Fraction& left, const Fraction& right);
friend bool operator>=(const Fraction& left, const Fraction& right);
friend bool operator>(const Fraction& left, const Fraction& right);

friend ostream& operator<<(ostream& out, const Fraction& value);
friend istream& operator>>(istream& in, Fraction& value);
};
