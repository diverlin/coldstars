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

#include "EnergizerEquipmentBuilder.hpp"
#include "../../../items/equipment/EnergizerEquipment.hpp"

#include <common/IdGenerator.hpp>
#include <common/Logger.hpp>
#include <common/rand.hpp>
#include <common/constants.hpp>

#include "../../../world/EntityManager.hpp"
#include "../../../resources/TextureManager.hpp"

#include <struct/RaceInformationCollector.hpp>

EnergizerEquipmentBuilder& EnergizerEquipmentBuilder::Instance()
{
    static EnergizerEquipmentBuilder instance;
    return instance;
}

EnergizerEquipmentBuilder::~EnergizerEquipmentBuilder()
{}

EnergizerEquipment* EnergizerEquipmentBuilder::GetNewEnergizerEquipmentTemplate(INTLONGEST id) const
{
    EnergizerEquipment* energizer_equipment = nullptr;

    if (id == NONE_ID)
    {
        id = EntityIdGenerator::Instance().GetNextId();
    }

     try 
    { 
        energizer_equipment = new EnergizerEquipment(id);
    }
    catch(std::bad_alloc)
    {
        Logger::Instance().Log("EXEPTION:bad_dynamic_memory_allocation\n");
    }
    EntityManager::Instance().RegisterEntity(energizer_equipment);
    
    return energizer_equipment;
} 
    
EnergizerEquipment* EnergizerEquipmentBuilder::GetNewEnergizerEquipment(TYPE::TECHLEVEL tech_level, TYPE::RACE race_id, int energy_max_orig, int restoration_orig) const
{
    EnergizerEquipment* energizer_equipment = GetNewEnergizerEquipmentTemplate();
    CreateNewInternals(energizer_equipment, tech_level, race_id, energy_max_orig, restoration_orig);
            
    return energizer_equipment;
} 
        
void EnergizerEquipmentBuilder::CreateNewInternals(EnergizerEquipment* energizer_equipment, TYPE::TECHLEVEL tech_level, TYPE::RACE race_id, int energy_max_orig, int restoration_orig) const
{     
    if (race_id == TYPE::RACE::NONE_ID)
    {
        race_id = getRand(RaceInformationCollector::Instance().RACES_GOOD_vec);
    }
    
    if (tech_level == TYPE::TECHLEVEL::NONE_ID)
    {
        tech_level = TYPE::TECHLEVEL::L0_ID; 
    }

    TextureOb* texOb_item = TextureManager::Instance().GetRandomTextureOb(TYPE::TEXTURE::ENERGIZER_EQUIPMENT_ID);   
    //item_texOb = TEXTURE_MANAGER.returnItemTexOb(ENERGIZER_ITEM_TEXTURE_ID, revision_id)

    energy_max_orig  = getRandInt(EQUIPMENT::ENERGIZER::ENERGY_MIN,      EQUIPMENT::ENERGIZER::ENERGY_MAX)      * (1 + EQUIPMENT::ENERGIZER::ENERGY_TECHLEVEL_RATE * (int)tech_level);
    restoration_orig = getRandInt(EQUIPMENT::ENERGIZER::RESTORATION_MIN, EQUIPMENT::ENERGIZER::RESTORATION_MAX) * (1 + EQUIPMENT::ENERGIZER::RESTORATION_TECHLEVEL_RATE * (int)tech_level);
    
    ItemCommonData common_data;
    common_data.tech_level          = tech_level;
    common_data.modules_num_max  = getRandInt(EQUIPMENT::ENERGIZER::MODULES_NUM_MIN, EQUIPMENT::ENERGIZER::MODULES_NUM_MAX);
    common_data.mass             = getRandInt(EQUIPMENT::ENERGIZER::MASS_MIN,        EQUIPMENT::ENERGIZER::MASS_MAX);
    common_data.condition_max    = getRandInt(EQUIPMENT::ENERGIZER::CONDITION_MIN,   EQUIPMENT::ENERGIZER::CONDITION_MAX);
    common_data.deterioration_normal = 1;

    energizer_equipment->SetEnergyMaxOrig(energy_max_orig);
    energizer_equipment->SetRestorationOrig(restoration_orig);
    energizer_equipment->SetEnergy(0.5*energy_max_orig);
    energizer_equipment->BindData2D(texOb_item);        
    energizer_equipment->SetParentSubTypeId(TYPE::ENTITY::ENERGIZER_SLOT_ID);
    energizer_equipment->SetItemCommonData(common_data);
    energizer_equipment->SetCondition(common_data.condition_max);
                    
    energizer_equipment->UpdateProperties();
    energizer_equipment->CountPrice();
}


