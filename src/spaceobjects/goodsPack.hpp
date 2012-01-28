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



#ifndef GOODSPACK_H
#define GOODSPACK_H


class GoodsPack : public CommonForSpaceItems
{
    	public:                  
        	GoodsPack(IdData _data_id, LifeData _data_life, TextureOb* _texOb);
        	~GoodsPack();
        	
        	TextureOb* getTexOb();
        	
        	void increase(unsigned int _ammount);       
                void decrease(unsigned int _ammount);
        	
        	void updateInfo();
        	void renderInfo(Rect slot_rect, float offset_x, float offset_y);
        	
        private:
        	unsigned int mineral;
        	unsigned int food;
        	unsigned int medicine;
        	unsigned int military;
        	unsigned int drug;
        	
        	InfoTable info;
        	
};

GoodsPack* createGoodsPack(unsigned int _subtype_id, vec2f);

#endif 
