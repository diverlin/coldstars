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

#include "resources.hpp"
#include "../common/constants.hpp"
#include "../config/config.hpp"
//#include <jeti/ShaderLoader.hpp>
#include <jeti/Mesh.hpp>
//#include <jeti/Screen.hpp>
#include "MeshCollector.hpp"

#include "TextureManager.hpp"
#include "GuiTextureObCollector.hpp"

#include <types/MyInt.hpp>
#include <types/RaceTypes.hpp>
#include <types/MeshTypes.hpp>
#include <types/TechLevelTypes.hpp>

void loadGameData()
{        
    load3DModels();
    loadImages();
}

void load3DModels()
{        
    MeshCollector::Instance().addMesh(TYPE::MESH::PLANE_ID,             new jeti::Mesh(DATA_PATH+"obj/plane/plane.obj",   glm::vec3(0.0f, 0.0f, 1.0f), nullptr));
    MeshCollector::Instance().addMesh(TYPE::MESH::SPHERE_ID,            new jeti::Mesh(DATA_PATH+"obj/sphere/sphere.obj", glm::vec3(1.0f, 0.0f, 0.0f), nullptr));
    MeshCollector::Instance().addMesh(TYPE::MESH::SPHERE_DEFORMED_ID,   new jeti::Mesh(DATA_PATH+"obj/sphere_deformed/sphere_deformed.obj", glm::vec3(1.0f, 0.0f, 0.0f), nullptr));
    
    {
    jeti::Material material_data;
    material_data.texture_path = DATA_PATH+"obj/vehicles/BabylonStation/station_texture/babylonstation.jpg";
    jeti::TextureOb* textureOb = new jeti::TextureOb(material_data);
    jeti::Mesh* mesh = new jeti::Mesh(DATA_PATH+"obj/vehicles/BabylonStation/babylon_station_mod.obj", glm::vec3(1.0f, 0.0f, 0.0f), textureOb);
    MeshCollector::Instance().addMesh(TYPE::MESH::SPACESTATION_ID, mesh);
    }

//    {
//    jeti::Material material_data;
//    material_data.texture_path = DATA_PATH+"obj/vehicles/Anna_V_2.0_variations/Anna_Textures/ship_hull12.jpg";
//    jeti::TextureOb* textureOb = new jeti::TextureOb(material_data);
//    jeti::Mesh* mesh = new jeti::Mesh(DATA_PATH+"obj/vehicles/Anna_V_2.0_variations/anna_mod.obj", glm::vec3(1.0f, 0.0f, 0.0f), textureOb);
//    MeshCollector::Instance().addMesh(TYPE::MESH::SPACESTATION_ID, mesh);
//    }

}



