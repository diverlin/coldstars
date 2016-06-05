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
#include "../../spaceobjects/Vehicle.hpp"

#include "../../parts/WeaponComplex.hpp"

#include <descriptors/DescriptorManager.hpp>

#include <item/equipment/ALL>

#ifdef USE_MODULES
#include <item/modules/ALL>
#endif

#include <item/others/Bomb.hpp>

#ifdef USE_ARTEFACTS
#include <item/artefacts/ALL>
#endif

#include <builder/item/equipment/ALL>
#include <builder/item/modules/ALL>
#include <builder/item/artefacts//ALL>
#include <builder/item/other/ALL>

#include <common/Global.hpp>
#include <managers/EntityManager.hpp>

#include <builder/slots/ItemSlotBuilder.hpp>

#include <math/rand.hpp>
#include <meti/RandUtils.hpp>

//#include <jeti/particlesystem/DriveEffect.hpp>

#include <slots/ItemSlot.hpp>

#include <types/TechLevelTypes.hpp>

#include <descriptors/DescriptorGenerator.hpp>

BaseVehicleBuilder::BaseVehicleBuilder()
{}
     
void BaseVehicleBuilder::CreateItemSlots(Vehicle* vehicle) const
{     
    // WEAPON SLOTS
    unsigned int slot_weapon_num = vehicle->GetVehicleDescriptor().slot_weapon_num;
    for (unsigned int i=0; i<slot_weapon_num; i++)
    {
        ItemSlot* weapon_slot = GetNewItemSlot(TYPE::ENTITY::WEAPON_SLOT_ID);  
        weapon_slot->setSubSubTypeId(SLOT_WEAPON_TYPES[i]);   
        vehicle->addItemSlot(weapon_slot);
    }
        
    if (vehicle->GetVehicleDescriptor().slot_radar_num)
    {
        ItemSlot* radar_slot = GetNewItemSlot(TYPE::ENTITY::RADAR_SLOT_ID);
        vehicle->addItemSlot(radar_slot);
    }
            
    if (vehicle->GetVehicleDescriptor().slot_scaner_num)
    {
        ItemSlot* scaner_slot = GetNewItemSlot(TYPE::ENTITY::SCANER_SLOT_ID); 
        vehicle->addItemSlot(scaner_slot);
    }

    if (vehicle->GetVehicleDescriptor().slot_energizer_num)
    {
        ItemSlot* energizer_slot = GetNewItemSlot(TYPE::ENTITY::ENERGIZER_SLOT_ID); 
        vehicle->addItemSlot(energizer_slot);
    }
    
    if (vehicle->GetVehicleDescriptor().slot_grapple_num)
    {
        ItemSlot* grapple_slot = GetNewItemSlot(TYPE::ENTITY::GRAPPLE_SLOT_ID);
        vehicle->addItemSlot(grapple_slot); 
    }
    
    if (vehicle->GetVehicleDescriptor().slot_droid_num)
    {
        ItemSlot* droid_slot = GetNewItemSlot(TYPE::ENTITY::DROID_SLOT_ID);  
        vehicle->addItemSlot(droid_slot); 
    }
    
    if (vehicle->GetVehicleDescriptor().slot_freezer_num)
    {
        //ItemSlot* freezer_slot = GetNewItemSlot(TYPE::ENTITY::FREEZER_SLOT_ID);
        //vehicle->AddItemSlot(freezer_slot);           
    }
    
    if (vehicle->GetVehicleDescriptor().slot_protector_num)
{
        ItemSlot* protector_slot = GetNewItemSlot(TYPE::ENTITY::PROTECTOR_SLOT_ID);  
        vehicle->addItemSlot(protector_slot);         
    }
    
    if (vehicle->GetVehicleDescriptor().slot_drive_num)
    {
        ItemSlot* drive_slot = GetNewItemSlot(TYPE::ENTITY::DRIVE_SLOT_ID); 
        vehicle->addItemSlot(drive_slot);
    }
    
    if (vehicle->GetVehicleDescriptor().slot_bak_num)
    {
        ItemSlot* bak_slot = GetNewItemSlot(TYPE::ENTITY::BAK_SLOT_ID);  
        vehicle->addItemSlot(bak_slot);
    }
    
    //////////// ARTEFACT SLOT /////////////////////////
    int artefact_num = vehicle->GetVehicleDescriptor().slot_artefact_num;
    for (int i=0; i<artefact_num; i++)
    {
        ItemSlot* artefact_slot = GetNewItemSlot(TYPE::ENTITY::ARTEFACT_SLOT_ID);
        artefact_slot->setSubSubTypeId(SLOT_ARTEFACT_TYPES[i]);  
        vehicle->addItemSlot(artefact_slot);         
    } 

    //////// OTSEC SLOT ////////////////////////////////
    int otsec_num = vehicle->GetVehicleDescriptor().slot_otsec_num;
    for (int i=0; i<otsec_num; i++)
    {
        ItemSlot* otsec_slot = GetNewItemSlot(TYPE::ENTITY::CARGO_SLOT_ID); 
        otsec_slot->setSubSubTypeId(SLOT_CARGO_TYPES[i]);   
        vehicle->addItemSlot(otsec_slot);         
    }

    //GATE SLOT
    {
        ItemSlot* gate_slot = GetNewItemSlotWithoutSaveAbility(TYPE::ENTITY::GATE_SLOT_ID); 
        vehicle->addItemSlot(gate_slot);
    }
}

