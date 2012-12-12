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

#include "Logger.hpp"
#include "myStr.hpp"
#include "TurnTimer.hpp"
#include "GameDate.hpp"

Logger& Logger::Instance()
{
	static Logger instance;
	return instance;
}

Logger::Logger():mode(LOG::TOSCREENTOFILE), line_counter(0), turn_counter(-1)
{}
		
Logger::~Logger()
{
	file.close();
}

void Logger::Log(const std::string& str, int dip)
{
	std::string spaces;
	for (int i=0; i<3*dip; i++)
	{
		spaces += " ";
	}
	
	std::string result = int2str(line_counter) + ": " + GameDate::Instance().GetDate().GetStr() + " " + int2str(TurnTimer::Instance().GetTurnTick()) + " " + spaces + str;
	switch(mode)
	{
		case LOG::TOSCREEN:
		{
			ToScreen(result);
			break;
		}
		
		case LOG::TOFILE:
		{
			ToFile(result);
			break;		
		}
		
		case LOG::TOSCREENTOFILE:
		{
			ToScreen(result);
			ToFile(result);
			break;
		}
	
	}
}
  	  	
void Logger::ToScreen(const std::string& str)
{
	std::cout<<str<<std::endl;
}

void Logger::ToFile(const std::string& str)
{
	if (turn_counter != TurnTimer::Instance().GetTurnCounter())
	{
		if (file)
		{
			file.close();
		}
		line_counter = 0;
		turn_counter = TurnTimer::Instance().GetTurnCounter();
		file.open(int2str(turn_counter) + ".log");
	}
	
	line_counter++;
	file<<str<<std::endl;
}

