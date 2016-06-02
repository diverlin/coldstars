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


#include <builder/dock/StoreBuilder.hpp>
#include <builder/slots/ItemSlotBuilder.hpp>
#include <builder/slots/VehicleSlotBuilder.hpp>
#include <builder/item/IncludeItemBuilders.hpp>
#include <builder/spaceobjects/ShipBuilder.hpp>
#include <builder/CommonBuilderHeaders.hpp>

#include <dock/Store.hpp>

#include <spaceobjects/Ship.hpp>

#include <item/equipment/ALL>

#include <common/constants.hpp>

#include <descriptors/VehicleDescriptorGenerator.hpp>
#include <descriptors/DescriptorGenerator.hpp>

StoreBuilder::StoreBuilder()
{}

StoreBuilder::~StoreBuilder()
{}

Store* StoreBuilder::createTemplate(id_type id) const
{
    Store* store = new Store(id);
    assert(store);

    global::get().entityManager().reg(store);
    
    return store;
} 

Store* StoreBuilder::create() const
{
    Store* store = createTemplate();
    createInternals(store);
    PutRandomEquipment(store);

    return store;
} 

void StoreBuilder::createInternals(Store* store) const
{
    for (unsigned int i=0; i<STORE_ITEM_SLOTS_NUM; i++)
    {
        ItemSlot* item_slot = GetNewItemSlot(TYPE::ENTITY::CARGO_SLOT_ID);
        store->addItemSlot(item_slot);
    }

    for (unsigned int i=0; i<STORE_VEHICLE_SLOTS_NUM; i++)
    {
        VehicleSlot* vehicle_slot = GetNewVehicleSlot(TYPE::ENTITY::NONE_ID);
        store->addVehicleSlot(vehicle_slot);
    }

    //store->SetTextureObBackground(TextureCollector::Instance().getTextureByTypeId(TYPE::TEXTURE::STORE_BACKGROUND_ID));
}


void StoreBuilder::PutRandomEquipment(Store* store) const
{
    //int race_id = RACES_GOOD_LIST[getRandInt(0, RACES_GOOD_LIST.size() - 1)];
    //int revision_id = 0;

    unsigned int vehicle_num     = 3;

    unsigned int lazer_num       = 3;
    unsigned int rocket_num      = 2;
    //unsigned int torped_num      = 2;
    unsigned int radar_num       = 1;
    unsigned int grapple_num     = 1;
    unsigned int drive_num       = 1;
    unsigned int protector_num   = 1;
    unsigned int bak_num         = 1;
    unsigned int droid_num       = 1;
    unsigned int scaner_num      = 1;
    unsigned int freezer_num     = 1;
    unsigned int energyBlock_num = 1;

    for (unsigned int i=0; i<vehicle_num; i++) {
        store->addVehicle(global::get().shipBuilder().create(generateVehicleDescriptor()));
    }
    for (unsigned int i=0; i<lazer_num; i++) {
        store->addItem(global::get().lazerBuilder().create());
    }
    for (unsigned int i=0; i<rocket_num; i++) {
        store->addItem(global::get().rocketBuilder().create());
    }
    for (unsigned int i=0; i<radar_num; i++) {
        store->addItem(global::get().radarBuilder().create(DescriptorGenerator::getNewRadarDescriptor()));
    }
    for (unsigned int i=0; i<grapple_num; i++) {
        store->addItem(global::get().grappleBuilder().create(DescriptorGenerator::getNewGrappleDescriptor()));
    }
    for (unsigned int i=0; i<drive_num; i++) {
        store->addItem(global::get().driveBuilder().create(DescriptorGenerator::getNewDriveDescriptor()));
    }
    for (unsigned int i=0; i<protector_num; i++) {
        store->addItem(global::get().protectorBuilder().create(DescriptorGenerator::getNewProtectorDescriptor()));
    }
    for (unsigned int i=0; i<bak_num; i++) {
        store->addItem(global::get().bakBuilder().create(DescriptorGenerator::getNewBakDescriptor()));
    }
    for (unsigned int i=0; i<droid_num; i++) {
        store->addItem(global::get().droidBuilder().create(DescriptorGenerator::getNewDroidDescriptor()));
    }
    for (unsigned int i=0; i<scaner_num; i++) {
        store->addItem(global::get().scanerBuilder().create(DescriptorGenerator::getNewScanerDescriptor()));
    }
#ifdef USE_EXTRA_EQUIPMENT
    for (unsigned int i=0; i<freezer_num; i++) {
        store->AddItem(global::get().freezerBuilder().create());
    }
    for (unsigned int i=0; i<energyBlock_num; i++) {
        store->AddItem(global::get().energizerBuilder().create());
    }
#endif
}
