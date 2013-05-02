#include "ObjLoader.hpp"
#include <sstream>
#include <fstream>
#include <cmath>

#include "../common/Logger.hpp"
#include "../common/myStr.hpp"
  
ObjLoader::ObjLoader(const std::string& path)
{
    	std::ifstream filestream;
    	filestream.open(path.c_str());
 
 	if (filestream.is_open() == false)
 	{
 		std::cout<<"FAULT: Not abe to open file:"<<path;
 		exit(EXIT_FAILURE);
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
	            		Vec3<float> pos;
	            		line_stream >> pos.x >> pos.y >> pos.z;
	            		positions.push_back(pos);
	        	}
	        	
        		else if (type_str == "vt")
	        	{
	            		Vec2<float> tex;
	            		line_stream >> tex.x >> tex.y;
	            		tex.y = 1 - tex.y; // this is needed for correct texture mapping in opengl 
	            		texcoords.push_back(tex);
	        	}
	        	
        		else if (type_str == "vn")
	        	{
	            		Vec3<float> nor;
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
    	
    	NormalizePositions();
}

void ObjLoader::NormalizePositions()
{
	float max_pos = 0;
	for (unsigned int i=0; i<positions.size(); i++)
	{
		if (max_pos < fabs(positions[i].x)) max_pos = fabs(positions[i].x);
		if (max_pos < fabs(positions[i].y)) max_pos = fabs(positions[i].y);
		if (max_pos < fabs(positions[i].z)) max_pos = fabs(positions[i].z);
	}

	for (unsigned int i=0; i<positions.size(); i++)
	{
		positions[i] /= max_pos;
	}	
	
}

Vec3<float> ObjLoader::GetBoundaryBox()
{
	Vec3<float> boundary_box;
	for (unsigned int i=0; i<positions.size(); i++)
	{
		if (boundary_box.x < fabs(positions[i].x)) boundary_box.x = fabs(positions[i].x);
		if (boundary_box.y < fabs(positions[i].y)) boundary_box.y = fabs(positions[i].y);
		if (boundary_box.z < fabs(positions[i].z)) boundary_box.z = fabs(positions[i].z);
	}
	
	boundary_box *= 2.0;
	
	return boundary_box;
}

  
