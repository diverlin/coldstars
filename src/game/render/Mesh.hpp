
#ifndef MESH_HPP
#define MESH_HPP

#include <string>
#include <vector>

#include "../common/myVector.hpp"
#include <GL/glew.h>

class ObjLoader;
class TextureOb;

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
		Mesh(const std::string&, TextureOb* textureOb, int);
		~Mesh();

		int GetTypeId() const { return type_id; };
				
		void Draw() const;
	
	private:
		int type_id;
		
		TextureOb* textureOb;
		std::vector<MeshFaceData> faces; 

		GLuint glList; 
		GLuint vbo_id;
      
      		void BuildFaces(const ObjLoader&);
		void CreateGlList(); 
		void CreateVbo(); 

		void DrawVbo() const;
		void DrawGlList() const;
};

#endif
