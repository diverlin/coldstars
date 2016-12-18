#include "Mesh.hpp"

#include <ceti/descriptor/Mesh.hpp>
#include "ObjLoader.hpp"

#include <sstream>
#include <fstream>

namespace jeti {

namespace {
const int VERTECIES_PER_POLYGON_NUM = 3;

const int VERTEX_POSITION_LOCATION = 0;
const int VERTEX_TEXCOORD_LOCATION = 1;
const int VERTEX_NORMAL_LOCATION   = 2;
const int VERTEX_COLOR_LOCATION    = 3;

const int STRIDE_POSITION = 3;
const int STRIDE_TEXCOORD = 2;
const int STRIDE_NORMAL   = 3;
const int STRIDE_COLOR    = 4;
} // namespace

Mesh::Mesh()
{
    m_listId = glGenLists(1);
    glGenVertexArrays(1, &m_vaoId);
    glGenBuffers(1, &m_vboId);

    __genQuad();
}

Mesh::Mesh(ceti::descriptor::Mesh* descriptor)
    :
      m_textureOb(nullptr),
      m_originDirection(descriptor->orientation())
{     
    m_listId = glGenLists(1);
    glGenVertexArrays(1, &m_vaoId);
    glGenBuffers(1, &m_vboId);

    if (!descriptor->modelPath().empty()) {
        m_id = descriptor->id();
        ObjLoader objLoader(descriptor->modelPath());
        fillVertices(objLoader);
        m_boundaryBox = objLoader.__boundaryBox();
    } else {
        __genQuad();
    }

    __validate();
}

Mesh::~Mesh()
{
    glDeleteVertexArrays(1, &m_vaoId);
    glDeleteVertexArrays(1, &m_vboId);
}

void Mesh::__genQuad()
{
    std::stringstream ss;
    ss << "v 0.5 0.0 -0.5 \n"
       << "v -0.5 0.0 -0.5 \n"
       << "v -0.5 0.0 0.5 \n"
       << "v 0.5 0.0 0.5 \n"
       << "v 0.5 0.0 -0.5 \n"
       << "v -0.5 0.0 -0.5 \n"
       << "v -0.5 0.0 0.5 \n"
       << "v 0.5 0.0 0.5 \n"
       << "vt 0.0 0.0 \n"
       << "vt 1.0 0.0 \n"
       << "vt 0.0 1.0 \n"
       << "vt 1.0 1.0 \n"
       << "vn 0.0 1.0 0.0 \n"
       << "vn 0.0 -1.0 0.0 \n"
       << "f 1/2/1 2/1/1 3/3/1 \n"
       << "f 4/4/1 1/2/1 3/3/1 \n"
       << "f 5/2/2 6/1/2 7/3/2 \n"
       << "f 8/4/2 5/2/2 7/3/2 \n";

    ObjLoader objLoader(ss);
    fillVertices(objLoader);

    m_isFlat = true;
}

void Mesh::fillVertices(const ObjLoader& objLoader)
{
    m_primitiveType = GL_TRIANGLES;

    m_hasTexCoords = true;
    m_hasNormals = true;
    m_hasColors = false;
    m_hasPointsSize = false;

    m_vertices.clear();

    for(unsigned int i=0; i<objLoader.m_faces_indexes.size(); ++i)
    {
        Vertex vertex;
        for(unsigned int j=0; j<VERTECIES_PER_POLYGON_NUM; ++j) {
            vertex.position = objLoader.m_positions[objLoader.m_faces_indexes[i].position_index[j] - 1];
            vertex.texcoord = objLoader.m_texcoords[objLoader.m_faces_indexes[i].texcoord_index[j] - 1];
            vertex.normal   = objLoader.m_normals[objLoader.m_faces_indexes[i].normal_index[j] - 1];

            m_vertices.push_back(vertex);
        }
    }

    m_vertexCount = m_vertices.size();

    __updateVbo();
}

void Mesh::fillPointVertices(const std::vector<glm::vec3>& positions, const std::vector<glm::vec4>& colors, const std::vector<float>& sizes)
{
    m_primitiveType = GL_POINTS;
    
    m_hasTexCoords = false;
    m_hasNormals = false;
    m_hasColors = true;
    m_hasPointsSize = true;

    m_vertices.clear();

    for(unsigned int i=0; i<positions.size(); ++i) {
        Vertex vertex;
        vertex.position = positions[i];
        vertex.color    = colors[i];
        vertex.size     = sizes[i];
        m_vertices.push_back(vertex);
    }

    m_vertexCount = m_vertices.size();

    __updateVbo();
}

void Mesh::fillPointVerticesFast(const std::vector<glm::vec3>& positions, const std::vector<glm::vec4>& colors, const std::vector<float>& sizes)
{  
    m_primitiveType = GL_POINTS;

    m_vertexCount = positions.size();

    int stride = STRIDE_POSITION + STRIDE_NORMAL + STRIDE_COLOR;
    
    GLfloat data_array[m_vertexCount * stride];

    uint32_t k=0;
    for (uint32_t i=0; i<m_vertexCount; i++) {
        data_array[k++] = positions[i].x;
        data_array[k++] = positions[i].y;
        data_array[k++] = positions[i].z;

        data_array[k++] = sizes[i];
        data_array[k++] = sizes[i];
        data_array[k++] = sizes[i];
        
        data_array[k++] = colors[i].r;
        data_array[k++] = colors[i].g;
        data_array[k++] = colors[i].b;
        data_array[k++] = colors[i].a;
    }

    glBindVertexArray(m_vaoId);
    glBindBuffer(GL_ARRAY_BUFFER, m_vboId);
    glBufferData(GL_ARRAY_BUFFER, sizeof(data_array), data_array, GL_DYNAMIC_DRAW);

    // attribute pointers
    glVertexAttribPointer(VERTEX_POSITION_LOCATION, STRIDE_POSITION, GL_FLOAT, GL_FALSE, stride*sizeof(GLfloat), (const GLvoid*)0);
    glEnableVertexAttribArray(VERTEX_POSITION_LOCATION);

    glVertexAttribPointer(VERTEX_NORMAL_LOCATION, STRIDE_NORMAL,     GL_FLOAT, GL_FALSE, stride*sizeof(GLfloat), (const GLvoid*)(STRIDE_POSITION * sizeof(GLfloat)));
    glEnableVertexAttribArray(VERTEX_NORMAL_LOCATION);

    glVertexAttribPointer(VERTEX_COLOR_LOCATION,    STRIDE_COLOR,    GL_FLOAT, GL_FALSE, stride*sizeof(GLfloat), (const GLvoid*)((STRIDE_POSITION+STRIDE_NORMAL) * sizeof(GLfloat)));
    glEnableVertexAttribArray(VERTEX_COLOR_LOCATION);
}


void Mesh::__updateVbo()
{    
    int stride = STRIDE_POSITION;
    
    if (m_hasTexCoords) { stride += STRIDE_TEXCOORD; }
    if ((m_hasNormals) or (m_hasPointsSize))  { stride += STRIDE_NORMAL; }
    if (m_hasColors)    { stride += STRIDE_COLOR; }

    GLfloat data_array[m_vertexCount * stride];

    uint32_t k=0;
    for (uint32_t i=0; i<m_vertexCount; i++)
    {
        data_array[k++] = m_vertices[i].position.x;
        data_array[k++] = m_vertices[i].position.y;
        data_array[k++] = m_vertices[i].position.z;
        
        if (m_hasTexCoords) {
            data_array[k++] = m_vertices[i].texcoord.x;
            data_array[k++] = m_vertices[i].texcoord.y;
        }

        if ( (m_hasNormals) || (m_hasPointsSize) )
        {
            if (m_hasNormals) {
                data_array[k++] = m_vertices[i].normal.x;
                data_array[k++] = m_vertices[i].normal.y;
                data_array[k++] = m_vertices[i].normal.z;
            } else if (m_hasPointsSize) {
                data_array[k++] = m_vertices[i].size;
                data_array[k++] = m_vertices[i].size;
                data_array[k++] = m_vertices[i].size;
            }
        }

        if (m_hasColors) {
            data_array[k++] = m_vertices[i].color.r;
            data_array[k++] = m_vertices[i].color.g;
            data_array[k++] = m_vertices[i].color.b;
            data_array[k++] = m_vertices[i].color.a;
        }
    }

    glBindVertexArray(m_vaoId);
    glBindBuffer(GL_ARRAY_BUFFER, m_vboId);
    glBufferData(GL_ARRAY_BUFFER, sizeof(data_array), data_array, GL_STATIC_DRAW);

    // attribute pointers
    int offset = 0;
    glVertexAttribPointer(VERTEX_POSITION_LOCATION, STRIDE_POSITION, GL_FLOAT, GL_FALSE, stride * sizeof(GLfloat), (const GLvoid*)(offset * sizeof(GLfloat)));
    glEnableVertexAttribArray(VERTEX_POSITION_LOCATION);
    offset += STRIDE_POSITION;

    if (m_hasTexCoords) {
        glVertexAttribPointer(VERTEX_TEXCOORD_LOCATION, STRIDE_TEXCOORD, GL_FLOAT, GL_FALSE, stride * sizeof(GLfloat), (const GLvoid*)(offset * sizeof(GLfloat)));
        glEnableVertexAttribArray(VERTEX_TEXCOORD_LOCATION);
        offset += STRIDE_TEXCOORD;
    }

    if ((m_hasNormals) || (m_hasPointsSize)) {
        glVertexAttribPointer(VERTEX_NORMAL_LOCATION, STRIDE_NORMAL, GL_FLOAT, GL_FALSE, stride * sizeof(GLfloat), (const GLvoid*)(offset * sizeof(GLfloat)));
        glEnableVertexAttribArray(VERTEX_NORMAL_LOCATION);
        offset += STRIDE_NORMAL;
    }

    if (m_hasColors) {
        glVertexAttribPointer(VERTEX_COLOR_LOCATION, STRIDE_COLOR, GL_FLOAT, GL_FALSE, stride * sizeof(GLfloat), (const GLvoid*)(offset * sizeof(GLfloat)));
        glEnableVertexAttribArray(VERTEX_COLOR_LOCATION);
        offset += STRIDE_COLOR;
    }
}     

void Mesh::__drawVbo() const
{
    glBindVertexArray(m_vaoId);
    glDrawArrays(m_primitiveType, 0, m_vertexCount);
}

void Mesh::__drawVbo(GLenum primitive_type) const
{
    glBindVertexArray(m_vaoId);
    glDrawArrays(primitive_type, 0, m_vertexCount);
}

void Mesh::draw() const
{
    __validate();
    __drawVbo();
}    

void Mesh::draw(GLenum primitive_type) const
{
    __validate();
    __drawVbo(primitive_type);
}  

void Mesh::__validate() const
{
    assert(m_vertices.size());
}

} // namespace jeti


