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
m_VboId(0)
{        
    ObjLoader objLoader(path);
    
    BuildFaces(objLoader);
    m_BoundaryBox = objLoader.GetBoundaryBox();
     
    //CreateList();   
    CreateVbo();
}

void Mesh::BuildFaces(const ObjLoader& objLoader)
{
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
}

void Mesh::CreateList()
{
    m_ListId = glGenLists(1);
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

  
void Mesh::CreateVbo()
{    
    m_VertexCount = m_Vertices.size();

    int positions_buffer_length = m_VertexCount * 3;
    int texcoords_buffer_length = m_VertexCount * 2;
    int normals_buffer_length   = m_VertexCount * 3;
    
    int data_buffer_lenght = positions_buffer_length + texcoords_buffer_length + normals_buffer_length;  
    GLfloat data_array[data_buffer_lenght];        
           
    uint32_t k=0;
    for (uint32_t i=0; i<m_Vertices.size(); i++)
    {
        data_array[k++] = m_Vertices[i].position.x; 
        data_array[k++] = m_Vertices[i].position.y;
        data_array[k++] = m_Vertices[i].position.z;
        
        data_array[k++] = m_Vertices[i].texcoord.x; 
        data_array[k++] = m_Vertices[i].texcoord.y;
        
        data_array[k++] = m_Vertices[i].normal.x; 
        data_array[k++] = m_Vertices[i].normal.y;
        data_array[k++] = m_Vertices[i].normal.z;
    }
 
 	glGenVertexArrays(1, &m_VaoId);
	glBindVertexArray(m_VaoId);
                   
    glGenBuffers(1, &m_VboId);

    glBindBuffer(GL_ARRAY_BUFFER, m_VboId);
    glBufferData(GL_ARRAY_BUFFER, sizeof(data_array), data_array, GL_STATIC_DRAW);      

    // attribute pointers    
    glVertexAttribPointer(VERT_POSITION, 3, GL_FLOAT, GL_FALSE, (3+2+3)*sizeof(GLfloat), (const GLvoid*)0);
	glEnableVertexAttribArray(VERT_POSITION);

	glVertexAttribPointer(VERT_TEXCOORD, 2, GL_FLOAT, GL_FALSE, (3+2+3)*sizeof(GLfloat), (const GLvoid*)(3*sizeof(GLfloat)));
	glEnableVertexAttribArray(VERT_TEXCOORD);

	glVertexAttribPointer(VERT_NORMAL, 3, GL_FLOAT, GL_FALSE,   (3+2+3)*sizeof(GLfloat), (const GLvoid*)(3*sizeof(GLfloat) + 2*sizeof(GLfloat)));
	glEnableVertexAttribArray(VERT_NORMAL);
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
