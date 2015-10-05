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


#include <builder/items/equipment/ProtectorEquipmentBuilder.hpp>
#include <items/equipment/ProtectorEquipment.hpp>
#include <managers/EntitiesManager.hpp>

#include <common/IdGenerator.hpp>
#include <ceti/Logger.hpp>
#include <math/rand.hpp>
#include <common/constants.hpp>

#include <common/Global.hpp>

#include <common/RaceDescriptors.hpp>

#include <meti/RandUtils.hpp>

ProtectorEquipmentBuilder::ProtectorEquipmentBuilder()
{}

ProtectorEquipmentBuilder::~ProtectorEquipmentBuilder()
{}

ProtectorEquipment* ProtectorEquipmentBuilder::createTemplate(INTLONGEST id) const
{
    if (id == NONE_ID) {
        id = EntityIdGenerator::Instance().GetNextId();
    }

    ProtectorEquipment* protector_equipment = new ProtectorEquipment(id);
    assert(protector_equipment);

    global::get().entitiesManager().RegisterEntity(protector_equipment);
    
    return protector_equipment;
} 
   
ProtectorEquipment* ProtectorEquipmentBuilder::create(TYPE::TECHLEVEL tech_level, TYPE::RACE race_id, int protection_orig) const
{
    ProtectorEquipment* protector_equipment = createTemplate();
    createInternals(protector_equipment, tech_level, race_id, protection_orig);
        
    return protector_equipment;
} 
         
void ProtectorEquipmentBuilder::createInternals(ProtectorEquipment* protector_equipment, TYPE::TECHLEVEL tech_level, TYPE::RACE race_id, int protection_orig) const
{     
    if (race_id == TYPE::RACE::NONE_ID) {
        race_id = meti::getRand(global::get().raceDescriptors().getRaces(TYPE::KIND::GOOD));
    }
    
    if (tech_level == TYPE::TECHLEVEL::NONE_ID) {
        tech_level = TYPE::TECHLEVEL::L0_ID; 
    }

    //jeti::Mesh* mesh = MeshCollector::Instance().getMesh(TYPE::MESH::PLANE_ID);
    //jeti::TextureOb* texOb_item = TextureCollector::Instance().getTextureByTypeId(TYPE::TEXTURE::PROTECTOR_EQUIPMENT_ID);
    //item_texOb = TEXTURE_MANAGER.returnItemTexOb(TYPE::TEXTURE::PROTECTOR_EQUIPMENT_ID, revision_id) 

    protection_orig = meti::getRandInt(EQUIPMENT::PROTECTOR::PROTECTION_MIN, EQUIPMENT::PROTECTOR::PROTECTION_MAX) * (1 + EQUIPMENT::PROTECTOR::PROTECTION_TECHLEVEL_RATE * (int)tech_level);
    
    ItemCommonData common_data;
    common_data.tech_level         = tech_level;
    common_data.modules_num_max = meti::getRandInt(EQUIPMENT::PROTECTOR::MODULES_NUM_MIN, EQUIPMENT::PROTECTOR::MODULES_NUM_MAX);
    common_data.mass            = meti::getRandInt(EQUIPMENT::PROTECTOR::MASS_MIN,        EQUIPMENT::PROTECTOR::MASS_MAX);
    common_data.condition_max   = meti::getRandInt(EQUIPMENT::PROTECTOR::CONDITION_MIN,   EQUIPMENT::PROTECTOR::CONDITION_MAX);
    common_data.deterioration_normal = 1;

    protector_equipment->SetProtectionOrig(protection_orig);  
    //alpitodorender protector_equipment->SetRenderData(mesh, texOb_item, texOb_item->size());
    protector_equipment->setParentSubTypeId(TYPE::ENTITY::PROTECTOR_SLOT_ID);
    protector_equipment->setItemCommonData(common_data);
    protector_equipment->setCondition(common_data.condition_max);
            
    protector_equipment->updateProperties();
    protector_equipment->CountPrice();
}
