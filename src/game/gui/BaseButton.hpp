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


#ifndef BaseButton_HPP
#define BaseButton_HPP

#include "BaseGuiElement.hpp"
class AnimationEffect2D;

class BaseButton : public BaseGuiElement
{
	public:
       		BaseButton(int, const std::string&,void (*pAction)(Player*), TextureOb* textureOb = nullptr);       		       
       		virtual ~BaseButton();  

			void SetTextureObAdditional(TextureOb* textureOb_additional) { this->textureOb_additional = textureOb_additional; }
			void SetTextureObMask(TextureOb* textureOb_mask) { this->textureOb_mask = textureOb_mask; }
      		
      		//void SetCallBack(void (*funcp)()) { this->pAction = pAction; }
      		
       		bool GetLock() const { return lock; }
       		bool GetPressed() const { return pressed; }
		
       		void LockOn();
       		void LockOff();

			void Reset();
		
       		void RenderInfo(int offset_x = 0, int offset_y = 0) const;        		
       		void Render(int offset_x = 0, int offset_y = 0) const;   
       		        
	protected:        	
        	bool lock;
        	bool pressed;
        	
        	float alpha;        	        	

			TextureOb* textureOb_additional;
			TextureOb* textureOb_mask;
       		
       		AnimationEffect2D* animation_scale;
       		
       		void (*pAction)(Player*);
       		 
     		void FullShadeOn();
     		void ShadeOn();
     		void ShadeOff();
};

#endif
