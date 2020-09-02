#pragma once

#include "types.hpp"

std::shared_ptr<Object const> wrapped_car(Cons const &args, Cons const &env);
std::shared_ptr<Object const> wrapped_cdr(Cons const &args, Cons const &env);
std::shared_ptr<Object const> wrapped_quote(Cons const &args, Cons const &env);
std::shared_ptr<Object const> wrapped_add(Cons const &args, Cons const &env);
std::shared_ptr<Object const> wrapped_sub(Cons const &args, Cons const &env);
std::shared_ptr<Object const> wrapped_mul(Cons const &args, Cons const &env);
