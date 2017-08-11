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

#include "Path.hpp"

#include <glm/gtx/transform.hpp>


namespace path {

void
Path::add(const glm::vec3& center, const glm::vec3& direction) {
    m_centers.push_back(center);
    m_directions.push_back(direction);
}

void
Path::clear() {
    m_centers.clear();
    m_directions.clear();
    m_it = -1;
}

bool
Path::isValid() const {
    if (m_it == -1 || m_centers.empty() || isCompleted()) {
        return false;
    }
    return true;
}

const glm::vec3&
Path::center() const {
    assert(m_it >= m_centers.size());
    return m_centers[m_it];
}

const glm::vec3&
Path::direction() const {
    assert(m_it >= m_directions.size());
    return m_directions[m_it];
}

void Path::update() {
    if (m_it++ == m_centers.size()) {
        m_isCompelted = true;
    }
}



float calcRadius(float speed, float angle_step) {
    return std::fabs((180*speed)/(M_PI*glm::degrees<float>(angle_step)));
}

bool isReachable(const glm::vec3& from, const glm::vec3& to, float speed, float angle_step) {
    float radius = calcRadius(speed, angle_step);
//    std::cout<<"radius="<<radius<<std::endl;
//    std::cout<<"aradius="<<glm::length(from - to)<<std::endl;
    if (glm::length(to-from) <= 2.01*radius) {
        return false;
    }

    return true;
}

bool isLookingTowards(const glm::vec3& v1, const glm::vec3& v2) {
    float acos = glm::dot(glm::normalize(v1), glm::normalize(v2));
    if (acos <  1.0f - std::fabs(ANGLE_STEP) ) {
        return false;
    }
    return true;
}


bool calcDirectPath(std::vector<glm::vec3>& centers,
                    std::vector<glm::vec3>& directions,
                    const glm::vec3& from,
                    const glm::vec3& to,
                    float speed)
{
    glm::vec3 new_center(from);
    glm::vec3 dir = glm::normalize(to - from);

    while(glm::length(to - new_center) >= speed) {
        new_center += dir * speed;
        centers.push_back(new_center);
        directions.push_back(dir);
    }

    return true;
}


glm::vec3 rotVec(glm::vec3 orig, glm::vec3 O, float angle) {
    glm::mat4 Rm = glm::rotate(angle, glm::vec3(0, 0, 1)); // where x, y, z is axis of rotation (e.g. 0 1 0)
    const auto& t = glm::vec4(orig, 1.0f)-glm::vec4(O,1.0f);
    glm::vec4 new_center_ = Rm*t;
    glm::vec3 new_center = glm::vec3(new_center_) + O;
    return new_center;
}


bool calcRoundPath(std::vector<glm::vec3>& centers,
                   std::vector<glm::vec3>& directions,
                   const glm::vec3& from,
                   const glm::vec3& to,
                   const glm::vec3& dir,
                   float speed)
{
    float angle_step = ANGLE_STEP;
    float radius = calcRadius(speed, angle_step);

    assert(isReachable(from, to, speed, angle_step));

    glm::vec3 up(0,0,1);
    glm::vec3 O1_dir = glm::cross(dir, up);
    glm::vec3 O2_dir = glm::cross(dir, -up);

    glm::vec3 O1(from + O1_dir * radius);
    glm::vec3 O2(from + O2_dir * radius);

    glm::vec3 to_O1(to-O1);
    glm::vec3 to_O2(to-O2);

    glm::vec3 O(O1);
    glm::vec3 to_O(to_O1);

    float diff1 = glm::length(to_O1);
    float diff2 = glm::length(to_O2);
    if (diff2 < diff1) {
        O = O2;
        to_O = to_O2;
    } else {
        angle_step *= -1;
    }

    glm::vec3 target_dir(glm::normalize(to - from));
    target_dir = glm::normalize(target_dir);
    float angle = std::acos(glm::dot(dir, target_dir));

    assert(std::isfinite(angle));

    // local vars
    glm::vec3 new_direction(dir);
    glm::vec3 new_center(from);

    float magic_num = 100.0f;
    while( glm::dot(new_direction, target_dir) < 1.0f - std::fabs(angle_step)/magic_num ) {

        new_direction = rotVec(new_direction, glm::vec3(0,0,0), angle_step);
        new_center = new_center + speed * new_direction;

        target_dir = glm::normalize(to - new_center);

        //std::cout<<"c: "<<meti::to_string(new_center)<<std::endl;
        //std::cout<<"d: "<<meti::to_string(new_direction)<<std::endl;
        //std::cout<<"td: "<<meti::to_string(target_dir)<<std::endl;

        centers.push_back(new_center);
        directions.push_back(new_direction);
    }

    // manual last step
    new_center = new_center + speed * new_direction;
    centers.push_back(new_center);
    directions.push_back(new_direction);

    //std::cout<<"cm: "<<meti::to_string(new_center)<<std::endl;
    //std::cout<<"dm: "<<meti::to_string(new_direction)<<std::endl;

//    glm::vec3 to_(800,800,0);
//    glm::vec3 dir_(glm::normalize(to_ - new_direction));
//    std::cout<<"dir_: "<<meti::to_string(dir_)<<std::endl;
    return true;
}

bool calcPath(std::vector<glm::vec3>& centers,
              std::vector<glm::vec3>& directions,
              const glm::vec3& from,
              const glm::vec3& to,
              const glm::vec3& dir,
              float speed)
{
    bool result = true;

    if (!isReachable(from, to, speed, ANGLE_STEP)) {
        return false;
    }
    if (!isLookingTowards(to-from, dir)) {
        result = calcRoundPath(centers,
                               directions,
                               from,
                               to,
                               dir,
                               speed);
    }

    // move forward to final destanation
    if (result) {
        glm::vec3 from2(from);
        glm::vec3 dir2(dir);
        if (centers.size()) {
            from2 = centers.back();
            dir2 = directions.back();
        }

        assert(isLookingTowards(to-from2, dir2));
        result = calcDirectPath(centers,
                                directions,
                                from2,
                                to,
                                speed);
    }
    return result;
}

} // namespace path
