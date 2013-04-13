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

#ifndef DATE_H
#define DATE_H

#include <string>

class Date
{
	public:
		Date();
		Date(unsigned int, unsigned int, unsigned int);
		~Date();

                void operator=(const Date&);
                		
                bool operator==(const Date&) const;
                bool operator!=(const Date&) const;
                                
                int GetDaysPassSince(const Date&) const;
		//unsigned int GetDay() const { return day; };
		//unsigned int GetMonth() const {return month; };
		//unsigned int GetYear() const {return year; };				

		std::string GetStr() const;

		unsigned int day;
		unsigned int month;
		unsigned int year;
};

#endif
