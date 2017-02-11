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

#include "MicroTaskManager.hpp"
#include "scenarios/ScenarioCollector.hpp"

#include <common/Global.hpp>
#include <managers/EntityManager.hpp>

MicroTaskManager::MicroTaskManager()
{}

MicroTaskManager::~MicroTaskManager()
{}

void MicroTaskManager::setTask(const Task& microtask)
{
    m_microtask = microtask;
    m_scenario = ScenarioCollector::Instance().get(microtask.GetScenarioTypeId());
    assert(m_scenario);
    if (m_microtask.targetId() != NONE) {
        m_target = (model::SpaceObject*)core::global::get().entityManager().get(microtask.targetId()); // hack
    }
}

void MicroTaskManager::__reset()
{
    m_scenario  = nullptr;
    m_target = nullptr;
    m_microtask.reset();
}    