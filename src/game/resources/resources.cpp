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
#include "ShaderCollector.hpp"
#include "../render/ShaderLoader.hpp"
#include "../render/Screen.hpp"
#include "MeshCollector.hpp"
#include "../render/Mesh.hpp"
#include "TextureManager.hpp"
#include "GuiTextureObCollector.hpp"

void loadGameData()
{    	
 	int width     = Config::Instance().SCREEN_WIDTH; 
      	int height    = Config::Instance().SCREEN_HEIGHT;
      	int bpp       = Config::Instance().BPP;
      	bool vert_sync = Config::Instance().VSYNC;
 	      	
      	Screen::Instance().InitBasic(width, height, bpp, vert_sync, GAME_TITLE);

	load3DModels();
    	loadImages();
    	if (Config::Instance().MODERN_EFFECTS == true)
	{
		loadShaders();
		Screen::Instance().InitPostEffects(Screen::Instance().GetWidth(), Screen::Instance().GetHeight());
	}
    	Screen::Instance().GetFont().loadFromFile("data/font/font.ttf");
}



void load3DModels()
{    	
	MeshCollector::Instance().RegisterMesh(new Mesh("data/obj/sphere/sphere.obj", nullptr, MESH::SPHERE_ID));
	MeshCollector::Instance().RegisterMesh(new Mesh("data/obj/sphere_deformed/sphere_deformed.obj", nullptr, MESH::SPHERE_DEFORMED_ID));
	
	{
	TextureOb* textureOb = new TextureOb(TEXTURE::NOTYPE_ID, "data/obj/vehicles/BabylonStation/station_texture/babylonstation.jpg", false);	
	MeshCollector::Instance().RegisterMesh(new Mesh("data/obj/vehicles/BabylonStation/babylon_station_mod.obj", textureOb, MESH::SPACESTATION_ID));
	}

	{
	TextureOb* textureOb = new TextureOb(TEXTURE::NOTYPE_ID, "data/obj/vehicles//Anna_V_2.0_variations/Anna_Textures/ship_hull12.jpg", false);	
	MeshCollector::Instance().RegisterMesh(new Mesh("data/obj/vehicles/Anna_V_2.0_variations/anna_mod.obj", textureOb, MESH::SPACESTATION_ID));
	}
}



