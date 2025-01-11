#pragma once
#include <iostream>
#include <vector>
#include <set>

#include "BlockInfo.h"
#include "openGL/Texture/Texture.h"
#include "openGL/shader/Shader.h"
#include "openGL/buffer/VAO.h"
#include "openGL/buffer/VBO.h"



class Block
{
public:

	Block(BlockType type, glm::vec3 pos);
	Block(Block&&) = default;
	~Block();
	

	BlockType blockType;

	// Transform
	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 scale = glm::vec3(1.0f);
	

public:

	void uploadData();
	void draw();

	// Adds the face to the block for rendering.
	void AddFace(BlockFace Face);

	void AddAllFaces();
	// Removes face for rendering
	void RemoveFace(BlockFace Face);

	bool isTransparent();
	
private:

	// Blocks use the same shader
	static std::unique_ptr<Shader> mShader;
	
	// Contains the faces that the block is currently rendering
	std::set<BlockFace> mRenderedFaces;

	// Stores the Mesh data in openGL usable format
	std::vector<GLfloat> mVertexData;

	// Each block can have different textures.
	std::unique_ptr<Texture> mTexture;

	VAO mVao;
	VBO mVbo;

	// Can we see through the block?
	bool bIsTransparent = false;
	
	

private:

	// Runs only once, the first time an object of this class was made.
	static void InitStatics();

	void AddVertexData(const BlockVertex& data);


	
};

