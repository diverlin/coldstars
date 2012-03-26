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



TextureManager :: TextureManager()
{}

TextureManager :: ~TextureManager()
{}

void TextureManager :: manage(TextureOb* texOb)
{
	switch(texOb->type_id)
	{
	  	case SPACESTATION_TEXTURE_ID: { spacestation_texOb_vec.push_back(texOb);    break; }       
	 	case SATELLITE_TEXTURE_ID:    { satellite_texOb_vec.push_back(texOb);   break; }       
	  		  		
  		case SLOT_TEXTURE_ID:        { slot_texOb_vec.push_back(texOb);        break; }       
    		case LANDINGAREA_TEXTURE_ID: { landingArea_texOb_vec.push_back(texOb); break; }
       		case TURREL_TEXTURE_ID:      { turrel_texOb_vec.push_back(texOb);      break; }

    		case NEBULA_TEXTURE_ID:      { nebulaBgEffect_texOb_vec.push_back(texOb); break; }
    		case STAR_TEXTURE_ID:        { star_texOb_vec.push_back(texOb);           break; } 
		case PLANET_TEXTURE_ID:      { planet_texOb_vec.push_back(texOb);         break; }
		case ATMOSPHERE_TEXTURE_ID:  { atmosphere_texOb_vec.push_back(texOb);     break; }
		case SHIP_TEXTURE_ID:        
		{  
			switch(texOb->race_id) 
			{
        			case RACE::R0:
        			{
        				switch(texOb->subtype_id)
        				{
        					case RANGER_ID:   { ship_race0_ranger_texOb_vec.push_back(texOb);   break; }
        					case WARRIOR_ID:  { ship_race0_warrior_texOb_vec.push_back(texOb);  break; }
           					case TRADER_ID:   { ship_race0_trader_texOb_vec.push_back(texOb);   break; }
           					case PIRAT_ID:    { ship_race0_pirat_texOb_vec.push_back(texOb);    break; }
           					case DIPLOMAT_ID: { ship_race0_diplomat_texOb_vec.push_back(texOb); break; }
        				}
        				
        				break;
        			}
        			

        			case RACE::R1:
        			{
        			         switch(texOb->subtype_id)
        			         {
        			         	case RANGER_ID:   { ship_race1_ranger_texOb_vec.push_back(texOb);   break; }
           					case WARRIOR_ID:  { ship_race1_warrior_texOb_vec.push_back(texOb);  break; }
           					case TRADER_ID:   { ship_race1_trader_texOb_vec.push_back(texOb);   break; }
           					case PIRAT_ID:    { ship_race1_pirat_texOb_vec.push_back(texOb);    break; }
           					case DIPLOMAT_ID: { ship_race1_diplomat_texOb_vec.push_back(texOb); break; }
        				 }
        				 
        				 break;
        			}

        			case RACE::R2:
        			{
        			         switch(texOb->subtype_id)
        			         {
        			         	case RANGER_ID: { ship_race2_ranger_texOb_vec.push_back(texOb); break; }
           					case WARRIOR_ID: { ship_race2_warrior_texOb_vec.push_back(texOb); break; }
           					case TRADER_ID: { ship_race2_trader_texOb_vec.push_back(texOb); break; }
           					case PIRAT_ID:  { ship_race2_pirat_texOb_vec.push_back(texOb);  break; }
           					case DIPLOMAT_ID: { ship_race2_diplomat_texOb_vec.push_back(texOb); break; }
        				 }
        				 
        				 break;
        			}
        			
        			
				case RACE::R3:
				{
					switch(texOb->subtype_id)
					{
						case RANGER_ID:  { ship_race3_ranger_texOb_vec.push_back(texOb);    break; }
           					case WARRIOR_ID: { ship_race3_warrior_texOb_vec.push_back(texOb);   break; }
           					case TRADER_ID:  { ship_race3_trader_texOb_vec.push_back(texOb);    break; }
           					case PIRAT_ID:   { ship_race3_pirat_texOb_vec.push_back(texOb);     break; }
           					case DIPLOMAT_ID: { ship_race3_diplomat_texOb_vec.push_back(texOb); break; }
        				}
        				
        				break;
        			}

        			case RACE::R4:
        			{
        				switch(texOb->subtype_id)
        				{	
        					case RANGER_ID:   { ship_race4_ranger_texOb_vec.push_back(texOb);   break; }
           					case WARRIOR_ID:  { ship_race4_warrior_texOb_vec.push_back(texOb);  break; }
           					case TRADER_ID:   { ship_race4_trader_texOb_vec.push_back(texOb);   break; }
           					case PIRAT_ID:    { ship_race4_pirat_texOb_vec.push_back(texOb);    break; } 
           					case DIPLOMAT_ID: { ship_race4_diplomat_texOb_vec.push_back(texOb); break; }
           				}
           				
           				break;
           			}
			
				case RACE::R6:
				{	
					switch(texOb->subtype_id)
					{
						case RANGER_ID:   { ship_race6_ranger_texOb_vec.push_back(texOb);   break; }
           					case WARRIOR_ID:  { ship_race6_warrior_texOb_vec.push_back(texOb);  break; }
           					case TRADER_ID:   { ship_race6_trader_texOb_vec.push_back(texOb);   break; }
           					case PIRAT_ID:    { ship_race6_pirat_texOb_vec.push_back(texOb);    break; }
           					case DIPLOMAT_ID: { ship_race6_diplomat_texOb_vec.push_back(texOb); break; }
        				}
        				
        				break;
        			}

				case RACE::R7:
				{	
					switch(texOb->subtype_id)
					{
						case RANGER_ID:   { ship_race7_ranger_texOb_vec.push_back(texOb);   break; }
           					case WARRIOR_ID:  { ship_race7_warrior_texOb_vec.push_back(texOb);  break; }
           					case TRADER_ID:   { ship_race7_trader_texOb_vec.push_back(texOb);   break; }
           					case PIRAT_ID:    { ship_race7_pirat_texOb_vec.push_back(texOb);    break; }
           					case DIPLOMAT_ID: { ship_race7_diplomat_texOb_vec.push_back(texOb); break; }
        				}
        				
        				break;
        			}
    			}
    		break;
    		}
    		
		case ROCKET_BULLET_TEXTURE_ID: { rocketBullet_texOb_vec.push_back(texOb); break; }
		case LAZER_EFFECT_TEXTURE_ID:  { lazerEffect_texOb_vec.push_back(texOb);  break; }
		case SHIELD_EFFECT_TEXTURE_ID: { shieldEffect_texOb_vec.push_back(texOb); break; }
		case DISTANTSTAR_TEXTURE_ID:   { starBgEffect_texOb_vec.push_back(texOb); break; }
                case PARTICLE_TEXTURE_ID:      { particles_texOb_vec.push_back(texOb); break; } 

    		// ASTEROIDS/MINERALS
    		case ASTEROID_TEXTURE_ID:  { asteroid_texOb_vec.push_back(texOb);  break; } 
		case MINERAL_TEXTURE_ID:   { mineral_texOb_vec.push_back(texOb);   break; } 
		case CONTAINER_TEXTURE_ID: { container_texOb_vec.push_back(texOb); break; }
		case BOMB_TEXTURE_ID:      { bomb_texOb_vec.push_back(texOb);      break; }

    		case BLACKHOLE_TEXTURE_ID: { blackhole_texOb_vec.push_back(texOb); break; }
       		case TEXT_BACKGROUND_TEXTURE_ID: { textBackground_texOb_vec.push_back(texOb); break; } 

		// LAND
    		case LAND_BG_TEXTURE_ID: { landBg_texOb_vec.push_back(texOb); break; }

		// IN KOSMOPORT
    		case ANGAR_BG_TEXTURE_ID: { angarBg_texOb_vec.push_back(texOb); break; }
		case STORE_BG_TEXTURE_ID: { storeBg_texOb_vec.push_back(texOb); break; }
		case SHOP_BG_TEXTURE_ID:  { shopBg_texOb_vec.push_back(texOb); break; }
		case GOVERMENT_BG_TEXTURE_ID: { govermentBg_texOb_vec.push_back(texOb); break; }
		
		
		// ITEMS
		case ROCKET_ITEM_TEXTURE_ID:      { rocketEquipment_texOb_vec.push_back(texOb);      break; } 
		case LAZER_ITEM_TEXTURE_ID:       { lazerEquipment_texOb_vec.push_back(texOb);       break; } 
		case DRIVE_ITEM_TEXTURE_ID:       { driveEquipment_texOb_vec.push_back(texOb);       break; } 
		case PROTECTOR_ITEM_TEXTURE_ID:   { protectorEquipment_texOb_vec.push_back(texOb);   break; } 
		case DROID_ITEM_TEXTURE_ID:       { droidEquipment_texOb_vec.push_back(texOb);       break; } 
		case GRAPPLE_ITEM_TEXTURE_ID:     { grappleEquipment_texOb_vec.push_back(texOb);     break; } 
		case BAK_ITEM_TEXTURE_ID:         { bakEquipment_texOb_vec.push_back(texOb);         break; } 
		case ENERGYBLOCK_ITEM_TEXTURE_ID: { energyBlockEquipment_texOb_vec.push_back(texOb); break; } 
		case FREEZER_ITEM_TEXTURE_ID:     { freezerEquipment_texOb_vec.push_back(texOb);     break; } 
		case RADAR_ITEM_TEXTURE_ID:       { radarEquipment_texOb_vec.push_back(texOb);       break; } 
		case SCANER_ITEM_TEXTURE_ID:      { scanerEquipment_texOb_vec.push_back(texOb);      break; } 
		
		case FACE_TEXTURE_ID:
		{
			switch(texOb->race_id)
			{
			       	case RACE::R0: { face_race0_texOb_vec.push_back(texOb); break; } 
       				case RACE::R1: { face_race1_texOb_vec.push_back(texOb); break; } 
       				case RACE::R2: { face_race2_texOb_vec.push_back(texOb); break; } 
       				case RACE::R3: { face_race3_texOb_vec.push_back(texOb); break; } 
       				case RACE::R4: { face_race4_texOb_vec.push_back(texOb); break; } 

       				case RACE::R6: { face_race6_texOb_vec.push_back(texOb); break; } 
       				case RACE::R7: { face_race7_texOb_vec.push_back(texOb); break; }   
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
		case RACE::R0: { return getRandomTexObFromList(&face_race0_texOb_vec); }
		case RACE::R1: { return getRandomTexObFromList(&face_race1_texOb_vec); }
		case RACE::R2: { return getRandomTexObFromList(&face_race2_texOb_vec); }
 		case RACE::R3: { return getRandomTexObFromList(&face_race3_texOb_vec); }
		case RACE::R4: { return getRandomTexObFromList(&face_race4_texOb_vec); }
		
		case RACE::R6: { return getRandomTexObFromList(&face_race6_texOb_vec); }
		case RACE::R7: { return getRandomTexObFromList(&face_race7_texOb_vec); }
	}
	
	return NULL;
}



TextureOb* TextureManager :: getRandomShipTexObWithFollowingAtrributes(int _race_id, int _subtype_id, int _size_id)
{
        switch(_race_id)
        {	
        	case RACE::R0:
        	{
                	switch(_subtype_id)
                	{
                		case RANGER_ID:   { return getRandomTexObFromList(&ship_race0_ranger_texOb_vec);   break; }
				case WARRIOR_ID:  { return getRandomTexObFromList(&ship_race0_warrior_texOb_vec);  break; }
 				case TRADER_ID:   { return getRandomTexObFromList(&ship_race0_trader_texOb_vec);   break; }
				case PIRAT_ID:    { return getRandomTexObFromList(&ship_race0_pirat_texOb_vec);    break; }
				case DIPLOMAT_ID: { return getRandomTexObFromList(&ship_race0_diplomat_texOb_vec); break; }
		       }
		       
		       break;
		}

        	case RACE::R1:
        	{
                	switch(_subtype_id)
                	{	
                		case RANGER_ID:   { return getRandomTexObFromList(&ship_race1_ranger_texOb_vec);   break; }
				case WARRIOR_ID:  { return getRandomTexObFromList(&ship_race1_warrior_texOb_vec);  break; } 
				case TRADER_ID:   { return getRandomTexObFromList(&ship_race1_trader_texOb_vec);   break; }
				case PIRAT_ID:    { return getRandomTexObFromList(&ship_race1_pirat_texOb_vec);    break; }
				case DIPLOMAT_ID: { return getRandomTexObFromList(&ship_race1_diplomat_texOb_vec); break; }
			}
			
			break;
		}
		
	        case RACE::R2:
        	{
                	switch(_subtype_id)
                	{	
                		case RANGER_ID:   { return getRandomTexObFromList(&ship_race2_ranger_texOb_vec);   break; }
				case WARRIOR_ID:  { return getRandomTexObFromList(&ship_race2_warrior_texOb_vec);  break; } 
				case TRADER_ID:   { return getRandomTexObFromList(&ship_race2_trader_texOb_vec);   break; }
				case PIRAT_ID:    { return getRandomTexObFromList(&ship_race2_pirat_texOb_vec);    break; }
				case DIPLOMAT_ID: { return getRandomTexObFromList(&ship_race2_diplomat_texOb_vec); break; }
			}
			
			break;
        	}
      

    	        case RACE::R3:
        	{
                	switch(_subtype_id)
                	{	
                		case RANGER_ID:   { return getRandomTexObFromList(&ship_race3_ranger_texOb_vec);   break; }
				case WARRIOR_ID:  { return getRandomTexObFromList(&ship_race3_warrior_texOb_vec);  break; } 
				case TRADER_ID:   { return getRandomTexObFromList(&ship_race3_trader_texOb_vec);   break; }
				case PIRAT_ID:    { return getRandomTexObFromList(&ship_race3_pirat_texOb_vec);    break; }
				case DIPLOMAT_ID: { return getRandomTexObFromList(&ship_race3_diplomat_texOb_vec); break; }
			}
			
			break;
        	}


    	        case RACE::R4:
        	{
                	switch(_subtype_id)
                	{	
                		case RANGER_ID:   { return getRandomTexObFromList(&ship_race4_ranger_texOb_vec);   break; }
				case WARRIOR_ID:  { return getRandomTexObFromList(&ship_race4_warrior_texOb_vec);  break; } 
				case TRADER_ID:   { return getRandomTexObFromList(&ship_race4_trader_texOb_vec);   break; }
				case PIRAT_ID:    { return getRandomTexObFromList(&ship_race4_pirat_texOb_vec);    break; }
				case DIPLOMAT_ID: { return getRandomTexObFromList(&ship_race4_diplomat_texOb_vec); break; }
			}
			
			break;
        	}


	        case RACE::R6:
        	{
                	switch(_subtype_id)
                	{	
                		case RANGER_ID:   { return getRandomTexObFromList(&ship_race6_ranger_texOb_vec);   break; }
				case WARRIOR_ID:  { return getRandomTexObFromList(&ship_race6_warrior_texOb_vec);  break; } 
				case TRADER_ID:   { return getRandomTexObFromList(&ship_race6_trader_texOb_vec);   break; }
				case PIRAT_ID:    { return getRandomTexObFromList(&ship_race6_pirat_texOb_vec);    break; }
				case DIPLOMAT_ID: { return getRandomTexObFromList(&ship_race6_diplomat_texOb_vec); break; }
			}
			
			break;
        	}

       	        case RACE::R7:
        	{
                	switch(_subtype_id)
                	{	
                		case RANGER_ID:   { return getRandomTexObFromList(&ship_race7_ranger_texOb_vec);   break; }
				case WARRIOR_ID:  { return getRandomTexObFromList(&ship_race7_warrior_texOb_vec);  break; } 
				case TRADER_ID:   { return getRandomTexObFromList(&ship_race7_trader_texOb_vec);   break; }
				case PIRAT_ID:    { return getRandomTexObFromList(&ship_race7_pirat_texOb_vec);    break; }
				case DIPLOMAT_ID: { return getRandomTexObFromList(&ship_race7_diplomat_texOb_vec); break; }
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
		case PARTICLE_TEXTURE_ID:    { requested_vec = &particles_texOb_vec;      break; }
		case DISTANTSTAR_TEXTURE_ID: { requested_vec = &starBgEffect_texOb_vec;   break; }
		case NEBULA_TEXTURE_ID:      { requested_vec = &nebulaBgEffect_texOb_vec; break; }
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
		case SPACESTATION_TEXTURE_ID:     { return getRandomTexObFromList(&spacestation_texOb_vec);             break; }
		case SATELLITE_TEXTURE_ID:        { return getRandomTexObFromList(&satellite_texOb_vec);            break; }
					
		case SLOT_TEXTURE_ID:             { return getRandomTexObFromList(&slot_texOb_vec);                 break; }
		case CONTAINER_TEXTURE_ID:        { return getRandomTexObFromList(&container_texOb_vec);            break; }
		case STAR_TEXTURE_ID:             { return getRandomTexObFromList(&star_texOb_vec);                 break; }
		case PLANET_TEXTURE_ID:           { return getRandomTexObFromList(&planet_texOb_vec);               break; }
		case ATMOSPHERE_TEXTURE_ID:       { return getRandomTexObFromList(&atmosphere_texOb_vec);           break; }
		case ASTEROID_TEXTURE_ID:         { return getRandomTexObFromList(&asteroid_texOb_vec);             break; }
		case MINERAL_TEXTURE_ID:          { return getRandomTexObFromList(&mineral_texOb_vec);              break; }
		case BOMB_TEXTURE_ID:             { return getRandomTexObFromList(&bomb_texOb_vec);                 break; }
		case BLACKHOLE_TEXTURE_ID:        { return getRandomTexObFromList(&blackhole_texOb_vec);            break; }
		case ROCKET_BULLET_TEXTURE_ID:    { return getRandomTexObFromList(&rocketBullet_texOb_vec);         break; }

		case ROCKET_ITEM_TEXTURE_ID:      { return getRandomTexObFromList(&rocketEquipment_texOb_vec);      break; }
		case LAZER_ITEM_TEXTURE_ID:       { return getRandomTexObFromList(&lazerEquipment_texOb_vec);       break; }
		case RADAR_ITEM_TEXTURE_ID:       { return getRandomTexObFromList(&radarEquipment_texOb_vec);       break; }
		case DRIVE_ITEM_TEXTURE_ID:       { return getRandomTexObFromList(&driveEquipment_texOb_vec);       break; }
		case BAK_ITEM_TEXTURE_ID:         { return getRandomTexObFromList(&bakEquipment_texOb_vec);         break; }
		case ENERGYBLOCK_ITEM_TEXTURE_ID: { return getRandomTexObFromList(&energyBlockEquipment_texOb_vec); break; }
		case PROTECTOR_ITEM_TEXTURE_ID:   { return getRandomTexObFromList(&protectorEquipment_texOb_vec);   break; }
		case DROID_ITEM_TEXTURE_ID:       { return getRandomTexObFromList(&droidEquipment_texOb_vec);       break; }
		case FREEZER_ITEM_TEXTURE_ID:     { return getRandomTexObFromList(&freezerEquipment_texOb_vec);     break; }
		case SCANER_ITEM_TEXTURE_ID:      { return getRandomTexObFromList(&scanerEquipment_texOb_vec);      break; }
		case GRAPPLE_ITEM_TEXTURE_ID:     { return getRandomTexObFromList(&grappleEquipment_texOb_vec);     break; }
																		
		case TURREL_TEXTURE_ID:           { return getRandomTexObFromList(&turrel_texOb_vec);               break; }
		case LAZER_EFFECT_TEXTURE_ID:     { return getRandomTexObFromList(&lazerEffect_texOb_vec);          break; }
		case LANDINGAREA_TEXTURE_ID:      { return getRandomTexObFromList(&landingArea_texOb_vec);          break; }
				
		case ANGAR_BG_TEXTURE_ID:         { return getRandomTexObFromList(&angarBg_texOb_vec);              break; }				
		case STORE_BG_TEXTURE_ID:         { return getRandomTexObFromList(&storeBg_texOb_vec);              break; }	
		case SHOP_BG_TEXTURE_ID:          { return getRandomTexObFromList(&shopBg_texOb_vec);               break; }	
		case GOVERMENT_BG_TEXTURE_ID:     { return getRandomTexObFromList(&govermentBg_texOb_vec);          break; }	

		case TEXT_BACKGROUND_TEXTURE_ID:  { return getRandomTexObFromList(&textBackground_texOb_vec);       break; }			

		case SHIELD_EFFECT_TEXTURE_ID:    { return getRandomTexObFromList(&shieldEffect_texOb_vec);         break; }	
		case NEBULA_TEXTURE_ID:           { return getRandomTexObFromList(&nebulaBgEffect_texOb_vec);       break; }
		case DISTANTSTAR_TEXTURE_ID:      { return getRandomTexObFromList(&starBgEffect_texOb_vec);         break; }				
				
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


