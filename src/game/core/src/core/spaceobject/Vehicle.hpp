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


#pragma once

#include <core/spaceobject/SpaceObject.hpp>

#include <core/part/WeaponComplex.hpp>
#include <core/part/DriveComplex.hpp>
#include <core/part/ProtectionComplex.hpp>

#include <core/struct/VehiclePropetries.hpp>
#include <core/struct/VehicleNeeds.hpp>

#include <core/type/StatusTypes.hpp>

//#include <boost/serialization/vector.hpp>

class VehicleSlot;
class Land; 
class GoodsPack;

namespace descriptor {
class Vehicle;
} // namespace descriptor

namespace model {
class Vehicle;
class Container;
class StarSystem;
class Item;
} // namespace model

namespace control {
class Container;
class Npc;
class Item;
} //namespace control

class Equipment;
class BaseParticleSystem;
class ShockWaveEffect;

//struct UnresolvedDataVehicle
//{
//    int drive_complex_target_id;
//    int drive_complex_action_id;

//    int starsystem_hyper_id;
//    int parent_vehicleslot_id;
//    int land_id;
//};


enum class VEHICLE_SPECIAL_ACTION_TYPE {
    NONE=0, INITIATE_DOCKING, INITIATE_LAUNCHING, INITIATE_JUMPIN, INITIATE_JUMPOUT
};


namespace control {

class Vehicle : public SpaceObject
{
public:
    Vehicle(model::Vehicle*, descriptor::Vehicle*);
    virtual ~Vehicle();

    WeaponComplex& weaponComplex() { return m_weapon_complex; }
    DriveComplex& driveComplex() { return m_drive_complex; }
    ProtectionComplex& protectorComplex() { return m_protector_complex; }
    const ProtectionComplex& protectorComplex() const { return m_protector_complex; }

    // wepon complex interface
    void fire(int, float);
    void setWeaponTarget(model::SpaceObject* object, ItemSlot* slot = nullptr);
    void prepareWeapons();
    int guessDamage(int dist);
    //\ weapon complex interface

    [[deprecated("move to gui")]]
    void CreateDriveComplexTextureDependedStuff();
    [[deprecated("move to gui")]]
    void CreateProtectionComplexTextureDependedStuff();

    void setGodMode(bool god_mode) { m_godMode = god_mode; }
    void SetSpecialActionId(VEHICLE_SPECIAL_ACTION_TYPE special_action_id) { m_specialActionId = special_action_id; }
    void SetParentVehicleSlot(VehicleSlot* parent_vehicleslot) { m_parentVehicleSlot = parent_vehicleslot; }

    void setLand(Land* land) { m_Land = land; }

    void setKorpusData(descriptor::Vehicle*);

    bool godMode() const { return m_godMode; }
    Land* const land() const { return m_Land; }
    VEHICLE_SPECIAL_ACTION_TYPE GetSpecialActionId() const { return m_specialActionId; }

    VehicleSlot* const parentVehicleSlot() const { return m_parentVehicleSlot; }

    [[warning("remove this ugly non const")]]
    VehiclePropetries& properties() { return m_properties; }
    const VehiclePropetries& properties() const { return m_properties; }
    VehicleNeeds& needs() { return m_needs; }
    descriptor::Vehicle* descriptor() const { return m_descriptor_vehicle; }

    virtual int givenExpirience() const override final;
    bool isSlotTypePresent(const entity::Type&) const;

    void addItemSlot(ItemSlot*);

    [[deprecated("ship swap items in different logic")]]
    bool grabItemsFromVehicle(Vehicle*);

    bool install(Item*);
    bool load(Item*);
    bool manage(Item*);

    bool isSlotFree(const place::type&) const;
    bool checkManage(const core::Id&);

    void manageItemsInCargo();
    [[deprecated("move to ext")]]
    void sellItemsInCargo();

    [[deprecated("move to ext")]]
    bool sellItem(Item*);
    [[deprecated("move to ext")]]
    bool buyItem(Item*);

