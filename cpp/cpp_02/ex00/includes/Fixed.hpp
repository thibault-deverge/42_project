#pragma once

#include <iostream>

class Fixed
{
private:
	static const int _FRAC_SIZE = 8;

	int _value;

public:
	Fixed();
	Fixed(const Fixed& rhs);
	~Fixed();		

	Fixed& operator=(const Fixed& rhs);

	int		getRawBits() const;
	void	setRawBits(const int raw);
};