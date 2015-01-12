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


#ifndef SHOW_HPP
#define SHOW_HPP


class Show
{
    private:
        bool m_AllPath;
        bool m_AllOrbits;
        
        bool m_InfoShips;                
        bool m_RangeRadar;
        bool m_CollisionRadius;
    
    public:
        Show()
        :          
        m_AllPath(false),
        m_AllOrbits(false),                
        m_InfoShips(false),             
        m_RangeRadar(false),
        m_CollisionRadius(false)
        {}
                
        ~Show() {}
                        
        bool GetAllOrbits()    const { return m_AllOrbits; }
        bool GetAllPath()      const { return m_AllPath; }
                
        //bool GetInfoShips()     const { return m_InfoShips; }
        bool GetRangeRadar()     const { return m_RangeRadar; }
        bool collisionRadius()     const { return m_CollisionRadius; }
                        
        void InverseAllPath()         { m_AllPath = !m_AllPath; }
        void InverseAllOrbits()     { m_AllOrbits = !m_AllOrbits; }
        void InverseRangeRadar()     { m_RangeRadar = !m_RangeRadar; }
        void InverseCollisionRadius()     { m_CollisionRadius = !m_CollisionRadius; }
};

#endif 



        
