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


#ifndef ROCKETBULLETBUILDER_H
#define ROCKETBULLETBUILDER_H

class RocketBullet;
class BulletData;
#include "../../common/constants.hpp"

class RocketBulletBuilder
{
	public:
		static RocketBulletBuilder& Instance();
		~RocketBulletBuilder();
		
		RocketBullet* GetNewRocketBulletTemplate(unsigned long int id = NONE_ID) const;							
		RocketBullet* GetNewRocketBullet(const BulletData&) const;   
		
		void CreateKorpusGeometry(RocketBullet*) const;   
        	       
        private:
        	RocketBulletBuilder() {};   	
        	RocketBulletBuilder(const RocketBulletBuilder&) = delete; 
        	RocketBulletBuilder& operator=(const RocketBulletBuilder&) = delete;
        	
        	void CreateNewInternals(RocketBullet*, const BulletData&) const; 
}; 


#endif 
    

        


