#include "WorldChunks.h"

void WorldChunks::generateChunks()
{
	for (int i = 0; i < 3; ++i) 
	{
		for (int j = 0; j < 3; ++j) 
		{
			chunks.emplace_back(glm::vec3(ChunkInfo::chunkWidth * i, -ChunkInfo::chunkHeight, ChunkInfo::chunkLength * j));
			chunks.back().generateChunk();
		}
	}
}

void WorldChunks::draw()
{
	for (auto& chunk : chunks) 
	{
		chunk.draw();
	}
}
