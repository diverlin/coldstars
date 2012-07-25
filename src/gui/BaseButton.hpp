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
#include "../common/rect.hpp"

class BaseButton
{
    	public:
       		BaseButton(TextureOb* textureOb, 
       		       int subtype_id, 
       		       int pos_x, 
       		       int pos_y, 
       		       int w, 
       		       int h, 
       		       std::string info_str);
       		       
       		virtual ~BaseButton();  

		void SetAdditionalTextureOb(TextureOb* textureOb_additional) { this->textureOb_additional = textureOb_additional; };
       		const Rect& GetRect() const { return rect; };
       		TextureOb* GetTextureOb() const { return textureOb; };
       		int GetTypeId() const { return type_id; };
       		int GetSubTypeId() const { return subtype_id; };
       		bool GetLock() const { return lock; };
       		bool GetPressed() const { return pressed; };

		virtual void PressEvent()=0;
		
       		void LockOn();
       		void LockOff();
       		virtual void Update()=0;

       		void SetCenter(int, int);

		void Reset();
		
       		void Render() const;    
       		//void RenderWithTitle(const std::string&, int offset_x = 0, int offset_y = 0) const;    
       		void RenderInfo(int offset_x = 0, int offset_y = 0) const;
        
        protected:
        	int type_id, subtype_id;
        	bool lock;
        	bool pressed;
        	float alpha;
        	
               	TextureOb* textureOb;
               	TextureOb* textureOb_additional;
       		Rect rect;
       		std::string info;  

     		void FullShadeOn();
     		void ShadeOn();
     		void ShadeOff();
};

#endif
