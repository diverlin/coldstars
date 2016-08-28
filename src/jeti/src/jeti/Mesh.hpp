#pragma once

#include <MyGl.hpp>

#include <glm/glm.hpp>

#include <string>
#include <vector>


namespace ceti {
namespace descriptor {
class Mesh;
} // namespace descriptor
} // namespace ceti


namespace jeti {

class ObjLoader;
class TextureOb;

class Mesh
{ 
public:
    Mesh(const ceti::descriptor::Mesh&);
    Mesh();
    ~Mesh();

    int id() const { return m_id; }

    TextureOb* textureOb() const { return m_textureOb; }
    const glm::vec3& boundaryBox() const { return m_boundaryBox; }
    const glm::vec3& originDirection() const { return m_originDirection; }

    void fillVertices(const ObjLoader&);
    void fillPointVertices(const std::vector<glm::vec3>&, const std::vector<glm::vec4>&, const std::vector<float>&);
    void fillPointVerticesFast(const std::vector<glm::vec3>&, const std::vector<glm::vec4>&, const std::vector<float>&);

    void draw() const;
    void draw(GLenum) const;
    
private:
    struct Vertex {
        glm::vec3 position;
        glm::vec2 texcoord;
        glm::vec3 normal;
        glm::vec4 color;
        float size;
    };

    static int m_id; // why static??
    GLenum m_primitiveType = GL_TRIANGLES;

    TextureOb* m_textureOb = nullptr;
    std::vector<Vertex> m_vertices;
    glm::vec3 m_boundaryBox;

    glm::vec3 m_originDirection;
    
    uint32_t m_vertexCount = 0;

    GLuint m_listId = 0;
    GLuint m_vaoId = 0;
    GLuint m_vboId = 0;

    bool m_hasTexCoords = true;
    bool m_hasNormals = true;
    bool m_hasColors = false;
    bool m_hasPointsSize = false;

    void __updateVbo();

    void __drawVbo() const;
    void __drawVbo(GLenum) const;
};

} // namespace jeti

