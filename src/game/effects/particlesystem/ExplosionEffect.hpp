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


#ifndef EXPLOSION_H
#define EXPLOSION_H

#include "BaseParticleSystem.hpp"

class ExplosionSlice : public BaseParticleSystem
{ 
    	public:
       		ExplosionSlice();       
       		virtual ~ExplosionSlice();
		
       		virtual void Update();
       		virtual void Render();
       		
                void CreateParticles();
       	private:

};

class ExplosionEffect : public BaseParticleSystem
{ 
    	public:
       		ExplosionEffect(int);       
       		virtual ~ExplosionEffect();
		
		bool GetObSize() const { return obSize; }
		void Add(ExplosionSlice* explosion_slice) { slice_vec.push_back(explosion_slice); }
		
       		virtual void Update();
       		virtual void Render();
       	private:
       		int obSize;
       		std::vector<ExplosionSlice*> slice_vec;

};


ExplosionEffect* getNewExplosion(int);


#endif 
