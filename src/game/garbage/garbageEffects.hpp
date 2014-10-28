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


#ifndef GARBAGEEFFECTS_H
#define GARBAGEEFFECTS_H

#include <vector>
class LazerTraceEffect; 
class ShockWaveEffect; 

namespace jeti {
class BaseParticleSystem;
}

class VerticalFlowText;

class GarbageEffects
{
    public:
        GarbageEffects();
        ~GarbageEffects();
        
        void add(LazerTraceEffect*);
        void add(jeti::BaseParticleSystem*);
        void add(ShockWaveEffect*);        
        void add(VerticalFlowText*);
        
        void clear();
    
    private:
            std::vector<LazerTraceEffect*>   effect_LAZERTRACE_vec;
            std::vector<jeti::BaseParticleSystem*> effect_PARTICLESYSTEM_vec;
            std::vector<ShockWaveEffect*>    effect_SHOCKWAVE_vec;            
            std::vector<VerticalFlowText*> text_DAMAGE_vec;          
};
             
#endif 
