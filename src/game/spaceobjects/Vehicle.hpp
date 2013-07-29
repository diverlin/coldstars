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


#ifndef VEHICLE_HPP
#define VEHICLE_HPP

#include <spaceobjects/BaseSpaceEntity.hpp>
#include <parts/WeaponComplex.hpp>
#include <parts/DriveComplex.hpp>
#include <parts/ProtectionComplex.hpp>
#include <struct/VehicleKorpusData.hpp>
#include <struct/VehiclePropetries.hpp>
#include <struct/VehicleNeeds.hpp>

class VehicleSlot; 
class BaseLand; 
class Npc;
class GoodsPack;
class Container;
class BaseItem;
class BaseEquipment;
class BaseParticleSystem;
class ShockWaveEffect;


struct UnresolvedDataUniqueVehicle
{
	int drive_complex_target_id;
	int drive_complex_action_id;

	int starsystem_hyper_id;
	int parent_vehicleslot_id;
	int land_id;
};


enum class VEHICLE_SPECIAL_ACTION_TYPE
{
	NONE_ID=0, INITIATE_DOCKING_ID, INITIATE_LAUNCHING_ID, INITIATE_JUMPIN_ID, INITIATE_JUMPOUT_ID
};


class Vehicle : public BaseSpaceEntity
{   
    public:
        Vehicle();
        virtual ~Vehicle(); 

        void CreateDriveComplexTextureDependedStuff();
        void CreateProtectionComplexTextureDependedStuff(); 
        		
		void SetGodMode(bool god_mode) { m_GodMode = god_mode; }
		void SetSpecialActionId(VEHICLE_SPECIAL_ACTION_TYPE special_action_id) { m_SpecialActionId = special_action_id; }
		void SetParentVehicleSlot(VehicleSlot* parent_vehicleslot) { m_ParentVehicleSlot = parent_vehicleslot; }

        void SetLand(BaseLand* land) { m_Land = land; }
            
        void SetKorpusData(const VehicleKorpusData&);

        bool GetGodMode() const { return m_GodMode; }
        BaseLand* const GetLand() const { return m_Land; }
        VEHICLE_SPECIAL_ACTION_TYPE GetSpecialActionId() const { return m_SpecialActionId; }
        
        VehicleSlot* const GetParentVehicleSlot() const { return m_ParentVehicleSlot; }
        
        const VehiclePropetries& GetProperties() const { return m_Properties; }
        const VehicleNeeds& GetNeeds() const { return m_Needs; }        
        const VehicleKorpusData& GetDataKorpus() const { return m_DataKorpus; }
        
        virtual int GetGivenExpirience() const override final;
        bool CheckItemSlotPresenceBySubTypeId(TYPE::ENTITY) const;
        
        void AddItemSlot(ItemSlot*); 
        
        bool GetAllItemsFromVehicle(Vehicle*);
        
        bool AddItemToCargoSlot(BaseItem*);
        bool AddAndManageItem(BaseItem*);
        
        void ManageItemsInCargo();
        void SellItemsInCargo();
        
        bool SellItem(BaseItem*);
        bool BuyItem(BaseItem*);
        
        bool UnpackContainerItemToCargoSlot(Container*);
        
        int GetFreeSpace() const { return m_Properties.free_space; }
        
        void BindOwnerNpc(Npc*);
                
		bool IsObjectWithinRadarRange(BaseSpaceEntity*) const;
        
        WeaponComplex& GetComplexWeapon() { return m_ComplexWeapon; }   // !!!
        DriveComplex& GetComplexDrive()   { return m_ComplexDrive; }                
        ProtectionComplex& GetComplexProtector() { return m_ComplexProtector; }

        const WeaponComplex& GetComplexWeapon() const { return m_ComplexWeapon; }
                
        ItemSlot* const GetSlotRadar()     const { return m_SlotRadar; }
        ItemSlot* const GetSlotScaner()    const { return m_SlotScaner; }
        ItemSlot* const GetSlotEnergizer() const { return m_SlotEnergizer; }
        ItemSlot* const GetSlotGrapple()   const { return m_SlotGrapple; }
        ItemSlot* const GetSlotDroid()     const { return m_SlotDroid; }
        ItemSlot* const GetSlotFreezer()   const { return m_SlotFreezer; }
        
