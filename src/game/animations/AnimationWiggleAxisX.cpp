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

#include "AnimationWiggleAxisX.hpp"
#include <cmath>

AnimationWiggleAxisX::AnimationWiggleAxisX(float step, float threshold):AnimationBase(step), threshold(threshold)
{}

/* virtual */
AnimationWiggleAxisX::~AnimationWiggleAxisX()
{}

/* virtual */
void AnimationWiggleAxisX::Update(vec3f& angle)
{
	if (clockwise)
	{
		angle.x += step;
		if (angle.x > threshold)
		{
			clockwise = false;
		}
	}
	else
	{
		angle.x -= step;
		if (fabs(angle.x) > threshold)
		{
			clockwise = true;
		}		
	}
}
