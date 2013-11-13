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

#include <common/IdGenerator.hpp>
#include <common/Logger.hpp>
#include <common/rand.hpp>
#include <common/constants.hpp>

#include <world/EntityManager.hpp>
#include <resources/TextureManager.hpp>

#include <struct/RaceInformationCollector.hpp>


DroidEquipmentBuilder& DroidEquipmentBuilder::Instance()
{
    static DroidEquipmentBuilder instance;
    return instance;
}

DroidEquipmentBuilder::~DroidEquipmentBuilder()
{}

DroidEquipment* DroidEquipmentBuilder::GetNewDroidEquipmentTemplate(INTLONGEST id) const
{
    DroidEquipment* droid_equipment = nullptr;
    if (id == NONE_ID)
    {
        id = EntityIdGenerator::Instance().GetNextId();
    }

    try 
    { 
        droid_equipment = new DroidEquipment(id);
    }
    catch(std::bad_alloc)
    {
        Logger::Instance().Log("EXEPTION:bad_dynamic_memory_allocation\n");
    }
    EntityManager::Instance().RegisterEntity(droid_equipment);
    
    return droid_equipment;
} 

DroidEquipment* DroidEquipmentBuilder::GetNewDroidEquipment(TYPE::TECHLEVEL tech_level, TYPE::RACE race_id, int repair_orig) const
{
    DroidEquipment* droid_equipment = GetNewDroidEquipmentTemplate();
    CreateNewInternals(droid_equipment, tech_level, race_id, repair_orig);
        
    return droid_equipment;
}  
            
void DroidEquipmentBuilder::CreateNewInternals(DroidEquipment* droid_equipment, TYPE::TECHLEVEL tech_level, TYPE::RACE race_id, int repair_orig) const
{     
    if (race_id == TYPE::RACE::NONE_ID)
    {
        race_id = getRand(RaceInformationCollector::Instance().RACES_GOOD_vec);
    }
    
    if (tech_level == TYPE::TECHLEVEL::NONE_ID)
    {
        tech_level = TYPE::TECHLEVEL::L0_ID; 
    }

    TextureOb* texOb_item = TextureManager::Instance().GetRandomTextureOb(TYPE::TEXTURE::DROID_EQUIPMENT_ID);    
    //item_texOb = TEXTURE_MANAGER.returnItemTexOb(TYPE::TEXTURE::DROID_EQUIPMENT_ID, revision_id)

    repair_orig     = getRandInt(EQUIPMENT::DROID::REPAIR_MIN, EQUIPMENT::DROID::REPAIR_MAX) * (1 + EQUIPMENT::DROID::REPAIR_TECHLEVEL_RATE*(int)tech_level);
    
    ItemCommonData common_data;
    common_data.tech_level         = tech_level;
    common_data.modules_num_max = getRandInt(EQUIPMENT::DROID::MODULES_NUM_MIN, EQUIPMENT::DROID::MODULES_NUM_MAX);
    common_data.mass            = getRandInt(EQUIPMENT::DROID::MASS_MIN,        EQUIPMENT::DROID::MASS_MAX);
    common_data.condition_max   = getRandInt(EQUIPMENT::DROID::CONDITION_MIN,   EQUIPMENT::DROID::CONDITION_MAX);
    common_data.deterioration_normal = 1;
   
    droid_equipment->SetRepairOrig(repair_orig);  
    droid_equipment->BindData2D(texOb_item);        
    droid_equipment->SetParentSubTypeId(TYPE::ENTITY::DROID_SLOT_ID);
    droid_equipment->SetItemCommonData(common_data);
    droid_equipment->SetCondition(common_data.condition_max);
            
    droid_equipment->UpdateProperties();
    droid_equipment->CountPrice();
}


