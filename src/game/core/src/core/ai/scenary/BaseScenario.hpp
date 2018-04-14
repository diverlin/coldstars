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

#include <core/type/AiScenarioType.hpp>

#include <string>

namespace core {
namespace control {
class Npc;
} // namespace control
} // namespace core

class BaseScenario
{
public:
    BaseScenario() {}
    virtual ~BaseScenario() {}

    void setTypeId(ai::type type) { m_type = type; }
    ai::type typeId() const { return m_type; }

    virtual void enter(core::control::Npc*) const {}
    virtual bool Validate(core::control::Npc*) const { return true; }
    virtual void UpdateInStaticInSpace(core::control::Npc*) const {}
    virtual void UpdateInStaticInDock(core::control::Npc*) const {}
    virtual void UpdateInDynamicInSpace(core::control::Npc*) const {}
    virtual void UpdateInDynamicInDock(core::control::Npc*) const {}
    virtual void exit(core::control::Npc*) const {}

    virtual std::string GetDescription(core::control::Npc*) const { return "_"; }

private:
    ai::type m_type = ai::type::NONE;
}; 

