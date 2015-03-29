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


#pragma once

#include <spaceobjects/SpaceObject.hpp>

class ItemSlot;

//namespace jeti {
//class Renderer;
//}

class Container : public SpaceObject
{
    public:                  
        Container(int);
        virtual ~Container();
        
        void SetTargetPos(const glm::vec3& target_pos, float velocity) { m_TargetPos = target_pos; m_Velocity = velocity; }
        void BindItemSlot(ItemSlot*);
        
        ItemSlot* const GetItemSlot() const { return m_ItemSlot; }

//        virtual void RenderInfoInSpace(const jeti::Renderer&, const glm::vec2&, float) override final;
        
        virtual void postDeathUniqueEvent(bool) override final;
            
        void UpdateInSpace(int, bool);

//        void Render(const jeti::Renderer&);
                            
        virtual void Save(boost::property_tree::ptree&) const override final;
        virtual void Load(const boost::property_tree::ptree&) override final;
        virtual void Resolve() override final;
        
    private:
        ItemSlot* m_ItemSlot;        
        
        glm::vec3 m_TargetPos;        
        float m_Velocity;

//        virtual void UpdateInfo() override final;
         
        virtual void putChildrenToGarbage() const override final;
                        
        void SaveData(boost::property_tree::ptree&, const std::string&) const;        
        void LoadData(const boost::property_tree::ptree&);
        void ResolveData();
};

