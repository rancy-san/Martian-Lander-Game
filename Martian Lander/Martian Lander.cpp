#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <time.h>
#include <iostream>
#include <Windows.h>
#include <fstream>

using namespace std;

int main() {
	clock_t msStart;
	clock_t sStart;
	clock_t mStart;
	clock_t tInit;

	int ms = 0;
	int s = 0;
	int m = 0;
	int t = 0;
	char timer[100];

	int playAgain = 1;
	double fuel = 100;
	int bounceCount = 0;
	double B = 0; // user
	double g = 3.7;
	double c = 0.13;
	double a = 8.3;
	double vmax = 46;

	int i = 0;
	int arraySize = 10000;
	double *x_i = new double[arraySize];
	x_i[0] = 1000;
	// d_x
	double d_x;
	d_x = t;
	// y_i
	double *y_i = new double[arraySize];
	y_i[0] = 0;
	// y' = y_i
	double yp = 0;
	// g'= x_i + d_x + y'
	double gp = 0;
	// g = g - c * (v + a*(v / vmax)*(v / vmax)*(v / vmax)) - B;
	double *g_i = new double[arraySize];
	g_i[0] = 0;
	// y_i+1 = y_i + d_x*(g + g')/2
	y_i = new double[arraySize];
	y_i[0] = 0;

	msStart = clock();
	sStart = clock();
	mStart = clock();
	tInit = clock();


	while (playAgain == 1) {
		//i++; // iterator/step
		cout << "************************ STARTING DESCENT ***************************" << endl;
		ms = (int)(clock() - msStart);
		s = (int)(clock() - sStart) / 1000;
		m = (int)(clock() - mStart) / 60000;
		t = (int)(clock() - tInit) / 1000;

		if (ms > 1000) {
			msStart = clock();
		}
		if (s > 60)
			sStart = clock();
		if (fuel > 0) {
			if (GetKeyState('W')) {
				cout << "W was pressed - increase burn: ";
				B = B + 0.001;
				fuel = fuel - B;
			}
			else if (GetKeyState('E')) {
				cout << "E was pressed - decrease burn: ";
				B = B - 0.001;
			}
		}

		if (s > 0)
			i = (int)s;
		// step
		d_x = t;

		// next x is prev. x + step
		x_i[i + 1] = x_i[i] - d_x;

		if (x_i[i] > 0) {
			if (y_i[i - 1] < 0)
				y_i[i - 1] = y_i[i - 1] * (-1);
			x_i[i + 1] = x_i[i] - d_x;
		}
		if (x_i[i] <= 0) {

			if (y_i[i - 1] > 0) {
				y_i[i - 1] = y_i[i - 1] * (-1);
				x_i[i + 1] = x_i[i] + d_x;
				bounceCount++;
			}
		}

		// the equation dv/dt given
		g_i[i - 1] = g - c * (y_i[i - 1] + a*(y_i[i - 1] / vmax)*(y_i[i - 1] / vmax)*(y_i[i - 1] / vmax)) - B;
		// y'
		yp = y_i[i - 1] + g_i[i] * d_x;
		// g'
		gp = x_i[i - 1] + d_x + yp;
		// y or velocity
		y_i[i + 1] = y_i[i] + (d_x*(g_i[i] + gp) / 2);
		cout << "BURN = " << 100 - fuel << "; " << "BURN RESERVE = " << fuel << endl;
		cout << "MINUTES: " << m << "; SECONDS: " << s << "; MLLISECONDS: " << ms << endl;
		cout << "SPEED OF DESCENT = " << y_i[i - 1] << "m/s" << endl;
		cout << "HEIGHT ABOVE MARTIAN SURFACE = " << x_i[i] << "meters" << endl;
		cout << "NUMBER OF BOUNCES = " << bounceCount << endl;
		system("CLS");
		if (x_i[i] <= 0) {
			cout << "Your lander has been destroyed. Press 1 to Play Again. Press 0 to quit and save results." << endl;
			cin >> playAgain;
			if (playAgain == 0) {
				msStart = clock();
				sStart = clock();
				mStart = clock();
				tInit = clock();
				i = 0;
				bounceCount = 0;
			}
				
		}
	}

	ofstream gameResult("gameResults.txt");
	if (gameResult.is_open())
	{
		for (int dataPoint = 0; dataPoint < arraySize; dataPoint++) {
			gameResult << x_i[dataPoint] << endl;
			gameResult << y_i[dataPoint] << endl;
			gameResult << g_i[dataPoint] << endl;
		}
		gameResult.close();
	}

	return 0;
}