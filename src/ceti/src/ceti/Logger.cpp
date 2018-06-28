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
    m_codes.add(Code::GUI);
    //m_codes.add(Code::ANY);
    //m_codes.add(Code::DATA);
    m_codes.add(Code::COMM);
}
        
Logger::~Logger()
{
    m_file.close();
}

void Logger::warn(const std::string& file, const std::string& func, const std::string& msg)
{
    std::string text = "WARNING!!!: "+ msg;
    log(file, func, text);
}

void Logger::error(const std::string& file, const std::string& func, const std::string& msg)
{
    std::string text = "ERROR!!!: "+ msg;
    log(file, func, text);
    throw std::runtime_error(text);
}

void Logger::log(const std::string& file, const std::string& func, const std::string& msg, Code code)
{
//    if (!m_codes.contains(code)) {
//        return;
//    }
    std::string final_msg;
    final_msg += m_sessionInfo;
//    msg2 += file + ": ";
    final_msg += func + ": ";
    final_msg += msg;
    if (m_toFile) {
        toFile(final_msg, code);
    }
    if (m_onScreen) {
        toScreen(final_msg, code);
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

