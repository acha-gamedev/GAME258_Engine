#include "Mesh.h"
#include <glm/gtc/type_ptr.hpp>

Mesh::Mesh(std::vector<Vertex>& _vertexlist, GLuint _shader) : vao(0), vbo(0), vertices(std::vector<Vertex>()), 
	shader(_shader), modelLoc(0), viewLoc(0), projectionLoc(0) {
	vertices = _vertexlist;
	GenerateBuffers();
}

Mesh::~Mesh() {
	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &vbo);
	vertices.clear();
}

void Mesh::Render(const glm::mat4 transform, const Camera* camera) {
	glBindVertexArray(vao);
	glEnable(GL_DEPTH_TEST);
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(transform));
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(camera->GetViewMatrix()));
	glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(camera->GetPerspectiveMatrix()));
	glDrawArrays(GL_TRIANGLES, 0, vertices.size());
	glBindVertexArray(0);
}

void Mesh::GenerateBuffers() {
	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

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
}