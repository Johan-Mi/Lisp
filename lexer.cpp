#include "lexer.hpp"

std::vector<Token> lex(std::string_view sv) {
	std::vector<Token> ret;

	decltype(sv)::const_iterator ident_begin = nullptr;

	while(true) {
		if(sv.empty()) {
			if(ident_begin) {
				ret.emplace_back(TokenType::Ident,
						std::string(ident_begin, sv.cbegin()));
			}
			return ret;
		}

		switch(sv[0]) {
			case '(':
				if(ident_begin) {
					ret.emplace_back(TokenType::Ident,
							std::string(ident_begin, sv.cbegin()));
					ident_begin = nullptr;
				}
				ret.emplace_back(TokenType::LParen);
				break;
			case ')':
				if(ident_begin) {
					ret.emplace_back(TokenType::Ident,
							std::string(ident_begin, sv.cbegin()));
					ident_begin = nullptr;
				}
				ret.emplace_back(TokenType::RParen);
				break;
			case '\'':
				if(ident_begin) {
					ret.emplace_back(TokenType::Ident,
							std::string(ident_begin, sv.cbegin()));
					ident_begin = nullptr;
				}
				ret.emplace_back(TokenType::Quote);
				break;
			case ' ':
			case '\t':
			case '\n':
				if(ident_begin) {
					ret.emplace_back(TokenType::Ident,
							std::string(ident_begin, sv.cbegin()));
					ident_begin = nullptr;
				}
				break;
			default:
				if(!ident_begin) {
					ident_begin = sv.cbegin();
				}
		}
		sv.remove_prefix(1);
	}
}
