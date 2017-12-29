#include "MapGenerator.h"
#include "simplexnoise.h"
//#include "Constants.h"
#include <cmath>
#include <vector>

static const float TILE_WIDTH = 64;
static const float TILE_HEIGHT = 64;

//void voronoi_f1f2_2d(float ss, float tt, float &f1, float &spos1, float &tpos1, float &f2, float &spos2, float &tpos2)
//{
//	float jitter = 1.0;
//	float sthiscell = floor(ss) + 0.5;
//	float tthiscell = floor(tt) + 0.5;
//	f1 = f2 = 1000;
//	float i, j;
//	for (i = -1; i <= 1; i += 1)
//	{
//		float stestcell = sthiscell + i;
//		for (j = -1; j <= 1; j += 1)
//		{
//			float ttestcell = tthiscell + j;
//			float spos = stestcell + jitter * (cellnoise(stestcell, ttestcell) - 0.5);
//			float tpos = ttestcell + jitter * (cellnoise(stestcell + 23, ttestcell - 87) - 0.5);
//			float soffset = spos - ss;
//			float toffset = tpos - tt;
//			float dist = soffset*soffset + toffset*toffset;
//			if (dist < f1)
//			{
//				f2 = f1;
//				spos2 = spos1;
//				tpos2 = tpos1;
//				f1 = dist;
//				spos1 = spos;
//				tpos1 = tpos;
//			}
//			else if (dist < f2)
//			{
//				f2 = dist;
//				spos2 = spos;
//				tpos2 = tpos;
//			}
//		}
//	}
//	f1 = sqrt(f1);  f2 = sqrt(f2);
//}

float noise(float nx, float ny)
{

	return (raw_noise_2d(nx, ny) + 1.0f) / 2.0f;
}

float fBm(float x, float y, int octaves, float lacunarity, float gain)
{
	float amp = 1;
	Vector2 vec(x, y);
	float sum = 0;
	for (int i = 0; i < octaves; i++)
	{
		sum += amp * raw_noise_2d(vec.x, vec.y);
		amp *= gain;
		vec *= lacunarity;
	}
	return sum;
}

float RidgedMultifractal(float x, float y, int octaves, float lacunarity, float gain, float H, float sharpness, float threshold)
{
	float result, signal, weight, exponent;
	Vector2 vec(x, y);

	for (int i = 0; i < octaves; i++)
	{
		if (i == 0)
		{
			signal = raw_noise_2d(vec.x, vec.y);
			if (signal <= 0.0)
				signal = -signal;
			signal = gain - signal;
			signal = pow(signal, sharpness);
			result = signal;
			weight = 1.0f;
		}
		else
		{
			exponent = pow(lacunarity, -i*H);
			vec *= lacunarity;
			weight = signal * threshold;
			weight = std::fminf(std::fmaxf(weight, 0.0f), 1.0f);
			signal = raw_noise_2d(vec.x, vec.y);
			signal = abs(signal);
			signal *= weight;
			result += signal * exponent;
		}
	}
	return result;
}

float turbulence(float x, float y, int octaves, float lacunarity, float gain)
{
	float amp = 1;
	Vector2 vec(x, y);
	float sum = 0;
	for (int i = 0; i < octaves; i++)
	{
		sum += std::abs(amp * raw_noise_2d(vec.x, vec.y));
		amp *= gain;
		vec *= lacunarity;
	}
	return sum / 2.0f;
}

void MapGenerator::generateMap(int seed, int* tileArr, int* heightArr, int width, int height, float frequency, Vector2 &position)
{
	static int octaves = 8;
	static float lacunarity = 2.5f;
	static float gain = 0.8f;
	static float H = 0.8f;
	static float sharpness = 2.0f;
	static float threshold = 2.0f;

	// TODO: implement usage of a random seed for x and y
	for (int i = 0; i < width; i++)
	{

		float nx = ((float)i * TILE_WIDTH + position.x + seed) * frequency;
		for (int j = 0; j < height; j++)
		{
			unsigned int index = i + j * width;
			static float multiplier = 8.0f;
			float ny = ((float)j * TILE_HEIGHT + position.y) * frequency;

			float heightVal =
				RidgedMultifractal(nx, ny, octaves, lacunarity, gain, H, sharpness, threshold) * multiplier;

			heightArr[index] = (int)heightVal;

			float noiseVal = noise(nx, ny);

			// If the height is larger than this, it is to be considered stone
			if (heightVal >= 3.5f)
			{
				tileArr[index] = TileType::Stone;
			}
			// If less than this it is to be considered water
			else if (heightVal < 0.5)
			{
				tileArr[index] = TileType::Water;
			}
			// Else use the value from the noise to gererate a random biome
			else
			{
				if (noiseVal >= 0.5f)
					tileArr[index] = TileType::Grass;
				else
					tileArr[index] = TileType::Sand;
			}
		}
	}
}
