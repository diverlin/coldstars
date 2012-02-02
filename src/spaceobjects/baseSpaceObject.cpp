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


BaseSpaceObject :: BaseSpaceObject()
{
        angle.x        = getRandInt(10, 40);
        angle.y        = getRandInt(10, 40);
      	angle.z        = 0.0;
      	
      	d_angle.x      = 0.0;
      	d_angle.y      = 0.0;
      	d_angle.z      = getRandInt(10, 100)*0.01;  
                
        place_type_id = NONE_ID;
                        
        starsystem = NULL;
        mesh       = NULL;
        texOb      = NULL;
}


BaseSpaceObject :: ~BaseSpaceObject()
{}


void BaseSpaceObject :: setStarSystem(StarSystem* starsystem)  { this->starsystem = starsystem; }
void BaseSpaceObject :: setIdData(IdData data_id)              { this->data_id = data_id; }
void BaseSpaceObject :: setLifeData(LifeData data_life)        { this->data_life = data_life; }
void BaseSpaceObject :: setMesh(ObjMeshInstance* mesh)         { this->mesh = mesh; }
void BaseSpaceObject :: setTextureOb(TextureOb* texOb)         { this->texOb = texOb; }
void BaseSpaceObject :: setPlaceTypeId(int place_type_id)      { this->place_type_id = place_type_id;  }

void BaseSpaceObject :: setAngle(vec3f angle)                  { this->angle = angle; }
void BaseSpaceObject :: setDeltaAngle(vec3f d_angle)           { this->d_angle = d_angle; }

int BaseSpaceObject :: getId()        const { return data_id.id; }   
int BaseSpaceObject :: getTypeId()    const { return data_id.type_id; }
int BaseSpaceObject :: getSubTypeId() const { return data_id.subtype_id; }

          
int BaseSpaceObject :: getCollisionRadius() const { return collision_radius; }

StarSystem* BaseSpaceObject :: getStarSystem()    { return starsystem; }           
int* BaseSpaceObject :: getpPlaceTypeId() { return &place_type_id; }
int BaseSpaceObject :: getPlaceTypeId() const  { return place_type_id; }
Points* BaseSpaceObject :: getPoints()    { return &points; }
   
bool BaseSpaceObject :: getAlive() const  { return data_life.is_alive; }
bool* BaseSpaceObject :: getpAlive()      { return &data_life.is_alive; }

bool BaseSpaceObject :: getGarbageReady() const  { return data_life.garbage_ready; }             

int BaseSpaceObject :: getMass() const { return mass; }
TextureOb* BaseSpaceObject :: getTexOb() const { return texOb; }
int BaseSpaceObject :: getArmor() const        { return data_life.armor; }
               	

void BaseSpaceObject :: createCenter()
{
	points.initCenterPoint();
	points.addCenterPoint();
}


