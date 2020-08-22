#pragma once

#include <vector>
#include <string>
#include <string_view>

enum struct TokenType { LParen, RParen, Quote, Ident };

struct Token {
	TokenType type;
	std::string str;
};

constexpr std::string_view token_type_to_str(TokenType const t) {
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
}

std::vector<Token> lex(std::string_view sv);
