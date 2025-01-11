#include "Block.h"
#include "Debugging/Logger.h"
#include "GlobalProperties.h"
#include <glm/gtc/matrix_transform.hpp>

std::unique_ptr<Shader> Block::mShader = nullptr;

Block::Block(BlockType type, glm::vec3 pos) : blockType(type), position(pos)
{
	// Runs only once
	InitStatics();

	// Do nothing for air
	if (type == BlockType::Air) 
	{
		bIsTransparent = true;
		return;
	}
	
	if (!BlockTextures.contains(type)) 
	{
		LOG(Warning, "No texture associated with block type {}", static_cast<int>(type));
	}

	mTexture = std::make_unique<Texture>(BlockTextures[type]);
	


}

Block::~Block()
{
	mVao.cleanUp();
	mVbo.cleanUp();
}

void Block::uploadData()
{
	// Bind buffers
	mVao.bind();
	mVbo.bind();

	// upload data to buffers
	mVbo.uploadData(mVertexData.data(), sizeof(float) * mVertexData.size());

	// Link buffers to vao
	mVao.LinkVBO(mVbo, 0, 3, 5 * sizeof(float), 0);
	mVao.LinkVBO(mVbo, 1, 2, 5 * sizeof(float), 3 * sizeof(float));

	// Unbind buffers
	mVao.unBind();
	mVbo.unBind();
}

void Block::draw()
{
	if (blockType == BlockType::Air) 
	{
		return;
	}

	mShader->activate();

	mShader->setInt("texSampler1", 0);

	glm::mat4 model = glm::mat4(1.0);
	model = glm::translate(model, position);
	//model = glm::scale(model, scale);
	mShader->setMat4f("model", model);

	mShader->setMat4f("view", CameraProperties::viewMatrix);

	glm::mat4 projection = glm::mat4(1.0f);
	projection = glm::perspective(glm::radians(CameraProperties::fov), (float) WindowProperties::width / WindowProperties::height , 0.1f, 100.0f);
	mShader->setMat4f("projection", projection);

	
	mTexture->bind();
	mTexture->setActiveTexture(0);

	mVao.bind();
	glDrawArrays(GL_TRIANGLES, 0, 36);
	mVao.unBind();
	mTexture->unbind();
}

void Block::AddFace(BlockFace face)
{
	auto [pos, bInserted] = mRenderedFaces.insert(face);
	
	if (bInserted)
	{
		for (auto data : FaceVertexData[face]) 
		{
			AddVertexData(data);
		}
		uploadData();
	}
}

void Block::AddAllFaces()
{
	for (int i = 0; i < 6; i++) 
	{
		AddFace(static_cast<BlockFace>(i));
	}
}

void Block::RemoveFace(BlockFace face)
{
	
	auto removeCount = mRenderedFaces.erase(face);

	if (removeCount) 
	{
		mVertexData.clear();
		for (auto faces : mRenderedFaces) 
		{
			for (auto data : FaceVertexData[face])
			{
				AddVertexData(data);
			}
		}
		uploadData();
	}
	

}

bool Block::isTransparent()
{
	return bIsTransparent;
}

void Block::AddVertexData(const BlockVertex& data)
{
	mVertexData.push_back(data.position.x);
	mVertexData.push_back(data.position.y);
	mVertexData.push_back(data.position.z);

	mVertexData.push_back(data.uv.x);
	mVertexData.push_back(data.uv.y);
}

void Block::InitStatics()
{
	static bool bInitialized = false;
	if (!bInitialized)
	{
		// Init Shader
		mShader = std::make_unique<Shader>("App/Shaders/BlockShader.vert", "App/Shaders/BlockShader.frag");

		bInitialized = true;
	}
	
}

