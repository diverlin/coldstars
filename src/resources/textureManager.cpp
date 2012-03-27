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


TextureManager :: TextureManager()
{}

TextureManager :: ~TextureManager()
{}

void TextureManager :: manage(TextureOb* texOb)
{
	switch(texOb->type_id)
	{
	  	case TEXTURE::SPACESTATION_ID: { spacestation_texOb_vec.push_back(texOb);    break; }       
	 	case TEXTURE::SATELLITE_ID:    { satellite_texOb_vec.push_back(texOb);   break; }       
	  		  		
  		case TEXTURE::SLOT_ID:        { slot_texOb_vec.push_back(texOb);        break; }       
    		case TEXTURE::LANDINGAREA_ID: { landingArea_texOb_vec.push_back(texOb); break; }
       		case TEXTURE::TURREL_ID:      { turrel_texOb_vec.push_back(texOb);      break; }

    		case TEXTURE::NEBULA_BACKGROUND_ID:      { nebulaBgEffect_texOb_vec.push_back(texOb); break; }
    		case TEXTURE::STAR_ID:        { star_texOb_vec.push_back(texOb);           break; } 
		case TEXTURE::PLANET_ID:      { planet_texOb_vec.push_back(texOb);         break; }
		case TEXTURE::ATMOSPHERE_ID:  { atmosphere_texOb_vec.push_back(texOb);     break; }
		case TEXTURE::SHIP_ID:        
		{  
			switch(texOb->race_id) 
			{
        			case RACE::R0_ID:
        			{
        				switch(texOb->subtype_id)
        				{
        					case CLASS::RANGER_ID:   { ship_race0_ranger_texOb_vec.push_back(texOb);   break; }
        					case CLASS::WARRIOR_ID:  { ship_race0_warrior_texOb_vec.push_back(texOb);  break; }
           					case CLASS::TRADER_ID:   { ship_race0_trader_texOb_vec.push_back(texOb);   break; }
           					case CLASS::PIRAT_ID:    { ship_race0_pirat_texOb_vec.push_back(texOb);    break; }
           					case CLASS::DIPLOMAT_ID: { ship_race0_diplomat_texOb_vec.push_back(texOb); break; }
        				}
        				
        				break;
        			}
        			

        			case RACE::R1_ID:
        			{
        			         switch(texOb->subtype_id)
        			         {
        			         	case CLASS::RANGER_ID:   { ship_race1_ranger_texOb_vec.push_back(texOb);   break; }
           					case CLASS::WARRIOR_ID:  { ship_race1_warrior_texOb_vec.push_back(texOb);  break; }
           					case CLASS::TRADER_ID:   { ship_race1_trader_texOb_vec.push_back(texOb);   break; }
           					case CLASS::PIRAT_ID:    { ship_race1_pirat_texOb_vec.push_back(texOb);    break; }
           					case CLASS::DIPLOMAT_ID: { ship_race1_diplomat_texOb_vec.push_back(texOb); break; }
        				 }
        				 
        				 break;
        			}

        			case RACE::R2_ID:
        			{
        			         switch(texOb->subtype_id)
        			         {
        			         	case CLASS::RANGER_ID: { ship_race2_ranger_texOb_vec.push_back(texOb); break; }
           					case CLASS::WARRIOR_ID: { ship_race2_warrior_texOb_vec.push_back(texOb); break; }
           					case CLASS::TRADER_ID: { ship_race2_trader_texOb_vec.push_back(texOb); break; }
           					case CLASS::PIRAT_ID:  { ship_race2_pirat_texOb_vec.push_back(texOb);  break; }
           					case CLASS::DIPLOMAT_ID: { ship_race2_diplomat_texOb_vec.push_back(texOb); break; }
        				 }
        				 
        				 break;
        			}
        			
        			
				case RACE::R3_ID:
				{
					switch(texOb->subtype_id)
					{
						case CLASS::RANGER_ID:  { ship_race3_ranger_texOb_vec.push_back(texOb);    break; }
           					case CLASS::WARRIOR_ID: { ship_race3_warrior_texOb_vec.push_back(texOb);   break; }
           					case CLASS::TRADER_ID:  { ship_race3_trader_texOb_vec.push_back(texOb);    break; }
           					case CLASS::PIRAT_ID:   { ship_race3_pirat_texOb_vec.push_back(texOb);     break; }
           					case CLASS::DIPLOMAT_ID: { ship_race3_diplomat_texOb_vec.push_back(texOb); break; }
        				}
        				
        				break;
        			}

        			case RACE::R4_ID:
        			{
        				switch(texOb->subtype_id)
        				{	
        					case CLASS::RANGER_ID:   { ship_race4_ranger_texOb_vec.push_back(texOb);   break; }
           					case CLASS::WARRIOR_ID:  { ship_race4_warrior_texOb_vec.push_back(texOb);  break; }
           					case CLASS::TRADER_ID:   { ship_race4_trader_texOb_vec.push_back(texOb);   break; }
           					case CLASS::PIRAT_ID:    { ship_race4_pirat_texOb_vec.push_back(texOb);    break; } 
           					case CLASS::DIPLOMAT_ID: { ship_race4_diplomat_texOb_vec.push_back(texOb); break; }
           				}
           				
           				break;
           			}
			
				case RACE::R6_ID:
				{	
					switch(texOb->subtype_id)
					{
						case CLASS::RANGER_ID:   { ship_race6_ranger_texOb_vec.push_back(texOb);   break; }
           					case CLASS::WARRIOR_ID:  { ship_race6_warrior_texOb_vec.push_back(texOb);  break; }
           					case CLASS::TRADER_ID:   { ship_race6_trader_texOb_vec.push_back(texOb);   break; }
           					case CLASS::PIRAT_ID:    { ship_race6_pirat_texOb_vec.push_back(texOb);    break; }
           					case CLASS::DIPLOMAT_ID: { ship_race6_diplomat_texOb_vec.push_back(texOb); break; }
        				}
        				
        				break;
        			}

				case RACE::R7_ID:
				{	
					switch(texOb->subtype_id)
					{
						case CLASS::RANGER_ID:   { ship_race7_ranger_texOb_vec.push_back(texOb);   break; }
           					case CLASS::WARRIOR_ID:  { ship_race7_warrior_texOb_vec.push_back(texOb);  break; }
           					case CLASS::TRADER_ID:   { ship_race7_trader_texOb_vec.push_back(texOb);   break; }
           					case CLASS::PIRAT_ID:    { ship_race7_pirat_texOb_vec.push_back(texOb);    break; }
           					case CLASS::DIPLOMAT_ID: { ship_race7_diplomat_texOb_vec.push_back(texOb); break; }
        				}
        				
        				break;
        			}
    			}
    		break;
    		}
    		
		case TEXTURE::ROCKET_BULLET_ID: { rocketBullet_texOb_vec.push_back(texOb); break; }
		case TEXTURE::LAZER_EFFECT_ID:  { lazerEffect_texOb_vec.push_back(texOb);  break; }
		case TEXTURE::SHIELD_EFFECT_ID: { shieldEffect_texOb_vec.push_back(texOb); break; }
		case TEXTURE::DISTANTSTAR_ID:   { starBgEffect_texOb_vec.push_back(texOb); break; }
                case TEXTURE::PARTICLE_EFFECT_ID:      { particles_texOb_vec.push_back(texOb); break; } 

    		// ASTEROIDS/MINERALS
    		case TEXTURE::ASTEROID_ID:  { asteroid_texOb_vec.push_back(texOb);  break; } 
		case TEXTURE::MINERAL_ID:   { mineral_texOb_vec.push_back(texOb);   break; } 
		case TEXTURE::CONTAINER_ID: { container_texOb_vec.push_back(texOb); break; }
		case TEXTURE::BOMB_ID:      { bomb_texOb_vec.push_back(texOb);      break; }

    		case TEXTURE::BLACKHOLE_ID: { blackhole_texOb_vec.push_back(texOb); break; }
       		case TEXTURE::TEXT_BACKGROUND_ID: { textBackground_texOb_vec.push_back(texOb); break; } 

		// LAND
    		case TEXTURE::LAND_BACKGROUND_ID: { landBg_texOb_vec.push_back(texOb); break; }

		// IN KOSMOPORT
    		case TEXTURE::ANGAR_BACKGROUND_ID: { angarBg_texOb_vec.push_back(texOb); break; }
		case TEXTURE::STORE_BACKGROUND_ID: { storeBg_texOb_vec.push_back(texOb); break; }
		case TEXTURE::SHOP_BACKGROUND_ID:  { shopBg_texOb_vec.push_back(texOb); break; }
		case TEXTURE::GOVERMENT_BACKGROUND_ID: { govermentBg_texOb_vec.push_back(texOb); break; }
		
		
		// ITEMS
		case TEXTURE::ROCKET_EQUIPMENT_ID:      { rocketEquipment_texOb_vec.push_back(texOb);      break; } 
		case TEXTURE::LAZER_EQUIPMENT_ID:       { lazerEquipment_texOb_vec.push_back(texOb);       break; } 
		case TEXTURE::DRIVE_EQUIPMENT_ID:       { driveEquipment_texOb_vec.push_back(texOb);       break; } 
		case TEXTURE::PROTECTOR_EQUIPMENT_ID:   { protectorEquipment_texOb_vec.push_back(texOb);   break; } 
		case TEXTURE::DROID_EQUIPMENT_ID:       { droidEquipment_texOb_vec.push_back(texOb);       break; } 
		case TEXTURE::GRAPPLE_EQUIPMENT_ID:     { grappleEquipment_texOb_vec.push_back(texOb);     break; } 
		case TEXTURE::BAK_EQUIPMENT_ID:         { bakEquipment_texOb_vec.push_back(texOb);         break; } 
		case TEXTURE::ENERGIZER_EQUIPMENT_ID: { energyBlockEquipment_texOb_vec.push_back(texOb); break; } 
		case TEXTURE::FREEZER_EQUIPMENT_ID:     { freezerEquipment_texOb_vec.push_back(texOb);     break; } 
		case TEXTURE::RADAR_EQUIPMENT_ID:       { radarEquipment_texOb_vec.push_back(texOb);       break; } 
		case TEXTURE::SCANER_EQUIPMENT_ID:      { scanerEquipment_texOb_vec.push_back(texOb);      break; } 
		
		case TEXTURE::FACE_ID:
		{
			switch(texOb->race_id)
			{
			       	case RACE::R0_ID: { face_race0_texOb_vec.push_back(texOb); break; } 
       				case RACE::R1_ID: { face_race1_texOb_vec.push_back(texOb); break; } 
       				case RACE::R2_ID: { face_race2_texOb_vec.push_back(texOb); break; } 
       				case RACE::R3_ID: { face_race3_texOb_vec.push_back(texOb); break; } 
       				case RACE::R4_ID: { face_race4_texOb_vec.push_back(texOb); break; } 

       				case RACE::R6_ID: { face_race6_texOb_vec.push_back(texOb); break; } 
       				case RACE::R7_ID: { face_race7_texOb_vec.push_back(texOb); break; }   
			}
			break;
		}
	}
}