void loadImages()
{
//####################################### TURREL_TEXTURE ###################################
{
	std::vector<int> arg;   
	arg.push_back(RACE::R0_ID);
	TextureManager::Instance().Add( new TextureOb(TEXTURE::TURREL_ID, "data/turrel/turrel1.png", true, &arg) );
}

{
	std::vector<int> arg;   
	arg.push_back(RACE::R0_ID);
	TextureManager::Instance().Add( new TextureOb(TEXTURE::TURREL_ID, "data/turrel/turrel2.png", true, &arg) );
}

//{
	//std::vector<int> arg;   
	//arg.push_back(RACE::R0_ID);
	//TextureManager::Instance().Add( new TextureOb(TEXTURE::TURREL_ID, "data/turrel/esphere-0.png", true, &arg) );
//}


//####################################### SLOT_TEXTURE ###################################
{
	std::vector<int> arg;   
	arg.push_back(RACE::R0_ID);
	TextureManager::Instance().Add( new TextureOb(TEXTURE::ITEM_SLOT_ID, "data/other/slot.png", true, &arg) );
}

{
	std::vector<int> arg;   
	arg.push_back(RACE::R0_ID);
	TextureManager::Instance().Add( new TextureOb(TEXTURE::VEHICLE_SLOT_ID, "data/other/H.png", true, &arg, 3, 2, 3) );
}

//####################################### TEXTURE::FACE_ID ################################
//RACE::R0_ID
{
	std::vector<int> arg; 
	arg.push_back(RACE::R0_ID);
	TextureManager::Instance().Add( new TextureOb(TEXTURE::FACE_ID, "data/race/0000.png", false, &arg) );
}

{
	std::vector<int> arg; 
	arg.push_back(RACE::R0_ID);
	TextureManager::Instance().Add( new TextureOb(TEXTURE::FACE_ID, "data/race/0001.png", false, &arg) );
}

//RACE::R1_ID
{
	std::vector<int> arg; 
	arg.push_back(RACE::R1_ID);
	TextureManager::Instance().Add( new TextureOb(TEXTURE::FACE_ID, "data/race/1000.png", false, &arg) );
}

{
	std::vector<int> arg; 
	arg.push_back(RACE::R1_ID);
	TextureManager::Instance().Add( new TextureOb(TEXTURE::FACE_ID, "data/race/1001.png", false, &arg) );
}

//RACE::R2_ID
{
	std::vector<int> arg; 
	arg.push_back(RACE::R2_ID);
	TextureManager::Instance().Add( new TextureOb(TEXTURE::FACE_ID, "data/race/2000.png", false, &arg) );
}

{
	std::vector<int> arg; 
	arg.push_back(RACE::R2_ID);
	TextureManager::Instance().Add( new TextureOb(TEXTURE::FACE_ID, "data/race/2001.png", false, &arg) );
}

//RACE::R3_ID
{
	std::vector<int> arg; 
	arg.push_back(RACE::R3_ID);
	TextureManager::Instance().Add( new TextureOb(TEXTURE::FACE_ID, "data/race/3000.png", false, &arg) );
}

{
	std::vector<int> arg; 
	arg.push_back(RACE::R3_ID);
	TextureManager::Instance().Add( new TextureOb(TEXTURE::FACE_ID, "data/race/3001.png", false, &arg) );
}

//RACE::R4_ID
{
	std::vector<int> arg; 
	arg.push_back(RACE::R4_ID);
	TextureManager::Instance().Add( new TextureOb(TEXTURE::FACE_ID, "data/race/4000.png", false, &arg) );
}

{
	std::vector<int> arg; 
	arg.push_back(RACE::R4_ID);
	TextureManager::Instance().Add( new TextureOb(TEXTURE::FACE_ID, "data/race/4001.png", false, &arg) );
}

//RACE::R6_ID
{
	std::vector<int> arg; 
	arg.push_back(RACE::R6_ID);
	TextureManager::Instance().Add( new TextureOb(TEXTURE::FACE_ID, "data/race/6000.png", false, &arg) );
}

{
	std::vector<int> arg; 
	arg.push_back(RACE::R6_ID);
	TextureManager::Instance().Add( new TextureOb(TEXTURE::FACE_ID, "data/race/6001.png", false, &arg) );
}

//RACE::R7_ID
{
	std::vector<int> arg; 
	arg.push_back(RACE::R7_ID);
	TextureManager::Instance().Add( new TextureOb(TEXTURE::FACE_ID, "data/race/7000.png", false, &arg) );
}

{
	std::vector<int> arg; 
	arg.push_back(RACE::R7_ID);
	TextureManager::Instance().Add( new TextureOb(TEXTURE::FACE_ID, "data/race/7001.png", false, &arg) );
}



//####################################### ASTEROID_TEXTURE ################################
{
	std::vector<int> arg; 
	TextureManager::Instance().Add( new TextureOb(TEXTURE::ASTEROID_ID, "data/asteroid/a_000.png", true, &arg) );
}

{
	std::vector<int> arg; 
	TextureManager::Instance().Add( new TextureOb(TEXTURE::ASTEROID_ID, "data/asteroid/a_001.png", true, &arg) );
}

{
	std::vector<int> arg; 
	TextureManager::Instance().Add( new TextureOb(TEXTURE::ASTEROID_ID, "data/asteroid/a_002.png", true, &arg) );
}

//####################################### MINERAL_TEXTURE ################################
{
	std::vector<int> arg; 
	TextureManager::Instance().Add( new TextureOb(TEXTURE::MINERAL_ID, "data/asteroid/m_000.png", true, &arg) );
}

{
	std::vector<int> arg; 
	TextureManager::Instance().Add( new TextureOb(TEXTURE::MINERAL_ID, "data/asteroid/m_001.png", true, &arg) );
}

{
	std::vector<int> arg; 
	TextureManager::Instance().Add( new TextureOb(TEXTURE::MINERAL_ID, "data/asteroid/m_002.png", true, &arg) );
}

{
	std::vector<int> arg; 
	TextureManager::Instance().Add( new TextureOb(TEXTURE::CONTAINER_ID, "data/item/container.png", true, &arg) );
}

{
	std::vector<int> arg; 
	TextureManager::Instance().Add( new TextureOb(TEXTURE::BOMB_ID, "data/item/bomb_item.png", true, &arg) );
}



//####################################### TEXTURE::SATELLITE_ID ################################
{
	std::vector<int> arg;   
	arg.push_back(RACE::R0_ID);
	TextureManager::Instance().Add( new TextureOb(TEXTURE::SATELLITE_ID, "data/satellite/sa_001.png", true, &arg, 3, 1, 6) );
}

{
	std::vector<int> arg;   
	arg.push_back(RACE::R0_ID);
	TextureManager::Instance().Add( new TextureOb(TEXTURE::SATELLITE_ID, "data/satellite/sa_002.png", true, &arg, 4, 1, 8) );
}

{
	std::vector<int> arg;   
	arg.push_back(RACE::R0_ID);
	TextureManager::Instance().Add( new TextureOb(TEXTURE::SATELLITE_ID, "data/satellite/sa_003.png", true, &arg, 3, 1, 6) );
}

{
	std::vector<int> arg;   
	arg.push_back(RACE::R0_ID);
	TextureManager::Instance().Add( new TextureOb(TEXTURE::SATELLITE_ID, "data/satellite/sa_004.png", true, &arg) );
}

{
	std::vector<int> arg;   
	arg.push_back(RACE::R0_ID);
	TextureManager::Instance().Add( new TextureOb(TEXTURE::SATELLITE_ID, "data/satellite/sa_005.png", true, &arg, 8, 1, 16) );
}

{
	std::vector<int> arg;   
	arg.push_back(RACE::R0_ID);
	TextureManager::Instance().Add( new TextureOb(TEXTURE::SATELLITE_ID, "data/satellite/sa_006.png", true, &arg, 8, 1, 16) );
}


// BLACKHOLE

{
	std::vector<int> arg;   
	TextureManager::Instance().Add( new TextureOb(TEXTURE::BLACKHOLE_ID, "data/blackhole/bh_00.png", true, &arg) );
}

//####################################### SHIP_TEXTURE ####################################
//################################ race texnologi
{
	std::vector<int> arg;   
	arg.push_back(RACE::R0_ID); arg.push_back(ENTITY::RANGER_ID);   //COLOR_VIOLET
	TextureManager::Instance().Add( new TextureOb(TEXTURE::SHIP_ID, "data/ship/k_00_0_0.png", true, &arg) );
}

{
	std::vector<int> arg;   
	arg.push_back(RACE::R0_ID); arg.push_back(ENTITY::WARRIOR_ID);  //COLOR_VIOLET
	TextureManager::Instance().Add( new TextureOb(TEXTURE::SHIP_ID, "data/ship/k_01_0_1.png", true, &arg) );
}

{
	std::vector<int> arg;   
	arg.push_back(RACE::R0_ID); arg.push_back(ENTITY::PIRAT_ID);    //COLOR_VIOLET
	TextureManager::Instance().Add( new TextureOb(TEXTURE::SHIP_ID, "data/ship/k_02_0_0.png", true, &arg) );
}

{
	std::vector<int> arg;   
	arg.push_back(RACE::R0_ID); arg.push_back(ENTITY::TRADER_ID);   //COLOR_VIOLET
	TextureManager::Instance().Add( new TextureOb(TEXTURE::SHIP_ID, "data/ship/k_03_0_0.png", true, &arg) );
}

{
	std::vector<int> arg;   
	arg.push_back(RACE::R0_ID); arg.push_back(ENTITY::DIPLOMAT_ID); //COLOR_VIOLET
	TextureManager::Instance().Add( new TextureOb(TEXTURE::SHIP_ID, "data/ship/k_04_0_0.png", true, &arg) );
}

//################################ race voennye
{
	std::vector<int> arg;   
	arg.push_back(RACE::R1_ID); arg.push_back(ENTITY::RANGER_ID);   //COLOR_GREY
	TextureManager::Instance().Add( new TextureOb(TEXTURE::SHIP_ID, "data/ship/k_10_0_0.png", true, &arg) );
}

{
	std::vector<int> arg;   
	arg.push_back(RACE::R1_ID); arg.push_back(ENTITY::WARRIOR_ID);  //COLOR_GREY
	TextureManager::Instance().Add( new TextureOb(TEXTURE::SHIP_ID, "data/ship/k_11_0_0.png", true, &arg) );
}

{
	std::vector<int> arg;   
	arg.push_back(RACE::R1_ID); arg.push_back(ENTITY::PIRAT_ID);    //COLOR_GREY
	TextureManager::Instance().Add( new TextureOb(TEXTURE::SHIP_ID, "data/ship/k_12_0_0.png", true, &arg) );
}

{
	std::vector<int> arg;   
	arg.push_back(RACE::R1_ID); arg.push_back(ENTITY::TRADER_ID);   //COLOR_GREY
	TextureManager::Instance().Add( new TextureOb(TEXTURE::SHIP_ID, "data/ship/k_12_0_0.png", true, &arg) );
}

{
	std::vector<int> arg;   
	arg.push_back(RACE::R1_ID); arg.push_back(ENTITY::DIPLOMAT_ID);  //COLOR_GREY
	TextureManager::Instance().Add( new TextureOb(TEXTURE::SHIP_ID, "data/ship/k_14_0_0.png", true, &arg) );
}

//################################ race zhuliki
{
	std::vector<int> arg;   
	arg.push_back(RACE::R2_ID); arg.push_back(ENTITY::RANGER_ID);    
	TextureManager::Instance().Add( new TextureOb(TEXTURE::SHIP_ID, "data/ship/race2_ranger_00.png", true, &arg) );
}

{
	std::vector<int> arg;   
	arg.push_back(RACE::R2_ID); arg.push_back(ENTITY::WARRIOR_ID);  //COLOR_GREEN
	TextureManager::Instance().Add( new TextureOb(TEXTURE::SHIP_ID, "data/ship/race2_warrior_00.png", true, &arg) );
}

{
	std::vector<int> arg;   
	arg.push_back(RACE::R2_ID); arg.push_back(ENTITY::TRADER_ID);    //COLOR_RED
	TextureManager::Instance().Add( new TextureOb(TEXTURE::SHIP_ID, "data/ship/race2_trader_00.png", true, &arg) );
}

{
	std::vector<int> arg;   
	arg.push_back(RACE::R2_ID); arg.push_back(ENTITY::PIRAT_ID);    //COLOR_RED
	TextureManager::Instance().Add( new TextureOb(TEXTURE::SHIP_ID, "data/ship/race2_pirat_00.png", true, &arg) );
}

{
	std::vector<int> arg;   
	arg.push_back(RACE::R2_ID); arg.push_back(ENTITY::DIPLOMAT_ID);   //COLOR_GREEN
	TextureManager::Instance().Add( new TextureOb(TEXTURE::SHIP_ID, "data/ship/race2_diplomat_00.png", true, &arg) );
}

//################################ race cheloveki
{
	std::vector<int> arg;   
	arg.push_back(RACE::R3_ID); arg.push_back(ENTITY::RANGER_ID); //COLOR_BLUE
	TextureManager::Instance().Add( new TextureOb(TEXTURE::SHIP_ID, "data/ship/k_30_0_0.png", true, &arg) );
}

{
	std::vector<int> arg;   
	arg.push_back(RACE::R3_ID); arg.push_back(ENTITY::WARRIOR_ID); //COLOR_BLUE
	TextureManager::Instance().Add( new TextureOb(TEXTURE::SHIP_ID, "data/ship/k_31_0_0.png", true, &arg) );
}

{
	std::vector<int> arg;   
	arg.push_back(RACE::R3_ID); arg.push_back(ENTITY::WARRIOR_ID); //COLOR_BLUE
	TextureManager::Instance().Add( new TextureOb(TEXTURE::SHIP_ID, "data/ship/k_31_0_1.png", true, &arg) );
}

{
	std::vector<int> arg;   
	arg.push_back(RACE::R3_ID); arg.push_back(ENTITY::PIRAT_ID);   //COLOR_BLUE
	TextureManager::Instance().Add( new TextureOb(TEXTURE::SHIP_ID, "data/ship/k_32_0_0.png", true, &arg) );
}

{
	std::vector<int> arg;   
	arg.push_back(RACE::R3_ID); arg.push_back(ENTITY::TRADER_ID);  //COLOR_BLUE
	TextureManager::Instance().Add( new TextureOb(TEXTURE::SHIP_ID, "data/ship/_k_33_0_0.png", true, &arg) );
}

{
	std::vector<int> arg;   
	arg.push_back(RACE::R3_ID); arg.push_back(ENTITY::DIPLOMAT_ID); //COLOR_BLUE
	TextureManager::Instance().Add( new TextureOb(TEXTURE::SHIP_ID, "data/ship/_k_34_0_0.png", true, &arg) );
}

//################################ race bio
{
	std::vector<int> arg;   
	arg.push_back(RACE::R4_ID); arg.push_back(ENTITY::WARRIOR_ID); //COLOR_GOLDENROD
	TextureManager::Instance().Add( new TextureOb(TEXTURE::SHIP_ID, "data/ship/k_41_0_0.png", true, &arg) );
}

{
	std::vector<int> arg;   
	arg.push_back(RACE::R4_ID); arg.push_back(ENTITY::TRADER_ID);  //COLOR_GOLDENROD
	TextureManager::Instance().Add( new TextureOb(TEXTURE::SHIP_ID, "data/ship/k_43_0_0.png", true, &arg) );
}

{
	std::vector<int> arg;   
	arg.push_back(RACE::R4_ID); arg.push_back(ENTITY::TRADER_ID);  //COLOR_GOLDENROD
	TextureManager::Instance().Add( new TextureOb(TEXTURE::SHIP_ID, "data/ship/k_43_0_1.png", true, &arg) );
}

{
	std::vector<int> arg;   
	arg.push_back(RACE::R4_ID); arg.push_back(ENTITY::DIPLOMAT_ID); //COLOR_GOLDENROD
	TextureManager::Instance().Add( new TextureOb(TEXTURE::SHIP_ID, "data/ship/k_44_0_0.png", true, &arg) );
}

//################################ enemy 1
{
	std::vector<int> arg;   
	arg.push_back(RACE::R6_ID); arg.push_back(ENTITY::WARRIOR_ID); //COLOR_GOLDENROD
	TextureManager::Instance().Add( new TextureOb(TEXTURE::SHIP_ID, "data/ship/k_61_0_0.png", true, &arg) );
}

{
	std::vector<int> arg;   
	arg.push_back(RACE::R6_ID); arg.push_back(ENTITY::WARRIOR_ID); //COLOR_GOLDENROD
	TextureManager::Instance().Add( new TextureOb(TEXTURE::SHIP_ID, "data/ship/k_61_0_1.png", true, &arg) );
}

{
	std::vector<int> arg;   
	arg.push_back(RACE::R6_ID); arg.push_back(ENTITY::WARRIOR_ID); //COLOR_GOLDENROD
	TextureManager::Instance().Add( new TextureOb(TEXTURE::SHIP_ID, "data/ship/k_61_0_2.png", true, &arg) );
}


//{
	//std::vector<int> arg;   
	//arg.push_back(RACE::R6_ID); arg.push_back(ENTITY::WARRIOR_ID); //COLOR_GOLDENROD
	//TextureManager::Instance().Add( new TextureOb(TEXTURE::SHIP_ID, "data/ship/k_61_0_3.png", true, &arg) );
//}


//{
	//std::vector<int> arg;   
	//arg.push_back(RACE::R6_ID); arg.push_back(ENTITY::WARRIOR_ID); //COLOR_GOLDENROD
	//TextureManager::Instance().Add( new TextureOb(TEXTURE::SHIP_ID, "data/ship/k_61_0_5.png", true, &arg) );
//}

//{
	//std::vector<int> arg;   
	//arg.push_back(RACE::R6_ID); arg.push_back(ENTITY::WARRIOR_ID); //COLOR_GOLDENROD
	//TextureManager::Instance().Add( new TextureOb(TEXTURE::SHIP_ID, "data/ship/k_61_0_6.png", true, &arg) );
//}

//{
	//std::vector<int> arg;   
	//arg.push_back(RACE::R6_ID); arg.push_back(ENTITY::WARRIOR_ID); //COLOR_GOLDENROD
	//TextureManager::Instance().Add( new TextureOb(TEXTURE::SHIP_ID, "data/ship/k_61_0_7.png", true, &arg) );
//}

//{
	//std::vector<int> arg;   
	//arg.push_back(RACE::R6_ID); arg.push_back(ENTITY::WARRIOR_ID); //COLOR_GOLDENROD
	//TextureManager::Instance().Add( new TextureOb(TEXTURE::SHIP_ID, "data/ship/k_61_0_8.png", true, &arg) );
//}

//{
	//std::vector<int> arg;   
	//arg.push_back(RACE::R6_ID); arg.push_back(ENTITY::WARRIOR_ID); //COLOR_GOLDENROD
	//TextureManager::Instance().Add( new TextureOb(TEXTURE::SHIP_ID, "data/ship/k_61_0_9.png", true, &arg) );
//}

//{
	//std::vector<int> arg;   
	//arg.push_back(RACE::R6_ID); arg.push_back(ENTITY::WARRIOR_ID); //COLOR_GOLDENROD
	//TextureManager::Instance().Add( new TextureOb(TEXTURE::SHIP_ID, "data/ship/k_61_0_10.png", true, &arg) );
//}

//{
	//std::vector<int> arg;   
	//arg.push_back(RACE::R6_ID); arg.push_back(ENTITY::WARRIOR_ID); //COLOR_GOLDENROD
	//TextureManager::Instance().Add( new TextureOb(TEXTURE::SHIP_ID, "data/ship/k_61_0_11.png", true, &arg) );
//}

//{
	//std::vector<int> arg;   
	//arg.push_back(RACE::R6_ID); arg.push_back(ENTITY::WARRIOR_ID); //COLOR_GOLDENROD
	//TextureManager::Instance().Add( new TextureOb(TEXTURE::SHIP_ID, "data/ship/k_61_0_12.png", true, &arg) );
//}



//################################ enemy 2
{
	std::vector<int> arg;   
	arg.push_back(RACE::R7_ID); arg.push_back(ENTITY::WARRIOR_ID); //COLOR_GOLDENROD
	TextureManager::Instance().Add( new TextureOb(TEXTURE::SHIP_ID, "data/ship/k_71_0_0.png", true, &arg) );
}

{
	std::vector<int> arg;   
	arg.push_back(RACE::R7_ID); arg.push_back(ENTITY::WARRIOR_ID); //COLOR_GOLDENROD
	TextureManager::Instance().Add( new TextureOb(TEXTURE::SHIP_ID, "data/ship/k_71_0_1e.png", true, &arg) );
}

//################################# TEXTURE::STAR_ID ###############################
{
	std::vector<int> arg;   
	arg.push_back(COLOR::YELLOW_ID); arg.push_back(1900); 
	TextureManager::Instance().Add( new TextureOb(TEXTURE::STAR_ID, "data/star/s_000.jpg", false, &arg) ); 
}

{
	std::vector<int> arg; 
	arg.push_back(COLOR::YELLOW_ID); arg.push_back(1825); 
	TextureManager::Instance().Add( new TextureOb(TEXTURE::STAR_ID, "data/star/s_001.png", false, &arg) ); 
}

{
	std::vector<int> arg; 
	arg.push_back(COLOR::BLUE_ID); arg.push_back(2525); 
	TextureManager::Instance().Add( new TextureOb(TEXTURE::STAR_ID, "data/star/s_100.jpg", false, &arg) ); 
}

{
	std::vector<int> arg; 
	arg.push_back(COLOR::BLUE_ID); arg.push_back(1925); 
	TextureManager::Instance().Add( new TextureOb(TEXTURE::STAR_ID, "data/star/s_101.png", false, &arg) ); 
}

// STARBASE_TEXTURE_ID
{
	std::vector<int> arg; 
	arg.push_back(RACE::R0_ID);  
	TextureManager::Instance().Add( new TextureOb(TEXTURE::SPACESTATION_ID, "data/starbase/sb_000.png", false, &arg) ); 
}

{
	std::vector<int> arg; 
	arg.push_back(RACE::R0_ID); 
	TextureManager::Instance().Add( new TextureOb(TEXTURE::SPACESTATION_ID, "data/starbase/sb_001.png", false, &arg) ); 
}

{
	std::vector<int> arg; 
	arg.push_back(RACE::R0_ID); 
	TextureManager::Instance().Add( new TextureOb(TEXTURE::SPACESTATION_ID, "data/starbase/sb_002.png", false, &arg) ); 
}

{
	std::vector<int> arg; 
	arg.push_back(RACE::R0_ID); 
	TextureManager::Instance().Add( new TextureOb(TEXTURE::SPACESTATION_ID, "data/starbase/sb_003.png", false, &arg) ); 
}


//################################## NEBULA EFFECT ################################
{
	std::vector<int> arg;   
	arg.push_back(COLOR::RED_ID); arg.push_back(0);
	TextureManager::Instance().Add( new TextureOb(TEXTURE::NEBULA_BACKGROUND_ID, "data/bg_space/nebula.bak/nebula1.png", true, &arg) );                                         
}

{
	std::vector<int> arg;   
	arg.push_back(COLOR::GREEN_ID); arg.push_back(1);
	TextureManager::Instance().Add( new TextureOb(TEXTURE::NEBULA_BACKGROUND_ID, "data/bg_space/nebula.bak/nebula2.png", true, &arg) );   
}

{
	std::vector<int> arg;   
	arg.push_back(COLOR::YELLOW_ID); arg.push_back(0);
	TextureManager::Instance().Add( new TextureOb(TEXTURE::NEBULA_BACKGROUND_ID, "data/bg_space/nebula.bak/nebula3.png", true, &arg) );   
}

{
	std::vector<int> arg;   
	arg.push_back(COLOR::BLUE_ID); arg.push_back(1);
	TextureManager::Instance().Add( new TextureOb(TEXTURE::NEBULA_BACKGROUND_ID, "data/bg_space/nebula.bak/nebula4.png", true, &arg) ); 
}

{
	std::vector<int> arg;   
	arg.push_back(COLOR::YELLOW_ID); arg.push_back(0);
	TextureManager::Instance().Add( new TextureOb(TEXTURE::NEBULA_BACKGROUND_ID, "data/bg_space/nebula.bak/nebula5.png", true, &arg) ); 
}

{
	std::vector<int> arg;  
	arg.push_back(COLOR::RED_ID); arg.push_back(0);
	TextureManager::Instance().Add( new TextureOb(TEXTURE::NEBULA_BACKGROUND_ID, "data/bg_space/nebula.bak/nebula6.png", true, &arg) ); 
}

{
	std::vector<int> arg;   
	arg.push_back(COLOR::BLUE_ID); arg.push_back(0);
	TextureManager::Instance().Add( new TextureOb(TEXTURE::NEBULA_BACKGROUND_ID, "data/bg_space/nebula.bak/nebula7.png", true, &arg) ); 
}

{
	std::vector<int> arg;  
	arg.push_back(COLOR::BLUE_ID); arg.push_back(1);
	TextureManager::Instance().Add( new TextureOb(TEXTURE::NEBULA_BACKGROUND_ID, "data/bg_space/nebula.bak/nebula8.png", true, &arg) ); 
}

{
	std::vector<int> arg;   
	arg.push_back(COLOR::BLUE_ID); arg.push_back(1);
	TextureManager::Instance().Add( new TextureOb(TEXTURE::NEBULA_BACKGROUND_ID, "data/bg_space/nebula.bak/nebula9.png", true, &arg) ); 
}

{
	std::vector<int> arg;  
	arg.push_back(COLOR::RED_ID); arg.push_back(0);
	TextureManager::Instance().Add( new TextureOb(TEXTURE::NEBULA_BACKGROUND_ID, "data/bg_space/nebula.bak/nebula10.png", true, &arg) ); 
}

{
	std::vector<int> arg;   
	arg.push_back(COLOR::YELLOW_ID); arg.push_back(0);
	TextureManager::Instance().Add( new TextureOb(TEXTURE::NEBULA_BACKGROUND_ID, "data/bg_space/nebula.bak/nebula11.png", true, &arg) ); 
}

{
	std::vector<int> arg;   
	arg.push_back(COLOR::BLUE_ID); arg.push_back(0);
	TextureManager::Instance().Add( new TextureOb(TEXTURE::NEBULA_BACKGROUND_ID, "data/bg_space/nebula.bak/nebula12.png", true, &arg) ); 
}

{
	std::vector<int> arg;   
	arg.push_back(COLOR::BLUE_ID); arg.push_back(0);
	TextureManager::Instance().Add( new TextureOb(TEXTURE::NEBULA_BACKGROUND_ID, "data/bg_space/nebula.bak/nebula13.png", true, &arg) ); 
}

{
	std::vector<int> arg;   
	arg.push_back(COLOR::RED_ID); arg.push_back(1);
	TextureManager::Instance().Add( new TextureOb(TEXTURE::NEBULA_BACKGROUND_ID, "data/bg_space/nebula.bak/nebula14.png", true, &arg) ); 
}

{
	std::vector<int> arg;   
	arg.push_back(COLOR::YELLOW_ID); arg.push_back(1);
	TextureManager::Instance().Add( new TextureOb(TEXTURE::NEBULA_BACKGROUND_ID, "data/bg_space/nebula.bak/nebula15.png", true, &arg) ); 
}

{
	std::vector<int> arg;   
	arg.push_back(COLOR::YELLOW_ID); arg.push_back(0);
	TextureManager::Instance().Add( new TextureOb(TEXTURE::NEBULA_BACKGROUND_ID, "data/bg_space/nebula.bak/nebula16.png", true, &arg) ); 
}

{
	std::vector<int> arg;   
	arg.push_back(COLOR::YELLOW_ID); arg.push_back(0);
	TextureManager::Instance().Add( new TextureOb(TEXTURE::NEBULA_BACKGROUND_ID, "data/bg_space/nebula.bak/nebula17.png", true, &arg) ); 
}

{
	std::vector<int> arg; 
	arg.push_back(COLOR::YELLOW_ID); arg.push_back(0);
	TextureManager::Instance().Add( new TextureOb(TEXTURE::NEBULA_BACKGROUND_ID, "data/bg_space/nebula.bak/nebula18.png", true, &arg) ); 
}

{
	std::vector<int> arg;   
	arg.push_back(COLOR::RED_ID); arg.push_back(0); 
	TextureManager::Instance().Add( new TextureOb(TEXTURE::NEBULA_BACKGROUND_ID, "data/bg_space/nebula.bak/nebula19.png", true, &arg) ); 
}
//### size 2 = 512x512
//### size 4 = 1024x1024 or 512x1024

//################################ TEXTURE::LAND_BACKGROUND_ID ###################################
{
	std::vector<int> arg; 
	TextureManager::Instance().Add( new TextureOb(TEXTURE::NATURELAND_BACKGROUND_ID, "data/bg_uninhabited/b_000.jpg", false, &arg) );
}

{
	std::vector<int> arg; 
	TextureManager::Instance().Add( new TextureOb(TEXTURE::NATURELAND_BACKGROUND_ID, "data/bg_uninhabited/b_001.png", false, &arg) );
}

{
	std::vector<int> arg; 
	TextureManager::Instance().Add( new TextureOb(TEXTURE::NATURELAND_BACKGROUND_ID, "data/bg_uninhabited/b_002.png", false, &arg) );
}

//################################ KOSMOPORT_BG_TEXTURE_ID ###############################
{
	std::vector<int> arg; 
	arg.push_back(RACE::R0_ID);
	TextureManager::Instance().Add( new TextureOb(TEXTURE::ANGAR_BACKGROUND_ID, "data/bg_kosmoport/an_000.jpg", false, &arg) );
}

{
	std::vector<int> arg; 
	arg.push_back(RACE::R0_ID);
	TextureManager::Instance().Add( new TextureOb(TEXTURE::STORE_BACKGROUND_ID, "data/bg_kosmoport/st_000.jpg", false, &arg) );
}

{
	std::vector<int> arg; 
	arg.push_back(RACE::R0_ID);
	TextureManager::Instance().Add( new TextureOb(TEXTURE::SHOP_BACKGROUND_ID, "data/bg_kosmoport/sh_000.jpg", false, &arg) );
}

{
	std::vector<int> arg; 
	arg.push_back(RACE::R0_ID);
	TextureManager::Instance().Add( new TextureOb(TEXTURE::GOVERMENT_BACKGROUND_ID, "data/bg_kosmoport/go_000.jpg", false, &arg) );
}


//################################ PLANET_TEXTURE ####################################
{
	std::vector<int> arg; 
	arg.push_back(ENTITY::PLANET_MIXED_ID); arg.push_back(5);
	TextureManager::Instance().Add( new TextureOb(TEXTURE::PLANET_ID, "data/planet/p_0000.png", "data/planet/p_0000_nm.png", false, &arg) );
}

{
	std::vector<int> arg; 
	arg.push_back(ENTITY::PLANET_WATER_ID); arg.push_back(5);
	TextureManager::Instance().Add( new TextureOb(TEXTURE::PLANET_ID, "data/planet/p_1000.png", "data/planet/p_1000_nm.png", false, &arg) );
}

{
	std::vector<int> arg; 
	arg.push_back(ENTITY::PLANET_VULCANIC_ID); arg.push_back(5);
	TextureManager::Instance().Add( new TextureOb(TEXTURE::PLANET_ID, "data/planet/p_2000.png", "data/planet/p_2000_nm.png", false, &arg) );
}

{
	std::vector<int> arg; 
	arg.push_back(ENTITY::PLANET_ICE_ID); arg.push_back(5);
	TextureManager::Instance().Add( new TextureOb(TEXTURE::PLANET_ID, "data/planet/p_3000.png", "data/planet/p_3000_nm.png", false, &arg) );
}

{
	std::vector<int> arg; 
	arg.push_back(ENTITY::PLANET_GAS_ID); arg.push_back(5);
	TextureManager::Instance().Add( new TextureOb(TEXTURE::PLANET_ID, "data/planet/p_4000.png", "data/planet/p_4000_nm.png", false, &arg) );
}

//################################ ATMOSPHERE_TEXTURE ####################################
{
	std::vector<int> arg; 
	TextureManager::Instance().Add( new TextureOb(TEXTURE::ATMOSPHERE_ID, "data/planet/atmosphere_000.png", true, &arg) );
}

{
	std::vector<int> arg; 
	TextureManager::Instance().Add( new TextureOb(TEXTURE::ATMOSPHERE_ID, "data/planet/atmosphere_001.png", true, &arg) );
}


//################################ EFFECTS TEXTURE ###################################
{
	std::vector<int> arg;  
	arg.push_back(COLOR::RED_ID); 
	TextureManager::Instance().Add( new TextureOb(TEXTURE::PARTICLE_EFFECT_ID, "data/effect/particles/particle0.png", true, &arg) ); 
}

{
	std::vector<int> arg;  
	arg.push_back(COLOR::BLUE_ID); 
	TextureManager::Instance().Add( new TextureOb(TEXTURE::PARTICLE_EFFECT_ID, "data/effect/particles/particle1.png", true, &arg) ); 
}

{
	std::vector<int> arg;  
	arg.push_back(COLOR::YELLOW_ID); 
	TextureManager::Instance().Add( new TextureOb(TEXTURE::PARTICLE_EFFECT_ID, "data/effect/particles/particle2.png", true, &arg) ); 
}

{
	std::vector<int> arg;  
	arg.push_back(COLOR::GREY_ID); 
	TextureManager::Instance().Add( new TextureOb(TEXTURE::PARTICLE_EFFECT_ID, "data/effect/particles/particle3.png", true, &arg) ); 
}

//{
	//std::vector<int> arg;  
	//arg.push_back(TECHLEVEL::L0_ID); arg.push_back(COLOR::BLUE_ID); 
	//TextureManager::Instance().Add( new TextureOb(TEXTURE::LAZER_EFFECT_ID, "data/effect/lazer/l_64_26_000.png", true, &arg, 4, 1, 10) );
//}

{
	std::vector<int> arg;  
	arg.push_back(TECHLEVEL::L0_ID); arg.push_back(COLOR::RED_ID); 
	TextureManager::Instance().Add( new TextureOb(TEXTURE::LAZER_EFFECT_ID, "data/effect/lazer/l_001.png", true, &arg) );
}

{
	std::vector<int> arg;  
	arg.push_back(TECHLEVEL::L0_ID); arg.push_back(COLOR::YELLOW_ID); 
	TextureManager::Instance().Add( new TextureOb(TEXTURE::LAZER_EFFECT_ID, "data/effect/lazer/l_002.png", true, &arg) );
}

{
	std::vector<int> arg;  
	arg.push_back(TECHLEVEL::L0_ID); arg.push_back(COLOR::BLUE_ID); 
	TextureManager::Instance().Add( new TextureOb(TEXTURE::LAZER_EFFECT_ID, "data/effect/lazer/l_003.png", true, &arg) );
}

{
	std::vector<int> arg;  
	arg.push_back(COLOR::RED_ID); 
	TextureManager::Instance().Add( new TextureOb(TEXTURE::SHIELD_EFFECT_ID, "data/effect/shield/shield0.png", true, &arg) );
}

{
	std::vector<int> arg;  
	arg.push_back(COLOR::GREEN_ID); 
	TextureManager::Instance().Add( new TextureOb(TEXTURE::SHIELD_EFFECT_ID, "data/effect/shield/shield1.png", true, &arg) );
}

{
	std::vector<int> arg;  
	arg.push_back(COLOR::BLUE_ID); 
	TextureManager::Instance().Add( new TextureOb(TEXTURE::SHIELD_EFFECT_ID, "data/effect/shield/shield2.png", true, &arg) );
}

{
	std::vector<int> arg;  
	arg.push_back(COLOR::YELLOW_ID); 
	TextureManager::Instance().Add( new TextureOb(TEXTURE::SHIELD_EFFECT_ID, "data/effect/shield/shield3.png", true, &arg) );
}


// TEXTURE::DISTANTSTAR_ID
{
	std::vector<int> arg;  
	arg.push_back(COLOR::YELLOW_ID); 
	TextureManager::Instance().Add( new TextureOb(TEXTURE::DISTANTSTAR_ID, "data/star/s1.png", true, &arg) );
}

{
	std::vector<int> arg;  
	arg.push_back(COLOR::BLUE_ID); 
	TextureManager::Instance().Add( new TextureOb(TEXTURE::DISTANTSTAR_ID, "data/star/s2.png", true, &arg) );
}

{
	std::vector<int> arg;  
	arg.push_back(COLOR::RED_ID); 
	TextureManager::Instance().Add( new TextureOb(TEXTURE::DISTANTSTAR_ID, "data/star/s3.png", true, &arg) );
}

//{
	//std::vector<int> arg;  
	//arg.push_back(COLOR::RED_ID); 
	//TextureManager::Instance().Add( new TextureOb(TEXTURE::DISTANTSTAR_ID, "data/star/s4.png", true, &arg) );
//}

//###################################### ITEM TEXTURE ###################################
//############################ DRIVE_ITEM
//#################### RACE_0
//####### TECH_LEVEL_0
{
	std::vector<int> arg;  
	arg.push_back(RACE::R0_ID); arg.push_back(TECHLEVEL::L0_ID);  
	TextureManager::Instance().Add( new TextureOb(TEXTURE::DRIVE_EQUIPMENT_ID, "data/item/drive/drive_Race0_Tech0.png", true, &arg) );
}

//####### TECH_LEVEL_1
{
	std::vector<int> arg;  
	arg.push_back(RACE::R0_ID); arg.push_back(TECHLEVEL::L1_ID);  
	TextureManager::Instance().Add( new TextureOb(TEXTURE::DRIVE_EQUIPMENT_ID, "data/item/drive/drive_Race0_Tech1.png", true, &arg) );
}

//####### TECH_LEVEL_2
{
	std::vector<int> arg;  
	arg.push_back(RACE::R0_ID); arg.push_back(TECHLEVEL::L2_ID); 
	TextureManager::Instance().Add( new TextureOb(TEXTURE::DRIVE_EQUIPMENT_ID, "data/item/drive/drive_Race0_Tech2.png", true, &arg) );
}

//#################### RACE1
//#################### RACE2
//#################### RACE3
//#################### RACE4

//#################### RACE6
//#################### RACE7



//############################ LAZER_ITEM
//#################### RACE_0
//####### TECH_LEVEL_0
{
	std::vector<int> arg;  
	arg.push_back(RACE::R0_ID); arg.push_back(TECHLEVEL::L0_ID); arg.push_back(COLOR::RED_ID); 
	TextureManager::Instance().Add( new TextureOb(TEXTURE::LAZER_EQUIPMENT_ID, "data/item/lazer/lazer_Race0_Tech0_Red0.png", true, &arg) );
}

{
	std::vector<int> arg;  
	arg.push_back(RACE::R0_ID); arg.push_back(TECHLEVEL::L0_ID); arg.push_back(COLOR::YELLOW_ID); 
	TextureManager::Instance().Add( new TextureOb(TEXTURE::LAZER_EQUIPMENT_ID, "data/item/lazer/lazer_Race0_Tech0_Yellow0.png", true, &arg) );
}

{
	std::vector<int> arg;  
	arg.push_back(RACE::R0_ID); arg.push_back(TECHLEVEL::L0_ID); arg.push_back(COLOR::BLUE_ID); 
	TextureManager::Instance().Add( new TextureOb(TEXTURE::LAZER_EQUIPMENT_ID, "data/item/lazer/lazer_Race0_Tech0_Blue0.png", true, &arg) );
}

//####### TECH_LEVEL_1
{
	std::vector<int> arg;  
	arg.push_back(RACE::R0_ID); arg.push_back(TECHLEVEL::L1_ID); arg.push_back(COLOR::BLUE_ID); 
	TextureManager::Instance().Add( new TextureOb(TEXTURE::LAZER_EQUIPMENT_ID, "data/item/lazer/lazer_Race0_Tech1_Blue0.png", true, &arg) );
}
//#################### RACE_1
//#################### RACE_2
//#################### RACE_3
//#################### RACE_4

//#################### RACE_6
//#################### RACE_7



//############################ LAZER_ITEM
//#################### RACE_0
//####### TECH_LEVEL_0
{
	std::vector<int> arg;  
	arg.push_back(RACE::R0_ID); arg.push_back(TECHLEVEL::L0_ID); arg.push_back(COLOR::YELLOW_ID); 
	TextureManager::Instance().Add( new TextureOb(TEXTURE::ROCKET_EQUIPMENT_ID, "data/item/rocket/rocket_Race0_Tech0.png", true, &arg) );
}
//####### TECH_LEVEL_1
{
	std::vector<int> arg;  
	arg.push_back(RACE::R0_ID); arg.push_back(TECHLEVEL::L1_ID); arg.push_back(COLOR::YELLOW_ID); 
	TextureManager::Instance().Add( new TextureOb(TEXTURE::ROCKET_EQUIPMENT_ID, "data/item/rocket/rocket_Race0_Tech1.png", true, &arg) );
}
//####### TECH_LEVEL_2
{
	std::vector<int> arg;  
	arg.push_back(RACE::R0_ID); arg.push_back(TECHLEVEL::L1_ID); arg.push_back(COLOR::YELLOW_ID); 
	TextureManager::Instance().Add( new TextureOb(TEXTURE::ROCKET_EQUIPMENT_ID, "data/item/rocket/rocket_Race0_Tech2.png", true, &arg) );
}

//TEXTURE_MANAGER.manageItem( textureOb(TORPED_ITEM_TEXTURE_ID, 'data/item/torped/tl0.png', True, [ 'torpedo',       TECHLEVEL::L0_ID, 3, 1, RACE::R0_ID, COLOR::YELLOW_ID]) )
//TEXTURE_MANAGER.manageItem( textureOb(TORPED_ITEM_TEXTURE_ID, 'data/item/torped/tl1.png', True, [ 'torpedo',       TECHLEVEL::L0_ID, 3, 1, RACE::R0_ID, COLOR::YELLOW_ID]) )

{
	std::vector<int> arg;  
	TextureManager::Instance().Add( new TextureOb(TEXTURE::ROCKET_BULLET_ID, "data/bullet/r_0.png", true, &arg) );
}

{
	std::vector<int> arg;  
	TextureManager::Instance().Add( new TextureOb(TEXTURE::ROCKET_BULLET_ID, "data/bullet/r_1.png", true, &arg) );
}

//{
	//std::vector<int> arg;  
	//TextureManager::Instance().Add( new TextureOb(TEXTURE::ROCKET_BULLET_ID, "data/bullet/t_0.png", true, &arg) );
//}

//{
	//std::vector<int> arg;  
	//TextureManager::Instance().Add( new TextureOb(TEXTURE::ROCKET_BULLET_ID, "data/bullet/t_1.png", true, &arg) );
//}
//TEXTURE_MANAGER.manage( textureOb(TORPED_BULLET_TEXTURE_ID, 'data/bullet/t_0.png', True, []) )
//TEXTURE_MANAGER.manage( textureOb(TORPED_BULLET_TEXTURE_ID, 'data/bullet/t_1.png', True, []) )



//############################ PROTECTOR_ITEM
//#################### RACE_0
//####### TECH_LEVEL_0
{
	std::vector<int> arg;  
	arg.push_back(RACE::R0_ID); arg.push_back(TECHLEVEL::L0_ID); 
	TextureManager::Instance().Add( new TextureOb(TEXTURE::PROTECTOR_EQUIPMENT_ID, "data/item/protector/protector_Race0_Tech0.png", true, &arg) );
}

//####### TECH_LEVEL_1
{
	std::vector<int> arg;  
	arg.push_back(RACE::R0_ID); arg.push_back(TECHLEVEL::L1_ID); 
	TextureManager::Instance().Add( new TextureOb(TEXTURE::PROTECTOR_EQUIPMENT_ID, "data/item/protector/protector_Race0_Tech1.png", true, &arg) );
}

//####### TECH_LEVEL_2
{
	std::vector<int> arg;  
	arg.push_back(RACE::R0_ID); arg.push_back(TECHLEVEL::L2_ID); 
	TextureManager::Instance().Add( new TextureOb(TEXTURE::PROTECTOR_EQUIPMENT_ID, "data/item/protector/protector_Race0_Tech2.png", true, &arg) );
}
//####### TECH_LEVEL_3
{
	std::vector<int> arg;  
	arg.push_back(RACE::R0_ID); arg.push_back(TECHLEVEL::L3_ID); 
	TextureManager::Instance().Add( new TextureOb(TEXTURE::PROTECTOR_EQUIPMENT_ID, "data/item/protector/protector_Race0_Tech3.png", true, &arg) );
}

//############################ DROID_ITEM
//#################### RACE_0
//####### TECH_LEVEL_0
{
	std::vector<int> arg;  
	arg.push_back(RACE::R0_ID); arg.push_back(TECHLEVEL::L0_ID); 
	TextureManager::Instance().Add( new TextureOb(TEXTURE::DROID_EQUIPMENT_ID, "data/item/droid/droid_Race0_Tech0.png", true, &arg) );
}

//####### TECH_LEVEL_1
{
	std::vector<int> arg;  
	arg.push_back(RACE::R0_ID); arg.push_back(TECHLEVEL::L1_ID); 
	TextureManager::Instance().Add( new TextureOb(TEXTURE::DROID_EQUIPMENT_ID, "data/item/droid/droid_Race0_Tech1.png", true, &arg) );
}

//####### TECH_LEVEL_2
{
	std::vector<int> arg;  
	arg.push_back(RACE::R0_ID); arg.push_back(TECHLEVEL::L2_ID); 
	TextureManager::Instance().Add( new TextureOb(TEXTURE::DROID_EQUIPMENT_ID, "data/item/droid/droid_Race0_Tech2.png", true, &arg) );
}


//############################ GRAPPLE_ITEM
//#################### RACE_0
//####### TECH_LEVEL_0
{
	std::vector<int> arg;  
	arg.push_back(RACE::R0_ID); arg.push_back(TECHLEVEL::L0_ID); 
	TextureManager::Instance().Add( new TextureOb(TEXTURE::GRAPPLE_EQUIPMENT_ID, "data/item/grapple/grapple_Race0_Tech0.png", true, &arg) );
}

//####### TECH_LEVEL_1
{
	std::vector<int> arg;  
	arg.push_back(RACE::R0_ID); arg.push_back(TECHLEVEL::L1_ID); 
	TextureManager::Instance().Add( new TextureOb(TEXTURE::GRAPPLE_EQUIPMENT_ID, "data/item/grapple/grapple_Race0_Tech1.png", true, &arg) );
}



//############################ BAK_ITEM
//#################### RACE_0
//####### TECH_LEVEL_0
{
	std::vector<int> arg;  
	arg.push_back(RACE::R0_ID); arg.push_back(TECHLEVEL::L0_ID); 
	TextureManager::Instance().Add( new TextureOb(TEXTURE::BAK_EQUIPMENT_ID, "data/item/bak/bak_Race0_Tech0.png", true, &arg) );
}

//####### TECH_LEVEL_1
{
	std::vector<int> arg;  
	arg.push_back(RACE::R0_ID); arg.push_back(TECHLEVEL::L1_ID); 
	TextureManager::Instance().Add( new TextureOb(TEXTURE::BAK_EQUIPMENT_ID, "data/item/bak/bak_Race0_Tech1.png", true, &arg) );
}


//############################ ENERGYBLOCK_ITEM
//#################### RACE_0
//####### TECH_LEVEL_0
{
	std::vector<int> arg;  
	arg.push_back(RACE::R0_ID); arg.push_back(TECHLEVEL::L0_ID); 
	TextureManager::Instance().Add( new TextureOb(TEXTURE::ENERGIZER_EQUIPMENT_ID, "data/item/energyBlock/energyBlock_Race0_Tech0.png", true, &arg) );
}

//####### TECH_LEVEL_1
{
	std::vector<int> arg;  
	arg.push_back(RACE::R0_ID); arg.push_back(TECHLEVEL::L1_ID); 
	TextureManager::Instance().Add( new TextureOb(TEXTURE::ENERGIZER_EQUIPMENT_ID, "data/item/energyBlock/energyBlock_Race0_Tech1.png", true, &arg) );
}


//############################ FREEZER_ITEM
//#################### RACE_0
//####### TECH_LEVEL_0
{
	std::vector<int> arg;  
	arg.push_back(RACE::R0_ID); arg.push_back(TECHLEVEL::L0_ID); 
	TextureManager::Instance().Add( new TextureOb(TEXTURE::FREEZER_EQUIPMENT_ID, "data/item/freezer/freezer_Race0_Tech0.png", true, &arg) );
}

//####### TECH_LEVEL_1
{
	std::vector<int> arg;  
	arg.push_back(RACE::R0_ID); arg.push_back(TECHLEVEL::L1_ID); 
	TextureManager::Instance().Add( new TextureOb(TEXTURE::FREEZER_EQUIPMENT_ID, "data/item/freezer/freezer_Race0_Tech1.png", true, &arg) );
}


//############################ FREEZER_ITEM
//#################### RACE_0
//####### TECH_LEVEL_0
{
	std::vector<int> arg;  
	arg.push_back(RACE::R0_ID); arg.push_back(TECHLEVEL::L0_ID); 
	TextureManager::Instance().Add( new TextureOb(TEXTURE::SCANER_EQUIPMENT_ID, "data/item/scaner/scaner_Race0_Tech0.png", true, &arg, 3, 1, 3) );
}
//####### TECH_LEVEL_1
{
	std::vector<int> arg;  
	arg.push_back(RACE::R0_ID); arg.push_back(TECHLEVEL::L1_ID); 
	TextureManager::Instance().Add( new TextureOb(TEXTURE::SCANER_EQUIPMENT_ID, "data/item/scaner/scaner_Race0_Tech1.png", true, &arg, 3, 1, 3) );
}

//############################ FREEZER_ITEM
//#################### RACE_0
//####### TECH_LEVEL_0
{
	std::vector<int> arg;  
	arg.push_back(RACE::R0_ID); arg.push_back(TECHLEVEL::L0_ID); 
	TextureManager::Instance().Add( new TextureOb(TEXTURE::RADAR_EQUIPMENT_ID, "data/item/radar/radar_Race0_Tech0.png", true, &arg, 3, 1, 3) );
}

//####### TECH_LEVEL_1
{
	std::vector<int> arg;  
	arg.push_back(RACE::R0_ID); arg.push_back(TECHLEVEL::L1_ID); 
	TextureManager::Instance().Add( new TextureOb(TEXTURE::RADAR_EQUIPMENT_ID, "data/item/radar/radar_Race0_Tech1.png", true, &arg, 3, 1, 3) );
}


//################## MODULES
{
	std::vector<int> arg;  
	TextureManager::Instance().Add(new TextureOb(TEXTURE::MODULE_ID, "data/item/module.png", true, &arg));
}



{
	std::vector<int> arg;  
	GuiTextureObCollector::Instance().starsystem_mark_war = new TextureOb(NONE_ID, "data/other/ss_mark_war.png", true, &arg);
}

{
	std::vector<int> arg;  
	GuiTextureObCollector::Instance().starsystem_mark_captured = new TextureOb(NONE_ID, "data/other/ss_mark_captured.png", true, &arg);
}

{
	std::vector<int> arg;  
	GuiTextureObCollector::Instance().starsystem_mark_player = new TextureOb(NONE_ID, "data/other/mark_player_ss.png", true, &arg);
}



{
	std::vector<int> arg;  
	GuiTextureObCollector::Instance().icon_minus = new TextureOb(NONE_ID, "data/icon/minus.png", true, &arg);
}

{
	std::vector<int> arg;  
	GuiTextureObCollector::Instance().icon_plus = new TextureOb(NONE_ID, "data/icon/plus.png", true, &arg);
}

{
	std::vector<int> arg;  
	GuiTextureObCollector::Instance().skill = new TextureOb(NONE_ID, "data/other/skill.png", true, &arg);
}

{
	std::vector<int> arg;  
	GuiTextureObCollector::Instance().skill_transparent = new TextureOb(NONE_ID, "data/other/skill_transparent.png", true, &arg);
}

{
	std::vector<int> arg;  
	GuiTextureObCollector::Instance().icon_map = new TextureOb(NONE_ID, "data/icon/starsystem_ICON.png", true, &arg);
}

{
	std::vector<int> arg;  
	GuiTextureObCollector::Instance().grapple_trail = new TextureOb(NONE_ID, "data/effect/grapple_jet.png", true, &arg);
}

{
	std::vector<int> arg;  
	GuiTextureObCollector::Instance().dot_blue = new TextureOb(NONE_ID, "data/other/dot_blue.png", true, &arg);
}

{
	std::vector<int> arg;  
	GuiTextureObCollector::Instance().dot_green = new TextureOb(NONE_ID, "data/other/dot_green.png", true, &arg);
}

{
	std::vector<int> arg;  
	GuiTextureObCollector::Instance().dot_red = new TextureOb(NONE_ID, "data/other/dot_red.png", true, &arg);
}

{
	std::vector<int> arg;  
	GuiTextureObCollector::Instance().dot_black = new TextureOb(NONE_ID, "data/other/dot_black.png", true, &arg);
}

{
	std::vector<int> arg;  
	GuiTextureObCollector::Instance().dot_yellow = new TextureOb(NONE_ID, "data/other/dot_yellow.png", true, &arg);
}

{
	std::vector<int> arg;  
	GuiTextureObCollector::Instance().dot_purple = new TextureOb(NONE_ID, "data/other/dot_purple.png", true, &arg);
}


{
	std::vector<int> arg;  
	GuiTextureObCollector::Instance().radar_screenrect = new TextureOb(NONE_ID, "data/gui/radar_screenrect.png", true, &arg);
}

{
	std::vector<int> arg;  
	GuiTextureObCollector::Instance().radar_range = new TextureOb(NONE_ID, "data/gui/radar_range.png", true, &arg);
}

{
	std::vector<int> arg;  
	GuiTextureObCollector::Instance().radar_background = new TextureOb(NONE_ID, "data/gui/radar_background.png", true, &arg);
}

{
	std::vector<int> arg;  
	GuiTextureObCollector::Instance().radar_bar = new TextureOb(NONE_ID, "data/gui/radar_bar.png", true, &arg);
}

{
	std::vector<int> arg;  
	GuiTextureObCollector::Instance().bar_bottom = new TextureOb(NONE_ID, "data/gui/bar_bottom.png", true, &arg);
}

{
	std::vector<int> arg;  
	GuiTextureObCollector::Instance().bar_left = new TextureOb(NONE_ID, "data/gui/bar_left.png", true, &arg);
}

{
	std::vector<int> arg;  
	GuiTextureObCollector::Instance().bar_top = new TextureOb(NONE_ID, "data/gui/bar_top.png", true, &arg);
}

{
	std::vector<int> arg;  
	GuiTextureObCollector::Instance().bar_top = new TextureOb(NONE_ID, "data/gui/bar_top.png", true, &arg);
}

{
	std::vector<int> arg;  
	GuiTextureObCollector::Instance().text_background =  new TextureOb(NONE_ID, "data/other/text_background.png", true, &arg);
}

{
	std::vector<int> arg;  
	GuiTextureObCollector::Instance().slot_mark_accept =  new TextureOb(NONE_ID, "data/other/slot_mark_accept.png", true, &arg);
}

{
	std::vector<int> arg;  
	GuiTextureObCollector::Instance().slot_mark_reject =  new TextureOb(NONE_ID, "data/other/slot_mark_reject.png", true, &arg);
}

}



