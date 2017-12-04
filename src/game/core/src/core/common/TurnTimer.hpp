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

class TurnTimer
{
    static const int TURN_TICKS = 150;
    static const int TURN_AUTODELAY = -50;

public:
    TurnTimer();
    ~TurnTimer();

    bool turnEnded()  const { return m_turnEnded; }
    int ticksLeft() const { return m_ticksLeft; }
    unsigned long int turnCount() const { return m_turnCount; }
    void nextTurn();

    void update(int threshold = TURN_AUTODELAY);
    
private:
    int m_ticksLeft = 0;
    unsigned long int m_turnCount = 0;
    bool m_turnEnded = false;
};


