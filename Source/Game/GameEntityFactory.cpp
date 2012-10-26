#include "GameEntityFactory.h"

GameEntityFactory::GameEntityFactory()
{
}

GameEntityFactory::~GameEntityFactory()
{
}

void GameEntityFactory::parsePosition(fstream& infile)
{
	float x, y, z;
	infile >> x >> y >> z;
	positions.push_back(VecF3(x, y, z));
}

void GameEntityFactory::parseNormal(fstream& infile)
{
	float x, y, z;
	infile >> x >> y >> z;
	normals.push_back(VecF3(x, y, z));
}

void GameEntityFactory::parseTexcoord(fstream& infile)
{
	float u, v;
	infile >> u >> v;
	texcoords.push_back(VecF2(u, v));
}

void GameEntityFactory::parseFace(fstream& infile)
{	
	unsigned int iPosition, iNormal, iTexcoord;
	PosNormTex vertex;
	
	for(unsigned int i=0; i<3; i++)
	{
		ZeroMemory(&vertex, sizeof(PosNormTex));
		
		infile >> iPosition;
		vertex.pos = positions[iPosition-1];
		
		if(infile.peek() == '/')
		{
			infile.ignore();
			if(infile.peek() != '/')
			{
				infile >> iTexcoord;
				vertex.tex = texcoords[iTexcoord-1];
			}
			if(infile.peek() == '/')
			{
				infile.ignore();
				infile >> iNormal;
				vertex.norm = normals[iNormal-1];
			}
		}
		privateVertices.push_back(vertex);
	}
}

vector<PosNormTex>* GameEntityFactory::createVerticesPlane()
{
	vector<PosNormTex>* vertices = new vector<PosNormTex>;
	vertices->push_back(PosNormTex(VecF3(-1.0f, 1.0f, 1.0f),	VecF3(0.0f, 0.0f, 1.0f),	VecF2(0.0f, 0.0f)));   
	vertices->push_back(PosNormTex(VecF3(1.0f, 1.0f, 1.0f),		VecF3(0.0f, 0.0f, 1.0f),	VecF2(1.0f, 0.0f)));
	vertices->push_back(PosNormTex(VecF3(-1.0f, -1.0f, 1.0f),	VecF3(0.0f, 0.0f, 1.0f),	VecF2(0.0f, 1.0f)));
	vertices->push_back(PosNormTex(VecF3(1.0f, -1.0f, 1.0f),	VecF3(0.0f, 0.0f, 1.0f),	VecF2(1.0f, 1.0f)));

	return vertices;
}

vector<unsigned int>* GameEntityFactory::createIndicesPlane()
{
	vector<unsigned int>* indices = new vector<unsigned int>;

	indices->push_back(0);
	indices->push_back(1);
	indices->push_back(2);
	indices->push_back(2);
	indices->push_back(1);
	indices->push_back(3);

	return indices;
}

