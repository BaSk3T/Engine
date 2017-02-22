#ifndef RENDERER_H
#define RENDERER_H

#include <string>

class Renderer
{
public:
	Renderer();
	virtual ~Renderer();

	virtual void RenderFrame() = 0;
	virtual void Translate(float x, float y, float z, float w) = 0;

	void SetName(std::string name) { m_Name = name; };

private:
	std::string m_Name;
};

#endif // !RENDERER_H
