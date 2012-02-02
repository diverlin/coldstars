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


#ifndef BASESPACEOBJECT_H
#define BASESPACEOBJECT_H


class BaseSpaceObject
{
	public:      
   		BaseSpaceObject();
    		~BaseSpaceObject();
                                
                // accessors
                void setStarSystem(StarSystem*);
		void setIdData(IdData);    
		void setLifeData(LifeData);
		void setMesh(ObjMeshInstance*);       	    
		void setTextureOb(TextureOb*);   
		void setPlaceTypeId(int);      
		
		void setAngle(vec3f);
		void setDeltaAngle(vec3f);
		         
                int getId() const;
                int getTypeId() const;
                int getSubTypeId() const;
                int getCollisionRadius() const;

                StarSystem* getStarSystem();
                int getPlaceTypeId() const;
                int* getpPlaceTypeId();
		Points* getPoints();
             
               	bool getAlive() const;
		bool* getpAlive();
               	bool getGarbageReady() const;
               	
               	int getMass() const;
               	TextureOb* getTexOb() const;
               	int getArmor() const;  
               	//
        	
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

               	void createCenter();
};

#endif 