vector<PosNormTex>* GameEntityFactory::createVerticesCube()
{
	vector<PosNormTex>* vertices = new vector<PosNormTex>;
	 // side 1
	vertices->push_back(PosNormTex(VecF3(-1.0f, -1.0f, 1.0f),	VecF3(0.0f, 0.0f, 1.0f),	VecF2(0.0f, 0.0f)));   
	vertices->push_back(PosNormTex(VecF3(1.0f, -1.0f, 1.0f),	VecF3(0.0f, 0.0f, 1.0f),	VecF2(0.0f, 1.0f)));
	vertices->push_back(PosNormTex(VecF3(-1.0f, 1.0f, 1.0f),	VecF3(0.0f, 0.0f, 1.0f),	VecF2(1.0f, 0.0f)));
	vertices->push_back(PosNormTex(VecF3(1.0f, 1.0f, 1.0f),		VecF3(0.0f, 0.0f, 1.0f),	VecF2(1.0f, 1.0f)));
																							 
	// side 2													 							 
	vertices->push_back(PosNormTex(VecF3(-1.0f, -1.0f, -1.0f),	VecF3(0.0f, 0.0f, -1.0f),	VecF2(0.0f, 0.0f)));    
	vertices->push_back(PosNormTex(VecF3(-1.0f, 1.0f, -1.0f),	VecF3(0.0f, 0.0f, -1.0f),	VecF2(0.0f, 1.0f)));
	vertices->push_back(PosNormTex(VecF3(1.0f, -1.0f, -1.0f),	VecF3(0.0f, 0.0f, -1.0f),	VecF2(1.0f, 0.0f)));
	vertices->push_back(PosNormTex(VecF3(1.0f, 1.0f, -1.0f),	VecF3(0.0f, 0.0f, -1.0f),	VecF2(1.0f, 1.0f)));
																							
	// side 3													 	 						
	vertices->push_back(PosNormTex(VecF3(-1.0f, 1.0f, -1.0f),	VecF3(0.0f, 1.0f, 0.0f),	VecF2(0.0f, 0.0f)));    
	vertices->push_back(PosNormTex(VecF3(-1.0f, 1.0f, 1.0f),	VecF3(0.0f, 1.0f, 0.0f),	VecF2(0.0f, 1.0f)));
	vertices->push_back(PosNormTex(VecF3(1.0f, 1.0f, -1.0f),	VecF3(0.0f, 1.0f, 0.0f),	VecF2(1.0f, 0.0f)));
	vertices->push_back(PosNormTex(VecF3(1.0f, 1.0f, 1.0f),		VecF3(0.0f, 1.0f, 0.0f),	VecF2(1.0f, 1.0f)));
																							 
	// side 4														 	 					 
	vertices->push_back(PosNormTex(VecF3(-1.0f, -1.0f, -1.0f),	VecF3(0.0f, -1.0f, 0.0f),	VecF2(0.0f, 0.0f)));    
	vertices->push_back(PosNormTex(VecF3(1.0f, -1.0f, -1.0f),	VecF3(0.0f, -1.0f, 0.0f),	VecF2(0.0f, 1.0f)));
	vertices->push_back(PosNormTex(VecF3(-1.0f, -1.0f, 1.0f),	VecF3(0.0f, -1.0f, 0.0f),	VecF2(1.0f, 0.0f)));
	vertices->push_back(PosNormTex(VecF3(1.0f, -1.0f, 1.0f),	VecF3(0.0f, -1.0f, 0.0f),	VecF2(1.0f, 1.0f)));
																							
	// side 5																 				
	vertices->push_back(PosNormTex(VecF3(1.0f, -1.0f, -1.0f),	VecF3(1.0f, 0.0f, 0.0f),	VecF2(0.0f, 0.0f)));    
	vertices->push_back(PosNormTex(VecF3(1.0f, 1.0f, -1.0f),	VecF3(1.0f, 0.0f, 0.0f),	VecF2(0.0f, 1.0f)));
	vertices->push_back(PosNormTex(VecF3(1.0f, -1.0f, 1.0f),	VecF3(1.0f, 0.0f, 0.0f),	VecF2(1.0f, 0.0f)));
	vertices->push_back(PosNormTex(VecF3(1.0f, 1.0f, 1.0f),		VecF3(1.0f, 0.0f, 0.0f),	VecF2(1.0f, 1.0f)));
																							  
	// side 6																				  
	vertices->push_back(PosNormTex(VecF3(-1.0f, -1.0f, -1.0f),	VecF3(-1.0f, 0.0f, 0.0f),	VecF2(0.0f, 0.0f)));    
	vertices->push_back(PosNormTex(VecF3(-1.0f, -1.0f, 1.0f),	VecF3(-1.0f, 0.0f, 0.0f),	VecF2(0.0f, 1.0f)));
	vertices->push_back(PosNormTex(VecF3(-1.0f, 1.0f, -1.0f),	VecF3(-1.0f, 0.0f, 0.0f),	VecF2(1.0f, 0.0f)));
	vertices->push_back(PosNormTex(VecF3(-1.0f, 1.0f, 1.0f),	VecF3(-1.0f, 0.0f, 0.0f),	VecF2(1.0f, 1.0f)));

	return vertices;
}

