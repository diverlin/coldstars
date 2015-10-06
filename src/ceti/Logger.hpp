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

#pragma once

#include <fstream>
#include <iostream>

#ifdef DEBUG
    #define LOG( ... )          std::cout  << __VA_ARGS__ << std::endl
    #define LOG_ERROR( ... )    std::cout  << __FILE__ << " " << __LINE__ << " " << __VA_ARGS__ << std::endl
#else
    #define LOG( ... )
    #define LOG_ERROR( ... )
#endif

class Logger
{
    public:
        static Logger& Instance();
        ~Logger();
        
        void Log(const std::string&, int dip = 0);
        void warn(const std::string&, int dip = 0);
        void error(const std::string&);

    private:
        Logger();
        Logger(const Logger&) = delete;
        Logger& operator=(const Logger&) = delete;

        enum class MODE: int { NONE=0, SCREEN, FILE, SCREENFILE };
        MODE mode;
        
        std::ofstream file;
        
        void toScreen(const std::string&, int);
        void toFile(const std::string&, int);
}; 

