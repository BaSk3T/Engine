#ifndef CHARACTERRENDERER_H
#define CHARACTERRENDERER_H

#include "../Renderer.h"

class CharacterRenderer : public Renderer
{
public:
	CharacterRenderer();
	~CharacterRenderer();

	virtual void RenderFrame();
};

#endif // !CHARACTERRENDERER_H
