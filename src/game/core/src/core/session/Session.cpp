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

#include "Session.hpp"

#include <core/manager/DescriptorManager.hpp>
#include <core/manager/EntityManager.hpp>
#include <core/manager/Garbage.hpp>
#include <core/resource/Data.hpp>
#include <core/type/CollectorType.hpp>
#include <core/pilot/Player.hpp>

namespace core {

Session::Session(Type type)
    :
      m_type(type)
    , m_player(new Player(int(type)))
    , m_descriptors(new manager::Descriptors)
    , m_entities(new manager::Entities)
    , m_garbage(new manager::Garbage)
    , m_types(new type::Collector)
{

}

void Session::init(bool save)
{
    Data data(save);
}

} // core
