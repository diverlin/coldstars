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

#include "../gui/BaseGuiElement.hpp"

class BaseButton : public BaseGuiElement
{
    	public:
       		BaseButton(TextureOb*, int, const std::string&);       		       
       		virtual ~BaseButton();  

       		bool GetLock() const { return lock; };
       		bool GetPressed() const { return pressed; };

		virtual void PressEvent()=0;
		
       		void LockOn();
       		void LockOff();
       		virtual void Update()=0;

		void Reset();
		
       		void Render() const;    
        
        protected:
        	bool lock;
        	bool pressed;
        	float alpha;
        	
     		void FullShadeOn();
     		void ShadeOn();
     		void ShadeOff();
};

#endif
