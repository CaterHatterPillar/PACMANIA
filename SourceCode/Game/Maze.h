#ifndef MAZE_H
#define MAZE_H

#include "../Math/PacMath.h"
#include "../DX/GraphicsContainerDX.h"
#include "../Messaging/ObserverDirector.h"
#include <fstream>
using namespace std;

class Maze{
private:
	MatF4 position;
	static const int sizeX=28;
	static const int sizeY=31;
	int grid[sizeX][sizeY];

	GraphicsContainer* graphicsContainer;

public:
	Maze(GraphicsContainer* graphicsContainer)
	{
		this->graphicsContainer = graphicsContainer; 

		// Init grid
		createMaze();
	};

	void createMaze()
	{
		// Reset grid
		for(int x=0; x<sizeX; x++)
			for(int y=0; y<sizeY; y++)
				grid[x][y]=0;

		loadFromTextfile();
	};

	void loadFromTextfile()
	{
		//Load High Score
		string line;
		string fileName = "root/Levels/maze1.txt";
		ifstream f(fileName);
		if(f.is_open())
		{
			for (int y=sizeY-1; y>=0; y--)
			{
				getline(f,line);
				for(int x=0; x<sizeX; x++)
				{
					if(line[x]=='#')
						grid[x][y]=1;
					else
						grid[x][y]=0;
				}
			}
			f.close();
		}
		else
		{
			string message =  "Unable to find: "+fileName;
			throw 0;
		}
	};

	MatF4 getPosition(int x, int y)
	{
		//D3DXMATRIX translation;
		//D3DXMatrixIdentity(&translation);
		//float middleX = (float)sizeX*0.5f-0.5f; // middle of grid
		//float middleY = (float)sizeY*0.5f-0.5f; // middle of grid
		//D3DXMatrixTranslation(&translation, (float)x-sizeX-10.0f, 20.0f, (float)y-sizeY);
		
		return MatF4();
	};

	MatF4 getTranslation(int x, int y)
	{
		MatF4 translation;
		float middleX = (float)sizeX*0.5f-0.5f; // middle of grid
		float middleY = (float)sizeY*0.5f-0.5f; // middle of grid
		translation.translation(((float)x), ((float)y), 0.0f);
		return translation;
	};

	void draw()
	{
		//Draw maze
		for(int y = 0; y<sizeY; y++)
		{
			for(int x = 0; x<sizeX; x++)
			{
				if(getTile(x,y)==1)
				{
					MatF4 scale;
					scale.scaling(0.5f,0.5f,0.5f);
					MsgRender* renderMsg = new MsgRender(graphicsContainer, getTranslation(x,y), MatF4(), scale);
					Singleton<ObserverDirector>::get().push(renderMsg);
				}
			}
		}
	};

	int getSizeX()
	{
		return sizeX;
	};

	int getSizeY()
	{
		return sizeY;
	};

	int getTile(int x, int y)
	{
		// treat coordinates outside of maze as empty tiles
		if(x<0 || y<0)
			return 0;
		if(x>=sizeX || y>=sizeY)
			return 0;

		// get maze tile
		return grid[x][y];
	};
};
#endif