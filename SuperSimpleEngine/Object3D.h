//Minigolf program by Jason Knox and Shea Mentges
#pragma once
class Object3D
{
public:
	virtual void draw(float deltatime);
	Object3D(void);
	~Object3D(void);
};

