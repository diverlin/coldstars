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


#include <builder/items/equipment/RadarEquipmentBuilder.hpp>
#include <items/equipment/RadarEquipment.hpp>
#include <managers/EntityManager.hpp>

#include <common/IdGenerator.hpp>
#include <ceti/Logger.hpp>
#include <math/rand.hpp>
#include <common/constants.hpp>

#include <common/Global.hpp>
         
#include <common/RaceDescriptors.hpp>

#include <meti/RandUtils.hpp>

RadarEquipmentBuilder::RadarEquipmentBuilder()
{}

RadarEquipmentBuilder::~RadarEquipmentBuilder()
{}

RadarEquipment* RadarEquipmentBuilder::createTemplate(ID id) const
{
    RadarEquipment* radar_equipment = new RadarEquipment(id);
    assert(radar_equipment);

    global::get().entitiesManager().reg(radar_equipment);
    
    return radar_equipment;
} 
  
RadarEquipment* RadarEquipmentBuilder::create(TYPE::TECHLEVEL tech_level, TYPE::RACE race_id, int radius_orig) const
{
    RadarEquipment* radar_equipment = createTemplate();
    createInternals(radar_equipment, tech_level, race_id, radius_orig);
        
    return radar_equipment;
} 
        
void RadarEquipmentBuilder::createInternals(RadarEquipment* radar_equipment, TYPE::TECHLEVEL tech_level, TYPE::RACE race_id, int radius_orig) const
{     
    if (race_id == TYPE::RACE::NONE_ID) {
        race_id = meti::getRand(global::get().raceDescriptors().getRaces(TYPE::KIND::GOOD));
    }
    
    if (tech_level == TYPE::TECHLEVEL::NONE_ID) {
        tech_level = TYPE::TECHLEVEL::L0_ID; 
    }

    //jeti::Mesh* mesh = MeshCollector::Instance().getMesh(TYPE::MESH::PLANE_ID);
    //jeti::TextureOb* texOb_item = TextureCollector::Instance().getTextureByTypeId(TYPE::TEXTURE::RADAR_EQUIPMENT_ID);
    //item_texOb = TEXTURE_MANAGER.returnItemTexOb(TYPE::TEXTURE::RADAR_EQUIPMENT_ID, revision_id) 

    radius_orig     = meti::getRandInt(EQUIPMENT::RADAR::RADIUS_MIN, EQUIPMENT::RADAR::RADIUS_MAX) * (1 + EQUIPMENT::RADAR::RADIUS_TECHLEVEL_RATE * (int)tech_level);
    
    ItemCommonData common_data;
    common_data.tech_level      = tech_level;
    common_data.modules_num_max = meti::getRandInt(EQUIPMENT::RADAR::MODULES_NUM_MIN, EQUIPMENT::RADAR::MODULES_NUM_MAX);
    common_data.mass            = meti::getRandInt(EQUIPMENT::RADAR::MASS_MIN,        EQUIPMENT::RADAR::MASS_MAX);
    common_data.condition_max   = meti::getRandInt(EQUIPMENT::RADAR::CONDITION_MIN,   EQUIPMENT::RADAR::CONDITION_MAX);
    common_data.deterioration_normal = 1;

    radar_equipment->SetRadiusOrig(radius_orig);
    //alpitodorender radar_equipment->SetRenderData(mesh, texOb_item, texOb_item->size());
    radar_equipment->setParentSubTypeId(TYPE::ENTITY::RADAR_SLOT_ID);
    radar_equipment->setItemCommonData(common_data);
    radar_equipment->setCondition(common_data.condition_max);

    radar_equipment->updateProperties();
    radar_equipment->CountPrice();
}


