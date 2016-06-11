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

#include <descriptors/Base.hpp>

class DescriptorManager;

class DescriptorGenerator {
public:
    DescriptorGenerator();
    ~DescriptorGenerator();

private:
    /* world */
    static descriptor::Base getNewStarsystemDescriptor(int race = -1);

    /* spaceobjects */
    static descriptor::Base getNewStarDescriptor();
    static descriptor::Base getNewPlanetDescriptor();
    static descriptor::Base getNewAsteroidDescriptor();
    static descriptor::Base getNewVehicleDescriptor();
    static descriptor::Base getNewContainerDescriptor();

    /* items */
    static descriptor::Base getNewBakDescriptor(int race = -1, int tech_level = -1);
    static descriptor::Base getNewDriveDescriptor(int race = -1, int tech_level = -1);
    static descriptor::Base getNewDroidDescriptor(int race = -1, int tech_level = -1);
    static descriptor::Base getNewGrappleDescriptor(int race = -1, int tech_level = -1);
    static descriptor::Base getNewScanerDescriptor(int race = -1, int tech_level = -1);
    static descriptor::Base getNewRadarDescriptor(int race = -1, int tech_level = -1);
    static descriptor::Base getNewProtectorDescriptor(int race = -1, int tech_level = -1);
    static descriptor::Base getNewBombDescriptor(int damage = -1, int radius = -1);

    friend DescriptorManager;
};
