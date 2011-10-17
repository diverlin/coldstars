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


#ifndef TEXTUREOB_H
#define TEXTUREOB_H

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
        //int color_r;
        //int color_g;
        //int color_b;
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
        std::vector<float> texCoord_bottomLeft_x_list;
        std::vector<float> texCoord_bottomLeft_y_list;
        std::vector<float> texCoord_bottomRight_x_list;
        std::vector<float> texCoord_bottomRight_y_list;
        std::vector<float> texCoord_topLeft_x_list;
        std::vector<float> texCoord_topLeft_y_list;
        std::vector<float> texCoord_topRight_x_list;
        std::vector<float> texCoord_topRight_y_list;

        GLuint texture;
        int w, h;
        int w_slice, h_slice;

        bool is_loaded, is_shared;
        
        TextureOb();
        TextureOb(int _type_id, std::string _path, bool _use_alpha, std::vector<int>* pTo_arg, int _columns_num = 1, int _rows_num = 1, float _fps = 0);

        void loadToVRAM();
             void loadSingleToVRAM();
             void loadSlicedToVRAM();
        void removeFromVRAM();
             void removeSingleFromVRAM();
             void removeSlicedFromVRAM();

        void identifyTextureCoords(int _rows_num, int _columns_num, float _fps);
             void addTexCoordQuad(float _w_start, float _h_start, float _w_offset, float _h_offset);

        int updateAnimationFrame();

        void slotArgManager(std::vector<int>* _pTo_arg);
        void turrelArgManager(std::vector<int>* _pTo_arg);
        // SPACE OBJECTS
        void sputnikArgManager(std::vector<int>* pTo_arg); 
        void shipArgManager(std::vector<int>* pTo_arg); 

        void nebulaArgManager(std::vector<int>* pTo_arg);
        void starArgManager(std::vector<int>* pTo_arg); 
        void planetArgManager(std::vector<int>* pTo_arg);
        void atmosphereArgManager(std::vector<int>* pTo_arg);
        void asteroidArgManager(std::vector<int>* pTo_arg); 
        void mineralArgManager(std::vector<int>* pTo_arg); 
        void containerArgManager(std::vector<int>* pTo_arg); 
        void bombArgManager(std::vector<int>* pTo_arg); 
        void blackholeArgManager(std::vector<int>* pTo_arg); 

        //######### IN KOSMOPORT
        void landBgArgManager(std::vector<int>* pTo_arg);
        void angarBgArgManager(std::vector<int>* pTo_arg);
        void storeBgArgManager(std::vector<int>* pTo_arg);
        void shopBgArgManager(std::vector<int>* pTo_arg);
        void govermentBgArgManager(std::vector<int>* pTo_arg);
        void faceArgManager(std::vector<int>* pTo_arg); 

        // ITEMS
        void DriveEquipmentArgManager(std::vector<int>* pTo_arg); 
        void LazerEquipmentArgManager(std::vector<int>* pTo_arg); 
        void RocketEquipmentArgManager(std::vector<int>* pTo_arg); 
        void ProtectorEquipmentArgManager(std::vector<int>* pTo_arg); 
        void DroidEquipmentArgManager(std::vector<int>* pTo_arg);
        void GrappleEquipmentArgManager(std::vector<int>* pTo_arg); 
        void BakEquipmentArgManager(std::vector<int>* pTo_arg); 
        void energyBlockItemArgManager(std::vector<int>* pTo_arg); 
        void FreezerEquipmentArgManager(std::vector<int>* pTo_arg); 
        void RadarEquipmentArgManager(std::vector<int>* pTo_arg); 
        void ScanerEquipmentArgManager(std::vector<int>* pTo_arg); 

         //# BULLETS
        void rocketBulletArgManager(std::vector<int>* pTo_arg); 
        void torpedBulletArgManager(std::vector<int>* pTo_arg); 
        void particleArgManager(std::vector<int>* pTo_arg); 
        void distStarArgManager(std::vector<int>* pTo_arg); 
        void lazerEffectArgManager(std::vector<int>* pTo_arg); 
        void shieldEffectArgManager(std::vector<int>* pTo_arg); 

};

typedef std::vector<TextureOb*> VEC_pTexOb_type; 



#endif 
