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

#include <core/Base.hpp>

namespace core {
class RoomDescr;
} // namespace core

namespace model {
class RoomModel;
} // model descriptor

namespace core {
namespace control {

class Kosmoport;

class Room : public Base
{
public:
    Room(RoomDescr*, model::RoomModel*);
    ~Room() = default;

    virtual void putChildrenToGarbage() const {}

    void setKosmoport(Kosmoport* kosmoport) { m_kosmoport = kosmoport; }
//    void setTextureObBackground(jeti::control::Material* textureOb_background) { m_textureOb_background = textureOb_background; }

    Kosmoport* const GetOwnerKosmoport() { return m_kosmoport; }
//    jeti::control::Material* GetBackgroundTextureOb() const { return m_textureOb_background; }

//    void RenderBackground(const ceti::Rect&) const;

protected:
    Kosmoport* m_kosmoport = nullptr;

    RoomDescr* m_descriptor_room = nullptr;
    model::RoomModel* m_model_room = nullptr;

    RoomDescr* descriptor() const { return m_descriptor_room; }
    model::RoomModel* model() const { return m_model_room; }
//    jeti::control::Material* m_textureOb_background = nullptr;

//    UnresolvedDataRoom data_unresolved_Room;
//    void SaveData(boost::property_tree::ptree&, const std::string&) const;
//    void LoadData(const boost::property_tree::ptree&);
//    void ResolveData();
};

} // namespace control
} // namespace core
