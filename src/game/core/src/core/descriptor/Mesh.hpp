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

#include "Association.hpp"
#include <ceti/descriptor/Mesh.hpp>

namespace descriptor {

class Mesh : public ceti::descriptor::Mesh, public Association
{
public:
    Mesh() = default;
//    Mesh(int_t type = -1);
    Mesh(const std::string& data);
    ~Mesh() = default;

    std::string data() const;

    bool operator==(const Mesh& rhs) const;

private:
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version) {
        ar & boost::serialization::base_object<ceti::descriptor::Mesh>(*this);
        ar & boost::serialization::base_object<Association>(*this);
    }
};

} // namespace descriptor
