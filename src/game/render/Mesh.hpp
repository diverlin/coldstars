
#ifndef MESH_HPP
#define MESH_HPP

#include <string>
#include <vector>

#include <glm/glm.hpp>

#include <render/MyGl.hpp>
#include <types/MeshTypes.hpp>

const int VERTECIES_PER_POLYGON_NUM = 3;

const int VERT_POSITION = 0;
const int VERT_TEXCOORD = 1;
const int VERT_NORMAL   = 2;

class ObjLoader;
class TextureOb;

struct Vertex
{
    glm::vec3 position;
    glm::vec2 texcoord;
    glm::vec3 normal;
};

class Mesh
{ 
    public:
        Mesh(const std::string&, TextureOb* textureOb, TYPE::MESH);
        ~Mesh();

        TYPE::MESH GetTypeId() const { return m_TypeId; };
        TextureOb* GetTextureOb() const { return m_TextureOb; };
        const glm::vec3& GetBoundaryBox() const { return m_BoundaryBox; };
                        
        void Draw() const;
    
    private:
        TYPE::MESH m_TypeId;
        GLenum m_PrimitiveType;
        
        TextureOb* m_TextureOb;
        std::vector<Vertex> m_Vertices; 
        glm::vec3 m_BoundaryBox;
    
        uint32_t m_VertexCount;

        GLuint m_ListId;
        GLuint m_VaoId;        
        GLuint m_VboId;
                              
        void BuildFaces(const ObjLoader&);

        void CreateList();      // for debug
        void CreateVbo(); 
                
        void DrawList() const;  // fo debug
        void DrawVbo() const;
};

#endif
