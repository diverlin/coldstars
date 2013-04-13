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
#include "constants.hpp"

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

void Date::operator=(const Date& rhs)
{
        day   = rhs.day;
	month = rhs.month;
	year  = rhs.year;
}
    
bool Date::operator==(const Date& rhs) const
{
        return ((day == rhs.day) and (month == rhs.month) and (year == rhs.year));
}

bool Date::operator!=(const Date& rhs) const
{
        return ((day != rhs.day) or (month != rhs.month) or (year != rhs.year));
}
            
int Date::GetDaysPassSince(const Date& rhs) const
{
	int diff_day   = rhs.day - day;
	int diff_month = rhs.month - month;
	int diff_year = rhs.year - year;
		
	int days = diff_day + (diff_month * DAYSINMONTH) + (diff_year * DAYSINYEAR);
	return days;
}
                            
std::string Date::GetStr() const { return int2str(day) + "/" + int2str(month) + "/" + int2str(year); };

