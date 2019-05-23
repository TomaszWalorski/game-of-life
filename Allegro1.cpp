#define USE_CONSOLE
#define _CRT_SECURE_NO_WARNINGS
#include <cstdlib>
#include <iostream>
#include <ctime>
#include <cstdio>
#include <sstream>

using namespace std;
#include "allegro.h"

int main()
{
	const int Z = 70, X = 150;

	FILE *f;
	int mt[Z][X], x, y;
	int sons, q, n, s, t1, l, m;
	int nt[Z][X], ct[Z][X], t, p, i = 0, o = 0, o1;
	BITMAP * scrn1;

	srand(time(NULL));

	allegro_init();
	install_keyboard();
	set_color_depth(16);
	set_gfx_mode(GFX_AUTODETECT_WINDOWED, 100 + 10 * X, 100 + 10 * Z, 0, 0);

	do {          // Looping algorithm
		clear_to_color(screen, makecol(128, 128, 128));

		textout_ex(screen, font, "CONWAY'S GAME OF LIFE (LIBRE ALLEGRO)", 150, 50, makecol(0, 200, 50), -1);
		textout_ex(screen, font, "Choose speed level and put enter:", 100, 100, makecol(0, 200, 50), -1);
		textout_ex(screen, font, "1. High", 100, 120, makecol(0, 200, 50), -1);
		textout_ex(screen, font, "2. Low", 100, 140, makecol(0, 200, 50), -1);

		while (!(key[KEY_1] || key[KEY_2])) {
			readkey();
		}
		if (key[KEY_1]) t1 = 1;
		if (key[KEY_2]) t1 = 2;

		textout_ex(screen, font, "1. Random number and positions of cells.", 100, 200, makecol(0, 200, 50), -1);
		textout_ex(screen, font, "2. Choosen number of cells and random localization. ", 100, 220, makecol(0, 200, 50), -1);
		readkey();

		while (!(key[KEY_1] || key[KEY_2])) {
			readkey();
		}
		if (key[KEY_1]) {
			//  Random number and localization of cells
			for (x = 0; x < Z; x++)
			{
				for (y = 0; y < X; y++)
				{
					q = (rand() % 2);
					mt[x][y] = q;
				}
			}
		};
		if (key[KEY_2]) {
			// Chosen number of cells and random positions
			for (x = 0; x < Z; x++)
			{
				for (y = 0; y < X; y++)
				{
					mt[x][y] = 0;
				}
			}

			textout_ex(screen, font, "1. Random number and positions of cells.", 100, 200, makecol(0, 200, 50), -1);
			cout << "\nEnter number of cells (between 1 and " << Z*X << ")\n\n";
			cin >> n;
			for (s = 0; s < n; s++)
			{
				x = (rand() % Z);
				y = (rand() % X);
				if (mt[x][y] == 1) s = s - 1;
				if (mt[x][y] == 0)mt[x][y] = 1;
			}

		}


		scrn1 = create_bitmap(10 * X, 10 * Z);
		if (!scrn1)
		{
			set_gfx_mode(GFX_TEXT, 0, 0, 0, 0);
			allegro_message("nie mogê za³adowaæ obrazka 1 !");
			allegro_exit();
			return 0;
		}

		i = 0;

		do { //  Looping algorithms of main part of program


			 // This algorithm check out do changes in array accured
			o = i % 4;
			if (o == 0)
			{
				for (x = 0; x < Z; x++)
				{
					for (y = 0; y < X; y++)
					{
						t = mt[x][y];
						ct[x][y] = t;
					}
				}
			}

			if (o == 2)
			{
				for (x = 0; x < Z; x++)
				{
					for (y = 0; y < X; y++)
					{
						t = mt[x][y];
						nt[x][y] = t;
					}
				}
			}

			p = 0;
			for (x = 0; x < Z; x++)
			{
				for (y = 0; y < X; y++)
				{
					t = ct[x][y];
					if (nt[x][y] != t) p++;
				}
			}

			i++;
			// Show the array on the screen
			rectfill(screen, 100, 10, 150, 20, makecol(128, 128, 128));
			textout_ex(screen, font, "GENERATION:", 10, 10, makecol(0, 200, 50), -1);
			textprintf_ex(screen, font, 100, 10, makecol(0, 200, 50), -1, "%d", i + 1);

			for (x = 0; x < Z; x++)
			{
				for (y = 0; y < X; y++)
				{
					if (mt[x][y] == 0)
						rectfill(scrn1, 10 * y, 10 * x, 10 * (y + 1), 10 * (x + 1), makecol(255, 255, 255));
					if (mt[x][y] == 1)
						rectfill(scrn1, 10 * y + 1, 10 * x + 1, 10 * (y + 1) - 1, 10 * (x + 1) - 1, makecol(25, 0, 0));
				}
			}
			blit(scrn1, screen, 0, 0, 50, 50, scrn1->w, scrn1->h);

			// algorithm check number of neighbours
			for (x = 0; x < Z; x++)
			{
				for (y = 0; y < X; y++)
				{

					sons = 0;

					// Count living neighbours
					if (mt[x][y] == 1 || mt[x][y] == 0)
					{// row above a cell
						if (x != 0)
						{
							if (y != 0)
							{
								if (mt[x - 1][y - 1] == 1)
									sons++;
							}
							if (mt[x - 1][y] == 1)
								sons++;
							if (y != X - 1)
							{
								if (mt[x - 1][y + 1] == 1)
									sons++;
							}
						}
						// row on he cell level
						if (y != 0) {
							if (mt[x][y - 1] == 1)
								sons++;
						}
						if (y != X - 1) {
							if (mt[x][y + 1] == 1)
								sons++;
						}
						// row under a cell
						if (x != Z - 1) {
							if (y != 0) {
								if (mt[x + 1][y - 1] == 1)
									sons++;
							}
							if (mt[x + 1][y] == 1)
								sons++;
							if (y != X - 1) {
								if (mt[x + 1][y + 1] == 1)
									sons++;
							}
						}
					}

					// Count dying neighbours
					if (mt[x][y] == 1 || mt[x][y] == 0)
					{ // row above a cell
						if (x != 0)
						{
							if (y != 0)
							{
								if (mt[x - 1][y - 1] == 3)
									sons++;
							}
							if (mt[x - 1][y] == 3)
								sons++;
							if (y != X - 1)
							{
								if (mt[x - 1][y + 1] == 3)
									sons++;
							}
						}
						// row equal a cell
						if (y != 0) {
							if (mt[x][y - 1] == 3)
								sons++;
						}
						if (y != X - 1) {
							if (mt[x][y + 1] == 3)
								sons++;
						}
						// row under a cell
						if (x != Z - 1) {
							if (y != 0) {
								if (mt[x + 1][y - 1] == 3)
									sons++;
							}
							if (mt[x + 1][y] == 3)
								sons++;
							if (y != X - 1) {
								if (mt[x + 1][y + 1] == 3)
									sons++;
							}
						}
					}// end of counting

					 // Main algorithm according to rules of Conway's Life
					if (mt[x][y] == 1) // part for living cell
					{
						if (sons < 2 || sons >3)
							mt[x][y] = 3;
					}
					if (mt[x][y] == 0) // part for empty place
					{
						if (sons == 3)
							mt[x][y] = 2;
						else
							mt[x][y] = 0;
					}
					sons = 0;
				}
			}

			//	Algorithm enters the change to the array
			for (x = 0; x < Z; x++)
			{
				for (y = 0; y < X; y++)
				{
					if (mt[x][y] == 3)
						mt[x][y] = 0;
					if (mt[x][y] == 2)
						mt[x][y] = 1;
					if (mt[x][y] == 1)
						mt[x][y] = 1;
					if (mt[x][y] == 0)
						mt[x][y] = 0;
				}
			}

		/*	// Program waits for a short period of time {LOW VERSION}
			if (t1 == 2) {
				system("cls");
				system("cls");
			}
			else system("cls"); */

		} while (p != 0);

		textout_ex(screen, font, "Game over", X * 10 / 2, Z * 10 / 2, makecol(200, 0, 0), -1); // the end of main part of program

																							   // Possibility of returning to the beginning of the program
		textout_ex(screen, font, "In order to start the game again press 1 and press enter button, else put 2 and enter.", 50, Z * 10 + 60, makecol(0, 200, 50), -1);
		while (!(key[KEY_1] || key[KEY_2])) {
			readkey();
		}
		if (key[KEY_1]) l = 1;
		if (key[KEY_2]) l = 2;

		readkey();

	} while (l == 1);

	allegro_exit();

	return 0;
}

