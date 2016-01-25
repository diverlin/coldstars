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


#include <builder/items/equipment/ScanerEquipmentBuilder.hpp>
#include <items/equipment/ScanerEquipment.hpp>
#include <managers/EntityManager.hpp>

#include <common/IdGenerator.hpp>
#include <ceti/Logger.hpp>
#include <math/rand.hpp>
#include <common/constants.hpp>

#include <common/Global.hpp>

//#include <resources/TextureCollector.hpp>
//#include <resources/MeshCollector.hpp>
//#include <jeti/TextureOb.hpp>

#include <descriptors/RaceDescriptors.hpp>

#include <meti/RandUtils.hpp>

ScanerEquipmentBuilder::ScanerEquipmentBuilder()
{}

ScanerEquipmentBuilder::~ScanerEquipmentBuilder()
{}

ScanerEquipment* ScanerEquipmentBuilder::createTemplate(id_type id) const
{
    ScanerEquipment* scaner_equipment = new ScanerEquipment(id);
    assert(scaner_equipment);

    global::get().entityManager().reg(scaner_equipment);
    
    return scaner_equipment;
} 

ScanerEquipment* ScanerEquipmentBuilder::create(TYPE::TECHLEVEL tech_level, TYPE::RACE race_id, int scan_orig) const
{
    ScanerEquipment* scaner_equipment = createTemplate();
    createInternals(scaner_equipment, tech_level, race_id, scan_orig);
        
    return scaner_equipment;
} 
            
void ScanerEquipmentBuilder::createInternals(ScanerEquipment* scaner_equipment, TYPE::TECHLEVEL tech_level, TYPE::RACE race_id, int scan_orig) const
{     
    if (race_id == TYPE::RACE::NONE_ID) {
        race_id = meti::getRand(global::get().raceDescriptors().getRaces(TYPE::KIND::GOOD));
    }
    
    if (tech_level == TYPE::TECHLEVEL::NONE_ID) {
        tech_level = TYPE::TECHLEVEL::L0_ID; 
    }

    //jeti::Mesh* mesh = MeshCollector::Instance().getMesh(TYPE::MESH::PLANE_ID);
    //jeti::TextureOb* texOb_item = TextureCollector::Instance().getTextureByTypeId(TYPE::TEXTURE::SCANER_EQUIPMENT_ID);
    //item_texOb = TEXTURE_MANAGER.returnItemTexOb(TYPE::TEXTURE::SCANER_EQUIPMENT_ID, revision_id)

    scan_orig       = meti::getRandInt(EQUIPMENT::SCANER::SCAN_MIN, EQUIPMENT::SCANER::SCAN_MAX) * (1 + EQUIPMENT::SCANER::SCAN_TECHLEVEL_RATE * (int)tech_level);
    
    ItemCommonData common_data;
    common_data.tech         = tech_level;
    common_data.modules_num = meti::getRandInt(EQUIPMENT::SCANER::MODULES_NUM_MIN, EQUIPMENT::SCANER::MODULES_NUM_MAX);
    common_data.mass            = meti::getRandInt(EQUIPMENT::SCANER::MASS_MIN,        EQUIPMENT::SCANER::MASS_MAX);
    common_data.condition   = meti::getRandInt(EQUIPMENT::SCANER::CONDITION_MIN,   EQUIPMENT::SCANER::CONDITION_MAX);
    common_data.deterioration = 1;
    
    scaner_equipment->SetScanOrig(scan_orig);  
    //alpitodorender scaner_equipment->SetRenderData(mesh, texOb_item, texOb_item->size());
    scaner_equipment->setParentSubTypeId(TYPE::ENTITY::SCANER_SLOT_ID);
    scaner_equipment->setItemCommonData(common_data);
    scaner_equipment->setCondition(common_data.condition);
               
    scaner_equipment->updateProperties();
    scaner_equipment->CountPrice();
}
