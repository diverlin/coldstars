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


#ifndef STORE_H
#define STORE_H


class Store
{
        public:
                Store(TextureOb*, TextureOb*);                      
                ~Store();

                ItemSlot* getEmptySlot();
                
                bool add(BaseItem*);
                                                        void createSlots();                                                        
                     	
                bool sellItemFromSlot(Npc*, ItemSlot*);		
                bool buyItemFromSlot(Npc*, ItemSlot*); 

                void Render() const;
                
        public:
                TextureOb* texOb_background; 
                TextureOb* texOb_slot;                 
              
                std::vector<ItemSlot*> slot_vec;
};
           
           
           
void equipStore(Store* store);
//Store* createStore(int race_id);

#endif




