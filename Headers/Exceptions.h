//
// Created by Adi on 5/16/2023.
//

#ifndef OOP_EXCEPTIONS_H
#define OOP_EXCEPTIONS_H

#include <iostream>

class gameErrors : public std::logic_error {
public:

    explicit gameErrors(const char *exp);

};

class not_enough_money : public gameErrors {

public:
    explicit not_enough_money(const char *exp = "not enough money");

};

class max_no_houses : public gameErrors {

public:
    explicit max_no_houses(const char *exp = "allready at 5 houses");
};

class owned : public gameErrors {
public:
    explicit owned(const char *exp = "allready has an owner");

};

class out_of_charges : public gameErrors {
public:
    explicit out_of_charges(const char *exp = "no more ability charges");
};


#endif //OOP_EXCEPTIONS_H
