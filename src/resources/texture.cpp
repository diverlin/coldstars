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


#include "texture.h"


TextureOb :: TextureOb()
{}

TextureOb :: TextureOb(int _type_id, std::string _path, bool _use_alpha, std::vector<int>* pTo_arg, int _columns_num, int _rows_num, float _fps)
{
    // TexOb attributes Init
    race_id = -1;
    tech_level_id = -1;

    color_id = -1;
    //color_r = 256;
    //color_g = 256;
    //color_b = 256;
    is_rotated = false;
    //

    type_id = _type_id; 
    id      = g_TEXTURE_ID_GENERATOR.returnNextId();
    
    path      = _path;
    use_alpha = _use_alpha;
    
    //slice_w = _slice_w;
    //slice_h = _slice_h;

    if ((_columns_num == 1) && (_rows_num == 1))
    {
        is_animated = false;
        loadSingleToVRAM();
        //removeSingleFromVRAM();
    }
    else
    {
        is_animated = true;
        loadSingleToVRAM();
        identifyTextureCoords(_columns_num, _rows_num, _fps);
        //removeSlicedFromVRAM();
    }         
       
    is_loaded = false;
    is_shared = false;


    if (type_id == SLOT_TEXTURE_ID)
       slotArgManager(pTo_arg);

    if (type_id == TURREL_TEXTURE_ID)
       turrelArgManager(pTo_arg);

    if (type_id == NEBULA_TEXTURE_ID)
       nebulaArgManager(pTo_arg);
          
    if (type_id == STAR_TEXTURE_ID)
       starArgManager(pTo_arg); 
 
    if (type_id == PLANET_TEXTURE_ID)
       planetArgManager(pTo_arg);
         
    if (type_id == ATMOSPHERE_TEXTURE_ID)
       atmosphereArgManager(pTo_arg);
 
    if (type_id == LAND_BG_TEXTURE_ID)
       landBgArgManager(pTo_arg);

    //######### IN KOSMOPORT
    if (type_id == ANGAR_BG_TEXTURE_ID)
       angarBgArgManager(pTo_arg);

    if (type_id == STORE_BG_TEXTURE_ID)
       storeBgArgManager(pTo_arg);

    if (type_id == SHOP_BG_TEXTURE_ID)
       shopBgArgManager(pTo_arg);

    if (type_id == GOVERMENT_BG_TEXTURE_ID)
       govermentBgArgManager(pTo_arg);
    //#########################################


    if (type_id == FACE_TEXTURE_ID)
       { loadToVRAM();
         faceArgManager(pTo_arg); }


    // other
    if (type_id == TEXT_BACKGROUND_TEXTURE_ID)
       { loadToVRAM();
       }
         


    if (type_id == SPUTNIK_TEXTURE_ID)
       { loadToVRAM();
         sputnikArgManager(pTo_arg); }

    if (type_id == SHIP_TEXTURE_ID)
       { loadToVRAM();
         shipArgManager(pTo_arg); }
          
    if (type_id == PARTICLE_TEXTURE_ID)
       { loadToVRAM();
         particleArgManager(pTo_arg); }

    if (type_id == ROCKET_BULLET_TEXTURE_ID)
       { loadToVRAM();
         rocketBulletArgManager(pTo_arg); }

    if (type_id == LAZER_EFFECT_TEXTURE_ID)
       { loadToVRAM();
         lazerEffectArgManager(pTo_arg); }

          
    if (type_id == DISTANTSTAR_TEXTURE_ID)
       { loadToVRAM();
         distStarArgManager(pTo_arg); }

    if (type_id == LAZER_EFFECT_TEXTURE_ID)
       { loadToVRAM();
         lazerEffectArgManager(pTo_arg); }

    if (type_id == SHIELD_EFFECT_TEXTURE_ID)
       { loadToVRAM();
         shieldEffectArgManager(pTo_arg); }


    // ITEMS
    if (type_id == DRIVE_ITEM_TEXTURE_ID)
        { loadToVRAM();  // remove
          DriveEquipmentArgManager(pTo_arg); }

    if (type_id == LAZER_ITEM_TEXTURE_ID)
        { loadToVRAM();  // remove
          LazerEquipmentArgManager(pTo_arg); }

    if ((type_id == ROCKET_ITEM_TEXTURE_ID) or (type_id == TORPED_ITEM_TEXTURE_ID))
        { loadToVRAM();  // remove
          RocketEquipmentArgManager(pTo_arg); }

    if (type_id == PROTECTOR_ITEM_TEXTURE_ID)
        { loadToVRAM();  // remove
          ProtectorEquipmentArgManager(pTo_arg); }

    if (type_id == DROID_ITEM_TEXTURE_ID)
        { loadToVRAM();  // remove
          DroidEquipmentArgManager(pTo_arg); }

    if (type_id == GRAPPLE_ITEM_TEXTURE_ID)
        { loadToVRAM();  // remove
          GrappleEquipmentArgManager(pTo_arg); }

    if (type_id == BAK_ITEM_TEXTURE_ID)
       { loadToVRAM();  // remove
         BakEquipmentArgManager(pTo_arg); }

    if (type_id == ENERGYBLOCK_ITEM_TEXTURE_ID)
       { loadToVRAM();  // remove
         energyBlockItemArgManager(pTo_arg); }
     

    if (type_id == FREEZER_ITEM_TEXTURE_ID)
       { loadToVRAM();  // remove
         FreezerEquipmentArgManager(pTo_arg); }

    if (type_id == RADAR_ITEM_TEXTURE_ID)
       { loadToVRAM();  // remove
         RadarEquipmentArgManager(pTo_arg); }

    if (type_id == SCANER_ITEM_TEXTURE_ID)
       { loadToVRAM();  // remove
         ScanerEquipmentArgManager(pTo_arg); }

    //# BULLETS
    if (type_id == ROCKET_BULLET_TEXTURE_ID)
       { loadToVRAM();  // remove
         rocketBulletArgManager(pTo_arg); }

    if (type_id == TORPED_BULLET_TEXTURE_ID)
       { loadToVRAM();  // remove
         torpedBulletArgManager(pTo_arg); }


    //### ASTEROIDS/MINERALS
    if (type_id == ASTEROID_TEXTURE_ID)
       { loadToVRAM();  // remove
         asteroidArgManager(pTo_arg); }

    if (type_id == MINERAL_TEXTURE_ID)
       { loadToVRAM();  // remove
         mineralArgManager(pTo_arg); }

    if (type_id == CONTAINER_TEXTURE_ID)
        { loadToVRAM();  // remove
          containerArgManager(pTo_arg); }

    if (type_id == BOMB_TEXTURE_ID)
        { loadToVRAM();  // remove
          bombArgManager(pTo_arg); }

    if (type_id == BLACKHOLE_TEXTURE_ID)
        { loadToVRAM();  // remove
          blackholeArgManager(pTo_arg); }
}  



