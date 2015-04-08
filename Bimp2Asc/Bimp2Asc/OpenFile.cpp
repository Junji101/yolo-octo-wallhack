#include "Headers\CImg.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace cimg_library;
using namespace std;

#define HEIGHT  550
#define WIDTH  550
#define XBOX 7
#define YBOX 10
#define files 19

char filenames[files][6] = {"(.bmp",").bmp","O.bmp","!.bmp","#.bmp","$.bmp","%.bmp","&.bmp",";.bmp","~.bmp","+.bmp","`.bmp","}.bmp","{.bmp","_.bmp","^.bmp","].bmp","[.bmp", "@.bmp"};
int cData[HEIGHT][WIDTH];

char yes(int x){
	if (x >= 254){
		return '.';
	}else if (x >= 204){
		return 'o';
	}else if (x >= 153){
		return 'x';
	}else if (x >= 102){
		return '&';
	}else{
		return '#';
	}
	
}

char compare(int m[XBOX][YBOX], int thresh_hold){
	cout << "Comparing";
	int tries = 0, pixels = 0;
	int newBox[XBOX][YBOX];
	for (int i = 0;  i < XBOX; i++){ //Sets an 2d array with 1 being darker than normal and 0 being lighter than normal
		for(int j = 0; j < YBOX; j++){
			if(m[i][j] <= thresh_hold){
				//cout << "Current value: " << m[i][j] << " Threshold: " << thresh_hold;
				newBox[i][j] = 1;
				pixels++;
			}else{
				//cout << "Current value: " << m[i][j] << " Threshold: " << thresh_hold;
				newBox[i][j] = 0;
			}
		}
	}
	cout<< "Trying to match: " << pixels << " pixels..." << endl;
	if (pixels == 0){
		return ' ';
	}
	while (tries < 10){
		for (int k = 0; k < files; k++){
			CImg<unsigned char> image(filenames[k]);
			int charBox[XBOX][YBOX];
			int testBox = 0;
			int filepix = 0;
			for (int x = 0; x < image.width(); x++){ //creates a 2d array of character with pixels being 1 and no pixels being 0
				for(int y = 0; y < image.height(); y++){
					if (image(x,y,0,1) < 250){
						//cout << "Pixel of" << filenames[k] <<  "at: " << x << ", " << y << endl;
						charBox[x][y] = 1;
						filepix++;
					}else{
						charBox[x][y] = 0;
					}
					if (newBox[x][y] == charBox[x][y]){
						testBox++;
					}
				}
			}
			//cout << "Current file: " << filenames[k] << " Pixels(file): "<< filepix <<  endl;
				
			//cin.get();
			//cout << "testBox: " << testBox << "Pixels: " << pixels << endl;
			if (testBox == (pixels+tries)){
				cout << "Found match: " << filenames[k][0] << endl;
				return filenames[k][0];
			}
		}
		//cout << "Tries: " << tries << endl;
		tries++;
	}
	return '.';
}

int main(){
	ofstream myfile;
	myfile.open("example.txt");
	myfile.clear();
	CImg<unsigned char> image("duck.bmp");
	CImgDisplay display(image,"This is a duck");
	cout << image._spectrum << endl;
	//image.RGBtoHSL();
	//display.wait();
	cout << "Height: " << image._height << " Width: " << image._width << endl;
	cout << "Warning: Image resolution must be below 550 x550" << endl;
	cout << "How many half resize iterations" << endl;
	int x;
	cin >> x;
	for (int k = 0; k < x; k++){
		image = image.resize_halfXY();
	}
	//double newHeight = image._height*4/50 + .5;
	//double newWidth = image._width*4/50 + .5;
	cout << " New Height: " << image._height << " New Width: " << image._width << endl;
	int newWidth = image._width;
	int newHieght = image._height;
	//vector<vector<float> > cData(newHieght, vector<float>(newWidth));
	cout << "Second File: " << filenames[1] << endl;

	cimg_forXY(image,x,y){
		int Red =  image(x,y,0,0);
		int Green = image(x,y,0,1);
		int Blue = image(x,y,0,2);
		int average = (Red+Green+Blue)/3;
		cData[x][y] = average;
		//cout << "Average:" << average << endl;
	}

	for (int i = 0 ; i < newHieght-10; i+=10){
		for (int j = 0; j < newWidth-7;j+=7){
			int currentBox[XBOX][YBOX]; //Sets currentBox to the size of the XBOX and YBOX
			int sum = 0;
			for (int k = 0; k < XBOX; k++){ //makes currentBox[][] = from current cData[][] section
				for (int m = 0; m < YBOX; m++){
					if (cData[j+k][i+m] < 0){
						currentBox[k][m] = 0;
					}
					currentBox[k][m] = cData[j+k][i+m];
					sum += currentBox[k][m];
				}
			}
			int average = sum/(XBOX*YBOX) - 1;
			cout << average;
			myfile << compare(currentBox,average);		}
		myfile << endl;
	}
	myfile.close();
	//cin >> x;
}