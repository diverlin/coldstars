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

#ifndef GAMEDATE_H
#define GAMEDATE_H

#include "Date.hpp"

class GameDate
{
    public:
        static GameDate& Instance();
        ~GameDate();
        
        void SetDate(unsigned int, unsigned int, unsigned int);
        void NextDay();
        const Date& GetDate() const { return date; };
    
        int operator-(const GameDate&) const;
        
    private:
        GameDate();
        GameDate(const GameDate&) = delete;
        GameDate& operator=(const GameDate&) = delete;
        
        std::string GetStr() const;

        Date date;
};

#endif