vector<unsigned int>* GameEntityFactory::createIndicesCube()
{
	vector<unsigned int>* indices = new vector<unsigned int>;

	indices->push_back(0);
	indices->push_back(1);
	indices->push_back(2);
		   
	indices->push_back(2);
	indices->push_back(1);
	indices->push_back(3);
		   
	indices->push_back(4);
	indices->push_back(5);
	indices->push_back(6);
		   
	indices->push_back(6);
	indices->push_back(5);
	indices->push_back(7);
		   
	indices->push_back(8);
	indices->push_back(9);
	indices->push_back(10);
		   
	indices->push_back(10);
	indices->push_back(9);
	indices->push_back(11);
		   
	indices->push_back(12);
	indices->push_back(13);
	indices->push_back(14);
		   
	indices->push_back(14);
	indices->push_back(13);
	indices->push_back(15);
		   
	indices->push_back(16);
	indices->push_back(17);
	indices->push_back(18);
		   
	indices->push_back(18);
	indices->push_back(17);
	indices->push_back(19);
		   
	indices->push_back(20);
	indices->push_back(21);
	indices->push_back(22);
		   
	indices->push_back(22);
	indices->push_back(21);
	indices->push_back(23);

	return indices;
}

vector<PosNormTex>* GameEntityFactory::createVerticesObj(string filename)
{
	fstream infile(filename);

	positions.clear();
	normals.clear();
	texcoords.clear();
	privateVertices.clear();

	string temp;

	if(infile)
	{
		while(!infile.eof())
		{
			temp = "unknown";
			infile >> temp;
			
			if(temp == "v")
				parsePosition(infile);
			if(temp == "vn")
				parseNormal(infile);
			if(temp == "vt")
				parseTexcoord(infile);
			if(temp == "f")
				parseFace(infile);
		}
	}

	vector<PosNormTex>* vertices = new vector<PosNormTex>;

	for(unsigned int i=0; i<privateVertices.size(); i++)
	{
		vertices->push_back(privateVertices.at(i));
	}

	return vertices;
}

vector<unsigned int>* GameEntityFactory::createIndicesObj(vector<PosNormTex>* vertices)
{
	vector<unsigned int>* indices = new vector<unsigned int>;
	for(unsigned int i=0; i<vertices->size(); i++)
		indices->push_back(i);

	return indices;
}

GameEntity* GameEntityFactory::createPacman(VecF3 position, Maze* maze)
{
	GameEntity* entity = new GameEntity();
	entity->setPosition(position);
	
	vector<PosNormTex>* vertices	= createVerticesObj("../../Models/Pacman.obj");
	vector<unsigned int>* indices	= createIndicesObj(vertices);

	ShaderId vertexShaderId = VERTEX_SHADER_DEFAULT;
	ShaderId pixelShaderId	= PIXEL_SHADER_DEFAULT;
	TextureId textureId		= TEXTURE_PACMAN;

	unsigned int numVertices	= vertices->size();
	unsigned int numIndices		= indices->size();
	unsigned int numFaces		= indices->size() / 3;
	unsigned int stride			= sizeof(PosNormTex);
	unsigned int offset			= 0;

	GraphicsContainer* graphicsContainer = createGraphicsContainer(	vertexShaderId,
		pixelShaderId,
		textureId,
		vertices,
		indices,
		numVertices,
		numIndices,
		numFaces,
		stride,
		offset);

	MoveBehaviour* moveBehaviour = new MoveBehaviourMazePlayer(maze, maze->getRandomFreePosition());
	moveBehaviour->init();

	Light* light = new Light;
	light->pos = VecF3(1.0f, 1.0f, -20.0f);
	light->spotPow = 128.0f;
	light->dir = VecF3(0.0f, 0.0f, 1.0f);
	light->range = 1000.0f;
	light->ambient = VecF4(0.3f, 0.3f, 0.3f, 1.0f);
	light->diffuse = VecF4(1.0f, 1.0f, 1.0f, 1.0f);
	light->specular = VecF4(1.0f, 1.0f, 1.0f, 1.0f);
	light->att = VecF3(0.5f, 0.0f, 0.0f);

	entity->setGraphicsContainer(graphicsContainer);
	entity->setMoveBehaviour(moveBehaviour);
	entity->setLight(light);

	entity->setRotation(VecF3(0.0f, 0.0f, -90.0f));
	entity->setScale(VecF3(0.35f,0.35f,0.35f));
	return entity;
}

