#include <cstdlib>
#include <iostream>

#include "types.hpp"
#include "functions.hpp"
#include "to-string.hpp"
#include "lexer.hpp"
#include "parser.hpp"

int main() {
	auto const lexed = lex("(car ())");
	auto const parsed = parse_expression(begin(lexed), end(lexed));
	if(parsed) {
		std::cout << to_string(std::get<std::shared_ptr<Object const>>(*parsed))
				  << '\n';
	} else {
		std::cout << "Couldn't parse expression\n";
	}

	return EXIT_SUCCESS;
}
