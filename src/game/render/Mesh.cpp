#include "Mesh.hpp"

#include <sstream>
#include <fstream>

#include <common/myStr.hpp>
#include <resources/ObjLoader.hpp>


Mesh::Mesh(const std::string& path, TextureOb* textureOb, TYPE::MESH type_id)
:
m_TypeId(type_id),
m_PrimitiveType(GL_TRIANGLES),
m_TextureOb(textureOb),
m_VertexCount(0),
m_ListId(0),
m_VaoId(0),        
m_VboId(0),
m_HasNormals(true)
{     
    m_ListId = glGenLists(1);   
 	glGenVertexArrays(1, &m_VaoId);
    glGenBuffers(1, &m_VboId);

    ObjLoader objLoader(path);
    
    FillVertices(objLoader);
    m_BoundaryBox = objLoader.GetBoundaryBox();
}

Mesh::Mesh()
:
m_TypeId(TYPE::MESH::PLANE_ID),
m_PrimitiveType(GL_TRIANGLES),
m_TextureOb(nullptr),
m_VertexCount(0),
m_ListId(0),
m_VaoId(0),        
m_VboId(0),
m_HasTexCoords(true),
m_HasNormals(true),
m_HasColors(false)
{     
    m_ListId = glGenLists(1);   
 	glGenVertexArrays(1, &m_VaoId);
    glGenBuffers(1, &m_VboId);
}

Mesh::~Mesh()
{
   glDeleteVertexArrays(1, &m_VaoId);
   glDeleteVertexArrays(1, &m_VboId);
}

void Mesh::FillVertices(const ObjLoader& objLoader)
{
    m_PrimitiveType = GL_TRIANGLES;

    m_HasTexCoords = true;
    m_HasNormals = true;
    m_HasColors = false;

    m_Vertices.clear();

    for(unsigned int i=0; i<objLoader.faces_indexes.size(); ++i)
    {
        Vertex vertex;
        for(unsigned int j=0; j<VERTECIES_PER_POLYGON_NUM; ++j)
        {
            vertex.position = objLoader.positions[objLoader.faces_indexes[i].position_index[j] - 1];
            vertex.texcoord = objLoader.texcoords[objLoader.faces_indexes[i].texcoord_index[j] - 1];
            vertex.normal   = objLoader.normals[objLoader.faces_indexes[i].normal_index[j] - 1];

            m_Vertices.push_back(vertex);
        }
    } 

    m_VertexCount = m_Vertices.size();

    UpdateVbo();
}

void Mesh::FillVertices(const std::vector<glm::vec3>& positions, const std::vector<glm::vec4>& colors)
{
    m_PrimitiveType = GL_POINTS;
    
    m_HasTexCoords = false;
    m_HasNormals = false;
    m_HasColors = true;

    m_Vertices.clear();

    for(unsigned int i=0; i<positions.size(); ++i)
    {
        Vertex vertex;
        vertex.position = positions[i];
        vertex.color    = colors[i];
        m_Vertices.push_back(vertex);
    } 

    m_VertexCount = m_Vertices.size();

    UpdateVbo();
}

//void FillVerticesFast(const std::vector<glm::vec3>& positions, const std::vector<glm::vec2>& texcoords) const
//{
    //m_VertexCount = positions.size();

    //int positions_buffer_length = m_VertexCount * 3;
    //int texcoords_buffer_length = m_VertexCount * 2;
    
    //int data_buffer_lenght = positions_buffer_length + texcoords_buffer_length;  
    //GLfloat data_array[data_buffer_lenght];        
           
    //uint32_t k=0;
    //for (uint32_t i=0; i<m_VertexCount; i++)
    //{
        //data_array[k++] = positions[i].x; 
        //data_array[k++] = positions[i].y;
        //data_array[k++] = positions[i].z;
        
        //data_array[k++] = texcoords[i].x; 
        //data_array[k++] = texcoords[i].y;
    //}

	//glBindVertexArray(m_VaoId);
    //glBindBuffer(GL_ARRAY_BUFFER, m_VboId);
    //glBufferData(GL_ARRAY_BUFFER, sizeof(data_array), data_array, GL_STATIC_DRAW);      

    //// attribute pointers    
    //glVertexAttribPointer(VERTEX_POSITION_LOCATION, 3, GL_FLOAT, GL_FALSE, (3+2+3)*sizeof(GLfloat), (const GLvoid*)0);
	//glEnableVertexAttribArray(VERTEX_POSITION_LOCATION);

	//glVertexAttribPointer(VERTEX_TEXCOORD_LOCATION, 2, GL_FLOAT, GL_FALSE, (3+2+3)*sizeof(GLfloat), (const GLvoid*)(3*sizeof(GLfloat)));
	//glEnableVertexAttribArray(VERTEX_TEXCOORD_LOCATION);
