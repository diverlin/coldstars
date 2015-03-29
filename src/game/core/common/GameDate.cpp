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

#include "GameDate.hpp"

GameDate::GameDate()
{}

GameDate::GameDate(int day, int month, int year)
    :
      m_day(day)
    , m_month(month)
    , m_year(year)
{
}

GameDate::~GameDate()
{}

void GameDate::set(int day, int month, int year)
{
    m_day = day;
    m_month = month;
    m_year = year;
}

void GameDate::operator=(const GameDate& rhs)
{
    m_day   = rhs.m_day;
    m_month = rhs.m_month;
    m_year  = rhs.m_year;
}

bool GameDate::operator==(const GameDate& rhs) const
{
    return ((m_day == rhs.m_month) && (m_month == rhs.m_month) && (m_year == rhs.m_year));
}

bool GameDate::operator!=(const GameDate& rhs) const
{
    return ((m_day != rhs.m_day) || (m_month != rhs.m_month) || (m_year != rhs.m_year));
}

int GameDate::operator-(const GameDate& rhs) const
{
    int diff_day    = rhs.m_day   - m_day;
    int diff_month  = rhs.m_month - m_month;
    int diff_year   = rhs.m_year  - m_year;

    return abs(diff_day + (diff_month * DAYS_IN_MONTH) + (diff_year * DAYS_IN_YEAR));
}

void GameDate::operator++(int val)
{
    m_day+=val;
    if (m_day>=31) {
        m_month++;
        m_day = 1;
        if (m_month>=12) {
            m_month = 1;
            m_year++;
        }
    }
}

std::string GameDate::str() const { return std::to_string(m_day) + "/" + std::to_string(m_month) + "/" + std::to_string(m_year); };

