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

#include "GameDate.hpp"
#include "myStr.hpp"

Date::Date()
{
	day = 0;
	month = 0;
	year = 0;
}

Date::Date(unsigned int day, unsigned int month, unsigned int year)
{
	this->day = day;
	this->month = month;
	this->year = year;
}

Date::~Date()
{}
	
std::string Date::GetStr() const { return "day:" + int2str(day) + " month:" + int2str(month) + " year:" + int2str(year); };


GameDate& GameDate::Instance()
{
	static GameDate instance;
	return instance;
}

GameDate::GameDate()
{}

GameDate::~GameDate()
{}

void GameDate::SetDate(unsigned int day, unsigned int month, unsigned int year)
{
	date.day = day;
	date.month = month;
	date.year = year;	
}

void GameDate::NextDay() 
{
        date.day++;
	if (date.day>=31)
	{
		date.month++;
		date.day = 1;
		if (date.month>=12)
		{
			date.month = 1;
			date.year++;
		}
	}
}
	
					

	

