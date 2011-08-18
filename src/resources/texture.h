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


#ifndef TEXTURE_H
#define TEXTURE_H

class TextureOb
{
    public:
        // TexOb attributes
        int type_id;
        int subtype_id;   //# warrior/trader and so on
        int mod_id;       // is not used for now
        int race_id;
        int tech_level_id;
        int size_id;      // counting from wxh of sprite
        
        int color_id;     // probably color_rgb will be more usefull
        int color_r;
        int color_g;
        int color_b;
        bool is_rotated;
        
        float brightThreshold;
        //

        int id;

        std::string path;
        bool use_alpha; 
     
        bool is_animated;
        unsigned int frame;
        unsigned int frames_total_num; 
        float last_update_time;
        float delay; 
        float fps;
        VEC_float_type texCoord_bottomLeft_x_list;
        VEC_float_type texCoord_bottomLeft_y_list;
        VEC_float_type texCoord_bottomRight_x_list;
        VEC_float_type texCoord_bottomRight_y_list;
        VEC_float_type texCoord_topLeft_x_list;
        VEC_float_type texCoord_topLeft_y_list;
        VEC_float_type texCoord_topRight_x_list;
        VEC_float_type texCoord_topRight_y_list;

        GLuint texture;
        int w, h;
        int w_slice, h_slice;

        bool is_loaded, is_shared;
        
        TextureOb();
        TextureOb(int _type_id, std::string _path, bool _use_alpha, VEC_int_type* pTo_arg, int _columns_num = 1, int _rows_num = 1, float _fps = 0);

        void loadToVRAM();
             void loadSingleToVRAM();
             void loadSlicedToVRAM();
        void removeFromVRAM();
             void removeSingleFromVRAM();
             void removeSlicedFromVRAM();

        void identifyTextureCoords(int _rows_num, int _columns_num, float _fps);
             void addTexCoordQuad(float _w_start, float _h_start, float _w_offset, float _h_offset);

        int updateAnimationFrame();

        void slotArgManager(VEC_int_type* _pTo_arg);
        void turrelArgManager(VEC_int_type* _pTo_arg);
        // SPACE OBJECTS
        void sputnikArgManager(VEC_int_type* pTo_arg); 
        void shipArgManager(VEC_int_type* pTo_arg); 

        void nebulaArgManager(VEC_int_type* pTo_arg);
        void starArgManager(VEC_int_type* pTo_arg); 
        void planetArgManager(VEC_int_type* pTo_arg);
        void atmosphereArgManager(VEC_int_type* pTo_arg);
        void asteroidArgManager(VEC_int_type* pTo_arg); 
        void mineralArgManager(VEC_int_type* pTo_arg); 
        void containerArgManager(VEC_int_type* pTo_arg); 
        void bombArgManager(VEC_int_type* pTo_arg); 
        void blackholeArgManager(VEC_int_type*pTo_arg); 

        //######### IN KOSMOPORT
        void landBgArgManager(VEC_int_type* pTo_arg);
        void angarBgArgManager(VEC_int_type* pTo_arg);
        void storeBgArgManager(VEC_int_type* pTo_arg);
        void shopBgArgManager(VEC_int_type* pTo_arg);
        void govermentBgArgManager(VEC_int_type* pTo_arg);
        void faceArgManager(VEC_int_type* pTo_arg); 

        // ITEMS
        void DriveEquipmentArgManager(VEC_int_type* pTo_arg); 
        void LazerEquipmentArgManager(VEC_int_type* pTo_arg); 
        void RocketEquipmentArgManager(VEC_int_type* pTo_arg); 
        void ProtectorEquipmentArgManager(VEC_int_type* pTo_arg); 
        void DroidEquipmentArgManager(VEC_int_type* pTo_arg);
        void GrappleEquipmentArgManager(VEC_int_type* pTo_arg); 
        void BakEquipmentArgManager(VEC_int_type* pTo_arg); 
        void energyBlockItemArgManager(VEC_int_type* pTo_arg); 
        void FreezerEquipmentArgManager(VEC_int_type* pTo_arg); 
        void RadarEquipmentArgManager(VEC_int_type* pTo_arg); 
        void ScanerEquipmentArgManager(VEC_int_type* pTo_arg); 

         //# BULLETS
        void rocketBulletArgManager(VEC_int_type* pTo_arg); 
        void torpedBulletArgManager(VEC_int_type* pTo_arg); 
        void particleArgManager(VEC_int_type* pTo_arg); 
        void distStarArgManager(VEC_int_type* pTo_arg); 
        void lazerEffectArgManager(VEC_int_type* pTo_arg); 
        void shieldEffectArgManager(VEC_int_type* pTo_arg); 

};

typedef std::vector<TextureOb*> VEC_pTexOb_type; 













class TextureManager
{   public:
        //VEC_pTexOb_type texOb_pList;
        VEC_pTexOb_type slot_texOb_pList;
        VEC_pTexOb_type turrel_texOb_pList;

        // BACKGROUND 
        VEC_pTexOb_type nebulaBgEffect_texOb_pList;
        VEC_pTexOb_type starBgEffect_texOb_pList;

          // BACKGROUND AT PLANET (KOSMOPORT)
          VEC_pTexOb_type angarBg_texOb_pList;
          VEC_pTexOb_type storeBg_texOb_pList;
          VEC_pTexOb_type shopBg_texOb_pList;
          VEC_pTexOb_type govermentBg_texOb_pList;
          // BACKGROUND AT PLANET (UNINHABITED LAND)
          VEC_pTexOb_type landBg_texOb_pList;

