//
//  groovy_builder.cpp
//  DesignPatterns
//
//  Created by Nicolás Cárdenas on 14/03/24.
//

#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

class Tag {
    friend ostream& operator <<(ostream& os, Tag tag) {
        os << "<" << tag.name;
        for (pair<string, string> att: tag.attributes) {
            os << " " << att.first << "=\"" << att.second << "\"";
        }
        if (tag.children.size() == 0 && tag.text.size() == 0) {
            os << "/>" << endl;
        } else {
            os << ">" << endl;
            if (tag.text.size() > 0) {
                os << tag.text << endl;
            }
            for (Tag child: tag.children) {
                os << child;
            }
            os << "</" << tag.name << ">" << endl;
        }
        return os;
    }
protected:
    string name, text;
    vector<Tag> children;
    unordered_map<string, string> attributes;
    
    Tag(string name, string text) : name(name), text(text) {}
    Tag(string name, const vector<Tag>& children): name(name), children(children) {}
};

struct P: Tag {
    P(string text) : Tag("p", text) {}
    P(initializer_list<Tag> children) : Tag("p", children) {}
};

struct Img: Tag {
    explicit Img(const string& url) : Tag("img", "") {
        attributes["src"] = url;
    }
};

void groovyBuilderMain() {
    cout <<
    P {
        Img{ "http://www.images.com/1" }
    };
}
