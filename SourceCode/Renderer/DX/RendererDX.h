#ifndef RENDERERDX_H
#define RENDERERDX_H

#include "../Common.h"
#include "Renderer.h"
#include "../GraphicsContainer.h"

class RendererDX : public Renderer
{
private:
	std::vector<GraphicsContainer*> renderQueue;
protected:
public:
	RendererDX();
	~RendererDX();

	void init()	;
	void update(double delta);
};

#endif //RENDERERDX_H