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
   
   
#ifndef SPACESTATION_HPP
#define SPACESTATION_HPP

#include <spaceobjects/Vehicle.hpp>
#include <dock/BaseLand.hpp>
   
   
class SpaceStation : public Vehicle
{
    public:  
        SpaceStation(int);
        virtual ~SpaceStation();
            
        BaseLand* const GetLand() const { return m_Land; };
        
        void BindLand(BaseLand* land);
        
        virtual void UpdateInSpace(int, bool) override final;
        
        void RenderInSpace_2D(float);
        void RenderInSpace_3D(const Vec2<float>&, float);         
                
        virtual void SaveData(boost::property_tree::ptree&) const override final;
        virtual void LoadData(const boost::property_tree::ptree&) override final;
        virtual void ResolveData() override final;
            
    private:
        BaseLand* m_Land;

        void UpdateRenderStuff_2D();            
        virtual void UpdateInfo() override final;  
            
        virtual void PutChildsToGarbage() const override final;
            
        void SaveDataUniqueSpaceStation(boost::property_tree::ptree&, const std::string&) const;
        void LoadDataUniqueSpaceStation(const boost::property_tree::ptree&);
        void ResolveDataUniqueSpaceStation();
};


#endif 

