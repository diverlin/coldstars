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

#include <iomanip>
#include <cassert>
#include <stdexcept>


namespace ceti {

void abort(const std::string& msg) {
    throw std::runtime_error("ERROR: " + msg + "\nAbort.");
}

} // namespace ceti

Logger& Logger::get()
{
    static Logger instance;
    return instance;
}

Logger::Logger()
{
    m_mode = Mode::SCREEN;
    m_codes.add(Code::ANY);
    m_codes.add(Code::DATA);
    m_codes.add(Code::TELEGRAMM);
}
        
Logger::~Logger()
{
    m_file.close();
}

void Logger::warn(const std::string& msg)
{
    std::string text = "WARNING!!!: "+ msg;
    log(text);
}

void Logger::error(const std::string& msg)
{
    std::string text = "ERROR!!!: "+ msg;
    log(text);
    throw std::runtime_error(text);
}

void Logger::log(const std::string& msg, Code code)
{
    if (!m_codes.contains(code)) {
        return;
    }

    switch(m_mode) {
        case Mode::SCREEN: { toScreen(msg, code); break; }
        case Mode::FILE: { toFile(msg, code); break;  }
        case Mode::SCREENFILE: {
            toScreen(msg, code);
            toFile(msg, code);
            break;
        }
        case Mode::NONE: { break; }
    }
}
            
void Logger::toScreen(const std::string& msg, Code code)
{
    std::cout<<std::setw(int(code))<<msg<<std::endl;
}

void Logger::toFile(const std::string& msg, Code code)
{
    if (!m_file) {
        m_file.open("log.txt");
    }
    m_file<<std::setw(int(code))<<msg<<std::endl;
}

