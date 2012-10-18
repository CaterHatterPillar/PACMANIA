//#include "Maze.h"
//#include "../Messaging/ObserverDirector.h"
//#include "../Singleton.h"
//
//Maze::Maze(GraphicsContainer* gcWall, GraphicsContainer* gcPill, GraphicsContainer* gcPillBloody)
//	{
//		this->gcWall = gcWall;
//		this->gcPill = gcPill; 
//		this->gcPillBloody = gcPillBloody; 
//
//		// Init grid
//		createMaze();
//	};
//
//void Maze::update(double delta)
//	{
//		//draw
//		draw();
//	};
//
//void Maze::draw()
//{
//	// Draw maze
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
//			if(getTile(x,y)==2)
//			{
//				MatF4 scale;
//				scale.scaling(0.1f,0.15f,0.1f);
//				MsgRender* renderMsg = new MsgRender(gcPill, getTranslation(x,y), MatF4(), scale);
//				Singleton<ObserverDirector>::get().push(renderMsg);
//			}
//			if(getTile(x,y)==3)
//			{
//				MatF4 scale;
//				scale.scaling(0.2f,0.3f,0.2f);
//				MsgRender* renderMsg = new MsgRender(gcPillBloody, getTranslation(x,y), MatF4(), scale);
//				Singleton<ObserverDirector>::get().push(renderMsg);
//			}
//		}
//	}
//};
//
//int Maze::getTile(int x, int y)
//{
//	// treat coordinates outside of maze as empty tiles
//	if(x<0 || y<0)
//		return 0;
//	if(x>=sizeX || y>=sizeY)
//		return 0;
//
//	// get maze tile
//	return grid[x][y];
//};
//
//void Maze::createMaze()
//{
//	// Reset grid
//	for(int x=0; x<sizeX; x++)
//		for(int y=0; y<sizeY; y++)
//			grid[x][y]=0;
//
//	loadFromTextfile();
//};
//
//void Maze::loadFromTextfile()
//{
//	//Load High Score
//		string line;
//		string fileName = "root/Levels/maze1.txt";
//		ifstream f(fileName);
//		if(f.is_open())
//		{
//			for (int y=sizeY-1; y>=0; y--)
//			{
//				getline(f,line);
//				for(int x=0; x<sizeX; x++)
//				{
//					switch(line[x])
//					{
//					case '#':
//						grid[x][y]=1;
//						break;
//					case '-':
//						createPill(x,y);
//						//grid[x][y]=2;
//						break;
//					case 'b':
//						grid[x][y]=3;
//						break;
//					default:
//						grid[x][y]=0;
//						break;
//					}
//				}
//			}
//			f.close();
//		}
//		else
//		{
//			string message =  "Unable to find: "+fileName;
//			throw 0;
//		}
//};
//
//void Maze::createPill(int x, int y)
//{
//};
//
//MatF4 Maze::getPosition(int x, int y)
//	{
//		//D3DXMATRIX translation;
//		//D3DXMatrixIdentity(&translation);
//		//float middleX = (float)sizeX*0.5f-0.5f; // middle of grid
//		//float middleY = (float)sizeY*0.5f-0.5f; // middle of grid
//		//D3DXMatrixTranslation(&translation, (float)x-sizeX-10.0f, 20.0f, (float)y-sizeY);
//		
//		return MatF4();
//	};
//
//MatF4 Maze::getTranslation(int x, int y)
//	{
//		MatF4 translation;
//		float middleX = (float)sizeX*0.5f-0.5f; // middle of grid
//		float middleY = (float)sizeY*0.5f-0.5f; // middle of grid
//		translation.translation(((float)x), ((float)y), 0.0f);
//		return translation;
//	};
//
//int Maze::getSizeX()
//	{
//		return sizeX;
//	};
//
//int Maze::getSizeY()
//	{
//		return sizeY;
//	};