//#include "Maze.h"
//
//void Maze::draw()
//{
//	//Draw maze
//	// compute culling
//	int cullingSize = 5;
//	int yStart = cullingPosition.y - cullingSize;
//	int yEnd = cullingPosition.y - cullingSize;
//
//	for(int y = 0; y<sizeY; y++)
//	{
//		for(int x = 0; x<sizeX; x++)
//		{
//			if(getTile(x,y)==1)
//			{
//				MatF4 scale;
//				scale.scaling(0.5f,0.5f,0.5f);
//				MsgRender* renderMsg = new MsgRender(gcWall, getTranslation(x,y), MatF4(), scale);
//				Singleton<ObserverDirector>::get().push(renderMsg);
//			}
//		}
//	}
//
//	// Draw pills
//	int pillsEaten = 0;
//	int pillsTotal = 0;
//	pillsTotal = 10;
//	for(int i = 0; i<(int)pills.size(); i++)
//	{
//		if(!pills[i].isAlive)
//		{
//			pillsEaten++;
//		}
//		pillsTotal++;
//	}
//
//	for(int i = 0; i<(int)pills.size(); i++)
//	{
//		float size = pills[i].getSize();
//		if(size>0.0f)
//		{
//			pills[i].setTotalFactor(pillsEaten, pillsTotal);
//
//			MatF4 scale;
//			int x = pills[i].pos.x;
//			int y = pills[i].pos.y;
//			if(!pills[i].isBloody)
//			{
//				scale.scaling(size*0.15f,size*0.2f,size*0.15f);
//				MsgRender* renderMsg = new MsgRender(gcPill, getTranslation(x,y), MatF4(), scale);
//				Singleton<ObserverDirector>::get().push(renderMsg);
//			}
//			if(pills[i].isBloody)
//			{
//				scale.scaling(size*0.25f,size*0.35f,size*0.25f);
//				MsgRender* renderMsg = new MsgRender(gcPillBloody, getTranslation(x,y), MatF4(), scale);
//				Singleton<ObserverDirector>::get().push(renderMsg);
//			}
//		}
//	}
//}
//