        Npc* const GetOwnerNpc() const { return m_OwnerNpc; }
        
        ItemSlot* const GetEmptyCargoSlot();
        GoodsPack* GetGoodsPack() const;
        
        void UpdateSpecialAction();         
        virtual void UpdateInSpace(int, bool) = 0;
        
        virtual void TakeIntoAccountAgressor(Vehicle*);
        virtual void Hit(int, bool);
        
        virtual void PostDeathUniqueEvent(bool); 
        
        void CheckNeedsInStatic();
        void ResolveNeedsInKosmoportInStatic();
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
            
		virtual void RenderStuffWhenFocusedInSpace() override final;
        virtual void RenderInfoInSpace(const Vec2<float>&, float) override final;
        void RenderInfo(const Vec2<float>&, int, int);
                    
        void RenderRadarRange();
        void RenderGrappleRange();        

		bool IsAbleToJumpTo(StarSystem*) const;
		
		bool IsArmorFull() const;
		int GetArmorMiss() const;
		void IncreaseArmor(int);
		
		bool IsFuelFull() const;
		int GetFuelMiss() const;
                
        void RepairKorpusOnAmount(int);
        
        void LockRandomItem(int);
        
        bool TryToConsumeEnergy(int);
        bool TryToGenerateEnergy(int);
        
        void TEST_DamageAndLockRandItems();
        	
	protected:
        std::vector<ItemSlot*> m_SlotTotal_vec;
            
        ItemSlot* const GetFuctionalSlot(TYPE::ENTITY) const;
        ItemSlot* const GetEmptyArtefactSlot() const;
        ItemSlot* const GetCargoSlotWithGoods(TYPE::ENTITY);
        
        bool ManageItem(BaseItem*);
        bool ManageFunctionEquipment(BaseItem*);
        bool ManageFunctionModule(BaseItem*);
        bool ManageFunctionArtefact(BaseItem*);
        bool ManageFunctionGoodsPack(BaseItem*);
                	
        virtual void UpdateInfo() = 0;
        
        void RenderGrabTrail() const;
        void RenderKorpus() const;
        void RenderTurrels() const;
        void RenderDriveEffect(float scale, float parent_d_alpha = 0.0) const;
        void RenderShieldEffect(float parent_d_alpha = 0.0) const;          
        
        void UpdateGrappleMicroProgram_inDynamic();
        
        virtual void PutChildsToGarbage() const override;
                	        	                                
        UnresolvedDataUniqueVehicle data_unresolved_Vehicle;
        
        void SaveDataUniqueVehicle(boost::property_tree::ptree&, const std::string&) const;		
        void LoadDataUniqueVehicle(const boost::property_tree::ptree&);
		void ResolveDataUniqueVehicle();

    private:
        bool m_GodMode;
		VEHICLE_SPECIAL_ACTION_TYPE m_SpecialActionId;
        
        Npc* m_OwnerNpc;
        
        VehicleSlot* m_ParentVehicleSlot;
       
        BaseLand* m_Land;
        
        ItemSlot* m_SlotRadar;
        ItemSlot* m_SlotScaner;
        ItemSlot* m_SlotEnergizer;
        ItemSlot* m_SlotGrapple;
        ItemSlot* m_SlotDroid;
        ItemSlot* m_SlotFreezer;
         
        std::vector<ItemSlot*> m_SlotFunct_vec;
        std::vector<ItemSlot*> m_SlotArtef_vec;
        std::vector<ItemSlot*> m_SlotCargo_vec;
      
        WeaponComplex     m_ComplexWeapon;
        DriveComplex      m_ComplexDrive;
        ProtectionComplex m_ComplexProtector;
        
        VehiclePropetries m_Properties;
        VehicleNeeds m_Needs;
        VehicleKorpusData m_DataKorpus;
                                                                               
        void DropRandomItemToSpace();   
        bool MergeIdenticalGoods(BaseItem*);
             	
    friend class GuiVehicle;
    friend class GuiVehicle2;             	
};

std::string getVehicleSpecialActionStr(VEHICLE_SPECIAL_ACTION_TYPE);

#endif 
