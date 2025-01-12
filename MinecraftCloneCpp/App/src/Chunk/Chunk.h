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

		Chunk(glm::vec3 pos);
		Chunk(Chunk&& other) = default;
		void generateChunk();

		void draw();

		

private:

	// Checks if the block is placed at the one of the sides of the chunk and adds the corresponding face
	void HandleChunkFaces(Block& block);

	// Adds block faces for blocks that are in contact with transparent blocks.
	void HandleTransparentFaces(Block& block);


	// Utility : Gets the flattened 1D index from a 3D position
	int getFlattenedIndex(glm::vec3 pos);

	// Utility : Gets the 3D index from a flattened 1D index
	glm::vec3 get3DIndex(int index);


	private:

		glm::vec3 position;

		std::vector<Block> mBlocks;
		Timer mGenerationTimer;
		Timer mDrawTimer;


};