        // PARTICLES
        VEC_pTexOb_type particles_texOb_pList;
        VEC_pTexOb_type rocketBullet_texOb_pList;
        VEC_pTexOb_type lazerEffect_texOb_pList;
        VEC_pTexOb_type shieldEffect_texOb_pList;


        // SPACE OBJECTS
        VEC_pTexOb_type star_texOb_pList;
        VEC_pTexOb_type planet_texOb_pList;
        VEC_pTexOb_type atmosphere_texOb_pList;
        VEC_pTexOb_type asteroid_texOb_pList;  
        VEC_pTexOb_type mineral_texOb_pList;   

        VEC_pTexOb_type container_texOb_pList;  
        VEC_pTexOb_type bomb_texOb_pList;   

        // SHIPS
        VEC_pTexOb_type ship_race0_ranger_texOb_pList;
        VEC_pTexOb_type ship_race0_warrior_texOb_pList;
        VEC_pTexOb_type ship_race0_trader_texOb_pList;
        VEC_pTexOb_type ship_race0_pirat_texOb_pList;
        VEC_pTexOb_type ship_race0_diplomat_texOb_pList;

        VEC_pTexOb_type ship_race1_ranger_texOb_pList;
        VEC_pTexOb_type ship_race1_warrior_texOb_pList;
        VEC_pTexOb_type ship_race1_trader_texOb_pList;
        VEC_pTexOb_type ship_race1_pirat_texOb_pList;
        VEC_pTexOb_type ship_race1_diplomat_texOb_pList;

        VEC_pTexOb_type ship_race2_ranger_texOb_pList;
        VEC_pTexOb_type ship_race2_warrior_texOb_pList;
        VEC_pTexOb_type ship_race2_trader_texOb_pList;
        VEC_pTexOb_type ship_race2_pirat_texOb_pList;
        VEC_pTexOb_type ship_race2_diplomat_texOb_pList;

        VEC_pTexOb_type ship_race3_ranger_texOb_pList;
        VEC_pTexOb_type ship_race3_warrior_texOb_pList;
        VEC_pTexOb_type ship_race3_trader_texOb_pList;
        VEC_pTexOb_type ship_race3_pirat_texOb_pList;
        VEC_pTexOb_type ship_race3_diplomat_texOb_pList;

        VEC_pTexOb_type ship_race4_ranger_texOb_pList;
        VEC_pTexOb_type ship_race4_warrior_texOb_pList;
        VEC_pTexOb_type ship_race4_trader_texOb_pList;
        VEC_pTexOb_type ship_race4_pirat_texOb_pList;
        VEC_pTexOb_type ship_race4_diplomat_texOb_pList;

        VEC_pTexOb_type ship_race6_ranger_texOb_pList;
        VEC_pTexOb_type ship_race6_warrior_texOb_pList;
        VEC_pTexOb_type ship_race6_trader_texOb_pList;
        VEC_pTexOb_type ship_race6_pirat_texOb_pList;
        VEC_pTexOb_type ship_race6_diplomat_texOb_pList;

        VEC_pTexOb_type ship_race7_ranger_texOb_pList;
        VEC_pTexOb_type ship_race7_warrior_texOb_pList;
        VEC_pTexOb_type ship_race7_trader_texOb_pList;
        VEC_pTexOb_type ship_race7_pirat_texOb_pList;
        VEC_pTexOb_type ship_race7_diplomat_texOb_pList;



        // ITEMS
        VEC_pTexOb_type LazerEquipment_texOb_pList;
        VEC_pTexOb_type RocketEquipment_texOb_pList;
        VEC_pTexOb_type DriveEquipment_texOb_pList;
        VEC_pTexOb_type ProtectorEquipment_texOb_pList;
        VEC_pTexOb_type DroidEquipment_texOb_pList;
        VEC_pTexOb_type GrappleEquipment_texOb_pList;
        VEC_pTexOb_type BakEquipment_texOb_pList;
        VEC_pTexOb_type energyBlockItem_texOb_pList;
        VEC_pTexOb_type FreezerEquipment_texOb_pList;
        VEC_pTexOb_type RadarEquipment_texOb_pList;
        VEC_pTexOb_type ScanerEquipment_texOb_pList;

        // FACE
        VEC_pTexOb_type face_race0_texOb_pList;
        VEC_pTexOb_type face_race1_texOb_pList;
        VEC_pTexOb_type face_race2_texOb_pList;
        VEC_pTexOb_type face_race3_texOb_pList;
        VEC_pTexOb_type face_race4_texOb_pList;
        VEC_pTexOb_type face_race6_texOb_pList;
        VEC_pTexOb_type face_race7_texOb_pList;
        VEC_pTexOb_type textBackground_texOb_pList;

        TextureManager();
        void manage(TextureOb* pTo_texOb);
        void manageItem(TextureOb* pTo_texOb);
        void manage_face(TextureOb* pTo_texOb);
        TextureOb* returnPointerToRandomTexObFromList(VEC_pTexOb_type* pTo_list);

        TextureOb* returnPointerToShipTexObByClosestSizeFromList(VEC_pTexOb_type* pTo_list, int _size_id);
        TextureOb* returnPointerToShipTexObBySizeFromList(VEC_pTexOb_type* pTo_list, int _size_id);

        TextureOb* returnPointerToRandomFaceTexObWithFolloingAttributes(int _race_id);
        TextureOb* returnPointerToRandomShipTexObWithFollowingAtrributes(int _race_id, int _subtype_id, int _size_id);


        TextureOb* returnParticleTexObByColorId(int _color_id);

        void DEBUG_CheckShipTexOb();
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
