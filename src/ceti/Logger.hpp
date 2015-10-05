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

const int GRAPPLE_QUEUE_LOG_DIP = 1;
const int DRIVECOMPLEX_LOG_DIP = 1;
const int WEAPONSTARGET_LOG_DIP = 1;
const int ENTITY_TRANSACTION_LOG_DIP = 1;
const int AISCENARIO_LOG_DIP = 2;
const int AI_LOG_DIP = 2;
const int SAVELOAD_LOG_DIP = 1;
const int CREATEDESTROY_LOG_DIP = 0;
const int ITEMINFLUENCE_LOG_DIP = 2;
const int TEXTURE_MANAGER_LOG_DIP = 0;
const int GUI_LOG_DIP = 0;
const int GOD_LOG_DIP = 0;
const int OBJLOADER_LOG_DIP = 0;

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