void TextureOb :: loadToVRAM()
{
    if (is_animated == false)
       loadSingleToVRAM();
    else
       loadSlicedToVRAM();
}         

void TextureOb :: removeFromVRAM()
{
    if (is_animated == false)
       removeSingleFromVRAM();
    else
       removeSlicedFromVRAM();
}         




void TextureOb :: loadSingleToVRAM()
{
     sf::Image Image;
     Image.LoadFromFile(path);
     w = Image.GetWidth();
     h = Image.GetHeight();

     glGenTextures(1, &texture);
     glBindTexture(GL_TEXTURE_2D, texture);
     gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, w, h, GL_RGBA, GL_UNSIGNED_BYTE, Image.GetPixelsPtr());
        
     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
}

void TextureOb :: loadSlicedToVRAM()
{}

void TextureOb :: removeSingleFromVRAM()
{}

void TextureOb :: removeSlicedFromVRAM()
{}



void TextureOb :: identifyTextureCoords(int _columns_num, int _rows_num, float _fps)
{
     frame = 0;
     frames_total_num = 0;

     //printf("_columns_num, _rows_num, w, h = %i, %i, %i, %i\n", _columns_num, _rows_num, w, h);
     w_slice = w/_columns_num;
     h_slice = h/_rows_num;

     float w_slicef, h_slicef;
     w_slicef = (float)w_slice/w;  
     h_slicef = (float)h_slice/h;
     //printf("w_slice, h_slice, = %i, %i\n", w_slice, h_slice);
     //printf("w_slicef, h_slicef, = %f, %f\n", w_slicef, h_slicef);

     float w_offsetf, h_offsetf;

     h_offsetf = 0;
     int r = 0;
     int c = 0;
  
     while (r < _rows_num)
     {
           w_offsetf = 0;
           while (c < _columns_num)
           {
               addTexCoordQuad(w_offsetf, h_offsetf, w_offsetf + w_slicef, h_offsetf + h_slicef);
               w_offsetf += w_slicef;
               frames_total_num++;
               c++;

           }
           h_offsetf += h_slicef;
           r++;
     }


     last_update_time = 0;
     if (_fps == 0)
        fps = frames_total_num*1.3;
     else 
        fps = _fps;
     delay = 1.f/fps;
}


void TextureOb :: addTexCoordQuad(float _w_start, float _h_start, float _w_end, float _h_end)
{
     //printf("=%f,%f,%f,%f\n", _w_start, _h_start, _w_end, _h_end);
     texCoord_bottomLeft_x_list.push_back(_w_start);   // 0
     texCoord_bottomLeft_y_list.push_back(_h_start);   // 0
     texCoord_bottomRight_x_list.push_back(_w_end);    // 1
     texCoord_bottomRight_y_list.push_back(_h_start);  // 0
     texCoord_topLeft_x_list.push_back(_w_end);        // 1
     texCoord_topLeft_y_list.push_back(_h_end);        // 1 
     texCoord_topRight_x_list.push_back(_w_start);     // 0
     texCoord_topRight_y_list.push_back(_h_end);       // 1
}

int TextureOb :: updateAnimationFrame()
{
     float elapsed_time = g_CLOCK.GetElapsedTime();
     if (elapsed_time - last_update_time > delay)
     {
         frame++;
         if ( frame >= texCoord_bottomLeft_x_list.size() )
              frame = 0;
         last_update_time = elapsed_time;
     } 

     return frame; 
}


void TextureOb :: slotArgManager(std::vector<int>* _pTo_arg)
{}
   
void TextureOb :: turrelArgManager(std::vector<int>* _pTo_arg)
{}
   

// SPACE OBJECTS
void TextureOb :: sputnikArgManager(std::vector<int>* _pTo_arg)
{}
   
void TextureOb :: shipArgManager(std::vector<int>* _pTo_arg)
{
     race_id    = (*_pTo_arg)[0];
     subtype_id = (*_pTo_arg)[1];   // warrior/trader and so on
     mod_id     = 0;
          
     size_id = returnObjectSize(w, h);
}

void TextureOb :: nebulaArgManager(std::vector<int>* _arg)
{
     color_id    = (*_arg)[0];
     is_rotated =  (*_arg)[1];
}

void TextureOb :: starArgManager(std::vector<int>* _pTo_arg)
{
	color_id        = (*_pTo_arg)[0];
	brightThreshold = (float)(*_pTo_arg)[1]/1000;
}

void TextureOb :: planetArgManager(std::vector<int>* _pTo_arg)
{}

