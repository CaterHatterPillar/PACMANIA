#ifndef MAZE_H
#define MAZE_H

#include "../Math/PacMath.h"
#include "../DX/GraphicsContainerDX.h"
#include "../Messaging/ObserverDirector.h"

#include <fstream>
using namespace std;

struct Pill
{
	VecI2 pos;
	bool isAlive;
	bool isBloody;
	float size;

	Pill(VecI2 pos, bool isBloody)
	{
		this->pos = pos;
		this->isBloody = isBloody;
		isAlive = true;
		size = 1.0f;
	}

	void checkCollision(VecF2 p2)
	{
		VecF3 v1((float)pos.x, (float)pos.y, 0.0f);
		VecF3 v2(p2.x, p2.y, 0.0f);

		// True: Collision occures
		float dist = v1.distanceTo(v2);
		if(dist < 0.9f)
		{
			isAlive = false;
		}
	}

	void update(float dt)
	{
		// Make pills shrink when eaten
		if(!isAlive)
		{
			if(size>0.0f)
				size-=dt * 4.0f;
		}	
	}
};

class Maze{
private:
	MatF4 position;
	static const int sizeX=28;
	static const int sizeY=31;
	int grid[sizeX][sizeY];

	//GameEntity* pacman = new GameEntity();

	//vector<GameEntity> pills;
	GraphicsContainer* gcWall;
	GraphicsContainer* gcPill;
	GraphicsContainer* gcPillBloody;

	vector<Pill> pills;

public:
	Maze(GraphicsContainer* gcWall, GraphicsContainer* gcPill, GraphicsContainer* gcPillBloody)
	{
		this->gcWall = gcWall;
		this->gcPill = gcPill; 
		this->gcPillBloody = gcPillBloody; 

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
					switch(line[x])
					{
					case '#':
						grid[x][y]=1;
						break;
					case '-':
						createPill(x,y, false);
						break;
					case 'b':
						createPill(x,y, true);
						break;
					default:
						grid[x][y]=0;
						break;
					}
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

	void createPill(int x, int y, bool isBloody)
	{
		VecI2 pos(x,y);
		pills.push_back(Pill(pos, isBloody));
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

	void update(double delta)
	{
		//Update pills
		for(int i = 0; i<(int)pills.size(); i++)
		{
			pills[i].update((float)delta);
		}

		//draw
		draw();
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
					MsgRender* renderMsg = new MsgRender(gcWall, getTranslation(x,y), MatF4(), scale);
					Singleton<ObserverDirector>::get().push(renderMsg);
				}
			}
		}

		// Draw pills
		for(int i = 0; i<(int)pills.size(); i++)
		{
			float size = pills[i].size;
			if(size>0.0f)
			{
				MatF4 scale;
				int x = pills[i].pos.x;
				int y = pills[i].pos.y;
				if(!pills[i].isBloody)
				{
					scale.scaling(size*0.15f,size*0.2f,size*0.15f);
					MsgRender* renderMsg = new MsgRender(gcPill, getTranslation(x,y), MatF4(), scale);
					Singleton<ObserverDirector>::get().push(renderMsg);
				}
				if(pills[i].isBloody)
				{
					scale.scaling(size*0.25f,size*0.35f,size*0.25f);
					MsgRender* renderMsg = new MsgRender(gcPillBloody, getTranslation(x,y), MatF4(), scale);
					Singleton<ObserverDirector>::get().push(renderMsg);
				}
			}
		}
	};

	void checkCollisionWithPills(VecF2 pos)
	{
		for(int i = 0; i<(int)pills.size(); i++)
		{
			if(pills[i].isAlive)
				pills[i].checkCollision(pos);
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