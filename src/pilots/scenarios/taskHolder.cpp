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



TaskHolder :: TaskHolder()
{
	is_valid = false;
	
	target   = NULL;
	scenario = NULL;
}

TaskHolder :: ~TaskHolder()
{}

bool TaskHolder :: getValid() const { return is_valid; }
SpaceObjectBase*  TaskHolder :: getTarget() const { return target; }	
ScenarioBase* TaskHolder :: getScenario()   const { return scenario; }

void TaskHolder :: set(ScenarioBase* scenario, SpaceObjectBase* target)
{
	is_valid = true;
	
	this->scenario = scenario;
	this->target   = target;
}


void TaskHolder :: reset()
{
	is_valid = false;
	
	scenario = NULL;
	target   = NULL;
}