void TextureOb :: atmosphereArgManager(std::vector<int>* _pTo_arg)
{}


void TextureOb :: asteroidArgManager(std::vector<int>* _pTo_arg)
{}

void TextureOb :: mineralArgManager(std::vector<int>* _pTo_arg)
{}

void TextureOb :: containerArgManager(std::vector<int>* _pTo_arg)
{}

void TextureOb :: bombArgManager(std::vector<int>* _pTo_arg)
{}

void TextureOb :: blackholeArgManager(std::vector<int>* _pTo_arg)
{}

//######### IN KOSMOPORT
void TextureOb :: landBgArgManager(std::vector<int>* _pTo_arg)
{}

void TextureOb :: angarBgArgManager(std::vector<int>* _pTo_arg)
{}

void TextureOb :: storeBgArgManager(std::vector<int>* _pTo_arg)
{}

void TextureOb :: shopBgArgManager(std::vector<int>* _pTo_arg)
{}

void TextureOb :: govermentBgArgManager(std::vector<int>* _pTo_arg)
{}

void TextureOb :: faceArgManager(std::vector<int>* _pTo_arg)
{
   race_id       = (*_pTo_arg)[0];
   subtype_id    = (*_pTo_arg)[1];   // warrior/trader and so on
}


// ITEMS
void TextureOb :: DriveEquipmentArgManager(std::vector<int>* _pTo_arg)
{
   race_id       = (*_pTo_arg)[0];
   tech_level_id = (*_pTo_arg)[1];
}

void TextureOb :: LazerEquipmentArgManager(std::vector<int>* _pTo_arg)
{
   race_id       = (*_pTo_arg)[0];
   tech_level_id = (*_pTo_arg)[1];
   color_id      = (*_pTo_arg)[2];
}

void TextureOb :: RocketEquipmentArgManager(std::vector<int>* _pTo_arg)
{
   race_id       = (*_pTo_arg)[0];
   tech_level_id = (*_pTo_arg)[1];
   color_id      = (*_pTo_arg)[2];
}

void TextureOb :: ProtectorEquipmentArgManager(std::vector<int>* _pTo_arg)
{
   race_id       = (*_pTo_arg)[0];
   tech_level_id = (*_pTo_arg)[1];
}

void TextureOb :: DroidEquipmentArgManager(std::vector<int>* _pTo_arg)
{
   race_id       = (*_pTo_arg)[0];
   tech_level_id = (*_pTo_arg)[1];
}

void TextureOb :: GrappleEquipmentArgManager(std::vector<int>* _pTo_arg)
{
   race_id       = (*_pTo_arg)[0];
   tech_level_id = (*_pTo_arg)[1];
}

void TextureOb :: BakEquipmentArgManager(std::vector<int>* _pTo_arg)
{
   race_id       = (*_pTo_arg)[0];
   tech_level_id = (*_pTo_arg)[1];
}

void TextureOb :: energyBlockItemArgManager(std::vector<int>* _pTo_arg)
{
   race_id       = (*_pTo_arg)[0];
   tech_level_id = (*_pTo_arg)[1];
}

void TextureOb :: FreezerEquipmentArgManager(std::vector<int>* _pTo_arg)
{
   race_id       = (*_pTo_arg)[0];
   tech_level_id = (*_pTo_arg)[1];
}

void TextureOb :: RadarEquipmentArgManager(std::vector<int>* _pTo_arg)
{
   race_id       = (*_pTo_arg)[0];
   tech_level_id = (*_pTo_arg)[1];
}

void TextureOb :: ScanerEquipmentArgManager(std::vector<int>* _pTo_arg)
{
   race_id       = (*_pTo_arg)[0];
   tech_level_id = (*_pTo_arg)[1];
}


//# BULLETS
void TextureOb :: rocketBulletArgManager(std::vector<int>* _pTo_arg)
{}

void TextureOb :: torpedBulletArgManager(std::vector<int>* _pTo_arg)
{}

void TextureOb :: particleArgManager(std::vector<int>* _pTo_arg)
{
   color_id = (*_pTo_arg)[0];
}

void TextureOb :: distStarArgManager(std::vector<int>* _pTo_arg)
{}

void TextureOb :: lazerEffectArgManager(std::vector<int>* _pTo_arg)
{
   tech_level_id = (*_pTo_arg)[0];
   color_id = (*_pTo_arg)[1];
}

void TextureOb :: shieldEffectArgManager(std::vector<int>* _pTo_arg)
{
   color_id = (*_pTo_arg)[0];
}










TextureManager :: TextureManager()
{}


