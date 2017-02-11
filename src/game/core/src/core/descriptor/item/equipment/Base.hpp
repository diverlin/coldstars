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

#include <core/descriptor/item/BaseItem.hpp>

namespace descriptor {
namespace item {

class BaseEquipment : public Base
{
public:
    BaseEquipment() = default;
    ~BaseEquipment() = default;

    void setModules(int modules) { m_modules = modules; }

    int modules() const { return m_modules; }

protected:
    std::string info() const {
        std::string result = "descriptor::item::BaseEquipment:\n";
        result += std::string(" modules = ") + std::to_string(m_modules) + "\n";
        result += descriptor::item::Base::info();
        return result;
    }

private:
    int m_modules = 0;

private:
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version) {
        ar & boost::serialization::base_object<descriptor::item::Base>(*this);
        ar & m_modules;
    }
};

} // namespace item
} // namespace descriptor


