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

#include "StateMachine.hpp"

StateMachine::StateMachine() 
{}
        
StateMachine::~StateMachine() 
{}
        
void StateMachine::updateInStaticInSpace()
{
    if (m_macrotaskManager.scenario()) {
        m_macrotaskManager.scenario()->UpdateInStaticInSpace(m_npc);
    }
    if (m_microtaskManager.scenario() != nullptr) {
        if (m_microtaskManager.scenario()->Validate(m_npc)) {
            m_microtaskManager.scenario()->UpdateInStaticInSpace(m_npc);
        } else {
            m_microtaskManager.scenario()->exit(m_npc);
            m_microtaskManager.__reset();
        }
    }
}

void StateMachine::updateInStaticInDock()
{
    if (m_macrotaskManager.scenario()) {
        m_macrotaskManager.scenario()->UpdateInStaticInDock(m_npc);
    }
    if (m_microtaskManager.scenario()) {
        if (m_microtaskManager.scenario()->Validate(m_npc)) {
            m_microtaskManager.scenario()->UpdateInStaticInDock(m_npc);
        } else {
            m_microtaskManager.scenario()->exit(m_npc);
            m_microtaskManager.__reset();
        }
    }
}

void StateMachine::updateInDynamicInSpace()
{
    if (m_microtaskManager.scenario()) {
        m_microtaskManager.scenario()->UpdateInDynamicInSpace(m_npc);
    }
}

void StateMachine::updateInDynamicInDock()
{
    if (m_microtaskManager.scenario()) {
        m_microtaskManager.scenario()->UpdateInDynamicInDock(m_npc);
    }
}    
        
void StateMachine::setCurrentMacroTask(const Task& macrotask)
{
    if (m_macrotaskManager.scenario()) {
        m_macrotaskManager.scenario()->exit(m_npc);
        m_macrotaskManager.__reset();
    }
    
    m_macrotaskManager.setTask(macrotask);
    m_macrotaskManager.scenario()->enter(m_npc);
}

                
void StateMachine::setCurrentMicroTask(const Task& microtask)
{
    if (m_microtaskManager.scenario()) {
        m_microtaskManager.scenario()->exit(m_npc);
        m_microtaskManager.__reset();
    }
    
    m_microtaskManager.setTask(microtask);
    m_microtaskManager.scenario()->enter(m_npc);
}

void StateMachine::reset()
{
    if (m_microtaskManager.scenario()) {
        m_microtaskManager.scenario()->exit(m_npc);
        m_microtaskManager.__reset();
    }

    if (m_macrotaskManager.scenario()) {
        m_macrotaskManager.scenario()->exit(m_npc);
        m_macrotaskManager.__reset();
    }
}




