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

#include "TextureOb.hpp"

#include <meti/RandUtils.hpp>

#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics/Color.hpp>

#include <stdexcept>
#include <iostream>

namespace jeti {

namespace {

void loadToVRAM(const std::string& path, GLuint& texture, int& w, int& h)
{
    sf::Image image;
    if (!image.loadFromFile(path)) {
        throw std::runtime_error("FAULT: Not abe to open file:" + path);
    }

    image.flipVertically();

    w = image.getSize().x;
    h = image.getSize().y;

    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, w, h, GL_RGBA, GL_UNSIGNED_BYTE, image.getPixelsPtr());

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
}

void loadToVRAM(GLuint& texture, int& w, int& h)
{
    std::cout<<"gen new loadToVRAM"<<std::endl;
    sf::Image image;
    const sf::Color& color = sf::Color(meti::getRandInt(50, 256),
                                       meti::getRandInt(50, 256),
                                       meti::getRandInt(50, 256));
    image.create(w, h, color);

    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, w, h, GL_RGBA, GL_UNSIGNED_BYTE, image.getPixelsPtr());

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
}

} // namespace

namespace control {

Material::Material()
{
    m_model.id = 0; // fixmeTextureIdGenerator::Instance().GetNextId();

    if ( ((m_model.col_num == 1) and (m_model.row_num == 1)) or (m_model.fps == 0) ) {
        m_model.is_animated = false;
    } else {
        m_model.is_animated = true;
    }

    load();

    __createTextureCoords(m_model.col_num, m_model.row_num, m_model.fps);

    //m_Material.size_id = getObjectSize(m_Data.w, m_Data.h);
}

Material::Material(const model::Material& material)
    :
      m_model(material)
{ 
    m_model.id = 0; // fixmeTextureIdGenerator::Instance().GetNextId();
    
    if ( ((m_model.col_num == 1) && (m_model.row_num == 1)) || (m_model.fps == 0) ) {
        m_model.is_animated = false;
    } else {
        m_model.is_animated = true;
    }

    load();
    
    __createTextureCoords(m_model.col_num, m_model.row_num, m_model.fps);
    
    //m_Material.size_id = getObjectSize(m_Data.w, m_Data.h);
}  

Material::~Material()
{ 

}

void Material::load()
{
    if (m_isLoaded) {
        return;
    }

    if (m_model.texture_path != "") {
        loadToVRAM(m_model.texture_path, m_model.texture, m_model.w, m_model.h);
    } else {
        loadToVRAM(m_model.texture, m_model.w, m_model.h);
    }
    if (m_model.normalmap_path != "") {
        loadToVRAM(m_model.normalmap_path, m_model.normalmap, m_model.w, m_model.h);
    }

    m_isLoaded = true;
}

void Material::unloadFromVRAM()
{
    m_isLoaded = false;
}

void Material::__createTextureCoords(int col_num, int row_num, int fps)
{
    m_currentFrame = 0;
    m_framesCount = 0;
    
    m_model.w_slice = m_model.w/col_num;
    m_model.h_slice = m_model.h/row_num;
    
    float w_slicef = (float)m_model.w_slice/m_model.w;
    float h_slicef = (float)m_model.h_slice/m_model.h;
    
    float w_offsetf = 0;
    float h_offsetf = 0;

    int r = 0;
    while (r < row_num) {
       w_offsetf = 0;
       int c = 0;
       while (c < col_num) {
            __addTexCoordQuad(w_offsetf, h_offsetf, w_offsetf + w_slicef, h_offsetf + h_slicef);
            w_offsetf += w_slicef;
            m_framesCount++;
            c++;
       }
       h_offsetf += h_slicef;
       r++;
    }
    
    m_lastUpdateTime = 0;
    
    if (m_frameNum == 0) {
        m_frameNum = m_framesCount*1.3;
    } else {
        m_frameNum = fps;
    }
    
    m_delay = 1.f/m_frameNum;
}


void Material::__addTexCoordQuad(float w_start, float h_start, float w_end, float h_end)
{
     m_model.texCoord_bottomLeft_vec.push_back( glm::vec2(w_start, h_start));   // (0, 0)
     m_model.texCoord_bottomRight_vec.push_back(glm::vec2(w_end,   h_start));   // (1, 0)
     m_model.texCoord_topLeft_vec.push_back(    glm::vec2(w_start, h_end));     // (0, 1)
     m_model.texCoord_topRight_vec.push_back(   glm::vec2(w_end,   h_end));     // (1, 1)
}

int Material::updateAnimationFrame(float elapsed_time)
{
    if (m_model.is_animated) {
        if (elapsed_time - m_lastUpdateTime > m_delay) {
            m_currentFrame++;
            if ( m_currentFrame >= m_framesCount ) {
                m_currentFrame = 0;
            }
            m_lastUpdateTime = elapsed_time;
        }
        return m_currentFrame;
    } else {
        return 0;
    } 
}

} // namespace control

} // namespace jeti