    //bool unpackContainerItemToCargoSlot(control::Container*);

    int freeSpace() const;
    int space() const;

    void bindNpc(control::Npc*);

    bool isObjectVisible(SpaceObject*) const;

public:
    [[warning("used only for tests")]]
    std::vector<ItemSlot*> bakSlots() const { return m_drive_complex.bakSlots(); }
    std::vector<ItemSlot*> driveSlots() const { return m_drive_complex.driveSlots(); }
    std::vector<ItemSlot*> radarSlots() const { return m_radarSlots; }
    std::vector<ItemSlot*> scanerSlots() const { return m_scanerSlots; }
#ifdef USE_EXTRA_EQUIPMENT
//    ItemSlot* energizerSlot() const { return m_energizerSlot; }
//    ItemSlot* freezerSlot()   const { return m_freezerSlot; }
#endif // USE_EXTRA_EQUIPMENT
    std::vector<ItemSlot*> grappleSlots() const { return m_grappleSlots; }
    std::vector<ItemSlot*> droidSlots() const { return m_droidSlots; }
    std::vector<ItemSlot*> protectorSlots() const { return protectorComplex().protectorSlots(); }

    std::vector<ItemSlot*> weaponSlots() const { return m_weapon_complex.weaponSlots(); }
    std::vector<ItemSlot*> cargoSlots() const { return m_cargoSlots; }

public:
    control::Npc* npc() const { return m_npc; }

    GoodsPack* goodsPack() const;

    void UpdateSpecialAction();
    virtual void UpdateInSpace(int, bool) = 0;

    virtual void remeberAgressor(Vehicle*);
    void hit(int) override;

    virtual void _postDeathUniqueEvent(bool);

    void CheckNeedsInStatic();
    void ResolveNeedsInKosmoportInStatic();
    void UpdateAllFunctionalItemsInStatic();

    bool dropItemToSpace(const entity::Type&);

private:
    void __increaseMass(int);
protected:
    void _decreaseMass(int);
    void _updatePropEnergy();
    void _updatePropFreeze();
    void _updatePropSpeed();
    void _updatePropFire();
    void _updatePropRadar();
    void _updatePropJump();
    void _updatePropProtection();
    void _updatePropRepair();
    void _updatePropScan();
    void _updatePropGrab();
    void _updateArtefactInfluence();
    friend class ItemSlot;
public:

    void HyperJumpEvent(model::StarSystem*);
    void DockingEvent();
    void LaunchingEvent();

    void UpdateSpecialEffect();
    void UpdateLockedItems();

    //        virtual void RenderStuffWhenFocusedInSpace(const jeti::Renderer&) override final;
    //        virtual void RenderInfoInSpace(const jeti::Renderer&, const glm::vec2&, float) override final;
    //        void RenderInfo(const glm::vec2&, int, int);

    //        void RenderRadarRange();
    //        void RenderGrappleRange();

    bool isAbleToJumpTo(model::StarSystem*) const;

    bool isArmorFull() const;
    int armorMiss() const;
    void increaseArmor(int);
    void repairKorpus(int);

    bool isFuelFull() const;
    int fuelMiss() const;

    void lockRandomItem(int);

    bool tryConsumeEnergy(int);
    bool tryGenerateEnergy(int);

    STATUS CheckGrabStatus() const;

    float adjustDissipateFilter() const;
    int criticalDamage() const;

private:
    void __updateFreeSpace();
//    bool __addItemToCargo(Item*);

protected:
    model::Vehicle* m_model_vehicle = nullptr;
    descriptor::Vehicle* m_descriptor_vehicle = nullptr;
    model::Vehicle* model() const { return m_model_vehicle; }

    ItemSlot* _freeArtefactSlot() const;
    ItemSlot* _cargoSlotWithGoods(place::type);

#ifdef USE_MODULES
    bool installModule(Item*);
#endif // USE_MODULES
#ifdef USE_ARTEFACTS
    bool installArtefact(Item*);
#endif // USE_ARTEFACTS
    bool _installGoodsPack(Item*);

