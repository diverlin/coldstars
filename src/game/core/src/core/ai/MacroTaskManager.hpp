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

#include "Task.hpp"

#include <core/ai/scenary/BaseScenario.hpp>

namespace core {
class SpaceObjectModel;
} // namespace model

class MacroTaskManager
{
public:
    MacroTaskManager() = default;
    ~MacroTaskManager() = default;

    void setTask(const Task&);

    core::SpaceObjectModel* target() const { return m_target; }
    const Task& task() const { return m_macrotask; }
    BaseScenario* scenario() const { return m_scenario; }

private:
    Task m_macrotask;
    BaseScenario* m_scenario = nullptr;
    core::SpaceObjectModel* m_target = nullptr;

    void __reset();

    friend class StateMachine;
};



