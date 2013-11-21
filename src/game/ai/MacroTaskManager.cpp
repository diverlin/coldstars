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

#include "MacroTaskManager.hpp"
#include "scenarios/ScenarioCollector.hpp"
#include "../world/EntityManager.hpp"

MacroTaskManager::MacroTaskManager()
{
    scenario  = nullptr;
    target = nullptr;
}

MacroTaskManager::~MacroTaskManager()
{}

void MacroTaskManager::SetTask(const Task& macrotask)
{
    this->macrotask = macrotask;
    scenario = ScenarioCollector::Instance().GetScenario(macrotask.GetScenarioTypeId());
    if (macrotask.GetTargetId() != NONE_ID)
    {
        target = (BaseSpaceEntity*)EntityManager::Instance().GetEntityById(macrotask.GetTargetId()); // hack
    }
}

void MacroTaskManager::Reset()
{
    scenario = nullptr;
    target = nullptr;
    macrotask.Reset();
}    

