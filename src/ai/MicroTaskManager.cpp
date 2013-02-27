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
#include "../world/EntityManager.hpp"

MicroTaskManager::MicroTaskManager()
{
	scenario = NULL;
	target = NULL;
}

MicroTaskManager::~MicroTaskManager()
{}

void MicroTaskManager::SetTask(const Task& microtask)
{
	this->microtask = microtask;
	scenario = ScenarioCollector::Instance().GetScenario(microtask.GetScenarioTypeId());
	if (microtask.GetTargetId() != NONE_ID)
	{
		target = (BaseSpaceEntity*)EntityManager::Instance().GetEntityById(microtask.GetTargetId()); // hack
	}
}

void MicroTaskManager::Reset()
{
	scenario  = NULL;
	target = NULL;
	microtask.Reset();
}	
