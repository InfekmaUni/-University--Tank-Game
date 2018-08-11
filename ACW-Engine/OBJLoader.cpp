#include "OBJLoader.h"
#include <DirectXMath.h>

using namespace GameEngine;

void OBJLoader::ReadFromFileInfo()
{
	std::ifstream obj("Meshes/" + _meshName + ".obj");
	int vCount = 0, tCount = 0, nCount = 0, fCount = 0;
	char input = ' ';

	obj.get(input);
	while (!obj.eof())
	{
		if (input == 'v') { // check how many vertex/texscoord/normals
			obj.get(input);
			if (input == ' ') { vCount++; }
			if (input == 't') { tCount++; }
			if (input == 'n') { nCount++; }
		}
		if (input == 'f') { // face
			obj.get(input);
			if (input == ' ') { fCount++; }
		}
		while (input != '\n') { // read remainder of file
			obj.get(input);
		}

		obj.get(input);
	}
	obj.close();

	_objInfo = OBJInfo(vCount, tCount, nCount, fCount, tCount > 0, nCount > 0);
}

void OBJLoader::ReadFromFile()
{
	int vertexIndex = 0, texcoordIndex = 0, normalIndex = 0, faceIndex = 0, vIndex = 0, tIndex = 0, nIndex = 0;
	char input, input2;

	// Initialize the four data structures.
	SimpleVertexType* const vertices = new SimpleVertexType[_objInfo.vertexCount];
	SimpleVertexType* const texcoords = new SimpleVertexType[_objInfo.textCount];
	SimpleVertexType* const normals = new SimpleVertexType[_objInfo.normalCount];
	FaceType* const faces = new FaceType[_objInfo.faceCount];

	// Open the file.
	std::ifstream fin("Meshes/" + _meshName + ".obj");
	std::cout << "Reading model file: " + _meshName << std::endl;

	// Check if it was successful in opening the file.
	if (fin.fail() == true)
	{
		return;
	}

	const bool RIGHT_HAND = true;
	// Read in the vertices, texture coordinates, and normals into the data structures.
	// Important: Also convert to left hand coordinate system since Maya uses right hand coordinate system.
	fin.get(input);
	while (!fin.eof())
	{
		if (input == 'v')
		{
			fin.get(input);

			// Read in the vertices.
			if (input == ' ')
			{
				fin >> vertices[vertexIndex].x >> vertices[vertexIndex].y >> vertices[vertexIndex].z;

				// Invert the Z vertex to change to left hand system.
				if (RIGHT_HAND)
					vertices[vertexIndex].z = vertices[vertexIndex].z * -1.0f;

				vertexIndex++;
			}

			// Read in the texture uv coordinates.
			if (input == 't')
			{
				fin >> texcoords[texcoordIndex].x >> texcoords[texcoordIndex].y;

				// Invert the V texture coordinates to left hand system.
				if (RIGHT_HAND)
					texcoords[texcoordIndex].y = 1.0f - texcoords[texcoordIndex].y;

				texcoordIndex++;
			}

			// Read in the normals.
			if (input == 'n')
			{
				fin >> normals[normalIndex].x >> normals[normalIndex].y >> normals[normalIndex].z;

				// Invert the Z normal to change to left hand system.
				if (RIGHT_HAND)
					normals[normalIndex].z = normals[normalIndex].z * -1.0f;

				normalIndex++;
			}
		}

		// Read in the faces.
		if (input == 'f')
		{
			fin.get(input);
			if (input == ' ')
			{
				// Read the face data in backwards to convert it to a left hand system from right hand system.
				if (RIGHT_HAND) {
					fin >> faces[faceIndex].vIndex3 >> input2 >> faces[faceIndex].tIndex3 >> input2 >> faces[faceIndex].nIndex3
						>> faces[faceIndex].vIndex2 >> input2 >> faces[faceIndex].tIndex2 >> input2 >> faces[faceIndex].nIndex2
						>> faces[faceIndex].vIndex1 >> input2 >> faces[faceIndex].tIndex1 >> input2 >> faces[faceIndex].nIndex1;
				}
				else {

					fin >> faces[faceIndex].vIndex1 >> input2 >> faces[faceIndex].tIndex1 >> input2 >> faces[faceIndex].nIndex1
						>> faces[faceIndex].vIndex2 >> input2 >> faces[faceIndex].tIndex2 >> input2 >> faces[faceIndex].nIndex2
						>> faces[faceIndex].vIndex3 >> input2 >> faces[faceIndex].tIndex3 >> input2 >> faces[faceIndex].nIndex3;
				}
				faceIndex++;
			}
		}

		// Read in the remainder of the line.
		while (input != '\n')
		{
			fin.get(input);
		}

		// Start reading the beginning of the next line.
		fin.get(input);
	}
	// Close the file.
	fin.close();

	_vertices = std::vector<SimpleVertexType>(vertices, vertices + vertexIndex);
	_normals = std::vector<SimpleVertexType>(normals, normals + normalIndex);
	_textureCoords = std::vector<SimpleVertexType>(texcoords, texcoords + texcoordIndex);

	SimpleVertex vertex = SimpleVertex();
	for (int i = 0; i < faceIndex; i++) {
		//
		// Vertex 1
		//

		vIndex = faces[i].vIndex1 - 1;
		tIndex = faces[i].tIndex1 - 1;
		nIndex = faces[i].nIndex1 - 1;

		vertex.Pos = DirectX::XMFLOAT3(_vertices.at(vIndex).x, _vertices.at(vIndex).y, _vertices.at(vIndex).z);
		vertex.Normal = DirectX::XMFLOAT3(_normals.at(nIndex).x, _normals.at(nIndex).y, _normals.at(nIndex).z);
		vertex.Tex = DirectX::XMFLOAT2(_textureCoords.at(tIndex).x, _textureCoords.at(tIndex).y);
		_objectVertexs.push_back(vertex);

		//
		// Vertex 2
		//

		vIndex = faces[i].vIndex2 - 1;
		tIndex = faces[i].tIndex2 - 1;
		nIndex = faces[i].nIndex2 - 1;

		vertex.Pos = DirectX::XMFLOAT3(_vertices.at(vIndex).x, _vertices.at(vIndex).y, _vertices.at(vIndex).z);
		vertex.Normal = DirectX::XMFLOAT3(_normals.at(nIndex).x, _normals.at(nIndex).y, _normals.at(nIndex).z);
		vertex.Tex = DirectX::XMFLOAT2(_textureCoords.at(tIndex).x, _textureCoords.at(tIndex).y);
		_objectVertexs.push_back(vertex);

		//
		// Vertex3
		//

		vIndex = faces[i].vIndex3 - 1;
		tIndex = faces[i].tIndex3 - 1;
		nIndex = faces[i].nIndex3 - 1;

		vertex.Pos = DirectX::XMFLOAT3(_vertices.at(vIndex).x, _vertices.at(vIndex).y, _vertices.at(vIndex).z);
		vertex.Normal = DirectX::XMFLOAT3(_normals.at(nIndex).x, _normals.at(nIndex).y, _normals.at(nIndex).z);
		vertex.Tex = DirectX::XMFLOAT2(_textureCoords.at(tIndex).x, _textureCoords.at(tIndex).y);
		_objectVertexs.push_back(vertex);
	}

	// setup indices
	for (unsigned short i = 0; i< (_objInfo.faceCount * 3); i++)
	{
		_indices.push_back(i);
	}

	_numVertices = static_cast<int>(_objectVertexs.size());
	_numIndices = static_cast<int>(_indices.size());
}