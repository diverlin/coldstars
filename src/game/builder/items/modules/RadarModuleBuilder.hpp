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


#ifndef RADARMODULEBUILDER_HPP
#define RADARMODULEBUILDER_HPP

#include <types/MyInt.hpp>

class RadarModule;


class RadarModuleBuilder
{
    public:
        static RadarModuleBuilder& Instance();
        ~RadarModuleBuilder();

        RadarModule* GetNewRadarModuleTemplate(INTLONGEST id = NONE_ID) const; 
        RadarModule* GetNewRadarModule(int radius_add = NONE_ID) const;
                                     
    private:
        RadarModuleBuilder() {};
        RadarModuleBuilder(const RadarModuleBuilder&) = delete;
        RadarModuleBuilder& operator=(const RadarModuleBuilder&) = delete;

        void CreateNewInternals(RadarModule*, int) const;
}; 

#endif 
    

        


