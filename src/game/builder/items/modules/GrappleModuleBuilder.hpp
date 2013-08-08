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


#ifndef GRAPPLEMODULEBUILDER_HPP
#define GRAPPLEMODULEBUILDER_HPP

#include <types/MyInt.hpp>

class GrappleModule;


class GrappleModuleBuilder
{
    public:
        static GrappleModuleBuilder& Instance();
        ~GrappleModuleBuilder();

        GrappleModule* GetNewGrappleModuleTemplate(INTLONGEST id = NONE_ID) const; 
        GrappleModule* GetNewGrappleModule(int strength_add = NONE_ID, int radius_add = NONE_ID, int speed_add = NONE_ID) const;
                                     
    private:
        GrappleModuleBuilder() {};
        GrappleModuleBuilder(const GrappleModuleBuilder&) = delete;
        GrappleModuleBuilder& operator=(const GrappleModuleBuilder&) = delete;

        void CreateNewInternals(GrappleModule*, int, int, int) const;
}; 

#endif 
    

        


