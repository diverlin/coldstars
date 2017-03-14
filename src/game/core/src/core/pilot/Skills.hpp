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

#include <boost/property_tree/ptree.hpp>
#include "../common/constants.hpp"
#include <types/RaceTypes.hpp>

class Skills
{ 
public:
    Skills();
    ~Skills();

    void bindStrategy(const int*);

    int availablePoints() const    { return m_availablePoints; }
    int expirience()  const { return m_expirience; }
    int nextLevelExpirience() const { return m_nextlevelExpirience; }
    int level() const { return m_level; }

    float attackNormalized()   const { return m_attack  * SKILLS::ATTACK_NORMALIZED_RATE; }
    float defenceNormalized()  const { return m_defence * SKILLS::DEFENCE_NORMALIZED_RATE; }

    int attack()   const { return m_attack; }
    int defence()  const { return m_defence; }
    int leader()   const { return m_leader; }
    int trader()   const { return m_trader; }
    int technic()  const { return m_technic; }
    int diplomat() const { return m_diplomat; }

    void addExpirience(unsigned long int);

    bool incrementAttack();
    void decrementAttack();

    bool IncrementDefence();
    void DecrementDefence();

    bool IncrementLeader();
    void DecrementLeader();

    bool IncrementTrader();
    void DecrementTrader();

    bool IncrementTechnic();
    void DecrementTechnic();

    bool IncrementDiplomat();
    void DecrementDiplomat();

    void manageAccordingToStrategy();

    void Save(boost::property_tree::ptree&, const std::string&) const;
    void Load(const boost::property_tree::ptree&);
    void Resolve();

private:
    int m_attack = 0;
    int m_defence = 0;
    int m_leader = 0;
    int m_trader = 0;
    int m_technic = 0;
    int m_diplomat = 0;

    int m_availablePoints = 0;
    int m_level = 0;

    unsigned long int m_expirience = 0;
    unsigned long int m_nextlevelExpirience = 0;

    int m_strategy[SKILLS_NUM];

    void __incrementSkillDependingOnArrayIndex(int);
    int __skillDependingOnArrayIndex(int);

    bool __checkLevelUp();
};

const int* getArrayDependingOnClassTypeId(int);
const int* getArrayDependingOnRaceId(race::Type);




