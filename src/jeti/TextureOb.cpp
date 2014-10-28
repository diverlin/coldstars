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

#include <SFML/Graphics/Image.hpp>

#include <types/TextureTypes.hpp>

#include <common/IdGenerator.hpp>

namespace jeti {

TextureOb::TextureOb(const Material& data)
    :
      m_IsLoaded(false),
      m_Data(data)
{ 
    m_Data.id = TextureIdGenerator::Instance().GetNextId();
    
    if ( ((m_Data.col_num == 1) and (m_Data.row_num == 1)) or (m_Data.fps == 0) ) {
        m_Data.is_animated = false;
    } else {
        m_Data.is_animated = true;
    }   

    //Load();
    
    CreateTextureCoords(m_Data.col_num, m_Data.row_num, m_Data.fps); 
    
    //m_Data.size_id = getObjectSize(m_Data.w, m_Data.h);
}  

TextureOb::~TextureOb()
{ 

}

void TextureOb::Load()
{
    loadToVRAM(m_Data.texture_path, m_Data.texture, m_Data.w, m_Data.h);
    if (m_Data.normalmap_path != "") {
        loadToVRAM(m_Data.normalmap_path, m_Data.normalmap, m_Data.w, m_Data.h);
    }

    m_IsLoaded = true;
}

void TextureOb::RemoveFromVRAM()
{
    m_IsLoaded = false;
}


void TextureOb::CreateTextureCoords(int col_num, int row_num, int fps)
{
    m_CurrentFrame = 0;
    m_FramesCount = 0;
    
    m_Data.w_slice = m_Data.w/col_num;
    m_Data.h_slice = m_Data.h/row_num;
    
    float w_slicef = (float)m_Data.w_slice/m_Data.w;  
    float h_slicef = (float)m_Data.h_slice/m_Data.h;
    
    float w_offsetf = 0;
    float h_offsetf = 0;

    int r = 0;
    while (r < row_num)
    {
       w_offsetf = 0;
       int c = 0;
       while (c < col_num)
       {
            AddTexCoordQuad(w_offsetf, h_offsetf, w_offsetf + w_slicef, h_offsetf + h_slicef);
            w_offsetf += w_slicef;
            m_FramesCount++;
            c++;
       }
       h_offsetf += h_slicef;
       r++;
    }
    
    m_LastUpdateTime = 0;
    
    if (m_Fps == 0) 
    {
        m_Fps = m_FramesCount*1.3;
    }
    else 
    {
        m_Fps = fps;
    }
    
    m_Delay = 1.f/m_Fps;
}


void TextureOb::AddTexCoordQuad(float w_start, float h_start, float w_end, float h_end)
{
     m_Data.texCoord_bottomLeft_vec.push_back( glm::vec2(w_start, h_start));   // (0, 0)
     m_Data.texCoord_bottomRight_vec.push_back(glm::vec2(w_end,   h_start));   // (1, 0)
     m_Data.texCoord_topLeft_vec.push_back(    glm::vec2(w_start, h_end));     // (0, 1)
     m_Data.texCoord_topRight_vec.push_back(   glm::vec2(w_end,   h_end));     // (1, 1)
}

int TextureOb::UpdateAnimationFrame(float elapsed_time)
{
    if (m_Data.is_animated)
    {
        if (elapsed_time - m_LastUpdateTime > m_Delay)
        {
            m_CurrentFrame++;
            if ( m_CurrentFrame >= m_FramesCount )
            {
                m_CurrentFrame = 0;
            }
            m_LastUpdateTime = elapsed_time;
        }
        return m_CurrentFrame;
    }
    else
    {
        return 0;
    } 
}


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

}




