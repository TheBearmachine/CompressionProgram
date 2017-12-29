#pragma once
#include "Vector2.h"

class MapGenerator
{
public:
	enum TileType
	{
		Grass,
		Water,
		Snow,
		Sand,
		Stone
	};

	enum ObjectType
	{

	};

	static void generateMap(int seed, int* tileArr, int* heightArr, int width, int height, float frequency, Vector2 &position);

private:

};
