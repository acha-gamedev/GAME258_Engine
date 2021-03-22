#include "Mesh.h"
#include <glm/gtc/type_ptr.hpp>

Mesh::Mesh(SubMesh& _submesh, GLuint _shader) : vao(0), vbo(0),
	shader(_shader), modelLoc(0), viewLoc(0), projectionLoc(0), textureLoc(0) {
	submesh = _submesh;
	GenerateBuffers();
}

Mesh::~Mesh() {
	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &vbo);
	submesh.vertices.clear();
	submesh.indexList.clear();
}

void Mesh::Render(std::vector<glm::mat4> transform, const Camera* camera) {
	glUniform1i(textureLoc, 0);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, submesh.textureID);
	glBindVertexArray(vao);
	glEnable(GL_DEPTH_TEST);

	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(camera->GetViewMatrix()));
	glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(camera->GetPerspectiveMatrix()));
	glUniform3fv(cameraPosLoc, 1, glm::value_ptr(camera->GetPosition()));
	glUniform3fv(lightPosLoc, 1, glm::value_ptr(camera->GetLights().front()->GetPosition()));
	glUniform1f(lightAmbiLoc, camera->GetLights().front()->GetAmbient());
	glUniform1f(lightDiffLoc, camera->GetLights().front()->GetDiffuse());
	glUniform1f(lightSpecLoc, camera->GetLights().front()->GetSpecular());
	glUniform3fv(lightColourLoc, 1, glm::value_ptr(camera->GetLights().front()->GetColour()));

	for (int i = 0; i < transform.size(); i++) {
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(transform[i]));
		glDrawArrays(GL_TRIANGLES, 0, submesh.vertices.size());
	}

	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Mesh::GenerateBuffers() {
	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, submesh.vertices.size() * sizeof(Vertex), &submesh.vertices[0], GL_STATIC_DRAW);

	//Position
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)0);
	//Normal
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, normal));
	//TexCoords
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, uvCoords));
	//Colour
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, rgbValue));

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	modelLoc = glGetUniformLocation(shader, "model");
	viewLoc = glGetUniformLocation(shader, "view");
	projectionLoc = glGetUniformLocation(shader, "projection");
	textureLoc = glGetUniformLocation(shader, "inputTexture");
	cameraPosLoc = glGetUniformLocation(shader, "cameraPos");
	lightPosLoc = glGetUniformLocation(shader, "light.position");
	lightAmbiLoc = glGetUniformLocation(shader, "light.ambient");
	lightDiffLoc = glGetUniformLocation(shader, "light.diffuse");
	lightSpecLoc = glGetUniformLocation(shader, "light.specular");
	lightColourLoc = glGetUniformLocation(shader, "light.colour");
}