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


#ifndef VEHICLESLOT_H
#define VEHICLESLOT_H

struct UnresolvedDataUniqueVehicleSlot
{
	UnresolvedDataUniqueVehicleSlot()
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

class VehicleSlot : public Base
{
        public:
                VehicleSlot(int);
                ~VehicleSlot();

		void SetTextureOb(TextureOb* textureOb) { this->textureOb = textureOb; }
		void SetOwner(Base* owner) { this->owner = owner; };
		
                Vehicle* GetVehicle() const { return vehicle; };
                const Rect& GetRect() const { return rect; };
                
                void SetRect(float, float, int, int);
                
                void Insert(Vehicle*);
                void Free(); 
        
                void Render() const;
                void RenderInfo() const;
                
                virtual void SaveData(boost::property_tree::ptree&) const;
		virtual void LoadData(const boost::property_tree::ptree&);
		virtual void ResolveData();
		
        private:
                TextureOb* textureOb;
                        
                Base* owner;
                
                Vehicle* vehicle;                
                Rect rect;   
                
                UnresolvedDataUniqueVehicleSlot unresolved_VehicleSlot;
                void SaveDataUniqueVehicleSlot(boost::property_tree::ptree&, const std::string&) const;
		void LoadDataUniqueVehicleSlot(const boost::property_tree::ptree&);
		void ResolveDataUniqueVehicleSlot();     
}; 

#endif
