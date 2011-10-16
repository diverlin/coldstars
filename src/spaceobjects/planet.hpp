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

class Planet : public CommonForPlanet
{
        public:
                Planet(int _subtype_id, 
                       TextureOb* _texOb, 
                       TextureOb* _texOb_atmoshere, 
                       ObjMeshInstance* _mesh, 
		       PlanetData _planet_data,
		       unsigned long int _population);
    	   
                ~Planet();

                int getDockingRadius() const;
                Kosmoport* getKosmoport();
                Land* getLand();

                bool addShip(Ship*);
                bool addNpc(Npc*);
                
                bool removeShipById(int _id);
                bool removeNpcById(int _id);

                void update_inSpace_inDynamic();
                void update_inSpace_inStatic();

                void updateInfo();
                void renderInfo();

                bool getPermissionToLand() const;
                
        private:
                TextureOb* texOb_atmosphere;

                Kosmoport* kosmoport;
                Land*      land;
                
                unsigned long int population;
                
		void createKosmoport();
                void createLand();
}; 


Planet* createPlanet(int orbit_radius);


#endif 
    

        


