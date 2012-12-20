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

#ifndef VEHICLE_H
#define VEHICLE_H

#include "../spaceobjects/BaseSpaceEntity.hpp"
class VehicleSlot; 
class BaseLand; 
class Npc;
class GoodsPack;
class Container;
class BaseItem;
class BaseEquipment;

#include "../parts/WeaponComplex.hpp"
#include "../parts/DriveComplex.hpp"
#include "../parts/ProtectionComplex.hpp"
#include "../parts/VehicleKorpusData.hpp"
#include "../parts/VehiclePropetries.hpp"

class BaseParticleSystem;
class ShockWaveEffect;

struct UnresolvedDataUniqueVehicle
{
	int drive_complex_target_id;
	int drive_complex_action_id;

	int starsystem_hyper_id;
	int parent_vehicleslot_id;
	int land_id;
	//std::string textureOb_gui_path; 	
};

class Vehicle : public BaseSpaceEntity
{   
    	public:
       	        Vehicle();
        	virtual ~Vehicle(); 

		virtual void PutChildsToGarbage() const;
		
		void SetGodMode(bool god_mode) { this->god_mode = god_mode; };
		void SetSpecialActionId(int special_action_id) { this->special_action_id = special_action_id; };
		void SetParentVehicleSlot(VehicleSlot* parent_vehicleslot) { this->parent_vehicleslot = parent_vehicleslot; };
		
        	void SetColor(const Color4f& color) { this->color = color; }
        	void SetLand(BaseLand* land) { this->land = land; };
        	        
                void SetKorpusData(const VehicleKorpusData&);
                void CreateDriveComplexTextureDependedStuff();
                void CreateProtectionComplexTextureDependedStuff();
                
                bool GetGodMode() const { return god_mode; };
        	BaseLand* GetLand() const { return land; };
        	int GetSpecialActionId() const { return special_action_id; };
        	
        	VehicleSlot* GetParentVehicleSlot() const { return parent_vehicleslot; };
        	
        	const VehiclePropetries& GetProperties() const { return properties; };
                               
                VehicleKorpusData& GetKorpusData() { return data_korpus; };
                			
                void AddItemSlot(ItemSlot*); 
                
                bool GetAllItemsFromVehicle(Vehicle*);
                
                bool AddItemToCargoSlot(BaseItem*);
                bool AddAndManageItem(BaseItem*);
               
                void ManageItemsInCargo();
                void SellItemsInCargo();
                
                bool SellItem(BaseItem*);
                bool BuyItem(BaseItem*);
                                                
                bool UnpackContainerItemToCargoSlot(Container*);
                
                int GetFreeSpace() const { return properties.free_space; };

                void BindOwnerNpc(Npc*);
                
		bool IsObjectWithinRadarRange(BaseSpaceEntity*) const;
		
                WeaponComplex& GetWeaponComplex() { return weapon_complex; };
                DriveComplex& GetDriveComplex()   { return drive_complex; };                
                ProtectionComplex& GetProtectionComplex() { return protection_complex; };
                
        	ItemSlot* GetRadarSlot()     const { return radar_slot; };
        	ItemSlot* GetScanerSlot()    const { return scaner_slot; };
        	ItemSlot* GetEnergizerSlot() const { return energizer_slot; };
        	ItemSlot* GetGrappleSlot()   const { return grapple_slot; };
        	ItemSlot* GetDroidSlot()     const { return droid_slot; };
        	ItemSlot* GetFreezerSlot()   const { return freezer_slot; };

                Npc* GetOwnerNpc() const { return owner_npc; };
        	
        	GoodsPack* GetGoodsPack() const;
                       	
         	bool BuyKorpusRepair();
        	       
        	void UpdateSpecialAction();         
        	virtual void UpdateInSpace(int, bool) = 0;
        	virtual void Hit(int, bool);

        	virtual void PostDeathUniqueEvent(bool); 
        	