TextureOb* TextureManager :: getRandomTexObFromList(std::vector<TextureOb*>* pTo_list)
{  
     if (pTo_list->size() > 1)
         return (*pTo_list)[getRandInt(0, pTo_list->size() )];
     else 
         return (*pTo_list)[0];
}

TextureOb* TextureManager :: getShipTexObByClosestSizeFromList(std::vector<TextureOb*>* pTo_list, int _size_id)
{  
    int size_id = _size_id;
    TextureOb* texOb;

    size_id -= 1;
    texOb = getShipTexObBySizeFromList(pTo_list, size_id);

    if (texOb == NULL)
    {
       size_id += 2;
       texOb = getShipTexObBySizeFromList(pTo_list, size_id);
    }
     
    if (texOb == NULL)
    {
       size_id -= 3;
       texOb = getShipTexObBySizeFromList(pTo_list, size_id);
    }

    if (texOb == NULL)
    {
       size_id += 4;
       texOb = getShipTexObBySizeFromList(pTo_list, size_id);
    }
   
    if (texOb == NULL)
    {
       size_id -= 5;
       texOb = getShipTexObBySizeFromList(pTo_list, size_id);
    }

    if (texOb == NULL)
    {
       size_id += 6;
       texOb = getShipTexObBySizeFromList(pTo_list, size_id);
    }

    if (texOb == NULL)
    {
       size_id -= 7;
       texOb = getShipTexObBySizeFromList(pTo_list, size_id);
    }

    if (texOb == NULL)
    {
       size_id += 8;
       texOb = getShipTexObBySizeFromList(pTo_list, size_id);
    }

    return texOb;
}


