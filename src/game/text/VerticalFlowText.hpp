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

#ifndef VERTICALFLOWTEXT_H
#define VERTICALFLOWTEXT_H

#include "../common/gameStruct.hpp"
#include "../common/myVector.hpp"

class VerticalFlowText
{
        public:
                VerticalFlowText(const std::string&, int, const vec2f&, const Color4i&, float);                                   
                ~VerticalFlowText();

		bool GetAlive() const { return is_alive; };
		
		const vec2f& GetPos() const { return pos; };

                void update();
                void Render(const vec2f&) const;
 
        private:
                bool is_alive;
                int live_time;

		int font_size;
		
                std::string str;
                Color4i color;

                vec2f offset;
                vec2f pos;
                
                float speed;
};

#endif 
