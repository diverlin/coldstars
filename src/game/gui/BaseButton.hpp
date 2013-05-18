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


#ifndef BASEBUTTON_H
#define BASEBUTTON_H

#include "../resources/textureOb.hpp"
#include "../common/Quad.hpp"
class AnimationEffect2D;

class BaseButton
{
    	public:
       		BaseButton(TextureOb*, int, const std::string&);       		       
       		virtual ~BaseButton();  

		void SetSubTypeId(int subtype_id) { this->subtype_id = subtype_id; } 
		void SetInfo(const std::string& info) { this->info = info; }
		void SetLabel(const std::string& label) { this->label = label; }		

		void SetQuad(const Quad& quad) { this->quad = quad; }	
													
		void SetTextureObAdditional(TextureOb* textureOb_additional) { this->textureOb_additional = textureOb_additional; }
		void SetTextureObMask(TextureOb* textureOb_mask) { this->textureOb_mask = textureOb_mask; }

       		TextureOb* GetTextureOb() const { return textureOb; }

		const Quad& GetQuad() { return quad; }
		
       		int GetTypeId() const { return type_id; }
       		int GetSubTypeId() const { return subtype_id; }
      		
       		bool GetLock() const { return lock; }
       		bool GetPressed() const { return pressed; }

		virtual void PressEvent() {}
		
       		void LockOn();
       		void LockOff();
       		virtual void Update() {};

		void Reset();
		
       		void RenderInfo(int offset_x = 0, int offset_y = 0) const;        		
       		void Render(int offset_x = 0, int offset_y = 0) const;   
       		        
        protected:
        	int type_id, subtype_id;
        	
        	bool lock;
        	bool pressed;
        	
        	float alpha;
        	Quad quad;
        	        	
               	TextureOb* textureOb;
               	TextureOb* textureOb_additional;
               	TextureOb* textureOb_mask;
       		
       		std::string info; 
       		std::string label; 
       		
       		AnimationEffect2D* animation_scale;
       		
     		void FullShadeOn();
     		void ShadeOn();
     		void ShadeOff();
};

#endif
