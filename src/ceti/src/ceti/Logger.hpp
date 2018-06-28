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
//    #define LOG( ... )          Logger::get().log(__VA_ARGS__)
//    #define LOG_DATA( ... )     Logger::get().log(__VA_ARGS__, Logger::Code::DATA)
//    #define LOG_COMM( ... )     Logger::get().log(__VA_ARGS__, Logger::Code::COMM)
    //#define LOG_COMM_DIP1( ... ) Logger::get().log(__VA_ARGS__, Logger::Code::COMM)
//    #define LOG_ERROR( ... )    Logger::get().log_error(__VA_ARGS__)
#else
//    #define LOG( ... )
//    #define LOG_DATA( ... )
//    #define LOG_COMM( ... )
//    #define LOG_COMM_DIP1( ... )
//    #define LOG_ERROR( ... )
#endif

#define USE_LOG_COMMON 0
#define USE_LOG_DATA 0
#define USE_LOG_COMM 1
#define USE_LOG_COMM_DIP1 0
#define USE_LOG_ERROR 0

#define LOG_SET_SESSION_INFO( ... )  Logger::get().setSessionInfo(__VA_ARGS__)

#if USE_LOG_COMMON
    #define LOG( ... )              Logger::get().log(__FILE__, __FUNCTION__, __VA_ARGS__)
#else
    #define LOG( ... )
#endif

#if USE_LOG_DATA
    #define LOG_DATA( ... )         Logger::get().log(__FILE__, __FUNCTION__, __VA_ARGS__, Logger::Code::DATA)
#else
    #define LOG_DATA( ... )
#endif

#if USE_LOG_COMM
    #define LOG_COMM( ... )         Logger::get().log(__FILE__, __FUNCTION__, __VA_ARGS__, Logger::Code::COMM)
#else
    #define LOG_COMM( ... )
#endif

#if USE_LOG_COMM_DIP1
    #define LOG_COMM_DIP1( ... )    Logger::get().log(__FILE__, __FUNCTION__, __VA_ARGS__, Logger::Code::COMM)
#else
    #define LOG_COMM_DIP1( ... )
#endif

#if USE_LOG_ERROR
    #define LOG_ERROR( ... )        Logger::get().log(__FILE__, __FUNCTION__, __VA_ARGS__, Logger::Code::EROR)
#else
    #define LOG_ERROR( ... )
#endif

namespace ceti {

void abort(const std::string& msg = "no info");

} // namespace ceti

class Logger
{
public:
    enum class Code: int { ANY, DATA, COMM, GUI };

    static Logger& get();
    ~Logger();

    void setSessionInfo(const std::string& sessionInfo) { m_sessionInfo = sessionInfo; }

    void log(const std::string& file, const std::string& func, const std::string&, Code code=Code::ANY);
    void warn(const std::string& file, const std::string& func, const std::string&);
    void error(const std::string& file, const std::string& func, const std::string&);

private:
    Logger();
    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;

    ceti::pack<Code> m_codes;
    bool m_onScreen = true;
    bool m_toFile = false;

    std::string m_sessionInfo;
    std::ofstream m_file;

    std::string decorate(std::string) const;

    void toScreen(const std::string&, Code);
    void toFile(const std::string&, Code);
};

