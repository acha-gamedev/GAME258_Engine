#ifndef MODEL_H
#define MODEL_H

#include "Mesh.h"

class Model {
private:
	GLuint shader;
	std::vector<Mesh*> meshes;
	glm::vec3 position;
	float angle;
	glm::vec3 rotation;
	glm::vec3 scale;
public:
	Model(GLuint _shader);
	Model(GLuint _shader, glm::vec3 _position, float _angle, glm::vec3 _rotation, glm::vec3 _scale);
	~Model();

	//Draw all meshes to the screen
	void Render(Camera* camera);

	//Add a mesh to the model
	void AddMesh(Mesh* _mesh);

	inline void SetPosition(const glm::vec3 _position) { position = _position; }
	inline glm::vec3 GetPosition() const { return position; }

	inline void SetAngle(const float _angle) { angle = _angle; }
	inline float GetAngle() const { return angle; }

	inline void SetRotation(const glm::vec3 _rotation) { rotation = _rotation; }
	inline glm::vec3 GetRotation() const { return rotation; }

	inline void SetScale(const glm::vec3 _scale) { scale = _scale; }
	inline glm::vec3 GetScale() const { return scale; }

private:
	glm::mat4 GetTransform() const;
};

#endif //MODEL_H