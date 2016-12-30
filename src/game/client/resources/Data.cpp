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

#include "Data.hpp"
#include <common/constants.hpp>
#include <common/Config.hpp>
#include <common/Global.hpp>
#include <descriptors/DescriptorManager.hpp>

//#include <jeti/ShaderLoader.hpp>
#include <jeti/Mesh.hpp>
//#include <jeti/Screen.hpp>
#include <ceti/descriptor/Collector.hpp>
#include <ceti/FsUtils.hpp>
#include <ceti/MdLoader.hpp>
#include <ceti/StringUtils.hpp>

#include "TextureCollector.hpp"
#include "GuiTextureObCollector.hpp"

#include <ceti/type/IdType.hpp>
#include <types/RaceTypes.hpp>
#include <types/MeshTypes.hpp>
#include <types/TechLevelTypes.hpp>

#include <core/types/TextureTypes.hpp>

#include <string>

namespace {
const std::string DATA_PATH = "data/";
const std::string CONFIG_PATH  = "";
} // namespace

Data::Data()
{
    type::init();

    __collectMeshDescriptors();
    __loadImages();
}

Data::~Data()
{
}


void Data::__generate()
{
    __collectMeshDescriptors();
    __loadImages();
}

void Data::__collectMeshDescriptors()
{        
    using namespace ceti::descriptor;

//    auto& dm = global::get().descriptors();
//    if (!dm.mesh().loaded()) {
//        dm.add(Mesh( int(type::mesh::PLANE_ID), "plane/plane.obj", "", meti::vec3(0.0f, 0.0f, 1.0f)) );
//        dm.add(Mesh( int(type::mesh::SPHERE_ID), "sphere/sphere.obj"));
//        dm.add(Mesh( int(type::mesh::SPHERE_DEFORMED_ID), "sphere_deformed/sphere_deformed.obj") );
    
//        dm.add(Mesh( int(type::mesh::SPACESTATION_ID), "vehicles/BabylonStation/babylon_station_mod.obj", "vehicles/BabylonStation/station_texture/babylonstation.jpg") );
//        dm.add(Mesh( int(type::mesh::SPACESTATION_ID), "vehicles/Anna_V_2.0_variations/anna_mod.obj", "vehicles/Anna_V_2.0_variations/Anna_Textures/ship_hull12.jpg") );

//        dm.mesh().save();
//    }

//    auto& dm = global::get().descriptors();
//    if (!dm.mesh().loaded()) {
//        ceti::Collector<Mesh> collector("mesh_descriptors.txt");

//        auto result = ceti::filesystem::getFilesList("/workspace/src/coldstars/data", ".omd");
//        for(const auto& filepath: result) {
//            ceti::descriptor::Mesh* mesh = ceti::InfoLoader::read(filepath);
//            //std::cout<<"descriptor:"<<material->data()<<std::endl;
//            collector.add(mesh);
//        }
//        collector.save();
//    }
}

namespace {

void resolveId(ceti::descriptor::Material* material)
{
    material->setType(type::toInt(material->association().type()));
}

}

