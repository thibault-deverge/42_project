#include <iostream>
#include <ctime>
#include "Account.hpp"

/*
********** PRIVATES VISIBILITY **********
*/
/* -----  Static variable ----- */
int Account::_nbAccounts = 0;
int Account::_totalAmount = 0;
int Account::_totalNbDeposits = 0;
int Account::_totalNbWithdrawals = 0;

/* ----- Static method ----- */
void Account::_displayTimestamp(void)
{
    std::time_t rawtime = std::time(0);
    struct tm*  time;
    char       buffer[64];

    time = localtime(&rawtime);
    strftime(buffer, 64, "[%Y%m%d_%H%M%S] ", time);
    std::cout << buffer;
}

/*
********** PUBLIC VISIBILITY **********
*/
/* ----- Constructors & Destructor*/
Account::Account() 
{
    _accountIndex = getNbAccounts();
    _amount = 0;
    _nbDeposits = 0;
    _nbWithdrawals = 0;
}

Account::Account(int initial_deposit)
{
    // Update member variables
    _accountIndex = getNbAccounts();
    _amount = initial_deposit;
    _nbDeposits = 0;
    _nbWithdrawals = 0;
    // Update static variables
    _totalAmount += initial_deposit;
    ++_nbAccounts;
    // Print creation's informations
    _displayTimestamp();
    std::cout << "index:" << _accountIndex << ';';
    std::cout << "amount:" << _amount << ';';
    std::cout << "created" << std::endl;
}

Account::~Account() 
{
    _displayTimestamp();
    std::cout << "index:" << _accountIndex << ';';
    std::cout << "amount:" << _amount << ';';
    std::cout << "closed" << std::endl;
}

/* ----- Static Methods ----- */
void Account::displayAccountsInfos(void)
{
    _displayTimestamp();
    std::cout << "accounts:" << getNbAccounts() << ';';
    std::cout << "total:" << getTotalAmount() << ';';
    std::cout << "deposits:" << getNbDeposits() << ';';
    std::cout << "withdrawals:" << getNbWithdrawals() << std::endl;
}

/* ----- Getters ----- */
int Account::getNbAccounts(void) { return _nbAccounts; }
int Account::getTotalAmount(void) { return _totalAmount; }
int Account::getNbDeposits(void) { return _totalNbDeposits; }
int Account::getNbWithdrawals(void) { return _totalNbWithdrawals; }

/* ----- Member's Method ----- */
void    Account::makeDeposit(int deposit)
{
    _displayTimestamp();
    // Display old status of account.
    std::cout << "index:" << _accountIndex << ';';
    std::cout << "p_amount:" << checkAmount() << ';';
    std::cout << "deposits:" << deposit << ';';
    // Update account with new deposit.
    _amount += deposit;
    _totalAmount += deposit;
    ++_nbDeposits; 
    ++_totalNbDeposits;
    // Display updated informations.
    std::cout << "amount:" << checkAmount() << ';';
    std::cout << "nb_deposit:" << _nbDeposits << std::endl;
}

bool    Account::makeWithdrawal(int withdrawal)
{
    _displayTimestamp();
    // Display old status of account.
    std::cout << "index:" << _accountIndex << ';';
    std::cout << "p_amount:" << checkAmount() << ';';
    // Check if withdrawal is valid and execute it or not.
    if (checkAmount() - withdrawal < 0)
    {
        std::cout << "withdrawal:" << "refused" << std::endl;
        return false;
    }
    else
    {
        _amount -= withdrawal;
        _totalAmount -= withdrawal;
        ++_nbWithdrawals;
        ++_totalNbWithdrawals;
        std::cout << "withdrawal:" << withdrawal << ';';
        std::cout << "amount:" << checkAmount() << ';';
        std::cout << "nb_withdrawals:" << _nbWithdrawals << std::endl;
        return true;
    }
}

int     Account::checkAmount(void) const { return _amount; }

void    Account::displayStatus(void) const
{
    _displayTimestamp();
    std::cout << "index:" << _accountIndex << ';';
    std::cout << "amount:" << checkAmount() << ';';
    std::cout << "deposits:" << _nbDeposits << ';';
    std::cout << "withdrawals:" << _nbWithdrawals << std::endl;
}