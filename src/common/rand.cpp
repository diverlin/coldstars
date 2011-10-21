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



int getRandInt(int range_start, int range_end)
{
    	if (range_start != range_end)
       		return rand()%(range_end-range_start) + range_start;
   	else
       		return range_start;
}

int getRandSign()
{
  	if (getRandInt(0,10) > 5)
     		return 1;
  	else
     		return -1; 
}

bool getRandBool()
{
  	if (getRandInt(0,10) > 5)
     		return true;
  	else
     		return false; 
}