    //        virtual void UpdateInfo() = 0;

    //        void RenderGrabTrail(const jeti::Renderer&) const;
    //        void RenderKorpus(const jeti::Renderer&);
    //        void RenderTurrels() const;
    //        void RenderDriveEffect(float scale, float parent_d_alpha = 0.0) const;
    //        void RenderShieldEffect(const jeti::Renderer&, float parent_d_alpha = 0.0) const;

    void UpdateGrappleMicroProgram_inDynamic();

    virtual void putChildrenToGarbage() const override;

private:
    bool m_godMode = false;
    VEHICLE_SPECIAL_ACTION_TYPE m_specialActionId = VEHICLE_SPECIAL_ACTION_TYPE::NONE;

    control::Npc* m_npc = nullptr;

    VehicleSlot* m_parentVehicleSlot = nullptr;

    Land* m_Land = nullptr;

    std::vector<ItemSlot*> m_radarSlots;
    std::vector<ItemSlot*> m_scanerSlots;
#ifdef USE_EXTRA_EQUIPMENT
    ItemSlot* m_energizerSlot = nullptr;
    ItemSlot* m_freezerSlot = nullptr;
#endif // USE_EXTRA_EQUIPMENT
    std::vector<ItemSlot*> m_grappleSlots;
    std::vector<ItemSlot*> m_droidSlots;

    std::vector<ItemSlot*> m_equipmentSlots;
    std::vector<ItemSlot*> m_artefactSlots;
    std::vector<ItemSlot*> m_cargoSlots;

    VehiclePropetries m_properties;
    VehicleNeeds m_needs;
    WeaponComplex     m_weapon_complex;
    DriveComplex      m_drive_complex;
    ProtectionComplex m_protector_complex;

    std::map<int, ItemSlot*> m_slots;

    [[deprecated("use predetermentistic way")]]
//    void __dropRandomItemToSpace();
    bool __mergeIdenticalGoods(Item*);

    model::Container* __wrapItemToContainer(Item*);
    bool _checkInstallEquipment(const core::Id&);

    std::vector<ItemSlot*> __equipedAndFunctionalSlots(const std::vector<ItemSlot*>&);
    void __createSlots(descriptor::Vehicle*);

    bool __manage(Item*);
    bool __insertItem(ItemSlot*, Item*);
    ItemSlot* __itemSlot(int) const;
    ItemSlot* __freeCargoSlot();

    bool __installItem(Item*);
    bool __installEquipment(Item*);
    ItemSlot* __freeFunctionalSlot(const entity::Type&) const;

    bool m_blockModel = false;
    void __blockModel() { m_blockModel = true; }
    void __releaseModel() { m_blockModel = false; }
    bool __modelBlocked() const { return m_blockModel; }

    void __actualizeItems();
};


} // namespace control
























//class Vehicle : public SpaceObject
//{
//public:
//    Vehicle();
//    virtual ~Vehicle();

//    // wepon complex interface
//    void fire(int, float);
//    void setWeaponTarget(SpaceObject* object, ItemSlot* slot = nullptr);
//    void prepareWeapons();
//    int guessDamage(int dist);
//    //\ weapon complex interface

//    [[deprecated("move to gui")]]
//    void CreateDriveComplexTextureDependedStuff();
//    [[deprecated("move to gui")]]
//    void CreateProtectionComplexTextureDependedStuff();

//    void setGodMode(bool god_mode) { m_godMode = god_mode; }
//    void SetSpecialActionId(VEHICLE_SPECIAL_ACTION_TYPE special_action_id) { m_specialActionId = special_action_id; }
//    void SetParentVehicleSlot(VehicleSlot* parent_vehicleslot) { m_parentVehicleSlot = parent_vehicleslot; }

//    void setLand(Land* land) { m_Land = land; }

