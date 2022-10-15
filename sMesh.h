#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <strstream>

#include "Vec.h"
#include "cTexture.h"

struct col
{
	float u;
	float v;
	float w = 1;
};

struct triangle
{
	vf3d p[3];
	col t[3];
};

struct sMesh
{
	std::list<triangle> listTris;
	unsigned int nTextureId;
};

bool LoadFromObjectFile(sMesh& mesh, const std::string& sObjFilename, const std::string& sTexFilename = std::string(""))
{
	std::ifstream f(sObjFilename);
	if (!f.is_open()) return false;

	// Local cache of verts
	std::vector<vf3d> verts;
	std::vector<col> texs;

	while (!f.eof())
	{
		char line[128];
		f.getline(line, 128);

		std::strstream s;
		s << line;

		char junk;

		if (line[0] == 'v')
		{
			if (line[1] == 't')
			{
				col v;
				s >> junk >> junk >> v.u >> v.v >> v.w;
				texs.push_back(v);
			}
			else
			{
				vf3d v;
				s >> junk >> v.x >> v.y >> v.z;
				verts.push_back(v);
			}
		}

		if (sTexFilename.empty())
		{
			if (line[0] == 'f')
			{
				int f[3];
				s >> junk >> f[0] >> f[1] >> f[2];
				mesh.listTris.push_back({ verts[f[0] - 1], verts[f[1] - 1], verts[f[2] - 1] });
			}
		}
		else
		{
			if (line[0] == 'f')
			{
				s >> junk;

				std::string tokens[6];
				int nTokenCount = -1;
				while (!s.eof())
				{
					char c = s.get();
					if (c == ' ' || c == '/')
					{
						if (tokens[nTokenCount].size() > 0)
							nTokenCount++;
					}
					else
						tokens[nTokenCount].append(1, c);
				}

				tokens[nTokenCount].pop_back();

				int stride = 1;
				if (!texs.empty()) stride++;

				if (!texs.empty())
				{
					mesh.listTris.push_back({
						{
							verts[stoi(tokens[0 * stride]) - 1],
							verts[stoi(tokens[1 * stride]) - 1],
							verts[stoi(tokens[2 * stride]) - 1]
						},
						{
							texs[stoi(tokens[0 * stride + 1]) - 1],
							texs[stoi(tokens[1 * stride + 1]) - 1],
							texs[stoi(tokens[2 * stride + 1]) - 1],
						}
						});
				}
				else
				{
					mesh.listTris.push_back({
						{
							verts[stoi(tokens[0 * stride]) - 1],
							verts[stoi(tokens[1 * stride]) - 1],
							verts[stoi(tokens[2 * stride]) - 1]
						},
						{
							{ 0, 0, 0 },
							{ 0, 0, 0 },
							{ 0, 0, 0 }
						}
						});
				}
			}
		}
	}

	if (!sTexFilename.empty())
	{
		cTexture texture;

		if (!texture.LoadData(sTexFilename, true))
		{
			std::cout << texture.GetErrMessage() << std::endl;
			return false;
		}

		if (!texture.LoadTexture())
		{
			std::cout << texture.GetErrMessage() << std::endl;
			return false;
		}

		mesh.nTextureId = texture.GetId();
	}

	return true;
}

bool GenerateBuffers(sMesh& mesh, float* &vert_buffer, unsigned int& vert_size, unsigned int& vertices_count)
{
	if (mesh.listTris.empty())
		return false;

	bool bHasTexture = (mesh.nTextureId != 0);

	if (bHasTexture)
	{
		// 3 - x,y,z; 2 - u,v; 3 - vertices per triangle
		vert_size = mesh.listTris.size() * 3 * 2 * 3;
	}
	else
	{
		// 3 - x,y,z; 3 - vertices per triangle
		vert_size = mesh.listTris.size() * 3 * 3;
	}

	vert_buffer = new float[vert_size];

	int vert = 0;
	vertices_count = 0;

	for (const auto& tri : mesh.listTris)
	{
		// vertices, textures and normals
		
		vert_buffer[vert++] = tri.p[0].x;
		vert_buffer[vert++] = tri.p[0].y;
		vert_buffer[vert++] = tri.p[0].z;

		vert_buffer[vert++] = tri.t[0].u;
		vert_buffer[vert++] = tri.t[0].v;

		vert_buffer[vert++] = tri.p[1].x;
		vert_buffer[vert++] = tri.p[1].y;
		vert_buffer[vert++] = tri.p[1].z;

		vert_buffer[vert++] = tri.t[1].u;
		vert_buffer[vert++] = tri.t[1].v;

		vert_buffer[vert++] = tri.p[2].x;
		vert_buffer[vert++] = tri.p[2].y;
		vert_buffer[vert++] = tri.p[2].z;

		vert_buffer[vert++] = tri.t[2].u;
		vert_buffer[vert++] = tri.t[2].v;

		vertices_count++;
	}

	vert_size *= sizeof(float);

	return true;
}
