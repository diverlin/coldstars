
#ifndef MESH_HPP
#define MESH_HPP

#include <string>
#include <vector>

#include "../common/myVector.hpp"
#include <GL/glew.h>
class ObjLoader;

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

class Mesh
{ 
	public:
		int GetTypeId() const { return type_id; };
				
		Mesh(const std::string&, int);
		~Mesh();
		
		void Draw() const;
	
	private:
		int type_id;
		
		std::vector<MeshFaceData> faces; // reconstracted data used in render

		GLuint glList; 
		GLuint vbo_id;
      
      		void BuildFaces(const ObjLoader&);
		void CreateGlList(); 
		void CreateVbo(); 

		void DrawVbo() const;
		void DrawGlList() const;
};

#endif
