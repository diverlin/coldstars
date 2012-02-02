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


#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H


struct UniqueTextureCollector
{
	TextureOb* texOb_module;
	TextureOb* texOb_mark_enemy_ss;	
	TextureOb* texOb_mark_player_ss;
	
	TextureOb* texOb_icon_minus;
	TextureOb* texOb_icon_plus;
	TextureOb* texOb_skill;	

	TextureOb* texOb_icon_map;
        TextureOb* texOb_grapple_trail;	

        TextureOb* texOb_dot_blue;	
        TextureOb* texOb_dot_red;
        TextureOb* texOb_dot_green;
        TextureOb* texOb_dot_black;
        TextureOb* texOb_dot_yellow;
};

class TextureManager
{   
	public:
        	TextureManager();
        	~TextureManager();
        	
        	void manage(TextureOb*);

        	TextureOb* getRandomFaceTexObWithFolloingAttributes(int _race_id);
        	TextureOb* getRandomShipTexObWithFollowingAtrributes(int _race_id, int _subtype_id, int _size_id);

        	TextureOb* getParticleTexObByColorId(int _color_id);
        	
		TextureOb* getRandomTexOb(int);

        	void DEBUG_CheckShipTexOb();
        	
        private:
        	std::vector<TextureOb*> slot_texOb_vec;
        	std::vector<TextureOb*> landingArea_texOb_vec;
        	std::vector<TextureOb*> turrel_texOb_vec;

        	// BACKGROUND 
        	std::vector<TextureOb*> nebulaBgEffect_texOb_vec;
        	std::vector<TextureOb*> starBgEffect_texOb_vec;

          	// BACKGROUND AT PLANET 
          	std::vector<TextureOb*> angarBg_texOb_vec;
          	std::vector<TextureOb*> storeBg_texOb_vec;
          	std::vector<TextureOb*> shopBg_texOb_vec;
          	std::vector<TextureOb*> govermentBg_texOb_vec;
          	std::vector<TextureOb*> landBg_texOb_vec;

        	// PARTICLES
        	std::vector<TextureOb*> particles_texOb_vec;
        	std::vector<TextureOb*> rocketBullet_texOb_vec;
        	std::vector<TextureOb*> lazerEffect_texOb_vec;
        	std::vector<TextureOb*> shieldEffect_texOb_vec;


        	// SPACE OBJECTS
        	std::vector<TextureOb*> spacestation_texOb_vec;
        	std::vector<TextureOb*> satellite_texOb_vec;
        	std::vector<TextureOb*> star_texOb_vec;
        	std::vector<TextureOb*> planet_texOb_vec;
        	std::vector<TextureOb*> atmosphere_texOb_vec;
        	std::vector<TextureOb*> asteroid_texOb_vec;  
        	std::vector<TextureOb*> mineral_texOb_vec;   
        	std::vector<TextureOb*> container_texOb_vec;  
        	std::vector<TextureOb*> bomb_texOb_vec;   
        	std::vector<TextureOb*> blackhole_texOb_vec;  
        	
        	// SHIPS
        	std::vector<TextureOb*> ship_race0_ranger_texOb_vec;
        	std::vector<TextureOb*> ship_race0_warrior_texOb_vec;
        	std::vector<TextureOb*> ship_race0_trader_texOb_vec;
        	std::vector<TextureOb*> ship_race0_pirat_texOb_vec;
        	std::vector<TextureOb*> ship_race0_diplomat_texOb_vec;

        	std::vector<TextureOb*> ship_race1_ranger_texOb_vec;
        	std::vector<TextureOb*> ship_race1_warrior_texOb_vec;
        	std::vector<TextureOb*> ship_race1_trader_texOb_vec;
        	std::vector<TextureOb*> ship_race1_pirat_texOb_vec;
        	std::vector<TextureOb*> ship_race1_diplomat_texOb_vec;

        	std::vector<TextureOb*> ship_race2_ranger_texOb_vec;
        	std::vector<TextureOb*> ship_race2_warrior_texOb_vec;
        	std::vector<TextureOb*> ship_race2_trader_texOb_vec;
        	std::vector<TextureOb*> ship_race2_pirat_texOb_vec;
        	std::vector<TextureOb*> ship_race2_diplomat_texOb_vec;

        	std::vector<TextureOb*> ship_race3_ranger_texOb_vec;
        	std::vector<TextureOb*> ship_race3_warrior_texOb_vec;
        	std::vector<TextureOb*> ship_race3_trader_texOb_vec;
        	std::vector<TextureOb*> ship_race3_pirat_texOb_vec;
        	std::vector<TextureOb*> ship_race3_diplomat_texOb_vec;

        	std::vector<TextureOb*> ship_race4_ranger_texOb_vec;
        	std::vector<TextureOb*> ship_race4_warrior_texOb_vec;
        	std::vector<TextureOb*> ship_race4_trader_texOb_vec;
        	std::vector<TextureOb*> ship_race4_pirat_texOb_vec;
        	std::vector<TextureOb*> ship_race4_diplomat_texOb_vec;

        	std::vector<TextureOb*> ship_race6_ranger_texOb_vec;
        	std::vector<TextureOb*> ship_race6_warrior_texOb_vec;
       		std::vector<TextureOb*> ship_race6_trader_texOb_vec;
        	std::vector<TextureOb*> ship_race6_pirat_texOb_vec;
        	std::vector<TextureOb*> ship_race6_diplomat_texOb_vec;

        	std::vector<TextureOb*> ship_race7_ranger_texOb_vec;
        	std::vector<TextureOb*> ship_race7_warrior_texOb_vec;
        	std::vector<TextureOb*> ship_race7_trader_texOb_vec;
        	std::vector<TextureOb*> ship_race7_pirat_texOb_vec;
        	std::vector<TextureOb*> ship_race7_diplomat_texOb_vec;



        	// ITEMS
        	std::vector<TextureOb*> lazerEquipment_texOb_vec;
        	std::vector<TextureOb*> rocketEquipment_texOb_vec;
        	std::vector<TextureOb*> driveEquipment_texOb_vec;
        	std::vector<TextureOb*> protectorEquipment_texOb_vec;
        	std::vector<TextureOb*> droidEquipment_texOb_vec;
        	std::vector<TextureOb*> grappleEquipment_texOb_vec;
        	std::vector<TextureOb*> bakEquipment_texOb_vec;
        	std::vector<TextureOb*> energyBlockEquipment_texOb_vec;
        	std::vector<TextureOb*> freezerEquipment_texOb_vec;
        	std::vector<TextureOb*> radarEquipment_texOb_vec;
        	std::vector<TextureOb*> scanerEquipment_texOb_vec;

        	// FACE
        	std::vector<TextureOb*> face_race0_texOb_vec;
        	std::vector<TextureOb*> face_race1_texOb_vec;
       		std::vector<TextureOb*> face_race2_texOb_vec;
        	std::vector<TextureOb*> face_race3_texOb_vec;
       		std::vector<TextureOb*> face_race4_texOb_vec;
        	std::vector<TextureOb*> face_race6_texOb_vec;
        	std::vector<TextureOb*> face_race7_texOb_vec;
        	
        	std::vector<TextureOb*> textBackground_texOb_vec;
        	
        	TextureOb* getRandomTexObFromList(std::vector<TextureOb*>*);
       		TextureOb* getShipTexObByClosestSizeFromList(std::vector<TextureOb*>* pTo_list, int _size_id);
        	TextureOb* getShipTexObBySizeFromList(std::vector<TextureOb*>* pTo_list, int _size_id);

};

        


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

#endif 
