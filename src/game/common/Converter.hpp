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

#ifndef CONVERTER_H
#define CONVERTER_H

#include "../math/Vec2.hpp"
#include <iostream>

template <typename VARTYPE>
class Converter
{
	public:
		Converter(const Vec2<VARTYPE>& in, const Vec2<VARTYPE>& out, float slice_num):
		in(in),
		out(out)
		{					
			in_slice = (in.y-in.x)/slice_num;
			out_slice = (out.y-out.x)/slice_num;
		}
		
		~Converter() {}
		
		VARTYPE GetEquivalent(VARTYPE val) const
		{
			if (val < in.x)
			{
				return out.x;
			}
			else if (val > in.y)
			{
				return out.y;
			}
			else
			{
				float i = (val-in.x)/in_slice;
				return i*out_slice + out.x;
			}
		}
		
	private:
		Vec2<VARTYPE> in;
		Vec2<VARTYPE> out;
		
		float in_slice;
		float out_slice;
};

#endif
