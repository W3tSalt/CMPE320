/*
 * fraction.cpp
 *
 *  Created on: Oct. 17, 2018
 *      Author: Ryan
 */

#include <iostream>
#include <fstream>
#include <string>
#include <cmath>

#include "fraction.h"

using namespace std;

FractionException::FractionException(const string& message): message(message) {}
string& FractionException::what(){
	return message;
}

/*----------------------- Constructors and Non-overloading Methods ----------------------------------*/

Fraction::Fraction() {
	mNumerator = 0;
	mDenominator = 1;
}

Fraction::Fraction(const int& num) {
	mNumerator = num;
	mDenominator = 1;
}

Fraction::Fraction(const int& num, const int& denom) {
	if(denom == 0) { throw FractionException("ERROR: Zero denominator"); }
	else {
		mNumerator = num;
		mDenominator = denom;
		normalize();
	}
}

int Fraction::numerator() {
	int copy(mNumerator);
	return copy;
}

int Fraction::denominator() {
	int copy(mDenominator);
	return copy;
}

void Fraction::normalize() {
	fractionSign();
	int GCD = gcd(abs(mNumerator), abs(mDenominator));
	mNumerator = mNumerator/GCD;
	mDenominator = mDenominator/GCD;
}

int Fraction::gcd(int n, int m) {
	if(m<=n && n%m==0) {
		return m;
	} else if(n<m) {
		return gcd(m,n);
	} else {
		int temp = n%m;
		return gcd(m,temp);
	}
}

void Fraction::fractionSign() {
	if(mNumerator >= 0 && mDenominator < 0) {
		mNumerator = mNumerator*-1;
		mDenominator = mDenominator*-1;
	} else if(mNumerator < 0 && mDenominator < 0) {
		mNumerator = mNumerator*-1;
		mDenominator = mDenominator*-1;
	}
	return;
}

/*----------------------------------------- Overloading --------------------------------------------*/

Fraction& Fraction::operator++() {
	mNumerator += mDenominator;
	normalize();
	return *this;
}

Fraction Fraction::operator++(int unused) {
	Fraction clone(mNumerator, mDenominator);
	mNumerator += mDenominator;
	normalize();
	return clone;
}

Fraction& Fraction::operator-() {
	mNumerator = -1*mNumerator;
	return *this;
}

Fraction& Fraction::operator+=(const Fraction right) {
	this->mNumerator = (this->mNumerator*right.mDenominator)+(right.mNumerator*this->mDenominator);
	this->mDenominator = this->mDenominator*right.mDenominator;
	this->normalize();
	return *this;
}

Fraction operator+(const Fraction& left, const Fraction& right) {
	Fraction temp((left.mNumerator*right.mDenominator)+(right.mNumerator*left.mDenominator), left.mDenominator*right.mDenominator);
	temp.normalize();
	return temp;
}

Fraction operator-(const Fraction& left, const Fraction& right) {
	Fraction temp((left.mNumerator*right.mDenominator)-(right.mNumerator*left.mDenominator), left.mDenominator*right.mDenominator);
	temp.normalize();
	return temp;
}

Fraction operator*(const Fraction& left, const Fraction& right) {
	Fraction temp(left.mNumerator*right.mNumerator, left.mDenominator*right.mDenominator);
	temp.normalize();
	return temp;
}

Fraction operator/(const Fraction& left, const Fraction& right) {
	Fraction temp(left.mNumerator*right.mDenominator, right.mNumerator*left.mDenominator);
	temp.normalize();
	return temp;
}

bool operator<(const Fraction& left, const Fraction& right) {
	if((double)(left.mNumerator)/(double)(left.mDenominator) < (double)(right.mNumerator)/(double)(right.mDenominator)) { return true; }
	else { return false; }
}

bool operator<=(const Fraction& left, const Fraction& right) {
	if((double)(left.mNumerator)/(double)(left.mDenominator) <= (double)(right.mNumerator)/(double)(right.mDenominator)) { return true; }
	else { return false; }
}

bool operator==(const Fraction& left, const Fraction& right) {
	if((double)(left.mNumerator)/(double)(left.mDenominator) == (double)(right.mNumerator)/(double)(right.mDenominator)) { return true; }
	else { return false; }
}

bool operator!=(const Fraction& left, const Fraction& right) {
	if((double)(left.mNumerator)/(double)(left.mDenominator) != (double)(right.mNumerator)/(double)(right.mDenominator)) { return true; }
	else { return false; }
}

bool operator>=(const Fraction& left, const Fraction& right) {
	if((double)(left.mNumerator)/(double)(left.mDenominator) >= (double)(right.mNumerator)/(double)(right.mDenominator)) { return true; }
	else { return false; }
}

bool operator>(const Fraction& left, const Fraction& right) {
	if((double)(left.mNumerator)/(double)(left.mDenominator) > (double)(right.mNumerator)/(double)(right.mDenominator)) { return true; }
	else { return false; }
}

ostream& operator<<(ostream& out, const Fraction& value) {
	out << value.mNumerator << '/' << value.mDenominator;
	return out;
}

istream& operator>>(istream& in, Fraction& value) {
	string temp;
	cin >> ws;
	cin >> temp;
	if(temp.find('/') == temp.npos) {
		value = Fraction(stoi(temp));
		return in;
	}
	string numer(temp.begin(),temp.end()-(temp.size()-temp.find('/')));
	string denom(temp.begin()+temp.find('/')+1, temp.end());
	if(stoi(denom) == 0) { throw FractionException("ERROR: Zero denominator invalid"); }
	else {
		value = Fraction(stoi(numer), stoi(denom));
		return in;
	}
}
