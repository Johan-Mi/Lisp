#include "lexer.hpp"

std::string token_type_to_str(TokenType const t) {
	switch(t) {
		case TokenType::LParen:
			return "LParen";
		case TokenType::RParen:
			return "RParen";
		case TokenType::Quote:
			return "Quote";
		case TokenType::Ident:
			return "Ident";
	}
	return "Invalid TokenType";
}

std::vector<Token> lex(std::string_view sv) {
	std::vector<Token> ret;

	Token token_buffer{};

	while(true) {
		if(sv.empty()) {
			if(!token_buffer.str.empty()) {
				ret.push_back(token_buffer);
			}
			return ret;
		}

		switch(sv[0]) {
			case '(':
				if(!token_buffer.str.empty()) {
					ret.push_back(token_buffer);
					token_buffer.str.clear();
				}
				ret.push_back({TokenType::LParen});
				break;
			case ')':
				if(!token_buffer.str.empty()) {
					ret.push_back(token_buffer);
					token_buffer.str.clear();
				}
				ret.push_back({TokenType::RParen});
				break;
			case '\'':
				if(!token_buffer.str.empty()) {
					ret.push_back(token_buffer);
					token_buffer.str.clear();
				}
				ret.push_back({TokenType::Quote});
				break;
			case ' ':
			case '\t':
			case '\n':
				if(!token_buffer.str.empty()) {
					ret.push_back(token_buffer);
					token_buffer.str.clear();
				}
				break;
			default:
				token_buffer.str += sv[0];
				token_buffer.type = TokenType::Ident;
		}
		sv.remove_prefix(1);
	}
}
