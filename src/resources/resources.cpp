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


#include "../common/constants.hpp"

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
		Screen::Instance().InitPostEffects(Screen::Instance().GetWindow().GetWidth(), Screen::Instance().GetWindow().GetHeight());
	}
	
    	Screen::Instance().GetFont().LoadFromFile("data/font/font.ttf");
}



void load3DModels()
{    	
g_SPHERE_MESH = new ObjMeshInstance("data/obj/sphere/planet.obj");

g_DEFORMED_SPHERE_MESH = new ObjMeshInstance("data/obj/sphere_deformed/planet.obj");
//g_DEFORMED_SPHERE_MESH = new ObjMeshInstance("data/obj/ship/Shipyard_Scene.obj");
//g_MODEL.import("data/obj/ship/Space.obj");
//g_MODEL.normalize();
}



void loadImages()
{
//####################################### TURREL_TEXTURE ###################################
{
	std::vector<int> arg;   
	arg.push_back(RACE::R0_ID);
	g_TEXTURE_MANAGER.Add( new TextureOb(TEXTURE::TURREL_ID, "data/turrel/lazer.png", true, &arg) );
}

//{
	//std::vector<int> arg;   
	//arg.push_back(RACE::R0_ID);
	//g_TEXTURE_MANAGER.Add( new TextureOb(TEXTURE::TURREL_ID, "data/turrel/esphere-0.png", true, &arg) );
//}


//####################################### SLOT_TEXTURE ###################################
{
	std::vector<int> arg;   
	arg.push_back(RACE::R0_ID);
	g_TEXTURE_MANAGER.Add( new TextureOb(TEXTURE::ITEMSLOT_ID, "data/other/slot.png", true, &arg) );
}

{
	std::vector<int> arg;   
	arg.push_back(RACE::R0_ID);
	g_TEXTURE_MANAGER.Add( new TextureOb(TEXTURE::VEHICLESLOT_ID, "data/other/H.png", true, &arg, 3, 2, 3) );
}

//####################################### TEXTURE::FACE_ID ################################
//RACE::R0_ID
{
	std::vector<int> arg; 
	arg.push_back(RACE::R0_ID);
	g_TEXTURE_MANAGER.Add( new TextureOb(TEXTURE::FACE_ID, "data/race/0000.png", false, &arg) );
}

{
	std::vector<int> arg; 
	arg.push_back(RACE::R0_ID);
	g_TEXTURE_MANAGER.Add( new TextureOb(TEXTURE::FACE_ID, "data/race/0001.png", false, &arg) );
}

//RACE::R1_ID
{
	std::vector<int> arg; 
	arg.push_back(RACE::R1_ID);
	g_TEXTURE_MANAGER.Add( new TextureOb(TEXTURE::FACE_ID, "data/race/1000.png", false, &arg) );
}

{
	std::vector<int> arg; 
	arg.push_back(RACE::R1_ID);
	g_TEXTURE_MANAGER.Add( new TextureOb(TEXTURE::FACE_ID, "data/race/1001.png", false, &arg) );
}

//RACE::R2_ID
{
	std::vector<int> arg; 
	arg.push_back(RACE::R2_ID);
	g_TEXTURE_MANAGER.Add( new TextureOb(TEXTURE::FACE_ID, "data/race/2000.png", false, &arg) );
}

{
	std::vector<int> arg; 
	arg.push_back(RACE::R2_ID);
	g_TEXTURE_MANAGER.Add( new TextureOb(TEXTURE::FACE_ID, "data/race/2001.png", false, &arg) );
}

//RACE::R3_ID
{
	std::vector<int> arg; 
	arg.push_back(RACE::R3_ID);
	g_TEXTURE_MANAGER.Add( new TextureOb(TEXTURE::FACE_ID, "data/race/3000.png", false, &arg) );
}

{
	std::vector<int> arg; 
	arg.push_back(RACE::R3_ID);
	g_TEXTURE_MANAGER.Add( new TextureOb(TEXTURE::FACE_ID, "data/race/3001.png", false, &arg) );
}

//RACE::R4_ID
{
	std::vector<int> arg; 
	arg.push_back(RACE::R4_ID);
	g_TEXTURE_MANAGER.Add( new TextureOb(TEXTURE::FACE_ID, "data/race/4000.png", false, &arg) );
}

{
	std::vector<int> arg; 
	arg.push_back(RACE::R4_ID);
	g_TEXTURE_MANAGER.Add( new TextureOb(TEXTURE::FACE_ID, "data/race/4001.png", false, &arg) );
}

//RACE::R6_ID
{
	std::vector<int> arg; 
	arg.push_back(RACE::R6_ID);
	g_TEXTURE_MANAGER.Add( new TextureOb(TEXTURE::FACE_ID, "data/race/6000.png", false, &arg) );
}

{
	std::vector<int> arg; 
	arg.push_back(RACE::R6_ID);
	g_TEXTURE_MANAGER.Add( new TextureOb(TEXTURE::FACE_ID, "data/race/6001.png", false, &arg) );
}

//RACE::R7_ID
{
	std::vector<int> arg; 
	arg.push_back(RACE::R7_ID);
	g_TEXTURE_MANAGER.Add( new TextureOb(TEXTURE::FACE_ID, "data/race/7000.png", false, &arg) );
}

{
	std::vector<int> arg; 
	arg.push_back(RACE::R7_ID);
	g_TEXTURE_MANAGER.Add( new TextureOb(TEXTURE::FACE_ID, "data/race/7001.png", false, &arg) );
}



//####################################### ASTEROID_TEXTURE ################################
{
	std::vector<int> arg; 
	g_TEXTURE_MANAGER.Add( new TextureOb(TEXTURE::ASTEROID_ID, "data/asteroid/a_000.png", true, &arg) );
}

{
	std::vector<int> arg; 
	g_TEXTURE_MANAGER.Add( new TextureOb(TEXTURE::ASTEROID_ID, "data/asteroid/a_001.png", true, &arg) );
}

{
	std::vector<int> arg; 
	g_TEXTURE_MANAGER.Add( new TextureOb(TEXTURE::ASTEROID_ID, "data/asteroid/a_002.png", true, &arg) );
}

//####################################### MINERAL_TEXTURE ################################
{
	std::vector<int> arg; 
	g_TEXTURE_MANAGER.Add( new TextureOb(TEXTURE::MINERAL_ID, "data/asteroid/m_000.png", true, &arg) );
}

{
	std::vector<int> arg; 
	g_TEXTURE_MANAGER.Add( new TextureOb(TEXTURE::MINERAL_ID, "data/asteroid/m_001.png", true, &arg) );
}

{
	std::vector<int> arg; 
	g_TEXTURE_MANAGER.Add( new TextureOb(TEXTURE::MINERAL_ID, "data/asteroid/m_002.png", true, &arg) );
}

{
	std::vector<int> arg; 
	g_TEXTURE_MANAGER.Add( new TextureOb(TEXTURE::CONTAINER_ID, "data/item/container.png", true, &arg) );
}

{
	std::vector<int> arg; 
	g_TEXTURE_MANAGER.Add( new TextureOb(TEXTURE::BOMB_ID, "data/item/bomb_item.png", true, &arg) );
}



//####################################### TEXTURE::SATELLITE_ID ################################
{
	std::vector<int> arg;   
	arg.push_back(RACE::R0_ID);
	g_TEXTURE_MANAGER.Add( new TextureOb(TEXTURE::SATELLITE_ID, "data/satellite/sa_001.png", true, &arg, 3, 1, 6) );
}

{
	std::vector<int> arg;   
	arg.push_back(RACE::R0_ID);
	g_TEXTURE_MANAGER.Add( new TextureOb(TEXTURE::SATELLITE_ID, "data/satellite/sa_002.png", true, &arg, 4, 1, 8) );
}

{
	std::vector<int> arg;   
	arg.push_back(RACE::R0_ID);
	g_TEXTURE_MANAGER.Add( new TextureOb(TEXTURE::SATELLITE_ID, "data/satellite/sa_003.png", true, &arg, 3, 1, 6) );
}

{
	std::vector<int> arg;   
	arg.push_back(RACE::R0_ID);
	g_TEXTURE_MANAGER.Add( new TextureOb(TEXTURE::SATELLITE_ID, "data/satellite/sa_004.png", true, &arg) );
}

{
	std::vector<int> arg;   
	arg.push_back(RACE::R0_ID);
	g_TEXTURE_MANAGER.Add( new TextureOb(TEXTURE::SATELLITE_ID, "data/satellite/sa_005.png", true, &arg, 8, 1, 16) );
}

{
	std::vector<int> arg;   
	arg.push_back(RACE::R0_ID);
	g_TEXTURE_MANAGER.Add( new TextureOb(TEXTURE::SATELLITE_ID, "data/satellite/sa_006.png", true, &arg, 8, 1, 16) );
}


// BLACKHOLE

{
	std::vector<int> arg;   
	g_TEXTURE_MANAGER.Add( new TextureOb(TEXTURE::BLACKHOLE_ID, "data/blackhole/bh_00.png", true, &arg) );
}

//####################################### SHIP_TEXTURE ####################################
//################################ race texnologi
{
	std::vector<int> arg;   
	arg.push_back(RACE::R0_ID); arg.push_back(CLASS::RANGER_ID);   //COLOR_VIOLET
	g_TEXTURE_MANAGER.Add( new TextureOb(TEXTURE::SHIP_ID, "data/ship/k_00_0_0.png", true, &arg) );
}

{
	std::vector<int> arg;   
	arg.push_back(RACE::R0_ID); arg.push_back(CLASS::WARRIOR_ID);  //COLOR_VIOLET
	g_TEXTURE_MANAGER.Add( new TextureOb(TEXTURE::SHIP_ID, "data/ship/k_01_0_0.png", true, &arg) );
}

{
	std::vector<int> arg;   
	arg.push_back(RACE::R0_ID); arg.push_back(CLASS::WARRIOR_ID);  //COLOR_VIOLET
	g_TEXTURE_MANAGER.Add( new TextureOb(TEXTURE::SHIP_ID, "data/ship/k_01_0_1.png", true, &arg) );
}

{
	std::vector<int> arg;   
	arg.push_back(RACE::R0_ID); arg.push_back(CLASS::PIRAT_ID);    //COLOR_VIOLET
	g_TEXTURE_MANAGER.Add( new TextureOb(TEXTURE::SHIP_ID, "data/ship/k_02_0_0.png", true, &arg) );
}

{
	std::vector<int> arg;   
	arg.push_back(RACE::R0_ID); arg.push_back(CLASS::TRADER_ID);   //COLOR_VIOLET
	g_TEXTURE_MANAGER.Add( new TextureOb(TEXTURE::SHIP_ID, "data/ship/k_03_0_0.png", true, &arg) );
}

{
	std::vector<int> arg;   
	arg.push_back(RACE::R0_ID); arg.push_back(CLASS::DIPLOMAT_ID); //COLOR_VIOLET
	g_TEXTURE_MANAGER.Add( new TextureOb(TEXTURE::SHIP_ID, "data/ship/k_04_0_0.png", true, &arg) );
}

//################################ race voennye
{
	std::vector<int> arg;   
	arg.push_back(RACE::R1_ID); arg.push_back(CLASS::RANGER_ID);   //COLOR_GREY
	g_TEXTURE_MANAGER.Add( new TextureOb(TEXTURE::SHIP_ID, "data/ship/k_10_0_0.png", true, &arg) );
}

{
	std::vector<int> arg;   
	arg.push_back(RACE::R1_ID); arg.push_back(CLASS::WARRIOR_ID);  //COLOR_GREY
	g_TEXTURE_MANAGER.Add( new TextureOb(TEXTURE::SHIP_ID, "data/ship/k_11_0_0.png", true, &arg) );
}

{
	std::vector<int> arg;   
	arg.push_back(RACE::R1_ID); arg.push_back(CLASS::PIRAT_ID);    //COLOR_GREY
	g_TEXTURE_MANAGER.Add( new TextureOb(TEXTURE::SHIP_ID, "data/ship/k_12_0_0.png", true, &arg) );
}

{
	std::vector<int> arg;   
	arg.push_back(RACE::R1_ID); arg.push_back(CLASS::TRADER_ID);   //COLOR_GREY
	g_TEXTURE_MANAGER.Add( new TextureOb(TEXTURE::SHIP_ID, "data/ship/k_12_0_0.png", true, &arg) );
}

{
	std::vector<int> arg;   
	arg.push_back(RACE::R1_ID); arg.push_back(CLASS::DIPLOMAT_ID);  //COLOR_GREY
	g_TEXTURE_MANAGER.Add( new TextureOb(TEXTURE::SHIP_ID, "data/ship/k_14_0_0.png", true, &arg) );
}

//################################ race zhuliki
{
	std::vector<int> arg;   
	arg.push_back(RACE::R2_ID); arg.push_back(CLASS::RANGER_ID);    
	g_TEXTURE_MANAGER.Add( new TextureOb(TEXTURE::SHIP_ID, "data/ship/race2_ranger_00.png", true, &arg) );
}

{
	std::vector<int> arg;   
	arg.push_back(RACE::R2_ID); arg.push_back(CLASS::WARRIOR_ID);  //COLOR_GREEN
	g_TEXTURE_MANAGER.Add( new TextureOb(TEXTURE::SHIP_ID, "data/ship/race2_warrior_00.png", true, &arg) );
}

{
	std::vector<int> arg;   
	arg.push_back(RACE::R2_ID); arg.push_back(CLASS::TRADER_ID);    //COLOR_RED
	g_TEXTURE_MANAGER.Add( new TextureOb(TEXTURE::SHIP_ID, "data/ship/race2_trader_00.png", true, &arg) );
}

{
	std::vector<int> arg;   
	arg.push_back(RACE::R2_ID); arg.push_back(CLASS::PIRAT_ID);    //COLOR_RED
	g_TEXTURE_MANAGER.Add( new TextureOb(TEXTURE::SHIP_ID, "data/ship/race2_pirat_00.png", true, &arg) );
}

{
	std::vector<int> arg;   
	arg.push_back(RACE::R2_ID); arg.push_back(CLASS::DIPLOMAT_ID);   //COLOR_GREEN
	g_TEXTURE_MANAGER.Add( new TextureOb(TEXTURE::SHIP_ID, "data/ship/race2_diplomat_00.png", true, &arg) );
}

//################################ race cheloveki
{
	std::vector<int> arg;   
	arg.push_back(RACE::R3_ID); arg.push_back(CLASS::RANGER_ID); //COLOR_BLUE
	g_TEXTURE_MANAGER.Add( new TextureOb(TEXTURE::SHIP_ID, "data/ship/k_30_0_0.png", true, &arg) );
}

{
	std::vector<int> arg;   
	arg.push_back(RACE::R3_ID); arg.push_back(CLASS::WARRIOR_ID); //COLOR_BLUE
	g_TEXTURE_MANAGER.Add( new TextureOb(TEXTURE::SHIP_ID, "data/ship/k_31_0_0.png", true, &arg) );
}

{
	std::vector<int> arg;   
	arg.push_back(RACE::R3_ID); arg.push_back(CLASS::WARRIOR_ID); //COLOR_BLUE
	g_TEXTURE_MANAGER.Add( new TextureOb(TEXTURE::SHIP_ID, "data/ship/k_31_0_1.png", true, &arg) );
}

{
	std::vector<int> arg;   
	arg.push_back(RACE::R3_ID); arg.push_back(CLASS::PIRAT_ID);   //COLOR_BLUE
	g_TEXTURE_MANAGER.Add( new TextureOb(TEXTURE::SHIP_ID, "data/ship/k_32_0_0.png", true, &arg) );
}

{
	std::vector<int> arg;   
	arg.push_back(RACE::R3_ID); arg.push_back(CLASS::TRADER_ID);  //COLOR_BLUE
	g_TEXTURE_MANAGER.Add( new TextureOb(TEXTURE::SHIP_ID, "data/ship/_k_33_0_0.png", true, &arg) );
}

{
	std::vector<int> arg;   
	arg.push_back(RACE::R3_ID); arg.push_back(CLASS::DIPLOMAT_ID); //COLOR_BLUE
	g_TEXTURE_MANAGER.Add( new TextureOb(TEXTURE::SHIP_ID, "data/ship/_k_34_0_0.png", true, &arg) );
}

//################################ race bio
{
	std::vector<int> arg;   
	arg.push_back(RACE::R4_ID); arg.push_back(CLASS::WARRIOR_ID); //COLOR_GOLDENROD
	g_TEXTURE_MANAGER.Add( new TextureOb(TEXTURE::SHIP_ID, "data/ship/k_41_0_0.png", true, &arg) );
}

{
	std::vector<int> arg;   
	arg.push_back(RACE::R4_ID); arg.push_back(CLASS::TRADER_ID);  //COLOR_GOLDENROD
	g_TEXTURE_MANAGER.Add( new TextureOb(TEXTURE::SHIP_ID, "data/ship/k_43_0_0.png", true, &arg) );
}

{
	std::vector<int> arg;   
	arg.push_back(RACE::R4_ID); arg.push_back(CLASS::TRADER_ID);  //COLOR_GOLDENROD
	g_TEXTURE_MANAGER.Add( new TextureOb(TEXTURE::SHIP_ID, "data/ship/k_43_0_1.png", true, &arg) );
}

{
	std::vector<int> arg;   
	arg.push_back(RACE::R4_ID); arg.push_back(CLASS::DIPLOMAT_ID); //COLOR_GOLDENROD
	g_TEXTURE_MANAGER.Add( new TextureOb(TEXTURE::SHIP_ID, "data/ship/k_44_0_0.png", true, &arg) );
}

//################################ enemy 1
{
	std::vector<int> arg;   
	arg.push_back(RACE::R6_ID); arg.push_back(CLASS::WARRIOR_ID); //COLOR_GOLDENROD
	g_TEXTURE_MANAGER.Add( new TextureOb(TEXTURE::SHIP_ID, "data/ship/k_61_0_0.png", true, &arg) );
}

{
	std::vector<int> arg;   
	arg.push_back(RACE::R6_ID); arg.push_back(CLASS::WARRIOR_ID); //COLOR_GOLDENROD
	g_TEXTURE_MANAGER.Add( new TextureOb(TEXTURE::SHIP_ID, "data/ship/k_61_0_1.png", true, &arg) );
}

{
	std::vector<int> arg;   
	arg.push_back(RACE::R6_ID); arg.push_back(CLASS::WARRIOR_ID); //COLOR_GOLDENROD
	g_TEXTURE_MANAGER.Add( new TextureOb(TEXTURE::SHIP_ID, "data/ship/k_61_0_2.png", true, &arg) );
}


//{
	//std::vector<int> arg;   
	//arg.push_back(RACE::R6_ID); arg.push_back(CLASS::WARRIOR_ID); //COLOR_GOLDENROD
	//g_TEXTURE_MANAGER.Add( new TextureOb(TEXTURE::SHIP_ID, "data/ship/k_61_0_3.png", true, &arg) );
//}


//{
	//std::vector<int> arg;   
	//arg.push_back(RACE::R6_ID); arg.push_back(CLASS::WARRIOR_ID); //COLOR_GOLDENROD
	//g_TEXTURE_MANAGER.Add( new TextureOb(TEXTURE::SHIP_ID, "data/ship/k_61_0_5.png", true, &arg) );
//}

//{
	//std::vector<int> arg;   
	//arg.push_back(RACE::R6_ID); arg.push_back(CLASS::WARRIOR_ID); //COLOR_GOLDENROD
	//g_TEXTURE_MANAGER.Add( new TextureOb(TEXTURE::SHIP_ID, "data/ship/k_61_0_6.png", true, &arg) );
//}

//{
	//std::vector<int> arg;   
	//arg.push_back(RACE::R6_ID); arg.push_back(CLASS::WARRIOR_ID); //COLOR_GOLDENROD
	//g_TEXTURE_MANAGER.Add( new TextureOb(TEXTURE::SHIP_ID, "data/ship/k_61_0_7.png", true, &arg) );
//}

//{
	//std::vector<int> arg;   
	//arg.push_back(RACE::R6_ID); arg.push_back(CLASS::WARRIOR_ID); //COLOR_GOLDENROD
	//g_TEXTURE_MANAGER.Add( new TextureOb(TEXTURE::SHIP_ID, "data/ship/k_61_0_8.png", true, &arg) );
//}

//{
	//std::vector<int> arg;   
	//arg.push_back(RACE::R6_ID); arg.push_back(CLASS::WARRIOR_ID); //COLOR_GOLDENROD
	//g_TEXTURE_MANAGER.Add( new TextureOb(TEXTURE::SHIP_ID, "data/ship/k_61_0_9.png", true, &arg) );
//}

//{
	//std::vector<int> arg;   
	//arg.push_back(RACE::R6_ID); arg.push_back(CLASS::WARRIOR_ID); //COLOR_GOLDENROD
	//g_TEXTURE_MANAGER.Add( new TextureOb(TEXTURE::SHIP_ID, "data/ship/k_61_0_10.png", true, &arg) );
//}

//{
	//std::vector<int> arg;   
	//arg.push_back(RACE::R6_ID); arg.push_back(CLASS::WARRIOR_ID); //COLOR_GOLDENROD
	//g_TEXTURE_MANAGER.Add( new TextureOb(TEXTURE::SHIP_ID, "data/ship/k_61_0_11.png", true, &arg) );
//}

//{
	//std::vector<int> arg;   
	//arg.push_back(RACE::R6_ID); arg.push_back(CLASS::WARRIOR_ID); //COLOR_GOLDENROD
	//g_TEXTURE_MANAGER.Add( new TextureOb(TEXTURE::SHIP_ID, "data/ship/k_61_0_12.png", true, &arg) );
//}



//################################ enemy 2
{
	std::vector<int> arg;   
	arg.push_back(RACE::R7_ID); arg.push_back(CLASS::WARRIOR_ID); //COLOR_GOLDENROD
	g_TEXTURE_MANAGER.Add( new TextureOb(TEXTURE::SHIP_ID, "data/ship/k_71_0_0.png", true, &arg) );
}

{
	std::vector<int> arg;   
	arg.push_back(RACE::R7_ID); arg.push_back(CLASS::WARRIOR_ID); //COLOR_GOLDENROD
	g_TEXTURE_MANAGER.Add( new TextureOb(TEXTURE::SHIP_ID, "data/ship/k_71_0_1e.png", true, &arg) );
}

//################################# TEXTURE::STAR_ID ###############################
{
	std::vector<int> arg;   
	arg.push_back(COLOR::YELLOW_ID); arg.push_back(1900); 
	g_TEXTURE_MANAGER.Add( new TextureOb(TEXTURE::STAR_ID, "data/star/s_000.jpg", false, &arg) ); 
}

{
	std::vector<int> arg; 
	arg.push_back(COLOR::YELLOW_ID); arg.push_back(1825); 
	g_TEXTURE_MANAGER.Add( new TextureOb(TEXTURE::STAR_ID, "data/star/s_001.png", false, &arg) ); 
}

{
	std::vector<int> arg; 
	arg.push_back(COLOR::BLUE_ID); arg.push_back(2525); 
	g_TEXTURE_MANAGER.Add( new TextureOb(TEXTURE::STAR_ID, "data/star/s_100.jpg", false, &arg) ); 
}

{
	std::vector<int> arg; 
	arg.push_back(COLOR::BLUE_ID); arg.push_back(1925); 
	g_TEXTURE_MANAGER.Add( new TextureOb(TEXTURE::STAR_ID, "data/star/s_101.png", false, &arg) ); 
}

// STARBASE_TEXTURE_ID
{
	std::vector<int> arg; 
	arg.push_back(RACE::R0_ID);  
	g_TEXTURE_MANAGER.Add( new TextureOb(TEXTURE::SPACESTATION_ID, "data/starbase/sb_000.png", false, &arg) ); 
}

{
	std::vector<int> arg; 
	arg.push_back(RACE::R0_ID); 
	g_TEXTURE_MANAGER.Add( new TextureOb(TEXTURE::SPACESTATION_ID, "data/starbase/sb_001.png", false, &arg) ); 
}

{
	std::vector<int> arg; 
	arg.push_back(RACE::R0_ID); 
	g_TEXTURE_MANAGER.Add( new TextureOb(TEXTURE::SPACESTATION_ID, "data/starbase/sb_002.png", false, &arg) ); 
}

{
	std::vector<int> arg; 
	arg.push_back(RACE::R0_ID); 
	g_TEXTURE_MANAGER.Add( new TextureOb(TEXTURE::SPACESTATION_ID, "data/starbase/sb_003.png", false, &arg) ); 
}


//################################## NEBULA EFFECT ################################
{
	std::vector<int> arg;   
	arg.push_back(COLOR::RED_ID); arg.push_back(0);
	g_TEXTURE_MANAGER.Add( new TextureOb(TEXTURE::NEBULA_BACKGROUND_ID, "data/bg_space/nebula.bak/nebula1.png", true, &arg) );                                         
}

{
	std::vector<int> arg;   
	arg.push_back(COLOR::GREEN_ID); arg.push_back(1);
	g_TEXTURE_MANAGER.Add( new TextureOb(TEXTURE::NEBULA_BACKGROUND_ID, "data/bg_space/nebula.bak/nebula2.png", true, &arg) );   
}

{
	std::vector<int> arg;   
	arg.push_back(COLOR::YELLOW_ID); arg.push_back(0);
	g_TEXTURE_MANAGER.Add( new TextureOb(TEXTURE::NEBULA_BACKGROUND_ID, "data/bg_space/nebula.bak/nebula3.png", true, &arg) );   
}

{
	std::vector<int> arg;   
	arg.push_back(COLOR::BLUE_ID); arg.push_back(1);
	g_TEXTURE_MANAGER.Add( new TextureOb(TEXTURE::NEBULA_BACKGROUND_ID, "data/bg_space/nebula.bak/nebula4.png", true, &arg) ); 
}

{
	std::vector<int> arg;   
	arg.push_back(COLOR::YELLOW_ID); arg.push_back(0);
	g_TEXTURE_MANAGER.Add( new TextureOb(TEXTURE::NEBULA_BACKGROUND_ID, "data/bg_space/nebula.bak/nebula5.png", true, &arg) ); 
}

{
	std::vector<int> arg;  
	arg.push_back(COLOR::RED_ID); arg.push_back(0);
	g_TEXTURE_MANAGER.Add( new TextureOb(TEXTURE::NEBULA_BACKGROUND_ID, "data/bg_space/nebula.bak/nebula6.png", true, &arg) ); 
}

{
	std::vector<int> arg;   
	arg.push_back(COLOR::BLUE_ID); arg.push_back(0);
	g_TEXTURE_MANAGER.Add( new TextureOb(TEXTURE::NEBULA_BACKGROUND_ID, "data/bg_space/nebula.bak/nebula7.png", true, &arg) ); 
}

{
	std::vector<int> arg;  
	arg.push_back(COLOR::BLUE_ID); arg.push_back(1);
	g_TEXTURE_MANAGER.Add( new TextureOb(TEXTURE::NEBULA_BACKGROUND_ID, "data/bg_space/nebula.bak/nebula8.png", true, &arg) ); 
}

{
	std::vector<int> arg;   
	arg.push_back(COLOR::BLUE_ID); arg.push_back(1);
	g_TEXTURE_MANAGER.Add( new TextureOb(TEXTURE::NEBULA_BACKGROUND_ID, "data/bg_space/nebula.bak/nebula9.png", true, &arg) ); 
}

{
	std::vector<int> arg;  
	arg.push_back(COLOR::RED_ID); arg.push_back(0);
	g_TEXTURE_MANAGER.Add( new TextureOb(TEXTURE::NEBULA_BACKGROUND_ID, "data/bg_space/nebula.bak/nebula10.png", true, &arg) ); 
}

{
	std::vector<int> arg;   
	arg.push_back(COLOR::YELLOW_ID); arg.push_back(0);
	g_TEXTURE_MANAGER.Add( new TextureOb(TEXTURE::NEBULA_BACKGROUND_ID, "data/bg_space/nebula.bak/nebula11.png", true, &arg) ); 
}

{
	std::vector<int> arg;   
	arg.push_back(COLOR::BLUE_ID); arg.push_back(0);
	g_TEXTURE_MANAGER.Add( new TextureOb(TEXTURE::NEBULA_BACKGROUND_ID, "data/bg_space/nebula.bak/nebula12.png", true, &arg) ); 
}

{
	std::vector<int> arg;   
	arg.push_back(COLOR::BLUE_ID); arg.push_back(0);
	g_TEXTURE_MANAGER.Add( new TextureOb(TEXTURE::NEBULA_BACKGROUND_ID, "data/bg_space/nebula.bak/nebula13.png", true, &arg) ); 
}

{
	std::vector<int> arg;   
	arg.push_back(COLOR::RED_ID); arg.push_back(1);
	g_TEXTURE_MANAGER.Add( new TextureOb(TEXTURE::NEBULA_BACKGROUND_ID, "data/bg_space/nebula.bak/nebula14.png", true, &arg) ); 
}

{
	std::vector<int> arg;   
	arg.push_back(COLOR::YELLOW_ID); arg.push_back(1);
	g_TEXTURE_MANAGER.Add( new TextureOb(TEXTURE::NEBULA_BACKGROUND_ID, "data/bg_space/nebula.bak/nebula15.png", true, &arg) ); 
}

{
	std::vector<int> arg;   
	arg.push_back(COLOR::YELLOW_ID); arg.push_back(0);
	g_TEXTURE_MANAGER.Add( new TextureOb(TEXTURE::NEBULA_BACKGROUND_ID, "data/bg_space/nebula.bak/nebula16.png", true, &arg) ); 
}

{
	std::vector<int> arg;   
	arg.push_back(COLOR::YELLOW_ID); arg.push_back(0);
	g_TEXTURE_MANAGER.Add( new TextureOb(TEXTURE::NEBULA_BACKGROUND_ID, "data/bg_space/nebula.bak/nebula17.png", true, &arg) ); 
}

{
	std::vector<int> arg; 
	arg.push_back(COLOR::YELLOW_ID); arg.push_back(0);
	g_TEXTURE_MANAGER.Add( new TextureOb(TEXTURE::NEBULA_BACKGROUND_ID, "data/bg_space/nebula.bak/nebula18.png", true, &arg) ); 
}

{
	std::vector<int> arg;   
	arg.push_back(COLOR::RED_ID); arg.push_back(0); 
	g_TEXTURE_MANAGER.Add( new TextureOb(TEXTURE::NEBULA_BACKGROUND_ID, "data/bg_space/nebula.bak/nebula19.png", true, &arg) ); 
}
//### size 2 = 512x512
//### size 4 = 1024x1024 or 512x1024

//################################ TEXTURE::LAND_BACKGROUND_ID ###################################
{
	std::vector<int> arg; 
	g_TEXTURE_MANAGER.Add( new TextureOb(TEXTURE::LAND_BACKGROUND_ID, "data/bg_uninhabited/b_000.jpg", false, &arg) );
}

{
	std::vector<int> arg; 
	g_TEXTURE_MANAGER.Add( new TextureOb(TEXTURE::LAND_BACKGROUND_ID, "data/bg_uninhabited/b_001.png", false, &arg) );
}

{
	std::vector<int> arg; 
	g_TEXTURE_MANAGER.Add( new TextureOb(TEXTURE::LAND_BACKGROUND_ID, "data/bg_uninhabited/b_002.png", false, &arg) );
}

//################################ KOSMOPORT_BG_TEXTURE_ID ###############################
{
	std::vector<int> arg; 
	arg.push_back(RACE::R0_ID);
	g_TEXTURE_MANAGER.Add( new TextureOb(TEXTURE::ANGAR_BACKGROUND_ID, "data/bg_kosmoport/an_000.jpg", false, &arg) );
}

{
	std::vector<int> arg; 
	arg.push_back(RACE::R0_ID);
	g_TEXTURE_MANAGER.Add( new TextureOb(TEXTURE::STORE_BACKGROUND_ID, "data/bg_kosmoport/st_000.jpg", false, &arg) );
}

{
	std::vector<int> arg; 
	arg.push_back(RACE::R0_ID);
	g_TEXTURE_MANAGER.Add( new TextureOb(TEXTURE::SHOP_BACKGROUND_ID, "data/bg_kosmoport/sh_000.jpg", false, &arg) );
}

{
	std::vector<int> arg; 
	arg.push_back(RACE::R0_ID);
	g_TEXTURE_MANAGER.Add( new TextureOb(TEXTURE::GOVERMENT_BACKGROUND_ID, "data/bg_kosmoport/go_000.jpg", false, &arg) );
}


//################################ PLANET_TEXTURE ####################################
{
	std::vector<int> arg; 
	arg.push_back(ENTITY::PLANET::SURFACE::EARTH_ID); arg.push_back(5);
	g_TEXTURE_MANAGER.Add( new TextureOb(TEXTURE::PLANET_ID, "data/planet/p_0000.png", false, &arg) );
}

{
	std::vector<int> arg; 
	arg.push_back(ENTITY::PLANET::SURFACE::WATER_ID); arg.push_back(5);
	g_TEXTURE_MANAGER.Add( new TextureOb(TEXTURE::PLANET_ID, "data/planet/p_1000.png", false, &arg) );
}

{
	std::vector<int> arg; 
	arg.push_back(ENTITY::PLANET::SURFACE::LAVA_ID); arg.push_back(5);
	g_TEXTURE_MANAGER.Add( new TextureOb(TEXTURE::PLANET_ID, "data/planet/p_2000.png", false, &arg) );
}

{
	std::vector<int> arg; 
	arg.push_back(ENTITY::PLANET::SURFACE::ICE_ID); arg.push_back(5);
	g_TEXTURE_MANAGER.Add( new TextureOb(TEXTURE::PLANET_ID, "data/planet/p_3000.png", false, &arg) );
}

{
	std::vector<int> arg; 
	arg.push_back(ENTITY::PLANET::SURFACE::GAS_ID); arg.push_back(5);
	g_TEXTURE_MANAGER.Add( new TextureOb(TEXTURE::PLANET_ID, "data/planet/p_4000.png", false, &arg) );
}

//################################ ATMOSPHERE_TEXTURE ####################################
{
	std::vector<int> arg; 
	g_TEXTURE_MANAGER.Add( new TextureOb(TEXTURE::ATMOSPHERE_ID, "data/planet/atmosphere_000.png", true, &arg) );
}

{
	std::vector<int> arg; 
	g_TEXTURE_MANAGER.Add( new TextureOb(TEXTURE::ATMOSPHERE_ID, "data/planet/atmosphere_001.png", true, &arg) );
}


//################################ EFFECTS TEXTURE ###################################
{
	std::vector<int> arg;  
	arg.push_back(COLOR::RED_ID); 
	g_TEXTURE_MANAGER.Add( new TextureOb(TEXTURE::PARTICLE_EFFECT_ID, "data/effect/particles/particle0.png", true, &arg) ); 
}

{
	std::vector<int> arg;  
	arg.push_back(COLOR::BLUE_ID); 
	g_TEXTURE_MANAGER.Add( new TextureOb(TEXTURE::PARTICLE_EFFECT_ID, "data/effect/particles/particle1.png", true, &arg) ); 
}

{
	std::vector<int> arg;  
	arg.push_back(COLOR::YELLOW_ID); 
	g_TEXTURE_MANAGER.Add( new TextureOb(TEXTURE::PARTICLE_EFFECT_ID, "data/effect/particles/particle2.png", true, &arg) ); 
}

{
	std::vector<int> arg;  
	arg.push_back(COLOR::GREY_ID); 
	g_TEXTURE_MANAGER.Add( new TextureOb(TEXTURE::PARTICLE_EFFECT_ID, "data/effect/particles/particle3.png", true, &arg) ); 
}

//{
	//std::vector<int> arg;  
	//arg.push_back(TECHLEVEL::L0_ID); arg.push_back(COLOR::BLUE_ID); 
	//g_TEXTURE_MANAGER.Add( new TextureOb(TEXTURE::LAZER_EFFECT_ID, "data/effect/lazer/l_64_26_000.png", true, &arg, 4, 1, 10) );
//}

{
	std::vector<int> arg;  
	arg.push_back(TECHLEVEL::L0_ID); arg.push_back(COLOR::RED_ID); 
	g_TEXTURE_MANAGER.Add( new TextureOb(TEXTURE::LAZER_EFFECT_ID, "data/effect/lazer/l_001.png", true, &arg) );
}

{
	std::vector<int> arg;  
	arg.push_back(TECHLEVEL::L0_ID); arg.push_back(COLOR::YELLOW_ID); 
	g_TEXTURE_MANAGER.Add( new TextureOb(TEXTURE::LAZER_EFFECT_ID, "data/effect/lazer/l_002.png", true, &arg) );
}

{
	std::vector<int> arg;  
	arg.push_back(TECHLEVEL::L0_ID); arg.push_back(COLOR::BLUE_ID); 
	g_TEXTURE_MANAGER.Add( new TextureOb(TEXTURE::LAZER_EFFECT_ID, "data/effect/lazer/l_003.png", true, &arg) );
}

{
	std::vector<int> arg;  
	arg.push_back(COLOR::RED_ID); 
	g_TEXTURE_MANAGER.Add( new TextureOb(TEXTURE::SHIELD_EFFECT_ID, "data/effect/shield/shield0.png", true, &arg) );
}

{
	std::vector<int> arg;  
	arg.push_back(COLOR::GREEN_ID); 
	g_TEXTURE_MANAGER.Add( new TextureOb(TEXTURE::SHIELD_EFFECT_ID, "data/effect/shield/shield1.png", true, &arg) );
}

{
	std::vector<int> arg;  
	arg.push_back(COLOR::BLUE_ID); 
	g_TEXTURE_MANAGER.Add( new TextureOb(TEXTURE::SHIELD_EFFECT_ID, "data/effect/shield/shield2.png", true, &arg) );
}

{
	std::vector<int> arg;  
	arg.push_back(COLOR::YELLOW_ID); 
	g_TEXTURE_MANAGER.Add( new TextureOb(TEXTURE::SHIELD_EFFECT_ID, "data/effect/shield/shield3.png", true, &arg) );
}


// TEXTURE::DISTANTSTAR_ID
{
	std::vector<int> arg;  
	arg.push_back(COLOR::YELLOW_ID); 
	g_TEXTURE_MANAGER.Add( new TextureOb(TEXTURE::DISTANTSTAR_ID, "data/star/s1.png", true, &arg) );
}

{
	std::vector<int> arg;  
	arg.push_back(COLOR::BLUE_ID); 
	g_TEXTURE_MANAGER.Add( new TextureOb(TEXTURE::DISTANTSTAR_ID, "data/star/s2.png", true, &arg) );
}

{
	std::vector<int> arg;  
	arg.push_back(COLOR::RED_ID); 
	g_TEXTURE_MANAGER.Add( new TextureOb(TEXTURE::DISTANTSTAR_ID, "data/star/s3.png", true, &arg) );
}

//{
	//std::vector<int> arg;  
	//arg.push_back(COLOR::RED_ID); 
	//g_TEXTURE_MANAGER.Add( new TextureOb(TEXTURE::DISTANTSTAR_ID, "data/star/s4.png", true, &arg) );
//}

//###################################### ITEM TEXTURE ###################################
//############################ DRIVE_ITEM
//#################### RACE_0
//####### TECH_LEVEL_0
{
	std::vector<int> arg;  
	arg.push_back(RACE::R0_ID); arg.push_back(TECHLEVEL::L0_ID);  
	g_TEXTURE_MANAGER.Add( new TextureOb(TEXTURE::DRIVE_EQUIPMENT_ID, "data/item/drive/drive_Race0_Tech0.png", true, &arg) );
}

//####### TECH_LEVEL_1
{
	std::vector<int> arg;  
	arg.push_back(RACE::R0_ID); arg.push_back(TECHLEVEL::L1_ID);  
	g_TEXTURE_MANAGER.Add( new TextureOb(TEXTURE::DRIVE_EQUIPMENT_ID, "data/item/drive/drive_Race0_Tech1.png", true, &arg) );
}

//####### TECH_LEVEL_2
{
	std::vector<int> arg;  
	arg.push_back(RACE::R0_ID); arg.push_back(TECHLEVEL::L2_ID); 
	g_TEXTURE_MANAGER.Add( new TextureOb(TEXTURE::DRIVE_EQUIPMENT_ID, "data/item/drive/drive_Race0_Tech2.png", true, &arg) );
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
	g_TEXTURE_MANAGER.Add( new TextureOb(TEXTURE::LAZER_EQUIPMENT_ID, "data/item/lazer/lazer_Race0_Tech0_Red0.png", true, &arg) );
}

{
	std::vector<int> arg;  
	arg.push_back(RACE::R0_ID); arg.push_back(TECHLEVEL::L0_ID); arg.push_back(COLOR::YELLOW_ID); 
	g_TEXTURE_MANAGER.Add( new TextureOb(TEXTURE::LAZER_EQUIPMENT_ID, "data/item/lazer/lazer_Race0_Tech0_Yellow0.png", true, &arg) );
}

{
	std::vector<int> arg;  
	arg.push_back(RACE::R0_ID); arg.push_back(TECHLEVEL::L0_ID); arg.push_back(COLOR::BLUE_ID); 
	g_TEXTURE_MANAGER.Add( new TextureOb(TEXTURE::LAZER_EQUIPMENT_ID, "data/item/lazer/lazer_Race0_Tech0_Blue0.png", true, &arg) );
}

//####### TECH_LEVEL_1
{
	std::vector<int> arg;  
	arg.push_back(RACE::R0_ID); arg.push_back(TECHLEVEL::L1_ID); arg.push_back(COLOR::BLUE_ID); 
	g_TEXTURE_MANAGER.Add( new TextureOb(TEXTURE::LAZER_EQUIPMENT_ID, "data/item/lazer/lazer_Race0_Tech1_Blue0.png", true, &arg) );
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
	g_TEXTURE_MANAGER.Add( new TextureOb(TEXTURE::ROCKET_EQUIPMENT_ID, "data/item/rocket/rocket_Race0_Tech0.png", true, &arg) );
}
//####### TECH_LEVEL_1
{
	std::vector<int> arg;  
	arg.push_back(RACE::R0_ID); arg.push_back(TECHLEVEL::L1_ID); arg.push_back(COLOR::YELLOW_ID); 
	g_TEXTURE_MANAGER.Add( new TextureOb(TEXTURE::ROCKET_EQUIPMENT_ID, "data/item/rocket/rocket_Race0_Tech1.png", true, &arg) );
}
//####### TECH_LEVEL_2
{
	std::vector<int> arg;  
	arg.push_back(RACE::R0_ID); arg.push_back(TECHLEVEL::L1_ID); arg.push_back(COLOR::YELLOW_ID); 
	g_TEXTURE_MANAGER.Add( new TextureOb(TEXTURE::ROCKET_EQUIPMENT_ID, "data/item/rocket/rocket_Race0_Tech2.png", true, &arg) );
}

//TEXTURE_MANAGER.manageItem( textureOb(TORPED_ITEM_TEXTURE_ID, 'data/item/torped/tl0.png', True, [ 'torpedo',       TECHLEVEL::L0_ID, 3, 1, RACE::R0_ID, COLOR::YELLOW_ID]) )
//TEXTURE_MANAGER.manageItem( textureOb(TORPED_ITEM_TEXTURE_ID, 'data/item/torped/tl1.png', True, [ 'torpedo',       TECHLEVEL::L0_ID, 3, 1, RACE::R0_ID, COLOR::YELLOW_ID]) )

{
	std::vector<int> arg;  
	g_TEXTURE_MANAGER.Add( new TextureOb(TEXTURE::ROCKET_BULLET_ID, "data/bullet/r_0.png", true, &arg) );
}

{
	std::vector<int> arg;  
	g_TEXTURE_MANAGER.Add( new TextureOb(TEXTURE::ROCKET_BULLET_ID, "data/bullet/r_1.png", true, &arg) );
}

//{
	//std::vector<int> arg;  
	//g_TEXTURE_MANAGER.Add( new TextureOb(TEXTURE::ROCKET_BULLET_ID, "data/bullet/t_0.png", true, &arg) );
//}

//{
	//std::vector<int> arg;  
	//g_TEXTURE_MANAGER.Add( new TextureOb(TEXTURE::ROCKET_BULLET_ID, "data/bullet/t_1.png", true, &arg) );
//}
//TEXTURE_MANAGER.manage( textureOb(TORPED_BULLET_TEXTURE_ID, 'data/bullet/t_0.png', True, []) )
//TEXTURE_MANAGER.manage( textureOb(TORPED_BULLET_TEXTURE_ID, 'data/bullet/t_1.png', True, []) )



//############################ PROTECTOR_ITEM
//#################### RACE_0
//####### TECH_LEVEL_0
{
	std::vector<int> arg;  
	arg.push_back(RACE::R0_ID); arg.push_back(TECHLEVEL::L0_ID); 
	g_TEXTURE_MANAGER.Add( new TextureOb(TEXTURE::PROTECTOR_EQUIPMENT_ID, "data/item/protector/protector_Race0_Tech0.png", true, &arg) );
}

//####### TECH_LEVEL_1
{
	std::vector<int> arg;  
	arg.push_back(RACE::R0_ID); arg.push_back(TECHLEVEL::L1_ID); 
	g_TEXTURE_MANAGER.Add( new TextureOb(TEXTURE::PROTECTOR_EQUIPMENT_ID, "data/item/protector/protector_Race0_Tech1.png", true, &arg) );
}

//####### TECH_LEVEL_2
{
	std::vector<int> arg;  
	arg.push_back(RACE::R0_ID); arg.push_back(TECHLEVEL::L2_ID); 
	g_TEXTURE_MANAGER.Add( new TextureOb(TEXTURE::PROTECTOR_EQUIPMENT_ID, "data/item/protector/protector_Race0_Tech2.png", true, &arg) );
}
//####### TECH_LEVEL_3
{
	std::vector<int> arg;  
	arg.push_back(RACE::R0_ID); arg.push_back(TECHLEVEL::L3_ID); 
	g_TEXTURE_MANAGER.Add( new TextureOb(TEXTURE::PROTECTOR_EQUIPMENT_ID, "data/item/protector/protector_Race0_Tech3.png", true, &arg) );
}

//############################ DROID_ITEM
//#################### RACE_0
//####### TECH_LEVEL_0
{
	std::vector<int> arg;  
	arg.push_back(RACE::R0_ID); arg.push_back(TECHLEVEL::L0_ID); 
	g_TEXTURE_MANAGER.Add( new TextureOb(TEXTURE::DROID_EQUIPMENT_ID, "data/item/droid/droid_Race0_Tech0.png", true, &arg) );
}

//####### TECH_LEVEL_1
{
	std::vector<int> arg;  
	arg.push_back(RACE::R0_ID); arg.push_back(TECHLEVEL::L1_ID); 
	g_TEXTURE_MANAGER.Add( new TextureOb(TEXTURE::DROID_EQUIPMENT_ID, "data/item/droid/droid_Race0_Tech1.png", true, &arg) );
}

//####### TECH_LEVEL_2
{
	std::vector<int> arg;  
	arg.push_back(RACE::R0_ID); arg.push_back(TECHLEVEL::L2_ID); 
	g_TEXTURE_MANAGER.Add( new TextureOb(TEXTURE::DROID_EQUIPMENT_ID, "data/item/droid/droid_Race0_Tech2.png", true, &arg) );
}


//############################ GRAPPLE_ITEM
//#################### RACE_0
//####### TECH_LEVEL_0
{
	std::vector<int> arg;  
	arg.push_back(RACE::R0_ID); arg.push_back(TECHLEVEL::L0_ID); 
	g_TEXTURE_MANAGER.Add( new TextureOb(TEXTURE::GRAPPLE_EQUIPMENT_ID, "data/item/grapple/grapple_Race0_Tech0.png", true, &arg) );
}

//####### TECH_LEVEL_1
{
	std::vector<int> arg;  
	arg.push_back(RACE::R0_ID); arg.push_back(TECHLEVEL::L1_ID); 
	g_TEXTURE_MANAGER.Add( new TextureOb(TEXTURE::GRAPPLE_EQUIPMENT_ID, "data/item/grapple/grapple_Race0_Tech1.png", true, &arg) );
}



//############################ BAK_ITEM
//#################### RACE_0
//####### TECH_LEVEL_0
{
	std::vector<int> arg;  
	arg.push_back(RACE::R0_ID); arg.push_back(TECHLEVEL::L0_ID); 
	g_TEXTURE_MANAGER.Add( new TextureOb(TEXTURE::BAK_EQUIPMENT_ID, "data/item/bak/bak_Race0_Tech0.png", true, &arg) );
}

//####### TECH_LEVEL_1
{
	std::vector<int> arg;  
	arg.push_back(RACE::R0_ID); arg.push_back(TECHLEVEL::L1_ID); 
	g_TEXTURE_MANAGER.Add( new TextureOb(TEXTURE::BAK_EQUIPMENT_ID, "data/item/bak/bak_Race0_Tech1.png", true, &arg) );
}


//############################ ENERGYBLOCK_ITEM
//#################### RACE_0
//####### TECH_LEVEL_0
{
	std::vector<int> arg;  
	arg.push_back(RACE::R0_ID); arg.push_back(TECHLEVEL::L0_ID); 
	g_TEXTURE_MANAGER.Add( new TextureOb(TEXTURE::ENERGIZER_EQUIPMENT_ID, "data/item/energyBlock/energyBlock_Race0_Tech0.png", true, &arg) );
}

//####### TECH_LEVEL_1
{
	std::vector<int> arg;  
	arg.push_back(RACE::R0_ID); arg.push_back(TECHLEVEL::L1_ID); 
	g_TEXTURE_MANAGER.Add( new TextureOb(TEXTURE::ENERGIZER_EQUIPMENT_ID, "data/item/energyBlock/energyBlock_Race0_Tech1.png", true, &arg) );
}


//############################ FREEZER_ITEM
//#################### RACE_0
//####### TECH_LEVEL_0
{
	std::vector<int> arg;  
	arg.push_back(RACE::R0_ID); arg.push_back(TECHLEVEL::L0_ID); 
	g_TEXTURE_MANAGER.Add( new TextureOb(TEXTURE::FREEZER_EQUIPMENT_ID, "data/item/freezer/freezer_Race0_Tech0.png", true, &arg) );
}

//####### TECH_LEVEL_1
{
	std::vector<int> arg;  
	arg.push_back(RACE::R0_ID); arg.push_back(TECHLEVEL::L1_ID); 
	g_TEXTURE_MANAGER.Add( new TextureOb(TEXTURE::FREEZER_EQUIPMENT_ID, "data/item/freezer/freezer_Race0_Tech1.png", true, &arg) );
}


//############################ FREEZER_ITEM
//#################### RACE_0
//####### TECH_LEVEL_0
{
	std::vector<int> arg;  
	arg.push_back(RACE::R0_ID); arg.push_back(TECHLEVEL::L0_ID); 
	g_TEXTURE_MANAGER.Add( new TextureOb(TEXTURE::SCANER_EQUIPMENT_ID, "data/item/scaner/scaner_Race0_Tech0.png", true, &arg, 3, 1) );
}
//####### TECH_LEVEL_1
{
	std::vector<int> arg;  
	arg.push_back(RACE::R0_ID); arg.push_back(TECHLEVEL::L1_ID); 
	g_TEXTURE_MANAGER.Add( new TextureOb(TEXTURE::SCANER_EQUIPMENT_ID, "data/item/scaner/scaner_Race0_Tech1.png", true, &arg, 3, 1) );
}

//############################ FREEZER_ITEM
//#################### RACE_0
//####### TECH_LEVEL_0
{
	std::vector<int> arg;  
	arg.push_back(RACE::R0_ID); arg.push_back(TECHLEVEL::L0_ID); 
	g_TEXTURE_MANAGER.Add( new TextureOb(TEXTURE::RADAR_EQUIPMENT_ID, "data/item/radar/radar_Race0_Tech0.png", true, &arg, 3, 1) );
}

//####### TECH_LEVEL_1
{
	std::vector<int> arg;  
	arg.push_back(RACE::R0_ID); arg.push_back(TECHLEVEL::L1_ID); 
	g_TEXTURE_MANAGER.Add( new TextureOb(TEXTURE::RADAR_EQUIPMENT_ID, "data/item/radar/radar_Race0_Tech1.png", true, &arg, 3, 1) );
}


//################## MODULES
{
	std::vector<int> arg;  
	g_TEXTURE_MANAGER.Add(new TextureOb(TEXTURE::MODULE_ID, "data/item/module.png", true, &arg));
}





{
	std::vector<int> arg;  
	g_GUI_TEXTUREOB_COLLECTOR.starsystem_mark_enemy = new TextureOb(NONE_ID, "data/other/mark_enemy_ss.png", true, &arg);
}

{
	std::vector<int> arg;  
	g_GUI_TEXTUREOB_COLLECTOR.starsystem_mark_player = new TextureOb(NONE_ID, "data/other/mark_player_ss.png", true, &arg);
}



{
	std::vector<int> arg;  
	g_GUI_TEXTUREOB_COLLECTOR.icon_minus = new TextureOb(NONE_ID, "data/icon/minus.png", true, &arg);
}

{
	std::vector<int> arg;  
	g_GUI_TEXTUREOB_COLLECTOR.icon_plus = new TextureOb(NONE_ID, "data/icon/plus.png", true, &arg);
}

{
	std::vector<int> arg;  
	g_GUI_TEXTUREOB_COLLECTOR.skill = new TextureOb(NONE_ID, "data/other/skill.png", true, &arg);
}

{
	std::vector<int> arg;  
	g_GUI_TEXTUREOB_COLLECTOR.skill_transparent = new TextureOb(NONE_ID, "data/other/skill_transparent.png", true, &arg);
}

{
	std::vector<int> arg;  
	g_GUI_TEXTUREOB_COLLECTOR.icon_map = new TextureOb(NONE_ID, "data/icon/starsystem_ICON.png", true, &arg);
}

{
	std::vector<int> arg;  
	g_GUI_TEXTUREOB_COLLECTOR.grapple_trail = new TextureOb(NONE_ID, "data/effect/grapple_jet.png", true, &arg);
}

{
	std::vector<int> arg;  
	g_GUI_TEXTUREOB_COLLECTOR.dot_blue = new TextureOb(NONE_ID, "data/other/dot_blue.png", true, &arg);
}

{
	std::vector<int> arg;  
	g_GUI_TEXTUREOB_COLLECTOR.dot_green = new TextureOb(NONE_ID, "data/other/dot_green.png", true, &arg);
}

{
	std::vector<int> arg;  
	g_GUI_TEXTUREOB_COLLECTOR.dot_red = new TextureOb(NONE_ID, "data/other/dot_red.png", true, &arg);
}

{
	std::vector<int> arg;  
	g_GUI_TEXTUREOB_COLLECTOR.dot_black = new TextureOb(NONE_ID, "data/other/dot_black.png", true, &arg);
}

{
	std::vector<int> arg;  
	g_GUI_TEXTUREOB_COLLECTOR.dot_yellow = new TextureOb(NONE_ID, "data/other/dot_yellow.png", true, &arg);
}

{
	std::vector<int> arg;  
	g_GUI_TEXTUREOB_COLLECTOR.dot_purple = new TextureOb(NONE_ID, "data/other/dot_purple.png", true, &arg);
}

{
	std::vector<int> arg;  
	g_GUI_TEXTUREOB_COLLECTOR.bar_radar = new TextureOb(NONE_ID, "data/gui/radar_bar.png", true, &arg);
}

{
	std::vector<int> arg;  
	g_GUI_TEXTUREOB_COLLECTOR.bar_bottom = new TextureOb(NONE_ID, "data/gui/bar_bottom.png", true, &arg);
}

{
	std::vector<int> arg;  
	g_GUI_TEXTUREOB_COLLECTOR.bar_left = new TextureOb(NONE_ID, "data/gui/bar_left.png", true, &arg);
}

{
	std::vector<int> arg;  
	g_GUI_TEXTUREOB_COLLECTOR.bar_top = new TextureOb(NONE_ID, "data/gui/bar_top.png", true, &arg);
}

{
	std::vector<int> arg;  
	g_GUI_TEXTUREOB_COLLECTOR.bar_top = new TextureOb(NONE_ID, "data/gui/bar_top.png", true, &arg);
}

{
	std::vector<int> arg;  
	g_GUI_TEXTUREOB_COLLECTOR.text_background =  new TextureOb(NONE_ID, "data/other/text_background.png", true, &arg);
}

{
	std::vector<int> arg;  
	g_GUI_TEXTUREOB_COLLECTOR.slot_mark_accept =  new TextureOb(NONE_ID, "data/other/slot_mark_accept.png", true, &arg);
}

{
	std::vector<int> arg;  
	g_GUI_TEXTUREOB_COLLECTOR.slot_mark_reject =  new TextureOb(NONE_ID, "data/other/slot_mark_reject.png", true, &arg);
}

}




