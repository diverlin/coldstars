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

//void nested(std::string graph) {

//}

//std::string get_nested_child(const std::string& text) {
//    return ceti::get_nested(text, "{", "}");
//}

//std::string parse_tags(const std::string& text)
//{
//    return ceti::get_nested(text, "[", "]");
//}

//std::string parse_name(const std::string& text)
//{
//    std::string nested = get_nested_child(text);
//    if (!nested.empty()) {
//        std::string name = ceti::replace(text, nested, "");
//        name = ceti::replace(name, "{}", "");
//        return name;
//    }
//    return "";
//}

//void parse_node(Node* node, std::string graph)
//{
//    std::string nested = get_nested_child(graph);
//    if (!nested.empty()) {
//        std::string name = ceti::replace(graph, nested, "");
//        std::cout<<

//    }
//}

class Node {
public:
    Node(const std::string& type,
         const std::string& position,
         const std::string& tags,
         const std::string& body)
        :
          m_type(type)
        , m_position(position)
        , m_body(body)
    {
        if (!tags.empty()) {
            m_tags = ceti::split(tags, ",");
            ceti::strip(m_tags);
        }
    }

    std::string toString() const {
        std::string result="type=";
        result += m_type;
        if (!m_position.empty()) {
            result+= ":position=";
            result += m_position;
        }
        if (!m_tags.empty()) {
            result += ":tags=";
            result += ceti::join(m_tags, ",");
        }
        if (!m_body.empty()) {
            result += ":body=";
            result += m_body;
        }
        return result;
    }

private:
    std::string m_type;
    std::string m_position;
    std::string m_body;
    std::vector<std::string> m_tags;
    std::vector<Node> m_children;
};

void log(const std::string& msg){
    //std::cout<<msg<<std::endl;
}

std::vector<Node> parse(const std::string& graph)
{
    std::vector<Node> result;

    int nest_level = 0;

    std::string name_buffer;
    std::string body_buffer;

    bool name_start = true;
    bool body_start = false;

    for (const char& ch: graph) {
        // enter body
        if (ch == '{') {
            log("{");
            nest_level++;
            name_start = false;
            body_start = true;
        }
        // leave body
        if (ch == '}') {
            log("}");
            nest_level--;
        }

        // collect buffers
        if (name_start) {
            name_buffer += ch;
        }
        if (body_start) {
            body_buffer += ch;
        }

        // on body ends we dump result
        if ((body_start == true) && (nest_level == 0)) {
            log("close body");
            name_start = true;
            body_start = false;

            ceti::superstrip(name_buffer, ',');
//            ceti::superstrip(body_buffer, ',');

            body_buffer = ceti::get_nested(body_buffer, '{', '}');
            std::string tags_buffer = ceti::get_nested(name_buffer, '[', ']');
            std::string position_buffer;
            if (!tags_buffer.empty()) {
                name_buffer = ceti::replace(name_buffer, "["+tags_buffer+"]", "");
                position_buffer = ceti::get_nested(tags_buffer, '(', ')');
                if (!position_buffer.empty()) {
                    tags_buffer = ceti::replace(tags_buffer, "("+position_buffer+")", "");
                }
            }

            result.push_back(Node(name_buffer, position_buffer, tags_buffer, body_buffer));

            name_buffer = "";
            body_buffer = "";
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

    std::string input = "starsystem[alien,small]{star,planet[ice]{kosmoport}}, starsystem[(140,70)]{blackhole,asteroid}, starsystem{star,star}";
    std::vector<Node> nodes = parse(input);
    assert(nodes.size()==3);
    EXPECT_EQ(Node("starsystem", "", "alien,small", "star,planet[ice]{kosmoport}").toString(), nodes[0].toString());
    EXPECT_EQ(Node("starsystem", "140,70", "", "blackhole,asteroid").toString(), nodes[1].toString());
    EXPECT_EQ(Node("starsystem", "", "", "star,star").toString(), nodes[2].toString());
    EXPECT_NE(Node("starsystem", "", "", "star, star").toString(), nodes[2].toString());

//    std::vector<std::string> parse(const std::string& graph)

}
