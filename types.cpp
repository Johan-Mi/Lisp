#include <type_traits>

#include "types.hpp"

Cons::Cons(Cons const &other)
	: first(std::make_unique<Object>(*other.first))
	, second(std::make_unique<Object>(*other.second)) {}

Cons::Cons(std::unique_ptr<Object> const &first,
		std::unique_ptr<Object> const &second)
	: first(std::make_unique<Object>(*first))
	, second(std::make_unique<Object>(*second)) {}
