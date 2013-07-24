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


#ifndef PARTICLE_HPP
#define PARTICLE_HPP
 
#include "../../struct/gameStruct.hpp"

class Particle
{
	public:
		Particle(const ParticleData&);       
		~Particle();
		
		void SetPosition(const Vec2<float>& pos) { this->pos = pos; };      		
		void SetVelocity(const Vec2<float>& _velocity) { d_pos = _velocity; };
		
		bool GetAlive()       const { return is_alive; };
		float GetAlpha()      const { return color.a; };
		float GetAlphaStart() const { return data_particle.color_start.a; };
		
		void Reborn();      
		
		void RandomizeLifeTime(float, float);
		void Randomize_d_alpha(float, float);
		
		
		void CalcRandomVelocity();            
		void CalcRandomAccurateVelocity();
		void CalcRandomDirtyVelocity();
		//void calcAccurateRandomVelocity2(Vec2<float>);
		
		void Update();
		void Render() const;
		void Render(float) const;
		void Render(float, float) const;
        		
	private:
		bool is_alive;
		
		Vec2<float> pos;
		Vec2<float> d_pos;
		
		Color4<float> color;
		
		float size;
		
		ParticleData data_particle;
};


#endif 
