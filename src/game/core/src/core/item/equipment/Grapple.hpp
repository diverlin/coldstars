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
class GrappleDescr;
} // namespace core

namespace model {
class Grapple;
} // namespace model

namespace core {
namespace control {

class Grapple : public Equipment
{
public:
    Grapple(GrappleDescr*, model::Grapple*);
    virtual ~Grapple() = default;

    void UpdateGrabScenarioProgram_inDynamic();

    virtual void updateProperties();

    model::Grapple* model() const { return m_model_grapple; }
    GrappleDescr* descriptor() const { return m_descriptor_grapple; }

private:
    int m_strength_add = 0;
    int m_radius_add = 0;
    int m_speed_add = 0;

    int m_free_strength = 0;

    model::Grapple* m_model_grapple = nullptr;
    GrappleDescr* m_descriptor_grapple = nullptr;

    void virtual addUniqueInfo();
    std::string strengthStr();
    std::string radiusStr();
    std::string speedStr();
};

} // namespace control
} // namespace core
