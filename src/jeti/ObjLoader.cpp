#include "ObjLoader.hpp"

#include <iostream>
#include <sstream>
#include <fstream>

#include <cmath>

#ifdef LOGGER_ENABLED
#include "<common/Logger.hpp>
#endif
  
namespace jeti {

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
#ifdef LOGGER_ENABLED
        Logger::Instance().Log(filename+": line num="+ceti::int2str(line_counter)+" "+line, OBJLOADER_LOG_DIP);
#endif
        
        std::stringstream line_stream(line);
        std::string type_str;
        line_stream >> type_str;
        {
            if (type_str == "v")
            {
                glm::vec3 pos;
                line_stream >> pos.x >> pos.z >> pos.y;                
                positions.push_back(pos);             
            }
            
            else if (type_str == "vt")
            {
                glm::vec2 tex;
                line_stream >> tex.x >> tex.y;
                texcoords.push_back(tex);
            }
            
            else if (type_str == "vn")
            {
                glm::vec3 nor;
                line_stream >> nor.x >> nor.z >> nor.y;
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

glm::vec3 ObjLoader::GetBoundaryBox()
{
    glm::vec3 boundary_box;
    for (unsigned int i=0; i<positions.size(); i++)
    {
        if (boundary_box.x < fabs(positions[i].x)) boundary_box.x = fabs(positions[i].x);
        if (boundary_box.y < fabs(positions[i].y)) boundary_box.y = fabs(positions[i].y);
        if (boundary_box.z < fabs(positions[i].z)) boundary_box.z = fabs(positions[i].z);
    }
    
    boundary_box *= 2.0;
    
    return boundary_box;
}

}