void loadImages()
{
//####################################### TURREL_TEXTURE ###################################
//{
//    jeti::Material material_data;
//    material_data.texture_path = DATA_PATH+"turrel/turrel1.png";
//    material_data.use_alpha = true;
//    jeti::TextureOb* textureOb = new jeti::TextureOb(material_data);

//    jeti::MaterialAssociationData association_data;
//    association_data.type_id = TYPE::TEXTURE::TURREL_ID;
//    textureOb->SetAssociation(association_data);

//    TextureManager::Instance().Add(textureOb);
//}

//{
//    jeti::Material material_data;
//    material_data.texture_path = DATA_PATH+"turrel/turrel2.png";
//    material_data.use_alpha = true;
//    jeti::TextureOb* textureOb = new jeti::TextureOb(material_data);

//    jeti::MaterialAssociationData association_data;
//    association_data.type_id = TYPE::TEXTURE::TURREL_ID;
//    textureOb->SetAssociation(association_data);

//    TextureManager::Instance().Add(textureOb);
//}

//{
//    jeti::Material material_data;
//    material_data.texture_path = DATA_PATH+"turrel/esphere-0.png";
//    material_data.use_alpha = true;
//    jeti::TextureOb* textureOb = new jeti::TextureOb(material_data);

//    jeti::MaterialAssociationData association_data;
//    association_data.type_id = TYPE::TEXTURE::TURREL_ID;
//    textureOb->SetAssociation(association_data);

//    TextureManager::Instance().Add(textureOb);
//}


//####################################### SLOT_TEXTURE ###################################
//{
//    jeti::Material material_data;
//    material_data.texture_path = DATA_PATH+"other/slot.png";
//    material_data.use_alpha = true;
//    jeti::TextureOb* textureOb = new jeti::TextureOb(material_data);

//    jeti::MaterialAssociationData association_data;
//    association_data.type_id = TYPE::TEXTURE::ITEM_SLOT_ID;
//    textureOb->SetAssociation(association_data);

//    TextureManager::Instance().Add(textureOb);
//}

//{
//    jeti::Material material_data;
//    material_data.texture_path = DATA_PATH+"other/H.png";
//    material_data.use_alpha = true;
//    material_data.col_num = 3;
//    material_data.row_num = 2;
//    material_data.fps = 3.0;
//    jeti::TextureOb* textureOb = new jeti::TextureOb(material_data);

//    jeti::MaterialAssociationData association_data;
//    association_data.type_id = TYPE::TEXTURE::VEHICLE_SLOT_ID;
//    textureOb->SetAssociation(association_data);

//    TextureManager::Instance().Add(textureOb);
//}

//####################################### TYPE::TEXTURE::FACE_ID ################################
//// TYPE::RACE::R0_ID
//{
//    jeti::Material material_data;
//    material_data.texture_path = DATA_PATH+"race/0000.png";
//    jeti::TextureOb* textureOb = new jeti::TextureOb(material_data);

//    jeti::MaterialAssociationData association_data;
//    association_data.type_id = TYPE::TEXTURE::FACE_ID;
//    association_data.race_id = TYPE::RACE::R0_ID;
//    textureOb->SetAssociation(association_data);

//    TextureManager::Instance().Add(textureOb);
//}

//{
//    jeti::Material material_data;
//    material_data.texture_path = DATA_PATH+"race/0001.png";
//    jeti::TextureOb* textureOb = new jeti::TextureOb(material_data);

//    jeti::MaterialAssociationData association_data;
//    association_data.type_id = TYPE::TEXTURE::FACE_ID;
//    association_data.race_id = TYPE::RACE::R0_ID;
//    textureOb->SetAssociation(association_data);

//    TextureManager::Instance().Add(textureOb);
//}

//// TYPE::RACE::R1_ID
//{
//    jeti::Material material_data;
//    material_data.texture_path = DATA_PATH+"race/1000.png";
//    jeti::TextureOb* textureOb = new jeti::TextureOb(material_data);

//    jeti::MaterialAssociationData association_data;
//    association_data.type_id = TYPE::TEXTURE::FACE_ID;
//    association_data.race_id = TYPE::RACE::R1_ID;
//    textureOb->SetAssociation(association_data);

//    TextureManager::Instance().Add(textureOb);
//}

//{
//    jeti::Material material_data;
//    material_data.texture_path = DATA_PATH+"race/1001.png";
//    jeti::TextureOb* textureOb = new jeti::TextureOb(material_data);

//    jeti::MaterialAssociationData association_data;
//    association_data.type_id = TYPE::TEXTURE::FACE_ID;
//    association_data.race_id = TYPE::RACE::R1_ID;
//    textureOb->SetAssociation(association_data);

//    TextureManager::Instance().Add(textureOb);
//}

//// TYPE::RACE::R2_ID
//{
//    jeti::Material material_data;
//    material_data.texture_path = DATA_PATH+"race/2000.png";
//    jeti::TextureOb* textureOb = new jeti::TextureOb(material_data);

//    jeti::MaterialAssociationData association_data;
//    association_data.type_id = TYPE::TEXTURE::FACE_ID;
//    association_data.race_id = TYPE::RACE::R2_ID;
//    textureOb->SetAssociation(association_data);

//    TextureManager::Instance().Add(textureOb);
//}

//{
//    jeti::Material material_data;
//    material_data.texture_path = DATA_PATH+"race/2001.png";
//    jeti::TextureOb* textureOb = new jeti::TextureOb(material_data);

//    jeti::MaterialAssociationData association_data;
//    association_data.type_id = TYPE::TEXTURE::FACE_ID;
//    association_data.race_id = TYPE::RACE::R2_ID;
//    textureOb->SetAssociation(association_data);

//    TextureManager::Instance().Add(textureOb);
//}

//// TYPE::RACE::R3_ID
//{
//    jeti::Material material_data;
//    material_data.texture_path = DATA_PATH+"race/3000.png";
//    jeti::TextureOb* textureOb = new jeti::TextureOb(material_data);

//    jeti::MaterialAssociationData association_data;
//    association_data.type_id = TYPE::TEXTURE::FACE_ID;
//    association_data.race_id = TYPE::RACE::R3_ID;
//    textureOb->SetAssociation(association_data);

//    TextureManager::Instance().Add(textureOb);
//}

//{
//    jeti::Material material_data;
//    material_data.texture_path = DATA_PATH+"race/3001.png";
//    jeti::TextureOb* textureOb = new jeti::TextureOb(material_data);

//    jeti::MaterialAssociationData association_data;
//    association_data.type_id = TYPE::TEXTURE::FACE_ID;
//    association_data.race_id = TYPE::RACE::R3_ID;
//    textureOb->SetAssociation(association_data);

//    TextureManager::Instance().Add(textureOb);
//}

//// TYPE::RACE::R4_ID
//{
//    jeti::Material material_data;
//    material_data.texture_path = DATA_PATH+"race/4000.png";
//    jeti::TextureOb* textureOb = new jeti::TextureOb(material_data);

//    jeti::MaterialAssociationData association_data;
//    association_data.type_id = TYPE::TEXTURE::FACE_ID;
//    association_data.race_id = TYPE::RACE::R4_ID;
//    textureOb->SetAssociation(association_data);

//    TextureManager::Instance().Add(textureOb);
//}

//{
//    jeti::Material material_data;
//    material_data.texture_path = DATA_PATH+"race/4001.png";
//    jeti::TextureOb* textureOb = new jeti::TextureOb(material_data);

//    jeti::MaterialAssociationData association_data;
//    association_data.type_id = TYPE::TEXTURE::FACE_ID;
//    association_data.race_id = TYPE::RACE::R4_ID;
//    textureOb->SetAssociation(association_data);

//    TextureManager::Instance().Add(textureOb);
//}

//// TYPE::RACE::R6_ID
//{
//    jeti::Material material_data;
//    material_data.texture_path = DATA_PATH+"race/6000.png";
//    jeti::TextureOb* textureOb = new jeti::TextureOb(material_data);

//    jeti::MaterialAssociationData association_data;
//    association_data.type_id = TYPE::TEXTURE::FACE_ID;
//    association_data.race_id = TYPE::RACE::R6_ID;
//    textureOb->SetAssociation(association_data);

//    TextureManager::Instance().Add(textureOb);
//}

//{
//    jeti::Material material_data;
//    material_data.texture_path = DATA_PATH+"race/6001.png";
//    jeti::TextureOb* textureOb = new jeti::TextureOb(material_data);

//    jeti::MaterialAssociationData association_data;
//    association_data.type_id = TYPE::TEXTURE::FACE_ID;
//    association_data.race_id = TYPE::RACE::R6_ID;
//    textureOb->SetAssociation(association_data);

//    TextureManager::Instance().Add(textureOb);
//}

//// TYPE::RACE::R7_ID
//{
//    jeti::Material material_data;
//    material_data.texture_path = DATA_PATH+"race/7000.png";
//    jeti::TextureOb* textureOb = new jeti::TextureOb(material_data);

//    jeti::MaterialAssociationData association_data;
//    association_data.type_id = TYPE::TEXTURE::FACE_ID;
//    association_data.race_id = TYPE::RACE::R7_ID;
//    textureOb->SetAssociation(association_data);

//    TextureManager::Instance().Add(textureOb);
//}

//{
//    jeti::Material material_data;
//    material_data.texture_path = DATA_PATH+"race/7001.png";
//    jeti::TextureOb* textureOb = new jeti::TextureOb(material_data);

//    jeti::MaterialAssociationData association_data;
//    association_data.type_id = TYPE::TEXTURE::FACE_ID;
//    association_data.race_id = TYPE::RACE::R7_ID;
//    textureOb->SetAssociation(association_data);

//    TextureManager::Instance().Add(textureOb);
//}



//####################################### ASTEROID_TEXTURE ################################
//{
//    jeti::Material material_data;
//    material_data.texture_path = DATA_PATH+"asteroid/a_000.png";
//    jeti::TextureOb* textureOb = new jeti::TextureOb(material_data);

//    jeti::MaterialAssociationData association_data;
//    association_data.type_id = TYPE::TEXTURE::ASTEROID_ID;
//    textureOb->SetAssociation(association_data);

//    TextureManager::Instance().Add(textureOb);
//}

//{
//    jeti::Material material_data;
//    material_data.texture_path = DATA_PATH+"asteroid/a_001.png";
//    jeti::TextureOb* textureOb = new jeti::TextureOb(material_data);

//    jeti::MaterialAssociationData association_data;
//    association_data.type_id = TYPE::TEXTURE::ASTEROID_ID;
//    textureOb->SetAssociation(association_data);

//    TextureManager::Instance().Add(textureOb);
//}

//{
//    jeti::Material material_data;
//    material_data.texture_path = DATA_PATH+"asteroid/a_002.png";
//    jeti::TextureOb* textureOb = new jeti::TextureOb(material_data);

//    jeti::MaterialAssociationData association_data;
//    association_data.type_id = TYPE::TEXTURE::ASTEROID_ID;
//    textureOb->SetAssociation(association_data);

//    TextureManager::Instance().Add(textureOb);
//}

//####################################### MINERAL_TEXTURE ################################
//{
//    jeti::Material material_data;
//    material_data.texture_path = DATA_PATH+"asteroid/m_000.png";
//    material_data.use_alpha = true;
//    jeti::TextureOb* textureOb = new jeti::TextureOb(material_data);

//    jeti::MaterialAssociationData association_data;
//    association_data.type_id = TYPE::TEXTURE::MINERAL_ID;
//    textureOb->SetAssociation(association_data);

//    TextureManager::Instance().Add(textureOb);
//}

//{
//    jeti::Material material_data;
//    material_data.texture_path = DATA_PATH+"asteroid/m_001.png";
//    material_data.use_alpha = true;
//    jeti::TextureOb* textureOb = new jeti::TextureOb(material_data);

//    jeti::MaterialAssociationData association_data;
//    association_data.type_id = TYPE::TEXTURE::MINERAL_ID;
//    textureOb->SetAssociation(association_data);

//    TextureManager::Instance().Add(textureOb);
//}

//{
//    jeti::Material material_data;
//    material_data.texture_path = DATA_PATH+"asteroid/m_002.png";
//    material_data.use_alpha = true;
//    jeti::TextureOb* textureOb = new jeti::TextureOb(material_data);

//    jeti::MaterialAssociationData association_data;
//    association_data.type_id = TYPE::TEXTURE::MINERAL_ID;
//    textureOb->SetAssociation(association_data);

//    TextureManager::Instance().Add(textureOb);
//}

//{
//    jeti::Material material_data;
//    material_data.texture_path = DATA_PATH+"item/container.png";
//    material_data.use_alpha = true;
//    jeti::TextureOb* textureOb = new jeti::TextureOb(material_data);

//    jeti::MaterialAssociationData association_data;
//    association_data.type_id = TYPE::TEXTURE::CONTAINER_ID;
//    textureOb->SetAssociation(association_data);

//    TextureManager::Instance().Add(textureOb);
//}

//{
//    jeti::Material material_data;
//    material_data.texture_path = DATA_PATH+"item/bomb_item.png";
//    material_data.use_alpha = true;
//    jeti::TextureOb* textureOb = new jeti::TextureOb(material_data);

//    jeti::MaterialAssociationData association_data;
//    association_data.type_id = TYPE::TEXTURE::BOMB_ID;
//    textureOb->SetAssociation(association_data);

//    TextureManager::Instance().Add(textureOb);
//}



//####################################### TYPE::TEXTURE::SATELLITE_ID ################################
//{
//    jeti::Material material_data;
//    material_data.texture_path = DATA_PATH+"satellite/sa_001.png";
//    material_data.use_alpha = true;
//    material_data.col_num = 3;
//    material_data.row_num = 1;
//    material_data.fps = 6.0;
//    jeti::TextureOb* textureOb = new jeti::TextureOb(material_data);

//    jeti::MaterialAssociationData association_data;
//    association_data.type_id = TYPE::TEXTURE::SATELLITE_ID;
//    association_data.race_id = TYPE::RACE::R0_ID;
//    textureOb->SetAssociation(association_data);

//    TextureManager::Instance().Add(textureOb);
//}

//{
//    jeti::Material material_data;
//    material_data.texture_path = DATA_PATH+"satellite/sa_002.png";
//    material_data.use_alpha = true;
//    material_data.col_num = 4;
//    material_data.row_num = 1;
//    material_data.fps = 8.0;
//    jeti::TextureOb* textureOb = new jeti::TextureOb(material_data);

//    jeti::MaterialAssociationData association_data;
//    association_data.type_id = TYPE::TEXTURE::SATELLITE_ID;
//    association_data.race_id = TYPE::RACE::R0_ID;
//    textureOb->SetAssociation(association_data);

//    TextureManager::Instance().Add(textureOb);
//}

//{
//    jeti::Material material_data;
//    material_data.texture_path = DATA_PATH+"satellite/sa_003.png";
//    material_data.use_alpha = true;
//    material_data.col_num = 3;
//    material_data.row_num = 1;
//    material_data.fps = 6.0;
//    jeti::TextureOb* textureOb = new jeti::TextureOb(material_data);

//    jeti::MaterialAssociationData association_data;
//    association_data.type_id = TYPE::TEXTURE::SATELLITE_ID;
//    association_data.race_id = TYPE::RACE::R0_ID;
//    textureOb->SetAssociation(association_data);

//    TextureManager::Instance().Add(textureOb);
//}

//{
//    jeti::Material material_data;
//    material_data.texture_path = DATA_PATH+"satellite/sa_004.png";
//    material_data.use_alpha = true;
//    material_data.col_num = 4;
//    material_data.row_num = 1;
//    material_data.fps = 8.0;
//    jeti::TextureOb* textureOb = new jeti::TextureOb(material_data);

//    jeti::MaterialAssociationData association_data;
//    association_data.type_id = TYPE::TEXTURE::SATELLITE_ID;
//    association_data.race_id = TYPE::RACE::R0_ID;
//    textureOb->SetAssociation(association_data);

//    TextureManager::Instance().Add(textureOb);
//}

//{
//    jeti::Material material_data;
//    material_data.texture_path = DATA_PATH+"satellite/sa_005.png";
//    material_data.use_alpha = true;
//    material_data.col_num = 8;
//    material_data.row_num = 1;
//    material_data.fps = 16.0;
//    jeti::TextureOb* textureOb = new jeti::TextureOb(material_data);

//    jeti::MaterialAssociationData association_data;
//    association_data.type_id = TYPE::TEXTURE::SATELLITE_ID;
//    association_data.race_id = TYPE::RACE::R0_ID;
//    textureOb->SetAssociation(association_data);

//    TextureManager::Instance().Add(textureOb);
//}

//{
//    jeti::Material material_data;
//    material_data.texture_path = DATA_PATH+"satellite/sa_006.png";
//    material_data.use_alpha = true;
//    material_data.col_num = 8;
//    material_data.row_num = 1;
//    material_data.fps = 16.0;
//    jeti::TextureOb* textureOb = new jeti::TextureOb(material_data);

//    jeti::MaterialAssociationData association_data;
//    association_data.type_id = TYPE::TEXTURE::SATELLITE_ID;
//    association_data.race_id = TYPE::RACE::R0_ID;
//    textureOb->SetAssociation(association_data);

//    TextureManager::Instance().Add(textureOb);
//}


// BLACKHOLE
//{
//    jeti::Material material_data;
//    material_data.texture_path = DATA_PATH+"blackhole/bh_00.png";
//    jeti::TextureOb* textureOb = new jeti::TextureOb(material_data);

//    jeti::MaterialAssociationData association_data;
//    association_data.type_id = TYPE::TEXTURE::BLACKHOLE_ID;
//    textureOb->SetAssociation(association_data);

//    TextureManager::Instance().Add(textureOb);
//}

//####################################### SHIP_TEXTURE ####################################
//################################ race texnologi
//{
//    jeti::Material material_data;
//    material_data.texture_path = DATA_PATH+"ship/k_00_0_0.png";
//    material_data.use_alpha = true;
//    jeti::TextureOb* textureOb = new jeti::TextureOb(material_data);

//    jeti::MaterialAssociationData association_data;
//    association_data.type_id    = TYPE::TEXTURE::SHIP_ID;
//    association_data.subtype_id = TYPE::ENTITY::RANGER_ID;
//    association_data.race_id    = TYPE::RACE::R0_ID;
//    textureOb->SetAssociation(association_data);

//    TextureManager::Instance().Add(textureOb);
//}

//{
//    jeti::Material material_data;
//    material_data.texture_path = DATA_PATH+"ship/k_01_0_1.png";
//    material_data.use_alpha = true;
//    jeti::TextureOb* textureOb = new jeti::TextureOb(material_data);

//    jeti::MaterialAssociationData association_data;
//    association_data.type_id    = TYPE::TEXTURE::SHIP_ID;
//    association_data.subtype_id = TYPE::ENTITY::WARRIOR_ID;
//    association_data.race_id    = TYPE::RACE::R0_ID;
//    textureOb->SetAssociation(association_data);

//    TextureManager::Instance().Add(textureOb);
//}

//{
//    jeti::Material material_data;
//    material_data.texture_path = DATA_PATH+"ship/k_02_0_0.png";
//    material_data.use_alpha = true;
//    jeti::TextureOb* textureOb = new jeti::TextureOb(material_data);

//    jeti::MaterialAssociationData association_data;
//    association_data.type_id    = TYPE::TEXTURE::SHIP_ID;
//    association_data.subtype_id = TYPE::ENTITY::PIRAT_ID;
//    association_data.race_id    = TYPE::RACE::R0_ID;
//    textureOb->SetAssociation(association_data);

//    TextureManager::Instance().Add(textureOb);
//}

//{
//    jeti::Material material_data;
//    material_data.texture_path = DATA_PATH+"ship/k_03_0_0.png";
//    material_data.use_alpha = true;
//    jeti::TextureOb* textureOb = new jeti::TextureOb(material_data);

//    jeti::MaterialAssociationData association_data;
//    association_data.type_id    = TYPE::TEXTURE::SHIP_ID;
//    association_data.subtype_id = TYPE::ENTITY::TRADER_ID;
//    association_data.race_id    = TYPE::RACE::R0_ID;
//    textureOb->SetAssociation(association_data);

//    TextureManager::Instance().Add(textureOb);
//}

//{
//    jeti::Material material_data;
//    material_data.texture_path = DATA_PATH+"ship/k_04_0_0.png";
//    material_data.use_alpha = true;
//    jeti::TextureOb* textureOb = new jeti::TextureOb(material_data);

//    jeti::MaterialAssociationData association_data;
//    association_data.type_id    = TYPE::TEXTURE::SHIP_ID;
//    association_data.subtype_id = TYPE::ENTITY::DIPLOMAT_ID;
//    association_data.race_id    = TYPE::RACE::R0_ID;
//    textureOb->SetAssociation(association_data);

//    TextureManager::Instance().Add(textureOb);
//}

////################################ race voennye
//{
//    jeti::Material material_data;
//    material_data.texture_path = DATA_PATH+"ship/k_10_0_0.png";
//    material_data.use_alpha = true;
//    jeti::TextureOb* textureOb = new jeti::TextureOb(material_data);

//    jeti::MaterialAssociationData association_data;
//    association_data.type_id    = TYPE::TEXTURE::SHIP_ID;
//    association_data.subtype_id = TYPE::ENTITY::RANGER_ID;
//    association_data.race_id    = TYPE::RACE::R1_ID;
//    textureOb->SetAssociation(association_data);

//    TextureManager::Instance().Add(textureOb);
//}

//{
//    jeti::Material material_data;
//    material_data.texture_path = DATA_PATH+"ship/k_11_0_0.png";
//    material_data.use_alpha = true;
//    jeti::TextureOb* textureOb = new jeti::TextureOb(material_data);

//    jeti::MaterialAssociationData association_data;
//    association_data.type_id    = TYPE::TEXTURE::SHIP_ID;
//    association_data.subtype_id = TYPE::ENTITY::WARRIOR_ID;
//    association_data.race_id    = TYPE::RACE::R1_ID;
//    textureOb->SetAssociation(association_data);

//    TextureManager::Instance().Add(textureOb);
//}

//{
//    jeti::Material material_data;
//    material_data.texture_path = DATA_PATH+"ship/k_12_0_0.png";
//    material_data.use_alpha = true;
//    jeti::TextureOb* textureOb = new jeti::TextureOb(material_data);

//    jeti::MaterialAssociationData association_data;
//    association_data.type_id    = TYPE::TEXTURE::SHIP_ID;
//    association_data.subtype_id = TYPE::ENTITY::PIRAT_ID;
//    association_data.race_id    = TYPE::RACE::R1_ID;
//    textureOb->SetAssociation(association_data);

//    TextureManager::Instance().Add(textureOb);
//}

//{
//    jeti::Material material_data;
//    material_data.texture_path = DATA_PATH+"ship/k_12_0_0.png";
//    material_data.use_alpha = true;
//    jeti::TextureOb* textureOb = new jeti::TextureOb(material_data);

//    jeti::MaterialAssociationData association_data;
//    association_data.type_id    = TYPE::TEXTURE::SHIP_ID;
//    association_data.subtype_id = TYPE::ENTITY::TRADER_ID;
//    association_data.race_id    = TYPE::RACE::R1_ID;
//    textureOb->SetAssociation(association_data);

//    TextureManager::Instance().Add(textureOb);
//}

//{
//    jeti::Material material_data;
//    material_data.texture_path = DATA_PATH+"ship/k_14_0_0.png";
//    material_data.use_alpha = true;
//    jeti::TextureOb* textureOb = new jeti::TextureOb(material_data);

//    jeti::MaterialAssociationData association_data;
//    association_data.type_id    = TYPE::TEXTURE::SHIP_ID;
//    association_data.subtype_id = TYPE::ENTITY::DIPLOMAT_ID;
//    association_data.race_id    = TYPE::RACE::R1_ID;
//    textureOb->SetAssociation(association_data);

//    TextureManager::Instance().Add(textureOb);
//}

////################################ race zhuliki
//{
//    jeti::Material material_data;
//    material_data.texture_path = DATA_PATH+"ship/race2_ranger_00.png";
//    material_data.use_alpha = true;
//    jeti::TextureOb* textureOb = new jeti::TextureOb(material_data);

//    jeti::MaterialAssociationData association_data;
//    association_data.type_id    = TYPE::TEXTURE::SHIP_ID;
//    association_data.subtype_id = TYPE::ENTITY::RANGER_ID;
//    association_data.race_id    = TYPE::RACE::R2_ID;
//    textureOb->SetAssociation(association_data);

//    TextureManager::Instance().Add(textureOb);
//}

//{
//    jeti::Material material_data;
//    material_data.texture_path = DATA_PATH+"ship/race2_warrior_00.png";
//    material_data.use_alpha = true;
//    jeti::TextureOb* textureOb = new jeti::TextureOb(material_data);

//    jeti::MaterialAssociationData association_data;
//    association_data.type_id    = TYPE::TEXTURE::SHIP_ID;
//    association_data.subtype_id = TYPE::ENTITY::WARRIOR_ID;
//    association_data.race_id    = TYPE::RACE::R2_ID;
//    textureOb->SetAssociation(association_data);

//    TextureManager::Instance().Add(textureOb);
//}

//{
//    jeti::Material material_data;
//    material_data.texture_path = DATA_PATH+"ship/race2_trader_00.png";
//    material_data.use_alpha = true;
//    jeti::TextureOb* textureOb = new jeti::TextureOb(material_data);

//    jeti::MaterialAssociationData association_data;
//    association_data.type_id    = TYPE::TEXTURE::SHIP_ID;
//    association_data.subtype_id = TYPE::ENTITY::TRADER_ID;
//    association_data.race_id    = TYPE::RACE::R2_ID;
//    textureOb->SetAssociation(association_data);

//    TextureManager::Instance().Add(textureOb);
//}

//{
//    jeti::Material material_data;
//    material_data.texture_path = DATA_PATH+"ship/race2_pirat_00.png";
//    material_data.use_alpha = true;
//    jeti::TextureOb* textureOb = new jeti::TextureOb(material_data);

//    jeti::MaterialAssociationData association_data;
//    association_data.type_id    = TYPE::TEXTURE::SHIP_ID;
//    association_data.subtype_id = TYPE::ENTITY::PIRAT_ID;
//    association_data.race_id    = TYPE::RACE::R2_ID;
//    textureOb->SetAssociation(association_data);

//    TextureManager::Instance().Add(textureOb);
//}

//{
//    jeti::Material material_data;
//    material_data.texture_path = DATA_PATH+"ship/race2_diplomat_00.png";
//    material_data.use_alpha = true;
//    jeti::TextureOb* textureOb = new jeti::TextureOb(material_data);

//    jeti::MaterialAssociationData association_data;
//    association_data.type_id    = TYPE::TEXTURE::SHIP_ID;
//    association_data.subtype_id = TYPE::ENTITY::DIPLOMAT_ID;
//    association_data.race_id    = TYPE::RACE::R2_ID;
//    textureOb->SetAssociation(association_data);

//    TextureManager::Instance().Add(textureOb);
//}

////################################ race cheloveki
//{
//    jeti::Material material_data;
//    material_data.texture_path = DATA_PATH+"ship/k_30_0_0.png";
//    material_data.use_alpha = true;
//    jeti::TextureOb* textureOb = new jeti::TextureOb(material_data);

//    jeti::MaterialAssociationData association_data;
//    association_data.type_id    = TYPE::TEXTURE::SHIP_ID;
//    association_data.subtype_id = TYPE::ENTITY::RANGER_ID;
//    association_data.race_id    = TYPE::RACE::R3_ID;
//    textureOb->SetAssociation(association_data);

//    TextureManager::Instance().Add(textureOb);
//}

//{
//    jeti::Material material_data;
//    material_data.texture_path = DATA_PATH+"ship/k_31_0_0.png";
//    material_data.use_alpha = true;
//    jeti::TextureOb* textureOb = new jeti::TextureOb(material_data);

//    jeti::MaterialAssociationData association_data;
//    association_data.type_id    = TYPE::TEXTURE::SHIP_ID;
//    association_data.subtype_id = TYPE::ENTITY::WARRIOR_ID;
//    association_data.race_id    = TYPE::RACE::R3_ID;
//    textureOb->SetAssociation(association_data);

//    TextureManager::Instance().Add(textureOb);
//}

//{
//    jeti::Material material_data;
//    material_data.texture_path = DATA_PATH+"ship/k_31_0_1.png";
//    material_data.use_alpha = true;
//    jeti::TextureOb* textureOb = new jeti::TextureOb(material_data);

//    jeti::MaterialAssociationData association_data;
//    association_data.type_id    = TYPE::TEXTURE::SHIP_ID;
//    association_data.subtype_id = TYPE::ENTITY::WARRIOR_ID;
//    association_data.race_id    = TYPE::RACE::R3_ID;
//    textureOb->SetAssociation(association_data);

//    TextureManager::Instance().Add(textureOb);
//}

//{
//    jeti::Material material_data;
//    material_data.texture_path = DATA_PATH+"ship/k_32_0_0.png";
//    material_data.use_alpha = true;
//    jeti::TextureOb* textureOb = new jeti::TextureOb(material_data);

//    jeti::MaterialAssociationData association_data;
//    association_data.type_id    = TYPE::TEXTURE::SHIP_ID;
//    association_data.subtype_id = TYPE::ENTITY::PIRAT_ID;
//    association_data.race_id    = TYPE::RACE::R3_ID;
//    textureOb->SetAssociation(association_data);

//    TextureManager::Instance().Add(textureOb);
//}

//{
//    jeti::Material material_data;
//    material_data.texture_path = DATA_PATH+"ship/_k_33_0_0.png";
//    material_data.use_alpha = true;
//    jeti::TextureOb* textureOb = new jeti::TextureOb(material_data);

//    jeti::MaterialAssociationData association_data;
//    association_data.type_id    = TYPE::TEXTURE::SHIP_ID;
//    association_data.subtype_id = TYPE::ENTITY::TRADER_ID;
//    association_data.race_id    = TYPE::RACE::R3_ID;
//    textureOb->SetAssociation(association_data);

//    TextureManager::Instance().Add(textureOb);
//}

//{
//    jeti::Material material_data;
//    material_data.texture_path = DATA_PATH+"ship/_k_34_0_0.png";
//    material_data.use_alpha = true;
//    jeti::TextureOb* textureOb = new jeti::TextureOb(material_data);

//    jeti::MaterialAssociationData association_data;
//    association_data.type_id    = TYPE::TEXTURE::SHIP_ID;
//    association_data.subtype_id = TYPE::ENTITY::DIPLOMAT_ID;
//    association_data.race_id    = TYPE::RACE::R3_ID;
//    textureOb->SetAssociation(association_data);

//    TextureManager::Instance().Add(textureOb);
//}

////################################ race bio
//{
//    jeti::Material material_data;
//    material_data.texture_path = DATA_PATH+"ship/k_41_0_0.png";
//    material_data.use_alpha = true;
//    jeti::TextureOb* textureOb = new jeti::TextureOb(material_data);

//    jeti::MaterialAssociationData association_data;
//    association_data.type_id    = TYPE::TEXTURE::SHIP_ID;
//    association_data.subtype_id = TYPE::ENTITY::WARRIOR_ID;
//    association_data.race_id    = TYPE::RACE::R4_ID;
//    textureOb->SetAssociation(association_data);

//    TextureManager::Instance().Add(textureOb);
//}

//{
//    jeti::Material material_data;
//    material_data.texture_path = DATA_PATH+"ship/k_43_0_0.png";
//    material_data.use_alpha = true;
//    jeti::TextureOb* textureOb = new jeti::TextureOb(material_data);

//    jeti::MaterialAssociationData association_data;
//    association_data.type_id    = TYPE::TEXTURE::SHIP_ID;
//    association_data.subtype_id = TYPE::ENTITY::TRADER_ID;
//    association_data.race_id    = TYPE::RACE::R4_ID;
//    textureOb->SetAssociation(association_data);

//    TextureManager::Instance().Add(textureOb);
//}

//{
//    jeti::Material material_data;
//    material_data.texture_path = DATA_PATH+"ship/k_43_0_1.png";
//    material_data.use_alpha = true;
//    jeti::TextureOb* textureOb = new jeti::TextureOb(material_data);

//    jeti::MaterialAssociationData association_data;
//    association_data.type_id    = TYPE::TEXTURE::SHIP_ID;
//    association_data.subtype_id = TYPE::ENTITY::TRADER_ID;
//    association_data.race_id    = TYPE::RACE::R4_ID;
//    textureOb->SetAssociation(association_data);

//    TextureManager::Instance().Add(textureOb);
//}

//{
//    jeti::Material material_data;
//    material_data.texture_path = DATA_PATH+"ship/k_44_0_0.png";
//    material_data.use_alpha = true;
//    jeti::TextureOb* textureOb = new jeti::TextureOb(material_data);

//    jeti::MaterialAssociationData association_data;
//    association_data.type_id    = TYPE::TEXTURE::SHIP_ID;
//    association_data.subtype_id = TYPE::ENTITY::DIPLOMAT_ID;
//    association_data.race_id    = TYPE::RACE::R4_ID;
//    textureOb->SetAssociation(association_data);

//    TextureManager::Instance().Add(textureOb);
//}

////################################ enemy 1
//{
//    jeti::Material material_data;
//    material_data.texture_path = DATA_PATH+"ship/k_61_0_0.png";
//    material_data.use_alpha = true;
//    jeti::TextureOb* textureOb = new jeti::TextureOb(material_data);

//    jeti::MaterialAssociationData association_data;
//    association_data.type_id    = TYPE::TEXTURE::SHIP_ID;
//    association_data.subtype_id = TYPE::ENTITY::WARRIOR_ID;
//    association_data.race_id    = TYPE::RACE::R6_ID;
//    textureOb->SetAssociation(association_data);

//    TextureManager::Instance().Add(textureOb);
//}

//{
//    jeti::Material material_data;
//    material_data.texture_path = DATA_PATH+"ship/k_61_0_1.png";
//    material_data.use_alpha = true;
//    jeti::TextureOb* textureOb = new jeti::TextureOb(material_data);

//    jeti::MaterialAssociationData association_data;
//    association_data.type_id    = TYPE::TEXTURE::SHIP_ID;
//    association_data.subtype_id = TYPE::ENTITY::WARRIOR_ID;
//    association_data.race_id    = TYPE::RACE::R6_ID;
//    textureOb->SetAssociation(association_data);

//    TextureManager::Instance().Add(textureOb);
//}

//{
//    jeti::Material material_data;
//    material_data.texture_path = DATA_PATH+"ship/k_61_0_2.png";
//    material_data.use_alpha = true;
//    jeti::TextureOb* textureOb = new jeti::TextureOb(material_data);

//    jeti::MaterialAssociationData association_data;
//    association_data.type_id    = TYPE::TEXTURE::SHIP_ID;
//    association_data.subtype_id = TYPE::ENTITY::WARRIOR_ID;
//    association_data.race_id    = TYPE::RACE::R6_ID;
//    textureOb->SetAssociation(association_data);

//    TextureManager::Instance().Add(textureOb);
//}


////{
//    //std::vector<int> arg;
//    //arg.push_back((int)TYPE::RACE::R6_ID); arg.push_back((int)TYPE::ENTITY::WARRIOR_ID); //COLOR_GOLDENROD
//    //TextureManager::Instance().Add( new jeti::TextureOb(TYPE::TEXTURE::SHIP_ID, DATA_PATH+"ship/k_61_0_3.png", true, &arg) );
////}


////{
//    //std::vector<int> arg;
//    //arg.push_back((int)TYPE::RACE::R6_ID); arg.push_back((int)TYPE::ENTITY::WARRIOR_ID); //COLOR_GOLDENROD
//    //TextureManager::Instance().Add( new jeti::TextureOb(TYPE::TEXTURE::SHIP_ID, DATA_PATH+"ship/k_61_0_5.png", true, &arg) );
////}

////{
//    //std::vector<int> arg;
//    //arg.push_back((int)TYPE::RACE::R6_ID); arg.push_back((int)TYPE::ENTITY::WARRIOR_ID); //COLOR_GOLDENROD
//    //TextureManager::Instance().Add( new jeti::TextureOb(TYPE::TEXTURE::SHIP_ID, DATA_PATH+"ship/k_61_0_6.png", true, &arg) );
////}

////{
//    //std::vector<int> arg;
//    //arg.push_back((int)TYPE::RACE::R6_ID); arg.push_back((int)TYPE::ENTITY::WARRIOR_ID); //COLOR_GOLDENROD
//    //TextureManager::Instance().Add( new jeti::TextureOb(TYPE::TEXTURE::SHIP_ID, DATA_PATH+"ship/k_61_0_7.png", true, &arg) );
////}

////{
//    //std::vector<int> arg;
//    //arg.push_back((int)TYPE::RACE::R6_ID); arg.push_back((int)TYPE::ENTITY::WARRIOR_ID); //COLOR_GOLDENROD
//    //TextureManager::Instance().Add( new jeti::TextureOb(TYPE::TEXTURE::SHIP_ID, DATA_PATH+"ship/k_61_0_8.png", true, &arg) );
////}

////{
//    //std::vector<int> arg;
//    //arg.push_back((int)TYPE::RACE::R6_ID); arg.push_back((int)TYPE::ENTITY::WARRIOR_ID); //COLOR_GOLDENROD
//    //TextureManager::Instance().Add( new jeti::TextureOb(TYPE::TEXTURE::SHIP_ID, DATA_PATH+"ship/k_61_0_9.png", true, &arg) );
////}

////{
//    //std::vector<int> arg;
//    //arg.push_back((int)TYPE::RACE::R6_ID); arg.push_back((int)TYPE::ENTITY::WARRIOR_ID); //COLOR_GOLDENROD
//    //TextureManager::Instance().Add( new jeti::TextureOb(TYPE::TEXTURE::SHIP_ID, DATA_PATH+"ship/k_61_0_10.png", true, &arg) );
////}

////{
//    //std::vector<int> arg;
//    //arg.push_back((int)TYPE::RACE::R6_ID); arg.push_back((int)TYPE::ENTITY::WARRIOR_ID); //COLOR_GOLDENROD
//    //TextureManager::Instance().Add( new jeti::TextureOb(TYPE::TEXTURE::SHIP_ID, DATA_PATH+"ship/k_61_0_11.png", true, &arg) );
////}

////{
//    //std::vector<int> arg;
//    //arg.push_back((int)TYPE::RACE::R6_ID); arg.push_back((int)TYPE::ENTITY::WARRIOR_ID); //COLOR_GOLDENROD
//    //TextureManager::Instance().Add( new jeti::TextureOb(TYPE::TEXTURE::SHIP_ID, DATA_PATH+"ship/k_61_0_12.png", true, &arg) );
////}



////################################ enemy 2
//{
//    jeti::Material material_data;
//    material_data.texture_path = DATA_PATH+"ship/k_71_0_0.png";
//    material_data.use_alpha = true;
//    jeti::TextureOb* textureOb = new jeti::TextureOb(material_data);

//    jeti::MaterialAssociationData association_data;
//    association_data.type_id    = TYPE::TEXTURE::SHIP_ID;
//    association_data.subtype_id = TYPE::ENTITY::WARRIOR_ID;
//    association_data.race_id    = TYPE::RACE::R7_ID;
//    textureOb->SetAssociation(association_data);

//    TextureManager::Instance().Add(textureOb);
//}

//{
//    jeti::Material material_data;
//    material_data.texture_path = DATA_PATH+"ship/k_71_0_1e.png";
//    material_data.use_alpha = true;
//    jeti::TextureOb* textureOb = new jeti::TextureOb(material_data);

//    jeti::MaterialAssociationData association_data;
//    association_data.type_id    = TYPE::TEXTURE::SHIP_ID;
//    association_data.subtype_id = TYPE::ENTITY::WARRIOR_ID;
//    association_data.race_id    = TYPE::RACE::R7_ID;
//    textureOb->SetAssociation(association_data);

//    TextureManager::Instance().Add(textureOb);
//}

////################################# TYPE::TEXTURE::STAR_ID ###############################
//{
//    jeti::Material material_data;
//    material_data.texture_path = DATA_PATH+"star/s_000.jpg";
//    material_data.brightThreshold = 1.9f;
//    material_data.color_id = COLOR::YELLOW_ID;
//    jeti::TextureOb* textureOb = new jeti::TextureOb(material_data);

//    jeti::MaterialAssociationData association_data;
//    association_data.type_id    = TYPE::TEXTURE::STAR_ID;
//    textureOb->SetAssociation(association_data);

//    TextureManager::Instance().Add(textureOb);
//}

//{
//    jeti::Material material_data;
//    material_data.texture_path = DATA_PATH+"star/s_001.png";
//    material_data.brightThreshold = 1.825f;
//    material_data.color_id = COLOR::YELLOW_ID;
//    jeti::TextureOb* textureOb = new jeti::TextureOb(material_data);

//    jeti::MaterialAssociationData association_data;
//    association_data.type_id    = TYPE::TEXTURE::STAR_ID;
//    textureOb->SetAssociation(association_data);

//    TextureManager::Instance().Add(textureOb);
//}

//{
//    jeti::Material material_data;
//    material_data.texture_path = DATA_PATH+"star/s_100.jpg";
//    material_data.brightThreshold = 2.525f;
//    material_data.color_id = COLOR::BLUE_ID;
//    jeti::TextureOb* textureOb = new jeti::TextureOb(material_data);

//    jeti::MaterialAssociationData association_data;
//    association_data.type_id    = TYPE::TEXTURE::STAR_ID;
//    textureOb->SetAssociation(association_data);

//    TextureManager::Instance().Add(textureOb);
//}

//{
//    jeti::Material material_data;
//    material_data.texture_path = DATA_PATH+"star/s_101.png";
//    material_data.brightThreshold = 1.925f;
//    material_data.color_id = COLOR::BLUE_ID;
//    jeti::TextureOb* textureOb = new jeti::TextureOb(material_data);

//    jeti::MaterialAssociationData association_data;
//    association_data.type_id    = TYPE::TEXTURE::STAR_ID;
//    textureOb->SetAssociation(association_data);

//    TextureManager::Instance().Add(textureOb);
//}

//// STARBASE_TEXTURE_ID
//{
//    jeti::Material material_data;
//    material_data.texture_path = DATA_PATH+"starbase/sb_000.png";
//    material_data.use_alpha = true;
//    jeti::TextureOb* textureOb = new jeti::TextureOb(material_data);

//    jeti::MaterialAssociationData association_data;
//    association_data.type_id    = TYPE::TEXTURE::SPACESTATION_ID;
//    association_data.race_id    = TYPE::RACE::R0_ID;
//    textureOb->SetAssociation(association_data);

//    TextureManager::Instance().Add(textureOb);
//}

//{
//    jeti::Material material_data;
//    material_data.texture_path = DATA_PATH+"starbase/sb_001.png";
//    material_data.use_alpha = true;
//    jeti::TextureOb* textureOb = new jeti::TextureOb(material_data);

//    jeti::MaterialAssociationData association_data;
//    association_data.type_id    = TYPE::TEXTURE::SPACESTATION_ID;
//    association_data.race_id    = TYPE::RACE::R0_ID;
//    textureOb->SetAssociation(association_data);

//    TextureManager::Instance().Add(textureOb);
//}

//{
//    jeti::Material material_data;
//    material_data.texture_path = DATA_PATH+"starbase/sb_002.png";
//    material_data.use_alpha = true;
//    jeti::TextureOb* textureOb = new jeti::TextureOb(material_data);

//    jeti::MaterialAssociationData association_data;
//    association_data.type_id    = TYPE::TEXTURE::SPACESTATION_ID;
//    association_data.race_id    = TYPE::RACE::R0_ID;
//    textureOb->SetAssociation(association_data);

//    TextureManager::Instance().Add(textureOb);
//}

//{
//    jeti::Material material_data;
//    material_data.texture_path = DATA_PATH+"starbase/sb_003.png";
//    material_data.use_alpha = true;
//    jeti::TextureOb* textureOb = new jeti::TextureOb(material_data);

//    jeti::MaterialAssociationData association_data;
//    association_data.type_id    = TYPE::TEXTURE::SPACESTATION_ID;
//    association_data.race_id    = TYPE::RACE::R0_ID;
//    textureOb->SetAssociation(association_data);

//    TextureManager::Instance().Add(textureOb);
//}


////################################## NEBULA EFFECT ################################
//{
//    jeti::Material material_data;
//    material_data.texture_path = DATA_PATH+"bg_space/nebula.bak/nebula1.png";
//    material_data.use_alpha = true;
//    material_data.color_id = COLOR::RED_ID;
//    material_data.is_rotated = false;
//    jeti::TextureOb* textureOb = new jeti::TextureOb(material_data);

//    jeti::MaterialAssociationData association_data;
//    association_data.type_id    = TYPE::TEXTURE::NEBULA_BACKGROUND_ID;
//    textureOb->SetAssociation(association_data);

//    TextureManager::Instance().Add(textureOb);
//}

//{
//    jeti::Material material_data;
//    material_data.texture_path = DATA_PATH+"bg_space/nebula.bak/nebula2.png";
//    material_data.use_alpha = true;
//    material_data.color_id = COLOR::GREEN_ID;
//    material_data.is_rotated = true;
//    jeti::TextureOb* textureOb = new jeti::TextureOb(material_data);

//    jeti::MaterialAssociationData association_data;
//    association_data.type_id    = TYPE::TEXTURE::NEBULA_BACKGROUND_ID;
//    textureOb->SetAssociation(association_data);

//    TextureManager::Instance().Add(textureOb);
//}

//{
//    jeti::Material material_data;
//    material_data.texture_path = DATA_PATH+"bg_space/nebula.bak/nebula3.png";
//    material_data.use_alpha = true;
//    material_data.color_id = COLOR::YELLOW_ID;
//    material_data.is_rotated = false;
//    jeti::TextureOb* textureOb = new jeti::TextureOb(material_data);

//    jeti::MaterialAssociationData association_data;
//    association_data.type_id    = TYPE::TEXTURE::NEBULA_BACKGROUND_ID;
//    textureOb->SetAssociation(association_data);

//    TextureManager::Instance().Add(textureOb);
//}

//{
//    jeti::Material material_data;
//    material_data.texture_path = DATA_PATH+"bg_space/nebula.bak/nebula4.png";
//    material_data.use_alpha = true;
//    material_data.color_id = COLOR::BLUE_ID;
//    material_data.is_rotated = true;
//    jeti::TextureOb* textureOb = new jeti::TextureOb(material_data);

//    jeti::MaterialAssociationData association_data;
//    association_data.type_id    = TYPE::TEXTURE::NEBULA_BACKGROUND_ID;
//    textureOb->SetAssociation(association_data);

//    TextureManager::Instance().Add(textureOb);
//}

//{
//    jeti::Material material_data;
//    material_data.texture_path = DATA_PATH+"bg_space/nebula.bak/nebula5.png";
//    material_data.use_alpha = true;
//    material_data.color_id = COLOR::YELLOW_ID;
//    material_data.is_rotated = false;
//    jeti::TextureOb* textureOb = new jeti::TextureOb(material_data);

//    jeti::MaterialAssociationData association_data;
//    association_data.type_id    = TYPE::TEXTURE::NEBULA_BACKGROUND_ID;
//    textureOb->SetAssociation(association_data);

//    TextureManager::Instance().Add(textureOb);
//}

//{
//    jeti::Material material_data;
//    material_data.texture_path = DATA_PATH+"bg_space/nebula.bak/nebula6.png";
//    material_data.use_alpha = true;
//    material_data.color_id = COLOR::RED_ID;
//    material_data.is_rotated = false;
//    jeti::TextureOb* textureOb = new jeti::TextureOb(material_data);

//    jeti::MaterialAssociationData association_data;
//    association_data.type_id    = TYPE::TEXTURE::NEBULA_BACKGROUND_ID;
//    textureOb->SetAssociation(association_data);

//    TextureManager::Instance().Add(textureOb);
//}

//{
//    jeti::Material material_data;
//    material_data.texture_path = DATA_PATH+"bg_space/nebula.bak/nebula7.png";
//    material_data.use_alpha = true;
//    material_data.color_id = COLOR::BLUE_ID;
//    material_data.is_rotated = false;
//    jeti::TextureOb* textureOb = new jeti::TextureOb(material_data);

//    jeti::MaterialAssociationData association_data;
//    association_data.type_id    = TYPE::TEXTURE::NEBULA_BACKGROUND_ID;
//    textureOb->SetAssociation(association_data);

//    TextureManager::Instance().Add(textureOb);
//}

//{
//    jeti::Material material_data;
//    material_data.texture_path = DATA_PATH+"bg_space/nebula.bak/nebula8.png";
//    material_data.use_alpha = true;
//    material_data.color_id = COLOR::BLUE_ID;
//    material_data.is_rotated = true;
//    jeti::TextureOb* textureOb = new jeti::TextureOb(material_data);

//    jeti::MaterialAssociationData association_data;
//    association_data.type_id    = TYPE::TEXTURE::NEBULA_BACKGROUND_ID;
//    textureOb->SetAssociation(association_data);

//    TextureManager::Instance().Add(textureOb);
//}

//{
//    jeti::Material material_data;
//    material_data.texture_path = DATA_PATH+"bg_space/nebula.bak/nebula9.png";
//    material_data.use_alpha = true;
//    material_data.color_id = COLOR::BLUE_ID;
//    material_data.is_rotated = true;
//    jeti::TextureOb* textureOb = new jeti::TextureOb(material_data);

//    jeti::MaterialAssociationData association_data;
//    association_data.type_id    = TYPE::TEXTURE::NEBULA_BACKGROUND_ID;
//    textureOb->SetAssociation(association_data);

//    TextureManager::Instance().Add(textureOb);
//}

//{
//    jeti::Material material_data;
//    material_data.texture_path = DATA_PATH+"bg_space/nebula.bak/nebula10.png";
//    material_data.use_alpha = true;
//    material_data.color_id = COLOR::RED_ID;
//    material_data.is_rotated = false;
//    jeti::TextureOb* textureOb = new jeti::TextureOb(material_data);

//    jeti::MaterialAssociationData association_data;
//    association_data.type_id    = TYPE::TEXTURE::NEBULA_BACKGROUND_ID;
//    textureOb->SetAssociation(association_data);

//    TextureManager::Instance().Add(textureOb);
//}

//{
//    jeti::Material material_data;
//    material_data.texture_path = DATA_PATH+"bg_space/nebula.bak/nebula11.png";
//    material_data.use_alpha = true;
//    material_data.color_id = COLOR::YELLOW_ID;
//    material_data.is_rotated = false;
//    jeti::TextureOb* textureOb = new jeti::TextureOb(material_data);

//    jeti::MaterialAssociationData association_data;
//    association_data.type_id    = TYPE::TEXTURE::NEBULA_BACKGROUND_ID;
//    textureOb->SetAssociation(association_data);

//    TextureManager::Instance().Add(textureOb);
//}

//{
//    jeti::Material material_data;
//    material_data.texture_path = DATA_PATH+"bg_space/nebula.bak/nebula12.png";
//    material_data.use_alpha = true;
//    material_data.color_id = COLOR::BLUE_ID;
//    material_data.is_rotated = false;
//    jeti::TextureOb* textureOb = new jeti::TextureOb(material_data);

//    jeti::MaterialAssociationData association_data;
//    association_data.type_id    = TYPE::TEXTURE::NEBULA_BACKGROUND_ID;
//    textureOb->SetAssociation(association_data);

//    TextureManager::Instance().Add(textureOb);
//}

//{
//    jeti::Material material_data;
//    material_data.texture_path = DATA_PATH+"bg_space/nebula.bak/nebula13.png";
//    material_data.use_alpha = true;
//    material_data.color_id = COLOR::BLUE_ID;
//    material_data.is_rotated = false;
//    jeti::TextureOb* textureOb = new jeti::TextureOb(material_data);

//    jeti::MaterialAssociationData association_data;
//    association_data.type_id    = TYPE::TEXTURE::NEBULA_BACKGROUND_ID;
//    textureOb->SetAssociation(association_data);

//    TextureManager::Instance().Add(textureOb);
//}

//{
//    jeti::Material material_data;
//    material_data.texture_path = DATA_PATH+"bg_space/nebula.bak/nebula14.png";
//    material_data.use_alpha = true;
//    material_data.color_id = COLOR::RED_ID;
//    material_data.is_rotated = true;
//    jeti::TextureOb* textureOb = new jeti::TextureOb(material_data);

//    jeti::MaterialAssociationData association_data;
//    association_data.type_id    = TYPE::TEXTURE::NEBULA_BACKGROUND_ID;
//    textureOb->SetAssociation(association_data);

//    TextureManager::Instance().Add(textureOb);
//}

//{
//    jeti::Material material_data;
//    material_data.texture_path = DATA_PATH+"bg_space/nebula.bak/nebula15.png";
//    material_data.use_alpha = true;
//    material_data.color_id = COLOR::YELLOW_ID;
//    material_data.is_rotated = true;
//    jeti::TextureOb* textureOb = new jeti::TextureOb(material_data);

//    jeti::MaterialAssociationData association_data;
//    association_data.type_id    = TYPE::TEXTURE::NEBULA_BACKGROUND_ID;
//    textureOb->SetAssociation(association_data);

//    TextureManager::Instance().Add(textureOb);
//}

//{
//    jeti::Material material_data;
//    material_data.texture_path = DATA_PATH+"bg_space/nebula.bak/nebula16.png";
//    material_data.use_alpha = true;
//    material_data.color_id = COLOR::YELLOW_ID;
//    material_data.is_rotated = false;
//    jeti::TextureOb* textureOb = new jeti::TextureOb(material_data);

//    jeti::MaterialAssociationData association_data;
//    association_data.type_id    = TYPE::TEXTURE::NEBULA_BACKGROUND_ID;
//    textureOb->SetAssociation(association_data);

//    TextureManager::Instance().Add(textureOb);
//}

//{
//    jeti::Material material_data;
//    material_data.texture_path = DATA_PATH+"bg_space/nebula.bak/nebula17.png";
//    material_data.use_alpha = true;
//    material_data.color_id = COLOR::YELLOW_ID;
//    material_data.is_rotated = false;
//    jeti::TextureOb* textureOb = new jeti::TextureOb(material_data);

//    jeti::MaterialAssociationData association_data;
//    association_data.type_id    = TYPE::TEXTURE::NEBULA_BACKGROUND_ID;
//    textureOb->SetAssociation(association_data);

//    TextureManager::Instance().Add(textureOb);
//}

//{
//    jeti::Material material_data;
//    material_data.texture_path = DATA_PATH+"bg_space/nebula.bak/nebula18.png";
//    material_data.use_alpha = true;
//    material_data.color_id = COLOR::YELLOW_ID;
//    material_data.is_rotated = false;
//    jeti::TextureOb* textureOb = new jeti::TextureOb(material_data);

//    jeti::MaterialAssociationData association_data;
//    association_data.type_id    = TYPE::TEXTURE::NEBULA_BACKGROUND_ID;
//    textureOb->SetAssociation(association_data);

//    TextureManager::Instance().Add(textureOb);
//}

//{
//    jeti::Material material_data;
//    material_data.texture_path = DATA_PATH+"bg_space/nebula.bak/nebula19.png";
//    material_data.use_alpha = true;
//    material_data.color_id = COLOR::RED_ID;
//    material_data.is_rotated = false;
//    jeti::TextureOb* textureOb = new jeti::TextureOb(material_data);

//    jeti::MaterialAssociationData association_data;
//    association_data.type_id    = TYPE::TEXTURE::NEBULA_BACKGROUND_ID;
//    textureOb->SetAssociation(association_data);

//    TextureManager::Instance().Add(textureOb);
//}
////### size 2 = 512x512
////### size 4 = 1024x1024 or 512x1024

////################################ TYPE::TEXTURE::LAND_BACKGROUND_ID ###################################
//{
//    jeti::Material material_data;
//    material_data.texture_path = DATA_PATH+"bg_uninhabited/b_000.jpg";
//    jeti::TextureOb* textureOb = new jeti::TextureOb(material_data);

//    jeti::MaterialAssociationData association_data;
//    association_data.type_id    = TYPE::TEXTURE::NATURELAND_BACKGROUND_ID;
//    textureOb->SetAssociation(association_data);

//    TextureManager::Instance().Add(textureOb);
//}

//{
//    jeti::Material material_data;
//    material_data.texture_path = DATA_PATH+"bg_uninhabited/b_001.png";
//    jeti::TextureOb* textureOb = new jeti::TextureOb(material_data);

//    jeti::MaterialAssociationData association_data;
//    association_data.type_id    = TYPE::TEXTURE::NATURELAND_BACKGROUND_ID;
//    textureOb->SetAssociation(association_data);

//    TextureManager::Instance().Add(textureOb);
//}

//{
//    jeti::Material material_data;
//    material_data.texture_path = DATA_PATH+"bg_uninhabited/b_002.png";
//    jeti::TextureOb* textureOb = new jeti::TextureOb(material_data);

//    jeti::MaterialAssociationData association_data;
//    association_data.type_id    = TYPE::TEXTURE::NATURELAND_BACKGROUND_ID;
//    textureOb->SetAssociation(association_data);

//    TextureManager::Instance().Add(textureOb);
//}

////################################ KOSMOPORT_BG_TEXTURE_ID ###############################
//{
//    jeti::Material material_data;
//    material_data.texture_path = DATA_PATH+"bg_kosmoport/an_000.jpg";
//    jeti::TextureOb* textureOb = new jeti::TextureOb(material_data);

//    jeti::MaterialAssociationData association_data;
//    association_data.type_id    = TYPE::TEXTURE::ANGAR_BACKGROUND_ID;
//    association_data.race_id    = TYPE::RACE::R0_ID;
//    textureOb->SetAssociation(association_data);

//    TextureManager::Instance().Add(textureOb);
//}

//{
//    jeti::Material material_data;
//    material_data.texture_path = DATA_PATH+"bg_kosmoport/st_000.jpg";
//    jeti::TextureOb* textureOb = new jeti::TextureOb(material_data);

//    jeti::MaterialAssociationData association_data;
//    association_data.type_id    = TYPE::TEXTURE::STORE_BACKGROUND_ID;
//    association_data.race_id    = TYPE::RACE::R0_ID;
//    textureOb->SetAssociation(association_data);

//    TextureManager::Instance().Add(textureOb);
//}

//{
//    jeti::Material material_data;
//    material_data.texture_path = DATA_PATH+"bg_kosmoport/sh_000.jpg";
//    jeti::TextureOb* textureOb = new jeti::TextureOb(material_data);

//    jeti::MaterialAssociationData association_data;
//    association_data.type_id    = TYPE::TEXTURE::SHOP_BACKGROUND_ID;
//    association_data.race_id    = TYPE::RACE::R0_ID;
//    textureOb->SetAssociation(association_data);

//    TextureManager::Instance().Add(textureOb);
//}

//{
//    jeti::Material material_data;
//    material_data.texture_path = DATA_PATH+"bg_kosmoport/go_000.jpg";
//    jeti::TextureOb* textureOb = new jeti::TextureOb(material_data);

//    jeti::MaterialAssociationData association_data;
//    association_data.type_id    = TYPE::TEXTURE::GOVERMENT_BACKGROUND_ID;
//    association_data.race_id    = TYPE::RACE::R0_ID;
//    textureOb->SetAssociation(association_data);

//    TextureManager::Instance().Add(textureOb);
//}


////################################ PLANET_TEXTURE ####################################
//{
//    jeti::Material material_data;
//    material_data.texture_path      = DATA_PATH+"planet/p_0000.png";
//    material_data.normalmap_path    = DATA_PATH+"planet/p_0000_nm.png";
//    jeti::TextureOb* textureOb = new jeti::TextureOb(material_data);

//    jeti::MaterialAssociationData association_data;
//    association_data.type_id    = TYPE::TEXTURE::PLANET_ID;
//    association_data.subtype_id = TYPE::ENTITY::PLANET_MIXED_ID;
//    textureOb->SetAssociation(association_data);

//    TextureManager::Instance().Add(textureOb);
//}

//{
//    jeti::Material material_data;
//    material_data.texture_path      = DATA_PATH+"planet/p_1000.png";
//    material_data.normalmap_path    = DATA_PATH+"planet/p_1000_nm.png";
//    jeti::TextureOb* textureOb = new jeti::TextureOb(material_data);

//    jeti::MaterialAssociationData association_data;
//    association_data.type_id    = TYPE::TEXTURE::PLANET_ID;
//    association_data.subtype_id = TYPE::ENTITY::PLANET_WATER_ID;
//    textureOb->SetAssociation(association_data);

//    TextureManager::Instance().Add(textureOb);
//}

//{
//    jeti::Material material_data;
//    material_data.texture_path      = DATA_PATH+"planet/p_2000.png";
//    material_data.normalmap_path    = DATA_PATH+"planet/p_2000_nm.png";
//    jeti::TextureOb* textureOb = new jeti::TextureOb(material_data);

//    jeti::MaterialAssociationData association_data;
//    association_data.type_id    = TYPE::TEXTURE::PLANET_ID;
//    association_data.subtype_id = TYPE::ENTITY::PLANET_VULCANIC_ID;
//    textureOb->SetAssociation(association_data);

//    TextureManager::Instance().Add(textureOb);

//}

//{
//    jeti::Material material_data;
//    material_data.texture_path      = DATA_PATH+"planet/p_3000.png";
//    material_data.normalmap_path    = DATA_PATH+"planet/p_3000_nm.png";
//    jeti::TextureOb* textureOb = new jeti::TextureOb(material_data);

//    jeti::MaterialAssociationData association_data;
//    association_data.type_id    = TYPE::TEXTURE::PLANET_ID;
//    association_data.subtype_id = TYPE::ENTITY::PLANET_ICE_ID;
//    textureOb->SetAssociation(association_data);

//    TextureManager::Instance().Add(textureOb);
//}

//{
//    jeti::Material material_data;
//    material_data.texture_path      = DATA_PATH+"planet/p_4000.png";
//    material_data.normalmap_path    = DATA_PATH+"planet/p_4000_nm.png";
//    jeti::TextureOb* textureOb = new jeti::TextureOb(material_data);

//    jeti::MaterialAssociationData association_data;
//    association_data.type_id    = TYPE::TEXTURE::PLANET_ID;
//    association_data.subtype_id = TYPE::ENTITY::PLANET_GAS_ID;
//    textureOb->SetAssociation(association_data);

//    TextureManager::Instance().Add(textureOb);
//}

////################################ ATMOSPHERE_TEXTURE ####################################
//{
//    jeti::Material material_data;
//    material_data.texture_path = DATA_PATH+"planet/atmosphere_000.png";
//    material_data.use_alpha = true;
//    jeti::TextureOb* textureOb = new jeti::TextureOb(material_data);

//    jeti::MaterialAssociationData association_data;
//    association_data.type_id    = TYPE::TEXTURE::ATMOSPHERE_ID;
//    textureOb->SetAssociation(association_data);

//    TextureManager::Instance().Add(textureOb);
//}

//{
//    jeti::Material material_data;
//    material_data.texture_path = DATA_PATH+"planet/atmosphere_001.png";
//    material_data.use_alpha = true;
//    jeti::TextureOb* textureOb = new jeti::TextureOb(material_data);

//    jeti::MaterialAssociationData association_data;
//    association_data.type_id    = TYPE::TEXTURE::ATMOSPHERE_ID;
//    textureOb->SetAssociation(association_data);

//    TextureManager::Instance().Add(textureOb);
//}

////################################ RING_TEXTURE ####################################
//{
//    jeti::Material material_data;
//    material_data.texture_path = DATA_PATH+"planet/ring.png";
//    material_data.use_alpha = true;
//    jeti::TextureOb* textureOb = new jeti::TextureOb(material_data);

//    jeti::MaterialAssociationData association_data;
//    association_data.type_id    = TYPE::TEXTURE::RING_ID;
//    textureOb->SetAssociation(association_data);

//    TextureManager::Instance().Add(textureOb);
//}

////################################ EFFECTS TEXTURE ###################################
//{
//    jeti::Material material_data;
//    material_data.texture_path = DATA_PATH+"effect/particles/particle0.png";
//    material_data.use_alpha = true;
//    material_data.color_id = COLOR::RED_ID;
//    jeti::TextureOb* textureOb = new jeti::TextureOb(material_data);

//    jeti::MaterialAssociationData association_data;
//    association_data.type_id    = TYPE::TEXTURE::PARTICLE_EFFECT_ID;
//    textureOb->SetAssociation(association_data);

//    TextureManager::Instance().Add(textureOb);
//}

//{
//    jeti::Material material_data;
//    material_data.texture_path = DATA_PATH+"effect/particles/particle1.png";
//    material_data.use_alpha = true;
//    material_data.color_id = COLOR::BLUE_ID;
//    jeti::TextureOb* textureOb = new jeti::TextureOb(material_data);

//    jeti::MaterialAssociationData association_data;
//    association_data.type_id    = TYPE::TEXTURE::PARTICLE_EFFECT_ID;
//    textureOb->SetAssociation(association_data);

//    TextureManager::Instance().Add(textureOb);
//}

//{
//    jeti::Material material_data;
//    material_data.texture_path = DATA_PATH+"effect/particles/particle2.png";
//    material_data.use_alpha = true;
//    material_data.color_id = COLOR::YELLOW_ID;
//    jeti::TextureOb* textureOb = new jeti::TextureOb(material_data);

//    jeti::MaterialAssociationData association_data;
//    association_data.type_id    = TYPE::TEXTURE::PARTICLE_EFFECT_ID;
//    textureOb->SetAssociation(association_data);

//    TextureManager::Instance().Add(textureOb);
//}

//{
//    jeti::Material material_data;
//    material_data.texture_path = DATA_PATH+"effect/particles/particle3.png";
//    material_data.use_alpha = true;
//    material_data.color_id = COLOR::GREY_ID;
//    jeti::TextureOb* textureOb = new jeti::TextureOb(material_data);

//    jeti::MaterialAssociationData association_data;
//    association_data.type_id    = TYPE::TEXTURE::PARTICLE_EFFECT_ID;
//    textureOb->SetAssociation(association_data);

//    TextureManager::Instance().Add(textureOb);
//}

////{
//    //std::vector<int> arg;
//    //arg.push_back((int)TYPE::TECHLEVEL::L0_ID); arg.push_back(COLOR::BLUE_ID);
//    //TextureManager::Instance().Add( new jeti::TextureOb(TYPE::TEXTURE::LAZER_EFFECT_ID, DATA_PATH+"effect/lazer/l_64_26_000.png", true, &arg, 4, 1, 10) );
////}

//{
//    jeti::Material material_data;
//    material_data.texture_path = DATA_PATH+"effect/lazer/l_001.png";
//    material_data.use_alpha = true;
//    material_data.color_id = COLOR::RED_ID;
//    jeti::TextureOb* textureOb = new jeti::TextureOb(material_data);

//    jeti::MaterialAssociationData association_data;
//    association_data.type_id        = TYPE::TEXTURE::LAZER_EFFECT_ID;
//    association_data.tech_level_id  = TYPE::TECHLEVEL::L0_ID;
//    textureOb->SetAssociation(association_data);

//    TextureManager::Instance().Add(textureOb);
//}

//{
//    jeti::Material material_data;
//    material_data.texture_path = DATA_PATH+"effect/lazer/l_002.png";
//    material_data.use_alpha = true;
//    material_data.color_id = COLOR::YELLOW_ID;
//    jeti::TextureOb* textureOb = new jeti::TextureOb(material_data);

//    jeti::MaterialAssociationData association_data;
//    association_data.type_id        = TYPE::TEXTURE::LAZER_EFFECT_ID;
//    association_data.tech_level_id  = TYPE::TECHLEVEL::L0_ID;
//    textureOb->SetAssociation(association_data);

//    TextureManager::Instance().Add(textureOb);
//}

//{
//    jeti::Material material_data;
//    material_data.texture_path = DATA_PATH+"effect/lazer/l_003.png";
//    material_data.use_alpha = true;
//    material_data.color_id = COLOR::BLUE_ID;
//    jeti::TextureOb* textureOb = new jeti::TextureOb(material_data);

//    jeti::MaterialAssociationData association_data;
//    association_data.type_id        = TYPE::TEXTURE::LAZER_EFFECT_ID;
//    association_data.tech_level_id  = TYPE::TECHLEVEL::L0_ID;
//    textureOb->SetAssociation(association_data);

//    TextureManager::Instance().Add(textureOb);
//}

//{
//    jeti::Material material_data;
//    material_data.texture_path = DATA_PATH+"effect/shield/shield0.png";
//    material_data.use_alpha = true;
//    material_data.color_id = COLOR::RED_ID;
//    jeti::TextureOb* textureOb = new jeti::TextureOb(material_data);

//    jeti::MaterialAssociationData association_data;
//    association_data.type_id        = TYPE::TEXTURE::SHIELD_EFFECT_ID;
//    textureOb->SetAssociation(association_data);

//    TextureManager::Instance().Add(textureOb);
//}

//{
//    jeti::Material material_data;
//    material_data.texture_path = DATA_PATH+"effect/shield/shield1.png";
//    material_data.use_alpha = true;
//    material_data.color_id = COLOR::GREEN_ID;
//    jeti::TextureOb* textureOb = new jeti::TextureOb(material_data);

//    jeti::MaterialAssociationData association_data;
//    association_data.type_id        = TYPE::TEXTURE::SHIELD_EFFECT_ID;
//    textureOb->SetAssociation(association_data);

//    TextureManager::Instance().Add(textureOb);
//}

//{
//    jeti::Material material_data;
//    material_data.texture_path = DATA_PATH+"effect/shield/shield2.png";
//    material_data.use_alpha = true;
//    material_data.color_id = COLOR::BLUE_ID;
//    jeti::TextureOb* textureOb = new jeti::TextureOb(material_data);

//    jeti::MaterialAssociationData association_data;
//    association_data.type_id        = TYPE::TEXTURE::SHIELD_EFFECT_ID;
//    textureOb->SetAssociation(association_data);

//    TextureManager::Instance().Add(textureOb);
//}

//{
//    jeti::Material material_data;
//    material_data.texture_path = DATA_PATH+"effect/shield/shield3.png";
//    material_data.use_alpha = true;
//    material_data.color_id = COLOR::YELLOW_ID;
//    jeti::TextureOb* textureOb = new jeti::TextureOb(material_data);

//    jeti::MaterialAssociationData association_data;
//    association_data.type_id        = TYPE::TEXTURE::SHIELD_EFFECT_ID;
//    textureOb->SetAssociation(association_data);

//    TextureManager::Instance().Add(textureOb);
//}


//// TYPE::TEXTURE::DISTANTSTAR_ID
//{
//    jeti::Material material_data;
//    material_data.texture_path = DATA_PATH+"star/s1.png";
//    material_data.use_alpha = true;
//    material_data.color_id = COLOR::YELLOW_ID;
//    jeti::TextureOb* textureOb = new jeti::TextureOb(material_data);

//    jeti::MaterialAssociationData association_data;
//    association_data.type_id        = TYPE::TEXTURE::DISTANTSTAR_ID;
//    textureOb->SetAssociation(association_data);

//    TextureManager::Instance().Add(textureOb);
//}

//{
//    jeti::Material material_data;
//    material_data.texture_path = DATA_PATH+"star/s2.png";
//    material_data.use_alpha = true;
//    material_data.color_id = COLOR::BLUE_ID;
//    jeti::TextureOb* textureOb = new jeti::TextureOb(material_data);

//    jeti::MaterialAssociationData association_data;
//    association_data.type_id        = TYPE::TEXTURE::DISTANTSTAR_ID;
//    textureOb->SetAssociation(association_data);

//    TextureManager::Instance().Add(textureOb);
//}

//{
//    jeti::Material material_data;
//    material_data.texture_path = DATA_PATH+"star/s3.png";
//    material_data.use_alpha = true;
//    material_data.color_id = COLOR::RED_ID;
//    jeti::TextureOb* textureOb = new jeti::TextureOb(material_data);

//    jeti::MaterialAssociationData association_data;
//    association_data.type_id        = TYPE::TEXTURE::DISTANTSTAR_ID;
//    textureOb->SetAssociation(association_data);

//    TextureManager::Instance().Add(textureOb);
//}

////###################################### ITEM TEXTURE ###################################
////############################ DRIVE_ITEM
////#################### RACE_0
////####### TECH_LEVEL_0
//{
//    jeti::Material material_data;
//    material_data.texture_path = DATA_PATH+"item/drive/drive_Race0_Tech0.png";
//    material_data.use_alpha = true;
//    jeti::TextureOb* textureOb = new jeti::TextureOb(material_data);

//    jeti::MaterialAssociationData association_data;
//    association_data.type_id        = TYPE::TEXTURE::DRIVE_EQUIPMENT_ID;
//    association_data.race_id        = TYPE::RACE::R0_ID;
//    association_data.tech_level_id  = TYPE::TECHLEVEL::L0_ID;
//    textureOb->SetAssociation(association_data);

//    TextureManager::Instance().Add(textureOb);
//}

////####### TECH_LEVEL_1
//{
//    jeti::Material material_data;
//    material_data.texture_path = DATA_PATH+"item/drive/drive_Race0_Tech1.png";
//    material_data.use_alpha = true;
//    jeti::TextureOb* textureOb = new jeti::TextureOb(material_data);

//    jeti::MaterialAssociationData association_data;
//    association_data.type_id        = TYPE::TEXTURE::DRIVE_EQUIPMENT_ID;
//    association_data.race_id        = TYPE::RACE::R0_ID;
//    association_data.tech_level_id  = TYPE::TECHLEVEL::L1_ID;
//    textureOb->SetAssociation(association_data);

//    TextureManager::Instance().Add(textureOb);
//}

////####### TECH_LEVEL_2
//{
//    jeti::Material material_data;
//    material_data.texture_path = DATA_PATH+"item/drive/drive_Race0_Tech2.png";
//    material_data.use_alpha = true;
//    jeti::TextureOb* textureOb = new jeti::TextureOb(material_data);

//    jeti::MaterialAssociationData association_data;
//    association_data.type_id        = TYPE::TEXTURE::DRIVE_EQUIPMENT_ID;
//    association_data.race_id        = TYPE::RACE::R0_ID;
//    association_data.tech_level_id  = TYPE::TECHLEVEL::L2_ID;
//    textureOb->SetAssociation(association_data);

//    TextureManager::Instance().Add(textureOb);
//}

////#################### RACE1
////#################### RACE2
////#################### RACE3
////#################### RACE4

////#################### RACE6
////#################### RACE7



////############################ LAZER_ITEM
////#################### RACE_0
////####### TECH_LEVEL_0
//{
//    jeti::Material material_data;
//    material_data.texture_path = DATA_PATH+"item/lazer/lazer_Race0_Tech0_Red0.png";
//    material_data.use_alpha = true;
//    material_data.color_id = COLOR::RED_ID;
//    jeti::TextureOb* textureOb = new jeti::TextureOb(material_data);

//    jeti::MaterialAssociationData association_data;
//    association_data.type_id        = TYPE::TEXTURE::LAZER_EQUIPMENT_ID;
//    association_data.race_id        = TYPE::RACE::R0_ID;
//    association_data.tech_level_id  = TYPE::TECHLEVEL::L0_ID;
//    textureOb->SetAssociation(association_data);

//    TextureManager::Instance().Add(textureOb);
//}

//{
//    jeti::Material material_data;
//    material_data.texture_path = DATA_PATH+"item/lazer/lazer_Race0_Tech0_Yellow0.png";
//    material_data.use_alpha = true;
//    material_data.color_id = COLOR::YELLOW_ID;
//    jeti::TextureOb* textureOb = new jeti::TextureOb(material_data);

//    jeti::MaterialAssociationData association_data;
//    association_data.type_id        = TYPE::TEXTURE::LAZER_EQUIPMENT_ID;
//    association_data.race_id        = TYPE::RACE::R0_ID;
//    association_data.tech_level_id  = TYPE::TECHLEVEL::L0_ID;
//    textureOb->SetAssociation(association_data);

//    TextureManager::Instance().Add(textureOb);
//}

//{
//    jeti::Material material_data;
//    material_data.texture_path = DATA_PATH+"item/lazer/lazer_Race0_Tech0_Blue0.png";
//    material_data.use_alpha = true;
//    material_data.color_id = COLOR::BLUE_ID;
//    jeti::TextureOb* textureOb = new jeti::TextureOb(material_data);

//    jeti::MaterialAssociationData association_data;
//    association_data.type_id        = TYPE::TEXTURE::LAZER_EQUIPMENT_ID;
//    association_data.race_id        = TYPE::RACE::R0_ID;
//    association_data.tech_level_id  = TYPE::TECHLEVEL::L0_ID;
//    textureOb->SetAssociation(association_data);

//    TextureManager::Instance().Add(textureOb);
//}

////####### TECH_LEVEL_1
//{
//    jeti::Material material_data;
//    material_data.texture_path = DATA_PATH+"item/lazer/lazer_Race0_Tech1_Blue0.png";
//    material_data.use_alpha = true;
//    material_data.color_id = COLOR::BLUE_ID;
//    jeti::TextureOb* textureOb = new jeti::TextureOb(material_data);

//    jeti::MaterialAssociationData association_data;
//    association_data.type_id        = TYPE::TEXTURE::LAZER_EQUIPMENT_ID;
//    association_data.race_id        = TYPE::RACE::R0_ID;
//    association_data.tech_level_id  = TYPE::TECHLEVEL::L1_ID;
//    textureOb->SetAssociation(association_data);

//    TextureManager::Instance().Add(textureOb);
//}
////#################### RACE_1
////#################### RACE_2
////#################### RACE_3
////#################### RACE_4

////#################### RACE_6
////#################### RACE_7



////############################ ROCKET_ITEM
////#################### RACE_0
////####### TECH_LEVEL_0
//{
//    jeti::Material material_data;
//    material_data.texture_path = DATA_PATH+"item/rocket/rocket_Race0_Tech0.png";
//    material_data.use_alpha = true;
//    jeti::TextureOb* textureOb = new jeti::TextureOb(material_data);

//    jeti::MaterialAssociationData association_data;
//    association_data.type_id        = TYPE::TEXTURE::ROCKET_EQUIPMENT_ID;
//    association_data.race_id        = TYPE::RACE::R0_ID;
//    association_data.tech_level_id  = TYPE::TECHLEVEL::L0_ID;
//    textureOb->SetAssociation(association_data);

//    TextureManager::Instance().Add(textureOb);
//}
////####### TECH_LEVEL_1
//{
//    jeti::Material material_data;
//    material_data.texture_path = DATA_PATH+"item/rocket/rocket_Race0_Tech1.png";
//    material_data.use_alpha = true;
//    jeti::TextureOb* textureOb = new jeti::TextureOb(material_data);

//    jeti::MaterialAssociationData association_data;
//    association_data.type_id        = TYPE::TEXTURE::ROCKET_EQUIPMENT_ID;
//    association_data.race_id        = TYPE::RACE::R0_ID;
//    association_data.tech_level_id  = TYPE::TECHLEVEL::L1_ID;
//    textureOb->SetAssociation(association_data);

//    TextureManager::Instance().Add(textureOb);
//}
////####### TECH_LEVEL_2
//{
//    jeti::Material material_data;
//    material_data.texture_path = DATA_PATH+"item/rocket/rocket_Race0_Tech2.png";
//    material_data.use_alpha = true;
//    jeti::TextureOb* textureOb = new jeti::TextureOb(material_data);

//    jeti::MaterialAssociationData association_data;
//    association_data.type_id        = TYPE::TEXTURE::ROCKET_EQUIPMENT_ID;
//    association_data.race_id        = TYPE::RACE::R0_ID;
//    association_data.tech_level_id  = TYPE::TECHLEVEL::L2_ID;
//    textureOb->SetAssociation(association_data);

//    TextureManager::Instance().Add(textureOb);
//}

////TEXTURE_MANAGER.manageItem( textureOb(TORPED_ITEM_TEXTURE_ID, 'data/item/torped/tl0.png', True, [ 'torpedo',       TYPE::TECHLEVEL::L0_ID, 3, 1, (int)TYPE::RACE::R0_ID, COLOR::YELLOW_ID]) )
////TEXTURE_MANAGER.manageItem( textureOb(TORPED_ITEM_TEXTURE_ID, 'data/item/torped/tl1.png', True, [ 'torpedo',       TYPE::TECHLEVEL::L0_ID, 3, 1, (int)TYPE::RACE::R0_ID, COLOR::YELLOW_ID]) )

//{
//    jeti::Material material_data;
//    material_data.texture_path = DATA_PATH+"bullet/r_0.png";
//    material_data.use_alpha = true;
//    jeti::TextureOb* textureOb = new jeti::TextureOb(material_data);

//    jeti::MaterialAssociationData association_data;
//    association_data.type_id        = TYPE::TEXTURE::ROCKET_BULLET_ID;
//    textureOb->SetAssociation(association_data);

//    TextureManager::Instance().Add(textureOb);
//}

//{
//    jeti::Material material_data;
//    material_data.texture_path = DATA_PATH+"bullet/r_1.png";
//    material_data.use_alpha = true;
//    jeti::TextureOb* textureOb = new jeti::TextureOb(material_data);

//    jeti::MaterialAssociationData association_data;
//    association_data.type_id        = TYPE::TEXTURE::ROCKET_BULLET_ID;
//    textureOb->SetAssociation(association_data);

//    TextureManager::Instance().Add(textureOb);
//}

////{
//    //std::vector<int> arg;
//    //TextureManager::Instance().Add( new jeti::TextureOb(TYPE::TEXTURE::ROCKET_BULLET_ID, DATA_PATH+"bullet/t_0.png", true, &arg) );
////}

////{
//    //std::vector<int> arg;
//    //TextureManager::Instance().Add( new jeti::TextureOb(TYPE::TEXTURE::ROCKET_BULLET_ID, DATA_PATH+"bullet/t_1.png", true, &arg) );
////}
////TEXTURE_MANAGER.manage( textureOb(TORPED_BULLET_TEXTURE_ID, 'data/bullet/t_0.png', True, []) )
////TEXTURE_MANAGER.manage( textureOb(TORPED_BULLET_TEXTURE_ID, 'data/bullet/t_1.png', True, []) )



////############################ PROTECTOR_EQUIPMENT
////#################### RACE_0
////####### TECH_LEVEL_0
//{
//    jeti::Material material_data;
//    material_data.texture_path = DATA_PATH+"item/protector/protector_Race0_Tech0.png";
//    material_data.use_alpha = true;
//    jeti::TextureOb* textureOb = new jeti::TextureOb(material_data);

//    jeti::MaterialAssociationData association_data;
//    association_data.type_id        = TYPE::TEXTURE::PROTECTOR_EQUIPMENT_ID;
//    association_data.race_id        = TYPE::RACE::R0_ID;
//    association_data.tech_level_id  = TYPE::TECHLEVEL::L0_ID;
//    textureOb->SetAssociation(association_data);

//    TextureManager::Instance().Add(textureOb);
//}

////####### TECH_LEVEL_1
//{
//    jeti::Material material_data;
//    material_data.texture_path = DATA_PATH+"item/protector/protector_Race0_Tech1.png";
//    material_data.use_alpha = true;
//    jeti::TextureOb* textureOb = new jeti::TextureOb(material_data);

//    jeti::MaterialAssociationData association_data;
//    association_data.type_id        = TYPE::TEXTURE::PROTECTOR_EQUIPMENT_ID;
//    association_data.race_id        = TYPE::RACE::R0_ID;
//    association_data.tech_level_id  = TYPE::TECHLEVEL::L1_ID;
//    textureOb->SetAssociation(association_data);

//    TextureManager::Instance().Add(textureOb);
//}

////####### TECH_LEVEL_2
//{
//    jeti::Material material_data;
//    material_data.texture_path = DATA_PATH+"item/protector/protector_Race0_Tech2.png";
//    material_data.use_alpha = true;
//    jeti::TextureOb* textureOb = new jeti::TextureOb(material_data);

//    jeti::MaterialAssociationData association_data;
//    association_data.type_id        = TYPE::TEXTURE::PROTECTOR_EQUIPMENT_ID;
//    association_data.race_id        = TYPE::RACE::R0_ID;
//    association_data.tech_level_id  = TYPE::TECHLEVEL::L2_ID;
//    textureOb->SetAssociation(association_data);

//    TextureManager::Instance().Add(textureOb);
//}
////####### TECH_LEVEL_3
//{
//    jeti::Material material_data;
//    material_data.texture_path = DATA_PATH+"item/protector/protector_Race0_Tech3.png";
//    material_data.use_alpha = true;
//    jeti::TextureOb* textureOb = new jeti::TextureOb(material_data);

//    jeti::MaterialAssociationData association_data;
//    association_data.type_id        = TYPE::TEXTURE::PROTECTOR_EQUIPMENT_ID;
//    association_data.race_id        = TYPE::RACE::R0_ID;
//    association_data.tech_level_id  = TYPE::TECHLEVEL::L3_ID;
//    textureOb->SetAssociation(association_data);

//    TextureManager::Instance().Add(textureOb);
//}

////############################ DROID_EQUIPMENT
////#################### RACE_0
////####### TECH_LEVEL_0
//{
//    jeti::Material material_data;
//    material_data.texture_path = DATA_PATH+"item/droid/droid_Race0_Tech0.png";
//    material_data.use_alpha = true;
//    jeti::TextureOb* textureOb = new jeti::TextureOb(material_data);

//    jeti::MaterialAssociationData association_data;
//    association_data.type_id        = TYPE::TEXTURE::DROID_EQUIPMENT_ID;
//    association_data.race_id        = TYPE::RACE::R0_ID;
//    association_data.tech_level_id  = TYPE::TECHLEVEL::L0_ID;
//    textureOb->SetAssociation(association_data);

//    TextureManager::Instance().Add(textureOb);
//}

////####### TECH_LEVEL_1
//{
//    jeti::Material material_data;
//    material_data.texture_path = DATA_PATH+"item/droid/droid_Race0_Tech1.png";
//    material_data.use_alpha = true;
//    jeti::TextureOb* textureOb = new jeti::TextureOb(material_data);

//    jeti::MaterialAssociationData association_data;
//    association_data.type_id        = TYPE::TEXTURE::DROID_EQUIPMENT_ID;
//    association_data.race_id        = TYPE::RACE::R0_ID;
//    association_data.tech_level_id  = TYPE::TECHLEVEL::L1_ID;
//    textureOb->SetAssociation(association_data);

//    TextureManager::Instance().Add(textureOb);
//}

////####### TECH_LEVEL_2
//{
//    jeti::Material material_data;
//    material_data.texture_path = DATA_PATH+"item/droid/droid_Race0_Tech2.png";
//    material_data.use_alpha = true;
//    jeti::TextureOb* textureOb = new jeti::TextureOb(material_data);

//    jeti::MaterialAssociationData association_data;
//    association_data.type_id        = TYPE::TEXTURE::DROID_EQUIPMENT_ID;
//    association_data.race_id        = TYPE::RACE::R0_ID;
//    association_data.tech_level_id  = TYPE::TECHLEVEL::L2_ID;
//    textureOb->SetAssociation(association_data);

//    TextureManager::Instance().Add(textureOb);
//}


////############################ GRAPPLE_EQUIPMENT
////#################### RACE_0
////####### TECH_LEVEL_0
//{
//    jeti::Material material_data;
//    material_data.texture_path = DATA_PATH+"item/grapple/grapple_Race0_Tech0.png";
//    material_data.use_alpha = true;
//    jeti::TextureOb* textureOb = new jeti::TextureOb(material_data);

//    jeti::MaterialAssociationData association_data;
//    association_data.type_id        = TYPE::TEXTURE::GRAPPLE_EQUIPMENT_ID;
//    association_data.race_id        = TYPE::RACE::R0_ID;
//    association_data.tech_level_id  = TYPE::TECHLEVEL::L0_ID;
//    textureOb->SetAssociation(association_data);

//    TextureManager::Instance().Add(textureOb);
//}

////####### TECH_LEVEL_1
//{
//    jeti::Material material_data;
//    material_data.texture_path = DATA_PATH+"item/grapple/grapple_Race0_Tech1.png";
//    material_data.use_alpha = true;
//    jeti::TextureOb* textureOb = new jeti::TextureOb(material_data);

//    jeti::MaterialAssociationData association_data;
//    association_data.type_id        = TYPE::TEXTURE::GRAPPLE_EQUIPMENT_ID;
//    association_data.race_id        = TYPE::RACE::R0_ID;
//    association_data.tech_level_id  = TYPE::TECHLEVEL::L1_ID;
//    textureOb->SetAssociation(association_data);

//    TextureManager::Instance().Add(textureOb);
//}



////############################ BAK_EQUIPMENT
////#################### RACE_0
////####### TECH_LEVEL_0
//{
//    jeti::Material material_data;
//    material_data.texture_path = DATA_PATH+"item/bak/bak_Race0_Tech0.png";
//    material_data.use_alpha = true;
//    jeti::TextureOb* textureOb = new jeti::TextureOb(material_data);

//    jeti::MaterialAssociationData association_data;
//    association_data.type_id        = TYPE::TEXTURE::BAK_EQUIPMENT_ID;
//    association_data.race_id        = TYPE::RACE::R0_ID;
//    association_data.tech_level_id  = TYPE::TECHLEVEL::L0_ID;
//    textureOb->SetAssociation(association_data);

//    TextureManager::Instance().Add(textureOb);
//}

////####### TECH_LEVEL_1
//{
//    jeti::Material material_data;
//    material_data.texture_path = DATA_PATH+"item/bak/bak_Race0_Tech1.png";
//    material_data.use_alpha = true;
//    jeti::TextureOb* textureOb = new jeti::TextureOb(material_data);

//    jeti::MaterialAssociationData association_data;
//    association_data.type_id        = TYPE::TEXTURE::BAK_EQUIPMENT_ID;
//    association_data.race_id        = TYPE::RACE::R0_ID;
//    association_data.tech_level_id  = TYPE::TECHLEVEL::L1_ID;
//    textureOb->SetAssociation(association_data);

//    TextureManager::Instance().Add(textureOb);
//}


////############################ ENERGIZER_EQUIPMENT
////#################### RACE_0
////####### TECH_LEVEL_0
//{
//    jeti::Material material_data;
//    material_data.texture_path = DATA_PATH+"item/energyBlock/energyBlock_Race0_Tech0.png";
//    material_data.use_alpha = true;
//    jeti::TextureOb* textureOb = new jeti::TextureOb(material_data);

//    jeti::MaterialAssociationData association_data;
//    association_data.type_id        = TYPE::TEXTURE::ENERGIZER_EQUIPMENT_ID;
//    association_data.race_id        = TYPE::RACE::R0_ID;
//    association_data.tech_level_id  = TYPE::TECHLEVEL::L0_ID;
//    textureOb->SetAssociation(association_data);

//    TextureManager::Instance().Add(textureOb);
//}

////####### TECH_LEVEL_1
//{
//    jeti::Material material_data;
//    material_data.texture_path = DATA_PATH+"item/energyBlock/energyBlock_Race0_Tech1.png";
//    material_data.use_alpha = true;
//    jeti::TextureOb* textureOb = new jeti::TextureOb(material_data);

//    jeti::MaterialAssociationData association_data;
//    association_data.type_id        = TYPE::TEXTURE::ENERGIZER_EQUIPMENT_ID;
//    association_data.race_id        = TYPE::RACE::R0_ID;
//    association_data.tech_level_id  = TYPE::TECHLEVEL::L1_ID;
//    textureOb->SetAssociation(association_data);

//    TextureManager::Instance().Add(textureOb);
//}


////############################ FREEZER_EQUIPMENT
////#################### RACE_0
////####### TECH_LEVEL_0
//{
//    jeti::Material material_data;
//    material_data.texture_path = DATA_PATH+"item/freezer/freezer_Race0_Tech0.png";
//    material_data.use_alpha = true;
//    jeti::TextureOb* textureOb = new jeti::TextureOb(material_data);

//    jeti::MaterialAssociationData association_data;
//    association_data.type_id        = TYPE::TEXTURE::FREEZER_EQUIPMENT_ID;
//    association_data.race_id        = TYPE::RACE::R0_ID;
//    association_data.tech_level_id  = TYPE::TECHLEVEL::L0_ID;
//    textureOb->SetAssociation(association_data);

//    TextureManager::Instance().Add(textureOb);
//}

////####### TECH_LEVEL_1
//{
//    jeti::Material material_data;
//    material_data.texture_path = DATA_PATH+"item/freezer/freezer_Race0_Tech1.png";
//    material_data.use_alpha = true;
//    jeti::TextureOb* textureOb = new jeti::TextureOb(material_data);

//    jeti::MaterialAssociationData association_data;
//    association_data.type_id        = TYPE::TEXTURE::FREEZER_EQUIPMENT_ID;
//    association_data.race_id        = TYPE::RACE::R0_ID;
//    association_data.tech_level_id  = TYPE::TECHLEVEL::L1_ID;
//    textureOb->SetAssociation(association_data);

//    TextureManager::Instance().Add(textureOb);
//}


////############################ SCANER_EQUIPMENT
////#################### RACE_0
////####### TECH_LEVEL_0
//{
//    jeti::Material material_data;
//    material_data.texture_path = DATA_PATH+"item/scaner/scaner_Race0_Tech0.png";
//    material_data.use_alpha = true;
//    material_data.col_num = 3;
//    material_data.row_num = 1;
//    material_data.fps = 3.0f;
//    jeti::TextureOb* textureOb = new jeti::TextureOb(material_data);

//    jeti::MaterialAssociationData association_data;
//    association_data.type_id        = TYPE::TEXTURE::SCANER_EQUIPMENT_ID;
//    association_data.race_id        = TYPE::RACE::R0_ID;
//    association_data.tech_level_id  = TYPE::TECHLEVEL::L0_ID;
//    textureOb->SetAssociation(association_data);

//    TextureManager::Instance().Add(textureOb);
//}
////####### TECH_LEVEL_1
//{
//    jeti::Material material_data;
//    material_data.texture_path = DATA_PATH+"item/scaner/scaner_Race0_Tech1.png";
//    material_data.use_alpha = true;
//    material_data.col_num = 3;
//    material_data.row_num = 1;
//    material_data.fps = 3.0f;
//    jeti::TextureOb* textureOb = new jeti::TextureOb(material_data);

//    jeti::MaterialAssociationData association_data;
//    association_data.type_id        = TYPE::TEXTURE::SCANER_EQUIPMENT_ID;
//    association_data.race_id        = TYPE::RACE::R0_ID;
//    association_data.tech_level_id  = TYPE::TECHLEVEL::L1_ID;
//    textureOb->SetAssociation(association_data);

//    TextureManager::Instance().Add(textureOb);
//}

////############################ RADAR_EQUIPMENT
////#################### RACE_0
////####### TECH_LEVEL_0
//{
//    jeti::Material material_data;
//    material_data.texture_path = DATA_PATH+"item/radar/radar_Race0_Tech0.png";
//    material_data.use_alpha = true;
//    material_data.col_num = 3;
//    material_data.row_num = 1;
//    material_data.fps = 3.0f;
//    jeti::TextureOb* textureOb = new jeti::TextureOb(material_data);

//    jeti::MaterialAssociationData association_data;
//    association_data.type_id        = TYPE::TEXTURE::RADAR_EQUIPMENT_ID;
//    association_data.race_id        = TYPE::RACE::R0_ID;
//    association_data.tech_level_id  = TYPE::TECHLEVEL::L0_ID;
//    textureOb->SetAssociation(association_data);

//    TextureManager::Instance().Add(textureOb);
//}

////####### TECH_LEVEL_1
//{
//    jeti::Material material_data;
//    material_data.texture_path = DATA_PATH+"item/radar/radar_Race0_Tech1.png";
//    material_data.use_alpha = true;
//    material_data.col_num = 3;
//    material_data.row_num = 1;
//    material_data.fps = 3.0f;
//    jeti::TextureOb* textureOb = new jeti::TextureOb(material_data);

//    jeti::MaterialAssociationData association_data;
//    association_data.type_id        = TYPE::TEXTURE::RADAR_EQUIPMENT_ID;
//    association_data.race_id        = TYPE::RACE::R0_ID;
//    association_data.tech_level_id  = TYPE::TECHLEVEL::L1_ID;
//    textureOb->SetAssociation(association_data);

//    TextureManager::Instance().Add(textureOb);
//}


////################## MODULES
//{
//    jeti::Material material_data;
//    material_data.texture_path = DATA_PATH+"item/module.png";
//    material_data.use_alpha = true;
//    jeti::TextureOb* textureOb = new jeti::TextureOb(material_data);

//    jeti::MaterialAssociationData association_data;
//    association_data.type_id = TYPE::TEXTURE::MODULE_ID;
//    textureOb->SetAssociation(association_data);

//    TextureManager::Instance().Add(textureOb);
//}



//// UNIQUE TEXTURES
//{
//    jeti::Material material_data;
//    material_data.texture_path = DATA_PATH+"other/ss_mark_war.png";
//    material_data.use_alpha = true;
//    jeti::TextureOb* textureOb = new jeti::TextureOb(material_data);

//    GuiTextureObCollector::Instance().starsystem_mark_war = textureOb;
//}

//{
//    jeti::Material material_data;
//    material_data.texture_path = DATA_PATH+"other/ss_mark_captured.png";
//    material_data.use_alpha = true;
//    jeti::TextureOb* textureOb = new jeti::TextureOb(material_data);
 
//    GuiTextureObCollector::Instance().starsystem_mark_captured = textureOb;
//}

//{
//    jeti::Material material_data;
//    material_data.texture_path = DATA_PATH+"other/mark_player_ss.png";
//    material_data.use_alpha = true;
//    jeti::TextureOb* textureOb = new jeti::TextureOb(material_data);

//    GuiTextureObCollector::Instance().starsystem_mark_player = textureOb;
//}

//{
//    jeti::Material material_data;
//    material_data.texture_path = DATA_PATH+"icon/minus.png";
//    material_data.use_alpha = true;
//    jeti::TextureOb* textureOb = new jeti::TextureOb(material_data);
 
//    GuiTextureObCollector::Instance().icon_minus = textureOb;
//}

//{
//    jeti::Material material_data;
//    material_data.texture_path = DATA_PATH+"icon/plus.png";
//    material_data.use_alpha = true;
//    jeti::TextureOb* textureOb = new jeti::TextureOb(material_data);

//    GuiTextureObCollector::Instance().icon_plus = textureOb;
//}

//{
//    jeti::Material material_data;
//    material_data.texture_path = DATA_PATH+"other/skill.png";
//    material_data.use_alpha = true;
//    jeti::TextureOb* textureOb = new jeti::TextureOb(material_data);

//    GuiTextureObCollector::Instance().skill = textureOb;
//}

//{
//    jeti::Material material_data;
//    material_data.texture_path = DATA_PATH+"other/skill_transparent.png";
//    material_data.use_alpha = true;
//    jeti::TextureOb* textureOb = new jeti::TextureOb(material_data);
 
//    GuiTextureObCollector::Instance().skill_transparent = textureOb;
//}

//{
//    jeti::Material material_data;
//    material_data.texture_path = DATA_PATH+"icon/starsystem_ICON.png";
//    material_data.use_alpha = true;
//    jeti::TextureOb* textureOb = new jeti::TextureOb(material_data);

//    GuiTextureObCollector::Instance().icon_map = textureOb;
//}

//{
//    jeti::Material material_data;
//    material_data.texture_path = DATA_PATH+"effect/grapple_jet.png";
//    material_data.use_alpha = true;
//    jeti::TextureOb* textureOb = new jeti::TextureOb(material_data);

//    GuiTextureObCollector::Instance().grapple_trail = textureOb;
//}

//{
//    jeti::Material material_data;
//    material_data.texture_path = DATA_PATH+"other/dot_blue.png";
//    material_data.use_alpha = true;
//    jeti::TextureOb* textureOb = new jeti::TextureOb(material_data);
 
//    GuiTextureObCollector::Instance().dot_blue = textureOb;
//}

//{
//    jeti::Material material_data;
//    material_data.texture_path = DATA_PATH+"other/dot_green.png";
//    material_data.use_alpha = true;
//    jeti::TextureOb* textureOb = new jeti::TextureOb(material_data);

//    GuiTextureObCollector::Instance().dot_green = textureOb;
//}

//{
//    jeti::Material material_data;
//    material_data.texture_path = DATA_PATH+"other/dot_red.png";
//    material_data.use_alpha = true;
//    jeti::TextureOb* textureOb = new jeti::TextureOb(material_data);
 
//    GuiTextureObCollector::Instance().dot_red = textureOb;
//}

//{
//    jeti::Material material_data;
//    material_data.texture_path = DATA_PATH+"other/dot_black.png";
//    material_data.use_alpha = true;
//    jeti::TextureOb* textureOb = new jeti::TextureOb(material_data);
 
//    GuiTextureObCollector::Instance().dot_black = textureOb;
//}

//{
//    jeti::Material material_data;
//    material_data.texture_path = DATA_PATH+"other/dot_yellow.png";
//    material_data.use_alpha = true;
//    jeti::TextureOb* textureOb = new jeti::TextureOb(material_data);
  
//    GuiTextureObCollector::Instance().dot_yellow = textureOb;
//}

//{
//    jeti::Material material_data;
//    material_data.texture_path = DATA_PATH+"other/dot_purple.png";
//    material_data.use_alpha = true;
//    jeti::TextureOb* textureOb = new jeti::TextureOb(material_data);
 
//    GuiTextureObCollector::Instance().dot_purple = textureOb;
//}


//{
//    jeti::Material material_data;
//    material_data.texture_path = DATA_PATH+"gui/radar_screenrect.png";
//    material_data.use_alpha = true;
//    jeti::TextureOb* textureOb = new jeti::TextureOb(material_data);

//    GuiTextureObCollector::Instance().radar_screenrect = textureOb;
//}

//{
//    jeti::Material material_data;
//    material_data.texture_path = DATA_PATH+"gui/radar_range.png";
//    material_data.use_alpha = true;
//    jeti::TextureOb* textureOb = new jeti::TextureOb(material_data);

//    GuiTextureObCollector::Instance().radar_range = textureOb;
//}

//{
//    jeti::Material material_data;
//    material_data.texture_path = DATA_PATH+"gui/radar_background.png";
//    material_data.use_alpha = true;
//    jeti::TextureOb* textureOb = new jeti::TextureOb(material_data);
 
//    GuiTextureObCollector::Instance().radar_background = textureOb;
//}

//{
//    jeti::Material material_data;
//    material_data.texture_path = DATA_PATH+"gui/radar_bar.png";
//    material_data.use_alpha = true;
//    jeti::TextureOb* textureOb = new jeti::TextureOb(material_data);

//    GuiTextureObCollector::Instance().radar_bar = textureOb;
//}

//{
//    jeti::Material material_data;
//    material_data.texture_path = DATA_PATH+"gui/bar_bottom.png";
//    material_data.use_alpha = true;
//    jeti::TextureOb* textureOb = new jeti::TextureOb(material_data);

//    GuiTextureObCollector::Instance().bar_bottom = textureOb;
//}

//{
//    jeti::Material material_data;
//    material_data.texture_path = DATA_PATH+"gui/bar_left.png";
//    material_data.use_alpha = true;
//    jeti::TextureOb* textureOb = new jeti::TextureOb(material_data);

//    GuiTextureObCollector::Instance().bar_left = textureOb;
//}

//{
//    jeti::Material material_data;
//    material_data.texture_path = DATA_PATH+"gui/bar_top.png";
//    material_data.use_alpha = true;
//    jeti::TextureOb* textureOb = new jeti::TextureOb(material_data);
 
//    GuiTextureObCollector::Instance().bar_top = textureOb;
//}

//{
//    jeti::Material material_data;
//    material_data.texture_path = DATA_PATH+"other/text_background.png";
//    material_data.use_alpha = true;
//    jeti::TextureOb* textureOb = new jeti::TextureOb(material_data);
  
//    GuiTextureObCollector::Instance().text_background = textureOb;
//}

//{
//    jeti::Material material_data;
//    material_data.texture_path = DATA_PATH+"other/slot_mark_accept.png";
//    material_data.use_alpha = true;
//    jeti::TextureOb* textureOb = new jeti::TextureOb(material_data);
 
//    GuiTextureObCollector::Instance().slot_mark_accept = textureOb;
//}

//{
//    jeti::Material material_data;
//    material_data.texture_path = DATA_PATH+"other/mask_round.png";
//    material_data.use_alpha = true;
//    jeti::TextureOb* textureOb = new jeti::TextureOb(material_data);

//    GuiTextureObCollector::Instance().mask_round = textureOb;
//}

//{
//    jeti::Material material_data;
//    material_data.texture_path = DATA_PATH+"other/slot_mark_reject.png";
//    material_data.use_alpha = true;
//    jeti::TextureOb* textureOb = new jeti::TextureOb(material_data);
 
//    GuiTextureObCollector::Instance().slot_mark_reject = textureOb;
//}

//{
//    jeti::Material material_data;
//    material_data.texture_path = DATA_PATH+"gui/mark_target.png";
//    material_data.use_alpha = true;
//    jeti::TextureOb* textureOb = new jeti::TextureOb(material_data);
  
//    GuiTextureObCollector::Instance().mark_target = textureOb;
//}
 
//{
//    jeti::Material material_data;
//    material_data.texture_path = DATA_PATH+"gui/mark_target_slot.png";
//    material_data.use_alpha = true;
//    jeti::TextureOb* textureOb = new jeti::TextureOb(material_data);

//    GuiTextureObCollector::Instance().mark_target_slot = textureOb;
//}
}