void TextureManager :: manage(TextureOb* pTo_texOb)
{   
    if (pTo_texOb->type_id == SLOT_TEXTURE_ID)
       slot_texOb_pList.push_back(pTo_texOb);

    if (pTo_texOb->type_id == TURREL_TEXTURE_ID)
       turrel_texOb_pList.push_back(pTo_texOb);

    if (pTo_texOb->type_id == NEBULA_TEXTURE_ID)
       nebulaBgEffect_texOb_pList.push_back(pTo_texOb);

    if (pTo_texOb->type_id == STAR_TEXTURE_ID)
       star_texOb_pList.push_back(pTo_texOb);

    if (pTo_texOb->type_id == PLANET_TEXTURE_ID)
       planet_texOb_pList.push_back(pTo_texOb);

    if (pTo_texOb->type_id == ATMOSPHERE_TEXTURE_ID)
       atmosphere_texOb_pList.push_back(pTo_texOb);

    if (pTo_texOb->type_id == SHIP_TEXTURE_ID)
    { 
        if (pTo_texOb->race_id == RACE_0_ID)
        {
           if (pTo_texOb->subtype_id == RANGER_ID)
              ship_race0_ranger_texOb_pList.push_back(pTo_texOb);
           if (pTo_texOb->subtype_id == WARRIOR_ID)
              ship_race0_warrior_texOb_pList.push_back(pTo_texOb);
           if (pTo_texOb->subtype_id == TRADER_ID)
              ship_race0_trader_texOb_pList.push_back(pTo_texOb);
           if (pTo_texOb->subtype_id == PIRAT_ID)
              ship_race0_pirat_texOb_pList.push_back(pTo_texOb);
           if (pTo_texOb->subtype_id == DIPLOMAT_ID)
              ship_race0_diplomat_texOb_pList.push_back(pTo_texOb);
        }

        if (pTo_texOb->race_id == RACE_1_ID)
        {
           if (pTo_texOb->subtype_id == RANGER_ID)
              ship_race1_ranger_texOb_pList.push_back(pTo_texOb);
           if (pTo_texOb->subtype_id == WARRIOR_ID)
              ship_race1_warrior_texOb_pList.push_back(pTo_texOb);
           if (pTo_texOb->subtype_id == TRADER_ID)
              ship_race1_trader_texOb_pList.push_back(pTo_texOb);
           if (pTo_texOb->subtype_id == PIRAT_ID)
              ship_race1_pirat_texOb_pList.push_back(pTo_texOb);
           if (pTo_texOb->subtype_id == DIPLOMAT_ID)
              ship_race1_diplomat_texOb_pList.push_back(pTo_texOb);
        }

        if (pTo_texOb->race_id == RACE_2_ID)
        {
           if (pTo_texOb->subtype_id == RANGER_ID)
              ship_race2_ranger_texOb_pList.push_back(pTo_texOb);
           if (pTo_texOb->subtype_id == WARRIOR_ID)
              ship_race2_warrior_texOb_pList.push_back(pTo_texOb);
           if (pTo_texOb->subtype_id == TRADER_ID)
              ship_race2_trader_texOb_pList.push_back(pTo_texOb);
           if (pTo_texOb->subtype_id == PIRAT_ID)
              ship_race2_pirat_texOb_pList.push_back(pTo_texOb);
           if (pTo_texOb->subtype_id == DIPLOMAT_ID)
              ship_race2_diplomat_texOb_pList.push_back(pTo_texOb);
        }

        if (pTo_texOb->race_id == RACE_3_ID)
        {
           if (pTo_texOb->subtype_id == RANGER_ID)
              ship_race3_ranger_texOb_pList.push_back(pTo_texOb);
           if (pTo_texOb->subtype_id == WARRIOR_ID)
              ship_race3_warrior_texOb_pList.push_back(pTo_texOb);
           if (pTo_texOb->subtype_id == TRADER_ID)
              ship_race3_trader_texOb_pList.push_back(pTo_texOb);
           if (pTo_texOb->subtype_id == PIRAT_ID)
              ship_race3_pirat_texOb_pList.push_back(pTo_texOb);
           if (pTo_texOb->subtype_id == DIPLOMAT_ID)
              ship_race3_diplomat_texOb_pList.push_back(pTo_texOb);
        }

        if (pTo_texOb->race_id == RACE_4_ID)
        {
           if (pTo_texOb->subtype_id == RANGER_ID)
              ship_race4_ranger_texOb_pList.push_back(pTo_texOb);
           if (pTo_texOb->subtype_id == WARRIOR_ID)
              ship_race4_warrior_texOb_pList.push_back(pTo_texOb);
           if (pTo_texOb->subtype_id == TRADER_ID)
              ship_race4_trader_texOb_pList.push_back(pTo_texOb);
           if (pTo_texOb->subtype_id == PIRAT_ID)
              ship_race4_pirat_texOb_pList.push_back(pTo_texOb);
           if (pTo_texOb->subtype_id == DIPLOMAT_ID)
              ship_race4_diplomat_texOb_pList.push_back(pTo_texOb);
        }

        if (pTo_texOb->race_id == RACE_6_ID)
        {
           if (pTo_texOb->subtype_id == RANGER_ID)
              ship_race6_ranger_texOb_pList.push_back(pTo_texOb);
           if (pTo_texOb->subtype_id == WARRIOR_ID)
              ship_race6_warrior_texOb_pList.push_back(pTo_texOb);
           if (pTo_texOb->subtype_id == TRADER_ID)
              ship_race6_trader_texOb_pList.push_back(pTo_texOb);
           if (pTo_texOb->subtype_id == PIRAT_ID)
              ship_race6_pirat_texOb_pList.push_back(pTo_texOb);
           if (pTo_texOb->subtype_id == DIPLOMAT_ID)
              ship_race6_diplomat_texOb_pList.push_back(pTo_texOb);
        }

        if (pTo_texOb->race_id == RACE_7_ID)
        {
           if (pTo_texOb->subtype_id == RANGER_ID)
              ship_race7_ranger_texOb_pList.push_back(pTo_texOb);
           if (pTo_texOb->subtype_id == WARRIOR_ID)
              ship_race7_warrior_texOb_pList.push_back(pTo_texOb);
           if (pTo_texOb->subtype_id == TRADER_ID)
              ship_race7_trader_texOb_pList.push_back(pTo_texOb);
           if (pTo_texOb->subtype_id == PIRAT_ID)
              ship_race7_pirat_texOb_pList.push_back(pTo_texOb);
           if (pTo_texOb->subtype_id == DIPLOMAT_ID)
              ship_race7_diplomat_texOb_pList.push_back(pTo_texOb);
        }
    }

    if (pTo_texOb->type_id == PARTICLE_TEXTURE_ID)
       particles_texOb_pList.push_back(pTo_texOb);

    if (pTo_texOb->type_id == ROCKET_BULLET_TEXTURE_ID)
       rocketBullet_texOb_pList.push_back(pTo_texOb);

    if (pTo_texOb->type_id == LAZER_EFFECT_TEXTURE_ID)
       lazerEffect_texOb_pList.push_back(pTo_texOb);

    if (pTo_texOb->type_id == SHIELD_EFFECT_TEXTURE_ID)
       shieldEffect_texOb_pList.push_back(pTo_texOb);

    if (pTo_texOb->type_id == DISTANTSTAR_TEXTURE_ID)
       starBgEffect_texOb_pList.push_back(pTo_texOb);

    // ASTEROIDS/MINERALS
    if (pTo_texOb->type_id == ASTEROID_TEXTURE_ID)
     { asteroid_texOb_pList.push_back(pTo_texOb); } 

    if (pTo_texOb->type_id == MINERAL_TEXTURE_ID)
       mineral_texOb_pList.push_back(pTo_texOb); 

    if (pTo_texOb->type_id == CONTAINER_TEXTURE_ID)
       container_texOb_pList.push_back(pTo_texOb); 

    if (pTo_texOb->type_id == BOMB_TEXTURE_ID)
       bomb_texOb_pList.push_back(pTo_texOb); 


    // other
    if (pTo_texOb->type_id == TEXT_BACKGROUND_TEXTURE_ID)
       textBackground_texOb_pList.push_back(pTo_texOb); 



    // LAND
    if (pTo_texOb->type_id == LAND_BG_TEXTURE_ID)
       landBg_texOb_pList.push_back(pTo_texOb);

    //######### IN KOSMOPORT
    if (pTo_texOb->type_id  == ANGAR_BG_TEXTURE_ID)
       angarBg_texOb_pList.push_back(pTo_texOb);

    if (pTo_texOb->type_id == STORE_BG_TEXTURE_ID)
       storeBg_texOb_pList.push_back(pTo_texOb);

    if (pTo_texOb->type_id == SHOP_BG_TEXTURE_ID)
       shopBg_texOb_pList.push_back(pTo_texOb);

    if (pTo_texOb->type_id == GOVERMENT_BG_TEXTURE_ID)
       govermentBg_texOb_pList.push_back(pTo_texOb);
}



