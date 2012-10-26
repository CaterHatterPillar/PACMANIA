#ifndef MAZE_H
#define MAZE_H

#include "../Math/PacMath.h"
#include "../DX/GraphicsContainerDX.h"
#include "../Messaging/ObserverDirector.h"

#include <fstream>
#include <time.h>
using namespace std;

class Pill
{
public:
	VecI2 pos;
	bool isAlive;
	bool isBloody;
	float size;
	float sizeOscillation;
	float oscFactor;
	float oscTotalFactor;
	float oscSpeed;

	Pill(VecI2 pos, bool isBloody)
	{
		this->pos = pos;
		this->isBloody = isBloody;
		isAlive = true;
		size = 1.0f;

		// Generate value between 0 -> 2PI
		sizeOscillation = 2*(float)PI*(float)rand()/(float)RAND_MAX;
		oscFactor = 0.1f+0.2f*(float)rand()/(float)RAND_MAX;
		oscSpeed = 0.1f+0.3f*(float)rand()/(float)RAND_MAX;
		oscTotalFactor = 0;
	}

	void checkCollision(VecF2 p2)
	{
		VecF3 v1((float)pos.x, (float)pos.y, 0.0f);
		VecF3 v2(p2.x, p2.y, 0.0f);

		// True: Collision occures
		float dist = v1.distanceTo(v2);
		if(dist < 0.5f)
		{
			isAlive = false;
		}
	}

	void update(float dt)
	{
		// Make pills oscillate
		if(isAlive)
		{
			sizeOscillation+=2.0f*(float)PI*dt * oscSpeed;
		}	

		// Make pills shrink when eaten
		if(!isAlive)
		{
			if(getSize()>0.0f)
				size-=dt * 6.0f;
		}	
	}

	void setTotalFactor(int pillsEaten, int totalNrOfPills)
	{
 		oscTotalFactor = (float)pillsEaten/50;
		if(oscTotalFactor>1.0f)
			oscTotalFactor = 1.0f;
	}

	float getSize()
	{
		float totalOscFactor = oscFactor*oscTotalFactor;
		return size + totalOscFactor * sin(sizeOscillation);
	}
};

class Maze  : public Component
{
private:
	MatF4 position;
	VecI2 cullingPosition;
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

		// Init random seed
		srand((unsigned)time(NULL));

		//Subscribe to game state
		SubscriptionMsg* subscription = new SubscriptionMsg(this, ENTITY_STATE);
		Singleton<ObserverDirector>::get().push(subscription);
	};
	
	virtual ~Maze()
	{
		if(gcWall)
			delete gcWall;
		if(gcPill)
			delete gcPill;
		if(gcPillBloody)
			delete gcPillBloody;
	}

	void createMaze()
	{
		// Reset grid
		for(int x=0; x<sizeX; x++)
			for(int y=0; y<sizeY; y++)
				grid[x][y]=0;

		loadFromTextfile();
	};

	
	VecI2 getRandomFreePosition()
	{
		VecI2 pos;
		do
		{
			pos.x = rand() % sizeX;
			pos.y = rand() % sizeY;
		}
		while(isWallPos(pos));

		return pos;
	}

	bool isEmptyPos(VecI2 pos)
	{
		return getTile(pos) == 0;
	}

	bool isWallPos(VecI2 pos)
	{
		return getTile(pos) == 1;
	}

	void loadFromTextfile()
	{
		//Load High Score
		string line;
		string fileName = "../../Levels/maze1.txt";
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

	void init()
	{
	}

	void msgEntityState(Msg* msg)
	{
		MsgEntityState* childMsg = (MsgEntityState*)msg;
		
		// Get position
		VecF3 goalPos(childMsg->pos);
		cullingPosition = VecI2((int)goalPos.x, (int)goalPos.y);

		delete msg;
	}

	void update(double delta)
	{

		// Check messages
		Msg* msg = peek();
		while(msg)
		{
			msg = pop();
			if(msg)
			{
				MsgType type = msg->Type();
				switch(type)
				{
				case ENTITY_STATE:
					msgEntityState(msg);
					break;
				}
			}
		}

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
		//
		// Draw maze
		//

		// compute culling
		int cullingSize = 8;
		VecI2 cullStart(cullingPosition.x - cullingSize, cullingPosition.y - cullingSize);
		VecI2 cullEnd(cullingPosition.x + cullingSize, cullingPosition.y + cullingSize);
		clamp(&cullStart.x, 0, sizeX);
		clamp(&cullStart.y, 0, sizeY);
		clamp(&cullEnd.x, 0, sizeX);
		clamp(&cullEnd.y, 0, sizeY);

		for(int y = cullStart.y; y<cullEnd.y; y++)
		{
			for(int x = cullStart.x; x<cullEnd.x; x++)
			{

				if(isWallPos(VecI2(x,y)))
				{
					MatF4 scale;
					scale.scaling(0.5f,0.5f,0.5f);
					MsgRender* renderMsg = new MsgRender(gcWall, getTranslation(x,y), MatF4(), scale);
					Singleton<ObserverDirector>::get().push(renderMsg);
				}
			}
		}


		//
		// Draw pills
		// 

		int pillsEaten = 0;
		int pillsTotal = 0;
		pillsTotal = 10;
		for(int i = 0; i<(int)pills.size(); i++)
		{
			if(!pills[i].isAlive)
			{
				pillsEaten++;
			}
			pillsTotal++;
		}

		for(int i = 0; i<(int)pills.size(); i++)
		{
			VecI2 pos(pills[i].pos.x,  pills[i].pos.y);
			VecF3 v1((float)pos.x, (float)pos.y, 0.0f);
			VecF3 v2((float)cullingPosition.x, (float)cullingPosition.y, 0.0f);
			// FALSE: Cull all objects % distance from pacman
			if(v1.distanceTo(v2) < 7.0f)
			{
				float size = pills[i].getSize();
				// FALSE: Cull all objects too small to see
				if(size>0.0f)
				{
					pills[i].setTotalFactor(pillsEaten, pillsTotal);
					MatF4 scale;
					if(!pills[i].isBloody)
					{
						scale.scaling(size*0.15f,size*0.2f,size*0.15f);
						MsgRender* renderMsg = new MsgRender(gcPill, getTranslation(pos.x,pos.y), MatF4(), scale);
						Singleton<ObserverDirector>::get().push(renderMsg);
					}
					if(pills[i].isBloody)
					{
						scale.scaling(size*0.25f,size*0.35f,size*0.25f);
						MsgRender* renderMsg = new MsgRender(gcPillBloody, getTranslation(pos.x,pos.y), MatF4(), scale);
						Singleton<ObserverDirector>::get().push(renderMsg);
					}
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

	int getTile(VecI2 pos)
	{
		// treat coordinates outside of maze as empty tiles
		if(pos.x<0 || pos.y<0)
			return 0;
		if(pos.x>=sizeX || pos.y>=sizeY)
			return 0;

		// get maze tile
		return grid[pos.x][pos.y];
	};
};
#endif