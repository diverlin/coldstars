#pragma once

#include <string>
#include <vector>

#include <glm/glm.hpp>

#include <MyGl.hpp>
#include <types/MeshTypes.hpp>

namespace jeti {

class ObjLoader;
class TextureOb;

const int VERTECIES_PER_POLYGON_NUM = 3;

const int VERTEX_POSITION_LOCATION = 0;
const int VERTEX_TEXCOORD_LOCATION = 1;
const int VERTEX_NORMAL_LOCATION   = 2;
const int VERTEX_COLOR_LOCATION    = 3;
                              
const int STRIDE_POSITION = 3;
const int STRIDE_TEXCOORD = 2;
const int STRIDE_NORMAL   = 3;
const int STRIDE_COLOR    = 4;

class Mesh
{ 
    public:
        Mesh(TYPE::MESH, const std::string&, const glm::vec3&, TextureOb*);
        Mesh();
        ~Mesh();

        TYPE::MESH GetTypeId() const { return m_TypeId; }
        TextureOb* GetTextureOb() const { return m_TextureOb; }
        const glm::vec3& GetBoundaryBox() const { return m_BoundaryBox; }
        const glm::vec3& GetOriginDirection() const { return m_OriginDirection; }

        void FillVertices(const ObjLoader&);
        void FillPointVertices(const std::vector<glm::vec3>&, const std::vector<glm::vec4>&, const std::vector<float>&);
        void FillPointVerticesFast(const std::vector<glm::vec3>&, const std::vector<glm::vec4>&, const std::vector<float>&);
                        
        void Draw() const;
        void Draw(GLenum) const;
    
    private:
        struct Vertex
        {
            glm::vec3 position;
            glm::vec2 texcoord;
            glm::vec3 normal;
            glm::vec4 color;
            float size;
        };

        TYPE::MESH m_TypeId;
        GLenum m_PrimitiveType;
        
        TextureOb* m_TextureOb;
        std::vector<Vertex> m_Vertices; 
        glm::vec3 m_BoundaryBox;

        glm::vec3 m_OriginDirection;
    
        uint32_t m_VertexCount;

        GLuint m_ListId;
        GLuint m_VaoId;        
        GLuint m_VboId;

        bool m_HasTexCoords;
        bool m_HasNormals;
        bool m_HasColors;
        bool m_HasPointsSize;

        void UpdateVbo(); 
                
        void DrawVbo() const;
        void DrawVbo(GLenum) const;
};

}

