//
//  builder.cpp
//  DesignPatterns
//
//  Created by Nicolás Cárdenas on 29/02/24.
//

#pragma once

#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

class HtmlElement {
    friend class HtmlBuilder;
    
    string name, text;
    vector<HtmlElement> elements;
    
    const size_t indent_size = 2;
    
    HtmlElement() {}
    
    HtmlElement(string name, string text) : name(name), text(text) {}

public:
    string str(int indent = 0) const {
        ostringstream oss;
        string i(indent_size * indent, ' ');
        oss << i << "<" << name << ">" << endl;
        if (text.size() > 0) {
            oss << string(indent_size * (indent + 1), ' ') << text << endl;
        }
        for (HtmlElement element: elements) {
            oss << element.str(indent + 1);
        }
        oss << i << "</" << name << ">" << endl;
        return oss.str();
    }
};

class HtmlBuilder {
    HtmlElement root;
public:
    HtmlBuilder(string root_name) {
        root.name = root_name;
    }
    
    HtmlBuilder add_child(string child_name, string child_text) {
        HtmlElement e{child_name, child_text};
        root.elements.emplace_back(e);
        return *this;
    }
    
    HtmlElement build() { return root; }
};

int builderMain() {
    HtmlElement html_element = HtmlBuilder{"ul"}
        .add_child("li", "item_one")
        .add_child("li", "item_two")
        .build();
    cout << html_element.str();
    return 0;
}