void TextureManager :: manageItem(TextureOb* pTo_texOb)
{
    if (pTo_texOb->type_id == ROCKET_ITEM_TEXTURE_ID)
     { RocketEquipment_texOb_pList.push_back(pTo_texOb); } 

    if (pTo_texOb->type_id == LAZER_ITEM_TEXTURE_ID)
     { LazerEquipment_texOb_pList.push_back(pTo_texOb); } 

    if (pTo_texOb->type_id == DRIVE_ITEM_TEXTURE_ID)
       DriveEquipment_texOb_pList.push_back(pTo_texOb); 

    if (pTo_texOb->type_id == PROTECTOR_ITEM_TEXTURE_ID)
       ProtectorEquipment_texOb_pList.push_back(pTo_texOb); 

    if (pTo_texOb->type_id == DROID_ITEM_TEXTURE_ID)
       DroidEquipment_texOb_pList.push_back(pTo_texOb); 

    if (pTo_texOb->type_id == GRAPPLE_ITEM_TEXTURE_ID)
       GrappleEquipment_texOb_pList.push_back(pTo_texOb); 

    if (pTo_texOb->type_id == BAK_ITEM_TEXTURE_ID)
       BakEquipment_texOb_pList.push_back(pTo_texOb); 

    if (pTo_texOb->type_id == ENERGYBLOCK_ITEM_TEXTURE_ID)
       energyBlockItem_texOb_pList.push_back(pTo_texOb); 

    if (pTo_texOb->type_id == FREEZER_ITEM_TEXTURE_ID)
       FreezerEquipment_texOb_pList.push_back(pTo_texOb); 

    if (pTo_texOb->type_id == RADAR_ITEM_TEXTURE_ID)
       RadarEquipment_texOb_pList.push_back(pTo_texOb); 

    if (pTo_texOb->type_id == SCANER_ITEM_TEXTURE_ID)
       ScanerEquipment_texOb_pList.push_back(pTo_texOb); 
}



void TextureManager :: manage_face(TextureOb* pTo_texOb)
{
    if (pTo_texOb->type_id == FACE_TEXTURE_ID)
    {
       if (pTo_texOb->race_id == RACE_0_ID) 
          face_race0_texOb_pList.push_back(pTo_texOb); 
       if (pTo_texOb->race_id == RACE_1_ID) 
          face_race1_texOb_pList.push_back(pTo_texOb); 
       if (pTo_texOb->race_id == RACE_2_ID) 
          face_race2_texOb_pList.push_back(pTo_texOb);  
       if (pTo_texOb->race_id == RACE_3_ID) 
          face_race3_texOb_pList.push_back(pTo_texOb); 
       if (pTo_texOb->race_id == RACE_4_ID) 
          face_race4_texOb_pList.push_back(pTo_texOb); 

       if (pTo_texOb->race_id == RACE_6_ID) 
          face_race6_texOb_pList.push_back(pTo_texOb); 
       if (pTo_texOb->race_id == RACE_7_ID) 
          face_race7_texOb_pList.push_back(pTo_texOb);       
    }
}


TextureOb* TextureManager :: returnPointerToRandomTexObFromList(VEC_pTexOb_type* pTo_list)
{  
     if (pTo_list->size() > 1)
         return (*pTo_list)[randIntInRange(0, pTo_list->size() )];
     else 
         return (*pTo_list)[0];
}

