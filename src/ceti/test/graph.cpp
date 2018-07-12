/*
     Copyright (C) ColdStars, Aleksandr Pivovarov <<coldstars8@gmail.com>>

     This program is free software; you can redistribute it and/or
     modify it under the terms of the GNU General Public License
     as published by the Free Software Foundation; either version 2
     of the License, or (at your option) any later version.

     This program is distributed in the hope that it will be useful,
     but WITHOUT ANY WARRANTY; without even the implied warranty of
     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
     GNU General Public License for more details.

     You should have received a copy of the GNU General Public License
     along with this program; if not, write to the Free Software
     Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/

//#include <ceti/TagsComponent.hpp>

#include <ceti/Pack.hpp>
#include <ceti/StringUtils.hpp>

#include <gtest/gtest.h>

//struct Node {
//    std::string type;
//    std::string pos;
//    ceti::pack<std::string> tags;
//    ceti::pack<Node*> children;
//};


//void parse(Node* root, std::string graph) {

//}

void nested(std::string graph) {

}

std::string get_nested_child(const std::string& text) {
    return ceti::get_nested(text, "{", "}");
}

std::string parse_tags(const std::string& text)
{
    return ceti::get_nested(text, "[", "]");
}

std::string parse_name(const std::string& text)
{
    std::string nested = get_nested_child(text);
    if (!nested.empty()) {
        std::string name = ceti::replace(text, nested, "");
        name = ceti::replace(name, "{}", "");
        return name;
    }
    return "";
}

//void parse_node(Node* node, std::string graph)
//{
//    std::string nested = get_nested_child(graph);
//    if (!nested.empty()) {
//        std::string name = ceti::replace(graph, nested, "");
//        std::cout<<

//    }
//}

    //ceti::pack<std::string> children;

struct Node {
    Node(const std::string& type,
         const std::string& body,
         const std::string& tags):
        type(type)
      , body(body)
      , tags(tags)
    {}
    std::string type;
    std::string body;
    std::string tags;
//    ceti::pack<std::string> tags;


    std::string toString() const {
        std::string result;
        result += type;
        if (!tags.empty()) {
            result += ":";
            result += tags;
        }
        if (!body.empty()) {
            result += ":";
            result += body;
        }
        return result;
    }
};


std::vector<Node> parse(const std::string& graph)
{
    std::vector<Node> result;

    int nest_level = 0;
    std::string name_buffer;
    std::string tags_buffer;
    std::string body_buffer;
    bool name_start = true;
    bool tags_start = false;
    bool body_start = false;
    for (const char& ch: graph) {
        if (ch == '[') {
            name_start = false;
            tags_start = true;
            body_start = false;
        }
        if (ch == ']') {
            name_start = false;
            tags_start = false;
            body_start = false;
        }

        if (ch == '{') {
            nest_level++;
            name_start = false;
            tags_start = false;
            body_start = true;
        }
        if (ch == '}') {
            nest_level--;
        }

        if (name_start) {
            name_buffer += ch;
        }

        if (tags_start && (ch != '[') && (ch != ']')) {
            tags_buffer += ch;
        }

        if (body_start && (ch != '{') && (ch != '}')) {
            body_buffer += ch;
        }

        if ((body_start == true) && (nest_level == 0)) {
            name_start = true;
            body_start = false;
            ceti::strip(name_buffer);
            if (name_buffer[0]==',') {
                name_buffer = name_buffer.substr(1, name_buffer.size()-1);
            }
            ceti::strip(name_buffer);

            ceti::strip(body_buffer);

            result.push_back(Node(name_buffer, body_buffer, tags_buffer));
            body_buffer = "";
            tags_buffer = "";
            name_buffer = "";
        }
    }

    return result;
}

//galaxy {
//    starsystem {
//        star,
//        planet[ice] {land},
//        planet[rock] {kosmoport { shop {korpus, lazer} } },
//        planet[whater],
//        ship,
//        ship {drive, lazer, rocket},
//        lazer,
//        drive[(100,0)]
//    },
//    starsystem {
//        star,
//        planet {land},
//        planet {kosmoport { angar { ship } },
//    }
//}

TEST(graph, common)
{
//    EXPECT_EQ("starsystem{}starsystem{}", get_nested_child("galaxy{starsystem{}starsystem{}}"));
//    EXPECT_EQ("", get_nested_child("{}"));
//    EXPECT_EQ("", get_nested_child(""));

    std::string input = "starsystem[alien,small]{star,planet}, starsystem{blackhole,asteroid}, starsystem{star,star}";
    std::vector<Node> nodes = parse(input);
    EXPECT_EQ(Node("starsystem", "star,planet", "alien,small").toString(), nodes[0].toString());
    EXPECT_EQ(Node("starsystem", "blackhole,asteroid", "").toString(), nodes[1].toString());
    EXPECT_EQ(Node("starsystem", "star,star", "").toString(), nodes[2].toString());
    EXPECT_NE(Node("starsystem", "star, star", "").toString(), nodes[2].toString());

//    std::vector<std::string> parse(const std::string& graph)

}
