#pragma once
#include <iostream>
#include <cmath>

using namespace std;
class Rational
{
public:
Rational(int numerator = 0, int denominator = 1) :numerator_(numerator), denominator_(denominator) {}
Rational& operator +=(const Rational& lhs)
{
	numerator_ = numerator_ * lhs.denominator_ + lhs.numerator_*denominator_;
	denominator_ = denominator_ * lhs.denominator_;
	return (*this);
}
Rational& operator +=(const int& lhs)
{
	numerator_ = numerator_ + lhs * denominator_;
	return (*this);
}
Rational& operator -=(const int& lhs)
{
	numerator_ = numerator_ - lhs * denominator_;
	return (*this);
}
Rational& operator *=( const int& lhs)
{
	numerator_ = numerator_ * lhs;
	return (*this);
}
Rational& operator /=(const int& lhs)
{
	denominator_ = denominator_ * lhs;
	return (*this);
}
Rational& operator -=(const Rational& lhs)
{
	numerator_ = numerator_ * lhs.denominator_ - lhs.numerator_*denominator_;
	denominator_ = denominator_ * lhs.denominator_;
	return (*this);
}
Rational& operator *=(const Rational& lhs)
{
	numerator_ = numerator_ * lhs.numerator_;
	denominator_ = denominator_ * lhs.denominator_;
	return (*this);
}
Rational& operator /=(const Rational& lhs)
{
	numerator_ = numerator_ * lhs.denominator_;
	denominator_ = denominator_ * lhs.numerator_;
	return (*this);
}
Rational operator -()const
{
	return(Rational(-numerator_, denominator_));
}
Rational operator +()const
{
	return(*this);
}
private:
    int numerator_;
    int denominator_;
};