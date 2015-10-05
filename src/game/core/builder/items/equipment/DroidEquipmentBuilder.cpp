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


#include <builder/items/equipment/DroidEquipmentBuilder.hpp>
#include <items/equipment/DroidEquipment.hpp>
#include <managers/EntitiesManager.hpp>

#include <common/IdGenerator.hpp>
#include <ceti/Logger.hpp>
#include <math/rand.hpp>
#include <common/constants.hpp>

#include <common/Global.hpp>

#include <common/RaceDescriptors.hpp>

#include <meti/RandUtils.hpp>


DroidEquipmentBuilder::DroidEquipmentBuilder()
{}

DroidEquipmentBuilder::~DroidEquipmentBuilder()
{}

DroidEquipment* DroidEquipmentBuilder::createTemplate(INTLONGEST id) const
{
    if (id == NONE_ID) {
        id = EntityIdGenerator::Instance().GetNextId();
    }

    DroidEquipment* droid_equipment = new DroidEquipment(id);
    assert(droid_equipment);

    global::get().entitiesManager().RegisterEntity(droid_equipment);
    
    return droid_equipment;
} 

DroidEquipment* DroidEquipmentBuilder::create(TYPE::TECHLEVEL tech_level, TYPE::RACE race_id, int repair_orig) const
{
    DroidEquipment* droid_equipment = createTemplate();
    createInternals(droid_equipment, tech_level, race_id, repair_orig);
        
    return droid_equipment;
}  
            
void DroidEquipmentBuilder::createInternals(DroidEquipment* droid_equipment, TYPE::TECHLEVEL tech_level, TYPE::RACE race_id, int repair_orig) const
{     
    if (race_id == TYPE::RACE::NONE_ID) {
        race_id = meti::getRand(global::get().raceDescriptors().getRaces(TYPE::KIND::GOOD));
    }
    
    if (tech_level == TYPE::TECHLEVEL::NONE_ID) {
        tech_level = TYPE::TECHLEVEL::L0_ID; 
    }

    //jeti::Mesh* mesh = MeshCollector::Instance().getMesh(TYPE::MESH::PLANE_ID);
    //jeti::TextureOb* texOb_item = TextureCollector::Instance().getTextureByTypeId(TYPE::TEXTURE::DROID_EQUIPMENT_ID);
    //item_texOb = TEXTURE_MANAGER.returnItemTexOb(TYPE::TEXTURE::DROID_EQUIPMENT_ID, revision_id)

    repair_orig     = meti::getRandInt(EQUIPMENT::DROID::REPAIR_MIN, EQUIPMENT::DROID::REPAIR_MAX) * (1 + EQUIPMENT::DROID::REPAIR_TECHLEVEL_RATE*(int)tech_level);
    
    ItemCommonData common_data;
    common_data.tech_level         = tech_level;
    common_data.modules_num_max = meti::getRandInt(EQUIPMENT::DROID::MODULES_NUM_MIN, EQUIPMENT::DROID::MODULES_NUM_MAX);
    common_data.mass            = meti::getRandInt(EQUIPMENT::DROID::MASS_MIN,        EQUIPMENT::DROID::MASS_MAX);
    common_data.condition_max   = meti::getRandInt(EQUIPMENT::DROID::CONDITION_MIN,   EQUIPMENT::DROID::CONDITION_MAX);
    common_data.deterioration_normal = 1;
   
    droid_equipment->SetRepairOrig(repair_orig);  
    //alpitodorender droid_equipment->SetRenderData(mesh, texOb_item, texOb_item->size());
    droid_equipment->setParentSubTypeId(TYPE::ENTITY::DROID_SLOT_ID);
    droid_equipment->setItemCommonData(common_data);
    droid_equipment->setCondition(common_data.condition_max);
            
    droid_equipment->updateProperties();
    droid_equipment->CountPrice();
}


