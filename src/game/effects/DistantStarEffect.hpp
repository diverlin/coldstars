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


#ifndef DISTANTSTAREFFECT_HPP
#define DISTANTSTAREFFECT_HPP

#include <effects/BaseBackGroundEffect.hpp>    
#include <types/MyInt.hpp>
#include <render/Render.hpp>

const int DISTANT_STAR_MIN = 10000;
const int DISTANT_STAR_MAX = 10000;

class DistantStarEffect : public BaseBackGroundEffect
{   
    public:
        DistantStarEffect(const std::vector<glm::vec3>&, const std::vector<glm::vec4>&);
        ~DistantStarEffect();
        
        void Render(const Renderer&) const;
        
        void Save(boost::property_tree::ptree&, const std::string&) const;        
        void Load(const boost::property_tree::ptree&);
        void Resolve();
    
    private:
        std::vector<glm::vec3> m_Positions;
        std::vector<glm::vec4> m_Colors;

        void SaveData(boost::property_tree::ptree&, const std::string&) const;        
        void LoadData(const boost::property_tree::ptree&);
        void ResolveData();
}; 

DistantStarEffect* GetNewDistantStarEffect(int color_id = NONE_ID);


#endif 
