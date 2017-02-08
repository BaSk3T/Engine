#ifndef RENDERER_H
#define RENDERER_H

class Renderer
{
public:
	Renderer();
	virtual ~Renderer();

	virtual void RenderFrame() = 0;
};

#endif // !RENDERER_H
