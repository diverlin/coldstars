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


#ifndef BUTTON_H
#define BUTTON_H

class Button
{
    	public:
       		Button(TextureOb* _texOb, 
       		       int _subtype_id, 
       		       float _pos_x, 
       		       float _pos_y, 
       		       int _w, 
       		       int _h, 
       		       std::string _info_str);
       		       
       		~Button();  
       		
       		void setShowInfoFlag(bool);       		       		
       		bool getShowInfoFlag() const;
       		Rect getRect() const;
       		TextureOb* getTexOb();
       		int getTypeId() const;
       		int getSubTypeId() const;
       		       
       		bool interaction(int _x, int _y);

       		void setCenter(int _x, int _y);

       		void render() const;    
       		void renderInfo() const;
        
        private:
        	int type_id, subtype_id;
        	
               	TextureOb* texOb;
       		Rect rect;
       		std::string info_str;
       		bool show_info;
        
};

#endif
