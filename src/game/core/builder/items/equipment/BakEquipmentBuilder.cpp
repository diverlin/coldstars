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


#include <builder/items/equipment/BakEquipmentBuilder.hpp>
#include <items/equipment/BakEquipment.hpp>
#include <managers/EntityManager.hpp>

#include <common/IdGenerator.hpp>
#include <ceti/Logger.hpp>
#include <math/rand.hpp>
#include <common/constants.hpp>

#include <common/Global.hpp>

#include <common/RaceDescriptors.hpp>

#include <meti/RandUtils.hpp>

BakEquipmentBuilder::BakEquipmentBuilder()
{
}

BakEquipmentBuilder::~BakEquipmentBuilder()
{}

BakEquipment* BakEquipmentBuilder::createTemplate(ID id) const
{
    BakEquipment* bak_equipment = new BakEquipment(id);
    assert(bak_equipment);

    global::get().entityManager().reg(bak_equipment);
    
    return bak_equipment;
} 
       
BakEquipment* BakEquipmentBuilder::create(TYPE::TECHLEVEL tech_level, TYPE::RACE race_id, int fuel_max) const
{
    BakEquipment* bak_equipment = createTemplate();
    createInternals(bak_equipment, tech_level, race_id, fuel_max);
    
    return bak_equipment;
}
                          
void BakEquipmentBuilder::createInternals(BakEquipment* bak_equipment, TYPE::TECHLEVEL tech_level, TYPE::RACE race_id, int fuel_max_orig) const
{     
    if (race_id == TYPE::RACE::NONE_ID) {
        race_id = meti::getRand(global::get().raceDescriptors().getRaces(TYPE::KIND::GOOD));
    }
    
    if (tech_level == TYPE::TECHLEVEL::NONE_ID) {
        tech_level = TYPE::TECHLEVEL::L0_ID; 
    }

    //jeti::Mesh* mesh = MeshCollector::Instance().getMesh(TYPE::MESH::PLANE_ID);
    //jeti::TextureOb* texOb_item = TextureCollector::Instance().getTextureByTypeId(TYPE::TEXTURE::BAK_EQUIPMENT_ID);
    //item_texOb = TEXTURE_MANAGER.returnItemTexOb(TYPE::TEXTURE::RADAR_EQUIPMENT_ID, revision_id) 
    
    fuel_max_orig = meti::getRandInt(EQUIPMENT::BAK::FUEL_MIN, EQUIPMENT::BAK::FUEL_MAX) * (1 + EQUIPMENT::BAK::FUEL_TECHLEVEL_RATE * (int)tech_level);

    ItemCommonData common_data;
    common_data.tech_level              = tech_level;
    common_data.modules_num_max        = meti::getRandInt(EQUIPMENT::BAK::MODULES_NUM_MIN, EQUIPMENT::BAK::MODULES_NUM_MAX);
    common_data.mass                   = meti::getRandInt(EQUIPMENT::BAK::MASS_MIN, EQUIPMENT::BAK::MASS_MAX);
    common_data.condition_max          = meti::getRandInt(EQUIPMENT::BAK::CONDITION_MIN, EQUIPMENT::BAK::CONDITION_MAX);
    common_data.deterioration_normal = 1;

    bak_equipment->SetFuelMaxOrig(fuel_max_orig);
    bak_equipment->SetFuel(fuel_max_orig);
    // alpitodorender bak_equipment->SetRenderData(mesh, texOb_item, texOb_item->size());
    bak_equipment->setParentSubTypeId(TYPE::ENTITY::BAK_SLOT_ID);
    bak_equipment->setItemCommonData(common_data);
    bak_equipment->setCondition(common_data.condition_max);
                                    
    bak_equipment->updateProperties();
    bak_equipment->CountPrice();
}


