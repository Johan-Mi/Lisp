#pragma once

#include "types.hpp"

std::unique_ptr<LispObject> car(LispObject &obj);
std::unique_ptr<LispObject> car(LispCons &obj);
std::unique_ptr<LispObject> car(LispNil &obj);
std::unique_ptr<LispObject> cdr(LispObject &obj);
std::unique_ptr<LispObject> cdr(LispCons &obj);
std::unique_ptr<LispObject> cdr(LispNil &obj);
