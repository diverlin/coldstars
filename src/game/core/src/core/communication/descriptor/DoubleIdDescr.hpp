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

#include "SingleIdDescr.hpp"

namespace core {

class DoubleIdDescr : public SingleIdDescr {
public:
    DoubleIdDescr(int_t, int_t);
    DoubleIdDescr(const std::string& data);
    DoubleIdDescr() = default;
    ~DoubleIdDescr() = default;
    std::string data() const;

    int_t secondId() const { return m_secondId; }

    std::string info() const {
        std::string result = SingleIdDescr::info();
        result += "DoubleIdDescr:\n";
        result += std::string(" second id = ") + std::to_string(m_secondId) + "\n";
        return result;
    }

private:
    int_t m_secondId = NONE;

private:
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version) {
        ar & boost::serialization::base_object<SingleIdDescr>(*this);
        ar & m_secondId;
    }
};

} // namespace core

