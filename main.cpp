#include <cstdlib>
#include <iostream>

#include "types.hpp"
#include "functions.hpp"
#include "to-string.hpp"
#include "lexer.hpp"
#include "parser.hpp"

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
			X(cons(X(Symbol{"cdr"}), X(BuiltinFunction{wrapped_cdr}))));
#undef X

	eval_print("42", env);
	eval_print("()", env);
	eval_print("'()", env);
	eval_print("(car '(4 9 16))", env);

	return EXIT_SUCCESS;
}
