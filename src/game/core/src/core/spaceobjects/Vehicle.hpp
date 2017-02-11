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

#include <core/spaceobjects/SpaceObject.hpp>

#include <core/parts/WeaponComplex.hpp>
#include <core/parts/DriveComplex.hpp>
#include <core/parts/ProtectionComplex.hpp>

#include <core/descriptor/VehicleDescriptor.hpp>
#include <core/struct/VehiclePropetries.hpp>
#include <core/struct/VehicleNeeds.hpp>

#include <core/types/StatusTypes.hpp>

class VehicleSlot;
class Land; 
class GoodsPack;

namespace model {
class Container;
class Starsystem;
} // namespace model

namespace control {
class Container;
class Npc;

namespace item {
class Base;
} // namespace item

} //namespace control

class BaseEquipment;
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
    NONE_ID=0, INITIATE_DOCKING_ID, INITIATE_LAUNCHING_ID, INITIATE_JUMPIN_ID, INITIATE_JUMPOUT_ID
};



namespace model {

class Vehicle : public model::SpaceObject {
public:
    Vehicle()=default;
    ~Vehicle() = default;
    Vehicle(const std::string& data);
    std::string data() const;

    int_t npc() const { return m_npc; }
    int_t dock() const { return m_dock; }
    [[warning("do we need this? using dock will be sufficient probably")]]
    int_t land() const { return m_land; }

//    int_t radarSlot() const { return m_radar_slot; }
//    int_t scanerSlot() const { return m_scaner_slot; }

//#ifdef USE_EXTRA_EQUIPMENT
//    int_t energizerSlot() const { return m_energizer_slot; }
//    int_t freezerSlot() const { return m_freezer_slot; }
//#endif // USE_EXTRA_EQUIPMENT
//    int_t grappleSlot() const { return m_grapple_slot; }
//    int_t droidSlot() const { return m_droid_slot; }

    WeaponComplex& weaponComplex() { return m_weapon_complex; }
    DriveComplex& driveComplex() { return m_drive_complex; }
    ProtectionComplex& protectorComplex() { return m_protector_complex; }

    VehiclePropetries& properties() { return m_properties; }
    VehicleNeeds& needs() { return m_needs; }

    [[warning("move out to control::")]]
    int_t descriptor() { return m_descriptor; }

private:
    int_t m_npc = NONE;
    int_t m_dock = NONE;
    int_t m_land = NONE;

//    int_t m_radar_slot = NONE;
//    int_t m_scaner_slot = NONE;
//#ifdef USE_EXTRA_EQUIPMENT
//    int_t m_energizer_slot = NONE;
//    int_t m_freezer_slot = NONE;
//#endif // USE_EXTRA_EQUIPMENT
//    int_t m_grapple_slot = NONE;
//    int_t m_droid_slot = NONE;

//    std::vector<int_t> m_equipment_slots;
//    std::vector<int_t> m_artefact_slots;
//    std::vector<int_t> m_cargo_slots;

    WeaponComplex     m_weapon_complex;
    DriveComplex      m_drive_complex;
    ProtectionComplex m_protector_complex;

    VehiclePropetries m_properties;
    VehicleNeeds m_needs;
    int_t m_descriptor;

private:
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version) {
        ar & boost::serialization::base_object<SpaceObject>(*this);
        ar & m_npc;
        ar & m_dock;
        ar & m_land;
//        ar & m_weapon_complex;
//        ar & m_drive_complex;
//        ar & m_protector_complex;
//        ar & m_properties;
//        ar & m_needs;
        ar & m_descriptor;
    }
};

} // namespace model


namespace control {

class Vehicle : public control::SpaceObject
{
public:
    Vehicle(model::Vehicle*);
    virtual ~Vehicle();

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

    void setKorpusData(const descriptor::Vehicle&);

    bool godMode() const { return m_godMode; }
    Land* const land() const { return m_Land; }
    VEHICLE_SPECIAL_ACTION_TYPE GetSpecialActionId() const { return m_specialActionId; }

    VehicleSlot* const parentVehicleSlot() const { return m_parentVehicleSlot; }

    const VehiclePropetries& properties() const { return model()->properties(); }
    const VehicleNeeds& needs() const { return model()->needs(); }
    const descriptor::Vehicle& descriptor() const { return m_descriptor; }
    [[warning("remove this, added for compatibility")]]
    const descriptor::Vehicle& vehicleDescriptor() const { return m_descriptor; }

    virtual int givenExpirience() const override final;
    bool isSlotTypePresent(const entity::type&) const;

    void addItemSlot(ItemSlot*);

    [[deprecated("ship swap items in different logic")]]
    bool grabItemsFromVehicle(Vehicle*);

    bool addItemToCargoSlot(item::Base*);
    bool manage(item::Base*);

    bool isSlotFree(const place::type&) const;
    bool checkManage(const core::Id&);

    void manageItemsInCargo();
    [[deprecated("move to ext")]]
    void sellItemsInCargo();

    [[deprecated("move to ext")]]
    bool sellItem(item::Base*);
    [[deprecated("move to ext")]]
    bool buyItem(item::Base*);

    bool unpackContainerItemToCargoSlot(control::Container*);

