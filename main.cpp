#include <cstdlib>
#include <iostream>

#include "types.hpp"
#include "functions.hpp"
#include "to-string.hpp"
#include "lexer.hpp"
#include "parser.hpp"
#include "wrapped.hpp"

void eval_print(std::string_view const expr_str, Cons const &env) {
	auto const lexed = lex(expr_str);
	auto const parsed = parse_expression(begin(lexed), end(lexed));
	if(parsed) {
		auto const expr = std::get<std::shared_ptr<Object const>>(*parsed);
		std::cout << ">>> " << expr_str << '\n'
				  << to_string(eval(expr, env)) << '\n';
	} else {
		std::cerr << "Couldn't parse expression\n";
	}
}

int main() {
#define X std::make_shared<Object const>
	auto const env = make_list(
			X(cons(X(Symbol{"car"}), X(BuiltinFunction{wrapped_car}))),
			X(cons(X(Symbol{"cdr"}), X(BuiltinFunction{wrapped_cdr}))),
			X(cons(X(Symbol{"cons"}), X(BuiltinFunction{wrapped_cons}))),
			X(cons(X(Symbol{"+"}), X(BuiltinFunction{wrapped_add}))),
			X(cons(X(Symbol{"-"}), X(BuiltinFunction{wrapped_sub}))),
			X(cons(X(Symbol{"*"}), X(BuiltinFunction{wrapped_mul}))),
			X(cons(X(Symbol{"quote"}), X(BuiltinFunction{wrapped_quote}))));
#undef X

	constexpr std::string_view tests[] = {
			"42",
			"()",
			"'()",
			"(quote (1 2 3 4 5))",
			"(car '(4 9 16))",
			"(cdr '(abc def))",
			"(cdr '(abc . def))",
			"(+)",
			"(+ 10)",
			"(+ 10 20)",
			"(+ 10 20 50)",
			"(-)",
			"(- 10)",
			"(- 10 30)",
			"(- 10 20 50)",
			"(*)",
			"(* 10)",
			"(* 10 20)",
			"(* 10 20 50)",
			"(cons (+ 2 3) (* 2 3))",
	};

	for(auto const s : tests) {
		eval_print(s, env);
	}

	return EXIT_SUCCESS;
}
