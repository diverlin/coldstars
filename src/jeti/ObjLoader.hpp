
#pragma once

#include <string>
#include <vector>

#include <glm/glm.hpp>

namespace jeti {

struct MeshFaceIndexesData
{
    unsigned long int position_index[3];
    unsigned long int texcoord_index[3];
    unsigned long int normal_index[3];
};

class ObjLoader
{ 
    public:        
        ObjLoader(const std::string&);
        ~ObjLoader() {};
    
    private:
        /** The data readed directly from file */
        std::vector<glm::vec3> positions;
        std::vector<glm::vec2> texcoords;
        std::vector<glm::vec3> normals;        
        std::vector<MeshFaceIndexesData> faces_indexes;
        /** */
        
        void NormalizePositions();
        glm::vec3 GetBoundaryBox();
        
    friend class Mesh;
};

}
