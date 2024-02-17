#pragma once
#include "TexturedShapeDrawer.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


class TransformableTextureShapeShader: public TexturedShapeDrawer
{
private:
	glm::mat4 modelTransformation;
	glm::mat4 viewTransformation;
	glm::mat4 projectionTransformation;
	unsigned int modelLoc;
	unsigned int viewLoc;
	unsigned int projectionLoc;

public:
	TransformableTextureShapeShader(const char* vertexShaderPath, const char* fragmentShaderPath, 
		unsigned int* textureIds, unsigned int texutresNumber, unsigned int& VAO, unsigned int& VBO, unsigned int&  EBO,  glm::mat4 * modelTransformation,
		glm::mat4* viewTransformation, glm::mat4* projectionTransformation) :
		TexturedShapeDrawer(vertexShaderPath, fragmentShaderPath, VAO, VBO,EBO, textureIds, texutresNumber),
		modelTransformation(*modelTransformation),
		viewTransformation(*viewTransformation),
		projectionTransformation(*projectionTransformation)
	{
		modelLoc = glGetUniformLocation(shaderProgramId, "model");
		viewLoc = glGetUniformLocation(shaderProgramId, "view");
		projectionLoc = glGetUniformLocation(shaderProgramId, "projection");
	};
	TransformableTextureShapeShader(const char* vertexShaderPath, const char* fragmentShaderPath, unsigned int& VAO, unsigned int& VBO, unsigned int& EBO, unsigned int* textureIds, unsigned int texutresNumber) :
		TexturedShapeDrawer(vertexShaderPath, fragmentShaderPath,  VAO, VBO, EBO, textureIds, texutresNumber)
	{
		modelTransformation = glm::mat4(1.0f);
		viewTransformation = glm::mat4(1.0f);
		projectionTransformation = glm::mat4(1.0f);

		modelLoc = glGetUniformLocation(shaderProgramId, "model");
		viewLoc = glGetUniformLocation(shaderProgramId, "view");
		projectionLoc = glGetUniformLocation(shaderProgramId, "projection");
	};
	virtual void drawShape(int shapeIdx)
	{
		glUseProgram(shaderProgramId);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelTransformation));
		glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projectionTransformation));
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(viewTransformation));
		TexturedShapeDrawer::drawShape(shapeIdx);
	};
	virtual void drawAllShapes()
	{
		glUseProgram(shaderProgramId);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelTransformation));
		glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projectionTransformation));
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(viewTransformation));
		TexturedShapeDrawer::drawAllShapes();
	};

	virtual void drawAllTriangles()
	{
		glUseProgram(shaderProgramId);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelTransformation));
		glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projectionTransformation));
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(viewTransformation));
		TexturedShapeDrawer::drawAllTriangles();
	};


	void transferTraingles(float vertices[], int vertices_sizeof, int singleVerticleElemsNum, int singleVerticleDataElemsNum);

	void setModelTransformation(glm::mat4* newModelTransformation) {
		modelTransformation = *newModelTransformation;
	};
	void setViewTransformation(glm::mat4* newViewTransformation) {
		viewTransformation = *newViewTransformation;
	};
	void setProjectionTransformation(glm::mat4* newProjectionTransformation) {
		projectionTransformation = *newProjectionTransformation;
	};
};