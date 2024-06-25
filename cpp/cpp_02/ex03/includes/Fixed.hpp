#pragma once

#include <iostream>
#include <string>
#include <cmath>

class Fixed
{
public:
	// Static public methods
	static Fixed& min(Fixed& fp1, Fixed& fp2);
	static const Fixed& min(const Fixed& fp1, const Fixed& fp2);
	static Fixed& max(Fixed& fp1, Fixed& fp2);
	static const Fixed& max(const Fixed& fp1, const Fixed& fp2);

private:
	// static const variables
	static const std::string _ERROR_RANGE;
	static const std::string _ERROR_DIVISION;
	static const int _FRAC_SIZE;

	// member attribute
	int _value;

public:
	// Constructors/destructor
	Fixed();
	Fixed(const int raw_int);
	Fixed(const float raw_float);
	Fixed(const Fixed& rhs);
	~Fixed();		

	// Operators overloads
	Fixed& operator=(const Fixed& rhs);

	bool operator<(const Fixed& rhs) const;
	bool operator<=(const Fixed& rhs) const;
	bool operator>(const Fixed& rhs) const;
	bool operator>=(const Fixed& rhs) const;
	bool operator==(const Fixed& rhs) const;
	bool operator!=(const Fixed& rhs) const;

	Fixed operator+(const Fixed& rhs) const;
	Fixed operator-(const Fixed& rhs) const;
	Fixed operator*(const Fixed& rhs) const;
	Fixed operator/(const Fixed& rhs) const;

	Fixed& operator++();
	Fixed operator++(int);
	Fixed& operator--();
	Fixed operator--(int);

	// Accessers
	int		getRawBits() const;
	void	setRawBits(const int raw);

	// Public methods
	float	toFloat() const;
	int		toInt() const;
};

// insertion operator overload
std::ostream& operator<<(std::ostream& ostream, const Fixed& fixed_pt);