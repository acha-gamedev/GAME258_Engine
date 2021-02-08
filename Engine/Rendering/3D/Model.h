#ifndef MODEL_H
#define MODEL_H

#include "Mesh.h"

class Model {
private:
	std::vector<Mesh*> meshes;
public:
	Model();
	~Model();

	//Draw all meshes to the screen
	void Render();

	//Add a mesh to the model
	void AddMesh(Mesh* _mesh);
};

#endif //MODEL_H