
#ifndef MESH_HPP
#define MESH_HPP

#include <string>
#include <vector>

#include <math/Vec2.hpp>
#include <math/Vec3.hpp>

#include <render/MyGl.hpp>
#include <common/MeshTypes.hpp>

class ObjLoader;
class TextureOb;

struct MeshVertexData
{
	Vec3<float> position;
	Vec2<float> texcoord;
	Vec3<float> normal;
};

struct MeshFaceData
{
	MeshVertexData vertices[3];
};

class Mesh
{ 
	public:
		Mesh(const std::string&, TextureOb* textureOb, TYPE::MESH);
		~Mesh();

		TYPE::MESH GetTypeId() const { return type_id; };
		TextureOb* GetTextureOb() const { return textureOb; };
		const Vec3<float>& GetBoundaryBox() const { return boundary_box; };
						
		void Draw() const;
	
	private:
		TYPE::MESH type_id;
		
		TextureOb* textureOb;
		std::vector<MeshFaceData> faces; 
		Vec3<float> boundary_box;

		GLuint glList; 
		GLuint vbo_id;
      		
        void BuildFaces(const ObjLoader&);
		void CreateGlList(); 
		void CreateVbo(); 

		void DrawVbo() const;
		void DrawGlList() const;
};

#endif
