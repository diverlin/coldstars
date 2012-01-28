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


#ifndef BOMB_H
#define BOMB_H


class Bomb : public CommonForSpaceItems
{
    	public:  
        	Bomb(IdData _data_id, LifeData _data_life, TextureOb* _texOb);
        	~Bomb();

        	int getFunctionalSlotSubTypeId() const;
        	TextureOb* getTexOb() const;
        	
        	int getDamage() const;
        	int getRadius() const;
        	
        	void bindSlot(ItemSlot*);
		void updateOwnerPropetries();
			
        	void updateInfo();
        
        	void renderInfo();
        	void renderInfo(Rect, float, float);
        	
        private:
        	InfoTable info;
        	int damage;
        	int radius;
};

Bomb* getNewBomb();


#endif 

