#include "ObjLoader.hpp"
#include <sstream>
#include <fstream>
#include "../common/Logger.hpp"
#include "../common/myStr.hpp"
  
ObjLoader::ObjLoader(const std::string& path)
{
    	std::ifstream filestream;
    	filestream.open(path.c_str());
 
 	if (filestream.is_open() == false)
 	{
 		std::cout<<"FAULT: Not abe to open file:"<<path;
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
}

  
