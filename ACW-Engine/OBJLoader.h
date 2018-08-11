#pragma once
#include <vector>
#include <string>
#include "Mesh.h"
#include "VIBO.h"

struct FaceType
{
	int vIndex1, vIndex2, vIndex3;
	int tIndex1, tIndex2, tIndex3;
	int nIndex1, nIndex2, nIndex3;
};

struct OBJInfo {
public:
	unsigned vertexCount;
	unsigned textCount;
	unsigned normalCount;
	unsigned faceCount;

	bool hasTexture;
	bool hasNormals;

	OBJInfo()
		: vertexCount(0), textCount(0), normalCount(0), faceCount(0), hasTexture(false), hasNormals(false)
	{}
	explicit OBJInfo(const unsigned c1, const unsigned c2, const unsigned c3, const unsigned c4, const bool t, const bool n)
		: vertexCount(c1), textCount(c2), normalCount(c3), faceCount(c4), hasTexture(t), hasNormals(n)
	{}
};

namespace GameEngine
{
	class OBJLoader
	{
	public:
		OBJLoader(std::string meshName) : _meshName(meshName)
		{
			ReadFromFileInfo(); ReadFromFile();
		}
		~OBJLoader() = default;

	private:
		std::string _meshName;
		unsigned _numVertices;
		unsigned _numIndices;

		// obj loader info
		OBJInfo _objInfo;
		std::vector<SimpleVertexType> _vertices;
		std::vector<SimpleVertexType> _normals;
		std::vector<SimpleVertexType> _textureCoords;

		std::vector<SimpleVertex> _objectVertexs; // type defined in vibo
		std::vector<unsigned short> _indices;

		// getters & setters
	public:
		std::vector<unsigned short> GetIndices() { return _indices; }
		std::vector<SimpleVertex> GetVertices() { return _objectVertexs; }

	private:
		void ReadFromFile();
		void ReadFromFileInfo();
	};
}