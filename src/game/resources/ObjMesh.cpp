#include "ObjMesh.hpp"
#include <sstream>
#include <fstream>
#include "../common/Logger.hpp"
#include "../common/myStr.hpp"
  
ObjMesh::ObjMesh(const std::string& filename, int type_id):type_id(type_id)
{
	path = filename;
    	std::ifstream filestream;
    	filestream.open(filename.c_str());
 
 	if (filestream.is_open() == false)
 	{
 		std::cout<<"FAULT: Not abe to open file:"<<filename;
 		exit(1);
 	}
 
    	std::string line;   
    	unsigned int line_counter = 0;
    	while(std::getline(filestream, line))
    	{
    		line_counter++;
    		#if OBJLOADER_LOG_ENABLED == 1
    		Logger::Instance().Log(filename+": line num="+int2str(line_counter)+" "+line, OBJLOADER_LOG_DIP);
        	#endif
        	
        	std::stringstream line_stream(line);
        	std::string type_str;
        	line_stream >> type_str;
        	{
        		if (type_str == "v")
	        	{
	            		vec3f pos;
	            		line_stream >> pos.x >> pos.y >> pos.z;
	            		positions.push_back(pos);
	        	}
	        	
        		else if (type_str == "vt")
	        	{
	            		vec2f tex;
	            		line_stream >> tex.x >> tex.y;
	            		texcoords.push_back(tex);
	        	}
	        	
        		else if (type_str == "vn")
	        	{
	            		vec3f nor;
	            		line_stream >> nor.x >> nor.y >> nor.z;
	            		normals.push_back(nor);
	        	}
	        	
        		else if (type_str == "f")
	        	{
	            		MeshFaceIndexesData face_indexes;
	            		char interupt;
	            		for(int i=0; i<3; ++i)
	            		{
	                		line_stream >> face_indexes.position_index[i] 
	                			    >> interupt 
	                        		    >> face_indexes.texcoord_index[i] 
	                        		    >> interupt
	                           	   	    >> face_indexes.normal_index[i];
	            		}
	            		faces_indexes.push_back(face_indexes);
	        	}
	        }
    	}

    	filestream.close();
 
 	BuildFaces();
  	//CreateGlList();
  	CreateVbo();
}
  
void ObjMesh::BuildFaces()
{
    	for(unsigned int i=0; i<faces_indexes.size(); ++i)
    	{
        	MeshFaceData face;
        	for(unsigned int j=0; j<3; ++j)
        	{
            		face.vertices[j].position = positions[faces_indexes[i].position_index[j] - 1];
            		face.vertices[j].texcoord = texcoords[faces_indexes[i].texcoord_index[j] - 1];
            		face.vertices[j].normal   = normals[faces_indexes[i].normal_index[j] - 1];
        	}
        	faces.push_back(face);
    	}
}
  
void ObjMesh::CreateGlList()
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

void ObjMesh::CreateVbo()
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

void ObjMesh::DrawVbo() const
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

void ObjMesh::Draw() const
{
	DrawVbo();
}	
