
#ifndef MESH_HPP
#define MESH_HPP

#include <string>
#include <vector>

#include <glm/glm.hpp>

#include <render/MyGl.hpp>
#include <types/MeshTypes.hpp>

class ObjLoader;
class TextureOb;

struct MeshVertexData
{
    glm::vec3 position;
    glm::vec2 texcoord;
    glm::vec3 normal;
};

struct MeshFaceData
{
    MeshVertexData vertices[3];
};

class Mesh
{ 
    public:
        Mesh(const std::string&, TextureOb* textureOb, TYPE::MESH);
        ~Mesh();

        TYPE::MESH GetTypeId() const { return type_id; };
        TextureOb* GetTextureOb() const { return textureOb; };
        const glm::vec3& GetBoundaryBox() const { return boundary_box; };
                        
        void Draw() const;
    
    private:
        TYPE::MESH type_id;
        
        TextureOb* textureOb;
        std::vector<MeshFaceData> faces; 
        glm::vec3 boundary_box;

        GLuint glList; 
        GLuint vbo_id;
              
        void BuildFaces(const ObjLoader&);
        void CreateGlList(); 
        void CreateVbo(); 

        void DrawVbo() const;
        void DrawGlList() const;
};

#endif
