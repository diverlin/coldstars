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
#include <MyGl.hpp>
#include <glm/glm.hpp>
 
namespace jeti {

struct Material
{
    int id;
    int w, h;
    int w_slice, h_slice;
    float fps;
    int col_num;
    int row_num;
    int size_id;

    glm::vec4 ambient;
    glm::vec4 diffuse;
    glm::vec4 specular;
    glm::vec4 emission;
    float shininess;

    GLuint texture;
    GLuint normalmap;

    glm::vec2 texture_offset;

    bool is_animated;        
    bool is_loaded;
    bool is_shared;
    bool use_alpha; 

    std::vector<glm::vec2> texCoord_bottomLeft_vec;
    std::vector<glm::vec2> texCoord_bottomRight_vec;
    std::vector<glm::vec2> texCoord_topLeft_vec;
    std::vector<glm::vec2> texCoord_topRight_vec;
    
    std::string texture_path; 
    std::string normalmap_path; 
    
    float brightThreshold;
    int color_id;
    bool is_rotated;

    Material()
    :
    id(0),
    w(1), h(1),
    w_slice(1), h_slice(1),
    fps(0.0f),
    col_num(1),
    row_num(1),    
    size_id(0),
    ambient(0.2f),
    diffuse(1.0f),
    specular(1.5f),
    emission(0.1f),
    shininess(100.0f),
    texture(0),
    normalmap(0),
    is_animated(false),        
    use_alpha(false),
    brightThreshold(1.0f),
    color_id(0),
    is_rotated(false)
    {}    
};

}
