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
#include <client/pilot/Player.hpp>
    
namespace gui {

void ButtonTrigger::onPressEventMBL(client::Player* player)
{
    if (m_action)
    {
        m_action(player);
    }
    
    if (isLocked() == false)
    {
        if (isPressed() == false)
        {
            _setIsPressed(true);
            ShadeOn();
        }
        else
        {
            _setIsPressed(false);
            shadeOff();
        }
    }
}

/*virtual override final*/    
void ButtonTrigger::_updateUnique(client::Player* player)
{
    if ( (isLocked() == false) and (isPressed() == false) )
    {
        if (m_alpha < 1.0f)
        {
            m_alpha += 0.01f;
        }
        else
        {
            m_alpha = 1.0f;
        }
    }
}

} // namespace gui
