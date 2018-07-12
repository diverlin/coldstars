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

class Node;
std::vector<Node> parse(const std::string& graph);
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
            ceti::remove_whitespaces(m_tags);
        }
    }

    void bornChildren() {
        if (m_body.empty()){
            return;
        }

        m_children = parse(m_body);
        m_body = "";

        for(Node& child: m_children) {
            child.bornChildren();
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
    std::cout<<msg<<std::endl;
}


Node process_buffers(std::string& name_buffer,
                     std::string& position_buffer,
                     std::string& tags_buffer,
                     std::string& body_buffer)
{
    ceti::trim_char(name_buffer, ',');

    body_buffer = ceti::get_nested(body_buffer, '{', '}');
    tags_buffer = ceti::get_nested(name_buffer, '[', ']');
    if (!tags_buffer.empty()) {
        name_buffer = ceti::replace(name_buffer, "["+tags_buffer+"]", "");
        position_buffer = ceti::get_nested(tags_buffer, '(', ')');
        if (!position_buffer.empty()) {
            tags_buffer = ceti::replace(tags_buffer, "("+position_buffer+")", "");
        }
    }

    Node node(name_buffer, position_buffer, tags_buffer, body_buffer);

    name_buffer = "";
    position_buffer = "";
    tags_buffer = "";
    body_buffer = "";

    return node;
}

std::vector<Node> parse(const std::string& input)
{
    std::string graph = input;
    ceti::remove_whitespaces(graph);

    std::vector<Node> result;

    int nest_level = 0;

    std::string name_buffer;
    std::string tags_buffer;
    std::string position_buffer;
    std::string body_buffer;

    bool name_start = true;
    bool body_start = false;

    unsigned int count = 0;
    for (const char& ch: graph) {
        count++;
        std::string mystring = std::string(ch);
        log(mystring);

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

        // to handle items without body {}
        if ((name_start == true) && (name_buffer.find('[') == name_buffer.npos) && (ch == ','))
        {
            if (name_buffer[0] != ',') {
                log("empty body");
                name_start = true;
                body_start = false;

                Node node = process_buffers(name_buffer, position_buffer, tags_buffer, body_buffer);
                result.push_back(node);
                continue;
            }
        }

        // on body ends we dump result
        if ((body_start == true) && (nest_level == 0)) {
            log("close body");
            name_start = true;
            body_start = false;

            Node node = process_buffers(name_buffer, position_buffer, tags_buffer, body_buffer);
            result.push_back(node);
            continue;
        }

        // corner case to process last element of {starsystem, starsystem, starsystem}
        if ((name_start == true) && (count == graph.length())) {
            log("close body");
            name_start = false;
            body_start = false;

            Node node = process_buffers(name_buffer, position_buffer, tags_buffer, body_buffer);
            result.push_back(node);
            continue;
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

TEST(graph, parser)
{
    std::string input = "starsystem[alien,small]{star,planet[ice]{kosmoport}}, starsystem[(140,70)]{blackhole,asteroid}, starsystem{star,star}";
    std::vector<Node> nodes = parse(input);
    assert(nodes.size()==3);
    EXPECT_EQ(Node("starsystem", "", "alien,small", "star,planet[ice]{kosmoport}").toString(), nodes[0].toString());
    EXPECT_EQ(Node("starsystem", "140,70", "", "blackhole,asteroid").toString(), nodes[1].toString());
    EXPECT_EQ(Node("starsystem", "", "", "star,star").toString(), nodes[2].toString());
    EXPECT_NE(Node("starsystem", "", "", "star, star").toString(), nodes[2].toString());
}

TEST(graph, parser_simple)
{
    std::string input = "starsystem, starsystem, hyperspace1";
    std::vector<Node> nodes = parse(input);
    assert(nodes.size()==3);
    EXPECT_EQ(Node("starsystem", "", "", "").toString(), nodes[0].toString());
    EXPECT_EQ(Node("starsystem", "", "", "").toString(), nodes[1].toString());
    EXPECT_EQ(Node("hyperspace1", "", "", "").toString(), nodes[2].toString());
}

TEST(graph, nodes)
{
    std::string input ="\
    galaxy {\
        starsystem {\
            star,\
            planet[ice] {land},\
            planet[rock] {kosmoport { shop {korpus, lazer} } },\
            planet[whater],\
            ship,\
            ship {drive, lazer, rocket},\
            lazer,\
            drive[(100,0)]\
        },\
        starsystem {\
            star,\
            planet {land},\
            planet {kosmoport { angar { ship } }\
        }\
    }";

    std::vector<Node> nodes = parse(input);
    assert(nodes.size()==1);
//    EXPECT_EQ(Node("starsystem", "", "", "").toString(), nodes[0].toString());
//    EXPECT_EQ(Node("starsystem", "", "", "").toString(), nodes[1].toString());
//    EXPECT_EQ(Node("hyperspace1", "", "", "").toString(), nodes[2].toString());
}


