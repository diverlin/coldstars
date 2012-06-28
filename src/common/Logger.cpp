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

Logger& Logger::Instance()
{
	static Logger instance;
	return instance;
}

Logger::~Logger()
{}

void Logger::Log(const std::string& str)
{
	switch(mode)
	{
		case LOG::TOSCREEN:
		{
			ToScreen(str);
			break;
		}
		
		case LOG::TOFILE:
		{
			ToFile(str);
			break;		
		}
		
		case LOG::TOSCREENTOFILE:
		{
			ToScreen(str);
			ToFile(str);
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

}
