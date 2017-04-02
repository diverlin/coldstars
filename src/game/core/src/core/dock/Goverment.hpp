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

#include "Room.hpp"

namespace descriptor {
class Goverment;
} // namespace descriptor

namespace model {
class Goverment;
} // namespace model

namespace control {

class Goverment : public Room
{
public:
    Goverment(descriptor::Goverment*, model::Goverment*);
    ~Goverment();

//    void SetTextureObFace(jeti::control::Material* textureOb_face) { this->textureOb_face = textureOb_face; };

//    void Save(boost::property_tree::ptree&) const;
//    void Load(const boost::property_tree::ptree&);
//    void Resolve();

private:
    descriptor::Goverment* m_descriptor_goverment = nullptr;
    model::Goverment* m_model_goverment = nullptr;

    descriptor::Goverment* descriptor() const { return m_descriptor_goverment; }
    model::Goverment* model() const { return m_model_goverment; }

//    jeti::control::Material* textureOb_face;

//    void SaveData(boost::property_tree::ptree&, const std::string&) const;
//    void LoadData(const boost::property_tree::ptree&);
//    void ResolveData();
};

} // namespace control
