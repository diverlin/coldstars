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


#ifndef BASEGAMEENTITY_H
#define BASEGAMEENTITY_H


class BaseGameEntity
{
	public:      
   		BaseGameEntity();
    		virtual ~BaseGameEntity();
                                                      
                           
		void setStarSystem(StarSystem* starsystem)  { this->starsystem = starsystem; }
		void setIdData(IdData data_id)              { this->data_id = data_id; }
		void setLifeData(LifeData data_life)        { this->data_life = data_life; }
		void setMesh(ObjMeshInstance* mesh)         { this->mesh = mesh; }
		void setTextureOb(TextureOb* texOb)         { this->texOb = texOb; }
		void setPlaceTypeId(int place_type_id)      { this->place_type_id = place_type_id;  }

		void setAngle(vec3f angle)                  { this->angle = angle; }
		void setDeltaAngle(vec3f d_angle)           { this->d_angle = d_angle; }

		void setParent(BaseGameEntity* parent)     { this->parent = parent; }
       	
		int getId()        const { return data_id.id; }   
		int getTypeId()    const { return data_id.type_id; }
		int getSubTypeId() const { return data_id.subtype_id; }

		StarSystem* getStarSystem() const { return starsystem; }           
		int getPlaceTypeId()        const { return place_type_id; }
		Points& GetPoints()          { return points; }

		int getCollisionRadius() const { return collision_radius; }   
		bool getAlive()          const { return data_life.is_alive; }
		bool getGarbageReady()   const { return data_life.garbage_ready; }             

		int getMass()         const { return mass; }
		TextureOb* getTexOb() const { return texOb; }
		int getArmor()        const { return data_life.armor; }
               	
		BaseGameEntity* getParent() const { return parent; }
               	
                          	
               	void movingByExternalForce(vec2f, float);
               	
               	void hit(int, bool);
        	
        protected:
		vec3f angle, d_angle;
     		
     		float collision_radius;
     		
                IdData data_id;
                LifeData data_life;
                
                TextureOb* texOb;
    		ObjMeshInstance* mesh; 
    
              	StarSystem* starsystem;
     		int place_type_id;
    		Points points;
    		     		              	
              	InfoTable info;
              	
              	int mass;
             	        	
        	BaseGameEntity* parent;

               	void createCenter();
               	void updateRotation();
               	
        	void checkDeath(bool);
        	virtual void postDeathUniqueEvent(bool) = 0;
        	
        friend class BaseVehicleBuilder;
};

#endif 
