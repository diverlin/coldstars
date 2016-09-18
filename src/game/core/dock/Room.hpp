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

#include "../common/Base.hpp"
#include <ceti/rect.hpp>

namespace jeti {
class TextureOb;
}

class Kosmoport;

struct UnresolvedDataRoom
{
    std::string textureOb_background_path;
    int owner_kosmoport_id;
};

class Room : public core::Base
{
        public: 
                Room();
                ~Room();
                
                virtual void putChildrenToGarbage() const {};
                
                void SetOwnerKosmoport(Kosmoport* owner_kosmoport) { this->owner_kosmoport = owner_kosmoport; };
                void SetTextureObBackground(jeti::TextureOb* textureOb_background) { this->textureOb_background = textureOb_background; };
                
                Kosmoport* const GetOwnerKosmoport() { return owner_kosmoport; };
                jeti::TextureOb* GetBackgroundTextureOb() const { return textureOb_background; };

                void RenderBackground(const ceti::Rect&) const;
                        
        protected:
            Kosmoport* owner_kosmoport;
                jeti::TextureOb* textureOb_background;
                
                UnresolvedDataRoom data_unresolved_Room;
                void SaveData(boost::property_tree::ptree&, const std::string&) const;        
        void LoadData(const boost::property_tree::ptree&);
        void ResolveData();
};


