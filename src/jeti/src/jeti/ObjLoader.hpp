
#pragma once

#include <glm/glm.hpp>

#include <fstream>
#include <string>
#include <vector>

namespace jeti {

class ObjLoader
{
    struct MeshFaceIndexesData {
        unsigned long int position_index[3];
        unsigned long int texcoord_index[3];
        unsigned long int normal_index[3];
    };

public:
    ObjLoader(std::stringstream&);
    ObjLoader(const std::string&);
    ~ObjLoader() {}
    
private:
    /** The data readed directly from file */
    std::vector<glm::vec3> m_positions;
    std::vector<glm::vec2> m_texcoords;
    std::vector<glm::vec3> m_normals;
    std::vector<MeshFaceIndexesData> m_faces_indexes;
    /** */

    void __readData(std::stringstream&);
    void __normalizePositions();
    glm::vec3 __boundaryBox();

    friend class Mesh;
};

} // namespace jeti