TextureOb* TextureManager :: getShipTexObBySizeFromList(std::vector<TextureOb*>* pTo_list, int _size_id)
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


TextureOb* TextureManager :: getRandomFaceTexObWithFolloingAttributes(int _race_id)
{
	switch(_race_id)
	{
		case RACE::R0_ID: { return getRandomTexObFromList(&face_race0_texOb_vec); }
		case RACE::R1_ID: { return getRandomTexObFromList(&face_race1_texOb_vec); }
		case RACE::R2_ID: { return getRandomTexObFromList(&face_race2_texOb_vec); }
 		case RACE::R3_ID: { return getRandomTexObFromList(&face_race3_texOb_vec); }
		case RACE::R4_ID: { return getRandomTexObFromList(&face_race4_texOb_vec); }
		
		case RACE::R6_ID: { return getRandomTexObFromList(&face_race6_texOb_vec); }
		case RACE::R7_ID: { return getRandomTexObFromList(&face_race7_texOb_vec); }
	}
	
	return NULL;
}



TextureOb* TextureManager :: getRandomShipTexObWithFollowingAtrributes(int _race_id, int _subtype_id, int _size_id)
{
        switch(_race_id)
        {	
        	case RACE::R0_ID:
        	{
                	switch(_subtype_id)
                	{
                		case CLASS::RANGER_ID:   { return getRandomTexObFromList(&ship_race0_ranger_texOb_vec);   break; }
				case CLASS::WARRIOR_ID:  { return getRandomTexObFromList(&ship_race0_warrior_texOb_vec);  break; }
 				case CLASS::TRADER_ID:   { return getRandomTexObFromList(&ship_race0_trader_texOb_vec);   break; }
				case CLASS::PIRAT_ID:    { return getRandomTexObFromList(&ship_race0_pirat_texOb_vec);    break; }
				case CLASS::DIPLOMAT_ID: { return getRandomTexObFromList(&ship_race0_diplomat_texOb_vec); break; }
		       }
		       
		       break;
		}

        	case RACE::R1_ID:
        	{
                	switch(_subtype_id)
                	{	
                		case CLASS::RANGER_ID:   { return getRandomTexObFromList(&ship_race1_ranger_texOb_vec);   break; }
				case CLASS::WARRIOR_ID:  { return getRandomTexObFromList(&ship_race1_warrior_texOb_vec);  break; } 
				case CLASS::TRADER_ID:   { return getRandomTexObFromList(&ship_race1_trader_texOb_vec);   break; }
				case CLASS::PIRAT_ID:    { return getRandomTexObFromList(&ship_race1_pirat_texOb_vec);    break; }
				case CLASS::DIPLOMAT_ID: { return getRandomTexObFromList(&ship_race1_diplomat_texOb_vec); break; }
			}
			
			break;
		}
		
	        case RACE::R2_ID:
        	{
                	switch(_subtype_id)
                	{	
                		case CLASS::RANGER_ID:   { return getRandomTexObFromList(&ship_race2_ranger_texOb_vec);   break; }
				case CLASS::WARRIOR_ID:  { return getRandomTexObFromList(&ship_race2_warrior_texOb_vec);  break; } 
				case CLASS::TRADER_ID:   { return getRandomTexObFromList(&ship_race2_trader_texOb_vec);   break; }
				case CLASS::PIRAT_ID:    { return getRandomTexObFromList(&ship_race2_pirat_texOb_vec);    break; }
				case CLASS::DIPLOMAT_ID: { return getRandomTexObFromList(&ship_race2_diplomat_texOb_vec); break; }
			}
			
			break;
        	}
      

    	        case RACE::R3_ID:
        	{
                	switch(_subtype_id)
                	{	
                		case CLASS::RANGER_ID:   { return getRandomTexObFromList(&ship_race3_ranger_texOb_vec);   break; }
				case CLASS::WARRIOR_ID:  { return getRandomTexObFromList(&ship_race3_warrior_texOb_vec);  break; } 
				case CLASS::TRADER_ID:   { return getRandomTexObFromList(&ship_race3_trader_texOb_vec);   break; }
				case CLASS::PIRAT_ID:    { return getRandomTexObFromList(&ship_race3_pirat_texOb_vec);    break; }
				case CLASS::DIPLOMAT_ID: { return getRandomTexObFromList(&ship_race3_diplomat_texOb_vec); break; }
			}
			
			break;
        	}


    	        case RACE::R4_ID:
        	{
                	switch(_subtype_id)
                	{	
                		case CLASS::RANGER_ID:   { return getRandomTexObFromList(&ship_race4_ranger_texOb_vec);   break; }
				case CLASS::WARRIOR_ID:  { return getRandomTexObFromList(&ship_race4_warrior_texOb_vec);  break; } 
				case CLASS::TRADER_ID:   { return getRandomTexObFromList(&ship_race4_trader_texOb_vec);   break; }
				case CLASS::PIRAT_ID:    { return getRandomTexObFromList(&ship_race4_pirat_texOb_vec);    break; }
				case CLASS::DIPLOMAT_ID: { return getRandomTexObFromList(&ship_race4_diplomat_texOb_vec); break; }
			}
			
			break;
        	}


	        case RACE::R6_ID:
        	{
                	switch(_subtype_id)
                	{	
                		case CLASS::RANGER_ID:   { return getRandomTexObFromList(&ship_race6_ranger_texOb_vec);   break; }
				case CLASS::WARRIOR_ID:  { return getRandomTexObFromList(&ship_race6_warrior_texOb_vec);  break; } 
				case CLASS::TRADER_ID:   { return getRandomTexObFromList(&ship_race6_trader_texOb_vec);   break; }
				case CLASS::PIRAT_ID:    { return getRandomTexObFromList(&ship_race6_pirat_texOb_vec);    break; }
				case CLASS::DIPLOMAT_ID: { return getRandomTexObFromList(&ship_race6_diplomat_texOb_vec); break; }
			}
			
			break;
        	}

       	        case RACE::R7_ID:
        	{
                	switch(_subtype_id)
                	{	
                		case CLASS::RANGER_ID:   { return getRandomTexObFromList(&ship_race7_ranger_texOb_vec);   break; }
				case CLASS::WARRIOR_ID:  { return getRandomTexObFromList(&ship_race7_warrior_texOb_vec);  break; } 
				case CLASS::TRADER_ID:   { return getRandomTexObFromList(&ship_race7_trader_texOb_vec);   break; }
				case CLASS::PIRAT_ID:    { return getRandomTexObFromList(&ship_race7_pirat_texOb_vec);    break; }
				case CLASS::DIPLOMAT_ID: { return getRandomTexObFromList(&ship_race7_diplomat_texOb_vec); break; }
			}
			
			break;
        	}
        }
       
        return NULL;

}





