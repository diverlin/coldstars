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



#ifndef CONTAINER_H
#define CONTAINER_H


class Container : public CommonForSpaceItems
{
    	public: 
        	int id, type_id;
                  
                ItemSlot* otsec_slot;
                            
        	int mass;
        	int size;

        	Container();
        	Container(TextureOb* _pTo_texOb, float _pos_x, float _pos_y, float _target_x, float _target_y);
        	~Container();
        
        	void renderInfo();
};

#endif 
