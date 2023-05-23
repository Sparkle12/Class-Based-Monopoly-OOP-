//
// Created by Adi on 5/16/2023.
//

#include "../Headers/Exceptions.h"

game_error::game_error(const char *exp) : std::logic_error(exp) {}

not_enough_money::not_enough_money(const char *exp) : game_error(exp) {}

max_no_houses::max_no_houses(const char *exp) : game_error(exp) {}

owned::owned(const char *exp) : game_error(exp) {}

out_of_charges::out_of_charges(const char *exp) : game_error(exp) {}
