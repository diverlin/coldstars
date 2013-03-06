#include "ObjMeshInstance.hpp"
#include <sstream>
#include <fstream>
     
ObjMeshInstance::ObjMeshInstance(const std::string& filename, int type_id):type_id(type_id)
{
	path = filename;
    	std::ifstream filestream;
    	filestream.open(filename.c_str());
 
    	std::string line_stream;   
    	while(std::getline(filestream, line_stream))
    	{
        	std::stringstream str_stream(line_stream);
        	std::string type_str;
        	str_stream >> type_str;
        	{
        		if (type_str == "v")
	        	{
	            		vec3f pos;
	            		str_stream >> pos.x >> pos.y >> pos.z;
	            		positions.push_back(pos);
	        	}
	        	
        		else if (type_str == "vt")
	        	{
	            		vec2f tex;
	            		str_stream >> tex.x >> tex.y;
	            		texcoords.push_back(tex);
	        	}
	        	
        		else if (type_str == "vn")
	        	{
	            		vec3f nor;
	            		str_stream >> nor.x >> nor.y >> nor.z;
	            		normals.push_back(nor);
	        	}
	        	
        		else if (type_str == "f")
	        	{
	            		MeshFaceIndexesData face_indexes;
	            		char interupt;
	            		for(int i=0; i<3; ++i)
	            		{
	                		str_stream >> face_indexes.position_index[i] >> interupt 
	                        		   >> face_indexes.texcoord_index[i] >> interupt
	                           	   	   >> face_indexes.normal_index[i];
	            		}
	            		faces_indexes.push_back(face_indexes);
	        	}
	        }
    	}
    	// Explicit closing of the file
    	filestream.close();
 
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

  	createGlList();
}
  
  
void ObjMeshInstance::createGlList()
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
