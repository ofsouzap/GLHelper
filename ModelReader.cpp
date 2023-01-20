#include "ModelReader.h"

using namespace GLHelper;

void ModelReader::readOBJModel(string filename, int* outVertCount, GLfloat** outPos, GLfloat** outUV, GLfloat** outNorm)
{

	// Read file lines

	vector<string> lines = FileReader::readFileLines(filename);
	int line_index = 0;

	if (lines.size() == 0)
		throw new FileNotOBJFileException();

	// Prepare data vectors

	vector<unsigned int> posInds, uvInds, normInds;
	vector<pos_t> pos;
	vector<uv_t> uv;
	vector<norm_t> norm;

	// Read file model details

	while (line_index < lines.size())
	{

		// Read a line

		string line = lines[line_index++];

		// Get parts of line

		string command, values;

		int sep_ind = line.find(" ");
		if (sep_ind != string::npos)
		{
			command = line.substr(0, sep_ind);
			values = line.substr(sep_ind);
		}
		else
		{
			command = line;
			values = "";
		}

		// Act on the command

		if (line.substr(0, 1) == "#")
			continue; // A comment line
		else if (command == "v")
		{
			
			// Vertex position

			pos_t vPos = pos_t();

			// Read components
			sscanf(values.c_str(), "%f %f %f", &vPos.x, &vPos.y, &vPos.z);

			// Store new vertex
			pos.push_back(vPos);

		}
		else if (command == "vt")
		{

			// Vertex UV coordinate

			uv_t vUV = uv_t();

			// Read components
			sscanf(values.c_str(), "%f %f", &vUV.u, &vUV.v);

			// Store new UV coord
			uv.push_back(vUV);

		}
		else if (command == "vn")
		{

			// Vertex normal vector

			norm_t vNorm = norm_t();

			// Read components
			sscanf(values.c_str(), "%f %f %f", &vNorm.x, &vNorm.y, &vNorm.z);

			// Store new normal
			norm.push_back(vNorm);

		}
		else if (command == "f")
		{

			// A triangle

			struct {
				int posInd, uvInd, normInd;
			} vert[3] = {};

			// Read vertex data indexes

			sscanf(
				values.c_str(),
				"%d/%d/%d %d/%d/%d %d/%d/%d",
				&vert[0].posInd,
				&vert[0].uvInd,
				&vert[0].normInd,
				&vert[1].posInd,
				&vert[1].uvInd,
				&vert[1].normInd,
				&vert[2].posInd,
				&vert[2].uvInd,
				&vert[2].normInd
				);

			// Write into index vectors

			posInds.push_back(vert[0].posInd);
			posInds.push_back(vert[1].posInd);
			posInds.push_back(vert[2].posInd);

			uvInds.push_back(vert[0].uvInd);
			uvInds.push_back(vert[1].uvInd);
			uvInds.push_back(vert[2].uvInd);

			normInds.push_back(vert[0].normInd);
			normInds.push_back(vert[1].normInd);
			normInds.push_back(vert[2].normInd);

		}

	}

	// Create buffers from read information

	int vertCount = posInds.size();

	int posCount = vertCount * 3;
	int uvCount = vertCount * 2;
	int normCount = vertCount * 3;

	vector<float> objPosVec(posCount);
	vector<float> objUVVec(uvCount);
	vector<float> objNormVec(normCount);

	int currPos = 0;
	int currUV = 0;
	int currNorm = 0;

	// Translate indices of data into data lists for returning

	for (int i = 0; i < vertCount; i++)
	{

		// Get indices of data to use
		int posInd = posInds[i] - 1;
		int uvInd = uvInds[i] - 1;
		int normInd = normInds[i] - 1;

		// Get data to use
		pos_t vPos = pos[posInd];
		uv_t vUV = uv[uvInd];
		norm_t vNorm = norm[normInd];

		// Store position data
		objPosVec[currPos++] = vPos.x;
		objPosVec[currPos++] = vPos.y;
		objPosVec[currPos++] = vPos.z;

		// Store UV data
		objUVVec[currUV++] = vUV.u;
		objUVVec[currUV++] = vUV.v;

		// Store normal data
		objNormVec[currNorm++] = vNorm.x;
		objNormVec[currNorm++] = vNorm.y;
		objNormVec[currNorm++] = vNorm.z;

	}

	// Set vertex count output
	*outVertCount = vertCount;

	// Allocate output arrays
	*outPos = new float[objPosVec.size()];
	*outUV = new float[objUVVec.size()];
	*outNorm = new float[objNormVec.size()];

	// Copy data into output arrays
	std::copy(objPosVec.begin(), objPosVec.end(), *outPos);
	std::copy(objUVVec.begin(), objUVVec.end(), *outUV);
	std::copy(objNormVec.begin(), objNormVec.end(), *outNorm);

}
