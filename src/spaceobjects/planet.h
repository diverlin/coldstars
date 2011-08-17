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


#ifndef PLANET_H
#define PLANET_H

class Planet
{
  public:
    int id;
    int type_id, subtype_id;

    TextureOb* pTo_texOb;
    TextureOb* pTo_atmosphereTexOb;

    StarSystem* pTo_starsystem;
    Points points;
    ObjMeshInstance* pTo_mesh; 
    GLuint texture;
    
    float orbit_center_x;
    float orbit_center_y;
    int radius;
    float speed;    
    float orbit_fi;
 
    int step;  
    float angle_x;
    float angle_y;
    float angle_z;
        
    float scale;
    float pos_z;

    // !!!!
    float rate;                                            
    int w, h;
    int collision_radius; 
    // !!!!
    

    // INFO 
    std::string info_title_0;
    std::string info_title_1;   std::string info_value_1;
    std::string info_title_2;   std::string info_value_2;
    std::string info_title_3;   std::string info_value_3;
    VEC_pString_type info_title_pList;        
    VEC_pString_type info_value_pList;  
    // 

    VEC_float_type orbit_vector_x;
    VEC_float_type orbit_vector_y;
    int len_orbit_array;
    

    Kosmoport* pTo_kosmoport;
    Land*      pTo_land;
 
    Planet(int _subtype_id, TextureOb* _pTo_texOb, TextureOb* _pTo_atmoshereTexOb, ObjMeshInstance* _pTo_mesh, float _size, float _orbit_center_x, float _orbit_center_y, int _radius, float _speed);
    ~Planet();

    void createKosmoport();
    void createLand();

    bool addShip(Ship* _pTo_ship);
    bool addNpc(Npc* _pTo_npc);
    bool removeShipById(int _id);
    bool removeNpcById(int _id);

    void detailedOrbitFormation();

    void update_inSpace_inDynamic();
         void updatePosition();
    void update_inSpace_inStatic();

    void render_NEW();
    void render_OLD();

    void updateInfo();
    void renderInfo();

    bool getPermissionToLand();
}; 

#endif 
    

        


