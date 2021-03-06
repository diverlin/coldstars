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


#include <builder/items/equipment/GrappleEquipmentBuilder.hpp>
#include <items/equipment/GrappleEquipment.hpp>

#include <common/IdGenerator.hpp>
#include <common/Logger.hpp>
#include <math/rand.hpp>
#include <common/constants.hpp>

#include <world/EntityManager.hpp>

#include <resources/TextureManager.hpp>
#include <resources/MeshCollector.hpp>
#include <resources/textureOb.hpp>

#include <struct/RaceInformationCollector.hpp>


GrappleEquipmentBuilder& GrappleEquipmentBuilder::Instance()
{
    static GrappleEquipmentBuilder instance;
    return instance;
}

GrappleEquipmentBuilder::~GrappleEquipmentBuilder()
{}

GrappleEquipment* GrappleEquipmentBuilder::GetNewGrappleEquipmentTemplate(INTLONGEST id) const
{
    GrappleEquipment* grapple_equipment = nullptr;
    
    if (id == NONE_ID)
    {
        id = EntityIdGenerator::Instance().GetNextId();
    }

      try 
    { 
        grapple_equipment = new GrappleEquipment(id);
    }
    catch(std::bad_alloc)
    {
        Logger::Instance().Log("EXEPTION:bad_dynamic_memory_allocation\n");
    }
    EntityManager::Instance().RegisterEntity(grapple_equipment);
    
    return grapple_equipment;
} 
        
GrappleEquipment* GrappleEquipmentBuilder::GetNewGrappleEquipment(TYPE::TECHLEVEL tech_level, TYPE::RACE race_id, int strength_orig, int radius_orig, int speed_orig) const
{
    GrappleEquipment* grapple_equipment = GetNewGrappleEquipmentTemplate();
    CreateNewInternals(grapple_equipment, tech_level, race_id, strength_orig, radius_orig, speed_orig);
        
    return grapple_equipment;
} 
            
void GrappleEquipmentBuilder::CreateNewInternals(GrappleEquipment* grapple_equipment, TYPE::TECHLEVEL tech_level, TYPE::RACE race_id, int strength_orig, int radius_orig, int speed_orig) const
{     
    if (race_id == TYPE::RACE::NONE_ID)
    {
        race_id = getRand(RaceInformationCollector::Instance().RACES_GOOD_vec);
    }
    
    if (tech_level == TYPE::TECHLEVEL::NONE_ID)
    {
        tech_level = TYPE::TECHLEVEL::L0_ID; 
    }

    Mesh* mesh = MeshCollector::Instance().GetMeshByTypeId(TYPE::MESH::PLANE_ID);
    TextureOb* texOb_item = TextureManager::Instance().GetRandomTextureOb(TYPE::TEXTURE::GRAPPLE_EQUIPMENT_ID);   
    //item_texOb = TEXTURE_MANAGER.returnItemTexOb(TYPE::TEXTURE::GRAPPLE_EQUIPMENT_ID, revision_id) 

    strength_orig   = getRandInt(EQUIPMENT::GRAPPLE::STRENGTH_MIN, EQUIPMENT::GRAPPLE::STRENGTH_MAX) * (1 + EQUIPMENT::GRAPPLE::STRENGTH_TECHLEVEL_RATE * (int)tech_level);
    radius_orig     = getRandInt(EQUIPMENT::GRAPPLE::RADIUS_MIN,   EQUIPMENT::GRAPPLE::RADIUS_MAX)   * (1 + EQUIPMENT::GRAPPLE::RADIUS_TECHLEVEL_RATE * (int)tech_level);
    speed_orig      = getRandInt(EQUIPMENT::GRAPPLE::SPEED_MIN,    EQUIPMENT::GRAPPLE::SPEED_MAX)    * (1 + EQUIPMENT::GRAPPLE::SPEED_TECHLEVEL_RATE * (int)tech_level);
    
    ItemCommonData common_data;
    common_data.tech_level         = tech_level;
    common_data.modules_num_max = getRandInt(EQUIPMENT::GRAPPLE::MODULES_NUM_MIN, EQUIPMENT::GRAPPLE::MODULES_NUM_MAX);
    common_data.mass            = getRandInt(EQUIPMENT::GRAPPLE::MASS_MIN,        EQUIPMENT::GRAPPLE::MASS_MAX);
    common_data.condition_max   = getRandInt(EQUIPMENT::GRAPPLE::CONDITION_MIN,   EQUIPMENT::GRAPPLE::CONDITION_MAX);
    common_data.deterioration_normal = 1;
                                                             
    grapple_equipment->SetStrengthOrig(strength_orig);
    grapple_equipment->SetRadiusOrig(radius_orig);
    grapple_equipment->SetSpeedOrig(speed_orig);

    grapple_equipment->SetRenderData(mesh, texOb_item, texOb_item->GetSize());    
    grapple_equipment->SetParentSubTypeId(TYPE::ENTITY::GRAPPLE_SLOT_ID);
    grapple_equipment->SetItemCommonData(common_data);        
    grapple_equipment->SetCondition(common_data.condition_max);
    
    grapple_equipment->UpdateProperties();
    grapple_equipment->CountPrice();
}


