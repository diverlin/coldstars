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

#include <ceti/descriptor/Texture.hpp>

#include <core/descriptor/Association.hpp>

#include <ceti/type/IdType.hpp>

#include <glm/glm.hpp>

#include <string>

namespace descriptor {

class Material : public ceti::descriptor::Material, public Association
{
public:
//    Material(int type,
//            const std::string& path,
//            bool alpha = true);

    Material(int_t type = NONE);
    Material(const std::string& data);
    ~Material() = default;

    std::string data() const;

    bool operator==(const Material& rhs) const;

private:
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version) {
        ar & boost::serialization::base_object<ceti::descriptor::Material>(*this);
        ar & boost::serialization::base_object<Association>(*this);
    }
};

} // namespace descriptor
