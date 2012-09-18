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

#ifndef SHIELD_H
#define SHIELD_H

#include "../resources/textureOb.hpp"
#include "../spaceobjects/BaseGameEntity.hpp"

class ShieldEffect
{  
     	public:
        	ShieldEffect();
        	~ShieldEffect();

                void SetTextureOb(TextureOb* textureOb) { this->textureOb = textureOb; };
		void SetAlpha(float alpha) { color.a = alpha; };
                void SetParent(BaseGameEntity* parent) { this->parent = parent; };
		
                Points& GetPoints() { return points; };
        	void Update();
        	void Render(float) const;            

        private:       
        	Color4f color;
        	float alpha_start;
        	float d_alpha;
                
                Points points;
                TextureOb* textureOb;
                BaseGameEntity* parent;
                
};

#endif 




