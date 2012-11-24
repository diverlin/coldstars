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

#include "TextureManager.hpp"
#include "../common/constants.hpp"
#include "../common/rand.hpp"
#include "../common/gameStruct.hpp"
#include "../resources/textureOb.hpp"

TextureManager& TextureManager::Instance()
{
	static TextureManager instance;
	return instance;
}

void TextureManager::Add(TextureOb* texOb)
{
	textureOb_total_vec.push_back(texOb);

	switch(texOb->type_id)
	{
	  	case TEXTURE::SPACESTATION_ID: { spacestation_texOb_vec.push_back(texOb);    break; }       
	 	case TEXTURE::SATELLITE_ID:    { satellite_texOb_vec.push_back(texOb);   break; }       
	  		  		
  		case TEXTURE::ITEM_SLOT_ID:    { itemslot_texOb_vec.push_back(texOb);        break; }       
    		case TEXTURE::VEHICLE_SLOT_ID: { vehicleslot_texOb_vec.push_back(texOb); break; }
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
        					case ENTITY::RANGER_ID:   { ship_race0_ranger_texOb_vec.push_back(texOb);   break; }
        					case ENTITY::WARRIOR_ID:  { ship_race0_warrior_texOb_vec.push_back(texOb);  break; }
           					case ENTITY::TRADER_ID:   { ship_race0_trader_texOb_vec.push_back(texOb);   break; }
           					case ENTITY::PIRAT_ID:    { ship_race0_pirat_texOb_vec.push_back(texOb);    break; }
           					case ENTITY::DIPLOMAT_ID: { ship_race0_diplomat_texOb_vec.push_back(texOb); break; }
        				}
        				
        				break;
        			}
        			

        			case RACE::R1_ID:
        			{
        			         switch(texOb->subtype_id)
        			         {
        			         	case ENTITY::RANGER_ID:   { ship_race1_ranger_texOb_vec.push_back(texOb);   break; }
           					case ENTITY::WARRIOR_ID:  { ship_race1_warrior_texOb_vec.push_back(texOb);  break; }
           					case ENTITY::TRADER_ID:   { ship_race1_trader_texOb_vec.push_back(texOb);   break; }
           					case ENTITY::PIRAT_ID:    { ship_race1_pirat_texOb_vec.push_back(texOb);    break; }
           					case ENTITY::DIPLOMAT_ID: { ship_race1_diplomat_texOb_vec.push_back(texOb); break; }
        				 }
        				 
        				 break;
        			}

        			case RACE::R2_ID:
        			{
        			         switch(texOb->subtype_id)
        			         {
        			         	case ENTITY::RANGER_ID: { ship_race2_ranger_texOb_vec.push_back(texOb); break; }
           					case ENTITY::WARRIOR_ID: { ship_race2_warrior_texOb_vec.push_back(texOb); break; }
           					case ENTITY::TRADER_ID: { ship_race2_trader_texOb_vec.push_back(texOb); break; }
           					case ENTITY::PIRAT_ID:  { ship_race2_pirat_texOb_vec.push_back(texOb);  break; }
           					case ENTITY::DIPLOMAT_ID: { ship_race2_diplomat_texOb_vec.push_back(texOb); break; }
        				 }
        				 
        				 break;
        			}
        			
        			
				case RACE::R3_ID:
				{
					switch(texOb->subtype_id)
					{
						case ENTITY::RANGER_ID:  { ship_race3_ranger_texOb_vec.push_back(texOb);    break; }
           					case ENTITY::WARRIOR_ID: { ship_race3_warrior_texOb_vec.push_back(texOb);   break; }
           					case ENTITY::TRADER_ID:  { ship_race3_trader_texOb_vec.push_back(texOb);    break; }
           					case ENTITY::PIRAT_ID:   { ship_race3_pirat_texOb_vec.push_back(texOb);     break; }
           					case ENTITY::DIPLOMAT_ID: { ship_race3_diplomat_texOb_vec.push_back(texOb); break; }
        				}
        				
        				break;
        			}

        			case RACE::R4_ID:
        			{
        				switch(texOb->subtype_id)
        				{	
        					case ENTITY::RANGER_ID:   { ship_race4_ranger_texOb_vec.push_back(texOb);   break; }
           					case ENTITY::WARRIOR_ID:  { ship_race4_warrior_texOb_vec.push_back(texOb);  break; }
           					case ENTITY::TRADER_ID:   { ship_race4_trader_texOb_vec.push_back(texOb);   break; }
           					case ENTITY::PIRAT_ID:    { ship_race4_pirat_texOb_vec.push_back(texOb);    break; } 
           					case ENTITY::DIPLOMAT_ID: { ship_race4_diplomat_texOb_vec.push_back(texOb); break; }
           				}
           				
           				break;
           			}
			
				case RACE::R6_ID:
				{	
					switch(texOb->subtype_id)
					{
						case ENTITY::RANGER_ID:   { ship_race6_ranger_texOb_vec.push_back(texOb);   break; }
           					case ENTITY::WARRIOR_ID:  { ship_race6_warrior_texOb_vec.push_back(texOb);  break; }
           					case ENTITY::TRADER_ID:   { ship_race6_trader_texOb_vec.push_back(texOb);   break; }
           					case ENTITY::PIRAT_ID:    { ship_race6_pirat_texOb_vec.push_back(texOb);    break; }
           					case ENTITY::DIPLOMAT_ID: { ship_race6_diplomat_texOb_vec.push_back(texOb); break; }
        				}
        				
        				break;
        			}

				case RACE::R7_ID:
				{	
					switch(texOb->subtype_id)
					{
						case ENTITY::RANGER_ID:   { ship_race7_ranger_texOb_vec.push_back(texOb);   break; }
           					case ENTITY::WARRIOR_ID:  { ship_race7_warrior_texOb_vec.push_back(texOb);  break; }
           					case ENTITY::TRADER_ID:   { ship_race7_trader_texOb_vec.push_back(texOb);   break; }
           					case ENTITY::PIRAT_ID:    { ship_race7_pirat_texOb_vec.push_back(texOb);    break; }
           					case ENTITY::DIPLOMAT_ID: { ship_race7_diplomat_texOb_vec.push_back(texOb); break; }
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

		// LAND
    		case TEXTURE::NATURELAND_BACKGROUND_ID: { landBg_texOb_vec.push_back(texOb); break; }

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



TextureOb* TextureManager::GetRandomTextureObFromVec(const std::vector<TextureOb*>& textureOb_vec)
{
     	if (textureOb_vec.size() == 0)
     	{
     		return NULL;
     	} 
     	
     	if (textureOb_vec.size() == 1)
	{
	        return textureOb_vec[0];
	}     	  
     	if (textureOb_vec.size() > 1)
	{
		return textureOb_vec[getRandInt(0, textureOb_vec.size())];
     	}
}

TextureOb* TextureManager::GetShipTexObByClosestSizeFromVec(const std::vector<TextureOb*>& textureOb_vec, int size_id)
{  
    	TextureOb* texOb = GetShipTexObBySizeFromVec(textureOb_vec, size_id);
        int sign_base = -1;
        int sign = 1;
        int i = 1;

	while (texOb == NULL)
	{
		sign *= sign_base;
		size_id += sign*i;
		texOb = GetShipTexObBySizeFromVec(textureOb_vec, size_id);
		i++;
		if (size_id > 2*SIZE_10_ID)
		{
			break;
		}
	}
	                                                                                                                             
        return texOb;
}


TextureOb* TextureManager::GetShipTexObBySizeFromVec(const std::vector<TextureOb*>& textureOb_vec, int size_id)
{  
	for (unsigned int i=0; i<textureOb_vec.size(); i++)
       	{
       		if (textureOb_vec[i]->size_id == size_id)
       		{
                	return textureOb_vec[i];
        	}
    	}

    	return NULL;
}


TextureOb* TextureManager::GetRandomFaceTexObWithFolloingAttributes(int race_id)
{
	switch(race_id)
	{
		case RACE::R0_ID: { return GetRandomTextureObFromVec(face_race0_texOb_vec); }
		case RACE::R1_ID: { return GetRandomTextureObFromVec(face_race1_texOb_vec); }
		case RACE::R2_ID: { return GetRandomTextureObFromVec(face_race2_texOb_vec); }
 		case RACE::R3_ID: { return GetRandomTextureObFromVec(face_race3_texOb_vec); }
		case RACE::R4_ID: { return GetRandomTextureObFromVec(face_race4_texOb_vec); }
		
		case RACE::R6_ID: { return GetRandomTextureObFromVec(face_race6_texOb_vec); }
		case RACE::R7_ID: { return GetRandomTextureObFromVec(face_race7_texOb_vec); }
	}
	
	return NULL;
}

TextureOb* TextureManager::GetRandomShipTexObWithFollowingAtrributes(int race_id, int subtype_id, int size_id)
{
        switch(race_id)
        {	
        	case RACE::R0_ID:
        	{
                	switch(subtype_id)
                	{
                		case ENTITY::RANGER_ID:   { return GetShipTexObByClosestSizeFromVec(ship_race0_ranger_texOb_vec, size_id);   break; }
				case ENTITY::WARRIOR_ID:  { return GetShipTexObByClosestSizeFromVec(ship_race0_warrior_texOb_vec, size_id);  break; }
 				case ENTITY::TRADER_ID:   { return GetShipTexObByClosestSizeFromVec(ship_race0_trader_texOb_vec, size_id);   break; }
				case ENTITY::PIRAT_ID:    { return GetShipTexObByClosestSizeFromVec(ship_race0_pirat_texOb_vec, size_id);    break; }
				case ENTITY::DIPLOMAT_ID: { return GetShipTexObByClosestSizeFromVec(ship_race0_diplomat_texOb_vec, size_id); break; }
		       }
		       
		       break;
		}

        	case RACE::R1_ID:
        	{
                	switch(subtype_id)
                	{	
                		case ENTITY::RANGER_ID:   { return GetShipTexObByClosestSizeFromVec(ship_race1_ranger_texOb_vec, size_id);   break; }
				case ENTITY::WARRIOR_ID:  { return GetShipTexObByClosestSizeFromVec(ship_race1_warrior_texOb_vec, size_id);  break; } 
				case ENTITY::TRADER_ID:   { return GetShipTexObByClosestSizeFromVec(ship_race1_trader_texOb_vec, size_id);   break; }
				case ENTITY::PIRAT_ID:    { return GetShipTexObByClosestSizeFromVec(ship_race1_pirat_texOb_vec, size_id);    break; }
				case ENTITY::DIPLOMAT_ID: { return GetShipTexObByClosestSizeFromVec(ship_race1_diplomat_texOb_vec, size_id); break; }
			}
			
			break;
		}
		
	        case RACE::R2_ID:
        	{
                	switch(subtype_id)
                	{	
                		case ENTITY::RANGER_ID:   { return GetShipTexObByClosestSizeFromVec(ship_race2_ranger_texOb_vec, size_id);   break; }
				case ENTITY::WARRIOR_ID:  { return GetShipTexObByClosestSizeFromVec(ship_race2_warrior_texOb_vec, size_id);  break; } 
				case ENTITY::TRADER_ID:   { return GetShipTexObByClosestSizeFromVec(ship_race2_trader_texOb_vec, size_id);   break; }
				case ENTITY::PIRAT_ID:    { return GetShipTexObByClosestSizeFromVec(ship_race2_pirat_texOb_vec, size_id);    break; }
				case ENTITY::DIPLOMAT_ID: { return GetShipTexObByClosestSizeFromVec(ship_race2_diplomat_texOb_vec, size_id); break; }
			}
			
			break;
        	}
      

    	        case RACE::R3_ID:
        	{
                	switch(subtype_id)
                	{	
                		case ENTITY::RANGER_ID:   { return GetShipTexObByClosestSizeFromVec(ship_race3_ranger_texOb_vec, size_id);   break; }
				case ENTITY::WARRIOR_ID:  { return GetShipTexObByClosestSizeFromVec(ship_race3_warrior_texOb_vec, size_id);  break; } 
				case ENTITY::TRADER_ID:   { return GetShipTexObByClosestSizeFromVec(ship_race3_trader_texOb_vec, size_id);   break; }
				case ENTITY::PIRAT_ID:    { return GetShipTexObByClosestSizeFromVec(ship_race3_pirat_texOb_vec, size_id);    break; }
				case ENTITY::DIPLOMAT_ID: { return GetShipTexObByClosestSizeFromVec(ship_race3_diplomat_texOb_vec, size_id); break; }
			}
			
			break;
        	}


    	        case RACE::R4_ID:
        	{
                	switch(subtype_id)
                	{	
                		case ENTITY::RANGER_ID:   { return GetShipTexObByClosestSizeFromVec(ship_race4_ranger_texOb_vec, size_id);   break; }
				case ENTITY::WARRIOR_ID:  { return GetShipTexObByClosestSizeFromVec(ship_race4_warrior_texOb_vec, size_id);  break; } 
				case ENTITY::TRADER_ID:   { return GetShipTexObByClosestSizeFromVec(ship_race4_trader_texOb_vec, size_id);   break; }
				case ENTITY::PIRAT_ID:    { return GetShipTexObByClosestSizeFromVec(ship_race4_pirat_texOb_vec, size_id);    break; }
				case ENTITY::DIPLOMAT_ID: { return GetShipTexObByClosestSizeFromVec(ship_race4_diplomat_texOb_vec, size_id); break; }
			}
			
			break;
        	}


	        case RACE::R6_ID:
        	{
                	switch(subtype_id)
                	{	
                		case ENTITY::RANGER_ID:   { return GetShipTexObByClosestSizeFromVec(ship_race6_ranger_texOb_vec, size_id);   break; }
				case ENTITY::WARRIOR_ID:  { return GetShipTexObByClosestSizeFromVec(ship_race6_warrior_texOb_vec, size_id);  break; } 
				case ENTITY::TRADER_ID:   { return GetShipTexObByClosestSizeFromVec(ship_race6_trader_texOb_vec, size_id);   break; }
				case ENTITY::PIRAT_ID:    { return GetShipTexObByClosestSizeFromVec(ship_race6_pirat_texOb_vec, size_id);    break; }
				case ENTITY::DIPLOMAT_ID: { return GetShipTexObByClosestSizeFromVec(ship_race6_diplomat_texOb_vec, size_id); break; }
			}
			
			break;
        	}

       	        case RACE::R7_ID:
        	{
                	switch(subtype_id)
                	{	
                		case ENTITY::RANGER_ID:   { return GetShipTexObByClosestSizeFromVec(ship_race7_ranger_texOb_vec, size_id);   break; }
				case ENTITY::WARRIOR_ID:  { return GetShipTexObByClosestSizeFromVec(ship_race7_warrior_texOb_vec, size_id);  break; } 
				case ENTITY::TRADER_ID:   { return GetShipTexObByClosestSizeFromVec(ship_race7_trader_texOb_vec, size_id);   break; }
				case ENTITY::PIRAT_ID:    { return GetShipTexObByClosestSizeFromVec(ship_race7_pirat_texOb_vec, size_id);    break; }
				case ENTITY::DIPLOMAT_ID: { return GetShipTexObByClosestSizeFromVec(ship_race7_diplomat_texOb_vec, size_id); break; }
			}
			
			break;
        	}
        }
       
        return NULL;

}

TextureOb* TextureManager::GetTexObByColorId(int _type_id, int _color_id)
{
	std::vector<TextureOb*>* requested_vec = NULL;
	
	switch(_type_id)
	{
		case TEXTURE::PARTICLE_EFFECT_ID:    { requested_vec = &particles_texOb_vec;      break; }
		case TEXTURE::DISTANTSTAR_ID: 	{ requested_vec = &starBgEffect_texOb_vec;   break; }
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
		case TEXTURE::SPACESTATION_ID:     { return GetRandomTextureObFromVec(spacestation_texOb_vec);             break; }
		case TEXTURE::SATELLITE_ID:        { return GetRandomTextureObFromVec(satellite_texOb_vec);            break; }
					
		case TEXTURE::ITEM_SLOT_ID:         { return GetRandomTextureObFromVec(itemslot_texOb_vec);             break; }
		case TEXTURE::VEHICLE_SLOT_ID:      { return GetRandomTextureObFromVec(vehicleslot_texOb_vec);          break; }
		case TEXTURE::CONTAINER_ID:        { return GetRandomTextureObFromVec(container_texOb_vec);            break; }
		case TEXTURE::STAR_ID:             { return GetRandomTextureObFromVec(star_texOb_vec);                 break; }
		case TEXTURE::PLANET_ID:           { return GetRandomTextureObFromVec(planet_texOb_vec);               break; }
		case TEXTURE::ATMOSPHERE_ID:       { return GetRandomTextureObFromVec(atmosphere_texOb_vec);           break; }
		case TEXTURE::ASTEROID_ID:         { return GetRandomTextureObFromVec(asteroid_texOb_vec);             break; }
		case TEXTURE::MINERAL_ID:          { return GetRandomTextureObFromVec(mineral_texOb_vec);              break; }
		case TEXTURE::BOMB_ID:             { return GetRandomTextureObFromVec(bomb_texOb_vec);                 break; }
		case TEXTURE::BLACKHOLE_ID:        { return GetRandomTextureObFromVec(blackhole_texOb_vec);            break; }
		case TEXTURE::ROCKET_BULLET_ID:    { return GetRandomTextureObFromVec(rocketBullet_texOb_vec);         break; }

		case TEXTURE::ROCKET_EQUIPMENT_ID:      { return GetRandomTextureObFromVec(rocketEquipment_texOb_vec);      break; }
		case TEXTURE::LAZER_EQUIPMENT_ID:       { return GetRandomTextureObFromVec(lazerEquipment_texOb_vec);       break; }
		case TEXTURE::RADAR_EQUIPMENT_ID:       { return GetRandomTextureObFromVec(radarEquipment_texOb_vec);       break; }
		case TEXTURE::DRIVE_EQUIPMENT_ID:       { return GetRandomTextureObFromVec(driveEquipment_texOb_vec);       break; }
		case TEXTURE::BAK_EQUIPMENT_ID:         { return GetRandomTextureObFromVec(bakEquipment_texOb_vec);         break; }
		case TEXTURE::ENERGIZER_EQUIPMENT_ID: { return GetRandomTextureObFromVec(energyBlockEquipment_texOb_vec); break; }
		case TEXTURE::PROTECTOR_EQUIPMENT_ID:   { return GetRandomTextureObFromVec(protectorEquipment_texOb_vec);   break; }
		case TEXTURE::DROID_EQUIPMENT_ID:       { return GetRandomTextureObFromVec(droidEquipment_texOb_vec);       break; }
		case TEXTURE::FREEZER_EQUIPMENT_ID:     { return GetRandomTextureObFromVec(freezerEquipment_texOb_vec);     break; }
		case TEXTURE::SCANER_EQUIPMENT_ID:      { return GetRandomTextureObFromVec(scanerEquipment_texOb_vec);      break; }
		case TEXTURE::GRAPPLE_EQUIPMENT_ID:     { return GetRandomTextureObFromVec(grappleEquipment_texOb_vec);     break; }

		case TEXTURE::MODULE_ID: { return GetRandomTextureObFromVec(module_texOb_vec);     break; }
																				
		case TEXTURE::TURREL_ID:           { return GetRandomTextureObFromVec(turrel_texOb_vec);               break; }
		case TEXTURE::LAZER_EFFECT_ID:     { return GetRandomTextureObFromVec(lazerEffect_texOb_vec);          break; }
		
		case TEXTURE::NATURELAND_BACKGROUND_ID: { return GetRandomTextureObFromVec(landBg_texOb_vec); break; }
			    			
		case TEXTURE::ANGAR_BACKGROUND_ID:         { return GetRandomTextureObFromVec(angarBg_texOb_vec);              break; }				
		case TEXTURE::STORE_BACKGROUND_ID:         { return GetRandomTextureObFromVec(storeBg_texOb_vec);              break; }	
		case TEXTURE::SHOP_BACKGROUND_ID:          { return GetRandomTextureObFromVec(shopBg_texOb_vec);               break; }	
		case TEXTURE::GOVERMENT_BACKGROUND_ID:     { return GetRandomTextureObFromVec(govermentBg_texOb_vec);          break; }	

		case TEXTURE::SHIELD_EFFECT_ID:    { return GetRandomTextureObFromVec(shieldEffect_texOb_vec);         break; }	
		case TEXTURE::NEBULA_BACKGROUND_ID:           { return GetRandomTextureObFromVec(nebulaBgEffect_texOb_vec);       break; }
		case TEXTURE::DISTANTSTAR_ID:      { return GetRandomTextureObFromVec(starBgEffect_texOb_vec);         break; }				
				
	}
}
		
void TextureManager::FillShipSubTypeList()
{
        if (ship_race0_ranger_texOb_vec.size() != 0)   RaceInformationCollector::Instance().RACE0_ALLOWED_SUBTYPE_vec.push_back(ENTITY::RANGER_ID);
        if (ship_race0_warrior_texOb_vec.size() != 0)  RaceInformationCollector::Instance().RACE0_ALLOWED_SUBTYPE_vec.push_back(ENTITY::WARRIOR_ID);
        if (ship_race0_trader_texOb_vec.size() != 0)   RaceInformationCollector::Instance().RACE0_ALLOWED_SUBTYPE_vec.push_back(ENTITY::TRADER_ID);
        if (ship_race0_pirat_texOb_vec.size() != 0)    RaceInformationCollector::Instance().RACE0_ALLOWED_SUBTYPE_vec.push_back(ENTITY::PIRAT_ID);
        if (ship_race0_diplomat_texOb_vec.size() != 0) RaceInformationCollector::Instance().RACE0_ALLOWED_SUBTYPE_vec.push_back(ENTITY::DIPLOMAT_ID);

        if (ship_race1_ranger_texOb_vec.size() != 0)   RaceInformationCollector::Instance().RACE1_ALLOWED_SUBTYPE_vec.push_back(ENTITY::RANGER_ID);
        if (ship_race1_warrior_texOb_vec.size() != 0)  RaceInformationCollector::Instance().RACE1_ALLOWED_SUBTYPE_vec.push_back(ENTITY::WARRIOR_ID);
        if (ship_race1_trader_texOb_vec.size() != 0)   RaceInformationCollector::Instance().RACE1_ALLOWED_SUBTYPE_vec.push_back(ENTITY::TRADER_ID);
        if (ship_race1_pirat_texOb_vec.size() != 0)    RaceInformationCollector::Instance().RACE1_ALLOWED_SUBTYPE_vec.push_back(ENTITY::PIRAT_ID); 
        if (ship_race1_diplomat_texOb_vec.size() != 0) RaceInformationCollector::Instance().RACE1_ALLOWED_SUBTYPE_vec.push_back(ENTITY::DIPLOMAT_ID);

        if (ship_race2_ranger_texOb_vec.size() != 0)   RaceInformationCollector::Instance().RACE2_ALLOWED_SUBTYPE_vec.push_back(ENTITY::RANGER_ID);
        if (ship_race2_warrior_texOb_vec.size() != 0)  RaceInformationCollector::Instance().RACE2_ALLOWED_SUBTYPE_vec.push_back(ENTITY::WARRIOR_ID);
        if (ship_race2_trader_texOb_vec.size() != 0)   RaceInformationCollector::Instance().RACE2_ALLOWED_SUBTYPE_vec.push_back(ENTITY::TRADER_ID); 
        if (ship_race2_pirat_texOb_vec.size() != 0)    RaceInformationCollector::Instance().RACE2_ALLOWED_SUBTYPE_vec.push_back(ENTITY::PIRAT_ID);
        if (ship_race2_diplomat_texOb_vec.size() != 0) RaceInformationCollector::Instance().RACE2_ALLOWED_SUBTYPE_vec.push_back(ENTITY::DIPLOMAT_ID);
     
        if (ship_race3_ranger_texOb_vec.size() != 0)   RaceInformationCollector::Instance().RACE3_ALLOWED_SUBTYPE_vec.push_back(ENTITY::RANGER_ID);
        if (ship_race3_warrior_texOb_vec.size() != 0)  RaceInformationCollector::Instance().RACE3_ALLOWED_SUBTYPE_vec.push_back(ENTITY::WARRIOR_ID);
        if (ship_race3_trader_texOb_vec.size() != 0)   RaceInformationCollector::Instance().RACE3_ALLOWED_SUBTYPE_vec.push_back(ENTITY::TRADER_ID);
        if (ship_race3_pirat_texOb_vec.size() != 0)    RaceInformationCollector::Instance().RACE3_ALLOWED_SUBTYPE_vec.push_back(ENTITY::PIRAT_ID);
        if (ship_race3_diplomat_texOb_vec.size() != 0) RaceInformationCollector::Instance().RACE3_ALLOWED_SUBTYPE_vec.push_back(ENTITY::DIPLOMAT_ID); 

        if (ship_race4_ranger_texOb_vec.size() != 0)   RaceInformationCollector::Instance().RACE4_ALLOWED_SUBTYPE_vec.push_back(ENTITY::RANGER_ID);
        if (ship_race4_warrior_texOb_vec.size() != 0)  RaceInformationCollector::Instance().RACE4_ALLOWED_SUBTYPE_vec.push_back(ENTITY::WARRIOR_ID); 
        if (ship_race4_trader_texOb_vec.size() != 0)   RaceInformationCollector::Instance().RACE4_ALLOWED_SUBTYPE_vec.push_back(ENTITY::TRADER_ID);
        if (ship_race4_pirat_texOb_vec.size() != 0)    RaceInformationCollector::Instance().RACE4_ALLOWED_SUBTYPE_vec.push_back(ENTITY::PIRAT_ID); 
        if (ship_race4_diplomat_texOb_vec.size() != 0) RaceInformationCollector::Instance().RACE4_ALLOWED_SUBTYPE_vec.push_back(ENTITY::DIPLOMAT_ID);

        if (ship_race6_ranger_texOb_vec.size() != 0)   RaceInformationCollector::Instance().RACE6_ALLOWED_SUBTYPE_vec.push_back(ENTITY::RANGER_ID);
        if (ship_race6_warrior_texOb_vec.size() != 0)  RaceInformationCollector::Instance().RACE6_ALLOWED_SUBTYPE_vec.push_back(ENTITY::WARRIOR_ID);
        if (ship_race6_trader_texOb_vec.size() != 0)   RaceInformationCollector::Instance().RACE6_ALLOWED_SUBTYPE_vec.push_back(ENTITY::TRADER_ID);
        if (ship_race6_pirat_texOb_vec.size() != 0)    RaceInformationCollector::Instance().RACE6_ALLOWED_SUBTYPE_vec.push_back(ENTITY::PIRAT_ID);
        if (ship_race6_diplomat_texOb_vec.size() != 0) RaceInformationCollector::Instance().RACE6_ALLOWED_SUBTYPE_vec.push_back(ENTITY::DIPLOMAT_ID);

        if (ship_race7_ranger_texOb_vec.size() != 0)   RaceInformationCollector::Instance().RACE7_ALLOWED_SUBTYPE_vec.push_back(ENTITY::RANGER_ID); 
        if (ship_race7_warrior_texOb_vec.size() != 0)  RaceInformationCollector::Instance().RACE7_ALLOWED_SUBTYPE_vec.push_back(ENTITY::WARRIOR_ID); 
        if (ship_race7_trader_texOb_vec.size() != 0)   RaceInformationCollector::Instance().RACE7_ALLOWED_SUBTYPE_vec.push_back(ENTITY::TRADER_ID); 
        if (ship_race7_pirat_texOb_vec.size() != 0)    RaceInformationCollector::Instance().RACE7_ALLOWED_SUBTYPE_vec.push_back(ENTITY::PIRAT_ID); 
        if (ship_race7_diplomat_texOb_vec.size() != 0) RaceInformationCollector::Instance().RACE7_ALLOWED_SUBTYPE_vec.push_back(ENTITY::DIPLOMAT_ID);                      
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
		
