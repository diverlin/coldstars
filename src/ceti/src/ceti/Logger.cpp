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
//#include <iostream>
//#include <iomanip>
#include <cassert>
#include <stdexcept>


namespace ceti {

void abort(const std::string& msg) {
    assert(false);
    throw std::runtime_error("ERROR: " + msg + "\nAbort.");
}

} // namespace ceti

//Logger& Logger::Instance()
//{
//    static Logger instance;
//    return instance;
//}

//Logger::Logger()
//{
//    mode = MODE::SCREEN;
//}
        
//Logger::~Logger()
//{
//    file.close();
//}

//void Logger::warn(const std::string& msg, int dip)
//{
//    std::string text = "WARNING!!!: "+ msg;
//    Log(text, dip);
//}

//void Logger::error(const std::string& msg)
//{
//    std::string text = "ERROR!!!: "+ msg;
//    Log(text);
//    throw std::runtime_error(text);
//}

//void Logger::Log(const std::string& msg, int dip)
//{
//    switch(mode)
//    {
//        case MODE::SCREEN: { toScreen(msg, dip); break; }
//        case MODE::FILE: { toFile(msg, dip); break;  }
//        case MODE::SCREENFILE: {
//            toScreen(msg, dip);
//            toFile(msg, dip);
//            break;
//        }
//        case MODE::NONE: { break; }
//    }
//}
            
//void Logger::toScreen(const std::string& msg, int dip)
//{
//    std::cout<<std::setw(dip)<<msg<<std::endl;
//}

//void Logger::toFile(const std::string& msg, int dip)
//{
//    if (!file) {
//        file.open("log.txt");
//    }
//    file<<std::setw(dip)<<msg<<std::endl;
//}

