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

#include <ceti/Pack.hpp>

#include <fstream>
#include <iostream>
#include <string>

#ifdef USE_LOG
//    #define LOGs( ... )         std::cout  << __VA_ARGS__ << " "
//    #define LOG( ... )          std::cout  << __VA_ARGS__ << std::endl
//    #define LOG_ERROR( ... )    std::cout  << __FILE__ << " " << __LINE__ << " " << __VA_ARGS__ << std::endl
    #define LOG( ... )          Logger::get().log(__VA_ARGS__)
    #define LOG_ERROR( ... )    Logger::get().log_error(__VA_ARGS__)
#else
    #define LOG( ... )
    #define LOG_ERROR( ... )
#endif

namespace ceti {

void abort(const std::string& msg = "no info");

} // namespace ceti

class Logger
{
public:
    enum class Code: int { ANY, DATA, TELEGRAMM };

    static Logger& get();
    ~Logger();

    void log(const std::string&, Code code=Code::ANY);
    void warn(const std::string&);
    void error(const std::string&);

private:
    enum class Mode: int { NONE=0, SCREEN, FILE, SCREENFILE };

    Logger();
    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;

    ceti::pack<Code> m_codes;
    Mode m_mode;

    std::ofstream m_file;

    void toScreen(const std::string&, Code);
    void toFile(const std::string&, Code);
};

