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


#ifndef TEXTSTUFF_H
#define TEXTSTUFF_H
#include "../common/gameStruct.hpp"


//class TextBoard
//{
 	//public:
       		//TextBoard();
       		//~TextBoard();

//};


class VerticalFlowText
{
        public:
                VerticalFlowText(std::string _str, 
                                vec2f _center, 
                                Color4i _color, 
                                float _collision_radius);
                                   
                ~VerticalFlowText();

		bool GetAlive() const;

                void update();
                void Render(vec2f) const;
 
        private:
                bool is_alive;
                int live_time;

                std::string str;
                Color4i color;

                vec2f offset;
                vec2f pos;
                
                float speed;
};



class InfoTable
{
	public:
            	std::vector<std::string> title_list;        
        	std::vector<std::string> value_list;
        	
		InfoTable();
		~InfoTable();

		void clear();
		void addTitleStr(std::string);
		void addNameStr(std::string);
		void addValueStr(std::string);
};

#endif 
