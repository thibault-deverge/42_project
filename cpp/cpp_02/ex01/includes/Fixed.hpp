#pragma once

#include <iostream>
#include <cmath>

class Fixed
{
private:
	static const std::string _ERROR_RANGE;
	static const int _FRAC_SIZE;

	int _value;

public:
	// Constructors / destructor
	Fixed();
	Fixed(const int raw_int);
	Fixed(const float raw_float);
	Fixed(const Fixed& rhs);
	~Fixed();		

	// Operator overload
	Fixed& operator=(const Fixed& rhs);

	// Accessers
	int		getRawBits() const;
	void	setRawBits(const int raw);

	// Member methods
	float	toFloat() const;
	int		toInt() const;
};

std::ostream& operator<<(std::ostream& of, const Fixed& fixed_pt);