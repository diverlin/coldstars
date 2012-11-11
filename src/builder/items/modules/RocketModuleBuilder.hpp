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

#ifndef ROCKETMODULEBUILDER_H
#define ROCKETMODULEBUILDER_H

class RocketModule;
#include "../../../common/constants.hpp"

class RocketModuleBuilder
{
	public:
		static RocketModuleBuilder& Instance();
		~RocketModuleBuilder();

        	RocketModule* GetNewRocketModuleTemplate(int id = NONE_ID) const;
                RocketModule* GetNewRocketModule(int ammo_max_add = NONE_ID, int damage_add = NONE_ID, int radius_add = NONE_ID) const;
        	 		                
        private:
		RocketModuleBuilder() {};
		RocketModuleBuilder(const RocketModuleBuilder&) = delete;
		RocketModuleBuilder& operator=(const RocketModuleBuilder&) = delete;

                void CreateNewInternals(RocketModule*, int, int, int) const;
}; 

#endif 
    

        