GameEntity* GameEntityFactory::createGhost(VecI2 position, Maze* maze)
{
	vector<PosNormTex>* vertices	= createVerticesObj("../../Models/Ghost.obj");
	vector<unsigned int>* indices	= createIndicesObj(vertices);

	ShaderId vertexShaderId = VERTEX_SHADER_DEFAULT;
	ShaderId pixelShaderId	= PIXEL_SHADER_DEFAULT;
	TextureId textureId		= TEXTURE_GHOST;

	unsigned int numVertices	= vertices->size();
	unsigned int numIndices		= indices->size();
	unsigned int numFaces		= indices->size() / 3;
	unsigned int stride			= sizeof(PosNormTex);
	unsigned int offset			= 0;

	GraphicsContainer* graphicsContainer = createGraphicsContainer(	vertexShaderId,
		pixelShaderId,
		textureId,
		vertices,
		indices,
		numVertices,
		numIndices,
		numFaces,
		stride,
		offset);

	Light* light = new Light;
	light->pos = VecF3(1.0f, 1.0f, -20.0f);
	light->spotPow = 128.0f;
	light->dir = VecF3(0.0f, 0.0f, 1.0f);
	light->range = 1000.0f;
	light->ambient = VecF4(-0.9f, -0.9f, -0.9f, 1.0f);
	light->diffuse = VecF4(-0.9f, -0.9f, -0.9f, 1.0f);
	light->specular = VecF4(-0.1f, -0.1f, -0.1f, 1.0f);
	light->att = VecF3(1.6f, 0.0f, 0.0f);


	// Build entity
	MoveBehaviour* moveBehaviour = new MoveBehaviourMaze(maze, maze->getRandomFreePosition());
	moveBehaviour->init();
	GameEntity* entity = new GameEntity();
	entity->setGraphicsContainer(graphicsContainer);
	entity->setMoveBehaviour(moveBehaviour);
	entity->setLight(light);

	entity->setRotation(VecF3(90.0f, 0.0f, 0.0f));
	entity->setScale(VecF3(0.35f,0.35f,0.35f));
	return entity;
}

GameEntity* GameEntityFactory::createPill( VecF3 position )
{
	GameEntity* entity = new GameEntity();
	entity->setPosition(position);

	vector<PosNormTex>* vertices	= createVerticesPlane();
	vector<unsigned int>* indices	= createIndicesPlane();

	ShaderId vertexShaderId = VERTEX_SHADER_DEFAULT;
	ShaderId pixelShaderId	= PIXEL_SHADER_DEFAULT;
	TextureId textureId		= TEXTURE_WALL;//TEXTURE_PILL;

	unsigned int numVertices	= vertices->size();
	unsigned int numIndices		= indices->size();
	unsigned int numFaces		= indices->size() / 3;
	unsigned int stride			= sizeof(PosNormTex);
	unsigned int offset			= 0;

	GraphicsContainer* graphicsContainer = createGraphicsContainer(	vertexShaderId,
		pixelShaderId,
		textureId,
		vertices,
		indices,
		numVertices,
		numIndices,
		numFaces,
		stride,
		offset);

	entity->setGraphicsContainer(graphicsContainer);
	entity->setMoveBehaviour(NULL);

	return entity;
}

