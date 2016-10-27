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

#include <glm/glm.hpp>

#include <MyGl.hpp>
 
#include <string>
#include <vector>

namespace jeti {

namespace model {

struct Material
{
    int id = 0;
    int w = 1, h = 1;
    int w_slice = 1, h_slice = 1;
    float fps = 0.0f;
    int col_num = 1;
    int row_num = 1;
    int size_id = 0;

    glm::vec4 ambient = glm::vec4(0.2f);
    glm::vec4 diffuse = glm::vec4(1.0f);
    glm::vec4 specular = glm::vec4(1.5f);
    glm::vec4 emission = glm::vec4(0.1f);
    float shininess = 100.0f;

    GLuint texture = 0;
    GLuint normalmap = 0;

    glm::vec2 texture_offset;

    bool is_animated = false;
    bool is_loaded = false;
    bool is_shared = false;
    bool use_alpha = false;

    std::vector<glm::vec2> texCoord_bottomLeft_vec;
    std::vector<glm::vec2> texCoord_bottomRight_vec;
    std::vector<glm::vec2> texCoord_topLeft_vec;
    std::vector<glm::vec2> texCoord_topRight_vec;
    
    std::string texture_path; 
    std::string normalmap_path; 
    
    float brightThreshold = 1.0f;
    int color_id = 0;
    bool is_rotated = 0;
};

} // namespace model

} // namespace jeti
