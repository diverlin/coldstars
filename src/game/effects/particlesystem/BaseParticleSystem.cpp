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

#include <cmath>

#include "BaseParticleSystem.hpp"
#include "../../common/rand.hpp"
#include "../../common/constants.hpp"

BaseParticleSystem::BaseParticleSystem():
type_id(NONE_ID),
is_alive(true),
is_dying(false),
parent(nullptr)
{}
 
/* virtual */
BaseParticleSystem::~BaseParticleSystem()
{
	for (unsigned int i=0; i<particles_vec.size(); i++) 
	{
		delete particles_vec[i];
	}
}


