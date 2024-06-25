#include "Fixed.hpp"

/*
** -------------------------- STATIC CONST VARIABLES ---------------------------
*/
const std::string Fixed::_ERROR_RANGE = "undefined behavior - range is -8388607/8388607";
const std::string Fixed::_ERROR_DIVISION = "error: division by 0 is not possible.";
const int Fixed::_FRAC_SIZE = 8;

/*
** -------------------------- STATIC PUBLIC METHODS ----------------------------
*/
// Min() function
Fixed& Fixed::min(Fixed& fp1, Fixed& fp2) { return fp1 < fp2 ? fp1 : fp2; }
const Fixed& Fixed::min(const Fixed& fp1, const Fixed& fp2) { return fp1 < fp2 ? fp1 : fp2; }

// Max() function
Fixed& Fixed::max(Fixed& fp1, Fixed& fp2) { return fp1 > fp2 ? fp1 : fp2; }
const Fixed& Fixed::max(const Fixed& fp1, const Fixed& fp2) { return fp1 > fp2 ? fp1 : fp2; }

/*
** ------------------------- CONSTRUCTOR & DESTRUCTOR --------------------------
*/
Fixed::Fixed(): _value(0) {}

Fixed::Fixed(const int raw_int)
{
	if (raw_int > 8388607 || raw_int < -8388608)
		throw std::invalid_argument(_ERROR_RANGE);
	setRawBits(raw_int << _FRAC_SIZE);
}

Fixed::Fixed(const float raw_float)
{
	setRawBits(roundf(raw_float * (1 << _FRAC_SIZE)));
}

Fixed::Fixed(const Fixed& rhs) { *this = rhs; }

Fixed::~Fixed() {}

/*
** --------------------------------- METHODS ----------------------------------
*/
float	Fixed::toFloat() const { return roundf(getRawBits()) / (1 << _FRAC_SIZE); }
int		Fixed::toInt() const { return getRawBits() >> _FRAC_SIZE; }

/*
** --------------------------------- OVERLOAD ---------------------------------
*/
// Assignment operator
Fixed& Fixed::operator=(const Fixed& rhs)
{
	setRawBits(rhs.getRawBits());
	return *this;
}

// Comparison operators
bool Fixed::operator<(const Fixed& rhs) const { return getRawBits() < rhs.getRawBits(); }
bool Fixed::operator<=(const Fixed& rhs) const { return getRawBits() <= rhs.getRawBits(); }
bool Fixed::operator==(const Fixed& rhs) const { return getRawBits() == rhs.getRawBits(); }
bool Fixed::operator>(const Fixed& rhs) const { return getRawBits() > rhs.getRawBits(); }
bool Fixed::operator>=(const Fixed& rhs) const { return getRawBits() >= rhs.getRawBits(); }
bool Fixed::operator!=(const Fixed& rhs) const { return getRawBits() != rhs.getRawBits(); }

// Arithmetic operators
Fixed Fixed::operator+(const Fixed& rhs) const { return Fixed(this->toFloat() + rhs.toFloat()); }
Fixed Fixed::operator-(const Fixed& rhs) const { return Fixed(this->toFloat() - rhs.toFloat()); }
Fixed Fixed::operator*(const Fixed& rhs) const { return Fixed(this->toFloat() * rhs.toFloat()); }
Fixed Fixed::operator/(const Fixed& rhs) const
{
	if (rhs.toFloat() == 0)
		throw std::invalid_argument(_ERROR_DIVISION);
	return Fixed(this->toFloat() / rhs.toFloat());
}

// Increment operators
Fixed& Fixed::operator++()
{
	this->setRawBits(this->getRawBits() + 1);
	return *this;
}

Fixed Fixed::operator++(int)
{
	Fixed temp(*this);
	this->setRawBits(this->getRawBits() + 1);
	return temp;
}

Fixed& Fixed::operator--()
{
	this->setRawBits(this->getRawBits() - 1);
	return *this;
}

Fixed Fixed::operator--(int)
{
	Fixed temp(*this);
	this->setRawBits(this->getRawBits() - 1);
	return temp;
}

// Insertion operator
std::ostream& operator<<(std::ostream& ostream, const Fixed& fixed_pt)
{
	ostream << fixed_pt.toFloat();
	return ostream;
}

/*
** --------------------------------- ACCESSOR ---------------------------------
*/
int		Fixed::getRawBits() const { return _value; }
void	Fixed::setRawBits(const int raw) { _value = raw; }