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


#ifndef STAR_HPP
#define STAR_HPP

#include <spaceobjects/BaseSpaceEntity.hpp>

glm::vec4 getColor4fById(int);

class Star : public BaseSpaceEntity
{
    public:
        Star(int);
        virtual ~Star();
        
        float GetOffset() const { return m_Offset; }
        int GetColorId() const;
        float GetBrightThreshold() const;
        float GetDeltaColor() const { return m_DeltaColor; }
        
        void Hit(int, bool) {};
        
        void CalcColor();        
        void UpdateInSpaceInStatic();    
        void UpdateInSpace(int, bool);
        void Update();
                
    private:
        float m_Offset;

        float m_DeltaColor;
        
        virtual void PostDeathUniqueEvent(bool) override final;
}; 

Star* GetNewStar();

#endif 
    

        


