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

#include <items/BaseItem.hpp>
#include <items/modules/BaseModule.hpp>

namespace jeti {
class AnimationEffect2D;
}

class BaseEquipment : public BaseItem
{
    public:
        BaseEquipment();
        virtual ~BaseEquipment();
        
        virtual void putChildrenToGarbage() const;
        
        bool InsertModule(BaseModule*);
        
        //        virtual void Render(const jeti::Renderer&, const ceti::Box2D&, const glm::vec2&, bool draw_text = true);

    protected:
        std::vector<BaseModule*> modules_vec;    // needs for inserted modules drawing
        
        jeti::AnimationEffect2D* animation_notfunctioning;
        
        virtual void AddCommonInfo();
        
        void SaveData(boost::property_tree::ptree&, const std::string&) const;
        void LoadData(const boost::property_tree::ptree&);
        void ResolveData();
};


