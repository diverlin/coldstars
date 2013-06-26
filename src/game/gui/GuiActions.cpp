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

#include "GuiActions.hpp"
#include "GuiGalaxyMap.hpp"
#include "../pilots/Player.hpp"
#include "../pilots/Npc.hpp"
#include "../spaceobjects/Vehicle.hpp"


#include "../world/EntityManager.hpp"
#include "../gui/GuiManager.hpp"

/* static */
void GuiActions::GalaxyMapGuiTransition(Player* player) 
{ 
	if (GuiManager::Instance().GetGuiGalaxyMap()->GetGalaxy() == nullptr)
	{
		GuiManager::Instance().GetGuiSpace().EnterGalaxyMap();

	}
	else
	{
		GuiManager::Instance().GetGuiSpace().ExitGalaxyMap();
	}

	std::cout<<"GuiActions::GalaxyMapGuiTransition"<<std::endl;
}

/* static */
void GuiActions::Save(Player* player) 
{ 
	EntityManager::Instance().SaveRequest();
	std::cout<<"GuiActions::Save"<<std::endl; 
}

/* static */
void GuiActions::Load(Player* player) 
{ 
	EntityManager::Instance().LoadRequest();
	std::cout<<"GuiActions::Load"<<std::endl; 
}



/* static */
void GuiActions::Test(Player* player) 
{ 
	std::cout<<"GuiActions::Test"<<std::endl; 
}

/* static */
void GuiActions::Test2(Player* player) 
{ 
	std::cout<<"GuiActions::Test2"<<std::endl; 
}