void loadShaders()
{
	{
	const std::string path_vert = "data/shaders/black2alpha.vert"; 
	const std::string path_frag = "data/shaders/black2alpha.frag";
	
	ShaderCollector::Instance().black2alpha = glCreateProgram();
	 	
	compileProgram(path_vert, path_frag, ShaderCollector::Instance().black2alpha);
	}
	
	{
	const std::string path_vert = "data/shaders/shockwave.vert"; 
	const std::string path_frag = "data/shaders/shockwave.frag"; 

	ShaderCollector::Instance().shockwave = glCreateProgram();
	
	compileProgram(path_vert, path_frag, ShaderCollector::Instance().shockwave);
	}

	{
	const std::string path_vert = "data/shaders/volumetricLight.vert"; 
	const std::string path_frag = "data/shaders/volumetricLight.frag"; 

	ShaderCollector::Instance().volumetriclight = glCreateProgram();
	
	compileProgram(path_vert, path_frag, ShaderCollector::Instance().volumetriclight);
	}

	{
	const std::string path_vert = "data/shaders/light.vert"; 
	const std::string path_frag = "data/shaders/light.frag"; 

	ShaderCollector::Instance().light = glCreateProgram();
	
	compileProgram(path_vert, path_frag, ShaderCollector::Instance().light);
	}

	{
	const std::string path_vert = "data/shaders/light_normalmap.vert"; 
	const std::string path_frag = "data/shaders/light_normalmap.frag"; 

	ShaderCollector::Instance().light_normalmap = glCreateProgram();
	
	compileProgram(path_vert, path_frag, ShaderCollector::Instance().light_normalmap);
	}
	
	{
	const std::string path_vert = "data/shaders/blur.vert"; 
	const std::string path_frag = "data/shaders/blur.frag"; 
	
	ShaderCollector::Instance().blur = glCreateProgram();

	compileProgram(path_vert, path_frag, ShaderCollector::Instance().blur);
	}

	{
	const std::string path_vert = "data/shaders/extractBright.vert"; 
	const std::string path_frag = "data/shaders/extractBright.frag"; 

	ShaderCollector::Instance().extractbright = glCreateProgram();
	
	compileProgram(path_vert, path_frag, ShaderCollector::Instance().extractbright);
	}

	{
	const std::string path_vert = "data/shaders/combine.vert"; 
	const std::string path_frag = "data/shaders/combine.frag"; 

	ShaderCollector::Instance().combine = glCreateProgram();
	
	compileProgram(path_vert, path_frag, ShaderCollector::Instance().combine);
	}

	{
	const std::string path_vert = "data/shaders/multitex.vert"; 
	const std::string path_frag = "data/shaders/multitex.frag"; 

	ShaderCollector::Instance().multitexturing = glCreateProgram();
	
	compileProgram(path_vert, path_frag, ShaderCollector::Instance().multitexturing);
	}

	{
	const std::string path_vert = "data/shaders/blank.vert"; 
	const std::string path_frag = "data/shaders/blank.frag"; 

	ShaderCollector::Instance().blank = glCreateProgram();
	
	compileProgram(path_vert, path_frag, ShaderCollector::Instance().blank);
	}

	{
	const std::string path_vert = "data/shaders/fogwarspark.vert"; 
	const std::string path_frag = "data/shaders/fogwarspark.frag"; 

	ShaderCollector::Instance().fogwarspark = glCreateProgram();
	
	compileProgram(path_vert, path_frag, ShaderCollector::Instance().fogwarspark);
	}

	{
	const std::string path_vert = "data/shaders/flash.vert"; 
	const std::string path_frag = "data/shaders/flash.frag"; 

	ShaderCollector::Instance().flash = glCreateProgram();
	
	compileProgram(path_vert, path_frag, ShaderCollector::Instance().flash);
	}

}
