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

#ifndef CONTAINER_HPP
#define CONTAINER_HPP

#include "BaseSpaceEntity.hpp"
#include "../slots/ItemSlot.hpp"

class Container : public BaseSpaceEntity
{
    public:                  
        Container(int);
        virtual ~Container();
        
        virtual void PutChildsToGarbage() const;
        
        void SetTargetPos(const Vec3<float>& target_pos, float velocity) { this->target_pos = target_pos; this->velocity = velocity; };
        void BindItemSlot(ItemSlot*);
        ItemSlot* GetItemSlot() const { return item_slot; };

        virtual void RenderInfoInSpace(const Vec2<float>&, float) override final;
        
        virtual void PostDeathUniqueEvent(bool);
            
        void UpdateInSpace(int, bool);

        void Render2D();
                            
        virtual void SaveData(boost::property_tree::ptree&) const;
		virtual void LoadData(const boost::property_tree::ptree&);
		virtual void ResolveData();
		
    private:
        ItemSlot* item_slot;        
        void UpdateInfo();  
        
        Vec3<float> target_pos;    	
        float velocity;
        
        void SaveDataUniqueContainer(boost::property_tree::ptree&, const std::string&) const;		
		void LoadDataUniqueContainer(const boost::property_tree::ptree&);
		void ResolveDataUniqueContainer();
};

#endif 
