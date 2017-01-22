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

#include <builder/item/equipment/ALL>
#include <builder/item/modules/ALL>
#include <builder/item/artefacts//ALL>
#include <builder/item/other/ALL>

#include <builder/spaceobjects/ShipBuilder.hpp>
#include <builder/CommonBuilderHeaders.hpp>

#include <dock/Store.hpp>

#include <spaceobjects/Ship.hpp>

#include <item/equipment/ALL>

#include <common/constants.hpp>

#include <descriptors/VehicleDescriptorGenerator.hpp>
#include <descriptors/DescriptorManager.hpp>

StoreBuilder::StoreBuilder()
{}

StoreBuilder::~StoreBuilder()
{}

Store* StoreBuilder::createTemplate(int_t id) const
{
    Store* store = new Store(id);
    assert(store);

   core::global::get().entityManager().reg(store);
    
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
        ItemSlot* item_slot = getNewItemSlot(type::entity::CARGO_SLOT_ID);
        store->addItemSlot(item_slot);
    }

    for (unsigned int i=0; i<STORE_VEHICLE_SLOTS_NUM; i++)
    {
        VehicleSlot* vehicle_slot = getNewVehicleSlot(type::entity::NONE_ID);
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
        assert(false);
        //store->addVehicle(ShipBuilder::getNew());
    }
    for (unsigned int i=0; i<lazer_num; i++) {
        store->addItem(core::global::get().lazerBuilder().getNew());
    }
    for (unsigned int i=0; i<rocket_num; i++) {
        store->addItem(core::global::get().rocketBuilder().getNew());
    }
    for (unsigned int i=0; i<radar_num; i++) {
        const auto& descr = core::global::get().descriptors().getRand(descriptor::Type::RADAR);
        store->addItem(core::global::get().radarBuilder().getNew(descr));
    }
    for (unsigned int i=0; i<grapple_num; i++) {
        const auto& descr = core::global::get().descriptors().getRand(descriptor::Type::GRAPPLE);
        store->addItem(core::global::get().grappleBuilder().getNew(descr));
    }
    for (unsigned int i=0; i<drive_num; i++) {
        const auto& descr = core::global::get().descriptors().getRand(descriptor::Type::DRIVE);
        store->addItem(core::global::get().driveBuilder().getNew(descr));
    }
    for (unsigned int i=0; i<protector_num; i++) {
        const auto& descr = core::global::get().descriptors().getRand(descriptor::Type::PROTECTOR);
        store->addItem(core::global::get().protectorBuilder().getNew(descr));
    }
    for (unsigned int i=0; i<bak_num; i++) {
        const auto& descr = core::global::get().descriptors().getRand(descriptor::Type::BAK);
        store->addItem(core::global::get().bakBuilder().getNew(descr));
    }
    for (unsigned int i=0; i<droid_num; i++) {
        const auto& descr = core::global::get().descriptors().getRand(descriptor::Type::DROID);
        store->addItem(core::global::get().droidBuilder().getNew(descr));
    }
    for (unsigned int i=0; i<scaner_num; i++) {
        const auto& descr = core::global::get().descriptors().getRand(descriptor::Type::SCANER);
        store->addItem(core::global::get().scanerBuilder().getNew(descr));
    }
#ifdef USE_EXTRA_EQUIPMENT
    for (unsigned int i=0; i<freezer_num; i++) {
        store->AddItem(core::global::get().freezerBuilder().create());
    }
    for (unsigned int i=0; i<energyBlock_num; i++) {
        store->AddItem(core::global::get().energizerBuilder().create());
    }
#endif
}
