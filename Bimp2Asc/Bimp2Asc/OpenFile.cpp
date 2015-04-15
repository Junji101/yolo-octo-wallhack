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
#define filenum 14
#define MAXBRIGHT 138975

char filenames[filenum][6] = {"`.bmp","~.bmp","^.bmp","!.bmp",";.bmp","(.bmp","&.bmp","%.bmp","+.bmp","].bmp","$.bmp","O.bmp","#.bmp", "@.bmp"};
int fileData[filenum];
int bratio = 25;
int cData[HEIGHT][WIDTH];

char yes(int x){
	if (x >= 254){
		return ' ';
	}else if (x >= 233){
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

int lowest(int y[filenum]){
	int z;
	for(int i = 0; i < filenum; i++){
		if (i == 0){
			z = y[i];
		} else if (y[i] < z){
			z = y[i];
		}
	}
	return z;
}
	
void chatData(int *cBox){
	//int fileRay[] = calloc(filenum*sizeof(int));
	for (int k = 0; k < filenum; k++){
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

			}
			
		}
		//## Giving the value of cBox to compare with brightness later. ###
		cBox[k] = MAXBRIGHT - MAXBRIGHT*((float) filepix/25);
		//free(image);
		cout << "Current file: " << filenames[k] << " Pixels(file): "<< filepix << " With brightness: "<< cBox[k] << endl;
		//cBox = charBox;
	}
}

//if (newBox[x][y] == charBox[x][y]){ Old matching code..
	//testBox++;
//}

char compare(int Brightness){
	//cout << "Comparing" << endl;
	for(int  k = 0; k < filenum; k++){
		if(fileData[k] <= Brightness){
			return filenames[k][0];
		}
	}
	return '.';
}

int main(){
	ofstream myfile;
	myfile.open("example.txt");
	myfile.clear();
	CImg<unsigned char> image("duck.bmp");
	CImgDisplay display(image,"This is a duck");
	int* filePnt = &fileData[0];
	chatData(filePnt);
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
		int Red =  image(x,y,0,0)*650;
		int Green = image(x,y,0,1)*510;
		int Blue = image(x,y,0,2)*475;
		int brightness = (Red+Green+Blue)/3;
		cData[x][y] = brightness;
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
			int avgbright = sum/(XBOX*YBOX) - 1;
			//cout << " Box#: "<< (i+j) << " brightness:" << avgbright << endl;
			//myfile << yes(avgbright);
			myfile << compare(avgbright);		
		}
		myfile << endl;
	}
	myfile.close();
	//cin >> x;
}