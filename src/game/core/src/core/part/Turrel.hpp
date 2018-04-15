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
#include <core/model/Base.hpp>
#include <ceti/Orientation.hpp>

#include <core/descriptor/part/Turrel.hpp>


namespace core {

class TurrelModel : public ceti::OrientationModel, public BaseModel
{
public:
    TurrelModel(int_t descriptor_id) {
        setDescriptor(descriptor_id);
    }
    ~TurrelModel() {}

private:
};


namespace control {

class Turrel : public ceti::control::Orientation, public Base
{
public:
    Turrel(TurrelDescr* descr, TurrelModel* model)
        :
          ceti::control::Orientation(model)
        , Base(descr, model)
        , m_model_turrel(model)
    {}
    ~Turrel() {}

    TurrelModel* model() const { return m_model_turrel; }

private:
    TurrelModel* m_model_turrel = nullptr;
}; 

} // namespace control
} // namespace core