TextureOb* TextureManager :: returnPointerToShipTexObByClosestSizeFromList(VEC_pTexOb_type* pTo_list, int _size_id)
{  
    int size_id = _size_id;
    TextureOb* pTo_texOb;

    size_id -= 1;
    pTo_texOb = returnPointerToShipTexObBySizeFromList(pTo_list, size_id);

    if (pTo_texOb == NULL)
    {
       size_id += 2;
       pTo_texOb = returnPointerToShipTexObBySizeFromList(pTo_list, size_id);
    }
     
    if (pTo_texOb == NULL)
    {
       size_id -= 3;
       pTo_texOb = returnPointerToShipTexObBySizeFromList(pTo_list, size_id);
    }

    if (pTo_texOb == NULL)
    {
       size_id += 4;
       pTo_texOb = returnPointerToShipTexObBySizeFromList(pTo_list, size_id);
    }
   
    if (pTo_texOb == NULL)
    {
       size_id -= 5;
       pTo_texOb = returnPointerToShipTexObBySizeFromList(pTo_list, size_id);
    }

    if (pTo_texOb == NULL)
    {
       size_id += 6;
       pTo_texOb = returnPointerToShipTexObBySizeFromList(pTo_list, size_id);
    }

    if (pTo_texOb == NULL)
    {
       size_id -= 7;
       pTo_texOb = returnPointerToShipTexObBySizeFromList(pTo_list, size_id);
    }

    if (pTo_texOb == NULL)
    {
       size_id += 8;
       pTo_texOb = returnPointerToShipTexObBySizeFromList(pTo_list, size_id);
    }

    return pTo_texOb;
}


TextureOb* TextureManager :: returnPointerToShipTexObBySizeFromList(VEC_pTexOb_type* pTo_list, int _size_id)
{  
    TextureOb* pTo_texOb = NULL;

    if (pTo_list->size() > 1)
    {
        for (unsigned int i = 0; i < pTo_list->size(); i++)
            if ( (*pTo_list)[i]->size_id == _size_id)
                pTo_texOb = (*pTo_list)[i];
    }

    return pTo_texOb;
}


TextureOb* TextureManager :: returnPointerToRandomFaceTexObWithFolloingAttributes(int _race_id)
{
       if (_race_id == RACE_0_ID) 
          return returnPointerToRandomTexObFromList(&face_race0_texOb_pList);

       if (_race_id == RACE_1_ID)
          return returnPointerToRandomTexObFromList(&face_race1_texOb_pList);

       if (_race_id == RACE_2_ID) 
          return returnPointerToRandomTexObFromList(&face_race2_texOb_pList);
 
       if (_race_id == RACE_3_ID) 
          return returnPointerToRandomTexObFromList(&face_race3_texOb_pList);

       if (_race_id == RACE_4_ID) 
          return returnPointerToRandomTexObFromList(&face_race4_texOb_pList);


       if (_race_id == RACE_6_ID)
          return returnPointerToRandomTexObFromList(&face_race6_texOb_pList);

       if (_race_id == RACE_7_ID) 
          return returnPointerToRandomTexObFromList(&face_race7_texOb_pList);
}



