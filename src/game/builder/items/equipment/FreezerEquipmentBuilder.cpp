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


#include <builder/items/equipment/FreezerEquipmentBuilder.hpp>
#include <items/equipment/FreezerEquipment.hpp>

#include <common/IdGenerator.hpp>
#include <common/Logger.hpp>
#include <math/rand.hpp>
#include <common/constants.hpp>

#include <world/EntityManager.hpp>

#include <resources/TextureCollector.hpp>
#include <resources/MeshCollector.hpp>
#include <jeti/TextureOb.hpp>

#include <struct/RaceInformationCollector.hpp>


FreezerEquipmentBuilder& FreezerEquipmentBuilder::Instance()
{
    static FreezerEquipmentBuilder instance;
    return instance;
}

FreezerEquipmentBuilder::~FreezerEquipmentBuilder()
{}

FreezerEquipment* FreezerEquipmentBuilder::GetNewFreezerEquipmentTemplate(INTLONGEST id) const
{
    FreezerEquipment* freezer_equipment = nullptr;

    if (id == NONE_ID)
    {
        id = EntityIdGenerator::Instance().GetNextId();
    }

     try 
        { 
            freezer_equipment = new FreezerEquipment(id);
        }
        catch(std::bad_alloc)
        {
            Logger::Instance().Log("EXEPTION:bad_dynamic_memory_allocation\n");
        }
        EntityManager::Instance().RegisterEntity(freezer_equipment);
        
        return freezer_equipment;
} 
    
FreezerEquipment* FreezerEquipmentBuilder::GetNewFreezerEquipment(TYPE::TECHLEVEL tech_level, TYPE::RACE race_id, int freeze_orig) const
{
    FreezerEquipment* freezer_equipment = GetNewFreezerEquipmentTemplate();
    CreateNewInternals(freezer_equipment, tech_level, race_id, freeze_orig);
    
    return freezer_equipment;
} 
        
void FreezerEquipmentBuilder::CreateNewInternals(FreezerEquipment* freezer_equipment, TYPE::TECHLEVEL tech_level, TYPE::RACE race_id, int freeze_orig) const
{     
    if (race_id == TYPE::RACE::NONE_ID)
    {
        race_id = getRand(RaceInformationCollector::Instance().RACES_GOOD_vec);
    }
    
    if (tech_level == TYPE::TECHLEVEL::NONE_ID)
    {
        tech_level = TYPE::TECHLEVEL::L0_ID; 
    }

    jeti::Mesh* mesh = MeshCollector::Instance().getMesh(TYPE::MESH::PLANE_ID);
    jeti::TextureOb* texOb_item = TextureCollector::Instance().getTextureByTypeId(TYPE::TEXTURE::FREEZER_EQUIPMENT_ID);
    //item_texOb = TEXTURE_MANAGER.returnItemTexOb(TYPE::TEXTURE::RADAR_EQUIPMENT_ID, revision_id) 

    freeze_orig     = getRandInt(EQUIPMENT::FREEZER::FREEZE_MIN, EQUIPMENT::FREEZER::FREEZE_MAX) * (1 + EQUIPMENT::FREEZER::FREEZE_TECHLEVEL_RATE*(int)tech_level);
    
    ItemCommonData common_data;
    common_data.tech_level         = tech_level;
    common_data.modules_num_max = getRandInt(EQUIPMENT::FREEZER::MODULES_NUM_MIN, EQUIPMENT::FREEZER::MODULES_NUM_MAX);
    common_data.mass            = getRandInt(EQUIPMENT::FREEZER::MASS_MIN,        EQUIPMENT::FREEZER::MASS_MAX);
    common_data.condition_max   = getRandInt(EQUIPMENT::FREEZER::CONDITION_MIN,   EQUIPMENT::FREEZER::CONDITION_MAX);
    common_data.deterioration_normal = 1;
    
    freezer_equipment->SetFreezeOrig(freeze_orig);  
    //alpitodorender freezer_equipment->SetRenderData(mesh, texOb_item, texOb_item->GetSize());
    freezer_equipment->SetParentSubTypeId(TYPE::ENTITY::FREEZER_SLOT_ID);
    freezer_equipment->SetItemCommonData(common_data);
    freezer_equipment->SetCondition(common_data.condition_max);
      
    freezer_equipment->UpdateProperties();
    freezer_equipment->CountPrice();
}


