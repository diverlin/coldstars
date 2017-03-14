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

#include <meti/VectorUtils.hpp>

#include <core/type/EntityTypes.hpp>
#include <core/type/GuiTypes.hpp>

int getObjectSize(int w, int h); 

bool get_dPos_ToPoint(const glm::vec3&, const glm::vec3&, float, glm::vec3&);
bool get_dPos_ToPoint(const glm::vec3&, const glm::vec3&, float, glm::vec3&, float&);

template <typename T>
inline T getMin(T val1, T val2)
{
    if (val1<val2)     return val1;
    else            return val2;
}

template <typename T>
inline T getMax(T val1, T val2)
{
    if (val1>val2)     return val1;
    else        return val2;
}

template <typename T>
inline T getMin(T val1, T val2, T val3)
{
    int min2 = getMin(val1, val2);
    return getMin(min2, val3);
}

glm::vec4 getColor4fById(int);

template <typename T>
int getIndexWithMinVal(const T* array, unsigned int size)
{
    int index_min = 0;
    T val_min = array[index_min];
    for (unsigned int i=1; i<size; i++)
    {
        if (array[i]<val_min)
        {
            val_min = array[i];
            index_min = i;
        }
    }
    
    return index_min;
}


//namespace core {

template <typename T>
bool isEqual(const T& v1, const T& v2)
{
    assert(false);
//    if (!v1.size() == v2.size())
//        return false;

//    auto it1 = v1.begin();
//    auto it2 = v2.begin();

//    while(it1 != v1.end()) {
//        if (**it1 != **it2) {
//            return false;
//        }
//        ++it1;
//        ++it2;
//    }

//    return true;
}

//} // namespace core
