
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

# pragma once

#include <map>
#include <cassert>
#include <string>

#include <common/Base.hpp>
class Player;

class EntityManager
{
    public:
        EntityManager() {}

        void saveRequest() { m_save_request = true; }
        void loadRequest() { m_load_request = true; }
        
        void registerEntity(Base*);
    
        Base* entity(const id_type&) const;
        Player* player() const;

        bool updateSaveRequest();
        bool updateLoadRequest();
        
        void addToGarbage(Base*);
        void clearGarbage();

    private:
        bool m_save_request = false;
        bool m_load_request = false;
        
        std::map<id_type, Base*> m_entities_map;

        std::vector<Base*> m_garbage;

        void removeEntity(Base*);

        void clear();
                
        void saveEvent(const std::string&);
        void loadPass0(const std::string&);
        void loadPass1() const;

};


