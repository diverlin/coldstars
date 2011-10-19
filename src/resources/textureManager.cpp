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


#include "textureManager.hpp"


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
         return (*pTo_list)[getRandInt(0, pTo_list->size() )];
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
        TextureOb* _texOb; 

        if (_race_id == RACE_0_ID)
        {
                if (_subtype_id == RANGER_ID)
                {
                        _texOb = returnPointerToRandomTexObFromList(&ship_race0_ranger_texOb_pList);
                        return _texOb;
                }
                if (_subtype_id == WARRIOR_ID)
                {
                        _texOb = returnPointerToRandomTexObFromList(&ship_race0_warrior_texOb_pList);
                        return _texOb;
                }
                if (_subtype_id == TRADER_ID)
                {
                        _texOb = returnPointerToRandomTexObFromList(&ship_race0_trader_texOb_pList);
                        return _texOb;
                }
                if (_subtype_id == PIRAT_ID)
                {
                        _texOb = returnPointerToRandomTexObFromList(&ship_race0_pirat_texOb_pList);
                        return _texOb;
                }
                if (_subtype_id == DIPLOMAT_ID)
                {
                        _texOb = returnPointerToRandomTexObFromList(&ship_race0_diplomat_texOb_pList);
                        return _texOb;
                }
        }

        if (_race_id == RACE_1_ID)
        {
                if (_subtype_id == RANGER_ID)
                {
                        _texOb = returnPointerToRandomTexObFromList(&ship_race1_ranger_texOb_pList);
                        return _texOb;
                }
                if (_subtype_id == WARRIOR_ID)
                {
                        _texOb = returnPointerToRandomTexObFromList(&ship_race1_warrior_texOb_pList);
                        return _texOb;
                }
                if (_subtype_id == TRADER_ID)
                {
                        _texOb = returnPointerToRandomTexObFromList(&ship_race1_trader_texOb_pList);
                        return _texOb;
                }
                if (_subtype_id == PIRAT_ID)
                {
                        _texOb = returnPointerToRandomTexObFromList(&ship_race1_pirat_texOb_pList);
                        return _texOb;
                }
                if (_subtype_id == DIPLOMAT_ID)
                {
                        _texOb = returnPointerToRandomTexObFromList(&ship_race1_diplomat_texOb_pList);
                        return _texOb;
                }
        }

        if (_race_id == RACE_2_ID)
        {
                if (_subtype_id == RANGER_ID)
                {
                        _texOb = returnPointerToRandomTexObFromList(&ship_race2_ranger_texOb_pList);
                        return _texOb;
                }
                if (_subtype_id == WARRIOR_ID)
                {
                        _texOb = returnPointerToRandomTexObFromList(&ship_race2_warrior_texOb_pList);
                        return _texOb;
                }
                if (_subtype_id == TRADER_ID)
                {
                        _texOb = returnPointerToRandomTexObFromList(&ship_race2_trader_texOb_pList);
                        return _texOb;
                }
                if (_subtype_id == PIRAT_ID)
                {
                        _texOb = returnPointerToRandomTexObFromList(&ship_race2_pirat_texOb_pList);
                        return _texOb;
                }
                if (_subtype_id == DIPLOMAT_ID)
                {
                        _texOb = returnPointerToRandomTexObFromList(&ship_race2_diplomat_texOb_pList);
                        return _texOb;
                }
        }
      

        if (_race_id == RACE_3_ID)
        {
                if (_subtype_id == RANGER_ID)
                {
                        _texOb = returnPointerToRandomTexObFromList(&ship_race3_ranger_texOb_pList);
                        return _texOb;
                }
                if (_subtype_id == WARRIOR_ID)
                {
                        _texOb = returnPointerToRandomTexObFromList(&ship_race3_warrior_texOb_pList);
                        return _texOb;
                }
                if (_subtype_id == TRADER_ID)
                {
                        _texOb = returnPointerToRandomTexObFromList(&ship_race3_trader_texOb_pList);
                        return _texOb;
                }
                if (_subtype_id == PIRAT_ID)
                {
                        _texOb = returnPointerToRandomTexObFromList(&ship_race3_pirat_texOb_pList);
                        return _texOb;
                }
                if (_subtype_id == DIPLOMAT_ID)
                {
                        _texOb = returnPointerToRandomTexObFromList(&ship_race3_diplomat_texOb_pList);
                        return _texOb;
                }
        }


        if (_race_id == RACE_4_ID)
        {
                if (_subtype_id == RANGER_ID)
                {
                        _texOb = returnPointerToRandomTexObFromList(&ship_race4_ranger_texOb_pList);
                        return _texOb;
                }
                if (_subtype_id == WARRIOR_ID)
                {
                        _texOb = returnPointerToRandomTexObFromList(&ship_race4_warrior_texOb_pList);
                        return _texOb;
                }
                if (_subtype_id == TRADER_ID)
                {
                        _texOb = returnPointerToRandomTexObFromList(&ship_race4_trader_texOb_pList);
                        return _texOb;
                }   
                if (_subtype_id == PIRAT_ID)
                {
                        _texOb = returnPointerToRandomTexObFromList(&ship_race4_pirat_texOb_pList);
                        return _texOb;
                }
                if (_subtype_id == DIPLOMAT_ID)
                {
                        _texOb = returnPointerToRandomTexObFromList(&ship_race4_diplomat_texOb_pList);
                        return _texOb;
                }
        }




        if (_race_id == RACE_6_ID)
        {
                if (_subtype_id == RANGER_ID)
                {
                        _texOb = returnPointerToRandomTexObFromList(&ship_race6_ranger_texOb_pList);
                        return _texOb;
                }
                if (_subtype_id == WARRIOR_ID)
                {
                        _texOb = returnPointerToRandomTexObFromList(&ship_race6_warrior_texOb_pList);
                        return _texOb;
                }
                if (_subtype_id == TRADER_ID)
                {
                        _texOb = returnPointerToRandomTexObFromList(&ship_race6_trader_texOb_pList);
                        return _texOb;
                }
                if (_subtype_id == PIRAT_ID)
                {
                        _texOb = returnPointerToRandomTexObFromList(&ship_race6_pirat_texOb_pList);
                        return _texOb;
                }
                if (_subtype_id == DIPLOMAT_ID)
                {
                        _texOb = returnPointerToRandomTexObFromList(&ship_race6_diplomat_texOb_pList);
                        return _texOb;
                }
        }


        if (_race_id == RACE_7_ID)
        {
                if (_subtype_id == RANGER_ID)
                {
                        _texOb = returnPointerToRandomTexObFromList(&ship_race7_ranger_texOb_pList);
                        return _texOb;
                }
                if (_subtype_id == WARRIOR_ID)
                {
                        _texOb = returnPointerToRandomTexObFromList(&ship_race7_warrior_texOb_pList);
                        return _texOb;
                }
                if (_subtype_id == TRADER_ID)
                {
                        _texOb = returnPointerToRandomTexObFromList(&ship_race7_trader_texOb_pList);
                        return _texOb;
                }
                if (_subtype_id == PIRAT_ID)
                {
                        _texOb = returnPointerToRandomTexObFromList(&ship_race7_pirat_texOb_pList);
                        return _texOb;
                }
                if (_subtype_id == DIPLOMAT_ID)
                {
                        _texOb = returnPointerToRandomTexObFromList(&ship_race7_diplomat_texOb_pList);
                        return _texOb;
                }
        }
       
        return NULL;

}





TextureOb* TextureManager :: returnParticleTexObByColorId(int _color_id)
{
	//printf("searching color id = %i\n", _color_id);
     	for(unsigned int i = 0; i < particles_texOb_pList.size(); i++)
     	{
            	//printf("current color id = %i\n", particles_texOb_pList[i]->color_id);  
         	if (particles_texOb_pList[i]->color_id == _color_id)
            		return particles_texOb_pList[i]; 
        
	}
	
     	//printf("Particle with requested color is absent\n"); 
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


