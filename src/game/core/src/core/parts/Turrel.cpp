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

#include "Turrel.hpp"

#include "../slots/ItemSlot.hpp"
//#include <jeti/Render.hpp>
#include <core/spaceobject/SpaceObject.hpp>

#include <ceti/Logger.hpp>

Turrel::Turrel(ItemSlot* slot)
    :
      ceti::control::Orientation(new ceti::model::Orientation)
{
    m_slot = slot;
}

Turrel::~Turrel()
{}

void Turrel::Render(float turrel_angle_inD)
{        
    //if (slot->GetTarget() != nullptr)
    //{
    //float _tur_xl = slot->GetTarget()->center().x - center().x;
    //float _tur_yl = slot->GetTarget()->center().y - center().y;

    //float _tur_angle_inR = atan2(_tur_yl, _tur_xl);
    //turrel_angle_inD = _tur_angle_inR * RADIAN_TO_DEGREE_RATE;
    //}

    //drawQuad(textureOb(), center(), size(), turrel_angle_inD);
}        

