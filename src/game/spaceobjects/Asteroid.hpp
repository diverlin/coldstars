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


#ifndef ASTEROID_HPP
#define ASTEROID_HPP

#include <spaceobjects/BasePlanet.hpp>

class Asteroid : public BasePlanet
{
    public:
        Asteroid(int);
        virtual ~Asteroid();

        int GetDamage() const { return GetMass()*10; };

        void UpdateInSpace(int, bool);            
        void CollisionEvent(bool);

        void Render_NEW(const Renderer&, const glm::vec2& scroll_coords);    
        void Render_OLD(const Renderer&);

        virtual void Save(boost::property_tree::ptree&) const override final;
        virtual void Load(const boost::property_tree::ptree&) override final;
        virtual void Resolve() override final;
        
    private:          
        void PostDeathUniqueEvent(bool);

        virtual void UpdateInfo() override final;
        
        void SaveData(boost::property_tree::ptree&, const std::string&) const;        
        void LoadData(const boost::property_tree::ptree&);
        void ResolveData();
}; 

#endif 
