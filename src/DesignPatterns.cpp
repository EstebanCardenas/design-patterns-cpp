//============================================================================
// Name        : DesignPatterns.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <string>
#include <vector>

#include "Structural/Flyweight/TextFormatting.hpp"

using namespace std;

struct WordToken
{
    int s, e;
    bool capitalize;

    WordToken(int s, int e): s(s), e(e), capitalize(false) {}

    bool covers(int idx) const {
        return idx >= s && idx <= e;
    }
};

struct Sentence
{
  string text;
  vector<WordToken*> tokens;

  Sentence(const string& text) : text(text)
  {
    int s = 0;
    int i = 0;
    for (; i<(int)text.length(); i++) {
        char c = text[i];
        if (c == ' ') {
            tokens.push_back(new WordToken{s, i-1});
            s = i + 1;
        }
    }
    if (s < (int)text.length() && s < i) {
        tokens.push_back(new WordToken{s, i-1});
    }
  }

  WordToken& operator[](size_t index)
  {
    return *tokens[index];
  }

  string str() const
  {
    string ans;
    int tokenIdx = 0;
    WordToken token = *tokens[tokenIdx];
    int i = 0;
    for (; i<(int)text.size(); i++) {
        char c = text[i];
        if (c == ' ') {
            ans += c;
            continue;
        }
        if (!token.covers(i)) {
            token = *tokens[++tokenIdx];
        }
        ans += token.capitalize ? toupper(c) : c;
    }
    return ans;
  }
};

int main() {
	Sentence sentence{"alpha beta gamma"};
	sentence[1].capitalize = true;
	cout << sentence.str();
	return 0;
}
