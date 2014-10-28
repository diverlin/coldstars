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

#include "garbageEffects.hpp"
#include "../effects/lazerTrace.hpp"
#include "../effects/ShockWaveEffect.hpp"
#include "../text/VerticalFlowText.hpp"
#include <render/particlesystem/Particle.hpp>


GarbageEffects::GarbageEffects()
{}

GarbageEffects::~GarbageEffects()
{}
         
         

void GarbageEffects::add(LazerTraceEffect* _effect)
{
    effect_LAZERTRACE_vec.push_back(_effect);
}

void GarbageEffects::add(jeti::BaseParticleSystem* _effect)
{
    effect_PARTICLESYSTEM_vec.push_back(_effect);
}
        
        
void GarbageEffects::add(ShockWaveEffect* _effect)
{
    effect_SHOCKWAVE_vec.push_back(_effect);
}        

void GarbageEffects::add(VerticalFlowText* _text)
{
    text_DAMAGE_vec.push_back(_text);
}

    
        
void GarbageEffects::clear()
{  
        for(unsigned int ei = 0; ei < effect_LAZERTRACE_vec.size(); ei++)
        {
               delete effect_LAZERTRACE_vec[ei];
        }
           effect_LAZERTRACE_vec.clear();
                       
        for(unsigned int i = 0; i < effect_PARTICLESYSTEM_vec.size(); i++)
        {
               delete effect_PARTICLESYSTEM_vec[i];
        }
           effect_PARTICLESYSTEM_vec.clear();
                       
        for(unsigned int ei = 0; ei < effect_SHOCKWAVE_vec.size(); ei++)
        {
               delete effect_SHOCKWAVE_vec[ei];
        }
           effect_SHOCKWAVE_vec.clear();
           
           for(unsigned int ti = 0; ti < text_DAMAGE_vec.size(); ti++)
        {
               delete text_DAMAGE_vec[ti];
        }
           text_DAMAGE_vec.clear();
}
