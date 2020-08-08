#pragma once

#include <type_traits>

template<class T, class... U>
inline constexpr bool is_any_of = (std::is_same<T, U>() || ...);

static_assert(is_any_of<int, int>);
static_assert(is_any_of<int, char, int, bool>);
static_assert(!is_any_of<char, float>);
static_assert(!is_any_of<char, float, bool>);
