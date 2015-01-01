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


#include "QuaternionUtils.hpp"

namespace meti {
      
void QuatFromAngleAndAxis(glm::quat& quat, float angle, const glm::vec3& axis)
{
    // Here we calculate the sin( theta / 2) once for optimization
    float result = sin(angle/2.0);

    // Calculate the x, y and z of the quaternion
    quat.x = axis.x * result;
    quat.y = axis.y * result;
    quat.z = axis.z * result;

    // Calcualte the w value by cos( theta / 2 )
    quat.w = cos(angle/2.0);
    
    quat = glm::normalize(quat); 
}



// q*start = dest
void RotationBetweenVectors(glm::quat& quat, const glm::vec3& start, const glm::vec3& dest)
{    
    float cosTheta = glm::dot(start, dest);
    glm::vec3 rotationAxis = glm::cross(start, dest);

    QuatFromAngleAndAxis(quat, acos(cosTheta), rotationAxis);
}

} // namespace meti
