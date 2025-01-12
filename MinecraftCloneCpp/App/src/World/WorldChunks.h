#pragma once
#include <vector>
#include <App/src/Chunk/Chunk.h>

class WorldChunks 
{
public:
	std::vector<Chunk> chunks;

	WorldChunks() {};
	
	void generateChunks();

	void draw();


};