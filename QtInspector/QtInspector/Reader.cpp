#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <sstream>
#include <fstream>
#include <cstring>
#include <QString>
#include <QDebug>
#include "Reader.h"

struct Reader::token {
	std::string value;
	token_type type;
	token(std::string value = "", token_type type = UNKNOWN) : value(value), type(type) {}
};
bool Reader::is_whitespace(const char c) {
	return isspace(c);
}
int Reader::next_whitespace(const std::string& source, int i) {
	while (i < (int)source.length()) {
		if (source[i] == '"') {
			i++;
			while (i < (int)source.length() && (source[i] != '"' || source[i - 1] == '\\')) i++;
		}
		if (source[i] == '\'') {
			i++;
			while (i < (int)source.length() && (source[i] != '\'' || source[i - 1] == '\\')) i++;
		}
		if (is_whitespace(source[i])) return i;
		i++;
	}
	return (int)source.length();
}
int Reader::skip_whitespaces(const std::string& source, int i) {
	while (i < (int)source.length()) {
		if (!is_whitespace(source[i])) return i;
		i++;
	}
	return -1;
}

std::vector<Reader::token> Reader::tokenize(std::string source) {
	source += " ";
	std::vector<token> tokens;
	int index = skip_whitespaces(source, 0);
	while (index >= 0) {
		int next = next_whitespace(source, index);
		std::string str = source.substr(index, next - index);

		size_t k = 0;
		while (k < str.length()) {
			if (str[k] == '"') {
				size_t tmp_k = k + 1;
				while (tmp_k < str.length() && (str[tmp_k] != '"' || str[tmp_k - 1] == '\\')) tmp_k++;
				tokens.push_back(token(str.substr(k + 1, tmp_k - k - 1), STRING));
				k = tmp_k + 1;
				continue;
			}
			if (str[k] == '\'') {
				size_t tmp_k = k + 1;
				while (tmp_k < str.length() && (str[tmp_k] != '\'' || str[tmp_k - 1] == '\\')) tmp_k++;
				tokens.push_back(token(str.substr(k + 1, tmp_k - k - 1), STRING));
				k = tmp_k + 1;
				continue;
			}
			if (str[k] == ',') {
				tokens.push_back(token(",", COMMA));
				k++;
				continue;
			}
			if (str[k] == 't' && k + 3 < str.length() && str.substr(k, 4) == "true") {
				tokens.push_back(token("true", BOOLEAN));
				k += 4;
				continue;
			}
			if (str[k] == 'f' && k + 4 < str.length() && str.substr(k, 5) == "false") {
				tokens.push_back(token("false", BOOLEAN));
				k += 5;
				continue;
			}
			if (str[k] == 'n' && k + 3 < str.length() && str.substr(k, 4) == "null") {
				tokens.push_back(token("null", NUL));
				k += 4;
				continue;
			}
			if (str[k] == '}') {
				tokens.push_back(token("}", CROUSH_CLOSE));
				k++;
				continue;
			}
			if (str[k] == '{') {
				tokens.push_back(token("{", CROUSH_OPEN));
				k++;
				continue;
			}
			if (str[k] == ']') {
				tokens.push_back(token("]", BRACKET_CLOSE));
				k++;
				continue;
			}
			if (str[k] == '[') {
				tokens.push_back(token("[", BRACKET_OPEN));
				k++;
				continue;
			}
			if (str[k] == ':') {
				tokens.push_back(token(":", COLON));
				k++;
				continue;
			}
			if (str[k] == '-' || (str[k] <= '9' && str[k] >= '0')) {
				size_t tmp_k = k;
				if (str[tmp_k] == '-') tmp_k++;
				while (tmp_k < str.size() && ((str[tmp_k] <= '9' && str[tmp_k] >= '0') || str[tmp_k] == '.')) tmp_k++;
				tokens.push_back(token(str.substr(k, tmp_k - k), NUMBER));
				k = tmp_k;
				continue;
			}
			tokens.push_back(token(str.substr(k), UNKNOWN));
			k = str.length();
		}

		index = skip_whitespaces(source, next);
	}

	return tokens;
}


INode* Reader::json_parse(std::vector<token> v, int i, int& r , std::string key) {

	qDebug() << i << QString(v[i].value.data()) << QString(key.data());
	if (v[i].type == CROUSH_OPEN) {
		
		qDebug() << "Hello";
		
		int k = i + 1;
		IObject* current = new IObject(QString(v[k].value.data()));
		while (v[k].type != CROUSH_CLOSE && k < v.size()) {
			std::string key = v[k].value;
			k += 2; // k+1 should be ':'
			int j = k;
			INode* vv = json_parse(v, k, j, key);
			current->addValue(vv);
			k = j;
			if (v[k].type == COMMA) k++;
		}
		r = k + 1;
		last = current;
		return current;
	}
	if (v[i].type == BRACKET_OPEN) {
		IArray* current = new IArray(QString(key.data()));
		int k = i + 1;
		while (v[k].type != BRACKET_CLOSE && k < v.size() ) {
			int j = k;
			INode* vv = json_parse(v, k, j, key);
			current->addValue(vv);
			k = j;
			if (v[k].type == COMMA) k++;
		}
		r = k + 1;
		last = current;
		return current;
	}
	if (v[i].type == NUMBER || v[i].type == STRING || v[i].type == BOOLEAN) {
		INode* current = new IValue(QString(key.data()),QString(v[i].value.data()));
		r = i + 1;
		last = current;
		return current;
	}

	if (v[i].type == NUL) {
		INode* current = new IValue(QString(key.data()), "NULL");
		r = i + 1;
		last = current;
		return current;
	}
	return nullptr;
}

INode* Reader::parse(const std::string& str) {
	int k;
	json_parse(tokenize(str), 0, k);
	return last;
}
INode* Reader::parse_file(const std::string& filename) {
	std::ifstream in(filename);
	std::string str = "";
	std::string tmp;
	while (std::getline(in, tmp)) str += tmp;
	in.close();
	return Reader::parse(str);
}