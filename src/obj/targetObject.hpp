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


#ifndef TARGETOBJECT_H
#define TARGETOBJECT_H


class TargetObject
{
	public:	
		TargetObject(ItemSlot*);
		~TargetObject();

                void bindSlot(ItemSlot*);

		template <typename TARGET>
		void setObject(TARGET _target);

		bool getValid() const;
		int getObId() const;
		int getObTypeId() const;
                vec2f* getpCenter();
                bool* getpAlive();
                bool getAlive() const;
                int getObPlaceTypeId() const;
                float getCollisionRadius() const;
                
		Star* getStar();
		Planet* getPlanet();
		Asteroid* getAsteroid();                
                Mineral* getMineral();
                Container* getContainer();
                Ship* getShip();
                Npc* getNpc() const;
                StarSystem* getStarSystem();
                
		void reset();
		void validation();
		
		void moveExternalyToPosition(vec2f);

	private:
		bool is_valid;
		
                int ob_id;
		int ob_type_id;
                
                ItemSlot* slot;

		Star* 	    star;
		Planet*     planet;
                Asteroid*   asteroid;
                Mineral*    mineral;
                Container*  container;
                Ship*       ship;
                Npc*	    npc;
                StarSystem* starsystem;
                                
                vec2f* pCenter;
                bool* pTo_is_alive; 
                int* pTo_place_type_id;
                float collision_radius;

		void set(Star*);
		void set(Planet*);
		void set(Asteroid*);
		void set(Mineral*);
		void set(Container*);
		void set(Ship*);
		void set(Npc*);
		void set(StarSystem*);
						                
                bool checkAvaliability();
                bool checkDistance();
};


#endif
