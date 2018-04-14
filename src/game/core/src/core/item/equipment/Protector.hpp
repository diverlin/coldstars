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

#include "Equipment.hpp"

namespace descriptor {
namespace item {
class Protector;
} // namespace item
} // namespace descriptor

namespace model {
namespace item {
class Protector;
} // namespace item
} // namespace model

namespace core {
namespace control {
namespace item {

class Protector : public Equipment
{
public:
    Protector(descriptor::item::Protector*, model::item::Protector*);
    virtual ~Protector() = default;

    virtual void updateProperties();

    descriptor::item::Protector* descriptor() const { return m_descriptor_protector; }
    model::item::Protector* model() const { return m_model_protector; }

private:
    descriptor::item::Protector* m_descriptor_protector = nullptr;
    model::item::Protector* m_model_protector = nullptr;

    int m_protection_add = 0;

    void virtual addUniqueInfo();
    std::string protectionStr();
};

} // namespace item
} // namespace control
} // namespace core
