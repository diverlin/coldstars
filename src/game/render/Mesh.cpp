#include "Mesh.hpp"

#include <sstream>
#include <fstream>

#include "../common/myStr.hpp"
#include "../resources/ObjLoader.hpp"
  
Mesh::Mesh(const std::string& path, TextureOb* textureOb, TYPE::MESH type_id)
:
m_TypeId(type_id),
m_TextureOb(textureOb)
{        
    ObjLoader objLoader(path);
    
    BuildFaces(objLoader);
    m_BoundaryBox = objLoader.GetBoundaryBox();
    
    //CreateGlList();
    CreateVbo();
}

void Mesh::BuildFaces(const ObjLoader& objLoader)
{
    for(unsigned int i=0; i<objLoader.faces_indexes.size(); ++i)
    {
        MeshFaceData face;
        for(unsigned int j=0; j<3; ++j)
        {
            face.vertices[j].position = objLoader.positions[objLoader.faces_indexes[i].position_index[j] - 1];
            face.vertices[j].texcoord = objLoader.texcoords[objLoader.faces_indexes[i].texcoord_index[j] - 1];
            face.vertices[j].normal   = objLoader.normals[objLoader.faces_indexes[i].normal_index[j] - 1];
        }
        m_Faces.push_back(face);
    }
}
  
void Mesh::CreateGlList()
{
    m_GlList = glGenLists(1);
    glNewList(m_GlList, GL_COMPILE);
    for(unsigned int i=0; i<m_Faces.size(); i++)
    { 
        glBegin(GL_POLYGON);
        for(unsigned int j=0; j<3; j++)
        {
            glNormal3f(  m_Faces[i].vertices[j].normal.x,   m_Faces[i].vertices[j].normal.y,   m_Faces[i].vertices[j].normal.z);
            glTexCoord2f(m_Faces[i].vertices[j].texcoord.x, m_Faces[i].vertices[j].texcoord.y);
            glVertex3f(  m_Faces[i].vertices[j].position.x, m_Faces[i].vertices[j].position.y, m_Faces[i].vertices[j].position.z);
        }  
        glEnd();   
    }    
    glEndList();
}

void Mesh::CreateVbo()
{
    int positions_buffer_length = m_Faces.size()*3*3;
    int texcoords_buffer_length = m_Faces.size()*3*2;
    int normals_buffer_length   = m_Faces.size()*3*3;
        
    GLfloat positions_array[positions_buffer_length];
    GLfloat texcoords_array[texcoords_buffer_length];
    GLfloat normals_array[normals_buffer_length];
            
    for (unsigned int i=0, j=0; i<m_Faces.size(); i++)
    {
        for (unsigned int k=0; k<3; k++)
        {
            positions_array[j++] = m_Faces[i].vertices[k].position.x; 
            positions_array[j++] = m_Faces[i].vertices[k].position.y;
            positions_array[j++] = m_Faces[i].vertices[k].position.z;
        }
    }

    for (unsigned int i=0, j=0; i<m_Faces.size(); i++)
    {
        for (unsigned int k=0; k<3; k++)
        {
            texcoords_array[j++] = m_Faces[i].vertices[k].texcoord.x; 
            texcoords_array[j++] = m_Faces[i].vertices[k].texcoord.y;
        }
    }

    for (unsigned int i=0, j=0; i<m_Faces.size(); i++)
    {
        for (unsigned int k=0; k<3; k++)
        {
            normals_array[j++] = m_Faces[i].vertices[k].normal.x; 
            normals_array[j++] = m_Faces[i].vertices[k].normal.y;
            normals_array[j++] = m_Faces[i].vertices[k].normal.z;
        }
    }
                
    glGenBuffers(1, &m_VboId);

    glBindBuffer(GL_ARRAY_BUFFER, m_VboId);
    glBufferData(GL_ARRAY_BUFFER, sizeof(positions_array)+sizeof(texcoords_array)+sizeof(normals_array), 0, GL_STATIC_DRAW);      

    glBufferSubData(GL_ARRAY_BUFFER, 0,                                                sizeof(positions_array), positions_array); // copy positions starting from 0 offest
    glBufferSubData(GL_ARRAY_BUFFER, sizeof(positions_array),                          sizeof(texcoords_array), texcoords_array); // copy texcoords after vertices
    glBufferSubData(GL_ARRAY_BUFFER, sizeof(positions_array)+sizeof(texcoords_array),  sizeof(normals_array),   normals_array);   // copy normals after normals
}

void Mesh::DrawVbo() const
{
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);
    {
        glBindBuffer(GL_ARRAY_BUFFER, m_VboId);
            
        // before draw, specify vertex and index arrays with their offsets
        glVertexPointer(3,   GL_FLOAT, 0, 0);
        glTexCoordPointer(2, GL_FLOAT, 0, (void*)(m_Faces.size()*3*3*sizeof(GLfloat)));
        glNormalPointer(     GL_FLOAT, 0, (void*)(m_Faces.size()*3*3*sizeof(GLfloat) + m_Faces.size()*3*2*sizeof(GLfloat)));
                    
        glDrawArrays(GL_TRIANGLES, 0, m_Faces.size()*3); 
    
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }        
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    glDisableClientState(GL_NORMAL_ARRAY);
}

void Mesh::Draw() const
{
    DrawVbo();
}    
