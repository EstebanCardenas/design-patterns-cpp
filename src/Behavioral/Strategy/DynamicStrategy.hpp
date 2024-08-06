/*
 * DynamicStrategy.hpp
 *
 *  Created on: Aug 5, 2024
 *      Author: necar
 */

#pragma once

#include <sstream>
#include <memory>
#include <vector>
#include <iostream>
#include <string>

using namespace std;

enum class OutputFormat {
	markdown,
	html
};

struct ListStrategy {
	virtual void start(ostringstream& oss) {}
	virtual void add_item(ostringstream& oss, const string& item) = 0;
	virtual void end(ostringstream& oss) {}
};

struct MarkdownListStrategy: ListStrategy {
	void add_item(ostringstream& oss, const string& item) override {
		oss << "* " << item << endl;
	}
};

struct HtmlListStrategy: ListStrategy {
	void start(ostringstream& oss) override {
		oss << "<ul>" << endl;
	}

	void add_item(ostringstream& oss, const string& item) override {
		oss << "  " << "<li>" << item << "</li>" << endl;
	}

	void end(ostringstream& oss) override {
		oss << "</ul>" << endl;
	}
};


class TextProcessor {
	ostringstream oss;
	unique_ptr<ListStrategy> strategy;
public:
	void clear() {
		oss.str("");
		oss.clear();
	}

	void append_list(const vector<string>& items) {
		strategy->start(oss);
		for (string item: items) {
			strategy->add_item(oss, item);
		}
		strategy->end(oss);
	}

	void set_output_format(const OutputFormat& format) {
		switch(format) {
		case OutputFormat::markdown:
			strategy = make_unique<MarkdownListStrategy>();
			break;
		case OutputFormat::html:
			strategy = make_unique<HtmlListStrategy>();
			break;
		}
	}

	string str() const { return oss.str(); }
};

int dStratMain() {
	vector<string> items{"foo", "bar", "baz"};
	TextProcessor tp;
	tp.set_output_format(OutputFormat::markdown);
	tp.append_list(items);
	cout << tp.str() << endl;

	tp.clear();
	tp.set_output_format(OutputFormat::html);
	tp.append_list(items);
	cout << tp.str() << endl;

	return 0;
}
