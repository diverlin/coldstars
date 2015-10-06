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


#include <builder/items/equipment/LazerEquipmentBuilder.hpp>
#include <items/equipment/LazerEquipment.hpp>
#include <managers/EntitiesManager.hpp>

#include <common/IdGenerator.hpp>
#include <ceti/Logger.hpp>
#include <math/rand.hpp>
#include <common/constants.hpp>

#include <common/Global.hpp>

//#include <resources/TextureCollector.hpp>
//#include <resources/MeshCollector.hpp>
//#include <jeti/TextureOb.hpp>

#include <common/RaceDescriptors.hpp>
#include <meti/RandUtils.hpp>

LazerEquipmentBuilder::LazerEquipmentBuilder()
{}

LazerEquipmentBuilder::~LazerEquipmentBuilder()
{}

LazerEquipment* LazerEquipmentBuilder::createTemplate(ID id) const
{ 
    LazerEquipment* lazer_equipment = new LazerEquipment(id);
    assert(lazer_equipment);

    global::get().entitiesManager().registerEntity(lazer_equipment);
    
    return lazer_equipment;
} 

LazerEquipment* LazerEquipmentBuilder::create(TYPE::TECHLEVEL tech_level, TYPE::RACE race_id, int damage_orig, int radius_orig) const
{
    LazerEquipment* lazer_equipment = createTemplate();
    createInternals(lazer_equipment, tech_level, race_id, damage_orig, radius_orig);

    return lazer_equipment;
} 

void LazerEquipmentBuilder::createInternals(LazerEquipment* lazer_equipment, TYPE::TECHLEVEL tech_level, TYPE::RACE race_id, int damage_orig, int radius_orig) const
{     
    if (race_id == TYPE::RACE::NONE_ID) {
        race_id = meti::getRand(global::get().raceDescriptors().getRaces(TYPE::KIND::GOOD));
    }
    
    if (tech_level == TYPE::TECHLEVEL::NONE_ID) {
        tech_level = TYPE::TECHLEVEL::L0_ID;
    }

    //jeti::Mesh* mesh = MeshCollector::Instance().getMesh(TYPE::MESH::PLANE_ID);
    //item_texOb = TEXTURE_MANAGER.returnItemTexOb(TYPE::TEXTURE::LAZER_EQUIPMENT_ID, revision_id)
    //jeti::TextureOb* texOb_item = TextureCollector::Instance().getTextureByTypeId(TYPE::TEXTURE::LAZER_EQUIPMENT_ID);

    damage_orig     = meti::getRandInt(EQUIPMENT::LAZER::DAMAGE_MIN, EQUIPMENT::LAZER::DAMAGE_MAX) * (1 + EQUIPMENT::LAZER::DAMAGE_TECHLEVEL_RATE * (int)tech_level);
    radius_orig     = meti::getRandInt(EQUIPMENT::LAZER::RADIUS_MIN, EQUIPMENT::LAZER::RADIUS_MAX) * (1 + EQUIPMENT::LAZER::RADIUS_TECHLEVEL_RATE * (int)tech_level);
    
    ItemCommonData common_data;
    common_data.tech_level         = tech_level;
    common_data.modules_num_max = meti::getRandInt(EQUIPMENT::LAZER::MODULES_NUM_MIN, EQUIPMENT::LAZER::MODULES_NUM_MAX);
    common_data.mass            = meti::getRandInt(EQUIPMENT::LAZER::MASS_MIN, EQUIPMENT::LAZER::MASS_MAX);
    common_data.condition_max   = meti::getRandInt(EQUIPMENT::LAZER::CONDITION_MIN, EQUIPMENT::LAZER::CONDITION_MAX);
    common_data.deterioration_normal = 1;

    lazer_equipment->SetDamageOrig(damage_orig);
    lazer_equipment->SetRadiusOrig(radius_orig);
    //alpitodorender lazer_equipment->SetRenderData(mesh, texOb_item, texOb_item->size());
    lazer_equipment->setParentSubTypeId(TYPE::ENTITY::WEAPON_SLOT_ID);
    lazer_equipment->setItemCommonData(common_data);
    lazer_equipment->setCondition(common_data.condition_max);

    lazer_equipment->updateProperties();
    lazer_equipment->CountPrice();
}


