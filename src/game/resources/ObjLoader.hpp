
#ifndef OBJLOADER_HPP
#define OBJLOADER_HPP

#include <string>
#include <vector>

#include "../math/myVector.hpp"

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
        std::vector<Vec3<float>> positions;
        std::vector<Vec2<float>> texcoords;
        std::vector<Vec3<float>> normals;        
        std::vector<MeshFaceIndexesData> faces_indexes;
        /** */
        
              void NormalizePositions();
              Vec3<float> GetBoundaryBox();
        
    friend class Mesh;
};

#endif
