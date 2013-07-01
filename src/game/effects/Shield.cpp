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

#include "Shield.hpp"
#include "../render/Render.hpp"
#include "../resources/textureOb.hpp"
#include "../spaceobjects/BaseSpaceEntity.hpp"

ShieldEffect::ShieldEffect()
{       
        alpha_start = 0.4;
        d_alpha = 0.01;

        color.r = 1.0;
        color.g = 1.0;
        color.b = 1.0;
        color.a = alpha_start;
        
        textureOb = nullptr;
        parent = nullptr;
}

ShieldEffect::~ShieldEffect()
{}

void ShieldEffect::SetParent(BaseSpaceEntity* parent) 
{ 
	this->parent = parent; 
	
	float rate = 1.3; 
	size.Set(parent->GetSize() * rate); 
}


void ShieldEffect::Update()
{      
	if (color.a > alpha_start) 	{ 	color.a -= d_alpha; }
	else						{	color.a = alpha_start; }
}

void ShieldEffect::Render(float parent_d_alpha) const
{
	setColor4f(color.r, color.g, color.b, color.a - parent_d_alpha);	
	drawScaledQuad(textureOb, parent->GetCenter(), size, parent->GetAngle().z);
}


