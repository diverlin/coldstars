#include "ObjLoader.hpp"

#include "constants.hpp"

#include <ceti/Logger.hpp>

#include <iostream>
#include <sstream>
#include <fstream>
#include <cmath>

namespace jeti {

ObjLoader::ObjLoader(std::stringstream& stringstream)
{
    __readData(stringstream);
}

ObjLoader::ObjLoader(const std::string& fname)
{
    std::string path = DATA_PATH + "/obj/" + fname;
    std::ifstream filestream;
    filestream.open(path.c_str());
    if (!filestream.is_open()) {
        std::cout<<"FAULT: Not abe to open file:"<<path;
        exit(EXIT_FAILURE);
    }
    std::stringstream stringstream;
    stringstream << filestream.rdbuf();
    filestream.close();

    __readData(stringstream);
}

void ObjLoader::__readData(std::stringstream& stringstream)
{
    std::string line;
    unsigned int line_counter = 0;
    while(std::getline(stringstream, line))
    {
        line_counter++;

        std::stringstream line_stream(line);
        std::string type_str;
        line_stream >> type_str;
        {
            if (type_str == "v")
            {
                glm::vec3 pos;
                line_stream >> pos.x >> pos.z >> pos.y;
                m_positions.push_back(pos);
            }

            else if (type_str == "vt")
            {
                glm::vec2 tex;
                line_stream >> tex.x >> tex.y;
                m_texcoords.push_back(tex);
            }

            else if (type_str == "vn")
            {
                glm::vec3 nor;
                line_stream >> nor.x >> nor.z >> nor.y;
                m_normals.push_back(nor);
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
                m_faces_indexes.push_back(face_indexes);
            }
        }
    }

    __normalizePositions();
}

void ObjLoader::__normalizePositions()
{
    float max_pos = 0;
    for (const auto& position: m_positions)
    {
        if (max_pos < fabs(position.x)) max_pos = fabs(position.x);
        if (max_pos < fabs(position.y)) max_pos = fabs(position.y);
        if (max_pos < fabs(position.z)) max_pos = fabs(position.z);
    }

    for (unsigned int i=0; i<m_positions.size(); i++)
    {
        m_positions[i] /= max_pos;
    }
    
}

glm::vec3 ObjLoader::__boundaryBox()
{
    glm::vec3 boundary_box;
    for (const auto& position: m_positions)
    {
        if (boundary_box.x < fabs(position.x)) boundary_box.x = fabs(position.x);
        if (boundary_box.y < fabs(position.y)) boundary_box.y = fabs(position.y);
        if (boundary_box.z < fabs(position.z)) boundary_box.z = fabs(position.z);
    }
    
    boundary_box *= 2.0;
    
    return boundary_box;
}

} // namespace jeti
