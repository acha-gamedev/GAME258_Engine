#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "Model.h"

class GameObject {
protected:
	glm::vec3 position;
	float angle;
	glm::vec3 rotation;
	glm::vec3 scale;
	Model* model;
	unsigned int modelInstance;
	std::string tag;
	BoundingBox boundingBox;
	bool hitStatus;
public:
	GameObject(Model* _model = nullptr);
	GameObject(glm::vec3 _position, Model* _model);
	virtual ~GameObject();

	//Draw the attached model to the screen, if present
	void Render(const Camera* camera);
	//Perform time-based actions
	void Update(const float dTime);

	inline glm::vec3 GetPosition() const { return position; }
	inline glm::vec3 GetRotation() const { return rotation; }
	inline float GetAngle() const { return angle; }
	inline glm::vec3 GetScale() const { return scale; }
	inline std::string GetTag() const { return tag; }
	inline BoundingBox* GetBoundingBox() { return &boundingBox; }
	inline bool GetHitStatus() const { return hitStatus; }

	void SetPosition(const glm::vec3 _position);
	void SetRotation(const glm::vec3 _rotation);
	void SetAngle(const float _angle);
	void SetScale(const glm::vec3 _scale);
	inline void SetTag(const std::string _tag) { tag = _tag; }
	void SetHitStatus(bool _hitStatus, int buttonType);
};

#endif//GAMEOBJECT_H