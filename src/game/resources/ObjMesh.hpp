
#ifndef OBJMESHINSTANCE_HPP
#define OBJMESHINSTANCE_HPP

#include <string>
#include <vector>

#include "../common/myVector.hpp"
#include <GL/glew.h>

struct MeshVertexData
{
	vec3f position;
	vec2f texcoord;
	vec3f normal;
};

struct MeshFaceData
{
	MeshVertexData vertices[3];
};

struct MeshFaceIndexesData
{
	unsigned long int position_index[3];
	unsigned long int texcoord_index[3];
	unsigned long int normal_index[3];
};

class ObjMesh
{ 
	public:
		int GetTypeId() const { return type_id; };
				
		ObjMesh(const std::string&, int);
		~ObjMesh();
		
		void Draw() const;
	
	private:
		int type_id;
		
		/** The data readed directly from file */
		std::vector<vec3f> positions;
		std::vector<vec2f> texcoords;
		std::vector<vec3f> normals;		
		std::vector<MeshFaceIndexesData> faces_indexes;
		/** */
		
		std::vector<MeshFaceData> faces; // reconstracted data used in render

		GLuint glList; 
		GLuint vbo_id;
		
		std::string path;
      
      		void BuildFaces();
		void CreateGlList(); 
		void CreateVbo(); 

		void DrawVbo() const;
		void DrawGlList() const;
};

#endif