void Data::__loadImages()
{
    using namespace ceti::descriptor;

    //ceti::InfoLoader il("/ramdisk/build/coldstars/src/game/client/data/ship/template.md");
    //exit(1);

    auto& dm = global::get().descriptors();
    if (!dm.material().loaded()) {
        ceti::Collector<Material> collector("material_descriptors.txt");

        auto result = ceti::filesystem::getFilesList("/workspace/src/coldstars/data", ".md");
        for(const auto& filepath: result) {
            ceti::descriptor::Material* material = ceti::InfoLoader::read(filepath);
            //std::cout<<"descriptor:"<<material->data()<<std::endl;

            resolveId(material);
            collector.add(material);
        }
        collector.save();

//        //############ TURREL #########
//        {
//            Material material(int(type::texture::TURREL_ID), "turrel/turrel1.png");
//            //material.setAnimation(Animation());
//            //material.setAssociation(Association());
//            dm.add(material);
//        }

//        {
//            Material material(int(type::texture::TURREL_ID), "turrel/turrel2.png");
//            //material.setAnimation(Animation());
//            //material.setAssociation(Association());
//            dm.add(material);
//        }

//        {
//            Material material(int(type::texture::TURREL_ID), "turrel/esphere-0.png");
//            //material.setAnimation(Animation());
//            //material.setAssociation(Association());
//            dm.add(material);
//        }

//        //############ SLOT ############
//        {
//            Material material(int(type::texture::ITEM_SLOT_ID), "other/slot.png");
//            //material.setAnimation(Animation());
//            //material.setAssociation(Association());
//            dm.add(material);
//        }

//        {
//            Material material( int(type::texture::VEHICLE_SLOT_ID), "other/H.png");
//            material.setAnimation(Animation(3, 2, 3.0f));
//            //material.setAssociation(Association());
//            dm.add(material);
//        }

//        //########### FACE_ID #########
//        //// type::RACE::R0_ID
//        {
//            Material material(int(type::texture::FACE_ID), "race/0000.png");
//            //material.setAnimation(Animation());
//            material.setAssociation(Association(int(type::race::R0_ID)));
//            dm.add(material);
//        }
//        {
//            Material material(int(type::texture::FACE_ID), "race/0001.png");
//            //material.setAnimation(Animation());
//            material.setAssociation(Association(int(type::race::R0_ID)));
//            dm.add(material);
//        }

//        //// type::RACE::R1_ID
//        {
//            Material material(int(type::texture::FACE_ID), "race/1000.png");
//            //material.setAnimation(Animation());
//            material.setAssociation(Association(int(type::race::R1_ID)));
//            dm.add(material);
//        }
//        {
//            Material material(int(type::texture::FACE_ID), "race/1001.png");
//            //material.setAnimation(Animation());
//            material.setAssociation(Association(int(type::race::R1_ID)));
//            dm.add(material);
//        }

//        //// type::RACE::R2_ID
//        {
//            Material material(int(type::texture::FACE_ID), "race/2000.png");
//            //material.setAnimation(Animation());
//            material.setAssociation(Association(int(type::race::R2_ID)));
//            dm.add(material);
//        }
//        {
//            Material material(int(type::texture::FACE_ID), "race/2001.png");
//            //material.setAnimation(Animation());
//            material.setAssociation(Association(int(type::race::R2_ID)));
//            dm.add(material);
//        }

//        //// type::RACE::R3_ID
//        {
//            Material material(int(type::texture::FACE_ID), "race/3000.png");
//            //material.setAnimation(Animation());
//            material.setAssociation(Association(int(type::race::R3_ID)));
//            dm.add(material);
//        }
//        {
//            Material material(int(type::texture::FACE_ID), "race/3001.png");
//            //material.setAnimation(Animation());
//            material.setAssociation(Association(int(type::race::R3_ID)));
//            dm.add(material);
//        }

//        //// type::RACE::R4_ID
//        {
//            Material material(int(type::texture::FACE_ID), "race/4000.png");
//            //material.setAnimation(Animation());
//            material.setAssociation(Association(int(type::race::R4_ID)));
//            dm.add(material);
//        }
//        {
//            Material material(int(type::texture::FACE_ID), "race/4001.png");
//            //material.setAnimation(Animation());
//            material.setAssociation(Association(int(type::race::R4_ID)));
//            dm.add(material);
//        }

//        //// type::RACE::R6_ID
//        {
//            Material material(int(type::texture::FACE_ID), "race/6000.png");
//            //material.setAnimation(Animation());
//            material.setAssociation(Association(int(type::race::R6_ID)));
//            dm.add(material);
//        }
//        {
//            Material material(int(type::texture::FACE_ID), "race/6001.png");
//            //material.setAnimation(Animation());
//            material.setAssociation(Association(int(type::race::R6_ID)));
//            dm.add(material);
//        }

//        //// type::RACE::R7_ID
//        {
//            Material material(int(type::texture::FACE_ID), "race/7000.png");
//            //material.setAnimation(Animation());
//            material.setAssociation(Association(int(type::race::R7_ID)));
//            dm.add(material);
//        }
//        {
//            Material material(int(type::texture::FACE_ID), "race/7001.png");
//            //material.setAnimation(Animation());
//            material.setAssociation(Association(int(type::race::R7_ID)));
//            dm.add(material);
//        }

//        //####################################### ASTEROID_TEXTURE ################################
//        {
//            Material material(int(type::texture::ASTEROID_ID), "asteroid/a_000.png");
//            //material.setAnimation(Animation());
//            //material.setAssociation(Association());
//            dm.add(material);
//        }
//        {
//            Material material(int(type::texture::ASTEROID_ID), "asteroid/a_001.png");
//            //material.setAnimation(Animation());
//            //material.setAssociation(Association());
//            dm.add(material);
//        }
//        {
//            Material material(int(type::texture::ASTEROID_ID), "asteroid/a_002.png");
//            //material.setAnimation(Animation());
//            //material.setAssociation(Association());
//            dm.add(material);
//        }

//        //####################################### MINERAL_TEXTURE ################################
//        {
//            Material material(int(type::texture::MINERAL_ID), "asteroid/m_000.png");
//            //material.setAnimation(Animation());
//            //material.setAssociation(Association());
//            dm.add(material);
//        }
//        {
//            Material material(int(type::texture::MINERAL_ID), "asteroid/m_001.png");
//            //material.setAnimation(Animation());
//            //material.setAssociation(Association());
//            dm.add(material);
//        }
//        {
//            Material material(int(type::texture::MINERAL_ID), "asteroid/m_002.png");
//            //material.setAnimation(Animation());
//            //material.setAssociation(Association());
//            dm.add(material);
//        }

//        //####################################### CONTAINER_TEXTURE ################################
//        {
//            Material material(int(type::texture::CONTAINER_ID), "item/container.png");
//            //material.setAnimation(Animation());
//            //material.setAssociation(Association());
//            dm.add(material);
//        }

//        //####################################### BOMB_TEXTURE ################################
//        {
//            Material material(int(type::texture::BOMB_ID), "item/bomb_item.png");
//            //material.setAnimation(Animation());
//            //material.setAssociation(Association());
//            dm.add(material);
//        }

        // BLACKHOLE
//        {
//            Material material(int(type::texture::BLACKHOLE_ID), "blackhole/bh_00.png");
//            //material.setAnimation(Animation());
//            //material.setAssociation(Association());
//            dm.add(material);
//        }

        //####################################### type::TEXTURE::SATELLITE_ID ################################
//        {
//            Material material(int(type::texture::SATELLITE_ID), "satellite/sa_001.png");
//            material.setAnimation(Animation(3, 1, 6.0f));
//            material.setAssociation(Association(int(type::race::R0_ID)));
//            dm.add(material);
//        }
//        {
//            Material material(int(type::texture::SATELLITE_ID), "satellite/sa_002.png");
//            material.setAnimation(Animation(4, 1, 8.0f));
//            material.setAssociation(Association(int(type::race::R0_ID)));
//            dm.add(material);
//        }
//        {
//            Material material(int(type::texture::SATELLITE_ID), "satellite/sa_003.png");
//            material.setAnimation(Animation(3, 1, 6.0f));
//            material.setAssociation(Association(int(type::race::R0_ID)));
//            dm.add(material);
//        }
//        {
//            Material material(int(type::texture::SATELLITE_ID), "satellite/sa_004.png");
//            material.setAnimation(Animation(4, 1, 8.0f));
//            material.setAssociation(Association(int(type::race::R0_ID)));
//            dm.add(material);
//        }
//        {
//            Material material(int(type::texture::SATELLITE_ID), "satellite/sa_005.png");
//            material.setAnimation(Animation(8, 1, 16.0f));
//            material.setAssociation(Association(int(type::race::R0_ID)));
//            dm.add(material);
//        }
//        {
//            Material material(int(type::texture::SATELLITE_ID), "satellite/sa_006.png");
//            material.setAnimation(Animation(8, 1, 16.0f));
//            material.setAssociation(Association(int(type::race::R0_ID)));
//            dm.add(material);
//        }

        ////####################################### SHIP_TEXTURE ####################################
        ////################################ type::race::R0_ID (SCI)
//        {
//            Material material(int(type::texture::SHIP_ID), "ship/race0_ranger_00.png");
//            //material.setAnimation(Animation());
//            material.setAssociation(Association(int(type::race::R0_ID), int(type::entity::RANGER_ID)));
//            dm.add(material);
//        }
//        {
//            Material material(int(type::texture::SHIP_ID), "ship/race0_warrior_00.png");
//            //material.setAnimation(Animation());
//            material.setAssociation(Association(int(type::race::R0_ID), int(type::entity::WARRIOR_ID)));
//            dm.add(material);
//        }
//        {
//            Material material(int(type::texture::SHIP_ID), "ship/race0_pirat_00.png");
//            //material.setAnimation(Animation());
//            material.setAssociation(Association(int(type::race::R0_ID), int(type::entity::PIRAT_ID)));
//            dm.add(material);
//        }
//        {
//            Material material(int(type::texture::SHIP_ID), "ship/race0_traider_00.png");
//            //material.setAnimation(Animation());
//            material.setAssociation(Association(int(type::race::R0_ID), int(type::entity::TRADER_ID)));
//            dm.add(material);
//        }
//        {
//            Material material(int(type::texture::SHIP_ID), "ship/race0_diplomat_00.png");
//            //material.setAnimation(Animation());
//            material.setAssociation(Association(int(type::race::R0_ID), int(type::entity::DIPLOMAT_ID)));
//            dm.add(material);
//        }

        ////################################ type::race::R1_ID (WARR)
//        {
//            Material material(int(type::texture::SHIP_ID), "ship/race1_ranger_00.png");
//            //material.setAnimation(Animation());
//            material.setAssociation(Association(int(type::race::R1_ID), int(type::entity::RANGER_ID)));
//            dm.add(material);
//        }
//        {
//            Material material(int(type::texture::SHIP_ID), "ship/race1_warrior_00.png");
//            //material.setAnimation(Animation());
//            material.setAssociation(Association(int(type::race::R1_ID), int(type::entity::WARRIOR_ID)));
//            dm.add(material);
//        }
//        {
//            Material material(int(type::texture::SHIP_ID), "ship/race1_pirat_00.png");
//            //material.setAnimation(Animation());
//            material.setAssociation(Association(int(type::race::R1_ID), int(type::entity::PIRAT_ID)));
//            dm.add(material);
//        }
//        {
//            Material material(int(type::texture::SHIP_ID), "ship/race1_trader_00.png");
//            //material.setAnimation(Animation());
//            material.setAssociation(Association(int(type::race::R1_ID), int(type::entity::TRADER_ID)));
//            dm.add(material);
//        }
//        {
//            Material material(int(type::texture::SHIP_ID), "ship/race1_diplomat_00.png");
//            //material.setAnimation(Animation());
//            material.setAssociation(Association(int(type::race::R1_ID), int(type::entity::DIPLOMAT_ID)));
//            dm.add(material);
//        }

        ////################################ type::race::R2_ID (TRIEF)
//        {
//            Material material(int(type::texture::SHIP_ID), "ship/race2_ranger_00.png");
//            //material.setAnimation(Animation());
//            material.setAssociation(Association(int(type::race::R2_ID), int(type::entity::RANGER_ID)));
//            dm.add(material);
//        }
//        {
//            Material material(int(type::texture::SHIP_ID), "ship/race2_warrior_00.png");
//            //material.setAnimation(Animation());
//            material.setAssociation(Association(int(type::race::R2_ID), int(type::entity::WARRIOR_ID)));
//            dm.add(material);
//        }
//        {
//            Material material(int(type::texture::SHIP_ID), "ship/race2_pirat_00.png");
//            //material.setAnimation(Animation());
//            material.setAssociation(Association(int(type::race::R2_ID), int(type::entity::PIRAT_ID)));
//            dm.add(material);
//        }
//        {
//            Material material(int(type::texture::SHIP_ID), "ship/race2_trader_00.png");
//            //material.setAnimation(Animation());
//            material.setAssociation(Association(int(type::race::R2_ID), int(type::entity::TRADER_ID)));
//            dm.add(material);
//        }
//        {
//            Material material(int(type::texture::SHIP_ID), "ship/race2_diplomat_00.png");
//            //material.setAnimation(Animation());
//            material.setAssociation(Association(int(type::race::R2_ID), int(type::entity::DIPLOMAT_ID)));
//            dm.add(material);
//        }

        ////################################ type::race::R3_ID (HUMAN)
//        {
//            Material material(int(type::texture::SHIP_ID), "ship/race3_ranger_00.png");
//            //material.setAnimation(Animation());
//            material.setAssociation(Association(int(type::race::R3_ID), int(type::entity::RANGER_ID)));
//            dm.add(material);
//        }
//        {
//            Material material(int(type::texture::SHIP_ID), "ship/race3_warrior_00.png");
//            //material.setAnimation(Animation());
//            material.setAssociation(Association(int(type::race::R3_ID), int(type::entity::WARRIOR_ID)));
//            dm.add(material);
//        }
//        {
//            Material material(int(type::texture::SHIP_ID), "ship/race3_warrior_01.png");
//            //material.setAnimation(Animation());
//            material.setAssociation(Association(int(type::race::R3_ID), int(type::entity::WARRIOR_ID)));
//            dm.add(material);
//        }
//        {
//            Material material(int(type::texture::SHIP_ID), "ship/race3_pirat_00.png");
//            //material.setAnimation(Animation());
//            material.setAssociation(Association(int(type::race::R3_ID), int(type::entity::PIRAT_ID)));
//            dm.add(material);
//        }
//        {
//            Material material(int(type::texture::SHIP_ID), "ship/race3_trader_00.png");
//            //material.setAnimation(Animation());
//            material.setAssociation(Association(int(type::race::R3_ID), int(type::entity::TRADER_ID)));
//            dm.add(material);
//        }
//        {
//            Material material(int(type::texture::SHIP_ID), "ship/race3_diplomat_00.png");
//            //material.setAnimation(Animation());
//            material.setAssociation(Association(int(type::race::R3_ID), int(type::entity::DIPLOMAT_ID)));
//            dm.add(material);
//        }

        ////################################ type::RACE::R4_ID (BIO)
//        {
//            Material material(int(type::texture::SHIP_ID), "ship/race4_warrior_00.png");
//            //material.setAnimation(Animation());
//            material.setAssociation(Association(int(type::race::R4_ID), int(type::entity::WARRIOR_ID)));
//            dm.add(material);
//        }
//        {
//            Material material(int(type::texture::SHIP_ID), "ship/race4_trader_00.png");
//            //material.setAnimation(Animation());
//            material.setAssociation(Association(int(type::race::R4_ID), int(type::entity::TRADER_ID)));
//            dm.add(material);
//        }
//        {
//            Material material(int(type::texture::SHIP_ID), "ship/race4_trader_01.png");
//            //material.setAnimation(Animation());
//            material.setAssociation(Association(int(type::race::R4_ID), int(type::entity::TRADER_ID)));
//            dm.add(material);
//        }
//        {
//            Material material(int(type::texture::SHIP_ID), "ship/race4_diplomat_00.png");
//            //material.setAnimation(Animation());
//            material.setAssociation(Association(int(type::race::R4_ID), int(type::entity::DIPLOMAT_ID)));
//            dm.add(material);
//        }

        ////################################ type::RACE::R6_ID (enemy 1)
//        {
//            Material material(int(type::texture::SHIP_ID), "ship/race6_warrior_00.png");
//            //material.setAnimation(Animation());
//            material.setAssociation(Association(int(type::race::R6_ID), int(type::entity::WARRIOR_ID)));
//            dm.add(material);
//        }
//        {
//            Material material(int(type::texture::SHIP_ID), "ship/race6_warrior_01.png");
//            //material.setAnimation(Animation());
//            material.setAssociation(Association(int(type::race::R6_ID), int(type::entity::WARRIOR_ID)));
//            dm.add(material);
//        }
//        {
//            Material material(int(type::texture::SHIP_ID), "ship/race6_warrior_02.png");
//            //material.setAnimation(Animation());
//            material.setAssociation(Association(int(type::race::R6_ID), int(type::entity::WARRIOR_ID)));
//            dm.add(material);
//        }
        ////{
        //    //std::vector<int> arg;
        //    //arg.push_back((int)type::RACE::R6_ID); arg.push_back((int)type::entity::WARRIOR_ID); //COLOR_GOLDENROD
        //    //TextureCollector::Instance().Add( new jeti::control::TextureOb(type::TEXTURE::SHIP_ID, DATA_PATH+"ship/k_61_0_3.png", true, &arg) );
        ////}


        ////{
        //    //std::vector<int> arg;
        //    //arg.push_back((int)type::RACE::R6_ID); arg.push_back((int)type::entity::WARRIOR_ID); //COLOR_GOLDENROD
        //    //TextureCollector::Instance().Add( new jeti::control::TextureOb(type::TEXTURE::SHIP_ID, DATA_PATH+"ship/k_61_0_5.png", true, &arg) );
        ////}

        ////{
        //    //std::vector<int> arg;
        //    //arg.push_back((int)type::RACE::R6_ID); arg.push_back((int)type::entity::WARRIOR_ID); //COLOR_GOLDENROD
        //    //TextureCollector::Instance().Add( new jeti::control::TextureOb(type::TEXTURE::SHIP_ID, DATA_PATH+"ship/k_61_0_6.png", true, &arg) );
        ////}

        ////{
        //    //std::vector<int> arg;
        //    //arg.push_back((int)type::RACE::R6_ID); arg.push_back((int)type::entity::WARRIOR_ID); //COLOR_GOLDENROD
        //    //TextureCollector::Instance().Add( new jeti::control::TextureOb(type::TEXTURE::SHIP_ID, DATA_PATH+"ship/k_61_0_7.png", true, &arg) );
        ////}

        ////{
        //    //std::vector<int> arg;
        //    //arg.push_back((int)type::RACE::R6_ID); arg.push_back((int)type::entity::WARRIOR_ID); //COLOR_GOLDENROD
        //    //TextureCollector::Instance().Add( new jeti::control::TextureOb(type::TEXTURE::SHIP_ID, DATA_PATH+"ship/k_61_0_8.png", true, &arg) );
        ////}

        ////{
        //    //std::vector<int> arg;
        //    //arg.push_back((int)type::RACE::R6_ID); arg.push_back((int)type::entity::WARRIOR_ID); //COLOR_GOLDENROD
        //    //TextureCollector::Instance().Add( new jeti::control::TextureOb(type::TEXTURE::SHIP_ID, DATA_PATH+"ship/k_61_0_9.png", true, &arg) );
        ////}

        ////{
        //    //std::vector<int> arg;
        //    //arg.push_back((int)type::RACE::R6_ID); arg.push_back((int)type::entity::WARRIOR_ID); //COLOR_GOLDENROD
        //    //TextureCollector::Instance().Add( new jeti::control::TextureOb(type::TEXTURE::SHIP_ID, DATA_PATH+"ship/k_61_0_10.png", true, &arg) );
        ////}

        ////{
        //    //std::vector<int> arg;
        //    //arg.push_back((int)type::RACE::R6_ID); arg.push_back((int)type::entity::WARRIOR_ID); //COLOR_GOLDENROD
        //    //TextureCollector::Instance().Add( new jeti::control::TextureOb(type::TEXTURE::SHIP_ID, DATA_PATH+"ship/k_61_0_11.png", true, &arg) );
        ////}

        ////{
        //    //std::vector<int> arg;
        //    //arg.push_back((int)type::RACE::R6_ID); arg.push_back((int)type::entity::WARRIOR_ID); //COLOR_GOLDENROD
        //    //TextureCollector::Instance().Add( new jeti::control::TextureOb(type::TEXTURE::SHIP_ID, DATA_PATH+"ship/k_61_0_12.png", true, &arg) );
        ////}

        ////################################ type::RACE::R7_ID (enemy 2)
//        {
//            Material material(int(type::texture::SHIP_ID), "ship/race7_warrior_00.png");
//            //material.setAnimation(Animation());
//            material.setAssociation(Association(int(type::race::R7_ID), int(type::entity::WARRIOR_ID)));
//            dm.add(material);
//        }
//        {
//            Material material(int(type::texture::SHIP_ID), "ship/race7_warrior_01.png");
//            //material.setAnimation(Animation());
//            material.setAssociation(Association(int(type::race::R7_ID), int(type::entity::WARRIOR_ID)));
//            dm.add(material);
//        }


//        //// STARBASE_TEXTURE_ID
//        {
//            Material material(int(type::texture::SPACESTATION_ID), "ship/sb_000.png");
//            //material.setAnimation(Animation());
//            material.setAssociation(Association(int(type::race::R0_ID)));
//            dm.add(material);
//        }
//        {
//            Material material(int(type::texture::SPACESTATION_ID), "ship/sb_001.png");
//            //material.setAnimation(Animation());
//            material.setAssociation(Association(int(type::race::R0_ID)));
//            dm.add(material);
//        }
//        {
//            Material material(int(type::texture::SPACESTATION_ID), "ship/sb_002.png");
//            //material.setAnimation(Animation());
//            material.setAssociation(Association(int(type::race::R0_ID)));
//            dm.add(material);
//        }
//        {
//            Material material(int(type::texture::SPACESTATION_ID), "ship/sb_003.png");
//            //material.setAnimation(Animation());
//            material.setAssociation(Association(int(type::race::R0_ID)));
//            dm.add(material);
//        }

    }

////################################# type::TEXTURE::STAR_ID ###############################
//{
//    jeti::Material material_data;
//    material_data.texture_path = DATA_PATH+"star/s_000.jpg";
//    material_data.brightThreshold = 1.9f;
//    material_data.color_id = COLOR::YELLOW_ID;
//    jeti::control::TextureOb* textureOb = new jeti::control::TextureOb(material_data);

//    jeti::MaterialAssociationData association_data;
//    association_data.type_id    = type::TEXTURE::STAR_ID;
//    textureOb->SetAssociation(association_data);

//    TextureCollector::Instance().Add(textureOb);
//}

//{
//    jeti::Material material_data;
//    material_data.texture_path = DATA_PATH+"star/s_001.png";
//    material_data.brightThreshold = 1.825f;
//    material_data.color_id = COLOR::YELLOW_ID;
//    jeti::control::TextureOb* textureOb = new jeti::control::TextureOb(material_data);

//    jeti::MaterialAssociationData association_data;
//    association_data.type_id    = type::TEXTURE::STAR_ID;
//    textureOb->SetAssociation(association_data);

//    TextureCollector::Instance().Add(textureOb);
//}

//{
//    jeti::Material material_data;
//    material_data.texture_path = DATA_PATH+"star/s_100.jpg";
//    material_data.brightThreshold = 2.525f;
//    material_data.color_id = COLOR::BLUE_ID;
//    jeti::control::TextureOb* textureOb = new jeti::control::TextureOb(material_data);

//    jeti::MaterialAssociationData association_data;
//    association_data.type_id    = type::TEXTURE::STAR_ID;
//    textureOb->SetAssociation(association_data);

//    TextureCollector::Instance().Add(textureOb);
//}

//{
//    jeti::Material material_data;
//    material_data.texture_path = DATA_PATH+"star/s_101.png";
//    material_data.brightThreshold = 1.925f;
//    material_data.color_id = COLOR::BLUE_ID;
//    jeti::control::TextureOb* textureOb = new jeti::control::TextureOb(material_data);

//    jeti::MaterialAssociationData association_data;
//    association_data.type_id    = type::TEXTURE::STAR_ID;
//    textureOb->SetAssociation(association_data);

//    TextureCollector::Instance().Add(textureOb);
//}

////################################## NEBULA EFFECT ################################
//{
//    jeti::Material material_data;
//    material_data.texture_path = DATA_PATH+"bg_space/nebula.bak/nebula1.png";
//    material_data.use_alpha = true;
//    material_data.color_id = COLOR::RED_ID;
//    material_data.is_rotated = false;
//    jeti::control::TextureOb* textureOb = new jeti::control::TextureOb(material_data);

//    jeti::MaterialAssociationData association_data;
//    association_data.type_id    = type::TEXTURE::NEBULA_BACKGROUND_ID;
//    textureOb->SetAssociation(association_data);

//    TextureCollector::Instance().Add(textureOb);
//}

//{
//    jeti::Material material_data;
//    material_data.texture_path = DATA_PATH+"bg_space/nebula.bak/nebula2.png";
//    material_data.use_alpha = true;
//    material_data.color_id = COLOR::GREEN_ID;
//    material_data.is_rotated = true;
//    jeti::control::TextureOb* textureOb = new jeti::control::TextureOb(material_data);

//    jeti::MaterialAssociationData association_data;
//    association_data.type_id    = type::TEXTURE::NEBULA_BACKGROUND_ID;
//    textureOb->SetAssociation(association_data);

//    TextureCollector::Instance().Add(textureOb);
//}

//{
//    jeti::Material material_data;
//    material_data.texture_path = DATA_PATH+"bg_space/nebula.bak/nebula3.png";
//    material_data.use_alpha = true;
//    material_data.color_id = COLOR::YELLOW_ID;
//    material_data.is_rotated = false;
//    jeti::control::TextureOb* textureOb = new jeti::control::TextureOb(material_data);

//    jeti::MaterialAssociationData association_data;
//    association_data.type_id    = type::TEXTURE::NEBULA_BACKGROUND_ID;
//    textureOb->SetAssociation(association_data);

//    TextureCollector::Instance().Add(textureOb);
//}

//{
//    jeti::Material material_data;
//    material_data.texture_path = DATA_PATH+"bg_space/nebula.bak/nebula4.png";
//    material_data.use_alpha = true;
//    material_data.color_id = COLOR::BLUE_ID;
//    material_data.is_rotated = true;
//    jeti::control::TextureOb* textureOb = new jeti::control::TextureOb(material_data);

//    jeti::MaterialAssociationData association_data;
//    association_data.type_id    = type::TEXTURE::NEBULA_BACKGROUND_ID;
//    textureOb->SetAssociation(association_data);

//    TextureCollector::Instance().Add(textureOb);
//}

//{
//    jeti::Material material_data;
//    material_data.texture_path = DATA_PATH+"bg_space/nebula.bak/nebula5.png";
//    material_data.use_alpha = true;
//    material_data.color_id = COLOR::YELLOW_ID;
//    material_data.is_rotated = false;
//    jeti::control::TextureOb* textureOb = new jeti::control::TextureOb(material_data);

//    jeti::MaterialAssociationData association_data;
//    association_data.type_id    = type::TEXTURE::NEBULA_BACKGROUND_ID;
//    textureOb->SetAssociation(association_data);

//    TextureCollector::Instance().Add(textureOb);
//}

//{
//    jeti::Material material_data;
//    material_data.texture_path = DATA_PATH+"bg_space/nebula.bak/nebula6.png";
//    material_data.use_alpha = true;
//    material_data.color_id = COLOR::RED_ID;
//    material_data.is_rotated = false;
//    jeti::control::TextureOb* textureOb = new jeti::control::TextureOb(material_data);

//    jeti::MaterialAssociationData association_data;
//    association_data.type_id    = type::TEXTURE::NEBULA_BACKGROUND_ID;
//    textureOb->SetAssociation(association_data);

//    TextureCollector::Instance().Add(textureOb);
//}

//{
//    jeti::Material material_data;
//    material_data.texture_path = DATA_PATH+"bg_space/nebula.bak/nebula7.png";
//    material_data.use_alpha = true;
//    material_data.color_id = COLOR::BLUE_ID;
//    material_data.is_rotated = false;
//    jeti::control::TextureOb* textureOb = new jeti::control::TextureOb(material_data);

//    jeti::MaterialAssociationData association_data;
//    association_data.type_id    = type::TEXTURE::NEBULA_BACKGROUND_ID;
//    textureOb->SetAssociation(association_data);

//    TextureCollector::Instance().Add(textureOb);
//}

//{
//    jeti::Material material_data;
//    material_data.texture_path = DATA_PATH+"bg_space/nebula.bak/nebula8.png";
//    material_data.use_alpha = true;
//    material_data.color_id = COLOR::BLUE_ID;
//    material_data.is_rotated = true;
//    jeti::control::TextureOb* textureOb = new jeti::control::TextureOb(material_data);

//    jeti::MaterialAssociationData association_data;
//    association_data.type_id    = type::TEXTURE::NEBULA_BACKGROUND_ID;
//    textureOb->SetAssociation(association_data);

//    TextureCollector::Instance().Add(textureOb);
//}

//{
//    jeti::Material material_data;
//    material_data.texture_path = DATA_PATH+"bg_space/nebula.bak/nebula9.png";
//    material_data.use_alpha = true;
//    material_data.color_id = COLOR::BLUE_ID;
//    material_data.is_rotated = true;
//    jeti::control::TextureOb* textureOb = new jeti::control::TextureOb(material_data);

//    jeti::MaterialAssociationData association_data;
//    association_data.type_id    = type::TEXTURE::NEBULA_BACKGROUND_ID;
//    textureOb->SetAssociation(association_data);

//    TextureCollector::Instance().Add(textureOb);
//}

//{
//    jeti::Material material_data;
//    material_data.texture_path = DATA_PATH+"bg_space/nebula.bak/nebula10.png";
//    material_data.use_alpha = true;
//    material_data.color_id = COLOR::RED_ID;
//    material_data.is_rotated = false;
//    jeti::control::TextureOb* textureOb = new jeti::control::TextureOb(material_data);

//    jeti::MaterialAssociationData association_data;
//    association_data.type_id    = type::TEXTURE::NEBULA_BACKGROUND_ID;
//    textureOb->SetAssociation(association_data);

//    TextureCollector::Instance().Add(textureOb);
//}

//{
//    jeti::Material material_data;
//    material_data.texture_path = DATA_PATH+"bg_space/nebula.bak/nebula11.png";
//    material_data.use_alpha = true;
//    material_data.color_id = COLOR::YELLOW_ID;
//    material_data.is_rotated = false;
//    jeti::control::TextureOb* textureOb = new jeti::control::TextureOb(material_data);

//    jeti::MaterialAssociationData association_data;
//    association_data.type_id    = type::TEXTURE::NEBULA_BACKGROUND_ID;
//    textureOb->SetAssociation(association_data);

//    TextureCollector::Instance().Add(textureOb);
//}

//{
//    jeti::Material material_data;
//    material_data.texture_path = DATA_PATH+"bg_space/nebula.bak/nebula12.png";
//    material_data.use_alpha = true;
//    material_data.color_id = COLOR::BLUE_ID;
//    material_data.is_rotated = false;
//    jeti::control::TextureOb* textureOb = new jeti::control::TextureOb(material_data);

//    jeti::MaterialAssociationData association_data;
//    association_data.type_id    = type::TEXTURE::NEBULA_BACKGROUND_ID;
//    textureOb->SetAssociation(association_data);

//    TextureCollector::Instance().Add(textureOb);
//}

//{
//    jeti::Material material_data;
//    material_data.texture_path = DATA_PATH+"bg_space/nebula.bak/nebula13.png";
//    material_data.use_alpha = true;
//    material_data.color_id = COLOR::BLUE_ID;
//    material_data.is_rotated = false;
//    jeti::control::TextureOb* textureOb = new jeti::control::TextureOb(material_data);

//    jeti::MaterialAssociationData association_data;
//    association_data.type_id    = type::TEXTURE::NEBULA_BACKGROUND_ID;
//    textureOb->SetAssociation(association_data);

//    TextureCollector::Instance().Add(textureOb);
//}

//{
//    jeti::Material material_data;
//    material_data.texture_path = DATA_PATH+"bg_space/nebula.bak/nebula14.png";
//    material_data.use_alpha = true;
//    material_data.color_id = COLOR::RED_ID;
//    material_data.is_rotated = true;
//    jeti::control::TextureOb* textureOb = new jeti::control::TextureOb(material_data);

//    jeti::MaterialAssociationData association_data;
//    association_data.type_id    = type::TEXTURE::NEBULA_BACKGROUND_ID;
//    textureOb->SetAssociation(association_data);

//    TextureCollector::Instance().Add(textureOb);
//}

//{
//    jeti::Material material_data;
//    material_data.texture_path = DATA_PATH+"bg_space/nebula.bak/nebula15.png";
//    material_data.use_alpha = true;
//    material_data.color_id = COLOR::YELLOW_ID;
//    material_data.is_rotated = true;
//    jeti::control::TextureOb* textureOb = new jeti::control::TextureOb(material_data);

//    jeti::MaterialAssociationData association_data;
//    association_data.type_id    = type::TEXTURE::NEBULA_BACKGROUND_ID;
//    textureOb->SetAssociation(association_data);

//    TextureCollector::Instance().Add(textureOb);
//}

//{
//    jeti::Material material_data;
//    material_data.texture_path = DATA_PATH+"bg_space/nebula.bak/nebula16.png";
//    material_data.use_alpha = true;
//    material_data.color_id = COLOR::YELLOW_ID;
//    material_data.is_rotated = false;
//    jeti::control::TextureOb* textureOb = new jeti::control::TextureOb(material_data);

//    jeti::MaterialAssociationData association_data;
//    association_data.type_id    = type::TEXTURE::NEBULA_BACKGROUND_ID;
//    textureOb->SetAssociation(association_data);

//    TextureCollector::Instance().Add(textureOb);
//}

//{
//    jeti::Material material_data;
//    material_data.texture_path = DATA_PATH+"bg_space/nebula.bak/nebula17.png";
//    material_data.use_alpha = true;
//    material_data.color_id = COLOR::YELLOW_ID;
//    material_data.is_rotated = false;
//    jeti::control::TextureOb* textureOb = new jeti::control::TextureOb(material_data);

//    jeti::MaterialAssociationData association_data;
//    association_data.type_id    = type::TEXTURE::NEBULA_BACKGROUND_ID;
//    textureOb->SetAssociation(association_data);

//    TextureCollector::Instance().Add(textureOb);
//}

//{
//    jeti::Material material_data;
//    material_data.texture_path = DATA_PATH+"bg_space/nebula.bak/nebula18.png";
//    material_data.use_alpha = true;
//    material_data.color_id = COLOR::YELLOW_ID;
//    material_data.is_rotated = false;
//    jeti::control::TextureOb* textureOb = new jeti::control::TextureOb(material_data);

//    jeti::MaterialAssociationData association_data;
//    association_data.type_id    = type::TEXTURE::NEBULA_BACKGROUND_ID;
//    textureOb->SetAssociation(association_data);

//    TextureCollector::Instance().Add(textureOb);
//}

//{
//    jeti::Material material_data;
//    material_data.texture_path = DATA_PATH+"bg_space/nebula.bak/nebula19.png";
//    material_data.use_alpha = true;
//    material_data.color_id = COLOR::RED_ID;
//    material_data.is_rotated = false;
//    jeti::control::TextureOb* textureOb = new jeti::control::TextureOb(material_data);

//    jeti::MaterialAssociationData association_data;
//    association_data.type_id    = type::TEXTURE::NEBULA_BACKGROUND_ID;
//    textureOb->SetAssociation(association_data);

//    TextureCollector::Instance().Add(textureOb);
//}
////### size 2 = 512x512
////### size 4 = 1024x1024 or 512x1024

////################################ type::TEXTURE::LAND_BACKGROUND_ID ###################################
//{
//    jeti::Material material_data;
//    material_data.texture_path = DATA_PATH+"bg_uninhabited/b_000.jpg";
//    jeti::control::TextureOb* textureOb = new jeti::control::TextureOb(material_data);

//    jeti::MaterialAssociationData association_data;
//    association_data.type_id    = type::TEXTURE::NATURELAND_BACKGROUND_ID;
//    textureOb->SetAssociation(association_data);

//    TextureCollector::Instance().Add(textureOb);
//}

//{
//    jeti::Material material_data;
//    material_data.texture_path = DATA_PATH+"bg_uninhabited/b_001.png";
//    jeti::control::TextureOb* textureOb = new jeti::control::TextureOb(material_data);

//    jeti::MaterialAssociationData association_data;
//    association_data.type_id    = type::TEXTURE::NATURELAND_BACKGROUND_ID;
//    textureOb->SetAssociation(association_data);

//    TextureCollector::Instance().Add(textureOb);
//}

//{
//    jeti::Material material_data;
//    material_data.texture_path = DATA_PATH+"bg_uninhabited/b_002.png";
//    jeti::control::TextureOb* textureOb = new jeti::control::TextureOb(material_data);

//    jeti::MaterialAssociationData association_data;
//    association_data.type_id    = type::TEXTURE::NATURELAND_BACKGROUND_ID;
//    textureOb->SetAssociation(association_data);

//    TextureCollector::Instance().Add(textureOb);
//}

////################################ KOSMOPORT_BG_TEXTURE_ID ###############################
//{
//    jeti::Material material_data;
//    material_data.texture_path = DATA_PATH+"bg_kosmoport/an_000.jpg";
//    jeti::control::TextureOb* textureOb = new jeti::control::TextureOb(material_data);

//    jeti::MaterialAssociationData association_data;
//    association_data.type_id    = type::TEXTURE::ANGAR_BACKGROUND_ID;
//    association_data.race_id    = type::RACE::R0_ID;
//    textureOb->SetAssociation(association_data);

//    TextureCollector::Instance().Add(textureOb);
//}

//{
//    jeti::Material material_data;
//    material_data.texture_path = DATA_PATH+"bg_kosmoport/st_000.jpg";
//    jeti::control::TextureOb* textureOb = new jeti::control::TextureOb(material_data);

//    jeti::MaterialAssociationData association_data;
//    association_data.type_id    = type::TEXTURE::STORE_BACKGROUND_ID;
//    association_data.race_id    = type::RACE::R0_ID;
//    textureOb->SetAssociation(association_data);

//    TextureCollector::Instance().Add(textureOb);
//}

//{
//    jeti::Material material_data;
//    material_data.texture_path = DATA_PATH+"bg_kosmoport/sh_000.jpg";
//    jeti::control::TextureOb* textureOb = new jeti::control::TextureOb(material_data);

//    jeti::MaterialAssociationData association_data;
//    association_data.type_id    = type::TEXTURE::SHOP_BACKGROUND_ID;
//    association_data.race_id    = type::RACE::R0_ID;
//    textureOb->SetAssociation(association_data);

//    TextureCollector::Instance().Add(textureOb);
//}

//{
//    jeti::Material material_data;
//    material_data.texture_path = DATA_PATH+"bg_kosmoport/go_000.jpg";
//    jeti::control::TextureOb* textureOb = new jeti::control::TextureOb(material_data);

//    jeti::MaterialAssociationData association_data;
//    association_data.type_id    = type::TEXTURE::GOVERMENT_BACKGROUND_ID;
//    association_data.race_id    = type::RACE::R0_ID;
//    textureOb->SetAssociation(association_data);

//    TextureCollector::Instance().Add(textureOb);
//}


////################################ PLANET_TEXTURE ####################################
//{
//    jeti::Material material_data;
//    material_data.texture_path      = DATA_PATH+"planet/p_0000.png";
//    material_data.normalmap_path    = DATA_PATH+"planet/p_0000_nm.png";
//    jeti::control::TextureOb* textureOb = new jeti::control::TextureOb(material_data);

//    jeti::MaterialAssociationData association_data;
//    association_data.type_id    = type::TEXTURE::PLANET_ID;
//    association_data.subtype_id = type::entity::PLANET_MIXED_ID;
//    textureOb->SetAssociation(association_data);

//    TextureCollector::Instance().Add(textureOb);
//}

//{
//    jeti::Material material_data;
//    material_data.texture_path      = DATA_PATH+"planet/p_1000.png";
//    material_data.normalmap_path    = DATA_PATH+"planet/p_1000_nm.png";
//    jeti::control::TextureOb* textureOb = new jeti::control::TextureOb(material_data);

//    jeti::MaterialAssociationData association_data;
//    association_data.type_id    = type::TEXTURE::PLANET_ID;
//    association_data.subtype_id = type::entity::PLANET_WATER_ID;
//    textureOb->SetAssociation(association_data);

//    TextureCollector::Instance().Add(textureOb);
//}

//{
//    jeti::Material material_data;
//    material_data.texture_path      = DATA_PATH+"planet/p_2000.png";
//    material_data.normalmap_path    = DATA_PATH+"planet/p_2000_nm.png";
//    jeti::control::TextureOb* textureOb = new jeti::control::TextureOb(material_data);

//    jeti::MaterialAssociationData association_data;
//    association_data.type_id    = type::TEXTURE::PLANET_ID;
//    association_data.subtype_id = type::entity::PLANET_VULCANIC_ID;
//    textureOb->SetAssociation(association_data);

//    TextureCollector::Instance().Add(textureOb);

//}

//{
//    jeti::Material material_data;
//    material_data.texture_path      = DATA_PATH+"planet/p_3000.png";
//    material_data.normalmap_path    = DATA_PATH+"planet/p_3000_nm.png";
//    jeti::control::TextureOb* textureOb = new jeti::control::TextureOb(material_data);

//    jeti::MaterialAssociationData association_data;
//    association_data.type_id    = type::TEXTURE::PLANET_ID;
//    association_data.subtype_id = type::entity::PLANET_ICE_ID;
//    textureOb->SetAssociation(association_data);

//    TextureCollector::Instance().Add(textureOb);
//}

//{
//    jeti::Material material_data;
//    material_data.texture_path      = DATA_PATH+"planet/p_4000.png";
//    material_data.normalmap_path    = DATA_PATH+"planet/p_4000_nm.png";
//    jeti::control::TextureOb* textureOb = new jeti::control::TextureOb(material_data);

//    jeti::MaterialAssociationData association_data;
//    association_data.type_id    = type::TEXTURE::PLANET_ID;
//    association_data.subtype_id = type::entity::PLANET_GAS_ID;
//    textureOb->SetAssociation(association_data);

//    TextureCollector::Instance().Add(textureOb);
//}

////################################ ATMOSPHERE_TEXTURE ####################################
//{
//    jeti::Material material_data;
//    material_data.texture_path = DATA_PATH+"planet/atmosphere_000.png";
//    material_data.use_alpha = true;
//    jeti::control::TextureOb* textureOb = new jeti::control::TextureOb(material_data);

//    jeti::MaterialAssociationData association_data;
//    association_data.type_id    = type::TEXTURE::ATMOSPHERE_ID;
//    textureOb->SetAssociation(association_data);

//    TextureCollector::Instance().Add(textureOb);
//}

//{
//    jeti::Material material_data;
//    material_data.texture_path = DATA_PATH+"planet/atmosphere_001.png";
//    material_data.use_alpha = true;
//    jeti::control::TextureOb* textureOb = new jeti::control::TextureOb(material_data);

//    jeti::MaterialAssociationData association_data;
//    association_data.type_id    = type::TEXTURE::ATMOSPHERE_ID;
//    textureOb->SetAssociation(association_data);

//    TextureCollector::Instance().Add(textureOb);
//}

////################################ RING_TEXTURE ####################################
//{
//    jeti::Material material_data;
//    material_data.texture_path = DATA_PATH+"planet/ring.png";
//    material_data.use_alpha = true;
//    jeti::control::TextureOb* textureOb = new jeti::control::TextureOb(material_data);

//    jeti::MaterialAssociationData association_data;
//    association_data.type_id    = type::TEXTURE::RING_ID;
//    textureOb->SetAssociation(association_data);

//    TextureCollector::Instance().Add(textureOb);
//}

////################################ EFFECTS TEXTURE ###################################
//{
//    jeti::Material material_data;
//    material_data.texture_path = DATA_PATH+"effect/particles/particle0.png";
//    material_data.use_alpha = true;
//    material_data.color_id = COLOR::RED_ID;
//    jeti::control::TextureOb* textureOb = new jeti::control::TextureOb(material_data);

//    jeti::MaterialAssociationData association_data;
//    association_data.type_id    = type::TEXTURE::PARTICLE_EFFECT_ID;
//    textureOb->SetAssociation(association_data);

//    TextureCollector::Instance().Add(textureOb);
//}

//{
//    jeti::Material material_data;
//    material_data.texture_path = DATA_PATH+"effect/particles/particle1.png";
//    material_data.use_alpha = true;
//    material_data.color_id = COLOR::BLUE_ID;
//    jeti::control::TextureOb* textureOb = new jeti::control::TextureOb(material_data);

//    jeti::MaterialAssociationData association_data;
//    association_data.type_id    = type::TEXTURE::PARTICLE_EFFECT_ID;
//    textureOb->SetAssociation(association_data);

//    TextureCollector::Instance().Add(textureOb);
//}

//{
//    jeti::Material material_data;
//    material_data.texture_path = DATA_PATH+"effect/particles/particle2.png";
//    material_data.use_alpha = true;
//    material_data.color_id = COLOR::YELLOW_ID;
//    jeti::control::TextureOb* textureOb = new jeti::control::TextureOb(material_data);

//    jeti::MaterialAssociationData association_data;
//    association_data.type_id    = type::TEXTURE::PARTICLE_EFFECT_ID;
//    textureOb->SetAssociation(association_data);

//    TextureCollector::Instance().Add(textureOb);
//}

//{
//    jeti::Material material_data;
//    material_data.texture_path = DATA_PATH+"effect/particles/particle3.png";
//    material_data.use_alpha = true;
//    material_data.color_id = COLOR::GREY_ID;
//    jeti::control::TextureOb* textureOb = new jeti::control::TextureOb(material_data);

//    jeti::MaterialAssociationData association_data;
//    association_data.type_id    = type::TEXTURE::PARTICLE_EFFECT_ID;
//    textureOb->SetAssociation(association_data);

//    TextureCollector::Instance().Add(textureOb);
//}

////{
//    //std::vector<int> arg;
//    //arg.push_back((int)type::TECHLEVEL::L0_ID); arg.push_back(COLOR::BLUE_ID);
//    //TextureCollector::Instance().Add( new jeti::control::TextureOb(type::TEXTURE::LAZER_EFFECT_ID, DATA_PATH+"effect/lazer/l_64_26_000.png", true, &arg, 4, 1, 10) );
////}

//{
//    jeti::Material material_data;
//    material_data.texture_path = DATA_PATH+"effect/lazer/l_001.png";
//    material_data.use_alpha = true;
//    material_data.color_id = COLOR::RED_ID;
//    jeti::control::TextureOb* textureOb = new jeti::control::TextureOb(material_data);

//    jeti::MaterialAssociationData association_data;
//    association_data.type_id        = type::TEXTURE::LAZER_EFFECT_ID;
//    association_data.tech_level_id  = type::TECHLEVEL::L0_ID;
//    textureOb->SetAssociation(association_data);

//    TextureCollector::Instance().Add(textureOb);
//}

//{
//    jeti::Material material_data;
//    material_data.texture_path = DATA_PATH+"effect/lazer/l_002.png";
//    material_data.use_alpha = true;
//    material_data.color_id = COLOR::YELLOW_ID;
//    jeti::control::TextureOb* textureOb = new jeti::control::TextureOb(material_data);

//    jeti::MaterialAssociationData association_data;
//    association_data.type_id        = type::TEXTURE::LAZER_EFFECT_ID;
//    association_data.tech_level_id  = type::TECHLEVEL::L0_ID;
//    textureOb->SetAssociation(association_data);

//    TextureCollector::Instance().Add(textureOb);
//}

//{
//    jeti::Material material_data;
//    material_data.texture_path = DATA_PATH+"effect/lazer/l_003.png";
//    material_data.use_alpha = true;
//    material_data.color_id = COLOR::BLUE_ID;
//    jeti::control::TextureOb* textureOb = new jeti::control::TextureOb(material_data);

//    jeti::MaterialAssociationData association_data;
//    association_data.type_id        = type::TEXTURE::LAZER_EFFECT_ID;
//    association_data.tech_level_id  = type::TECHLEVEL::L0_ID;
//    textureOb->SetAssociation(association_data);

//    TextureCollector::Instance().Add(textureOb);
//}

//{
//    jeti::Material material_data;
//    material_data.texture_path = DATA_PATH+"effect/shield/shield0.png";
//    material_data.use_alpha = true;
//    material_data.color_id = COLOR::RED_ID;
//    jeti::control::TextureOb* textureOb = new jeti::control::TextureOb(material_data);

//    jeti::MaterialAssociationData association_data;
//    association_data.type_id        = type::TEXTURE::SHIELD_EFFECT_ID;
//    textureOb->SetAssociation(association_data);

//    TextureCollector::Instance().Add(textureOb);
//}

//{
//    jeti::Material material_data;
//    material_data.texture_path = DATA_PATH+"effect/shield/shield1.png";
//    material_data.use_alpha = true;
//    material_data.color_id = COLOR::GREEN_ID;
//    jeti::control::TextureOb* textureOb = new jeti::control::TextureOb(material_data);

//    jeti::MaterialAssociationData association_data;
//    association_data.type_id        = type::TEXTURE::SHIELD_EFFECT_ID;
//    textureOb->SetAssociation(association_data);

//    TextureCollector::Instance().Add(textureOb);
//}

//{
//    jeti::Material material_data;
//    material_data.texture_path = DATA_PATH+"effect/shield/shield2.png";
//    material_data.use_alpha = true;
//    material_data.color_id = COLOR::BLUE_ID;
//    jeti::control::TextureOb* textureOb = new jeti::control::TextureOb(material_data);

//    jeti::MaterialAssociationData association_data;
//    association_data.type_id        = type::TEXTURE::SHIELD_EFFECT_ID;
//    textureOb->SetAssociation(association_data);

//    TextureCollector::Instance().Add(textureOb);
//}

//{
//    jeti::Material material_data;
//    material_data.texture_path = DATA_PATH+"effect/shield/shield3.png";
//    material_data.use_alpha = true;
//    material_data.color_id = COLOR::YELLOW_ID;
//    jeti::control::TextureOb* textureOb = new jeti::control::TextureOb(material_data);

//    jeti::MaterialAssociationData association_data;
//    association_data.type_id        = type::TEXTURE::SHIELD_EFFECT_ID;
//    textureOb->SetAssociation(association_data);

//    TextureCollector::Instance().Add(textureOb);
//}


//// type::TEXTURE::DISTANTSTAR_ID
//{
//    jeti::Material material_data;
//    material_data.texture_path = DATA_PATH+"star/s1.png";
//    material_data.use_alpha = true;
//    material_data.color_id = COLOR::YELLOW_ID;
//    jeti::control::TextureOb* textureOb = new jeti::control::TextureOb(material_data);

//    jeti::MaterialAssociationData association_data;
//    association_data.type_id        = type::TEXTURE::DISTANTSTAR_ID;
//    textureOb->SetAssociation(association_data);

//    TextureCollector::Instance().Add(textureOb);
//}

//{
//    jeti::Material material_data;
//    material_data.texture_path = DATA_PATH+"star/s2.png";
//    material_data.use_alpha = true;
//    material_data.color_id = COLOR::BLUE_ID;
//    jeti::control::TextureOb* textureOb = new jeti::control::TextureOb(material_data);

//    jeti::MaterialAssociationData association_data;
//    association_data.type_id        = type::TEXTURE::DISTANTSTAR_ID;
//    textureOb->SetAssociation(association_data);

//    TextureCollector::Instance().Add(textureOb);
//}

//{
//    jeti::Material material_data;
//    material_data.texture_path = DATA_PATH+"star/s3.png";
//    material_data.use_alpha = true;
//    material_data.color_id = COLOR::RED_ID;
//    jeti::control::TextureOb* textureOb = new jeti::control::TextureOb(material_data);

//    jeti::MaterialAssociationData association_data;
//    association_data.type_id        = type::TEXTURE::DISTANTSTAR_ID;
//    textureOb->SetAssociation(association_data);

//    TextureCollector::Instance().Add(textureOb);
//}

////###################################### ITEM TEXTURE ###################################
////############################ DRIVE_ITEM
////#################### RACE_0
////####### TECH_LEVEL_0
//{
//    jeti::Material material_data;
//    material_data.texture_path = DATA_PATH+"item/drive/drive_Race0_Tech0.png";
//    material_data.use_alpha = true;
//    jeti::control::TextureOb* textureOb = new jeti::control::TextureOb(material_data);

//    jeti::MaterialAssociationData association_data;
//    association_data.type_id        = type::TEXTURE::DRIVE_EQUIPMENT_ID;
//    association_data.race_id        = type::RACE::R0_ID;
//    association_data.tech_level_id  = type::TECHLEVEL::L0_ID;
//    textureOb->SetAssociation(association_data);

//    TextureCollector::Instance().Add(textureOb);
//}

////####### TECH_LEVEL_1
//{
//    jeti::Material material_data;
//    material_data.texture_path = DATA_PATH+"item/drive/drive_Race0_Tech1.png";
//    material_data.use_alpha = true;
//    jeti::control::TextureOb* textureOb = new jeti::control::TextureOb(material_data);

//    jeti::MaterialAssociationData association_data;
//    association_data.type_id        = type::TEXTURE::DRIVE_EQUIPMENT_ID;
//    association_data.race_id        = type::RACE::R0_ID;
//    association_data.tech_level_id  = type::TECHLEVEL::L1_ID;
//    textureOb->SetAssociation(association_data);

//    TextureCollector::Instance().Add(textureOb);
//}

////####### TECH_LEVEL_2
//{
//    jeti::Material material_data;
//    material_data.texture_path = DATA_PATH+"item/drive/drive_Race0_Tech2.png";
//    material_data.use_alpha = true;
//    jeti::control::TextureOb* textureOb = new jeti::control::TextureOb(material_data);

//    jeti::MaterialAssociationData association_data;
//    association_data.type_id        = type::TEXTURE::DRIVE_EQUIPMENT_ID;
//    association_data.race_id        = type::RACE::R0_ID;
//    association_data.tech_level_id  = type::TECHLEVEL::L2_ID;
//    textureOb->SetAssociation(association_data);

//    TextureCollector::Instance().Add(textureOb);
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
//    jeti::control::TextureOb* textureOb = new jeti::control::TextureOb(material_data);

//    jeti::MaterialAssociationData association_data;
//    association_data.type_id        = type::TEXTURE::LAZER_EQUIPMENT_ID;
//    association_data.race_id        = type::RACE::R0_ID;
//    association_data.tech_level_id  = type::TECHLEVEL::L0_ID;
//    textureOb->SetAssociation(association_data);

//    TextureCollector::Instance().Add(textureOb);
//}

//{
//    jeti::Material material_data;
//    material_data.texture_path = DATA_PATH+"item/lazer/lazer_Race0_Tech0_Yellow0.png";
//    material_data.use_alpha = true;
//    material_data.color_id = COLOR::YELLOW_ID;
//    jeti::control::TextureOb* textureOb = new jeti::control::TextureOb(material_data);

//    jeti::MaterialAssociationData association_data;
//    association_data.type_id        = type::TEXTURE::LAZER_EQUIPMENT_ID;
//    association_data.race_id        = type::RACE::R0_ID;
//    association_data.tech_level_id  = type::TECHLEVEL::L0_ID;
//    textureOb->SetAssociation(association_data);

//    TextureCollector::Instance().Add(textureOb);
//}

//{
//    jeti::Material material_data;
//    material_data.texture_path = DATA_PATH+"item/lazer/lazer_Race0_Tech0_Blue0.png";
//    material_data.use_alpha = true;
//    material_data.color_id = COLOR::BLUE_ID;
//    jeti::control::TextureOb* textureOb = new jeti::control::TextureOb(material_data);

//    jeti::MaterialAssociationData association_data;
//    association_data.type_id        = type::TEXTURE::LAZER_EQUIPMENT_ID;
//    association_data.race_id        = type::RACE::R0_ID;
//    association_data.tech_level_id  = type::TECHLEVEL::L0_ID;
//    textureOb->SetAssociation(association_data);

//    TextureCollector::Instance().Add(textureOb);
//}

////####### TECH_LEVEL_1
//{
//    jeti::Material material_data;
//    material_data.texture_path = DATA_PATH+"item/lazer/lazer_Race0_Tech1_Blue0.png";
//    material_data.use_alpha = true;
//    material_data.color_id = COLOR::BLUE_ID;
//    jeti::control::TextureOb* textureOb = new jeti::control::TextureOb(material_data);

//    jeti::MaterialAssociationData association_data;
//    association_data.type_id        = type::TEXTURE::LAZER_EQUIPMENT_ID;
//    association_data.race_id        = type::RACE::R0_ID;
//    association_data.tech_level_id  = type::TECHLEVEL::L1_ID;
//    textureOb->SetAssociation(association_data);

//    TextureCollector::Instance().Add(textureOb);
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
//    jeti::control::TextureOb* textureOb = new jeti::control::TextureOb(material_data);

//    jeti::MaterialAssociationData association_data;
//    association_data.type_id        = type::TEXTURE::ROCKET_EQUIPMENT_ID;
//    association_data.race_id        = type::RACE::R0_ID;
//    association_data.tech_level_id  = type::TECHLEVEL::L0_ID;
//    textureOb->SetAssociation(association_data);

//    TextureCollector::Instance().Add(textureOb);
//}
////####### TECH_LEVEL_1
//{
//    jeti::Material material_data;
//    material_data.texture_path = DATA_PATH+"item/rocket/rocket_Race0_Tech1.png";
//    material_data.use_alpha = true;
//    jeti::control::TextureOb* textureOb = new jeti::control::TextureOb(material_data);

//    jeti::MaterialAssociationData association_data;
//    association_data.type_id        = type::TEXTURE::ROCKET_EQUIPMENT_ID;
//    association_data.race_id        = type::RACE::R0_ID;
//    association_data.tech_level_id  = type::TECHLEVEL::L1_ID;
//    textureOb->SetAssociation(association_data);

//    TextureCollector::Instance().Add(textureOb);
//}
////####### TECH_LEVEL_2
//{
//    jeti::Material material_data;
//    material_data.texture_path = DATA_PATH+"item/rocket/rocket_Race0_Tech2.png";
//    material_data.use_alpha = true;
//    jeti::control::TextureOb* textureOb = new jeti::control::TextureOb(material_data);

//    jeti::MaterialAssociationData association_data;
//    association_data.type_id        = type::TEXTURE::ROCKET_EQUIPMENT_ID;
//    association_data.race_id        = type::RACE::R0_ID;
//    association_data.tech_level_id  = type::TECHLEVEL::L2_ID;
//    textureOb->SetAssociation(association_data);

//    TextureCollector::Instance().Add(textureOb);
//}

////TEXTURE_MANAGER.manageItem( textureOb(TORPED_ITEM_TEXTURE_ID, 'data/item/torped/tl0.png', True, [ 'torpedo',       type::TECHLEVEL::L0_ID, 3, 1, (int)type::RACE::R0_ID, COLOR::YELLOW_ID]) )
////TEXTURE_MANAGER.manageItem( textureOb(TORPED_ITEM_TEXTURE_ID, 'data/item/torped/tl1.png', True, [ 'torpedo',       type::TECHLEVEL::L0_ID, 3, 1, (int)type::RACE::R0_ID, COLOR::YELLOW_ID]) )

//{
//    jeti::Material material_data;
//    material_data.texture_path = DATA_PATH+"bullet/r_0.png";
//    material_data.use_alpha = true;
//    jeti::control::TextureOb* textureOb = new jeti::control::TextureOb(material_data);

//    jeti::MaterialAssociationData association_data;
//    association_data.type_id        = type::TEXTURE::ROCKET_BULLET_ID;
//    textureOb->SetAssociation(association_data);

//    TextureCollector::Instance().Add(textureOb);
//}

//{
//    jeti::Material material_data;
//    material_data.texture_path = DATA_PATH+"bullet/r_1.png";
//    material_data.use_alpha = true;
//    jeti::control::TextureOb* textureOb = new jeti::control::TextureOb(material_data);

//    jeti::MaterialAssociationData association_data;
//    association_data.type_id        = type::TEXTURE::ROCKET_BULLET_ID;
//    textureOb->SetAssociation(association_data);

//    TextureCollector::Instance().Add(textureOb);
//}

////{
//    //std::vector<int> arg;
//    //TextureCollector::Instance().Add( new jeti::control::TextureOb(type::TEXTURE::ROCKET_BULLET_ID, DATA_PATH+"bullet/t_0.png", true, &arg) );
////}

////{
//    //std::vector<int> arg;
//    //TextureCollector::Instance().Add( new jeti::control::TextureOb(type::TEXTURE::ROCKET_BULLET_ID, DATA_PATH+"bullet/t_1.png", true, &arg) );
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
//    jeti::control::TextureOb* textureOb = new jeti::control::TextureOb(material_data);

//    jeti::MaterialAssociationData association_data;
//    association_data.type_id        = type::TEXTURE::PROTECTOR_EQUIPMENT_ID;
//    association_data.race_id        = type::RACE::R0_ID;
//    association_data.tech_level_id  = type::TECHLEVEL::L0_ID;
//    textureOb->SetAssociation(association_data);

//    TextureCollector::Instance().Add(textureOb);
//}

////####### TECH_LEVEL_1
//{
//    jeti::Material material_data;
//    material_data.texture_path = DATA_PATH+"item/protector/protector_Race0_Tech1.png";
//    material_data.use_alpha = true;
//    jeti::control::TextureOb* textureOb = new jeti::control::TextureOb(material_data);

//    jeti::MaterialAssociationData association_data;
//    association_data.type_id        = type::TEXTURE::PROTECTOR_EQUIPMENT_ID;
//    association_data.race_id        = type::RACE::R0_ID;
//    association_data.tech_level_id  = type::TECHLEVEL::L1_ID;
//    textureOb->SetAssociation(association_data);

//    TextureCollector::Instance().Add(textureOb);
//}

////####### TECH_LEVEL_2
//{
//    jeti::Material material_data;
//    material_data.texture_path = DATA_PATH+"item/protector/protector_Race0_Tech2.png";
//    material_data.use_alpha = true;
//    jeti::control::TextureOb* textureOb = new jeti::control::TextureOb(material_data);

//    jeti::MaterialAssociationData association_data;
//    association_data.type_id        = type::TEXTURE::PROTECTOR_EQUIPMENT_ID;
//    association_data.race_id        = type::RACE::R0_ID;
//    association_data.tech_level_id  = type::TECHLEVEL::L2_ID;
//    textureOb->SetAssociation(association_data);

//    TextureCollector::Instance().Add(textureOb);
//}
////####### TECH_LEVEL_3
//{
//    jeti::Material material_data;
//    material_data.texture_path = DATA_PATH+"item/protector/protector_Race0_Tech3.png";
//    material_data.use_alpha = true;
//    jeti::control::TextureOb* textureOb = new jeti::control::TextureOb(material_data);

//    jeti::MaterialAssociationData association_data;
//    association_data.type_id        = type::TEXTURE::PROTECTOR_EQUIPMENT_ID;
//    association_data.race_id        = type::RACE::R0_ID;
//    association_data.tech_level_id  = type::TECHLEVEL::L3_ID;
//    textureOb->SetAssociation(association_data);

//    TextureCollector::Instance().Add(textureOb);
//}

////############################ DROID_EQUIPMENT
////#################### RACE_0
////####### TECH_LEVEL_0
//{
//    jeti::Material material_data;
//    material_data.texture_path = DATA_PATH+"item/droid/droid_Race0_Tech0.png";
//    material_data.use_alpha = true;
//    jeti::control::TextureOb* textureOb = new jeti::control::TextureOb(material_data);

//    jeti::MaterialAssociationData association_data;
//    association_data.type_id        = type::TEXTURE::DROID_EQUIPMENT_ID;
//    association_data.race_id        = type::RACE::R0_ID;
//    association_data.tech_level_id  = type::TECHLEVEL::L0_ID;
//    textureOb->SetAssociation(association_data);

//    TextureCollector::Instance().Add(textureOb);
//}

////####### TECH_LEVEL_1
//{
//    jeti::Material material_data;
//    material_data.texture_path = DATA_PATH+"item/droid/droid_Race0_Tech1.png";
//    material_data.use_alpha = true;
//    jeti::control::TextureOb* textureOb = new jeti::control::TextureOb(material_data);

//    jeti::MaterialAssociationData association_data;
//    association_data.type_id        = type::TEXTURE::DROID_EQUIPMENT_ID;
//    association_data.race_id        = type::RACE::R0_ID;
//    association_data.tech_level_id  = type::TECHLEVEL::L1_ID;
//    textureOb->SetAssociation(association_data);

//    TextureCollector::Instance().Add(textureOb);
//}

////####### TECH_LEVEL_2
//{
//    jeti::Material material_data;
//    material_data.texture_path = DATA_PATH+"item/droid/droid_Race0_Tech2.png";
//    material_data.use_alpha = true;
//    jeti::control::TextureOb* textureOb = new jeti::control::TextureOb(material_data);

//    jeti::MaterialAssociationData association_data;
//    association_data.type_id        = type::TEXTURE::DROID_EQUIPMENT_ID;
//    association_data.race_id        = type::RACE::R0_ID;
//    association_data.tech_level_id  = type::TECHLEVEL::L2_ID;
//    textureOb->SetAssociation(association_data);

//    TextureCollector::Instance().Add(textureOb);
//}


////############################ GRAPPLE_EQUIPMENT
////#################### RACE_0
////####### TECH_LEVEL_0
//{
//    jeti::Material material_data;
//    material_data.texture_path = DATA_PATH+"item/grapple/grapple_Race0_Tech0.png";
//    material_data.use_alpha = true;
//    jeti::control::TextureOb* textureOb = new jeti::control::TextureOb(material_data);

//    jeti::MaterialAssociationData association_data;
//    association_data.type_id        = type::TEXTURE::GRAPPLE_EQUIPMENT_ID;
//    association_data.race_id        = type::RACE::R0_ID;
//    association_data.tech_level_id  = type::TECHLEVEL::L0_ID;
//    textureOb->SetAssociation(association_data);

//    TextureCollector::Instance().Add(textureOb);
//}

////####### TECH_LEVEL_1
//{
//    jeti::Material material_data;
//    material_data.texture_path = DATA_PATH+"item/grapple/grapple_Race0_Tech1.png";
//    material_data.use_alpha = true;
//    jeti::control::TextureOb* textureOb = new jeti::control::TextureOb(material_data);

//    jeti::MaterialAssociationData association_data;
//    association_data.type_id        = type::TEXTURE::GRAPPLE_EQUIPMENT_ID;
//    association_data.race_id        = type::RACE::R0_ID;
//    association_data.tech_level_id  = type::TECHLEVEL::L1_ID;
//    textureOb->SetAssociation(association_data);

//    TextureCollector::Instance().Add(textureOb);
//}



////############################ BAK_EQUIPMENT
////#################### RACE_0
////####### TECH_LEVEL_0
//{
//    jeti::Material material_data;
//    material_data.texture_path = DATA_PATH+"item/bak/bak_Race0_Tech0.png";
//    material_data.use_alpha = true;
//    jeti::control::TextureOb* textureOb = new jeti::control::TextureOb(material_data);

//    jeti::MaterialAssociationData association_data;
//    association_data.type_id        = type::TEXTURE::BAK_EQUIPMENT_ID;
//    association_data.race_id        = type::RACE::R0_ID;
//    association_data.tech_level_id  = type::TECHLEVEL::L0_ID;
//    textureOb->SetAssociation(association_data);

//    TextureCollector::Instance().Add(textureOb);
//}

////####### TECH_LEVEL_1
//{
//    jeti::Material material_data;
//    material_data.texture_path = DATA_PATH+"item/bak/bak_Race0_Tech1.png";
//    material_data.use_alpha = true;
//    jeti::control::TextureOb* textureOb = new jeti::control::TextureOb(material_data);

//    jeti::MaterialAssociationData association_data;
//    association_data.type_id        = type::TEXTURE::BAK_EQUIPMENT_ID;
//    association_data.race_id        = type::RACE::R0_ID;
//    association_data.tech_level_id  = type::TECHLEVEL::L1_ID;
//    textureOb->SetAssociation(association_data);

//    TextureCollector::Instance().Add(textureOb);
//}


////############################ ENERGIZER_EQUIPMENT
////#################### RACE_0
////####### TECH_LEVEL_0
//{
//    jeti::Material material_data;
//    material_data.texture_path = DATA_PATH+"item/energyBlock/energyBlock_Race0_Tech0.png";
//    material_data.use_alpha = true;
//    jeti::control::TextureOb* textureOb = new jeti::control::TextureOb(material_data);

//    jeti::MaterialAssociationData association_data;
//    association_data.type_id        = type::TEXTURE::ENERGIZER_EQUIPMENT_ID;
//    association_data.race_id        = type::RACE::R0_ID;
//    association_data.tech_level_id  = type::TECHLEVEL::L0_ID;
//    textureOb->SetAssociation(association_data);

//    TextureCollector::Instance().Add(textureOb);
//}

////####### TECH_LEVEL_1
//{
//    jeti::Material material_data;
//    material_data.texture_path = DATA_PATH+"item/energyBlock/energyBlock_Race0_Tech1.png";
//    material_data.use_alpha = true;
//    jeti::control::TextureOb* textureOb = new jeti::control::TextureOb(material_data);

//    jeti::MaterialAssociationData association_data;
//    association_data.type_id        = type::TEXTURE::ENERGIZER_EQUIPMENT_ID;
//    association_data.race_id        = type::RACE::R0_ID;
//    association_data.tech_level_id  = type::TECHLEVEL::L1_ID;
//    textureOb->SetAssociation(association_data);

//    TextureCollector::Instance().Add(textureOb);
//}


////############################ FREEZER_EQUIPMENT
////#################### RACE_0
////####### TECH_LEVEL_0
//{
//    jeti::Material material_data;
//    material_data.texture_path = DATA_PATH+"item/freezer/freezer_Race0_Tech0.png";
//    material_data.use_alpha = true;
//    jeti::control::TextureOb* textureOb = new jeti::control::TextureOb(material_data);

//    jeti::MaterialAssociationData association_data;
//    association_data.type_id        = type::TEXTURE::FREEZER_EQUIPMENT_ID;
//    association_data.race_id        = type::RACE::R0_ID;
//    association_data.tech_level_id  = type::TECHLEVEL::L0_ID;
//    textureOb->SetAssociation(association_data);

//    TextureCollector::Instance().Add(textureOb);
//}

////####### TECH_LEVEL_1
//{
//    jeti::Material material_data;
//    material_data.texture_path = DATA_PATH+"item/freezer/freezer_Race0_Tech1.png";
//    material_data.use_alpha = true;
//    jeti::control::TextureOb* textureOb = new jeti::control::TextureOb(material_data);

//    jeti::MaterialAssociationData association_data;
//    association_data.type_id        = type::TEXTURE::FREEZER_EQUIPMENT_ID;
//    association_data.race_id        = type::RACE::R0_ID;
//    association_data.tech_level_id  = type::TECHLEVEL::L1_ID;
//    textureOb->SetAssociation(association_data);

//    TextureCollector::Instance().Add(textureOb);
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
//    jeti::control::TextureOb* textureOb = new jeti::control::TextureOb(material_data);

//    jeti::MaterialAssociationData association_data;
//    association_data.type_id        = type::TEXTURE::SCANER_EQUIPMENT_ID;
//    association_data.race_id        = type::RACE::R0_ID;
//    association_data.tech_level_id  = type::TECHLEVEL::L0_ID;
//    textureOb->SetAssociation(association_data);

//    TextureCollector::Instance().Add(textureOb);
//}
////####### TECH_LEVEL_1
//{
//    jeti::Material material_data;
//    material_data.texture_path = DATA_PATH+"item/scaner/scaner_Race0_Tech1.png";
//    material_data.use_alpha = true;
//    material_data.col_num = 3;
//    material_data.row_num = 1;
//    material_data.fps = 3.0f;
//    jeti::control::TextureOb* textureOb = new jeti::control::TextureOb(material_data);

//    jeti::MaterialAssociationData association_data;
//    association_data.type_id        = type::TEXTURE::SCANER_EQUIPMENT_ID;
//    association_data.race_id        = type::RACE::R0_ID;
//    association_data.tech_level_id  = type::TECHLEVEL::L1_ID;
//    textureOb->SetAssociation(association_data);

//    TextureCollector::Instance().Add(textureOb);
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
//    jeti::control::TextureOb* textureOb = new jeti::control::TextureOb(material_data);

//    jeti::MaterialAssociationData association_data;
//    association_data.type_id        = type::TEXTURE::RADAR_EQUIPMENT_ID;
//    association_data.race_id        = type::RACE::R0_ID;
//    association_data.tech_level_id  = type::TECHLEVEL::L0_ID;
//    textureOb->SetAssociation(association_data);

//    TextureCollector::Instance().Add(textureOb);
//}

////####### TECH_LEVEL_1
//{
//    jeti::Material material_data;
//    material_data.texture_path = DATA_PATH+"item/radar/radar_Race0_Tech1.png";
//    material_data.use_alpha = true;
//    material_data.col_num = 3;
//    material_data.row_num = 1;
//    material_data.fps = 3.0f;
//    jeti::control::TextureOb* textureOb = new jeti::control::TextureOb(material_data);

//    jeti::MaterialAssociationData association_data;
//    association_data.type_id        = type::TEXTURE::RADAR_EQUIPMENT_ID;
//    association_data.race_id        = type::RACE::R0_ID;
//    association_data.tech_level_id  = type::TECHLEVEL::L1_ID;
//    textureOb->SetAssociation(association_data);

//    TextureCollector::Instance().Add(textureOb);
//}


////################## MODULES
//{
//    jeti::Material material_data;
//    material_data.texture_path = DATA_PATH+"item/module.png";
//    material_data.use_alpha = true;
//    jeti::control::TextureOb* textureOb = new jeti::control::TextureOb(material_data);

//    jeti::MaterialAssociationData association_data;
//    association_data.type_id = type::TEXTURE::MODULE_ID;
//    textureOb->SetAssociation(association_data);

//    TextureCollector::Instance().Add(textureOb);
//}



//// UNIQUE TEXTURES
//{
//    jeti::Material material_data;
//    material_data.texture_path = DATA_PATH+"other/ss_mark_war.png";
//    material_data.use_alpha = true;
//    jeti::control::TextureOb* textureOb = new jeti::control::TextureOb(material_data);

//    GuiTextureObCollector::Instance().starsystem_mark_war = textureOb;
//}

//{
//    jeti::Material material_data;
//    material_data.texture_path = DATA_PATH+"other/ss_mark_captured.png";
//    material_data.use_alpha = true;
//    jeti::control::TextureOb* textureOb = new jeti::control::TextureOb(material_data);
 
//    GuiTextureObCollector::Instance().starsystem_mark_captured = textureOb;
//}

//{
//    jeti::Material material_data;
//    material_data.texture_path = DATA_PATH+"other/mark_player_ss.png";
//    material_data.use_alpha = true;
//    jeti::control::TextureOb* textureOb = new jeti::control::TextureOb(material_data);

//    GuiTextureObCollector::Instance().starsystem_mark_player = textureOb;
//}

//{
//    jeti::Material material_data;
//    material_data.texture_path = DATA_PATH+"icon/minus.png";
//    material_data.use_alpha = true;
//    jeti::control::TextureOb* textureOb = new jeti::control::TextureOb(material_data);
 
//    GuiTextureObCollector::Instance().icon_minus = textureOb;
//}

//{
//    jeti::Material material_data;
//    material_data.texture_path = DATA_PATH+"icon/plus.png";
//    material_data.use_alpha = true;
//    jeti::control::TextureOb* textureOb = new jeti::control::TextureOb(material_data);

//    GuiTextureObCollector::Instance().icon_plus = textureOb;
//}

//{
//    jeti::Material material_data;
//    material_data.texture_path = DATA_PATH+"other/skill.png";
//    material_data.use_alpha = true;
//    jeti::control::TextureOb* textureOb = new jeti::control::TextureOb(material_data);

//    GuiTextureObCollector::Instance().skill = textureOb;
//}

//{
//    jeti::Material material_data;
//    material_data.texture_path = DATA_PATH+"other/skill_transparent.png";
//    material_data.use_alpha = true;
//    jeti::control::TextureOb* textureOb = new jeti::control::TextureOb(material_data);
 
//    GuiTextureObCollector::Instance().skill_transparent = textureOb;
//}

//{
//    jeti::Material material_data;
//    material_data.texture_path = DATA_PATH+"icon/starsystem_ICON.png";
//    material_data.use_alpha = true;
//    jeti::control::TextureOb* textureOb = new jeti::control::TextureOb(material_data);

//    GuiTextureObCollector::Instance().icon_map = textureOb;
//}

//{
//    jeti::Material material_data;
//    material_data.texture_path = DATA_PATH+"effect/grapple_jet.png";
//    material_data.use_alpha = true;
//    jeti::control::TextureOb* textureOb = new jeti::control::TextureOb(material_data);

//    GuiTextureObCollector::Instance().grapple_trail = textureOb;
//}

//{
//    jeti::Material material_data;
//    material_data.texture_path = DATA_PATH+"other/dot_blue.png";
//    material_data.use_alpha = true;
//    jeti::control::TextureOb* textureOb = new jeti::control::TextureOb(material_data);
 
//    GuiTextureObCollector::Instance().dot_blue = textureOb;
//}

//{
//    jeti::Material material_data;
//    material_data.texture_path = DATA_PATH+"other/dot_green.png";
//    material_data.use_alpha = true;
//    jeti::control::TextureOb* textureOb = new jeti::control::TextureOb(material_data);

//    GuiTextureObCollector::Instance().dot_green = textureOb;
//}

//{
//    jeti::Material material_data;
//    material_data.texture_path = DATA_PATH+"other/dot_red.png";
//    material_data.use_alpha = true;
//    jeti::control::TextureOb* textureOb = new jeti::control::TextureOb(material_data);
 
//    GuiTextureObCollector::Instance().dot_red = textureOb;
//}

//{
//    jeti::Material material_data;
//    material_data.texture_path = DATA_PATH+"other/dot_black.png";
//    material_data.use_alpha = true;
//    jeti::control::TextureOb* textureOb = new jeti::control::TextureOb(material_data);
 
//    GuiTextureObCollector::Instance().dot_black = textureOb;
//}

//{
//    jeti::Material material_data;
//    material_data.texture_path = DATA_PATH+"other/dot_yellow.png";
//    material_data.use_alpha = true;
//    jeti::control::TextureOb* textureOb = new jeti::control::TextureOb(material_data);
  
//    GuiTextureObCollector::Instance().dot_yellow = textureOb;
//}

//{
//    jeti::Material material_data;
//    material_data.texture_path = DATA_PATH+"other/dot_purple.png";
//    material_data.use_alpha = true;
//    jeti::control::TextureOb* textureOb = new jeti::control::TextureOb(material_data);
 
//    GuiTextureObCollector::Instance().dot_purple = textureOb;
//}


//{
//    jeti::Material material_data;
//    material_data.texture_path = DATA_PATH+"gui/radar_screenrect.png";
//    material_data.use_alpha = true;
//    jeti::control::TextureOb* textureOb = new jeti::control::TextureOb(material_data);

//    GuiTextureObCollector::Instance().radar_screenrect = textureOb;
//}

//{
//    jeti::Material material_data;
//    material_data.texture_path = DATA_PATH+"gui/radar_range.png";
//    material_data.use_alpha = true;
//    jeti::control::TextureOb* textureOb = new jeti::control::TextureOb(material_data);

//    GuiTextureObCollector::Instance().radar_range = textureOb;
//}

//{
//    jeti::Material material_data;
//    material_data.texture_path = DATA_PATH+"gui/radar_background.png";
//    material_data.use_alpha = true;
//    jeti::control::TextureOb* textureOb = new jeti::control::TextureOb(material_data);
 
//    GuiTextureObCollector::Instance().radar_background = textureOb;
//}

//{
//    jeti::Material material_data;
//    material_data.texture_path = DATA_PATH+"gui/radar_bar.png";
//    material_data.use_alpha = true;
//    jeti::control::TextureOb* textureOb = new jeti::control::TextureOb(material_data);

//    GuiTextureObCollector::Instance().radar_bar = textureOb;
//}

//{
//    jeti::Material material_data;
//    material_data.texture_path = DATA_PATH+"gui/bar_bottom.png";
//    material_data.use_alpha = true;
//    jeti::control::TextureOb* textureOb = new jeti::control::TextureOb(material_data);

//    GuiTextureObCollector::Instance().bar_bottom = textureOb;
//}

//{
//    jeti::Material material_data;
//    material_data.texture_path = DATA_PATH+"gui/bar_left.png";
//    material_data.use_alpha = true;
//    jeti::control::TextureOb* textureOb = new jeti::control::TextureOb(material_data);

//    GuiTextureObCollector::Instance().bar_left = textureOb;
//}

//{
//    jeti::Material material_data;
//    material_data.texture_path = DATA_PATH+"gui/bar_top.png";
//    material_data.use_alpha = true;
//    jeti::control::TextureOb* textureOb = new jeti::control::TextureOb(material_data);
 
//    GuiTextureObCollector::Instance().bar_top = textureOb;
//}

//{
//    jeti::Material material_data;
//    material_data.texture_path = DATA_PATH+"other/text_background.png";
//    material_data.use_alpha = true;
//    jeti::control::TextureOb* textureOb = new jeti::control::TextureOb(material_data);
  
//    GuiTextureObCollector::Instance().text_background = textureOb;
//}

//{
//    jeti::Material material_data;
//    material_data.texture_path = DATA_PATH+"other/slot_mark_accept.png";
//    material_data.use_alpha = true;
//    jeti::control::TextureOb* textureOb = new jeti::control::TextureOb(material_data);
 
//    GuiTextureObCollector::Instance().slot_mark_accept = textureOb;
//}

//{
//    jeti::Material material_data;
//    material_data.texture_path = DATA_PATH+"other/mask_round.png";
//    material_data.use_alpha = true;
//    jeti::control::TextureOb* textureOb = new jeti::control::TextureOb(material_data);

//    GuiTextureObCollector::Instance().mask_round = textureOb;
//}

//{
//    jeti::Material material_data;
//    material_data.texture_path = DATA_PATH+"other/slot_mark_reject.png";
//    material_data.use_alpha = true;
//    jeti::control::TextureOb* textureOb = new jeti::control::TextureOb(material_data);
 
//    GuiTextureObCollector::Instance().slot_mark_reject = textureOb;
//}

//{
//    jeti::Material material_data;
//    material_data.texture_path = DATA_PATH+"gui/mark_target.png";
//    material_data.use_alpha = true;
//    jeti::control::TextureOb* textureOb = new jeti::control::TextureOb(material_data);
  
//    GuiTextureObCollector::Instance().mark_target = textureOb;
//}
 
//{
//    jeti::Material material_data;
//    material_data.texture_path = DATA_PATH+"gui/mark_target_slot.png";
//    material_data.use_alpha = true;
//    jeti::control::TextureOb* textureOb = new jeti::control::TextureOb(material_data);

//    GuiTextureObCollector::Instance().mark_target_slot = textureOb;
//}
}


