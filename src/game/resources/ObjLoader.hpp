
#ifndef OBJLOADER_HPP
#define OBJLOADER_HPP

#include <string>
#include <vector>

#include "../common/myVector.hpp"

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
		std::vector<vec3f> positions;
		std::vector<vec2f> texcoords;
		std::vector<vec3f> normals;		
		std::vector<MeshFaceIndexesData> faces_indexes;
		/** */
		
		void NormalizePositions();
		
	friend class Mesh;
};

#endif