TextureOb* TextureManager :: getTexObByColorId(int _type_id, int _color_id)
{
	std::vector<TextureOb*>* requested_vec = NULL;
	
	switch(_type_id)
	{
		case TEXTURE::PARTICLE_EFFECT_ID:    { requested_vec = &particles_texOb_vec;      break; }
		case TEXTURE::DISTANTSTAR_ID: { requested_vec = &starBgEffect_texOb_vec;   break; }
		case TEXTURE::NEBULA_BACKGROUND_ID:      { requested_vec = &nebulaBgEffect_texOb_vec; break; }
	}
	
	//printf("searching color id = %i\n", _color_id);
     	for(unsigned int i = 0; i < requested_vec->size(); i++)
     	{
            	//printf("current color id = %i\n", particles_texOb_vec[i]->color_id);  
         	if ((*requested_vec)[i]->color_id == _color_id)
         	{
            		return (*requested_vec)[i]; 
            	}
        
	}
	
     	//printf("Particle with requested color is absent\n"); 
     	return NULL;
}

                
TextureOb* TextureManager :: getRandomTexOb(int texture_type_id)
{
	switch(texture_type_id)
	{
		case TEXTURE::SPACESTATION_ID:     { return getRandomTexObFromList(&spacestation_texOb_vec);             break; }
		case TEXTURE::SATELLITE_ID:        { return getRandomTexObFromList(&satellite_texOb_vec);            break; }
					
		case TEXTURE::SLOT_ID:             { return getRandomTexObFromList(&slot_texOb_vec);                 break; }
		case TEXTURE::CONTAINER_ID:        { return getRandomTexObFromList(&container_texOb_vec);            break; }
		case TEXTURE::STAR_ID:             { return getRandomTexObFromList(&star_texOb_vec);                 break; }
		case TEXTURE::PLANET_ID:           { return getRandomTexObFromList(&planet_texOb_vec);               break; }
		case TEXTURE::ATMOSPHERE_ID:       { return getRandomTexObFromList(&atmosphere_texOb_vec);           break; }
		case TEXTURE::ASTEROID_ID:         { return getRandomTexObFromList(&asteroid_texOb_vec);             break; }
		case TEXTURE::MINERAL_ID:          { return getRandomTexObFromList(&mineral_texOb_vec);              break; }
		case TEXTURE::BOMB_ID:             { return getRandomTexObFromList(&bomb_texOb_vec);                 break; }
		case TEXTURE::BLACKHOLE_ID:        { return getRandomTexObFromList(&blackhole_texOb_vec);            break; }
		case TEXTURE::ROCKET_BULLET_ID:    { return getRandomTexObFromList(&rocketBullet_texOb_vec);         break; }

		case TEXTURE::ROCKET_EQUIPMENT_ID:      { return getRandomTexObFromList(&rocketEquipment_texOb_vec);      break; }
		case TEXTURE::LAZER_EQUIPMENT_ID:       { return getRandomTexObFromList(&lazerEquipment_texOb_vec);       break; }
		case TEXTURE::RADAR_EQUIPMENT_ID:       { return getRandomTexObFromList(&radarEquipment_texOb_vec);       break; }
		case TEXTURE::DRIVE_EQUIPMENT_ID:       { return getRandomTexObFromList(&driveEquipment_texOb_vec);       break; }
		case TEXTURE::BAK_EQUIPMENT_ID:         { return getRandomTexObFromList(&bakEquipment_texOb_vec);         break; }
		case TEXTURE::ENERGIZER_EQUIPMENT_ID: { return getRandomTexObFromList(&energyBlockEquipment_texOb_vec); break; }
		case TEXTURE::PROTECTOR_EQUIPMENT_ID:   { return getRandomTexObFromList(&protectorEquipment_texOb_vec);   break; }
		case TEXTURE::DROID_EQUIPMENT_ID:       { return getRandomTexObFromList(&droidEquipment_texOb_vec);       break; }
		case TEXTURE::FREEZER_EQUIPMENT_ID:     { return getRandomTexObFromList(&freezerEquipment_texOb_vec);     break; }
		case TEXTURE::SCANER_EQUIPMENT_ID:      { return getRandomTexObFromList(&scanerEquipment_texOb_vec);      break; }
		case TEXTURE::GRAPPLE_EQUIPMENT_ID:     { return getRandomTexObFromList(&grappleEquipment_texOb_vec);     break; }
																		
		case TEXTURE::TURREL_ID:           { return getRandomTexObFromList(&turrel_texOb_vec);               break; }
		case TEXTURE::LAZER_EFFECT_ID:     { return getRandomTexObFromList(&lazerEffect_texOb_vec);          break; }
		case TEXTURE::LANDINGAREA_ID:      { return getRandomTexObFromList(&landingArea_texOb_vec);          break; }
				
		case TEXTURE::ANGAR_BACKGROUND_ID:         { return getRandomTexObFromList(&angarBg_texOb_vec);              break; }				
		case TEXTURE::STORE_BACKGROUND_ID:         { return getRandomTexObFromList(&storeBg_texOb_vec);              break; }	
		case TEXTURE::SHOP_BACKGROUND_ID:          { return getRandomTexObFromList(&shopBg_texOb_vec);               break; }	
		case TEXTURE::GOVERMENT_BACKGROUND_ID:     { return getRandomTexObFromList(&govermentBg_texOb_vec);          break; }	

		case TEXTURE::TEXT_BACKGROUND_ID:  { return getRandomTexObFromList(&textBackground_texOb_vec);       break; }			

		case TEXTURE::SHIELD_EFFECT_ID:    { return getRandomTexObFromList(&shieldEffect_texOb_vec);         break; }	
		case TEXTURE::NEBULA_BACKGROUND_ID:           { return getRandomTexObFromList(&nebulaBgEffect_texOb_vec);       break; }
		case TEXTURE::DISTANTSTAR_ID:      { return getRandomTexObFromList(&starBgEffect_texOb_vec);         break; }				
				
	}
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
     if (ship_race0_ranger_texOb_vec.size() == 0)   printf("ship_race0_ranger_texOb_vec.size() = 0\n"); 
     if (ship_race0_warrior_texOb_vec.size() == 0)  printf("ship_race0_warrior_texOb_vec.size() = 0\n"); 
     if (ship_race0_trader_texOb_vec.size() == 0)   printf("ship_race0_trader_texOb_vec.size() = 0\n"); 
     if (ship_race0_pirat_texOb_vec.size() == 0)    printf("ship_race0_pirat_texOb_vec.size() = 0\n"); 
     if (ship_race0_diplomat_texOb_vec.size() == 0) printf("ship_race0_diplomat_texOb_vec.size() = 0\n"); 

     if (ship_race1_ranger_texOb_vec.size() == 0)   printf("ship_race1_ranger_texOb_vec.size() = 0\n"); 
     if (ship_race1_warrior_texOb_vec.size() == 0)  printf("ship_race1_warrior_texOb_vec.size() = 0\n"); 
     if (ship_race1_trader_texOb_vec.size() == 0)   printf("ship_race1_trader_texOb_vec.size() = 0\n"); 
     if (ship_race1_pirat_texOb_vec.size() == 0)    printf("ship_race1_pirat_texOb_vec.size() = 0\n"); 
     if (ship_race1_diplomat_texOb_vec.size() == 0) printf("ship_race1_diplomat_texOb_vec.size() = 0\n"); 

     if (ship_race2_ranger_texOb_vec.size() == 0)   printf("ship_race2_ranger_texOb_vec.size() = 0\n"); 
     if (ship_race2_warrior_texOb_vec.size() == 0)  printf("ship_race2_warrior_texOb_vec.size() = 0\n"); 
     if (ship_race2_trader_texOb_vec.size() == 0)   printf("ship_race2_trader_texOb_vec.size() = 0\n"); 
     if (ship_race2_pirat_texOb_vec.size() == 0)    printf("ship_race2_pirat_texOb_vec.size() = 0\n"); 
     if (ship_race2_diplomat_texOb_vec.size() == 0) printf("ship_race2_diplomat_texOb_vec.size() = 0\n"); 
     
     if (ship_race3_ranger_texOb_vec.size() == 0)   printf("ship_race3_ranger_texOb_vec.size() = 0\n"); 
     if (ship_race3_warrior_texOb_vec.size() == 0)  printf("ship_race3_warrior_texOb_vec.size() = 0\n"); 
     if (ship_race3_trader_texOb_vec.size() == 0)   printf("ship_race3_trader_texOb_vec.size() = 0\n"); 
     if (ship_race3_pirat_texOb_vec.size() == 0)    printf("ship_race3_pirat_texOb_vec.size() = 0\n"); 
     if (ship_race3_diplomat_texOb_vec.size() == 0) printf("ship_race3_diplomat_texOb_vec.size() = 0\n"); 

     if (ship_race4_ranger_texOb_vec.size() == 0)   printf("ship_race4_ranger_texOb_vec.size() = 0\n"); 
     if (ship_race4_warrior_texOb_vec.size() == 0)  printf("ship_race4_warrior_texOb_vec.size() = 0\n"); 
     if (ship_race4_trader_texOb_vec.size() == 0)   printf("ship_race4_trader_texOb_vec.size() = 0\n"); 
     if (ship_race4_pirat_texOb_vec.size() == 0)    printf("ship_race4_pirat_texOb_vec.size() = 0\n"); 
     if (ship_race4_diplomat_texOb_vec.size() == 0) printf("ship_race4_diplomat_texOb_vec.size() = 0\n"); 

     if (ship_race6_ranger_texOb_vec.size() == 0)   printf("ship_race6_ranger_texOb_vec.size() = 0\n"); 
     if (ship_race6_warrior_texOb_vec.size() == 0)  printf("ship_race6_warrior_texOb_vec.size() = 0\n"); 
     if (ship_race6_trader_texOb_vec.size() == 0)   printf("ship_race6_trader_texOb_vec.size() = 0\n"); 
     if (ship_race6_pirat_texOb_vec.size() == 0)    printf("ship_race6_pirat_texOb_vec.size() = 0\n"); 
     if (ship_race6_diplomat_texOb_vec.size() == 0) printf("ship_race6_diplomat_texOb_vec.size() = 0\n"); 


     if (ship_race7_ranger_texOb_vec.size() == 0)   printf("ship_race7_ranger_texOb_vec.size() = 0\n"); 
     if (ship_race7_warrior_texOb_vec.size() == 0)  printf("ship_race7_warrior_texOb_vec.size() = 0\n"); 
     if (ship_race7_trader_texOb_vec.size() == 0)   printf("ship_race7_trader_texOb_vec.size() = 0\n"); 
     if (ship_race7_pirat_texOb_vec.size() == 0)    printf("ship_race7_pirat_texOb_vec.size() = 0\n"); 
     if (ship_race7_diplomat_texOb_vec.size() == 0) printf("ship_race7_diplomat_texOb_vec.size() = 0\n"); 
}