//}

void Mesh::UpdateList()
{
    glNewList(m_ListId, GL_COMPILE);
    for(unsigned int i=0; i<m_Vertices.size(); i++)
    { 
        glBegin(m_PrimitiveType);
        {
            glNormal3f(  m_Vertices[i].normal.x,   m_Vertices[i].normal.y,   m_Vertices[i].normal.z);
            glTexCoord2f(m_Vertices[i].texcoord.x, m_Vertices[i].texcoord.y);
            glVertex3f(  m_Vertices[i].position.x, m_Vertices[i].position.y, m_Vertices[i].position.z);
        }
        glEnd();   
    }    
    glEndList();
}

  
void Mesh::UpdateVbo()
{    
    int positions_buffer_length = m_VertexCount * 3;
    int texcoords_buffer_length = m_VertexCount * 2;
    int normals_buffer_length   = m_VertexCount * 3;
    int colors_buffer_length    = m_VertexCount * 4;
    
    int data_buffer_lenght = positions_buffer_length + texcoords_buffer_length + normals_buffer_length + colors_buffer_length;

    GLfloat data_array[data_buffer_lenght];        
           
    uint32_t k=0;
    for (uint32_t i=0; i<m_VertexCount; i++)
    {
        data_array[k++] = m_Vertices[i].position.x; 
        data_array[k++] = m_Vertices[i].position.y;
        data_array[k++] = m_Vertices[i].position.z;
        
        data_array[k++] = m_Vertices[i].texcoord.x; 
        data_array[k++] = m_Vertices[i].texcoord.y;
      
        data_array[k++] = m_Vertices[i].normal.x; 
        data_array[k++] = m_Vertices[i].normal.y;
        data_array[k++] = m_Vertices[i].normal.z;

        data_array[k++] = m_Vertices[i].color.r; 
        data_array[k++] = m_Vertices[i].color.g;
        data_array[k++] = m_Vertices[i].color.b;
        data_array[k++] = m_Vertices[i].color.a;
    }
 
	glBindVertexArray(m_VaoId);
    glBindBuffer(GL_ARRAY_BUFFER, m_VboId);
    glBufferData(GL_ARRAY_BUFFER, sizeof(data_array), data_array, GL_STATIC_DRAW);      

    // attribute pointers    
    glVertexAttribPointer(VERTEX_POSITION_LOCATION, 3, GL_FLOAT, GL_FALSE, (3+2+3+4)*sizeof(GLfloat), (const GLvoid*)0);
	glEnableVertexAttribArray(VERTEX_POSITION_LOCATION);

    if (m_HasTexCoords)
    {
        glVertexAttribPointer(VERTEX_TEXCOORD_LOCATION, 2, GL_FLOAT, GL_FALSE, (3+2+3+4)*sizeof(GLfloat), (const GLvoid*)(3*sizeof(GLfloat)));
        glEnableVertexAttribArray(VERTEX_TEXCOORD_LOCATION);
    }

    if (m_HasNormals)
    { 
	    glVertexAttribPointer(VERTEX_NORMAL_LOCATION, 3, GL_FLOAT, GL_FALSE,   (3+2+3+4)*sizeof(GLfloat), (const GLvoid*)((3 + 2)*sizeof(GLfloat)));
	    glEnableVertexAttribArray(VERTEX_NORMAL_LOCATION);
    }

    if (m_HasColors)
    { 
	    glVertexAttribPointer(VERTEX_COLOR_LOCATION, 3, GL_FLOAT, GL_FALSE,   (3+2+3+4)*sizeof(GLfloat), (const GLvoid*)((3 + 2 + 3)*sizeof(GLfloat)));
	    glEnableVertexAttribArray(VERTEX_COLOR_LOCATION);
    }
}     
  
void Mesh::DrawVbo() const
{
    glBindVertexArray(m_VaoId);
    glDrawArrays(m_PrimitiveType, 0, m_VertexCount); 
}

void Mesh::DrawList() const
{
    glCallList(m_ListId);
}
        
void Mesh::Draw() const
{
    DrawVbo();
}    


//initialization:
    //for each batch
        //generate, store, and bind a VAO
        //bind all the buffers needed for a draw call
        //unbind the VAO

//main loop/whenever you render:
    //for each batch
        //bind VAO
        //glDrawArrays(...); or glDrawElements(...); etc.
    //unbind VAO
