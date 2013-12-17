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


#ifndef TEXTUREOB_HPP
#define TEXTUREOB_HPP

#include <string>
#include <vector>
#include <render/MyGl.hpp>
#include <glm/glm.hpp>
 
#include <types/TextureTypes.hpp>
#include <types/RaceTypes.hpp>
#include <types/EntityTypes.hpp>
#include <types/TechLevelTypes.hpp>

struct MaterialData
{
    int id;
    int w, h;
    int w_slice, h_slice;
    float fps;
    int col_num;
    int row_num;
    int size_id;

    glm::vec4 color;

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

    MaterialData()
    :
    id(0),
    w(1), h(1),
    w_slice(1), h_slice(1),
    fps(0.0f),
    col_num(1),
    row_num(1),    
    size_id(0),
    color(1.0f),
    texture(0),
    normalmap(0),
    is_animated(false),        
    use_alpha(false),
    brightThreshold(1.0f),
    color_id(0),
    is_rotated(false)
    {}
    
};

struct MaterialAssociation
{
    TYPE::TEXTURE type_id;
    TYPE::ENTITY subtype_id;   //# warrior/trader and so on
    TYPE::RACE race_id;
    TYPE::TECHLEVEL tech_level_id;

    MaterialAssociation()
    :
    type_id(TYPE::TEXTURE::NONE_ID),
    subtype_id(TYPE::ENTITY::NONE_ID),
    race_id(TYPE::RACE::NONE_ID),
    tech_level_id(TYPE::TECHLEVEL::NONE_ID)
    {}
};


class TextureOb
{
    public:
        TextureOb(const MaterialData& data);
        ~TextureOb();

        const glm::vec3 GetSize() const { return glm::vec3(GetFrameWidth(), GetFrameHeight(), 1.0f); }     // ugly

        int GetFrameWidth() const  { return m_Data.w_slice; }
        int GetFrameHeight() const { return m_Data.h_slice; }
        
        void RemoveFromVRAM();
        
        int UpdateAnimationFrame(float);

        const MaterialData& GetData() const { return m_Data; }
        const MaterialAssociation& GetAssociation() const { return m_Association; }

        //void SetData(const MaterialData& data) { m_Data = data; } 
        void SetAssociation(const MaterialAssociation& association) { m_Association = association; }

    private:
        MaterialAssociation m_Association;
        MaterialData m_Data;

        unsigned int m_CurrentFrame;
        unsigned int m_FramesCount; 
        float m_LastUpdateTime;
        float m_Delay;
        float m_Fps; 
                    
        void CreateTextureCoords(int _rows_num, int _columns_num, int _fps);
        void AddTexCoordQuad(float _w_start, float _h_start, float _w_offset, float _h_offset);
};

void loadToVRAM(const std::string&, GLuint&, int&, int&);
            
#endif 
