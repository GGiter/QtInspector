#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <sstream>
#include <fstream>
#include <cstring>
#include "dataTypes.h"

class Reader {
private:
	enum token_type { UNKNOWN, STRING, NUMBER, CROUSH_OPEN, CROUSH_CLOSE, BRACKET_OPEN, BRACKET_CLOSE, COMMA, COLON, BOOLEAN, NUL };

	struct token;
	static bool is_whitespace(const char c);
	static int next_whitespace(const std::string& source, int i);
	static int skip_whitespaces(const std::string& source, int i);

	static std::vector<token> tokenize(std::string source);
	INode* json_parse(std::vector<token> v, int i, int& r, std::string key = "", INode* parent = nullptr);
public:
	INode* last;
	INode* parse(const std::string& str);
	INode* parse_file(const std::string& str);
};
