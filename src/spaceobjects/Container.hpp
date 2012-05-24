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


class Container : public BaseGameEntity
{
    	public:                  
        	Container(int);
        	virtual ~Container();
        	
        	ItemSlot* GetItemSlot() const { return item_slot; };

        	void RenderInfoInSpace(vec2f);
        	
        	virtual void PostDeathUniqueEvent(bool);
            	
        	void UpdateInSpace(int, bool);
        	
		void SilentKill();
          	void CalcCollisionrRadius();
        	void Render2D();
                                
        	virtual void SaveData(boost::property_tree::ptree&) const;
		virtual void LoadData(const boost::property_tree::ptree&);
		virtual void ResolveData();
		
        private:
                ItemSlot* item_slot;        
        	void UpdateInfo();  
                
                vec2f target_pos;
        	vec2f d_pos;
        	
        	float velocity;
        	bool keep_moving;
};

#endif 
