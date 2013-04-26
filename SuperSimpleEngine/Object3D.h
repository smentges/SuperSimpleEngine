#pragma once
class Object3D
{
public:
	virtual void draw(float deltatime);
	Object3D(void);
	~Object3D(void);
};

