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

#include "TagsComponent.hpp"
#include <ceti/StringUtils.hpp>

namespace ceti {

int TagsComponent::counter = 0;
std::map<std::string, int> TagsComponent::dict;
std::map<int, std::string> TagsComponent::rdict;

TagsComponent::TagsComponent() {}
TagsComponent::~TagsComponent() {}

void TagsComponent::reg(const std::string& tag) {
    if (tag.find(",") == tag.npos) {
        __reg(tag);
    } else {
        std::vector<std::string> v = ceti::split(tag, ",");
        for (std::string& s: v) {
            ceti::remove_whitespaces(s);
            __reg(s);
        }
    }
}

void TagsComponent::reg(const ceti::pack<std::string>& tags) {
    for (auto tag: tags) {
        __reg(tag);
    }
}

void TagsComponent::unreg(const std::string& tag) {
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

void TagsComponent::unreg(const ceti::pack<std::string>& tags) {
    for (const std::string& tag: tags) {
        unreg(tag);
    }
}

void TagsComponent::add(const std::string& tag) {
    if (tag.find(",") == tag.npos) {
        __add(tag);
    } else {
        std::vector<std::string> v = ceti::split(tag, ",");
        for (std::string& s: v) {
            ceti::remove_whitespaces(s);
            __add(s);
        }
    }
}

void TagsComponent::add(const ceti::pack<std::string>& tags) {
    for (const std::string& tag: tags) {
        __add(tag);
    }
}

void TagsComponent::remove(const std::string& tag) {
    auto it = dict.find(tag);
    if (it == dict.end()) {
        __warn_not_registered_tag(tag);
        return;
    }
    int id = it->second;

    if (!m_data.contains(id)) {
        return;
    }
    m_data.remove(id);
}

void TagsComponent::remove(const ceti::pack<std::string>& tags) {
    for (const std::string& tag: tags) {
        remove(tag);
    }
}

ceti::pack<int> TagsComponent::ids_from(const std::string& tags) {
    ceti::pack<int> result;
    if (tags.find(",") == tags.npos) {
        result.add(__id(tags));
    } else {
        std::vector<std::string> v = ceti::split(tags, ",");
        for (std::string& s: v) {
            ceti::remove_whitespaces(s);
            result.add(__id(s));
        }
    }
    return result;
}

ceti::pack<int> TagsComponent::ids_from(const ceti::pack<std::string>& tags) {
    ceti::pack<int> result;
    for (const std::string& tag: tags) {
        result.add(__id(tag));
    }
    return result;
}

bool TagsComponent::match(const ceti::pack<int> queue) const {
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


void TagsComponent::__reg(const std::string& tag) {
    auto it = dict.find(tag);
    if (it != dict.end()) {
        return;
    }

    counter++;

    dict.insert(std::make_pair(tag, counter));
    rdict.insert(std::make_pair(counter, tag));
}

int TagsComponent::__id(const std::string& tag) {
    auto it = dict.find(tag);
    if (it != dict.end()) {
        return it->second;
    }
    assert(false); // normally shoudn't go here
    return -1;
}

void TagsComponent::__add(const std::string& tag) {
    auto it = dict.find(tag);
    if (it == dict.end()) {
        __warn_not_registered_tag(tag);
        return;
    }
    int id = it->second;
    m_data.add(id);
}

void TagsComponent::__warn_not_registered_tag(const std::string& tag) const {
    std::cout<<"tag ["<<tag<<"] is not registered"<<std::endl;
}

} // namespace ceti

