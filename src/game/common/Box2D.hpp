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

#ifndef BOX2D_HPP
#define BOX2D_HPP

#include <math/Vec2.hpp>
class Rect; //tmp  hack

class Box2D
{  
    public:
        Box2D();
        Box2D(const Vec2<float>&);
        Box2D(const Vec2<float>&, const Vec2<float>&);
        Box2D(const Box2D&);
        Box2D(const Rect&); // depr
        ~Box2D();
        
        void Set(const Box2D&);
        
        void SetCenter(const Vec2<float>& center)    { m_Center = center; } 
        void SetCenter(float x, float y)            { m_Center.Set(x,y); } 
        void SetSize(const Vec2<float>& size)        { m_Size = size; } 
        void SetSize(float x, float y)                { m_Size.Set(x,y); } 
        void SetScale(const Vec2<float>& scale)        { m_Scale = scale; }
        void SetScale(float x, float y)                { m_Scale.Set(x,y); }
        void SetAngle(float angle)                    { m_Angle = angle; }
                
        const Vec2<float>& GetCenter() const    { return m_Center; }                    
        const Vec2<float>& GetSize() const        { return m_Size; }
        const Vec2<float>& GetScale() const        { return m_Scale; }
        float GetAngle() const        { return m_Angle; }
                
        const Vec2<float> GetMiddleTop() const { return m_Center + Vec2<float>(0, m_Size.y/2); }
        
        bool CheckInteraction(const Vec2<float>&) const;    
                                          
    private:
        Vec2<float> m_Center;
        Vec2<float> m_Size;
        Vec2<float> m_Scale;
        
        float m_Angle;
};

#endif 
