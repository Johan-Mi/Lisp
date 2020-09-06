#include <cstdlib>
#include <iostream>
#include <fstream>
#include <streambuf>

#include "types.hpp"
#include "functions.hpp"
#include "to-string.hpp"
#include "lexer.hpp"
#include "parser.hpp"
#include "wrapped.hpp"

int main() {
#define X std::make_shared<Object const>
	auto const env = make_list(
			X(Cons{X(Symbol{"car"}), X(BuiltinFunction{wrapped_car})}),
			X(Cons{X(Symbol{"cdr"}), X(BuiltinFunction{wrapped_cdr})}),
			X(Cons{X(Symbol{"cons"}), X(BuiltinFunction{wrapped_cons})}),
			X(Cons{X(Symbol{"lambda"}), X(BuiltinFunction{wrapped_lambda})}),
			X(Cons{X(Symbol{"+"}), X(BuiltinFunction{wrapped_add})}),
			X(Cons{X(Symbol{"-"}), X(BuiltinFunction{wrapped_sub})}),
			X(Cons{X(Symbol{"*"}), X(BuiltinFunction{wrapped_mul})}),
			X(Cons{X(Symbol{"quote"}), X(BuiltinFunction{wrapped_quote})}));
#undef X

	std::ifstream file_stream("program.lisp");
	std::string program_str((std::istreambuf_iterator<char>(file_stream)),
			std::istreambuf_iterator<char>());
	file_stream.close();
	auto lexed = lex(program_str);
	if(auto const parsed = parse_expressions(begin(lexed), end(lexed))) {
		for(auto const &a :
				std::get<std::vector<std::shared_ptr<Object const>>>(*parsed)) {
			std::cout << to_string(eval(a, env)) << '\n';
		}
	} else {
		std::cerr << "Couldn't parse file\n";
	}

	return EXIT_SUCCESS;
}
