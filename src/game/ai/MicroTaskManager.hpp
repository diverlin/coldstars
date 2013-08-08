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

#ifndef MICROTASKMANAGER_H
#define MICROTASKMANAGER_H

#include "Task.hpp"
#include "scenarios/BaseScenario.hpp"
class BaseSpaceEntity;

class MicroTaskManager
{
    public:
        MicroTaskManager();
        ~MicroTaskManager();
        
        void SetTask(const Task&);
        
        BaseSpaceEntity* GetTarget() const { return target; };
        const Task& GetTask() const { return microtask; };    
        BaseScenario* GetScenario() const { return scenario; };
                
    private:
        Task microtask;    
        BaseScenario* scenario;
        BaseSpaceEntity* target;
        
        void Reset();    
        
    friend class StateMachine;
};


#endif 
     
