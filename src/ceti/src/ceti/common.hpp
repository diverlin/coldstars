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

namespace ceti {
       
template <typename T>
inline T getMin(T val1, T val2, T val3)
{
    return std::min(std::min(val1, val2), val3);
}

template <typename T>
int getIndexWithMinVal(const T* array, unsigned int size)
{
    int index_min = 0;
    T val_min = array[index_min];
    for (unsigned int i=1; i<size; i++) {
        if (array[i]<val_min) {
            val_min = array[i];
            index_min = i;
        }
    }
    
    return index_min;
}

} // namespace ceti
