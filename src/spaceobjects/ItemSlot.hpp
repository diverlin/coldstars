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


#ifndef ITEMSLOT_H
#define ITEMSLOT_H

struct UnresolvedDataUniqueItemSlot
{
	UnresolvedDataUniqueItemSlot()
	{
		owner_vehicle_id = NONE_ID;
		owner_angar_id   = NONE_ID;
		owner_store_id   = NONE_ID;
			
		rect_blx = 0.0;
        	rect_bly = 0.0;
        	rect_w = 0; 
        	rect_h = 0;  
	};
	
	int owner_vehicle_id;
	int owner_angar_id;
	int owner_store_id;
	
	float rect_blx;
        float rect_bly;
        int rect_w; 
        int rect_h;         
};


class ItemSlot : public Base
{   
	public:        
		ItemSlot(int id);
		~ItemSlot();
                
		void SetTextureOb(TextureOb* textureOb)       	{ this->textureOb = textureOb; };
		void SetOwnerVehicle(Vehicle* owner_vehicle) 	{ this->owner_vehicle = owner_vehicle; };
		void SetOwnerAngar(Angar* owner_angar) 		{ this->owner_angar = owner_angar; };
		void SetOwnerStore(Store* owner_store) 	{ this->owner_store = owner_store; };
		void SetTurrel(Turrel* turrel)                	{ this->turrel = turrel; };
                                
		Turrel* GetTurrel()     const { return turrel; };
		bool GetEquipedStatus() const { return is_EQUIPED; };
		
                Rect& GetRect() { return rect; };
		Vehicle* GetOwnerVehicle() const { return owner_vehicle; };

		BaseItem* GetItem()                         const { return item; };                
             	RocketEquipment*    GetRocketEquipment()    const { return (RocketEquipment*)item; }
 		LazerEquipment*     GetLazerEquipment()     const { return (LazerEquipment*)item; }
		RadarEquipment*     GetRadarEquipment()     const { return (RadarEquipment*)item; }
		DriveEquipment*     GetDriveEquipment()     const { return (DriveEquipment*)item; }
		BakEquipment*       GetBakEquipment()       const { return (BakEquipment*)item; }
		EnergizerEquipment* GetEnergizerEquipment() const { return (EnergizerEquipment*)item; }
		ProtectorEquipment* GetProtectorEquipment() const { return (ProtectorEquipment*)item; }
		DroidEquipment*     GetDroidEquipment()     const { return (DroidEquipment*)item; }
		FreezerEquipment*   GetFreezerEquipment()   const { return (FreezerEquipment*)item; }
		ScanerEquipment*    GetScanerEquipment()    const { return (ScanerEquipment*)item; }
		GrappleEquipment*   GetGrappleEquipment()   const { return (GrappleEquipment*)item; }

		RocketModule*       GetRocketModule()       const { return (RocketModule*)item; }
		LazerModule*        GetLazerModule()        const { return (LazerModule*)item; }
		RadarModule*        GetRadarModule()        const { return (RadarModule*)item; }
		DriveModule*        GetDriveModule()        const { return (DriveModule*)item; }
		BakModule*          GetBakModule()          const { return (BakModule*)item; }
		EnergizerModule*    GetEnergizerModule()    const { return (EnergizerModule*)item; }
		ProtectorModule*    GetProtectorModule()    const { return (ProtectorModule*)item; }
		DroidModule*        GetDroidModule()        const { return (DroidModule*)item; }
		FreezerModule*      GetFreezerModule()      const { return (FreezerModule*)item; }
		ScanerModule*       GetScanerModule()       const { return (ScanerModule*)item; }
		GrappleModule*      GetGrappleModule()      const { return (GrappleModule*)item; }

		Bomb* GetBomb()           const { return (Bomb*)item; }
		//Artefact* GetArtefact() const { return artefact; }
		GoodsPack* GetGoodsPack() const { return (GoodsPack*)item; }
		//Vehicle* GetVehicle()   const { return vehicle; }

                void SetRect(float, float, int, int);
                                
		bool InsertItem(BaseItem*);
            
		void RemoveItem();
                
		void Render(GLuint);
       
		void RenderEquipedItem();
		void RenderItemInfo(float offset_x = 0, float offset_y = 0);
                
                bool CheckInteraction(int, int);
                
                void DropItemToSpace();
                
                bool SwapItemWith(ItemSlot*);
                
                void UpdateRange(TextureOb*);
           	void DrawRange();
           	
           	bool CheckTarget(BaseGameEntity*) const;
           	
           	void UpdateOwnerAbilities();
        
        	virtual void SaveData(boost::property_tree::ptree&) const;
		virtual void LoadData(const boost::property_tree::ptree&);
		virtual void ResolveData();
		
        private:
                bool is_EQUIPED;                       
                
                TextureOb* textureOb;
                
                Rect rect;
                                
                Vehicle* owner_vehicle;              
                Angar*   owner_angar;
                Store*   owner_store;
                                
                Turrel* turrel;          // only for weapons slot
                
                BaseItem*    item;

		std::vector<vec2f> range_vec;
           	PathVisual range_visual;
           	
           	int GetItemRadius() const;
           	                
                bool CheckStarSystem(BaseGameEntity*) const;
           	bool CheckDistance(BaseGameEntity*) const;
                
                UnresolvedDataUniqueItemSlot unresolved_ItemSlot;
                void SaveDataUniqueItemSlot(boost::property_tree::ptree&, const std::string&) const;
		void LoadDataUniqueItemSlot(const boost::property_tree::ptree&);
		void ResolveDataUniqueItemSlot();
}; 

#endif
