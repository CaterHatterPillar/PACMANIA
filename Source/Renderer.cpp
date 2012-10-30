#include "Renderer.h"

std::vector<MsgRender*>* Renderer::renderList;

Renderer::~Renderer()
{
	if(renderList)
	{
		for(int i = 0; i < (int)renderList->size(); i++)
		{
			if(renderList->at(i))
				delete renderList->at(i);
		}
		delete renderList;
	}
}