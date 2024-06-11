/*
 * Lexing.hpp
 *
 *  Created on: May 27, 2024
 *      Author: necar
 */

#pragma once

#include <string>
#include <iostream>
#include <vector>
#include <sstream>
#include <memory>
#include <boost/lexical_cast.hpp>

using namespace std;

struct Token {
	enum Type {integer, plus, minus, lparen, rparen} type;
	string text;

	Token(Type t, const string& txt): type(t), text(txt) {}

	friend ostream& operator<<(ostream& os, const Token& token) {
		os << "`" << token.text << "`";
		return os;
	}
};

vector<Token> lex(const string& input) {
	vector<Token> result;

	for (int i=0; i<input.length(); i++) {
		char c = input[i];
		switch (input[i]) {
		case '+':
			result.push_back({Token::Type::plus, {c}});
			break;
		case '-':
			result.push_back({Token::Type::minus, {c}});
			break;
		case '(':
			result.push_back({Token::Type::lparen, {c}});
			break;
		case ')':
			result.push_back({Token::Type::rparen, {c}});
			break;
		default:
			ostringstream oss;
			oss << c;
			for (int j=i+1; j < input.length(); j++) {
				if (isdigit(input[j])) {
					oss << input[j];
					i++;
				} else {
					result.push_back({Token::integer, oss.str()});
					break;
				}
			}
		}
	}

	return result;
}

struct Element {
	virtual int eval() const = 0;
};

struct Integer: Element {
	int value;

	Integer(int v): value(v) {}

	int eval() const override {
		return value;
	}
};

struct BinaryOperation: Element {
	enum Type {addition, subtraction} type;
	shared_ptr<Element> left, right;

	int eval() const override {
		switch (type) {
		case addition:
			return left->eval() + right->eval();
			break;
		case subtraction:
			return left->eval() - right->eval();
			break;
		}
	}
};

shared_ptr<Element> parse(const vector<Token>& tokens) {
	auto result = make_unique<BinaryOperation>();
	bool have_lhs = false;

	for (int i=0; i<tokens.size(); i++) {
		Token token = tokens[i];
		switch (token.type) {
			case Token::integer:
			{
				int value = boost::lexical_cast<int>(token.text);
				auto integer = make_shared<Integer>(value);
				if (!have_lhs) {
					result->left = integer;
					have_lhs = true;
				} else {
					result->right = integer;
				}
			}
				break;
			case Token::plus:
				result->type = BinaryOperation::addition;
				break;
			case Token::minus:
				result->type = BinaryOperation::subtraction;
				break;
			case Token::lparen:
			{
				int j = i;
				for (; j < tokens.size(); j++) {
					if (tokens[j].type == Token::rparen) {
						break;
					}
				}
				vector<Token> sub_tokens(tokens.begin() + i + 1, tokens.begin() + j);
				shared_ptr<Element> element = parse(sub_tokens);
				if (!have_lhs) {
					result->left = element;
					have_lhs = true;
				} else {
					result->right = element;
				}
				i = j;
			}
				break;
		}
	}

	return result;
}

int interpreterMain() {
	string ipt = "(13-4)-(12+1)";
	vector<Token> tokens = lex(ipt);
	for (const Token& token: tokens) {
		cout << token << "  ";
	}
	cout << endl;

	auto parsed = parse(tokens);
	cout << ipt << " = " << parsed->eval() << endl;

	return 0;
}
