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
		virtual ~ExplosionSlice() override final;
		
		virtual void Update() override final;
		virtual void Render(float) override final;
		
		void CreateParticles();
	private:

};

class ExplosionEffect : public BaseParticleSystem
{ 
	public:
		ExplosionEffect(float);       
		virtual ~ExplosionEffect() override final;
		
		float GetRadius() const { return radius; }
		void Add(ExplosionSlice* explosion_slice) { slice_vec.push_back(explosion_slice); }
		
		virtual void Update() override final;
		virtual void Render(float) override final;
		
    private:
		float radius;
		std::vector<ExplosionSlice*> slice_vec;

};


ExplosionEffect* getNewExplosionEffect(float);


#endif 
