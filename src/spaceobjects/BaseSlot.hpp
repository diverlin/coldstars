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


#ifndef BASESLOT_H
#define BASESLOT_H

#include "../common/constants.hpp"
#include "../common/rect.hpp"
class Vehicle;

struct UnresolvedDataUniqueBaseSlot
{
	UnresolvedDataUniqueBaseSlot()
	{
		owner_type_id = NONE_ID;
		owner_id = NONE_ID;
			
		rect_blx = 0.0;
        	rect_bly = 0.0;
        	rect_w = 0; 
        	rect_h = 0;  
	};
	
	int owner_type_id;
	int owner_id;
	
	float rect_blx;
        float rect_bly;
        int rect_w; 
        int rect_h;         
};


class BaseSlot : public Base
{   
	public:        
		BaseSlot();
		~BaseSlot();
                
		void SetTextureOb(TextureOb* textureOb)       	{ this->textureOb = textureOb; };
		void SetOwner(Base* owner) { this->owner = owner; };
		
		bool GetEquiped() const { return is_EQUIPED; };
		
                Rect& GetRect() { return rect; };
		Vehicle* GetOwnerVehicle() const { return (Vehicle*)owner; };
		Base* GetOwner() const { return owner; };
			
                void SetRect(float, float, int, int);
        
        	virtual void SaveData(boost::property_tree::ptree&) const;
		virtual void LoadData(const boost::property_tree::ptree&);
		virtual void ResolveData();
		
        protected:
                bool is_EQUIPED;                       
                
                TextureOb* textureOb;
                
                Rect rect;
                                
                Base* owner; 
             
                UnresolvedDataUniqueBaseSlot unresolved_BaseSlot;
                void SaveDataUniqueBaseSlot(boost::property_tree::ptree&, const std::string&) const;
		void LoadDataUniqueBaseSlot(const boost::property_tree::ptree&);
		void ResolveDataUniqueBaseSlot();
}; 

#endif