// TODO
/*
VBO1
GLuint points_vbo = 0;
glGenBuffers (1, &points_vbo);
glBindBuffer (GL_ARRAY_BUFFER, points_vbo);
glBufferData (GL_ARRAY_BUFFER, 9 * sizeof (float), points, GL_STATIC_DRAW);

VBO2
GLuint colours_vbo = 0;
glGenBuffers (1, &colours_vbo);
glBindBuffer (GL_ARRAY_BUFFER, colours_vbo);
glBufferData (GL_ARRAY_BUFFER, 9 * sizeof (float), colours, GL_STATIC_DRAW);

VAO(VBO1+VBO2)
GLuint vao = 0;
glGenVertexArrays (1, &vao);
glBindVertexArray (vao);
glBindBuffer (GL_ARRAY_BUFFER, points_vbo);
glVertexAttribPointer (0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
glBindBuffer (GL_ARRAY_BUFFER, colours_vbo);
glVertexAttribPointer (1, 3, GL_FLOAT, GL_FALSE, 0, NULL);

// per each draw call
glEnableVertexAttribArray (0);
glEnableVertexAttribArray (1);


  glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glUseProgram (shader_programme);
  glBindVertexArray (vao);
  glDrawArrays (GL_TRIANGLES, 0, 3);

 */
