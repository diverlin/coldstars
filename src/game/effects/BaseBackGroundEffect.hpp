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

#ifndef BASEBACKGROUNDEFFECT_HPP
#define BASEBACKGROUNDEFFECT_HPP

#include <boost/property_tree/ptree.hpp>
#include "../resources/textureOb.hpp"
#include "../math/myVector.hpp"

class BaseBackGroundEffect
{
    public:
        BaseBackGroundEffect();
        ~BaseBackGroundEffect();
        
        void SetTextureOb(TextureOb* textureOb, const Vec3<float>& scale_factor = Vec3<float>(1.0, 1.0, 1.0));
        
        void SetSize(const Vec3<float>& size)         { this->size = size; }
        void SetCenter(const Vec3<float>& center)        { this->center = center; }
        void SetParallaxRate(float parallax_rate)     { this->parallax_rate = parallax_rate; } 
            
    protected:
        unsigned long int id;
        
        static unsigned long int counter;
        
        TextureOb* textureOb;
        std::string textureOb_path;
        
        Vec3<float> center;
        Vec3<float> size;        
        
        float parallax_rate;
        
        void SaveDataUniqueBaseBackGroundEffect(boost::property_tree::ptree&, const std::string&) const;        
        void LoadDataUniqueBaseBackGroundEffect(const boost::property_tree::ptree&);
        void ResolveDataUniqueBaseBackGroundEffect();
    
};

#endif 

