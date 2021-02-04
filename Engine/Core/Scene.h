#ifndef SCENE_H
#define SCENE_H

//abstract parent class: do not create instance
class Scene {
public:
	Scene() {};
	virtual ~Scene() {};

	virtual bool OnCreate() = 0;
	virtual void Update(const float dTime) = 0;
	virtual void Render() = 0;
};

#endif //SCENE_H