GameEntity* GameEntityFactory::createBloodyPill( VecF3 position )
{
	GameEntity* entity = new GameEntity();
	entity->setPosition(position);

	vector<PosNormTex>* vertices	= createVerticesPlane();
	vector<unsigned int>* indices	= createIndicesPlane();

	ShaderId vertexShaderId = VERTEX_SHADER_DEFAULT;
	ShaderId pixelShaderId	= PIXEL_SHADER_DEFAULT;
	TextureId textureId		= TEXTURE_PILL_BLOODY;

	unsigned int numVertices	= vertices->size();
	unsigned int numIndices		= indices->size();
	unsigned int numFaces		= indices->size() / 3;
	unsigned int stride			= sizeof(PosNormTex);
	unsigned int offset			= 0;

	GraphicsContainer* graphicsContainer = createGraphicsContainer(	vertexShaderId,
		pixelShaderId,
		textureId,
		vertices,
		indices,
		numVertices,
		numIndices,
		numFaces,
		stride,
		offset);

	entity->setGraphicsContainer(graphicsContainer);
	entity->setMoveBehaviour(NULL);

	return entity;
}

GameEntity* GameEntityFactory::createWall( VecF3 position )
{
	GameEntity* entity = new GameEntity();
	entity->setPosition(position);

	vector<PosNormTex>* vertices	= createVerticesCube();
	vector<unsigned int>* indices	= createIndicesCube();

	ShaderId vertexShaderId = VERTEX_SHADER_DEFAULT;
	ShaderId pixelShaderId	= PIXEL_SHADER_DEFAULT;
	TextureId textureId		= TEXTURE_WALL;

	unsigned int numVertices	= vertices->size();
	unsigned int numIndices		= indices->size();
	unsigned int numFaces		= indices->size() / 3;
	unsigned int stride			= sizeof(PosNormTex);
	unsigned int offset			= 0;

	GraphicsContainer* graphicsContainer = createGraphicsContainer(	vertexShaderId,
		pixelShaderId,
		textureId,
		vertices,
		indices,
		numVertices,
		numIndices,
		numFaces,
		stride,
		offset);

	entity->setGraphicsContainer(graphicsContainer);
	entity->setMoveBehaviour(NULL);

	return entity;
}

Maze* GameEntityFactory::createMaze()
{
	vector<PosNormTex>* vertices	= createVerticesCube();
	vector<unsigned int>* indices	= createIndicesCube();

	ShaderId vertexShaderId = VERTEX_SHADER_DEFAULT;
	ShaderId pixelShaderId	= PIXEL_SHADER_DEFAULT;

	unsigned int numVertices	= vertices->size();
	unsigned int numIndices		= indices->size();
	unsigned int numFaces		= indices->size() / 3;
	unsigned int stride			= sizeof(PosNormTex);
	unsigned int offset			= 0;

	GraphicsContainer* gcWall = createGraphicsContainer(	vertexShaderId,
		pixelShaderId,
		TEXTURE_WALL,
		vertices,
		indices,
		numVertices,
		numIndices,
		numFaces,
		stride,
		offset);

	vector<PosNormTex>* verticesPlane	= createVerticesPlane();
	vector<unsigned int>* indicesPlane	= createIndicesPlane();

	vector<PosNormTex>* verticesPlane2	= createVerticesPlane();
	vector<unsigned int>* indicesPlane2	= createIndicesPlane();

	numVertices		= verticesPlane->size();
	numIndices		= indicesPlane->size();
	numFaces		= indicesPlane->size() / 3;
	stride			= sizeof(PosNormTex);
	offset			= 0;

	GraphicsContainer* gcPill = createGraphicsContainer(	vertexShaderId,
		pixelShaderId,
		TEXTURE_PILL,
		verticesPlane,
		indicesPlane,
		numVertices,
		numIndices,
		numFaces,
		stride,
		offset);

	GraphicsContainer* gcPillBloody = createGraphicsContainer(	vertexShaderId,
		pixelShaderId,
		TEXTURE_PILL_BLOODY,
		verticesPlane2,
		indicesPlane2,
		numVertices,
		numIndices,
		numFaces,
		stride,
		offset);

	Maze* maze = new Maze(gcWall, gcPill, gcPillBloody);

	return maze;
}
