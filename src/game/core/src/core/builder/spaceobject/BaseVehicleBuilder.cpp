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

#include "BaseVehicleBuilder.hpp"
#include <core/spaceobject/Vehicle.hpp>

#include <core/part/WeaponComplex.hpp>

#include <core/manager/DescriptorManager.hpp>

#include <core/item/equipment/ALL>

#ifdef USE_MODULES
#include <core/item/modules/ALL>
#endif // USE_MODULES

#include <core/item/other/Bomb.hpp>

#ifdef USE_ARTEFACTS
#include <core/item/artefacts/ALL>
#endif // USE_ARTEFACTS

#include <core/builder/item/equipment/ALL>
#ifdef USE_MODULES
#include <core/builder/item/module/ALL>
#endif // USE_MODULES

#ifdef USE_ARTEFACTS
#include <core/builder/item/artefact/ALL>
#endif // USE_ARTEFACTS
#include <core/builder/item/other/ALL>

#include <common/Global.hpp>
#include <core/manager/EntityManager.hpp>

#include <math/rand.hpp>
#include <meti/RandUtils.hpp>

//#include <jeti/particlesystem/DriveEffect.hpp>

#include <core/slot/ItemSlot.hpp>

#include <core/type/TechLevelType.hpp>

#include <core/generator/DescriptorGenerator.hpp>


