#include "parser.hpp"
#include <cstdint>

void munch(std::string_view &sv) {
	sv.remove_prefix(sv.find_first_not_of(" \t\n"));
}

std::optional<std::tuple<Symbol, std::string_view>> parse_symbol(
		std::string_view sv) {
	// symbol: symbol_initial symbol_subsequent*
	// TODO Add peculiar identifiers (+ | - | ...)

	uint_fast8_t state = 0;

	auto start = cbegin(sv);

	while(true) {
		if(sv.empty()) {
			state = state == 1 ? 3 : 2;
		}

		switch(state) {
			case 0:
				if(char_is_symbol_initial(sv[0])) {
					sv.remove_prefix(1);
					state = 1;
				} else {
					state = 2;
				}
				break;
			case 1:
				if(char_is_symbol_subsequent(sv[0])) {
					sv.remove_prefix(1);
				} else if(char_is_delimiter(sv[0])) {
					state = 3;
				} else {
					state = 2;
				}
				break;
			case 2:
				return std::nullopt;
			case 3:
				return {{{std::string(start, begin(sv))}, sv}};
		}
	}
}
