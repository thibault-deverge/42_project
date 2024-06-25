#include "Fixed.hpp"

/*
** -------------------------- STATIC CONST VARIABLES ---------------------------
*/
const std::string Fixed::_ERROR_RANGE = "undefined behavior - range is -8388607/8388607";
const int Fixed::_FRAC_SIZE = 8;

/*
** ------------------------- CONSTRUCTOR & DESTRUCTOR --------------------------
*/
Fixed::Fixed(): _value(0) { std::cout << "Default constructor called\n"; }

Fixed::Fixed(const int raw_int)
{
	if (raw_int > 8388607 || raw_int < -8388608)
		throw std::invalid_argument(_ERROR_RANGE);
	std::cout << "Int constructor called" << std::endl;
	setRawBits(raw_int << _FRAC_SIZE);
}

Fixed::Fixed(const float raw_float)
{
	std::cout << "Float constructor called" << std::endl;
	setRawBits(roundf(raw_float * (1 << _FRAC_SIZE)));
}

Fixed::Fixed(const Fixed& rhs)
{
	std::cout << "Copy constructor called" << std::endl;
	*this = rhs;
}

Fixed::~Fixed() { std::cout << "Destructor called" << std::endl; }

/*
** --------------------------------- METHODS ----------------------------------
*/
float	Fixed::toFloat() const { return roundf(getRawBits()) / (1 << _FRAC_SIZE); }
int		Fixed::toInt() const { return getRawBits() >> _FRAC_SIZE; }

/*
** --------------------------------- OVERLOAD ---------------------------------
*/
Fixed& Fixed::operator=(const Fixed& rhs)
{
	std::cout << "Copy assignment operator called" << std::endl;	
	if (this != &rhs)
		setRawBits(rhs.getRawBits());
	return *this;
}

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