void BaseVehicleBuilder::equip(Vehicle* vehicle, const descriptor::Base& descriptor) const
{
//    TYPE::ENTITY type = (TYPE::ENTITY)descriptor.type();
//    switch(type) {
//    case TYPE::ENTITY::BAK_EQUIPMENT_ID:
//    {
//        BakEquipment* bak_equipment = global::get().bakBuilder().create(descriptor);
//        if (vehicle->AddAndManageItem(bak_equipment) == false) {
//            global::get().entityManager().addToGarbage(bak_equipment);
//        }
//        break;
//    }
//    case TYPE::ENTITY::DRIVE_EQUIPMENT_ID:
//    {
//        DriveEquipment* bak_equipment = global::get().driveBuilder().create(descriptor);
//        if (vehicle->AddAndManageItem(drive_equipment) == false) {
//            global::get().entityManager().addToGarbage(drive_equipment);
//        }
//        break;
//    }
//    case TYPE::ENTITY::DROID_EQUIPMENT_ID:
//    {
//        DriveEquipment* bak_equipment = global::get().driveBuilder().create(descriptor);
//        if (vehicle->AddAndManageItem(drive_equipment) == false) {
//            global::get().entityManager().addToGarbage(drive_equipment);
//        }
//        break;
//    }
//    }
}

void BaseVehicleBuilder::equip(Vehicle* vehicle, TYPE::TECH tech_level) const
{
    unsigned int weapons_num = meti::getRandInt(vehicle->GetVehicleDescriptor().slot_weapon_num/2, vehicle->GetVehicleDescriptor().slot_weapon_num);
    for (unsigned int i=0; i<weapons_num; i++)
    {
        bool rand = 0; //getRandBool();
        if (rand)
        {
            item::equipment::Rocket* rocket_equipment = global::get().rocketBuilder().getNew(tech_level);
            if (vehicle->manage(rocket_equipment) == false) {
                global::get().entityManager().addToGarbage(rocket_equipment);
            }
        }
        else
        {
            item::equipment::Lazer* lazer_equipment = global::get().lazerBuilder().getNew(tech_level);
            if (vehicle->manage(lazer_equipment) == false) {
                global::get().entityManager().addToGarbage(lazer_equipment);
            }
        }
    }   
    
    if (vehicle->isSlotExists(TYPE::ENTITY::RADAR_SLOT_ID)) {
        auto descr = global::get().descriptors().getRand(descriptor::Type::RADAR);
        item::equipment::Radar* radar_equipment = global::get().radarBuilder().getNew(descr);
        if (vehicle->manage(radar_equipment) == false) {
            global::get().entityManager().addToGarbage(radar_equipment);
        }
    }
    
    if (vehicle->isSlotExists(TYPE::ENTITY::DRIVE_SLOT_ID)) {
        auto descr = global::get().descriptors().getRand(descriptor::Type::DRIVE);
        item::equipment::Drive* drive_equipment = global::get().driveBuilder().getNew(descr);
        if (vehicle->manage(drive_equipment) == false) {
            global::get().entityManager().addToGarbage(drive_equipment);
        }
    }
    
    if (vehicle->isSlotExists(TYPE::ENTITY::BAK_SLOT_ID)) {
        auto descr = global::get().descriptors().getRand(descriptor::Type::BAK);
        item::equipment::Bak* bak_equipment = global::get().bakBuilder().getNew(descr);
        if (vehicle->manage(bak_equipment) == false) {
            global::get().entityManager().addToGarbage(bak_equipment);
        }
    }

#ifdef USE_EXTRA_EQUIPMENT
    if (vehicle->isSlotExists(TYPE::ENTITY::ENERGIZER_SLOT_ID) == true)
    {
        item::equipment::EnergizerEquipment* energizer_equipment = global::get().energizerBuilder().create(tech_level);
        if (vehicle->manage(energizer_equipment) == false) {
            global::get().entityManager().addToGarbage(energizer_equipment);
        }     
    }
    
    if (vehicle->isSlotExists(TYPE::ENTITY::FREEZER_SLOT_ID) == true)
    {
        item::equipment::FreezerEquipment* freezer_equipment = global::get().freezerBuilder().create(tech_level);
        if (vehicle->manage(freezer_equipment) == false) {
            global::get().entityManager().addToGarbage(freezer_equipment);
        }
    }
#endif

    if (vehicle->isSlotExists(TYPE::ENTITY::PROTECTOR_SLOT_ID)) {
        auto descr = global::get().descriptors().getRand(descriptor::Type::PROTECTOR);
        item::equipment::Protector* protector_equipment = global::get().protectorBuilder().getNew(descr);
        if (vehicle->manage(protector_equipment) == false) {
            global::get().entityManager().addToGarbage(protector_equipment);
        }  
    }
        
    if (vehicle->isSlotExists(TYPE::ENTITY::DROID_SLOT_ID)) {
        auto descr = global::get().descriptors().getRand(descriptor::Type::DROID);
        item::equipment::Droid* droid_equipment = global::get().droidBuilder().getNew(descr);
        if (vehicle->manage(droid_equipment) == false) {
            global::get().entityManager().addToGarbage(droid_equipment);
        }  
    }
    
    if (vehicle->isSlotExists(TYPE::ENTITY::SCANER_SLOT_ID)) {
        auto descr = global::get().descriptors().getRand(descriptor::Type::SCANER);
        item::equipment::Scaner* scaner_equipment = global::get().scanerBuilder().getNew(descr);
        if (vehicle->manage(scaner_equipment) == false) {
            global::get().entityManager().addToGarbage(scaner_equipment);
        }  
    }
    
    if (vehicle->isSlotExists(TYPE::ENTITY::GRAPPLE_SLOT_ID)) {
        auto descr = global::get().descriptors().getRand(descriptor::Type::GRAPPLE);
        item::equipment::Grapple* grapple_equipment = global::get().grappleBuilder().getNew(descr);
        if (vehicle->manage(grapple_equipment) == false) {
            global::get().entityManager().addToGarbage(grapple_equipment);
        }
    }
}

