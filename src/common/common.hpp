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

#ifndef COMMON_H
#define COMMON_H

int randIntInRange(int range_start, int range_end);
int getRandomSign();

struct Color
{
   float r;
   float g;
   float b;
   float a;
};

struct See
{
   bool ASTEROID;
   bool CONTAINER;
   bool MINERAL;

   bool RANGER;
   bool WARRIOR;
   bool TRADER;  
   bool PIRAT;
   bool DIPLOMAT;
};

std :: string returnRaceStringByRaceId(int id);  // replace by generator class

int returnObjectSize(int w, int h);  //size 0...9


float distBetweenCenters(Points* points1, Points* points2);
float distBetweenCenters(Points* points, float x2, float y2);
float distBetweenCenters(float x1, float y1, float x2, float y2);


std::string int2str(int var); 
std::string bool2str(bool var); 

bool get_dX_dY_ToPoint(float x1, float y1, float x2, float y2, float step, float* pTo_dx, float* pTo_dy);
void get_dX_dY_angleInD_ToPoint(float x1, float y1, float x2, float y2, float step, float* pTo_dx, float* pTo_dy, float* pTo_angle_inD);


#endif
