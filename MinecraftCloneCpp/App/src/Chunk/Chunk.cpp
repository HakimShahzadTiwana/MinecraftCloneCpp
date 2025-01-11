#include "Chunk.h"
#include "Debugging/Logger.h"
#include <random>

Chunk::Chunk()
{
	mBlocks.reserve(ChunkInfo::chunkWidth * ChunkInfo::chunkHeight * ChunkInfo::chunkLength);
}

void Chunk::generateChunk()
{

	// ToDO  Create sperate class for this
	// Create a random device (for seeding)
	std::random_device rd;

	// Use a Mersenne Twister engine
	std::mt19937 gen(rd());

	// Define the range
	std::uniform_int_distribution<int> dist(0,1);


	mGenerationTimer.start();

	for (int x = 0; x < ChunkInfo::chunkWidth; ++x)
	{
		for (int y = 0; y < ChunkInfo::chunkHeight; ++y)
		{
			for (int z = 0; z < ChunkInfo::chunkLength; ++z)
			{

				int randomNumber = dist(gen);
				BlockType type = BlockType::Grass;

				glm::vec3 blockPos = glm::vec3(x, y, z);

				//Place block in chunk
				mBlocks.emplace_back(type, blockPos);
				Block& currentBlock = mBlocks.back();

				// Add faces to the blocks that are at the sides of the chunk
				{
					if (blockPos.x == 0)
					{
						currentBlock.AddFace(BlockFace::Left);
					}

					if (blockPos.x == ChunkInfo::chunkWidth - 1)
					{
						currentBlock.AddFace(BlockFace::Right);
					}

					if (blockPos.y == 0)
					{
						currentBlock.AddFace(BlockFace::Bottom);
					}

					if (blockPos.y == ChunkInfo::chunkHeight - 1)
					{
						currentBlock.AddFace(BlockFace::Top);
					}

					if (blockPos.z == 0)
					{
						currentBlock.AddFace(BlockFace::Back);
					}

					if (blockPos.z == ChunkInfo::chunkLength - 1)
					{
						currentBlock.AddFace(BlockFace::Front);
					}
				}

				int above  = getFlattenedIndex(glm::vec3(blockPos.x    , blockPos.y + 1, blockPos.z    ));
				int below  = getFlattenedIndex(glm::vec3(blockPos.x    , blockPos.y - 1, blockPos.z    ));
				int right  = getFlattenedIndex(glm::vec3(blockPos.x + 1, blockPos.y    , blockPos.z    ));
				int left   = getFlattenedIndex(glm::vec3(blockPos.x - 1, blockPos.y    , blockPos.z    ));
				int front  = getFlattenedIndex(glm::vec3(blockPos.x    , blockPos.y    , blockPos.z + 1));
				int behind = getFlattenedIndex(glm::vec3(blockPos.x    , blockPos.y    , blockPos.z - 1));

				

				// Add faces to blocks that are next to transparent blocks
				if (currentBlock.isTransparent())
				{
					if (above < mBlocks.size() && !mBlocks[above].isTransparent())
					{
						mBlocks[above].AddFace(BlockFace::Bottom);
					}

					if (below < mBlocks.size() && !mBlocks[below].isTransparent())
					{
						mBlocks[below].AddFace(BlockFace::Top);
					}

					if (right < mBlocks.size() && !mBlocks[right].isTransparent())
					{
						mBlocks[right].AddFace(BlockFace::Back);
					}

					if (left < mBlocks.size() && !mBlocks[left].isTransparent())
					{
						mBlocks[left].AddFace(BlockFace::Front);
					}

					if (front < mBlocks.size() && !mBlocks[front].isTransparent())
					{
						mBlocks[front].AddFace(BlockFace::Left);
					}

					if (behind < mBlocks.size() && !mBlocks[behind].isTransparent())
					{
						mBlocks[behind].AddFace(BlockFace::Right);
					}
				}

					
				// If block is not transparent check if there are any surrounding blocks. 
				else 
				{
					if (above < mBlocks.size() && mBlocks[above].isTransparent())
					{
						currentBlock.AddFace(BlockFace::Top);
					}

					if (below < mBlocks.size() && mBlocks[below].isTransparent())
					{
						currentBlock.AddFace(BlockFace::Bottom);
					}

					if (right < mBlocks.size() && mBlocks[right].isTransparent())
					{
						currentBlock.AddFace(BlockFace::Right);
					}

					if (left < mBlocks.size() && mBlocks[left].isTransparent())
					{
						currentBlock.AddFace(BlockFace::Left);
					}

					if (front < mBlocks.size() && mBlocks[front].isTransparent())
					{
						currentBlock.AddFace(BlockFace::Front);
					}

					if (behind < mBlocks.size() && mBlocks[behind].isTransparent())
					{
						currentBlock.AddFace(BlockFace::Back);
					}
				}


			}
		}
	}

	float generatedTime = mGenerationTimer.stop();
	LOG(Log, " Chunk Generation time {}", generatedTime);
}

void Chunk::draw()
{
	mDrawTimer.start();
	for(auto& block : mBlocks )
	{
		
		block.draw();
		
	}
	//float drawTime = drawTimer.stop();
}

int Chunk::getFlattenedIndex(glm::vec3 pos)
{
	return pos.x + (pos.y * ChunkInfo::chunkWidth) + (pos.z * ChunkInfo::chunkWidth * ChunkInfo::chunkHeight);
}

glm::vec3 Chunk::get3DIndex(int index)
{
	int x = index % ChunkInfo::chunkWidth; // Calculate the x-coordinate
	int y = (index / ChunkInfo::chunkWidth) % ChunkInfo::chunkHeight; // Calculate the y-coordinate
	int z = index / (ChunkInfo::chunkWidth * ChunkInfo::chunkHeight); // Calculate the z-coordinate

	return glm::vec3(x, y, z);
}