//    void setKorpusData(descriptor::Vehicle*);

//    bool godMode() const { return m_godMode; }
//    Land* const land() const { return m_Land; }
//    VEHICLE_SPECIAL_ACTION_TYPE GetSpecialActionId() const { return m_specialActionId; }

//    VehicleSlot* const parentVehicleSlot() const { return m_parentVehicleSlot; }

//    const VehiclePropetries& properties() const { return m_properties; }
//    const VehicleNeeds& needs() const { return m_needs; }
//    descriptor::Vehicle* vehicleDescriptor() const { return m_vehicleDescriptor; }

//    virtual int givenExpirience() const override final;
//    bool isSlotTypePresent(const entity::Type&) const;

//    void addItemSlot(ItemSlot*);

//    [[deprecated("ship swap items in different logic")]]
//    bool grabItemsFromVehicle(Vehicle*);

//    bool addItemToCargoSlot(item::Base*);
//    bool manage(item::Base*);

//    bool isSlotFree(const entity::Type&) const;
//    bool checkManage(const core::Id&);

//    void manageItemsInCargo();
//    [[deprecated("move to ext")]]
//    void sellItemsInCargo();

//    [[deprecated("move to ext")]]
//    bool sellItem(item::Base*);
//    [[deprecated("move to ext")]]
//    bool buyItem(item::Base*);

//    bool unpackContainerItemToCargoSlot(Container*);

//    int freeSpace() const { return m_properties.free_space; }
//    int space() const { return m_vehicleDescriptor.space; }

//    void bindNpc(Npc*);

//    bool isObjectVisible(SpaceObject*) const;

//    WeaponComplex& weaponComplex() { return m_weaponComplex; }   // !!!
//    const WeaponComplex& weaponComplex() const { return m_weaponComplex; }
//    DriveComplex& driveComplex()   { return m_driveComplex; }
//    ProtectionComplex& protectorComplex() { return m_protectorComplex; }

//    ItemSlot* const radarSlot()     const { return m_radarSlot; }
//    ItemSlot* const scanerSlot()    const { return m_scanerSlot; }
//#ifdef USE_EXTRA_EQUIPMENT
//    ItemSlot* const energizerSlot() const { return m_energizerSlot; }
//    ItemSlot* const freezerSlot()   const { return m_freezerSlot; }
//#endif // USE_EXTRA_EQUIPMENT
//    ItemSlot* const grappleSlot()   const { return m_grappleSlot; }
//    ItemSlot* const droidSlot()     const { return m_droidSlot; }

//    Npc* const npc() const { return m_npc; }

//    ItemSlot* const freeCargoSlot();
//    GoodsPack* goodsPack() const;

//    void UpdateSpecialAction();
//    virtual void UpdateInSpace(int, bool) = 0;

//    virtual void remeberAgressor(Vehicle*);
//    void hit(int) override;

//    virtual void _postDeathUniqueEvent(bool);

//    void CheckNeedsInStatic();
//    void ResolveNeedsInKosmoportInStatic();
//    void UpdateAllFunctionalItemsInStatic();

//    bool dropItemToSpace(const entity::Type&);

//protected:
//    void _increaseMass(int);
//    void _decreaseMass(int);
//    void _updatePropEnergy();
//    void _updatePropFreeze();
//    void _updatePropSpeed();
//    void _updatePropFire();
//    void _updatePropRadar();
//    void _updatePropJump();
//    void _updatePropProtection();
//    void _updatePropRepair();
//    void _updatePropScan();
//    void _updatePropGrab();
//    void _updateArtefactInfluence();
//    friend class ItemSlot;
//public:

//    void HyperJumpEvent(Starsystem*);
//    void DockingEvent();
//    void LaunchingEvent();

//    void UpdateSpecialEffect();
//    void UpdateLockedItems();

