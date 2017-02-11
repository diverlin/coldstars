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
class Drive;
} // namespace item
} // namespace descriptor

namespace model {
namespace item {
class Drive;
} // namespace item
} // namespace model

namespace control {
namespace item {

class Drive : public control::item::Base
{
public:
    Drive(model::item::Drive*);
    virtual ~Drive() = default;

private:
    virtual void updateProperties();
    void CountPrice();

    model::item::Drive* model() const { return m_model_drive; }
    descriptor::item::Drive* descriptor() const { return m_descriptor_drive; }

private:
    int m_speed_add = 0;
    int m_hyper_add = 0;

    model::item::Drive* m_model_drive = nullptr;
    descriptor::item::Drive* m_descriptor_drive = nullptr;

    void virtual addUniqueInfo();
    std::string speedStr();
    std::string hyperStr();
};

} // namespace item
} // namespace control