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


#ifndef GALAXYBUILDER_HPP
#define GALAXYBUILDER_HPP

#include <types/MyInt.hpp>

class Galaxy;
class GalaxyDescription;


class GalaxyBuilder
{
    public:
        static GalaxyBuilder& Instance();
        ~GalaxyBuilder();
        
        Galaxy* GetNewGalaxyTemplate(INTLONGEST id = NONE_ID) const; 
        Galaxy* GetNewGalaxy(const GalaxyDescription&) const; 
                                                
    private:
        GalaxyBuilder() {};
        GalaxyBuilder(const GalaxyBuilder&) = delete;
        GalaxyBuilder& operator=(const GalaxyBuilder&) = delete;
        
        void CreateNewInternals(Galaxy*, const GalaxyDescription&) const;
}; 
    
#endif 
    

        