void loadShaders()
{
//static const char * pTo_lightVertexSource = {
//"/* vertex */"
//"    void main() {"
//"        gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;"
//"    }"
//};   

//static const char * pTo_lightFragSource = {
//"/* fragment */"
//"    void main() {"
//"        gl_FragColor = vec4(0.0, 1.0, 0.0, 0.0);"
//"    }"
//};       

static const char * pTo_blackToAlphaVertexSource = {
"/* vertex */"
"void main()" 
"{"
"  gl_Position = ftransform();"
"  gl_TexCoord[0] = gl_MultiTexCoord0;"
"}"
};   

static const char * pTo_blackToAlphaFragSource = {
"/* fragment */"
"uniform sampler2D sceneTex;     /* texture unit 0 */"
"void main()"
"{"
"    vec4 c = texture2D(sceneTex, gl_TexCoord[0].st);"
"    float rgb = c.r + c.g + c.b;"
"    if (c.g > 0.6)"
"       gl_FragColor = vec4(0.0, 0.0, 0.0, 0.0);"
"    else"
"       gl_FragColor = c;"
"}"
};       

g_SHADERS_PACK.black2alpha = glCreateProgram();
compile_program(pTo_blackToAlphaVertexSource, pTo_blackToAlphaFragSource, g_SHADERS_PACK.black2alpha);





// shaders are taken from http://www.geeks3d.com/20091116/shader-library-2d-shockwave-post-processing-filter-glsl/
static const GLchar * pTo_shockWaveVertexSource = {
"/* Vertex program */"
" "
"void main(void)"
"{"
"  gl_Position = ftransform();"
"  gl_TexCoord[0] = gl_MultiTexCoord0;"
"}"
};


static const GLchar * pTo_shockWaveFragSource = {
"/* Fragment program */"
" "
"uniform sampler2D sceneTex;     /* texture unit 0 */"
"uniform vec2 center[10];"        
"uniform vec3 shockParams[10];   /* 10.0, 0.8, 0.1 */" 
"uniform float time[10];         /* effect elapsed time */"
"uniform int imax;               /* how many shaders */"
" "
"void main()"
"{"
"  vec2 uv = gl_TexCoord[0].xy;"
"  vec2 texCoord = uv;"
"  for(int i=0; i<imax; i++)"
"  {"
"      float distance = distance(uv, center[i]);"
"      /* if ( (distance <= (time[i] + shockParams[i].z)) && (distance >= (time[i] - shockParams[i].z)) ) */"
"      if (distance <= (time[i] + shockParams[i].z))"
"         if (distance >= (time[i] - shockParams[i].z))"
"         {"
"              float diff = (distance - time[i]);"
"              float powDiff = 1.0 - pow(abs(diff*shockParams[i].x), shockParams[i].y);"
"              float diffTime = diff  * powDiff;"
"              vec2 diffUV = normalize(uv - center[i]);"
"              texCoord = uv + (diffUV * diffTime);"
"         }"
"  }"
" "
"  gl_FragColor = texture2D(sceneTex, texCoord);"
"}"
};

g_SHADERS_PACK.shockwave = glCreateProgram();
compile_program(pTo_shockWaveVertexSource, pTo_shockWaveFragSource, g_SHADERS_PACK.shockwave);





static const GLchar * pTo_volumetricLightVertexSource = {
"/* Vertex program */"
" "
"void main(void)"
"{"
"  gl_Position = ftransform();"
"  gl_TexCoord[0] = gl_MultiTexCoord0;"
"}"
};


static const GLchar * pTo_volumetricLightFragSource = {
"/* Fragment program */"
" "
"uniform sampler2D FullSampler;"
"uniform sampler2D BlurSampler;"
"uniform vec4 sun_pos;"
" "
"const vec4 ShaftParams	= vec4(0.05, 1.0, 0.05, 1.0);"
"const vec4 sunColor	= vec4(0.9, 0.8, 0.6, 1.0);"
" "
"float saturate(float val)"
"{"
"	return clamp(val,0.0,1.0);"
"}"
" "
"void main(void)"
"{ "
"	vec2  sunPosProj = sun_pos.xy;"
"	float sign = sun_pos.w;"
" "
"	vec2  tc = gl_TexCoord[0].xy;"
" "
"	vec2  sunVec = sunPosProj.xy - tc; /* + vec2(0.5,0.5); */"
"	float sunDist = saturate(sign) * (1.0 - saturate(dot(sunVec,sunVec) * ShaftParams.y));"
" "
"	sunVec *= ShaftParams.x * sign;"
" "
"	tc += sunVec;"
"	vec4 accum = texture2D(BlurSampler, tc);"
"	tc += sunVec;"
"	accum += texture2D(BlurSampler, tc) * 0.875;"
"	tc += sunVec;"
"	accum += texture2D(BlurSampler, tc) * 0.75;"
"	tc += sunVec;"
"	accum += texture2D(BlurSampler, tc) * 0.625;"
"	tc += sunVec;"
"	accum += texture2D(BlurSampler, tc) * 0.5;"
"	tc += sunVec;"
"	accum += texture2D(BlurSampler, tc) * 0.375;"
"	tc += sunVec;"
"	accum += texture2D(BlurSampler, tc) * 0.25;"
"	tc += sunVec;"
"	accum += texture2D(BlurSampler, tc) * 0.125;"
" "
"	accum  *= 1.65 * sunDist;"
" "
"	vec4 cScreen = texture2D(FullSampler, gl_TexCoord[0].xy);"
"	accum = cScreen + accum * ShaftParams.w * sunColor * ( 1.0 - cScreen );"
" "
"	gl_FragColor = accum;"
"}"
};

g_SHADERS_PACK.volumetriclight = glCreateProgram();
compile_program(pTo_volumetricLightVertexSource, pTo_volumetricLightFragSource, g_SHADERS_PACK.volumetriclight );


















//http://www.gamedev.ru/code/forum/?id=90743
static const GLchar * pTo_lightVertexSource = {
"/* Vertex program */"
" "
"uniform vec4 lightPos, eyePos;"
"varying vec3 l, v, n;"
" "
"void main(void)"
"{"
"    vec3 p = vec3(gl_ModelViewMatrix * gl_Vertex);      /* transformed point to world space */ "
"    l = normalize(vec3(lightPos) - p);                  /* vector to light source */           "
"    v = normalize(vec3(eyePos)   - p);                  /* vector to the eye */                "
"    n = normalize(gl_NormalMatrix * gl_Normal);         /* transformed n */                    "
"    gl_TexCoord[0] = gl_MultiTexCoord0;                                                        " 
" "
"    gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;                                    "
"}"
};   

//http://www.gamedev.ru/code/forum/?id=90743
static const GLchar * pTo_lightFragSource = {
"/* Fragment program */"
" "
"uniform sampler2D Texture_0;"
"varying vec3 l, v, n;"
" "
"void main (void)"
"{"
"    const vec4  diffColor = vec4(1.0, 1.0, 1.0, 1.0);"
"    const vec4  ambientColor = vec4(0.1, 0.1, 0.1, 1.0);"
"    const vec4  specColor = vec4(0.7, 0.7, 0.0, 0.0);"
"    const float specPower = 30.0;"
" "
"    vec3 n2   = normalize(n);"
"    vec3 l2   = normalize(l);"
"    vec3 v2   = normalize(v);"
"    vec3 r    = reflect(-v2, n2);"
"    vec4 diff = diffColor * max(dot(n2, l2), 0.0);"
"    vec4 spec = specColor * pow(max(dot(l2, r), 0.0), specPower);"
"    vec2 texCoord0 = gl_TexCoord[0].xy;"
"    vec4 texColor0 = texture2D(Texture_0, texCoord0);"
" "
"    gl_FragColor = (diff + ambientColor) * texColor0;"
"}"
};       

g_SHADERS_PACK.light = glCreateProgram();
compile_program(pTo_lightVertexSource, pTo_lightFragSource, g_SHADERS_PACK.light);








static const GLchar * pTo_blurVertexSource = {
"/* Vertex program */"
" "
"void main(void)"
"{"
"  gl_Position = ftransform();"
"  gl_TexCoord[0] = gl_MultiTexCoord0;"
"}"
};     

static const GLchar * pTo_blurFragmentSource = {
"/* Fragment program */"
"uniform sampler2D sceneTex;  /* 0 */"
" "
"uniform float rt_w;    /* render target width  */"
"uniform float rt_h;    /* render target height */"
"uniform float vx_offset;"
" "
"float offset[3] = float[]( 0.0, 1.3846153846, 3.2307692308 );"
"float weight[3] = float[]( 0.2270270270, 0.3162162162, 0.0702702703 );"
" "
"void main()"
"{"
"  vec3 tc = vec3(0.0, 0.0, 0.0);"
"  if (gl_TexCoord[0].x<(vx_offset-0.01))"
"  {"
"    vec2 uv = gl_TexCoord[0].xy;"
"    tc = texture2D(sceneTex, uv).rgb * weight[0];"
" "
"    for (int i=1; i<3; i++)"
"    {"
"      tc += texture2D(sceneTex, uv + vec2(offset[i])/rt_w, 0.0).rgb * weight[i];"
"      tc += texture2D(sceneTex, uv - vec2(offset[i])/rt_w, 0.0).rgb * weight[i];"
"    }"
"  }"
"  else if (gl_TexCoord[0].x>=(vx_offset+0.01))"
"  {"
"    tc = texture2D(sceneTex, gl_TexCoord[0].xy).rgb;"
"  }"
"  gl_FragColor = vec4(tc, 1.0);"
"}"
};  

g_SHADERS_PACK.blur = glCreateProgram();
compile_program(pTo_blurVertexSource, pTo_blurFragmentSource, g_SHADERS_PACK.blur);





static const GLchar * pTo_extractBrightVertexSource = {
"/* Vertex program */"
" "
"void main(void)"
"{"
"  gl_Position = ftransform();"
"  gl_TexCoord[0] = gl_MultiTexCoord0;"
"}"
};  


static const GLchar * pTo_extractBrightFragmentSource = {
"/* Fragment program */"
"uniform sampler2D source;"
"uniform float threshold;"
" "
"void main(void)"
"{"
"    vec4 c = texture2D(source, gl_TexCoord[0].st);"
"    float rgb = c.r + c.g + c.b;"
"    if (rgb > threshold)   /* threshold ~ 1.9 */ "
"       gl_FragColor = c;"
"    else"
"       gl_FragColor = vec4(0.0, 0.0, 0.0, 0.0);"
"}"
};  

g_SHADERS_PACK.extractbright = glCreateProgram();
compile_program(pTo_extractBrightVertexSource, pTo_extractBrightFragmentSource, g_SHADERS_PACK.extractbright);







static const GLchar * pTo_combineVertexSource = {
"/* Vertex program */"
" "
"void main(void)"
"{"
"  gl_Position = ftransform();   /* This transforms the input vertex the same way the fixed-function pipeline would */"
"  gl_TexCoord[0] = gl_MultiTexCoord0;"
"}"
};  


static const GLchar * pTo_combineFragmentSource = {
"/* Fragment program */"
"uniform sampler2D Scene;"
" "
"uniform sampler2D Pass0_tex1;"
"uniform sampler2D Pass0_tex2;"
"uniform sampler2D Pass0_tex3;"
"uniform sampler2D Pass0_tex4;"
" "
"uniform sampler2D Pass1_tex1;"
"uniform sampler2D Pass1_tex2;"
"uniform sampler2D Pass1_tex3;"
"uniform sampler2D Pass1_tex4;"
" "
"uniform sampler2D Pass2_tex1;"
"uniform sampler2D Pass2_tex2;"
"uniform sampler2D Pass2_tex3;"
"uniform sampler2D Pass2_tex4;"
" "
"void main(void)"
"{"
"    vec4 t0 = texture2D(Scene, gl_TexCoord[0].st);"
" "
"    vec4 p0t1 = texture2D(Pass0_tex1, gl_TexCoord[0].st);"
"    vec4 p0t2 = texture2D(Pass0_tex2, gl_TexCoord[0].st);"
"    vec4 p0t3 = texture2D(Pass0_tex3, gl_TexCoord[0].st);"
"    vec4 p0t4 = texture2D(Pass0_tex4, gl_TexCoord[0].st);"
" "
"    vec4 p1t1 = texture2D(Pass1_tex1, gl_TexCoord[0].st);"
"    vec4 p1t2 = texture2D(Pass1_tex2, gl_TexCoord[0].st);"
"    vec4 p1t3 = texture2D(Pass1_tex3, gl_TexCoord[0].st);"
"    vec4 p1t4 = texture2D(Pass1_tex4, gl_TexCoord[0].st);"
" "
"    vec4 p2t1 = texture2D(Pass2_tex1, gl_TexCoord[0].st);"
"    vec4 p2t2 = texture2D(Pass2_tex2, gl_TexCoord[0].st);"
"    vec4 p2t3 = texture2D(Pass2_tex3, gl_TexCoord[0].st);"
"    vec4 p2t4 = texture2D(Pass2_tex4, gl_TexCoord[0].st);"
" "
" "
"    gl_FragColor = t0 + p0t1 + p0t2 + p0t3 + p0t4 + p1t1 + p1t2 + p1t3 + p1t4 + p2t1 + p2t2 + p2t3 + p2t4;"
"}"
};  

g_SHADERS_PACK.combine = glCreateProgram();
compile_program(pTo_combineVertexSource, pTo_combineFragmentSource, g_SHADERS_PACK.combine);









static const GLchar * pTo_multitexVertexSource = {
"/* Vertex program */"
" "
"void main(void)"
"{"
"  gl_Position = ftransform();"
"  gl_TexCoord[0] = gl_MultiTexCoord0;"
"}"
};


static const GLchar * pTo_multitexFragmentSource = {
"/* Fragment program */"
"uniform sampler2D Texture_0;     /* texture unit 0 */"
"uniform sampler2D Texture_1;"
" "
"uniform vec2 displ;"
" "
"void main() {"
"  vec2 uv = gl_TexCoord[0].xy;"
"  vec2 texCoord0 = uv - displ;"
"  vec2 texCoord1 = uv + displ;"
" "
"  vec4 color0 = texture2D(Texture_0, texCoord0);"
"  vec4 color1 = texture2D(Texture_1, texCoord1);"
"  /*vec4 color3 = vec4(1.0, 1.0, 0.0, 1.0); */"
"  vec4 tmp = mix(color0, color1, 0.5);"
" "
"  /*gl_FragColor = mix(tmp, color3, 0.4); */"
"  gl_FragColor = tmp;"
"}"
};

    
g_SHADERS_PACK.multitexturing = glCreateProgram();
compile_program(pTo_multitexVertexSource, pTo_multitexFragmentSource, g_SHADERS_PACK.multitexturing);
}
