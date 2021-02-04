#ifndef GAMEINTERFACE_H
#define GAMEINTERFACE_H

//abstract parent class: do not create instance
class GameInterface {
public:
	GameInterface() {};
	virtual ~GameInterface() {};

	virtual bool OnCreate() = 0;
	virtual void Update(const float dTime) = 0;
	virtual void Render() = 0;
};

#endif //GAMEINTERFACE_H