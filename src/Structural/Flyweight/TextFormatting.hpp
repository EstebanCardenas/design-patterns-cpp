/*
 * TextFormatting.hpp
 *
 *  Created on: May 11, 2024
 *      Author: necar
 */

#pragma once

#include <string.h>
#include <string>
#include <ostream>
#include <iostream>
#include <vector>

using namespace std;

class FormattedText {
	string plain_text;
	bool* caps;
public:
	FormattedText(const string& pt): plain_text(pt) {
		caps = new bool[plain_text.size()];
		memset(caps, 0, plain_text.size());
	}

	~FormattedText() {
		delete caps;
	}

	void capitalize(int s, int e) {
		for (int i=s; i<=e; i++) {
			caps[i] = true;
		}
	}

	friend ostream& operator<<(ostream& os, const FormattedText& text) {
		string ans;
		for (int i=0; i<text.plain_text.length(); i++) {
			char c = text.plain_text[i];
			ans += text.caps[i] ? toupper(c) : c;
		}
		return os << ans;
	}
};

class BetterFormattedText {
public:
	struct TextRange {
		int s, e;
		bool capitalize;

		bool covers(int pos) const {
			return pos >= s && pos <= e;
		}
	};

	TextRange& get_range(int s, int e) {
		formatting.push_back({s, e});
		return *formatting.rbegin();
	}

	BetterFormattedText(const string& pt): plain_text(pt) {}

	friend ostream& operator<<(ostream& os, const BetterFormattedText& obj) {
		string s;
		for (int i=0; i<obj.plain_text.length(); i++) {
			char c = obj.plain_text[i];
			for (TextRange rng: obj.formatting) {
				if (rng.covers(i) && rng.capitalize) {
					c = toupper(c);
				}
				s += c;
			}
		}
		return os << s;
	}
private:
	string plain_text;
	vector<TextRange> formatting;
};

int formattedTxtMain() {
	FormattedText ft{"this is a brave world"};
	ft.capitalize(10, 15);
	cout << ft << endl;

	BetterFormattedText bft{"This is a brave new world"};
	bft.get_range(10, 15).capitalize = true;
	cout << bft;
	return 0;
}
