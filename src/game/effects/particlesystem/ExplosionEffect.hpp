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


#ifndef EXPLOSIONEFFECT_HPP
#define EXPLOSIONEFFECT_HPP

#include "BaseParticleSystem.hpp"

class ExplosionEffect : public BaseParticleSystem
{ 
    public:
        ExplosionEffect(float);       
        virtual ~ExplosionEffect() override final;
        
        float GetRadius() const { return m_Radius; }

        virtual void Update() override final;
        
        void CreateParticles();

    private:
        float m_Radius;
};  

ExplosionEffect* getNewExplosionEffect(float);
    
#endif 
