#include "Fixed.hpp"

/*
** ------------------------- CONSTRUCTOR & DESTRUCTOR --------------------------
*/
Fixed::Fixed(): _value(0) 
{
	std::cout << "Default constructor called" << std::endl;
}

Fixed::Fixed(const Fixed& rhs)
{
	std::cout << "Copy constructor called" << std::endl;
	*this = rhs;
}

Fixed::~Fixed() 
{
	std::cout << "Destructor called" << std::endl;
}

/*
** --------------------------------- OVERLOAD ---------------------------------
*/
Fixed& Fixed::operator=(const Fixed& rhs)
{
	std::cout << "Copy assignment operator called" << std::endl;	
	if (this != &rhs)
		this->_value = rhs.getRawBits();
	return *this;
}

/*
** --------------------------------- ACCESSOR ---------------------------------
*/
int		Fixed::getRawBits() const
{
	std::cout << "getRawBits member function called" << std::endl;
	return _value;
}

void	Fixed::setRawBits(const int raw)
{
	_value = raw;
}