namespace GovermentBuilder {

void
VehicleBuilder::equip(core::control::Vehicle* vehicle)
{
    vehicle->manage(GovermentBuilder::item::Drive::gen());
    vehicle->manage(GovermentBuilder::item::Bak::gen());
    vehicle->manage(GovermentBuilder::item::Protector::gen());
    vehicle->manage(GovermentBuilder::item::Scaner::gen());
    vehicle->manage(GovermentBuilder::item::Radar::gen());
    vehicle->manage(GovermentBuilder::item::Grapple::gen());
    vehicle->manage(GovermentBuilder::item::Lazer::gen());
    vehicle->manage(GovermentBuilder::item::Rocket::gen());
    vehicle->load(GovermentBuilder::item::Rocket::gen());
}

//void BaseVehicle::_createSlots(Vehicle* vehicle)
//{
//    assert(false);
////    // WEAPON SLOTS
////    unsigned int slot_weapon_num = vehicle->vehicleDescriptor().slot_weapon_num;
////    for (unsigned int i=0; i<slot_weapon_num; i++) {
////        ItemSlot* weapon_slot = getNewItemSlot(entity::Type::WEAPON_SLOT);
////        weapon_slot->setSubSubTypeId(SLOT_WEAPON_TYPES[i]);
////        vehicle->addItemSlot(weapon_slot);
////    }
        
////    if (vehicle->vehicleDescriptor().slot_radar_num) {
////        ItemSlot* radar_slot = getNewItemSlot(entity::Type::RADAR_SLOT);
////        vehicle->addItemSlot(radar_slot);
////    }
            
////    if (vehicle->vehicleDescriptor().slot_scaner_num) {
////        ItemSlot* scaner_slot = getNewItemSlot(entity::Type::SCANER_SLOT);
////        vehicle->addItemSlot(scaner_slot);
////    }

////    if (vehicle->vehicleDescriptor().slot_energizer_num) {
////        ItemSlot* energizer_slot = getNewItemSlot(entity::Type::ENERGIZER_SLOT);
////        vehicle->addItemSlot(energizer_slot);
////    }
    
////    if (vehicle->vehicleDescriptor().slot_grapple_num) {
////        ItemSlot* grapple_slot = getNewItemSlot(entity::Type::GRAPPLE_SLOT);
////        vehicle->addItemSlot(grapple_slot);
////    }
    
////    if (vehicle->vehicleDescriptor().slot_droid_num) {
////        ItemSlot* droid_slot = getNewItemSlot(entity::Type::DROID_SLOT);
////        vehicle->addItemSlot(droid_slot);
////    }
    
////    if (vehicle->vehicleDescriptor().slot_freezer_num) {
////        //ItemSlot* freezer_slot = GetNewItemSlot(entity::Type::FREEZER_SLOT);
////        //vehicle->AddItemSlot(freezer_slot);
////    }
    
////    if (vehicle->vehicleDescriptor().slot_protector_num) {
////        ItemSlot* protector_slot = getNewItemSlot(entity::Type::PROTECTOR_SLOT);
////        vehicle->addItemSlot(protector_slot);
////    }
    
////    if (vehicle->vehicleDescriptor().slot_drive_num) {
////        ItemSlot* drive_slot = getNewItemSlot(entity::Type::DRIVE_SLOT);
////        vehicle->addItemSlot(drive_slot);
////    }
    
////    if (vehicle->vehicleDescriptor().slot_bak_num) {
////        ItemSlot* bak_slot = getNewItemSlot(entity::Type::BAK_SLOT);
////        vehicle->addItemSlot(bak_slot);
////    }
    
////    //////////// ARTEFACT SLOT /////////////////////////
////    int artefact_num = vehicle->vehicleDescriptor().slot_artefact_num;
////    for (int i=0; i<artefact_num; i++) {
////        ItemSlot* artefact_slot = getNewItemSlot(entity::Type::ARTEFACT_SLOT);
////        artefact_slot->setSubSubTypeId(SLOT_ARTEFACT_TYPES[i]);
////        vehicle->addItemSlot(artefact_slot);
////    }

////    //////// OTSEC SLOT ////////////////////////////////
////    int otsec_num = vehicle->vehicleDescriptor().slot_otsec_num;
////    for (int i=0; i<otsec_num; i++) {
////        ItemSlot* otsec_slot = getNewItemSlot(entity::Type::CARGO_SLOT);
////        otsec_slot->setSubSubTypeId(SLOT_CARGO_TYPES[i]);
////        vehicle->addItemSlot(otsec_slot);
////    }

////    // GATE SLOT
////    {
////        ItemSlot* gate_slot = getNewItemSlot(entity::Type::GATE_SLOT);
////        vehicle->addItemSlot(gate_slot);
////    }
//}

void VehicleBuilder::equip(Vehicle* vehicle, descriptor::Vehicle* descr)
{
//    entity::Type type = (entity::Type)descriptor.type();
//    switch(type) {
//    case entity::Type::BAK_EQUIPMENT:
//    {
//        BakEquipment* bak_equipment = core::global::get().bakBuilder().create(descriptor);
//        if (vehicle->AddAndManageItem(bak_equipment) == false) {
//           manager::EntityManager::get().addToGarbage(bak_equipment);
//        }
//        break;
//    }
//    case entity::Type::DRIVE_EQUIPMENT:
//    {
//        DriveEquipment* bak_equipment = core::global::get().driveBuilder().create(descriptor);
//        if (vehicle->AddAndManageItem(drive_equipment) == false) {
//           manager::EntityManager::get().addToGarbage(drive_equipment);
//        }
//        break;
//    }
//    case entity::Type::DROID_EQUIPMENT:
//    {
//        DriveEquipment* bak_equipment = core::global::get().driveBuilder().create(descriptor);
//        if (vehicle->AddAndManageItem(drive_equipment) == false) {
//           manager::EntityManager::get().addToGarbage(drive_equipment);
//        }
//        break;
//    }
//    }
}

void VehicleBuilder::equip(Vehicle* vehicle, tech::Type tech_level)
{
    assert(false);
//    unsigned int weapons_num = meti::getRandInt(vehicle->vehicleDescriptor().slot_weapon_num/2, vehicle->vehicleDescriptor().slot_weapon_num);
//    for (unsigned int i=0; i<weapons_num; i++) {
//        if (vehicle->isSlotFree(entity::Type::WEAPON_SLOT)) {
//            bool rand = 0; //getRandBool();
//            if (rand) {
//                vehicle->manage(core::global::get().rocketBuilder().gen(tech_level) );
//            } else {
//                vehicle->manage(core::global::get().lazerBuilder().gen(tech_level) );
//            }
//        }
//    }
    
//    if (vehicle->isSlotFree(entity::Type::RADAR_SLOT)) {
//        vehicle->manage(core::global::get().radarBuilder().gen());
//    }
    
//    if (vehicle->isSlotFree(entity::Type::DRIVE_SLOT)) {
//        vehicle->manage(core::global::get().driveBuilder().gen());
//    }
    
//    if (vehicle->isSlotFree(entity::Type::BAK_SLOT)) {
//        vehicle->manage(core::global::get().bakBuilder().gen());
//    }

//#ifdef USE_EXTRA_EQUIPMENT
//    if (vehicle->isSlotFree(entity::Type::ENERGIZER_SLOT)) {
//        vehicle->manage(core::global::get().energizerBuilder().gen());
//    }
    
//    if (vehicle->isSlotFree(entity::Type::FREEZER_SLOT)) {
//        vehicle->manage(core::global::get().freezerBuilder().gen());
//    }
//#endif

//    if (vehicle->isSlotFree(entity::Type::PROTECTOR_SLOT)) {
//        vehicle->manage(core::global::get().protectorBuilder().gen());
//    }
        
//    if (vehicle->isSlotFree(entity::Type::DROID_SLOT)) {
//        vehicle->manage(core::global::get().droidBuilder().gen());
//    }
    
//    if (vehicle->isSlotFree(entity::Type::SCANER_SLOT)) {
//        vehicle->manage(core::global::get().scanerBuilder().gen());
//    }
    
//    if (vehicle->isSlotFree(entity::Type::GRAPPLE_SLOT)) {
//        vehicle->manage(core::global::get().grappleBuilder().gen());
//    }
}

#ifdef USE_MODULES
void BaseVehicleBuilder::EquipModules(Vehicle* vehicle, tech::Type tech_level)
{
    for (unsigned int i=0; i<4; i++) 
    {     
        if (vehicle->GetEmptyCargoSlot() == nullptr) {
            return;
        }
            
        entity::Type module_group = meti::getRand(MODULE_TYPES);
        switch(module_group) {
            case entity::Type::LAZER_MODULE:       { vehicle->AddItemToCargoSlot(core::global::get().lazerModuleBuilder().create()); break; }
            case entity::Type::ROCKET_MODULE:      { vehicle->AddItemToCargoSlot(core::global::get().rocketModuleBuilder().create()); break; }
            case entity::Type::DRIVE_MODULE:       { vehicle->AddItemToCargoSlot(core::global::get().driveModuleBuilder().create()); break; }
            case entity::Type::RADAR_MODULE:       { vehicle->AddItemToCargoSlot(core::global::get().radarModuleBuilder().create()); break; }
            case entity::Type::BAK_MODULE:         { vehicle->AddItemToCargoSlot(core::global::get().bakModuleBuilder().create()); break; }
            //case entity::Type::ENERGIZER_MODULE: { vehicle->AddItemToCargoSlot(core::global::get().energizerModuleBuilder().create()); break; }
            case entity::Type::PROTECTOR_MODULE:   { vehicle->AddItemToCargoSlot(core::global::get().protectorModuleBuilder().create()); break; }
            case entity::Type::DROID_MODULE:       { vehicle->AddItemToCargoSlot(core::global::get().droidModuleBuilder().create()); break; }
            //case entity::Type::FREEZER_MODULE:   { vehicle->AddItemToCargoSlot(core::global::get().freezerModuleBuilder().create()); break; }
            case entity::Type::GRAPPLE_MODULE:     { vehicle->AddItemToCargoSlot(core::global::get().grappleModuleBuilder().create()); break; }
            case entity::Type::SCANER_MODULE:      { vehicle->AddItemToCargoSlot(core::global::get().scanerModuleBuilder().create()); break; }
        }
    }
}
#endif // USE_MODULES

#ifdef USE_ARTEFACTS
void BaseVehicleBuilder::EquipArtefacts(Vehicle* vehicle, tech::Type tech_level)
{
    for (unsigned int i=0; i<2; i++) {
        if (vehicle->GetEmptyCargoSlot() == nullptr) {
            return;
        }                    
        vehicle->manage(core::global::get().gravityArtefactBuilder().create());
    }   

    for (unsigned int i=0; i<2; i++) {
        if (vehicle->GetEmptyCargoSlot() == nullptr) {
            return;
        }            
        vehicle->manage(core::global::get().protectorArtefactBuilder().create());
    }  
}
#endif // USE_ARTEFACTS

void VehicleBuilder::equipBomb(Vehicle* vehicle, tech::Type tech_level)
{
    for (unsigned int i=0; i<2; i++) {
        //vehicle->AddItemToCargoSlot(core::global::get().bombBuilder().create());
    }    
}

} // namespace builder



