#include "Mesh.hpp"

#include <sstream>
#include <fstream>

#include <common/myStr.hpp>
#include <resources/ObjLoader.hpp>
  
const int POLYGON_VERT_NUM = 3;
  

Mesh::Mesh(const std::string& path, TextureOb* textureOb, TYPE::MESH type_id)
:
m_TypeId(type_id),
m_TextureOb(textureOb),
m_VaoId(0),        
m_VboId(0)
{        
    ObjLoader objLoader(path);
    
    BuildFaces(objLoader);
    m_BoundaryBox = objLoader.GetBoundaryBox();
        
    CreateVbo();
}

void Mesh::BuildFaces(const ObjLoader& objLoader)
{
    for(unsigned int i=0; i<objLoader.faces_indexes.size(); ++i)
    {
        MeshFaceData face;
        for(unsigned int j=0; j<POLYGON_VERT_NUM; ++j)
        {
            face.vertices[j].position = objLoader.positions[objLoader.faces_indexes[i].position_index[j] - 1];
            face.vertices[j].texcoord = objLoader.texcoords[objLoader.faces_indexes[i].texcoord_index[j] - 1];
            face.vertices[j].normal   = objLoader.normals[objLoader.faces_indexes[i].normal_index[j] - 1];
        }
        m_Faces.push_back(face);
    }
}
  
void Mesh::CreateVbo()
{    
    int positions_buffer_length = m_Faces.size() * POLYGON_VERT_NUM * 3;
    int texcoords_buffer_length = m_Faces.size() * POLYGON_VERT_NUM * 2;
    int normals_buffer_length   = m_Faces.size() * POLYGON_VERT_NUM * 3;
    
    int data_buffer_lenght = positions_buffer_length + texcoords_buffer_length + normals_buffer_length;  
    GLfloat data_array[data_buffer_lenght];        
           
    uint32_t k=0;
    for (unsigned int i=0; i<m_Faces.size(); i++)
    {
        for (unsigned int j=0; j<POLYGON_VERT_NUM; j++)
        {
            data_array[k++] = m_Faces[i].vertices[j].position.x; 
            data_array[k++] = m_Faces[i].vertices[j].position.y;
            data_array[k++] = m_Faces[i].vertices[j].position.z;
            
            data_array[k++] = m_Faces[i].vertices[j].texcoord.x; 
            data_array[k++] = m_Faces[i].vertices[j].texcoord.y;
            
            data_array[k++] = m_Faces[i].vertices[j].normal.x; 
            data_array[k++] = m_Faces[i].vertices[j].normal.y;
            data_array[k++] = m_Faces[i].vertices[j].normal.z;
        }
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
    glDrawArrays(GL_TRIANGLES, 0, m_Faces.size()*POLYGON_VERT_NUM); 
}

void Mesh::Draw() const
{
    DrawVbo();
}    
