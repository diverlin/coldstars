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

#include <meti/VectorUtils.hpp>
#include <ceti/Orientation.hpp>

#include <vector>

namespace path {

class Path {
public:
    Path()=default;
    ~Path()=default;

    const std::vector<glm::vec3>& centers() const { return m_centers; }
    std::vector<glm::vec3>& centers() { return m_centers; }

    const std::vector<glm::vec3>& directions() const { return m_directions; }
    std::vector<glm::vec3>& directions() { return m_directions; }

    void clear();

    const glm::vec3& center() const;
    const glm::vec3& direction() const;

    void init();
    void update();
    bool isValid() const { return m_isValid; }

private:
    std::vector<glm::vec3> m_centers;
    std::vector<glm::vec3> m_directions;

    int m_it = 0;
    bool m_isValid = false;
};

const float ANGLE_STEP = 0.01f;

float calcRadius(float speed, float angle_step);

bool isReachable(const glm::vec3& from,
                 const glm::vec3& to,
                 float radius,
                 float angle_step);

bool isLookingTowards(const glm::vec3& v1,
                      const glm::vec3& v2);

glm::vec3 rotVec(glm::vec3 orig, glm::vec3 O, float angle);

bool calcDirectPath(std::vector<glm::vec3>& centers,
                    std::vector<glm::vec3>& directions,
                    const glm::vec3& from,
                    const glm::vec3& to,
                    float speed);

bool calcRoundPath(std::vector<glm::vec3>& centers,
                   std::vector<glm::vec3>& directions,
                   const glm::vec3& from,
                   const glm::vec3& to,
                   const glm::vec3& dir,
                   float speed);

bool calcPath(std::vector<glm::vec3>& centers,
              std::vector<glm::vec3>& directions,
              const glm::vec3& from,
              const glm::vec3& to,
              const glm::vec3& dir,
              float speed);

} // namespace path
