#include "Mesh.hpp"
#include <sstream>
#include <fstream>
#include "../common/Logger.hpp"
#include "../common/myStr.hpp"
#include "../resources/ObjLoader.hpp"
  
Mesh::Mesh(const std::string& path, TextureOb* textureOb, int type_id):textureOb(textureOb), type_id(type_id)
{    	
     	ObjLoader objLoader(path);
     	     
 	BuildFaces(objLoader);
 	boundary_box = objLoader.GetBoundaryBox();
  	
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
        	faces.push_back(face);
    	}
}
  
void Mesh::CreateGlList()
{
 	glList = glGenLists(1);
      	glNewList(glList, GL_COMPILE);
      	for(unsigned int i=0; i<faces.size(); i++)
      	{ 
        	glBegin(GL_POLYGON);
         	for(unsigned int j=0; j<3; j++)
         	{
             		glNormal3f(  faces[i].vertices[j].normal.x,   faces[i].vertices[j].normal.y,   faces[i].vertices[j].normal.z);
             		glTexCoord2f(faces[i].vertices[j].texcoord.x, faces[i].vertices[j].texcoord.y);
             		glVertex3f(  faces[i].vertices[j].position.x, faces[i].vertices[j].position.y, faces[i].vertices[j].position.z);
         	}  
         	glEnd();   
      	}    
      	glEndList();
}

void Mesh::CreateVbo()
{
	int positions_buffer_length = faces.size()*3*3;
	int texcoords_buffer_length = faces.size()*3*2;
	int normals_buffer_length   = faces.size()*3*3;
		
	GLfloat positions_array[positions_buffer_length];
	GLfloat texcoords_array[texcoords_buffer_length];
	GLfloat normals_array[normals_buffer_length];
			
	for (unsigned int i=0, j=0; i<faces.size(); i++)
	{
		for (unsigned int k=0; k<3; k++)
		{
			positions_array[j++] = faces[i].vertices[k].position.x; 
			positions_array[j++] = faces[i].vertices[k].position.y;
			positions_array[j++] = faces[i].vertices[k].position.z;
		}
	}

	for (unsigned int i=0, j=0; i<faces.size(); i++)
	{
		for (unsigned int k=0; k<3; k++)
		{
			texcoords_array[j++] = faces[i].vertices[k].texcoord.x; 
			texcoords_array[j++] = faces[i].vertices[k].texcoord.y;
		}
	}

	for (unsigned int i=0, j=0; i<faces.size(); i++)
	{
		for (unsigned int k=0; k<3; k++)
		{
			normals_array[j++] = faces[i].vertices[k].normal.x; 
			normals_array[j++] = faces[i].vertices[k].normal.y;
			normals_array[j++] = faces[i].vertices[k].normal.z;
		}
	}
				
	glGenBuffers(1, &vbo_id);

	glBindBuffer(GL_ARRAY_BUFFER, vbo_id);
    	glBufferData(GL_ARRAY_BUFFER, sizeof(positions_array)+sizeof(texcoords_array)+sizeof(normals_array), 0, GL_STATIC_DRAW);      

        glBufferSubData(GL_ARRAY_BUFFER_ARB, 0,                                                sizeof(positions_array), positions_array); // copy positions starting from 0 offest
        glBufferSubData(GL_ARRAY_BUFFER_ARB, sizeof(positions_array),                          sizeof(texcoords_array), texcoords_array); // copy texcoords after vertices
        glBufferSubData(GL_ARRAY_BUFFER_ARB, sizeof(positions_array)+sizeof(texcoords_array),  sizeof(normals_array),   normals_array);   // copy normals after normals
}

void Mesh::DrawVbo() const
{
	glEnableClientState(GL_VERTEX_ARRAY);
    	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
    	
	glBindBuffer(GL_ARRAY_BUFFER, vbo_id);
	    
	// before draw, specify vertex and index arrays with their offsets
        glVertexPointer(3, GL_FLOAT, 0, 0);
        glTexCoordPointer(2, GL_FLOAT, 0, (void*)(faces.size()*3*3*sizeof(GLfloat)));
        glNormalPointer(GL_FLOAT, 0, (void*)(faces.size()*3*3*sizeof(GLfloat)+faces.size()*3*2*sizeof(GLfloat)));
                
	glDrawArrays(GL_TRIANGLES, 0, faces.size()*3); 

    	glBindBufferARB(GL_ARRAY_BUFFER_ARB, 0);
    		
	glDisableClientState(GL_VERTEX_ARRAY);
    	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);

}

void Mesh::Draw() const
{
	DrawVbo();
}	
