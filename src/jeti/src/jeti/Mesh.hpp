#pragma once

#include <MyGl.hpp>

#include <ceti/type/IdType.hpp>

#include <glm/glm.hpp>

#include <string>
#include <vector>


namespace ceti {
class MeshDescr;
} // namespace ceti

namespace jeti {

class ObjLoader;
//class TextureOb;

class Mesh
{ 
public:
    enum class State { NONE, QUAD, QUAD_ADDITIVE, NORMAL, PARTICLES, LINES };

    Mesh(bool circle = false);
    Mesh(const std::string&);
    Mesh(ceti::MeshDescr*);
    ~Mesh();

    int_t id() const { return m_id; }

    bool isFlat() const { return m_states == State::QUAD || m_states == State::QUAD_ADDITIVE; }

    //TextureOb* textureOb() const { return m_textureOb; }
    const glm::vec3& boundaryBox() const { return m_boundaryBox; }
    const glm::vec3& originDirection() const { return m_originDirection; }

    float linesWidth() const { return m_linesWidth; }

    void fillLineVertices(const ObjLoader&);
    void fillLineVertices(const std::vector<glm::vec3>& positions, const std::vector<glm::vec4>& colors, float linesWidth);
    void fillPointVertices(const std::vector<glm::vec3>&, const std::vector<glm::vec4>&, const std::vector<float>&);
    void fillPointVerticesFast(const std::vector<glm::vec3>&, const std::vector<glm::vec4>&, const std::vector<float>&);

    void draw() const;
    void draw(GLenum) const;

    void setStates(Mesh::State states) { m_states = states; }
    const State& states() const { return m_states; }
    
private:
    struct Vertex {
        glm::vec3 position;
        glm::vec2 texcoord;
        glm::vec3 normal;
        glm::vec4 color;
        float size;
    };

    int_t m_id = -1;
    GLenum m_primitiveType = GL_TRIANGLES;
    float m_linesWidth = 1.0f;
    State m_states = State::NORMAL;

    //TextureOb* m_textureOb = nullptr;
    std::vector<Vertex> m_vertices;
    glm::vec3 m_boundaryBox;

    glm::vec3 m_originDirection = glm::vec3(0.0f, 1.0f, 0.0f);
    
    uint32_t m_vertexCount = 0;

    GLuint m_vaoId = 0;
    GLuint m_vboId = 0;

    bool m_hasTexCoords = true;
    bool m_hasNormals = true;
    bool m_hasColors = false;
    bool m_hasPointsSize = false;

    void __updateVbo();

    void __drawVbo() const;
    void __drawVbo(GLenum) const;
    void __validate() const;

    void __genQuad();
    void __genCircle();
};

} // namespace jeti

