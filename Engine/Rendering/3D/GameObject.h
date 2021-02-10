#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "Model.h"

class GameObject {
private:
	Model* model;
public:
	GameObject(Model* _model = nullptr);
	virtual ~GameObject();

	//Draw the attached model to the screen, if present
	void Render();
};

#endif//GAMEOBJECT_H