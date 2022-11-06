#include <stdio.h>
#include <math.h>
#include "raylib.h"

const int WIDTH = 800;
const int HEIGHT = 600;

int i, k =0;

int fsin1[4096], fsin2[4096], fsin3[4096];
int rgb[256];

void Init();
void Plasma();

int main(int argc, char* argv[])
{

	InitWindow(WIDTH, HEIGHT, "Plasma effect");
	SetTargetFPS(60);

	Init();

	while (!WindowShouldClose())
	{
		BeginDrawing();
		ClearBackground(RAYWHITE);

		k += 4;
       
		Plasma();
		EndDrawing();
	}
	CloseWindow();

	return 0;
}
void Init()
{
	int l = 4;
	for (i = 0; i < 4096; i++)
	{
		fsin1[i] = sin(i / (l * 15.0)) * 96.0 + 96.0;
		fsin2[i] = sin(i / (l * 20.0)) * 112.0 + 112.0;
		fsin3[i] = sin(i / (l * 35.0)) * 128.0 + 128.0;
	}

	for (i = 0; i < 64; i++)
	{
		rgb[i] = (i << 2) << 16 | (i << 1) << 8;
		rgb[64 + i] = (255 - (i << 1)) << 16 | ((i << 1) + 128) << 8 | i << 2;
		rgb[128 + i] = ((63 - i) << 1) << 16 | (255 - (i << 1)) << 8 | 255;
		rgb[192 + i] = (128 - (i << 1)) << 8 | (63 - i) << 2;
	}
}

void Plasma()
{
	int x, y;
	unsigned char c;

	int k1 = k;
	int k3 = 3 * k;
	if (k1 > 503) k1 = k1 - (k1 / 503) * 503;
	if (k3 > 880) k3 = k3 - (k3 / 880) * 880;

	for (y = 0; y < HEIGHT; y++)
		for (x = 0; x < WIDTH; x++)
		{
			c = fsin1[x] + fsin2[y + k1] + fsin3[x + y + k3];
			Color cc = { rgb[c] >> 24, (rgb[c] << 8) >> 24, (rgb[c] << 16) >> 24, 255 };
			DrawPixel(x, y, cc);
		}
}

