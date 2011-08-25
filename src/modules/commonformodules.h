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


#ifndef COMMONFORMODULES_H
#define COMMONFORMODULES_H


class CommonForModules
{
    	public:
    	    	int getId() const;
    		int getType() const;
    		int getSubType() const;

    		
       	      	VEC_pString_type info_title_pList;  // make private
      		VEC_pString_type info_value_pList;  // make private 
      		
           	Rect rect;
      		int mass;   
    
      		CommonForModules();
      		void CommonForModules_init(int _subtype_id, TextureOb* _pTo_texOb);
      		~CommonForModules();
      		
      		TextureOb* getTexOb() const;

      		void render(Rect slot_rect);
           		void (CommonForModules::*pToFunc_render)(Rect slot_rect); 
           		void _renderFrame(Rect slot_rect);
           		void _renderFrames(Rect slot_rect);

      		void renderInfo(Rect slot_rect); 
      		
      	private:
      	      	int id, type_id, subtype_id;
      	      		
     		TextureOb* pTo_texOb;
     		int w, h;  
};

#endif
