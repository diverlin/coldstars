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

#include <ceti/Pack.hpp>
#include <ceti/StringUtils.hpp>

#include <gtest/gtest.h>

#include <string>
#include <map>

class TagsComponent {
public:
    TagsComponent() {}
    ~TagsComponent() {}

    static void reg(const std::string& tag) {
        if (tag.find(",") == tag.npos) {
            __reg(tag);
        } else {
            std::vector<std::string> v = ceti::split(tag, ",");
            for (std::string& s: v) {
                ceti::strip(s);
                __reg(s);
            }
        }
    }

    static void reg(const ceti::pack<std::string>& tags) {
        for (auto tag: tags) {
            __reg(tag);
        }
    }
    static void unreg(const std::string& tag) {
        auto it = dict.find(tag);
        if (it == dict.end()) {
            return;
        }

        int id = it->second;
        dict.erase(it);

        auto it2 = rdict.find(id);
        if (it2 == rdict.end()) {
            return;
        }
        rdict.erase(it2);
    }
    static void unreg(const ceti::pack<std::string>& tags) {
        for (const std::string& tag: tags) {
            unreg(tag);
        }
    }

    void add(const std::string& tag) {
        if (tag.find(",") == tag.npos) {
            __add(tag);
        } else {
            std::vector<std::string> v = ceti::split(tag, ",");
            for (std::string& s: v) {
                ceti::strip(s);
                __add(s);
            }
        }
    }

    void add(const ceti::pack<std::string>& tags) {
        for (const std::string& tag: tags) {
            __add(tag);
        }
    }

    void remove(const std::string& tag) {
        auto it = dict.find(tag);
        if (it == dict.end()) {
            warn_not_registered_tag(tag);
            return;
        }
        int id = it->second;

        if (!m_data.contains(id)) {
            return;
        }
        m_data.remove(id);
    }

    void remove(const ceti::pack<std::string>& tags) {
        for (const std::string& tag: tags) {
            remove(tag);
        }
    }

    static ceti::pack<int> ids_from(const std::string& tags) {
        ceti::pack<int> result;
        if (tags.find(",") == tags.npos) {
            result.add(__id(tags));
        } else {
            std::vector<std::string> v = ceti::split(tags, ",");
            for (std::string& s: v) {
                ceti::strip(s);
                result.add(__id(s));
            }
        }
        return result;
    }

    static ceti::pack<int> ids_from(const ceti::pack<std::string>& tags) {
        ceti::pack<int> result;
        for (const std::string& tag: tags) {
            result.add(__id(tag));
        }
        return result;
    }

    const ceti::pack<int>& tags() const { return m_data; }

    bool match(const ceti::pack<int> queue) const {
        if (queue.size() > tags().size()) {
            return false;
        }

        for (int id: queue) {
            if (!m_data.contains(id)) {
                return false;
            }
        }
        return true;
    }

private:
    ceti::pack<int> m_data;

    static void __reg(const std::string& tag) {
        auto it = dict.find(tag);
        if (it != dict.end()) {
            return;
        }

        counter++;

        dict.insert(std::make_pair(tag, counter));
        rdict.insert(std::make_pair(counter, tag));
    }

    static int __id(const std::string& tag) {
        auto it = dict.find(tag);
        if (it != dict.end()) {
            return it->second;
        }
        assert(false); // normally shoudn't go here
        return -1;
    }

    void __add(const std::string& tag) {
        auto it = dict.find(tag);
        if (it == dict.end()) {
            warn_not_registered_tag(tag);
            return;
        }
        int id = it->second;
        m_data.add(id);
    }

    void warn_not_registered_tag(const std::string& tag) const {
        std::cout<<"tag ["<<tag<<"] is not registered"<<std::endl;
    }

protected:
    static int counter;
    static std::map<std::string, int> dict;
    static std::map<int, std::string> rdict;
};

int TagsComponent::counter = 0;
std::map<std::string, int> TagsComponent::dict;
std::map<int, std::string> TagsComponent::rdict;


TEST(tags, common)
{
    TagsComponent::reg("star, asteroid, item, race1, inhabited, planet, cold, agressive");

    TagsComponent component1;
    component1.add("star, race1, cold");

    TagsComponent component2;
    component2.add("star, cold");

    TagsComponent component3;
    component3.add("star");

    TagsComponent component4;
    component4.add("star, inhabited");

    TagsComponent component5;
    component5.add("planet, inhabited");

    EXPECT_TRUE(component1.tags() == TagsComponent::ids_from("star, race1, cold"));
    EXPECT_TRUE(component1.match(component2.tags()));
    EXPECT_TRUE(component1.match(component3.tags()));
    EXPECT_TRUE(component2.match(component3.tags()));
    EXPECT_TRUE(component4.match(component3.tags()));
    EXPECT_FALSE(component3.match(component4.tags()));
    EXPECT_FALSE(component1.match(component4.tags()));
    EXPECT_FALSE(component1.match(component5.tags()));
}
