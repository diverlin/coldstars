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


#ifndef BASESLOT_HPP
#define BASESLOT_HPP

#include <common/Base.hpp>
#include <types/MyInt.hpp>
#include <glm/glm.hpp>

class Vehicle;

namespace jeti {
class TextureOb;
}

struct UnresolvedDataBaseSlot
{
    UnresolvedDataBaseSlot()
    :
    owner_id(NONE_ID) 
    {}
    
    INTLONGEST owner_id;    
};


class BaseSlot : public Base
{   
    public:        
        BaseSlot();
        virtual ~BaseSlot();
                
        void SetTextureOb(jeti::TextureOb* textureOb) { this->textureOb = textureOb; };
        void SetOwner(Base* owner) { this->owner = owner; };
        void SetPosition(const glm::vec2& position) { this->position = position; };
        void SelectEvent() { selected = true; };
        void DeselectEvent() { selected = false; };
                
        bool GetSelected() const { return selected; };
        
        const glm::vec2& GetPosition() const { return position; };
        
        Vehicle* GetOwnerVehicle() const { return (Vehicle*)owner; };
        Base* GetOwner() const { return owner; };
        
    protected:        
        bool selected;                     
        
        jeti::TextureOb* textureOb;
                        
        Base* owner; 
        
        glm::vec2 position;
     
        UnresolvedDataBaseSlot unresolved_BaseSlot;
        void SaveData(boost::property_tree::ptree&, const std::string&) const;
        void LoadData(const boost::property_tree::ptree&);
        void ResolveData();
}; 

#endif
