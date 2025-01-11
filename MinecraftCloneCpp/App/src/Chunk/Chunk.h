#pragma once
#include "App/src/Blocks/Block.h"
#include "Debugging/Timer.h"
#include <vector>

struct ChunkInfo
{
	static constexpr int chunkLength = 5;
	static constexpr int chunkWidth = 5;
	static constexpr int chunkHeight = 5;
};

// TODO Maybe implement move semantics for blocks
class Chunk 
{
	public:
		Chunk();

		void generateChunk();

		void draw();


private:

	int getFlattenedIndex(glm::vec3 pos);

	glm::vec3 get3DIndex(int index);
	private:

		std::vector<Block> mBlocks;
		Timer mGenerationTimer;
		Timer mDrawTimer;


};