TextureOb* TextureManager :: returnPointerToRandomShipTexObWithFollowingAtrributes(int _race_id, int _subtype_id, int _size_id)
{
        TextureOb* pTo_texOb = NULL; 

        if (_race_id == RACE_0_ID)
        {
            if (_subtype_id == RANGER_ID)
            {
               pTo_texOb = returnPointerToRandomTexObFromList(&ship_race0_ranger_texOb_pList);
               return pTo_texOb;
            }
            if (_subtype_id == WARRIOR_ID)
            {
               pTo_texOb = returnPointerToRandomTexObFromList(&ship_race0_warrior_texOb_pList);
               return pTo_texOb;
            }
            if (_subtype_id == TRADER_ID)
            {
               pTo_texOb = returnPointerToRandomTexObFromList(&ship_race0_trader_texOb_pList);
               return pTo_texOb;
            }
            if (_subtype_id == PIRAT_ID)
            {
               pTo_texOb = returnPointerToRandomTexObFromList(&ship_race0_pirat_texOb_pList);
               return pTo_texOb;
            }
            if (_subtype_id == DIPLOMAT_ID)
            {
               pTo_texOb = returnPointerToRandomTexObFromList(&ship_race0_diplomat_texOb_pList);
               return pTo_texOb;
            }
        }

        if (_race_id == RACE_1_ID)
        {
            if (_subtype_id == RANGER_ID)
            {
               pTo_texOb = returnPointerToRandomTexObFromList(&ship_race1_ranger_texOb_pList);
               return pTo_texOb;
            }
            if (_subtype_id == WARRIOR_ID)
            {
               pTo_texOb = returnPointerToRandomTexObFromList(&ship_race1_warrior_texOb_pList);
               return pTo_texOb;
            }
            if (_subtype_id == TRADER_ID)
            {
               pTo_texOb = returnPointerToRandomTexObFromList(&ship_race1_trader_texOb_pList);
               return pTo_texOb;
            }
            if (_subtype_id == PIRAT_ID)
            {
               pTo_texOb = returnPointerToRandomTexObFromList(&ship_race1_pirat_texOb_pList);
               return pTo_texOb;
            }
            if (_subtype_id == DIPLOMAT_ID)
            {
               pTo_texOb = returnPointerToRandomTexObFromList(&ship_race1_diplomat_texOb_pList);
               return pTo_texOb;
            }
        }

        if (_race_id == RACE_2_ID)
        {
            if (_subtype_id == RANGER_ID)
            {
               pTo_texOb = returnPointerToRandomTexObFromList(&ship_race2_ranger_texOb_pList);
               return pTo_texOb;
            }
            if (_subtype_id == WARRIOR_ID)
            {
               pTo_texOb = returnPointerToRandomTexObFromList(&ship_race2_warrior_texOb_pList);
               return pTo_texOb;
            }
            if (_subtype_id == TRADER_ID)
            {
               pTo_texOb = returnPointerToRandomTexObFromList(&ship_race2_trader_texOb_pList);
               return pTo_texOb;
            }
            if (_subtype_id == PIRAT_ID)
            {
               pTo_texOb = returnPointerToRandomTexObFromList(&ship_race2_pirat_texOb_pList);
               return pTo_texOb;
            }
            if (_subtype_id == DIPLOMAT_ID)
            {
               pTo_texOb = returnPointerToRandomTexObFromList(&ship_race2_diplomat_texOb_pList);
               return pTo_texOb;
            }
        }
      

        if (_race_id == RACE_3_ID)
        {
            if (_subtype_id == RANGER_ID)
            {
               pTo_texOb = returnPointerToRandomTexObFromList(&ship_race3_ranger_texOb_pList);
               return pTo_texOb;
            }
            if (_subtype_id == WARRIOR_ID)
            {
               pTo_texOb = returnPointerToRandomTexObFromList(&ship_race3_warrior_texOb_pList);
               return pTo_texOb;
            }
            if (_subtype_id == TRADER_ID)
            {
               pTo_texOb = returnPointerToRandomTexObFromList(&ship_race3_trader_texOb_pList);
               return pTo_texOb;
            }
            if (_subtype_id == PIRAT_ID)
            {
               pTo_texOb = returnPointerToRandomTexObFromList(&ship_race3_pirat_texOb_pList);
               return pTo_texOb;
            }
            if (_subtype_id == DIPLOMAT_ID)
            {
               pTo_texOb = returnPointerToRandomTexObFromList(&ship_race3_diplomat_texOb_pList);
               return pTo_texOb;
            }
        }


        if (_race_id == RACE_4_ID)
        {
            if (_subtype_id == RANGER_ID)
            {
               pTo_texOb = returnPointerToRandomTexObFromList(&ship_race4_ranger_texOb_pList);
               return pTo_texOb;
            }
            if (_subtype_id == WARRIOR_ID)
            {
               pTo_texOb = returnPointerToRandomTexObFromList(&ship_race4_warrior_texOb_pList);
               return pTo_texOb;
            }
            if (_subtype_id == TRADER_ID)
            {
               pTo_texOb = returnPointerToRandomTexObFromList(&ship_race4_trader_texOb_pList);
               return pTo_texOb;
            }
            if (_subtype_id == PIRAT_ID)
            {
               pTo_texOb = returnPointerToRandomTexObFromList(&ship_race4_pirat_texOb_pList);
               return pTo_texOb;
            }
            if (_subtype_id == DIPLOMAT_ID)
            {
               pTo_texOb = returnPointerToRandomTexObFromList(&ship_race4_diplomat_texOb_pList);
               return pTo_texOb;
            }
        }




        if (_race_id == RACE_6_ID)
        {
            if (_subtype_id == RANGER_ID)
            {
               pTo_texOb = returnPointerToRandomTexObFromList(&ship_race6_ranger_texOb_pList);
               return pTo_texOb;
            }
            if (_subtype_id == WARRIOR_ID)
            {
               pTo_texOb = returnPointerToRandomTexObFromList(&ship_race6_warrior_texOb_pList);
               return pTo_texOb;
            }
            if (_subtype_id == TRADER_ID)
            {
               pTo_texOb = returnPointerToRandomTexObFromList(&ship_race6_trader_texOb_pList);
               return pTo_texOb;
            }
            if (_subtype_id == PIRAT_ID)
            {
               pTo_texOb = returnPointerToRandomTexObFromList(&ship_race6_pirat_texOb_pList);
               return pTo_texOb;
            }
            if (_subtype_id == DIPLOMAT_ID)
            {
               pTo_texOb = returnPointerToRandomTexObFromList(&ship_race6_diplomat_texOb_pList);
               return pTo_texOb;
            }
        }


        if (_race_id == RACE_7_ID)
        {
            if (_subtype_id == RANGER_ID)
            {
               pTo_texOb = returnPointerToRandomTexObFromList(&ship_race7_ranger_texOb_pList);
               return pTo_texOb;
            }
            if (_subtype_id == WARRIOR_ID)
            {
               pTo_texOb = returnPointerToRandomTexObFromList(&ship_race7_warrior_texOb_pList);
               return pTo_texOb;
            }
            if (_subtype_id == TRADER_ID)
            {
               pTo_texOb = returnPointerToRandomTexObFromList(&ship_race7_trader_texOb_pList);
               return pTo_texOb;
            }
            if (_subtype_id == PIRAT_ID)
            {
               pTo_texOb = returnPointerToRandomTexObFromList(&ship_race7_pirat_texOb_pList);
               return pTo_texOb;
            }
            if (_subtype_id == DIPLOMAT_ID)
            {
               pTo_texOb = returnPointerToRandomTexObFromList(&ship_race7_diplomat_texOb_pList);
               return pTo_texOb;
            }
        }
       
         return NULL;

}





TextureOb* TextureManager :: returnParticleTexObByColorId(int _color_id)
{
	printf("searching color id = %i\n", _color_id);
     	for(unsigned int i = 0; i < particles_texOb_pList.size(); i++)
     	{
            	printf("current color id = %i\n", particles_texOb_pList[i]->color_id);  
         	if (particles_texOb_pList[i]->color_id == _color_id)
            		return particles_texOb_pList[i]; 
        
	}
	
     	printf("Particle with requested color is absent\n"); 
     	return NULL;
}





      //def loadAllTexturesInStarSystem(self, starsystem):
          //for n in starsystem.NEBULA_static_effect_list:
              //n.texOb.loadToVRAM()
              //n.linkTexture()

          //for n in starsystem.NEBULA_rotated_effect_list:
              //n.texOb.loadToVRAM()
              //n.linkTexture()

          //for s in starsystem.STAR_list:
              //s.texOb.loadToVRAM()
              //s.linkTexture()

          //for p in starsystem.PLANET_list:
              //p.texOb.loadToVRAM()
              //p.linkTexture()











