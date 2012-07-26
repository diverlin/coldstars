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

#include "BaseGuiElement.hpp"

BaseGuiElement::BaseGuiElement(TextureOb* textureOb, int subtype_id, const std::string& info)
{	
    	this->textureOb = textureOb;
	this->subtype_id = subtype_id;
    	this->info = info; 

	textureOb_additional = NULL;
}

BaseGuiElement::~BaseGuiElement()
{}

void BaseGuiElement::SetCenter(int x, int y)
{        
     	rect.SetCenter((float)x, (float)y);
}

void BaseGuiElement::RenderInfo(int offset_x, int offset_y) const
{
     	drawSimpleText(info, 12, rect.GetBottomLeft().x - 50 + offset_x, rect.GetBottomLeft().y + 30 + offset_y);
}
