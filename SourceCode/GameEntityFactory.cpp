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

void GameEntityFactory::parseFace(fstream& infile, vector<unsigned int>* indices)
{	
	for(unsigned int i=0; i<3; i++)
	{
		unsigned int index;
		
		infile >> index;
		indices->push_back(index);
		
		if(infile.peek() == '/')
		{
			infile.ignore();
			if(infile.peek() != '/')
			{
				infile.ignore();
			}
			if(infile.peek() == '/')
			{
				infile.ignore();
				infile.ignore();
			}
		}
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
	vector<unsigned int>* indices;

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
		}
	}

	vector<VecF3> tempNormals;
	for(int i=0; i<normals.size(); i++)
	{
		tempNormals.push_back(normals[i]);
		tempNormals.push_back(normals[i]);
		tempNormals.push_back(normals[i]);
	}

	vector<PosNormTex>* vertices = new vector<PosNormTex>;

	for(int i=0; i<positions.size(); i++)
	{
		vertices->push_back(PosNormTex(positions[i], tempNormals[i], VecF2(0, 0)));
	}

	return vertices;
}

vector<unsigned int>* GameEntityFactory::createIndicesObj(string filename)
{
	fstream infile(filename);

	string temp;

	vector<unsigned int>* indices = new vector<unsigned int>;

	if(infile)
	{
		while(!infile.eof())
		{
			temp = "unknown";
			infile >> temp;
			
			if(temp == "f")
				parseFace(infile, indices);
		}
	}

	return indices;
}