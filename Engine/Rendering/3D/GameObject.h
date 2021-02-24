#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "Model.h"

class GameObject {
protected:
	Model* model;
public:
	GameObject(Model* _model = nullptr);
	virtual ~GameObject();

	//Draw the attached model to the screen, if present
	void Render(Camera* camera);
};

#endif//GAMEOBJECT_H