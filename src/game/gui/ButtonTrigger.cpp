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


#include "ButtonTrigger.hpp"
#include "../pilots/Player.hpp"
    
/*virtual override final*/
void ButtonTrigger::OnPressEventLMB(Player* player)
{
    if (m_pAction)
	{
        m_pAction(player);
	}
	
	if (m_Lock == false)
	{
		if (m_Pressed == false)
		{
			m_Pressed = true;
			ShadeOn();
		}
		else
		{
			m_Pressed = false;
			ShadeOff();
		}
	}
}

/*virtual override final*/	
void ButtonTrigger::UpdateUnique(Player* player)
{
	if ( (m_Lock == false) and (m_Pressed == false) )
	{
		if (m_Alpha < 1.0f)
		{
			m_Alpha += 0.01f;
		}
		else
		{
			m_Alpha = 1.0f;
		}
	}
}
