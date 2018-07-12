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

    const std::string& type() const { return m_type; }
    const std::string& position() const { return m_position; }
    std::string tagsAsString() const { return ceti::join(m_tags, ","); }
    const std::vector<Node>& children() const { return m_children; }

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
            result += tagsAsString();
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

void log2(const std::string& msg){
    //std::cout<<msg<<std::endl;
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

void processing_magic(std::string& input)
{
    // write now the case
    // angar{ship[damaged,equiped], ship}
    // not parsed well, but
    // angar{ship[damaged,equiped]{}, ship}
    // so the idea is to add {} where it's needed to simulate empty body
    ceti::remove_whitespaces(input);
    input = ceti::replace(input, "],", "]{},");
}

bool validate_syntax(const std::string& input)
{
    int counter_open1 = 0;
    int counter_close1 = 0;
    int counter_open2 = 0;
    int counter_close2 = 0;
    int counter_open3 = 0;
    int counter_close3 = 0;

    for (const char& ch: input) {
        if (ch =='{') {
            counter_open1++;
        }
        if (ch =='}') {
            counter_close1++;
        }
        if (ch =='[') {
            counter_open2++;
        }
        if (ch ==']') {
            counter_close2++;
        }
        if (ch =='(') {
            counter_open3++;
        }
        if (ch ==')') {
            counter_close3++;
        }
    }

    if (counter_open1 != counter_close1) {
        log("the number of \"{\" doesn't match to \"}\", please check you file");
        return false;
    }
    if (counter_open2 != counter_close2) {
        log("the number of \"[\" doesn't match to \"]\", please check you file");
        return false;
    }
    if (counter_open3 != counter_close3) {
        log("the number of \"(\" doesn't match to \")\", please check you file");
        return false;
    }

    return true;
}

std::vector<Node> parse(const std::string& input)
{
    std::string graph = input;
    processing_magic(graph);
    assert(validate_syntax(graph));

    std::vector<Node> result;

    int nested_level = 0;

    std::string name_buffer;
    std::string tags_buffer;
    std::string position_buffer;
    std::string body_buffer;

    bool collecting_name = true;
    bool collecting_body = false;

    unsigned int count = 0;
    bool dump_requested = false;
    for (const char& ch: graph) {
        count++;

        if (!collecting_name && !collecting_body) {
            collecting_name = true;
        }

        // start collecting body
        if (ch == '{') {
            log2("{");
            nested_level++;
            collecting_name = false;
            collecting_body = true;
        }
        // end collecting body
        if (ch == '}') {
            log2("}");
            nested_level--;
            if (nested_level==0) {
                dump_requested = true;
            }
        }

        // skip coma at the beginning
        if (name_buffer.empty() && ch == ',') {
            continue;
        }

        /// collect buffers depending on mode
        if (collecting_name) {
            name_buffer += ch;
        }
        if (collecting_body) {
            body_buffer += ch;
        }

        // dump desicion
        if (collecting_name && (count == graph.length())) {
            dump_requested = true;
        }

        if (collecting_name && (name_buffer.find('[') == name_buffer.npos) && (ch==',')) {
            dump_requested = true;
        }

        if (dump_requested) {
            Node node = process_buffers(name_buffer, position_buffer, tags_buffer, body_buffer);
            result.push_back(node);

            // reset flags
            dump_requested = false;
            collecting_name = false;
            collecting_body = false;
        }
    }

    return result;
}

TEST(graph, parse)
{
    std::string input = "starsystem[alien,small]{star,planet[ice]{kosmoport}}, starsystem[(140,70)]{blackhole,asteroid}, starsystem{star,star}";
    std::vector<Node> nodes = parse(input);
    assert(nodes.size()==3);
    EXPECT_EQ(Node("starsystem", "", "alien,small", "star,planet[ice]{kosmoport}").toString(), nodes[0].toString());
    EXPECT_EQ(Node("starsystem", "140,70", "", "blackhole,asteroid").toString(), nodes[1].toString());
    EXPECT_EQ(Node("starsystem", "", "", "star,star").toString(), nodes[2].toString());
    EXPECT_NE(Node("starsystem", "", "", "star, star").toString(), nodes[2].toString());
}

TEST(graph, parse_simple)
{
    std::string input = "s1{}, s2, h1[(100,0)]";
    std::vector<Node> nodes = parse(input);
    assert(nodes.size()==3);
    EXPECT_EQ(Node("s1", "", "", "").toString(), nodes[0].toString());
    EXPECT_EQ(Node("s2", "", "", "").toString(), nodes[1].toString());
    EXPECT_EQ(Node("h1", "100,0", "", "").toString(), nodes[2].toString());
}

TEST(graph, parse_complex)
{
    std::string input ="\
    galaxy {\
        starsystem {\
            star[pulsar],\
            planet[ice,giant] {land},\
            planet[rock] {kosmoport[kualkua,friend] { shop {korpus, lazer} } },\
            planet[water],\
            ship[kualkua],\
            ship[vorlon] {drive, lazer, rocket},\
            lazer_error,\
            drive[(100,0)]\
        },\
        starsystem[small,radioactive] {\
            star,\
            planet {land},\
            planet {kosmoport { angar { ship, ship[equiped,damaged], ship } } }\
        }\
    }";

    std::vector<Node> nodes = parse(input);
    assert(nodes.size()==1);
    Node& galaxy = nodes[0];
    galaxy.bornChildren();

    EXPECT_EQ("galaxy", galaxy.type());
    EXPECT_EQ(2, galaxy.children().size());

    const Node& starsystem1 = galaxy.children()[0];
    const Node& starsystem2 = galaxy.children()[1];

    EXPECT_EQ("starsystem", starsystem1.type());
    EXPECT_EQ("starsystem", starsystem2.type());
    EXPECT_EQ("", starsystem1.tagsAsString());
    EXPECT_EQ("small,radioactive", starsystem2.tagsAsString());

    // starsystem1 children
    EXPECT_EQ(8, starsystem1.children().size());
    const Node& starsystem1_star1 = starsystem1.children()[0];
    EXPECT_EQ("star", starsystem1_star1.type());
    EXPECT_EQ("pulsar", starsystem1_star1.tagsAsString());

    const Node& starsystem1_planet1 = starsystem1.children()[1];
    EXPECT_EQ("planet", starsystem1_planet1.type());
    EXPECT_EQ("ice,giant", starsystem1_planet1.tagsAsString());

    const Node& starsystem1_planet2 = starsystem1.children()[2];
    EXPECT_EQ("planet", starsystem1_planet2.type());
    EXPECT_EQ("rock", starsystem1_planet2.tagsAsString());

    const Node& starsystem1_planet3 = starsystem1.children()[3];
    EXPECT_EQ("planet", starsystem1_planet3.type());
    EXPECT_EQ("water", starsystem1_planet3.tagsAsString());

    const Node& starsystem1_ship1 = starsystem1.children()[4];
    EXPECT_EQ("ship", starsystem1_ship1.type());
    EXPECT_EQ("kualkua", starsystem1_ship1.tagsAsString());

    const Node& starsystem1_ship2 = starsystem1.children()[5];
    EXPECT_EQ("ship", starsystem1_ship2.type());
    EXPECT_EQ("vorlon", starsystem1_ship2.tagsAsString());
    EXPECT_EQ(3, starsystem1_ship2.children().size());
    EXPECT_EQ("drive", starsystem1_ship2.children()[0].type());
    EXPECT_EQ("lazer", starsystem1_ship2.children()[1].type());
    EXPECT_EQ("rocket", starsystem1_ship2.children()[2].type());

    const Node& starsystem1_lazer = starsystem1.children()[6];
    EXPECT_EQ("lazer_error", starsystem1_lazer.type());

    const Node& starsystem1_drive = starsystem1.children()[7];
    EXPECT_EQ("drive", starsystem1_drive.type());
    EXPECT_EQ("100,0", starsystem1_drive.position());

    // starsystem1_planet2 nesting
    EXPECT_EQ(1, starsystem1_planet2.children().size());
    const Node& starsystem1_planet2_kosmoport = starsystem1_planet2.children()[0];
    EXPECT_EQ("kosmoport", starsystem1_planet2_kosmoport.type());
    EXPECT_EQ("kualkua,friend", starsystem1_planet2_kosmoport.tagsAsString());

    EXPECT_EQ(1, starsystem1_planet2_kosmoport.children().size());
    const Node& starsystem1_planet2_kosmoport_shop = starsystem1_planet2_kosmoport.children()[0];
    EXPECT_EQ(2, starsystem1_planet2_kosmoport_shop.children().size());

    const Node& starsystem1_planet2_kosmoport_shop_korpus = starsystem1_planet2_kosmoport_shop.children()[0];
    const Node& starsystem1_planet2_kosmoport_shop_lazer = starsystem1_planet2_kosmoport_shop.children()[1];
    EXPECT_EQ("korpus", starsystem1_planet2_kosmoport_shop_korpus.type());
    EXPECT_EQ("lazer", starsystem1_planet2_kosmoport_shop_lazer.type());

    // starsystem2 children
    EXPECT_EQ(3, starsystem2.children().size());

    const Node& starsystem2_star = starsystem2.children()[0];
    EXPECT_EQ("star", starsystem2_star.type());

    const Node& starsystem2_planet1 = starsystem2.children()[1];
    EXPECT_EQ("planet", starsystem2_planet1.type());

    const Node& starsystem2_planet2 = starsystem2.children()[2];
    EXPECT_EQ("planet", starsystem2_planet2.type());


    // starsystem2-planet1 children
    EXPECT_EQ(1, starsystem2_planet1.children().size());
    const Node& starsystem2_planet1_land = starsystem2_planet1.children()[0];
    EXPECT_EQ("land", starsystem2_planet1_land.type());

    // starsystem2-planet2 nesting
    EXPECT_EQ(1, starsystem2_planet2.children().size());
    const Node& starsystem2_planet2_kosmoport = starsystem2_planet2.children()[0];
    EXPECT_EQ("kosmoport", starsystem2_planet2_kosmoport.type());

    EXPECT_EQ(1, starsystem2_planet2_kosmoport.children().size());
    const Node& starsystem2_planet2_kosmoport_angar = starsystem2_planet2_kosmoport.children()[0];
    EXPECT_EQ("angar", starsystem2_planet2_kosmoport_angar.type());

    EXPECT_EQ(3, starsystem2_planet2_kosmoport_angar.children().size());
    const Node& starsystem2_planet2_kosmoport_angar_ship1 = starsystem2_planet2_kosmoport_angar.children()[0];
    const Node& starsystem2_planet2_kosmoport_angar_ship2 = starsystem2_planet2_kosmoport_angar.children()[1];
    const Node& starsystem2_planet2_kosmoport_angar_ship3 = starsystem2_planet2_kosmoport_angar.children()[2];

    EXPECT_EQ("ship", starsystem2_planet2_kosmoport_angar_ship1.type());
    EXPECT_EQ("ship", starsystem2_planet2_kosmoport_angar_ship2.type());
    EXPECT_EQ("ship", starsystem2_planet2_kosmoport_angar_ship3.type());
    }