//    //        virtual void RenderStuffWhenFocusedInSpace(const jeti::Renderer&) override final;
//    //        virtual void RenderInfoInSpace(const jeti::Renderer&, const glm::vec2&, float) override final;
//    //        void RenderInfo(const glm::vec2&, int, int);

//    //        void RenderRadarRange();
//    //        void RenderGrappleRange();

//    bool isAbleToJumpTo(Starsystem*) const;

//    bool isArmorFull() const;
//    int armorMiss() const;
//    void increaseArmor(int);
//    void repairKorpus(int);

//    bool isFuelFull() const;
//    int fuelMiss() const;

//    void lockRandomItem(int);

//    bool tryConsumeEnergy(int);
//    bool tryGenerateEnergy(int);

//    STATUS CheckGrabStatus() const;

//    float adjustDissipateFilter() const;
//    int criticalDamage() const;

//protected:
//    std::vector<ItemSlot*> m_slots;

//    ItemSlot* const _functionalSlot(const entity::Type&) const;
//    ItemSlot* const _freeArtefactSlot() const;
//    ItemSlot* const _cargoSlotWithGoods(entity::Type);

//    bool _installItem(item::Base*);
//    bool _installEquipment(item::Base*);
//#ifdef USE_MODULES
//    bool installModule(item::Base*);
//#endif // USE_MODULES
//#ifdef USE_ARTEFACTS
//    bool installArtefact(item::Base*);
//#endif // USE_ARTEFACTS
//    bool _installGoodsPack(item::Base*);

//    //        virtual void UpdateInfo() = 0;

//    //        void RenderGrabTrail(const jeti::Renderer&) const;
//    //        void RenderKorpus(const jeti::Renderer&);
//    //        void RenderTurrels() const;
//    //        void RenderDriveEffect(float scale, float parent_d_alpha = 0.0) const;
//    //        void RenderShieldEffect(const jeti::Renderer&, float parent_d_alpha = 0.0) const;

//    void UpdateGrappleMicroProgram_inDynamic();

//    virtual void putChildrenToGarbage() const override;

//    UnresolvedDataVehicle data_unresolved_Vehicle;

//    void SaveData(boost::property_tree::ptree&, const std::string&) const;
//    void LoadData(const boost::property_tree::ptree&);
//    void ResolveData();

//private:
//    bool m_godMode;
//    VEHICLE_SPECIAL_ACTION_TYPE m_specialActionId;

//    Npc* m_npc = nullptr;

//    VehicleSlot* m_parentVehicleSlot = nullptr;

//    Land* m_Land = nullptr;

//    ItemSlot* m_radarSlot = nullptr;
//    ItemSlot* m_scanerSlot = nullptr;
//#ifdef USE_EXTRA_EQUIPMENT
//    ItemSlot* m_energizerSlot = nullptr;
//    ItemSlot* m_freezerSlot = nullptr;
//#endif // USE_EXTRA_EQUIPMENT
//    ItemSlot* m_grappleSlot = nullptr;
//    ItemSlot* m_droidSlot = nullptr;


//    std::vector<ItemSlot*> m_equipmentSlots;
//    std::vector<ItemSlot*> m_artefactSlots;
//    std::vector<ItemSlot*> m_cargoSlots;

//    WeaponComplex     m_weaponComplex;
//    DriveComplex      m_driveComplex;
//    ProtectionComplex m_protectorComplex;

//    VehiclePropetries m_properties;
//    VehicleNeeds m_needs;
//    descriptor::Vehicle m_vehicleDescriptor;

//    [[deprecated("use predetermentistic way")]]
////    void __dropRandomItemToSpace();
//    bool __mergeIdenticalGoods(item::Base*);

//    Container* __wrapItemToContainer(item::Base*);
//    bool _checkInstallEquipment(const core::Id&);
//    ItemSlot* const _freeFunctionalSlot(const core::Id&) const;

//    friend class GuiVehicle;
//    friend class GuiVehicle2;
//};

std::string getVehicleSpecialActionStr(VEHICLE_SPECIAL_ACTION_TYPE);