    int freeSpace() const { return model()->properties().free_space; }
    int space() const { return descriptor().space(); }

    void bindNpc(control::Npc*);

    bool isObjectVisible(SpaceObject*) const;

    [[warning("incapsulate this")]]
    WeaponComplex& weaponComplex() { return model()->weaponComplex(); }   // !!!
    [[warning("incapsulate this")]]
    const WeaponComplex& weaponComplex() const { return model()->weaponComplex(); }
    [[warning("incapsulate this")]]
    DriveComplex& driveComplex()   { return model()->driveComplex(); }
    [[warning("incapsulate this")]]
    ProtectionComplex& protectorComplex() { return model()->protectorComplex(); }

    ItemSlot* const radarSlot()     const { return m_radarSlot; }
    ItemSlot* const scanerSlot()    const { return m_scanerSlot; }
#ifdef USE_EXTRA_EQUIPMENT
    ItemSlot* const energizerSlot() const { return m_energizerSlot; }
    ItemSlot* const freezerSlot()   const { return m_freezerSlot; }
#endif // USE_EXTRA_EQUIPMENT
    ItemSlot* const grappleSlot()   const { return m_grappleSlot; }
    ItemSlot* const droidSlot()     const { return m_droidSlot; }

    control::Npc* const npc() const { return m_npc; }

    ItemSlot* const freeCargoSlot();
    GoodsPack* goodsPack() const;

    void UpdateSpecialAction();
    virtual void UpdateInSpace(int, bool) = 0;

    virtual void remeberAgressor(Vehicle*);
    void hit(int) override;

    virtual void _postDeathUniqueEvent(bool);

    void CheckNeedsInStatic();
    void ResolveNeedsInKosmoportInStatic();
    void UpdateAllFunctionalItemsInStatic();

    bool dropItemToSpace(const entity::type&);

protected:
    void _increaseMass(int);
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

    void HyperJumpEvent(model::Starsystem*);
    void DockingEvent();
    void LaunchingEvent();

    void UpdateSpecialEffect();
    void UpdateLockedItems();

    //        virtual void RenderStuffWhenFocusedInSpace(const jeti::Renderer&) override final;
    //        virtual void RenderInfoInSpace(const jeti::Renderer&, const glm::vec2&, float) override final;
    //        void RenderInfo(const glm::vec2&, int, int);

    //        void RenderRadarRange();
    //        void RenderGrappleRange();

    bool isAbleToJumpTo(model::Starsystem*) const;

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

protected:
    model::Vehicle* m_model_vehicle = nullptr;
    model::Vehicle* model() const { return m_model_vehicle; }

    [[warning("make it private")]]
    std::vector<ItemSlot*> m_slots;

    ItemSlot* const _functionalSlot(const entity::type&) const;
    ItemSlot* const _freeArtefactSlot() const;
    ItemSlot* const _cargoSlotWithGoods(place::type);

    bool _installItem(control::item::Base*);
    bool _installEquipment(control::item::Base*);
#ifdef USE_MODULES
    bool installModule(control::item::Base*);
#endif // USE_MODULES
#ifdef USE_ARTEFACTS
    bool installArtefact(item::Base*);
#endif // USE_ARTEFACTS
    bool _installGoodsPack(control::item::Base*);

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
    VEHICLE_SPECIAL_ACTION_TYPE m_specialActionId = VEHICLE_SPECIAL_ACTION_TYPE::NONE_ID;

    control::Npc* m_npc = nullptr;

    VehicleSlot* m_parentVehicleSlot = nullptr;

    Land* m_Land = nullptr;

    ItemSlot* m_radarSlot = nullptr;
    ItemSlot* m_scanerSlot = nullptr;
#ifdef USE_EXTRA_EQUIPMENT
    ItemSlot* m_energizerSlot = nullptr;
    ItemSlot* m_freezerSlot = nullptr;
#endif // USE_EXTRA_EQUIPMENT
    ItemSlot* m_grappleSlot = nullptr;
    ItemSlot* m_droidSlot = nullptr;

    std::vector<ItemSlot*> m_equipmentSlots;
    std::vector<ItemSlot*> m_artefactSlots;
    std::vector<ItemSlot*> m_cargoSlots;

    [[deprecated("use predetermentistic way")]]
//    void __dropRandomItemToSpace();
    bool __mergeIdenticalGoods(item::Base*);

    model::Container* __wrapItemToContainer(item::Base*);
    bool _checkInstallEquipment(const core::Id&);
    ItemSlot* const _freeFunctionalSlot(const core::Id&) const;

    descriptor::Vehicle m_descriptor;
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

//    void setKorpusData(const descriptor::Vehicle&);

//    bool godMode() const { return m_godMode; }
//    Land* const land() const { return m_Land; }
//    VEHICLE_SPECIAL_ACTION_TYPE GetSpecialActionId() const { return m_specialActionId; }

//    VehicleSlot* const parentVehicleSlot() const { return m_parentVehicleSlot; }

//    const VehiclePropetries& properties() const { return m_properties; }
//    const VehicleNeeds& needs() const { return m_needs; }
//    const descriptor::Vehicle& vehicleDescriptor() const { return m_vehicleDescriptor; }

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

