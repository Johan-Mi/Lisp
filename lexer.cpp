#include "lexer.hpp"

std::vector<Token> lex(std::string_view sv) {
	std::vector<Token> ret;

	Token current_token;

	while(true) {
		if(sv.empty()) {
			if(!current_token.str.empty()) {
				ret.push_back(current_token);
			}
			return ret;
		}

		switch(sv[0]) {
			case '(':
				if(!current_token.str.empty()) {
					ret.push_back(current_token);
					current_token.str.clear();
				}
				ret.emplace_back(TokenType::LParen);
				break;
			case ')':
				if(!current_token.str.empty()) {
					ret.push_back(current_token);
					current_token.str.clear();
				}
				ret.emplace_back(TokenType::RParen);
				break;
			case '\'':
				if(!current_token.str.empty()) {
					ret.push_back(current_token);
					current_token.str.clear();
				}
				ret.emplace_back(TokenType::Quote);
				break;
			case ' ':
			case '\t':
			case '\n':
				if(!current_token.str.empty()) {
					ret.push_back(current_token);
					current_token.str.clear();
				}
				break;
			default:
				current_token.str += sv[0];
				current_token.type = TokenType::Ident;
		}
		sv.remove_prefix(1);
	}
}