void TextureManager :: DEBUG_CheckShipTexOb()
{
     if (ship_race0_ranger_texOb_pList.size() == 0)
        printf("ship_race0_ranger_texOb_pList.size() = 0\n"); 
     if (ship_race0_warrior_texOb_pList.size() == 0)
        printf("ship_race0_warrior_texOb_pList.size() = 0\n"); 
     if (ship_race0_trader_texOb_pList.size() == 0)
        printf("ship_race0_trader_texOb_pList.size() = 0\n"); 
     if (ship_race0_pirat_texOb_pList.size() == 0)
        printf("ship_race0_pirat_texOb_pList.size() = 0\n"); 
     if (ship_race0_diplomat_texOb_pList.size() == 0)
        printf("ship_race0_diplomat_texOb_pList.size() = 0\n"); 

     if (ship_race1_ranger_texOb_pList.size() == 0)
        printf("ship_race1_ranger_texOb_pList.size() = 0\n"); 
     if (ship_race1_warrior_texOb_pList.size() == 0)
        printf("ship_race1_warrior_texOb_pList.size() = 0\n"); 
     if (ship_race1_trader_texOb_pList.size() == 0)
        printf("ship_race1_trader_texOb_pList.size() = 0\n"); 
     if (ship_race1_pirat_texOb_pList.size() == 0)
        printf("ship_race1_pirat_texOb_pList.size() = 0\n"); 
     if (ship_race1_diplomat_texOb_pList.size() == 0)
        printf("ship_race1_diplomat_texOb_pList.size() = 0\n"); 

     if (ship_race2_ranger_texOb_pList.size() == 0)
        printf("ship_race2_ranger_texOb_pList.size() = 0\n"); 
     if (ship_race2_warrior_texOb_pList.size() == 0)
        printf("ship_race2_warrior_texOb_pList.size() = 0\n"); 
     if (ship_race2_trader_texOb_pList.size() == 0)
        printf("ship_race2_trader_texOb_pList.size() = 0\n"); 
     if (ship_race2_pirat_texOb_pList.size() == 0)
        printf("ship_race2_pirat_texOb_pList.size() = 0\n"); 
     if (ship_race2_diplomat_texOb_pList.size() == 0)
        printf("ship_race2_diplomat_texOb_pList.size() = 0\n"); 
     

     if (ship_race3_ranger_texOb_pList.size() == 0)
        printf("ship_race3_ranger_texOb_pList.size() = 0\n"); 
     if (ship_race3_warrior_texOb_pList.size() == 0)
        printf("ship_race3_warrior_texOb_pList.size() = 0\n"); 
     if (ship_race3_trader_texOb_pList.size() == 0)
        printf("ship_race3_trader_texOb_pList.size() = 0\n"); 
     if (ship_race3_pirat_texOb_pList.size() == 0)
        printf("ship_race3_pirat_texOb_pList.size() = 0\n"); 
     if (ship_race3_diplomat_texOb_pList.size() == 0)
        printf("ship_race3_diplomat_texOb_pList.size() = 0\n"); 

     if (ship_race4_ranger_texOb_pList.size() == 0)
        printf("ship_race4_ranger_texOb_pList.size() = 0\n"); 
     if (ship_race4_warrior_texOb_pList.size() == 0)
        printf("ship_race4_warrior_texOb_pList.size() = 0\n"); 
     if (ship_race4_trader_texOb_pList.size() == 0)
        printf("ship_race4_trader_texOb_pList.size() = 0\n"); 
     if (ship_race4_pirat_texOb_pList.size() == 0)
        printf("ship_race4_pirat_texOb_pList.size() = 0\n"); 
     if (ship_race4_diplomat_texOb_pList.size() == 0)
        printf("ship_race4_diplomat_texOb_pList.size() = 0\n"); 

     if (ship_race6_ranger_texOb_pList.size() == 0)
        printf("ship_race6_ranger_texOb_pList.size() = 0\n"); 
     if (ship_race6_warrior_texOb_pList.size() == 0)
        printf("ship_race6_warrior_texOb_pList.size() = 0\n"); 
     if (ship_race6_trader_texOb_pList.size() == 0)
        printf("ship_race6_trader_texOb_pList.size() = 0\n"); 
     if (ship_race6_pirat_texOb_pList.size() == 0)
        printf("ship_race6_pirat_texOb_pList.size() = 0\n"); 
     if (ship_race6_diplomat_texOb_pList.size() == 0)
        printf("ship_race6_diplomat_texOb_pList.size() = 0\n"); 


     if (ship_race7_ranger_texOb_pList.size() == 0)
        printf("ship_race7_ranger_texOb_pList.size() = 0\n"); 
     if (ship_race7_warrior_texOb_pList.size() == 0)
        printf("ship_race7_warrior_texOb_pList.size() = 0\n"); 
     if (ship_race7_trader_texOb_pList.size() == 0)
        printf("ship_race7_trader_texOb_pList.size() = 0\n"); 
     if (ship_race7_pirat_texOb_pList.size() == 0)
        printf("ship_race7_pirat_texOb_pList.size() = 0\n"); 
     if (ship_race7_diplomat_texOb_pList.size() == 0)
        printf("ship_race7_diplomat_texOb_pList.size() = 0\n"); 
}


