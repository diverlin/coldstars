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

#ifndef BASEEQUIPMENT_HPP
#define BASEEQUIPMENT_HPP

#include "../BaseItem.hpp"
#include "../modules/BaseModule.hpp"
class AnimationEffect2D;

class BaseEquipment : public BaseItem
{
    public:
        BaseEquipment();
        virtual ~BaseEquipment();
        
        virtual void PutChildsToGarbage() const;
        
        bool InsertModule(BaseModule*);
        
        virtual void Render(const Box2D&, const glm::vec2&, bool draw_text = true);
                            
    protected:
        std::vector<BaseModule*> modules_vec;    // needs for inserted modules drawing
        
        AnimationEffect2D* animation_notfunctioning;
        
        virtual void AddCommonInfo();
        
        void SaveDataUniqueBaseEquipment(boost::property_tree::ptree&, const std::string&) const;
        void LoadDataUniqueBaseEquipment(const boost::property_tree::ptree&);
        void ResolveDataUniqueBaseEquipment();   
};

#endif 
