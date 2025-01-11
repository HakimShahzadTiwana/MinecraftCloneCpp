#pragma once
#include <glm/glm.hpp>
#include <unordered_map>
#include <vector>
#include <string>



struct BlockVertex
{
	// Postion Co-ordinates
	glm::vec3 position;

	// Texture Co-ordinates
	glm::vec2 uv;
};

enum class BlockType
{
	Air		= 0,
	Dirt	= 1,
	Grass	= 2,
	Stone	= 3

	

};

inline std::unordered_map<BlockType,std::string> BlockTextures =
{
	{BlockType::Dirt,"App/Textures/atlas/dirt_block.png"},
	{BlockType::Grass,"App/Textures/atlas/grass_block.png"},
	{BlockType::Stone, "App/Textures/atlas/stone_block.png"}
};


enum class BlockFace 
{ 
	Front,
	Back,
	Right,
	Left,
	Top,
	Bottom
};

inline std::unordered_map<BlockFace,std::vector<BlockVertex>> FaceVertexData =
{
	{BlockFace::Front,
						{	// Position						  // UVs
							{ glm::vec3(-0.5f, -0.5f, 0.5f)  , glm::vec2(0.0f, 0.0f) * 0.5f + glm::vec2(0.5f, 0.5f) }, // Bottom-left-front
							{ glm::vec3(0.5f, -0.5f, 0.5f)   , glm::vec2(1.0f, 0.0f) * 0.5f + glm::vec2(0.5f, 0.5f) }, // Bottom-right-front
							{ glm::vec3(0.5f, 0.5f, 0.5f)    , glm::vec2(1.0f, 1.0f) * 0.5f + glm::vec2(0.5f, 0.5f) }, // Top-right-front
							{ glm::vec3(0.5f, 0.5f, 0.5f)    , glm::vec2(1.0f, 1.0f) * 0.5f + glm::vec2(0.5f, 0.5f) }, // Top-right-front
							{ glm::vec3(-0.5f, 0.5f, 0.5f)   , glm::vec2(0.0f, 1.0f) * 0.5f + glm::vec2(0.5f, 0.5f) }, // Top-left-front
							{ glm::vec3(-0.5f, -0.5f, 0.5f)  , glm::vec2(0.0f, 0.0f) * 0.5f + glm::vec2(0.5f, 0.5f) }, // Bottom-left-front
						}
	},
	{BlockFace::Back, // Clockwise
						{	// Position						  // UVs
							{ glm::vec3(-0.5f, -0.5f, -0.5f) , glm::vec2(0.0f, 0.0f) * 0.5f + glm::vec2(0.5f, 0.5f) }, // Bottom-left-back
							{ glm::vec3(-0.5f, 0.5f, -0.5f)  , glm::vec2(0.0f, 1.0f) * 0.5f + glm::vec2(0.5f, 0.5f) }, // Top-left-back
							{ glm::vec3(0.5f, 0.5f, -0.5f)   , glm::vec2(1.0f, 1.0f) * 0.5f + glm::vec2(0.5f, 0.5f) }, // Top-right-back
							{ glm::vec3(0.5f, 0.5f, -0.5f)   , glm::vec2(1.0f, 1.0f) * 0.5f + glm::vec2(0.5f, 0.5f) }, // Top-right-back
							{ glm::vec3(0.5f, -0.5f, -0.5f)  , glm::vec2(1.0f, 0.0f) * 0.5f + glm::vec2(0.5f, 0.5f) }, // Bottom-right-back
							{ glm::vec3(-0.5f, -0.5f, -0.5f) , glm::vec2(0.0f, 0.0f) * 0.5f + glm::vec2(0.5f, 0.5f) }, // Bottom-left-back
						}
	},
	{BlockFace::Right, // Clockwise 
						{	// Position						  // UVs
							{ glm::vec3(0.5f, 0.5f, 0.5f)    , glm::vec2(0.0f, 1.0f) * 0.5f + glm::vec2(0.5f, 0.5f) }, // Top-right-front
							{ glm::vec3(0.5f, -0.5f, 0.5f)   , glm::vec2(0.0f, 0.0f) * 0.5f + glm::vec2(0.5f, 0.5f) }, // Bottom-right-front
							{ glm::vec3(0.5f, -0.5f, -0.5f)  , glm::vec2(1.0f, 0.0f) * 0.5f + glm::vec2(0.5f, 0.5f) }, // Bottom-right-back
							{ glm::vec3(0.5f, -0.5f, -0.5f)  , glm::vec2(1.0f, 0.0f) * 0.5f + glm::vec2(0.5f, 0.5f) }, // Bottom-right-back
							{ glm::vec3(0.5f, 0.5f, -0.5f)   , glm::vec2(1.0f, 1.0f) * 0.5f + glm::vec2(0.5f, 0.5f) }, // Top-right-back  
							{ glm::vec3(0.5f, 0.5f, 0.5f)    , glm::vec2(0.0f, 1.0f) * 0.5f + glm::vec2(0.5f, 0.5f) }, // Top-right-front
						}
	},
	{BlockFace::Left,
						{	// Position						  // UVs
							{ glm::vec3(-0.5f, 0.5f, 0.5f)   , glm::vec2(1.0f, 1.0f) * 0.5f + glm::vec2(0.5f, 0.5f) }, // Top-left-front
							{ glm::vec3(-0.5f, 0.5f, -0.5f)  , glm::vec2(0.0f, 1.0f) * 0.5f + glm::vec2(0.5f, 0.5f) }, // Top-left-back
							{ glm::vec3(-0.5f, -0.5f, -0.5f) , glm::vec2(0.0f, 0.0f) * 0.5f + glm::vec2(0.5f, 0.5f) }, // Bottom-left-back
							{ glm::vec3(-0.5f, -0.5f, -0.5f) , glm::vec2(0.0f, 0.0f) * 0.5f + glm::vec2(0.5f, 0.5f) }, // Bottom-left-back
							{ glm::vec3(-0.5f, -0.5f, 0.5f)  , glm::vec2(1.0f, 0.0f) * 0.5f + glm::vec2(0.5f, 0.5f) }, // Bottom-left-front
							{ glm::vec3(-0.5f, 0.5f, 0.5f)   , glm::vec2(1.0f, 1.0f) * 0.5f + glm::vec2(0.5f, 0.5f) }, // Top-left-front
						}
	},
	{BlockFace::Top, //Clockwise
						{	// Position						  // UVs
							{ glm::vec3(-0.5f, 0.5f, -0.5f)  , glm::vec2(0.0f, 0.0f) * 0.5f + glm::vec2(0.0f, 0.5f) }, // Top-left-back
							{ glm::vec3(-0.5f, 0.5f, 0.5f)   , glm::vec2(1.0f, 0.0f) * 0.5f + glm::vec2(0.0f, 0.5f) }, // Top-left-front
							{ glm::vec3(0.5f, 0.5f, 0.5f)    , glm::vec2(1.0f, 1.0f) * 0.5f + glm::vec2(0.0f, 0.5f) }, // Top-right-front
							{ glm::vec3(0.5f, 0.5f, 0.5f)    , glm::vec2(1.0f, 1.0f) * 0.5f + glm::vec2(0.0f, 0.5f) }, // Top-right-front
							{ glm::vec3(0.5f, 0.5f, -0.5f)   , glm::vec2(0.0f, 1.0f) * 0.5f + glm::vec2(0.0f, 0.5f) }, // Top-right-back
							{ glm::vec3(-0.5f, 0.5f, -0.5f)  , glm::vec2(0.0f, 0.0f) * 0.5f + glm::vec2(0.0f, 0.5f) }, // Top-left-back
						}
	},
	{BlockFace::Bottom,
						{	// Position						  // UVs
							{ glm::vec3(-0.5f, -0.5f, -0.5f) , glm::vec2(0.0f, 0.0f) * 0.5f }, // Bottom-left-back
							{ glm::vec3(0.5f, -0.5f, -0.5f)  , glm::vec2(0.0f, 1.0f) * 0.5f }, // Bottom-right-back
							{ glm::vec3(0.5f, -0.5f, 0.5f)   , glm::vec2(1.0f, 1.0f) * 0.5f }, // Bottom-right-front
							{ glm::vec3(0.5f, -0.5f, 0.5f)   , glm::vec2(1.0f, 1.0f) * 0.5f }, // Bottom-right-front
							{ glm::vec3(-0.5f, -0.5f, 0.5f)  , glm::vec2(1.0f, 0.0f) * 0.5f }, // Bottom-left-front
							{ glm::vec3(-0.5f, -0.5f, -0.5f) , glm::vec2(0.0f, 0.0f) * 0.5f }, // Bottom-left-back
						}
	},
};




