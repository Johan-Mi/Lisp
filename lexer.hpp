#pragma once

#include <vector>
#include <string>
#include <string_view>

enum struct TokenType {
	LParen, RParen, Quote, Ident 
};

struct Token {
	TokenType type;
	std::string str;
};

std::string token_type_to_str(TokenType const t);

std::vector<Token> lex(std::string_view sv);
