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

#include <string>

class GameDate
{
    static const int CURRENT_YEAR = 4000;
    static const int DAYS_IN_MONTH = 31;
    static const int MONTH_IN_YEAR = 12;
    static const int DAYS_IN_YEAR = DAYS_IN_MONTH * MONTH_IN_YEAR;
public:
    GameDate();
    GameDate(int, int, int);
    ~GameDate();

    void set(int, int, int);

    void operator=(const GameDate&);
    bool operator==(const GameDate&) const;
    bool operator!=(const GameDate&) const;
    int operator-(const GameDate&) const;

    void dayPass();

    std::string str() const;

private:
    int m_day = 0;
    int m_month = 0;
    int m_year = CURRENT_YEAR;
};


