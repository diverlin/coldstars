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

namespace core {
class DriveDescr;
} // namespace core

namespace model {
class DriveModel;
} // namespace model

namespace core {
namespace control {

class Drive : public Equipment
{
public:
    Drive(DriveDescr*, model::DriveModel*);
    virtual ~Drive() = default;

    int speed() const;

public:
    DriveDescr* descriptor() const { return m_descriptor_drive; }
    model::DriveModel* model() const { return m_model_drive; }

private:
    virtual void updateProperties();

private:
    int m_speed_add = 0;
    int m_hyper_add = 0;

    DriveDescr* m_descriptor_drive = nullptr;
    model::DriveModel* m_model_drive = nullptr;

    void virtual addUniqueInfo();
    std::string speedStr();
    std::string hyperStr();
};

} // namespace control
} // namespace core
