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
class Radar;
} // namespace item
} // namespace descriptor

namespace model {
namespace item {
class Radar;
} // namespace item
} // namespace model

namespace control {
namespace item {

class Radar : public Equipment
{
public:
    Radar(model::item::Radar*);
    virtual ~Radar() = default;

    virtual void updateProperties();

public:
    model::item::Radar* model() const { return m_model_radar; }
    descriptor::item::Radar* descriptor() const { return m_descriptor_radar; }

private:
    model::item::Radar* m_model_radar = nullptr;
    descriptor::item::Radar* m_descriptor_radar = nullptr;

    int m_radius_add = 0;

    void virtual addUniqueInfo();
    std::string radiusStr();
};

} // namespace item
} // namespace control










