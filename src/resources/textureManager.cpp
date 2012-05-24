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

void TextureManager::Add(TextureOb* texOb)
{
	textureOb_total_vec.push_back(texOb);

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

		case TEXTURE::MODULE_ID: { module_texOb_vec.push_back(texOb);      break; } 
				
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



TextureOb* TextureManager :: GetRandomTextureObFromList(std::vector<TextureOb*>* pTo_list)
{  
     	if (pTo_list->size() > 1)
		return (*pTo_list)[getRandInt(0, pTo_list->size() )];
     	else 
        	return (*pTo_list)[0];
	
	assert(NULL);
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
		case RACE::R0_ID: { return GetRandomTextureObFromList(&face_race0_texOb_vec); }
		case RACE::R1_ID: { return GetRandomTextureObFromList(&face_race1_texOb_vec); }
		case RACE::R2_ID: { return GetRandomTextureObFromList(&face_race2_texOb_vec); }
 		case RACE::R3_ID: { return GetRandomTextureObFromList(&face_race3_texOb_vec); }
		case RACE::R4_ID: { return GetRandomTextureObFromList(&face_race4_texOb_vec); }
		
		case RACE::R6_ID: { return GetRandomTextureObFromList(&face_race6_texOb_vec); }
		case RACE::R7_ID: { return GetRandomTextureObFromList(&face_race7_texOb_vec); }
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
                		case CLASS::RANGER_ID:   { return GetRandomTextureObFromList(&ship_race0_ranger_texOb_vec);   break; }
				case CLASS::WARRIOR_ID:  { return GetRandomTextureObFromList(&ship_race0_warrior_texOb_vec);  break; }
 				case CLASS::TRADER_ID:   { return GetRandomTextureObFromList(&ship_race0_trader_texOb_vec);   break; }
				case CLASS::PIRAT_ID:    { return GetRandomTextureObFromList(&ship_race0_pirat_texOb_vec);    break; }
				case CLASS::DIPLOMAT_ID: { return GetRandomTextureObFromList(&ship_race0_diplomat_texOb_vec); break; }
		       }
		       
		       break;
		}

        	case RACE::R1_ID:
        	{
                	switch(_subtype_id)
                	{	
                		case CLASS::RANGER_ID:   { return GetRandomTextureObFromList(&ship_race1_ranger_texOb_vec);   break; }
				case CLASS::WARRIOR_ID:  { return GetRandomTextureObFromList(&ship_race1_warrior_texOb_vec);  break; } 
				case CLASS::TRADER_ID:   { return GetRandomTextureObFromList(&ship_race1_trader_texOb_vec);   break; }
				case CLASS::PIRAT_ID:    { return GetRandomTextureObFromList(&ship_race1_pirat_texOb_vec);    break; }
				case CLASS::DIPLOMAT_ID: { return GetRandomTextureObFromList(&ship_race1_diplomat_texOb_vec); break; }
			}
			
			break;
		}
		
	        case RACE::R2_ID:
        	{
                	switch(_subtype_id)
                	{	
                		case CLASS::RANGER_ID:   { return GetRandomTextureObFromList(&ship_race2_ranger_texOb_vec);   break; }
				case CLASS::WARRIOR_ID:  { return GetRandomTextureObFromList(&ship_race2_warrior_texOb_vec);  break; } 
				case CLASS::TRADER_ID:   { return GetRandomTextureObFromList(&ship_race2_trader_texOb_vec);   break; }
				case CLASS::PIRAT_ID:    { return GetRandomTextureObFromList(&ship_race2_pirat_texOb_vec);    break; }
				case CLASS::DIPLOMAT_ID: { return GetRandomTextureObFromList(&ship_race2_diplomat_texOb_vec); break; }
			}
			
			break;
        	}
      

    	        case RACE::R3_ID:
        	{
                	switch(_subtype_id)
                	{	
                		case CLASS::RANGER_ID:   { return GetRandomTextureObFromList(&ship_race3_ranger_texOb_vec);   break; }
				case CLASS::WARRIOR_ID:  { return GetRandomTextureObFromList(&ship_race3_warrior_texOb_vec);  break; } 
				case CLASS::TRADER_ID:   { return GetRandomTextureObFromList(&ship_race3_trader_texOb_vec);   break; }
				case CLASS::PIRAT_ID:    { return GetRandomTextureObFromList(&ship_race3_pirat_texOb_vec);    break; }
				case CLASS::DIPLOMAT_ID: { return GetRandomTextureObFromList(&ship_race3_diplomat_texOb_vec); break; }
			}
			
			break;
        	}


    	        case RACE::R4_ID:
        	{
                	switch(_subtype_id)
                	{	
                		case CLASS::RANGER_ID:   { return GetRandomTextureObFromList(&ship_race4_ranger_texOb_vec);   break; }
				case CLASS::WARRIOR_ID:  { return GetRandomTextureObFromList(&ship_race4_warrior_texOb_vec);  break; } 
				case CLASS::TRADER_ID:   { return GetRandomTextureObFromList(&ship_race4_trader_texOb_vec);   break; }
				case CLASS::PIRAT_ID:    { return GetRandomTextureObFromList(&ship_race4_pirat_texOb_vec);    break; }
				case CLASS::DIPLOMAT_ID: { return GetRandomTextureObFromList(&ship_race4_diplomat_texOb_vec); break; }
			}
			
			break;
        	}


	        case RACE::R6_ID:
        	{
                	switch(_subtype_id)
                	{	
                		case CLASS::RANGER_ID:   { return GetRandomTextureObFromList(&ship_race6_ranger_texOb_vec);   break; }
				case CLASS::WARRIOR_ID:  { return GetRandomTextureObFromList(&ship_race6_warrior_texOb_vec);  break; } 
				case CLASS::TRADER_ID:   { return GetRandomTextureObFromList(&ship_race6_trader_texOb_vec);   break; }
				case CLASS::PIRAT_ID:    { return GetRandomTextureObFromList(&ship_race6_pirat_texOb_vec);    break; }
				case CLASS::DIPLOMAT_ID: { return GetRandomTextureObFromList(&ship_race6_diplomat_texOb_vec); break; }
			}
			
			break;
        	}

       	        case RACE::R7_ID:
        	{
                	switch(_subtype_id)
                	{	
                		case CLASS::RANGER_ID:   { return GetRandomTextureObFromList(&ship_race7_ranger_texOb_vec);   break; }
				case CLASS::WARRIOR_ID:  { return GetRandomTextureObFromList(&ship_race7_warrior_texOb_vec);  break; } 
				case CLASS::TRADER_ID:   { return GetRandomTextureObFromList(&ship_race7_trader_texOb_vec);   break; }
				case CLASS::PIRAT_ID:    { return GetRandomTextureObFromList(&ship_race7_pirat_texOb_vec);    break; }
				case CLASS::DIPLOMAT_ID: { return GetRandomTextureObFromList(&ship_race7_diplomat_texOb_vec); break; }
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

                
TextureOb* TextureManager::GetRandomTextureOb(int texture_type_id)
{
	switch(texture_type_id)
	{
		case TEXTURE::SPACESTATION_ID:     { return GetRandomTextureObFromList(&spacestation_texOb_vec);             break; }
		case TEXTURE::SATELLITE_ID:        { return GetRandomTextureObFromList(&satellite_texOb_vec);            break; }
					
		case TEXTURE::SLOT_ID:             { return GetRandomTextureObFromList(&slot_texOb_vec);                 break; }
		case TEXTURE::CONTAINER_ID:        { return GetRandomTextureObFromList(&container_texOb_vec);            break; }
		case TEXTURE::STAR_ID:             { return GetRandomTextureObFromList(&star_texOb_vec);                 break; }
		case TEXTURE::PLANET_ID:           { return GetRandomTextureObFromList(&planet_texOb_vec);               break; }
		case TEXTURE::ATMOSPHERE_ID:       { return GetRandomTextureObFromList(&atmosphere_texOb_vec);           break; }
		case TEXTURE::ASTEROID_ID:         { return GetRandomTextureObFromList(&asteroid_texOb_vec);             break; }
		case TEXTURE::MINERAL_ID:          { return GetRandomTextureObFromList(&mineral_texOb_vec);              break; }
		case TEXTURE::BOMB_ID:             { return GetRandomTextureObFromList(&bomb_texOb_vec);                 break; }
		case TEXTURE::BLACKHOLE_ID:        { return GetRandomTextureObFromList(&blackhole_texOb_vec);            break; }
		case TEXTURE::ROCKET_BULLET_ID:    { return GetRandomTextureObFromList(&rocketBullet_texOb_vec);         break; }

		case TEXTURE::ROCKET_EQUIPMENT_ID:      { return GetRandomTextureObFromList(&rocketEquipment_texOb_vec);      break; }
		case TEXTURE::LAZER_EQUIPMENT_ID:       { return GetRandomTextureObFromList(&lazerEquipment_texOb_vec);       break; }
		case TEXTURE::RADAR_EQUIPMENT_ID:       { return GetRandomTextureObFromList(&radarEquipment_texOb_vec);       break; }
		case TEXTURE::DRIVE_EQUIPMENT_ID:       { return GetRandomTextureObFromList(&driveEquipment_texOb_vec);       break; }
		case TEXTURE::BAK_EQUIPMENT_ID:         { return GetRandomTextureObFromList(&bakEquipment_texOb_vec);         break; }
		case TEXTURE::ENERGIZER_EQUIPMENT_ID: { return GetRandomTextureObFromList(&energyBlockEquipment_texOb_vec); break; }
		case TEXTURE::PROTECTOR_EQUIPMENT_ID:   { return GetRandomTextureObFromList(&protectorEquipment_texOb_vec);   break; }
		case TEXTURE::DROID_EQUIPMENT_ID:       { return GetRandomTextureObFromList(&droidEquipment_texOb_vec);       break; }
		case TEXTURE::FREEZER_EQUIPMENT_ID:     { return GetRandomTextureObFromList(&freezerEquipment_texOb_vec);     break; }
		case TEXTURE::SCANER_EQUIPMENT_ID:      { return GetRandomTextureObFromList(&scanerEquipment_texOb_vec);      break; }
		case TEXTURE::GRAPPLE_EQUIPMENT_ID:     { return GetRandomTextureObFromList(&grappleEquipment_texOb_vec);     break; }

		case TEXTURE::MODULE_ID: { return GetRandomTextureObFromList(&module_texOb_vec);     break; }
																				
		case TEXTURE::TURREL_ID:           { return GetRandomTextureObFromList(&turrel_texOb_vec);               break; }
		case TEXTURE::LAZER_EFFECT_ID:     { return GetRandomTextureObFromList(&lazerEffect_texOb_vec);          break; }
		case TEXTURE::LANDINGAREA_ID:      { return GetRandomTextureObFromList(&landingArea_texOb_vec);          break; }
				
		case TEXTURE::ANGAR_BACKGROUND_ID:         { return GetRandomTextureObFromList(&angarBg_texOb_vec);              break; }				
		case TEXTURE::STORE_BACKGROUND_ID:         { return GetRandomTextureObFromList(&storeBg_texOb_vec);              break; }	
		case TEXTURE::SHOP_BACKGROUND_ID:          { return GetRandomTextureObFromList(&shopBg_texOb_vec);               break; }	
		case TEXTURE::GOVERMENT_BACKGROUND_ID:     { return GetRandomTextureObFromList(&govermentBg_texOb_vec);          break; }	

		case TEXTURE::TEXT_BACKGROUND_ID:  { return GetRandomTextureObFromList(&textBackground_texOb_vec);       break; }			

		case TEXTURE::SHIELD_EFFECT_ID:    { return GetRandomTextureObFromList(&shieldEffect_texOb_vec);         break; }	
		case TEXTURE::NEBULA_BACKGROUND_ID:           { return GetRandomTextureObFromList(&nebulaBgEffect_texOb_vec);       break; }
		case TEXTURE::DISTANTSTAR_ID:      { return GetRandomTextureObFromList(&starBgEffect_texOb_vec);         break; }				
				
	}
}
		
void TextureManager::FillShipSubTypeList()
{
        if (ship_race0_ranger_texOb_vec.size() != 0)   RACE0_ALLOWED_SUBTYPE_LIST.push_back(CLASS::RANGER_ID);
        if (ship_race0_warrior_texOb_vec.size() != 0)  RACE0_ALLOWED_SUBTYPE_LIST.push_back(CLASS::WARRIOR_ID);
        if (ship_race0_trader_texOb_vec.size() != 0)   RACE0_ALLOWED_SUBTYPE_LIST.push_back(CLASS::TRADER_ID);
        if (ship_race0_pirat_texOb_vec.size() != 0)    RACE0_ALLOWED_SUBTYPE_LIST.push_back(CLASS::PIRAT_ID);
        if (ship_race0_diplomat_texOb_vec.size() != 0) RACE0_ALLOWED_SUBTYPE_LIST.push_back(CLASS::DIPLOMAT_ID);

        if (ship_race1_ranger_texOb_vec.size() != 0)   RACE1_ALLOWED_SUBTYPE_LIST.push_back(CLASS::RANGER_ID);
        if (ship_race1_warrior_texOb_vec.size() != 0)  RACE1_ALLOWED_SUBTYPE_LIST.push_back(CLASS::WARRIOR_ID);
        if (ship_race1_trader_texOb_vec.size() != 0)   RACE1_ALLOWED_SUBTYPE_LIST.push_back(CLASS::TRADER_ID);
        if (ship_race1_pirat_texOb_vec.size() != 0)    RACE1_ALLOWED_SUBTYPE_LIST.push_back(CLASS::PIRAT_ID); 
        if (ship_race1_diplomat_texOb_vec.size() != 0) RACE1_ALLOWED_SUBTYPE_LIST.push_back(CLASS::DIPLOMAT_ID);

        if (ship_race2_ranger_texOb_vec.size() != 0)   RACE2_ALLOWED_SUBTYPE_LIST.push_back(CLASS::RANGER_ID);
        if (ship_race2_warrior_texOb_vec.size() != 0)  RACE2_ALLOWED_SUBTYPE_LIST.push_back(CLASS::WARRIOR_ID);
        if (ship_race2_trader_texOb_vec.size() != 0)   RACE2_ALLOWED_SUBTYPE_LIST.push_back(CLASS::TRADER_ID); 
        if (ship_race2_pirat_texOb_vec.size() != 0)    RACE2_ALLOWED_SUBTYPE_LIST.push_back(CLASS::PIRAT_ID);
        if (ship_race2_diplomat_texOb_vec.size() != 0) RACE2_ALLOWED_SUBTYPE_LIST.push_back(CLASS::DIPLOMAT_ID);
     
        if (ship_race3_ranger_texOb_vec.size() != 0)   RACE3_ALLOWED_SUBTYPE_LIST.push_back(CLASS::RANGER_ID);
        if (ship_race3_warrior_texOb_vec.size() != 0)  RACE3_ALLOWED_SUBTYPE_LIST.push_back(CLASS::WARRIOR_ID);
        if (ship_race3_trader_texOb_vec.size() != 0)   RACE3_ALLOWED_SUBTYPE_LIST.push_back(CLASS::TRADER_ID);
        if (ship_race3_pirat_texOb_vec.size() != 0)    RACE3_ALLOWED_SUBTYPE_LIST.push_back(CLASS::PIRAT_ID);
        if (ship_race3_diplomat_texOb_vec.size() != 0) RACE3_ALLOWED_SUBTYPE_LIST.push_back(CLASS::DIPLOMAT_ID); 

        if (ship_race4_ranger_texOb_vec.size() != 0)   RACE4_ALLOWED_SUBTYPE_LIST.push_back(CLASS::RANGER_ID);
        if (ship_race4_warrior_texOb_vec.size() != 0)  RACE4_ALLOWED_SUBTYPE_LIST.push_back(CLASS::WARRIOR_ID); 
        if (ship_race4_trader_texOb_vec.size() != 0)   RACE4_ALLOWED_SUBTYPE_LIST.push_back(CLASS::TRADER_ID);
        if (ship_race4_pirat_texOb_vec.size() != 0)    RACE4_ALLOWED_SUBTYPE_LIST.push_back(CLASS::PIRAT_ID); 
        if (ship_race4_diplomat_texOb_vec.size() != 0) RACE4_ALLOWED_SUBTYPE_LIST.push_back(CLASS::DIPLOMAT_ID);

        if (ship_race6_ranger_texOb_vec.size() != 0)   RACE6_ALLOWED_SUBTYPE_LIST.push_back(CLASS::RANGER_ID);
        if (ship_race6_warrior_texOb_vec.size() != 0)  RACE6_ALLOWED_SUBTYPE_LIST.push_back(CLASS::WARRIOR_ID);
        if (ship_race6_trader_texOb_vec.size() != 0)   RACE6_ALLOWED_SUBTYPE_LIST.push_back(CLASS::TRADER_ID);
        if (ship_race6_pirat_texOb_vec.size() != 0)    RACE6_ALLOWED_SUBTYPE_LIST.push_back(CLASS::PIRAT_ID);
        if (ship_race6_diplomat_texOb_vec.size() != 0) RACE6_ALLOWED_SUBTYPE_LIST.push_back(CLASS::DIPLOMAT_ID);

        if (ship_race7_ranger_texOb_vec.size() != 0)   RACE7_ALLOWED_SUBTYPE_LIST.push_back(CLASS::RANGER_ID); 
        if (ship_race7_warrior_texOb_vec.size() != 0)  RACE7_ALLOWED_SUBTYPE_LIST.push_back(CLASS::WARRIOR_ID); 
        if (ship_race7_trader_texOb_vec.size() != 0)   RACE7_ALLOWED_SUBTYPE_LIST.push_back(CLASS::TRADER_ID); 
        if (ship_race7_pirat_texOb_vec.size() != 0)    RACE7_ALLOWED_SUBTYPE_LIST.push_back(CLASS::PIRAT_ID); 
        if (ship_race7_diplomat_texOb_vec.size() != 0) RACE7_ALLOWED_SUBTYPE_LIST.push_back(CLASS::DIPLOMAT_ID);                      
}

TextureOb* TextureManager::GetTextureObByPath(const std::string& path)
{
	for (unsigned int i = 0; i<textureOb_total_vec.size(); i++)
	{
		if (textureOb_total_vec[i]->path == path)
		{
			return textureOb_total_vec[i];
		}
	}
	
	return NULL;
}
		
