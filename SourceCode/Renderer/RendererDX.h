#ifndef RENDERERDX_H
#define RENDERERDX_H

#include "Renderer.h"

class RendererDX : public Renderer
{
private:
protected:
public:
	RendererDX();
	~RendererDX();

	void init()	;
	void update(double delta);
};

#endif //RENDERERDX_H