        	void UpdateAllFunctionalItemsInStatic();
             	void IncreaseMass(int);
             	void DecreaseMass(int);
             	void UpdatePropertiesEnergy();
             	void UpdatePropertiesFreeze();
             	void UpdatePropertiesSpeed();
             	void UpdatePropertiesFire();
             	void UpdatePropertiesRadar();
             	void UpdatePropertiesJump();
             	void UpdatePropertiesProtection();
             	void UpdatePropertiesRepair();
             	void UpdatePropertiesScan();
             	void UpdatePropertiesGrab();
             	void UpdateArtefactInfluence();

        	void HyperJumpEvent(StarSystem*);
        	void DockingEvent();
        	void LaunchingEvent();
        	
		void UpdateSpecialEffect();
        	void UpdateLockedItems();
                
        	void RenderInfoInSpace(const vec2f&);
        	void RenderInfo(const vec2f&, int, int);
        	        	
        	void RenderRadarRange();
        	void RenderGrappleRange();        

		bool IsArmorFull() const;
		int GetArmorMiss() const;
		void IncreaseArmor(int);
		
		bool IsFuelFull() const;
		int GetFuelMiss() const;
		void BuyFuelAsMuchAsPossible();

		void LockRandomItem(int);

                bool TryToConsumeEnergy(int);
                bool TryToGenerateEnergy(int);
                                		
		void TEST_DamageAndLockRandItems();

	protected:
		int special_action_id;
	
	        VehiclePropetries properties;
                VehicleKorpusData data_korpus;
                
        	WeaponComplex     weapon_complex;
            	DriveComplex      drive_complex;
        	ProtectionComplex protection_complex;
                
		Npc* owner_npc;

        	ItemSlot* radar_slot;
        	ItemSlot* scaner_slot;
        	ItemSlot* energizer_slot;
        	ItemSlot* grapple_slot;
        	ItemSlot* droid_slot;
        	ItemSlot* freezer_slot;
                
                std::vector<ItemSlot*> slot_total_vec;
                std::vector<ItemSlot*> slot_funct_vec;
        	std::vector<ItemSlot*> slot_artef_vec;
        	std::vector<ItemSlot*> slot_cargo_vec;
                
   	     	BaseLand* land;
   	     	
                Color4f color;
                                
                VehicleSlot* parent_vehicleslot;
                        
                ItemSlot* GetFuctionalSlot(int) const;
       	        ItemSlot* GetEmptyCargoSlot();
       	        ItemSlot* GetEmptyArtefactSlot() const;
       	        ItemSlot* GetCargoSlotWithGoods(int);
       	        
       	        bool ManageItem(BaseItem*);
       	        bool ManageFunctionEquipment(BaseItem*);
                bool ManageFunctionModule(BaseItem*);
                bool ManageFunctionArtefact(BaseItem*);
                bool ManageFunctionGoodsPack(BaseItem*);
                	
                virtual void UpdateInfo() = 0;
             	     		
                void RenderGrabTrail() const;
		void RenderKorpus() const;
             	void RenderTurrels() const;
             	void RenderDriveEffect(float parent_d_alpha = 0.0) const;
          	void RenderShieldEffect(float parent_d_alpha = 0.0) const;
        	                
        	void UpdateGrappleMicroProgram();       
        	                                
                UnresolvedDataUniqueVehicle data_unresolved_Vehicle;
                
                void SaveDataUniqueVehicle(boost::property_tree::ptree&, const std::string&) const;		
		void LoadDataUniqueVehicle(const boost::property_tree::ptree&);
		void ResolveDataUniqueVehicle();

        private:
        	bool god_mode;
        	
                void RepairKorpusEvent(int);
                 	
             	void DropRandomItemToSpace();   
                bool MergeIdenticalGoods(BaseItem*);
                
                bool UpdateFadeInEffect();
        	bool UpdateFadeOutEffect();
             	
        friend class GuiVehicle;
        friend class GuiVehicle2;             	
};

#endif 
