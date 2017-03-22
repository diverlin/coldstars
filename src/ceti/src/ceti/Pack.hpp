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

#pragma once

#include <vector>   
#include <set>
#include <algorithm>

#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>

namespace ceti {

template<typename T>
class pack : public std::vector<T>
{
public:
    pack() = default;
    ~pack() = default;

    void add(T element) {
        this->push_back(element);
    }

    T remove(T element) {
        auto it = std::find(this->begin(), this->end(), element);
        if (it != this->end()) {
            // swap the one to be removed with the last element
            // and remove the item at the end of the container
            // to prevent moving all items after '5' by one
            std::swap(*it, this->back());
            this->pop_back();
        }
    }

    T take(T element) {
        auto it = std::find(this->begin(), this->end(), element);
        if (it != this->end()) {
            // swap the one to be removed with the last element
            // and remove the item at the end of the container
            // to prevent moving all items after '5' by one
            std::swap(*it, this->back());
            this->pop_back();
            return *it;
        }
        assert(false);
        return nullptr;
    }

    bool operator==(const pack& rhs) {
        if (this->size() != rhs.size()) {
            return false;
        }

        std::set<T> set1(this->begin(), this->end());
        std::set<T> set2(rhs.begin(), rhs.end());
        return (set1 == set2);
    }

private:
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version) {
        ar & boost::serialization::base_object<std::vector<T>>(*this);
    }
};

} // namespace ceti







