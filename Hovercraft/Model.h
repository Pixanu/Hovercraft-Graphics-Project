#pragma once

#include "Mesh.h"
#include "Texture.h"
#include "Shader.h"
#include "Material.h"
#include "OBJloader.h"

class Model
{

private:
	Material* material;
	Texture* overrideTextureDiffuse;
	Texture* overrideTextureSpecular;
	std::vector<Mesh*> meshes;
	glm::vec3 position;

	void updateUniforms()
	{

	}


public:

	Model(
		glm::vec3 position,
		Material* material,
		Texture* overDiffuse,
		Texture* overSpecular,
		std::vector<Mesh*>& meshes)
	{
		this->position = position;
		this->material = material;
		this->overrideTextureDiffuse = overDiffuse;
		this->overrideTextureSpecular = overSpecular;

		for (auto* i : meshes)
		{
			this->meshes.push_back(new Mesh(*i));
		}

		for (auto& i : this->meshes)
		{
			i->move(this->position);
			i->setOrigin(this->position);
		}
	}

	//OBJ FILE MODEL
	Model(
		glm::vec3 position,
		Material* material,
		Texture* overDiffuse,
		Texture* overSpecular,
		const char* objFile)
	{

		std::vector<Vertex> mesh = loadOBJ(objFile);
		this->meshes.push_back(new Mesh(mesh.data(), mesh.size(), NULL, 0, glm::vec3(1.f, 0.f, 0.f),
			glm::vec3(0.f),
			glm::vec3(0.f),
			glm::vec3(1.f)));

		this->position = position;
		this->material = material;
		this->overrideTextureDiffuse = overDiffuse;
		this->overrideTextureSpecular = overSpecular;

		

		for (auto& i : this->meshes)
		{
			i->move(this->position);
			i->setOrigin(this->position);
		}
	}


	~Model()
	{

		for (auto*& i : this->meshes)
			delete i;

	}

	//FUNCTIONS

	void rotate(const glm::vec3 roatation)
	{
		for (auto& i : this->meshes)
			i->rotate(roatation);
	}

	void update()
	{

	}

	void render(Shader* shader)
	{

		this->updateUniforms();

		//UPDATE THE UNIFORMS
		this->material->sendToShader(*shader);

		//use a program
		shader->use();

		//DRAW
		for (auto& i : this->meshes)
		{
			//activate textures  for each mesh
			this->overrideTextureDiffuse->bind(0);
			this->overrideTextureSpecular->bind(1);

			i->render(shader);//activates shader
		}


	}


};