#ifdef USE_MODULES
void BaseVehicleBuilder::EquipModules(Vehicle* vehicle, TYPE::TECH tech_level) const
{
    for (unsigned int i=0; i<4; i++) 
    {     
        if (vehicle->GetEmptyCargoSlot() == nullptr)
        {
            return;
        }
            
        TYPE::ENTITY module_subtype_id = meti::getRand(MODULE_TYPES);
        switch(module_subtype_id)  
        {
            case TYPE::ENTITY::LAZER_MODULE_ID:       { vehicle->AddItemToCargoSlot(global::get().lazerModuleBuilder().create()); break; }
            case TYPE::ENTITY::ROCKET_MODULE_ID:      { vehicle->AddItemToCargoSlot(global::get().rocketModuleBuilder().create()); break; }
            case TYPE::ENTITY::DRIVE_MODULE_ID:       { vehicle->AddItemToCargoSlot(global::get().driveModuleBuilder().create()); break; }
            case TYPE::ENTITY::RADAR_MODULE_ID:       { vehicle->AddItemToCargoSlot(global::get().radarModuleBuilder().create()); break; }
            case TYPE::ENTITY::BAK_MODULE_ID:         { vehicle->AddItemToCargoSlot(global::get().bakModuleBuilder().create()); break; }
            //case TYPE::ENTITY::ENERGIZER_MODULE_ID: { vehicle->AddItemToCargoSlot(global::get().energizerModuleBuilder().create()); break; }
            case TYPE::ENTITY::PROTECTOR_MODULE_ID:   { vehicle->AddItemToCargoSlot(global::get().protectorModuleBuilder().create()); break; }
            case TYPE::ENTITY::DROID_MODULE_ID:       { vehicle->AddItemToCargoSlot(global::get().droidModuleBuilder().create()); break; }
            //case TYPE::ENTITY::FREEZER_MODULE_ID:   { vehicle->AddItemToCargoSlot(global::get().freezerModuleBuilder().create()); break; }
            case TYPE::ENTITY::GRAPPLE_MODULE_ID:     { vehicle->AddItemToCargoSlot(global::get().grappleModuleBuilder().create()); break; }
            case TYPE::ENTITY::SCANER_MODULE_ID:      { vehicle->AddItemToCargoSlot(global::get().scanerModuleBuilder().create()); break; }
        }
    }
}
#endif // USE_MODULES

#ifdef USE_ARTEFACTS
void BaseVehicleBuilder::EquipArtefacts(Vehicle* vehicle, TYPE::TECH tech_level) const
{
    for (unsigned int i=0; i<2; i++) {
        if (vehicle->GetEmptyCargoSlot() == nullptr) {
            return;
        }                    
        vehicle->manage(global::get().gravityArtefactBuilder().create());
    }   

    for (unsigned int i=0; i<2; i++) {
        if (vehicle->GetEmptyCargoSlot() == nullptr) {
            return;
        }            
        vehicle->manage(global::get().protectorArtefactBuilder().create());
    }  
}
#endif // USE_ARTEFACTS

void BaseVehicleBuilder::EquipBomb(Vehicle* vehicle, TYPE::TECH tech_level) const
{
    for (unsigned int i=0; i<2; i++) {
        //vehicle->AddItemToCargoSlot(global::get().bombBuilder().create());
    }    
}




