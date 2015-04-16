#include "Headers\CImg.h"
#include <iostream>
#include <fstream>
#include <string>
#include "Headers\inttypes.h"

using namespace cimg_library;
using namespace std;

#define inline _inline
#define HEIGHT  700
#define WIDTH  550
#define XBOX 5
#define YBOX 5
#define fileNum 14
#define MAXBRIGHT 138975

char imageFile[] = {"duck.bmp"};
char outFile[] = {"example.txt"};
char fileNames[fileNum][20] = {"`.bmp","~.bmp","^.bmp","!.bmp","Colon.bmp",";.bmp","(.bmp","Asterisk.bmp","+.bmp","].bmp","$.bmp","O.bmp","#.bmp", "@.bmp"};
char letters[fileNum] = {'`','~','^','!',':',';','(','*','+',']','$','O','#','@'};
int fileData[fileNum];
int cData[HEIGHT][WIDTH];


void chatData(int *cBox){
	//int fileRay[] = calloc(fileNum*sizeof(int));
	for (int k = 0; k < fileNum; k++){
		CImg<unsigned char> image(fileNames[k]);
		int charBox[7][10];
		int testBox = 0;
		int filepix = 0;
		for (int x = 0; x < image.width(); x++){ //creates a 2d array of character with pixels being 1 and no pixels being 0
			for(int y = 0; y < image.height(); y++){
				if (image(x,y,0,1) < 250){
					//cout << "Pixel of" << fileNames[k] <<  "at: " << x << ", " << y << endl;
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
		cout << "Current file: " << fileNames[k] << " Pixels(file): "<< filepix << " With brightness: "<< cBox[k] << endl;
		//cBox = charBox;
	}
}

char compare(int Brightness){
	//cout << "Comparing" << endl;
	for(int  k = 0; k < fileNum; k++){
		if(fileData[k] <= Brightness){
			return letters[k];
		}
	}
	return '.';
}

void doTheThing(string outPutFile, CImg<unsigned char> newImage){
	ofstream myfile;
	myfile.open(outPutFile);
	myfile.clear();
	CImg<unsigned char> image;
	image = newImage;
	//CImg<unsigned char> image(imageFileName);
	//CImgDisplay display(newimage,"This is a duck");
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
		//image = image.resize_halfXY);
	}
	//double newHeight = image._height*4/50 + .5;
	//double newWidth = image._width*4/50 + .5;
	cout << " New Height: " << image._height << " New Width: " << image._width << endl;
	int newWidth = image._width;
	int newHieght = image._height;
	//vector<vector<float> > cData(newHieght, vector<float>(newWidth));
	cout << "Second File: " << fileNames[1] << endl;

	cimg_forXY(image,x,y){
		int Red =  image(x,y,0,0)*650;
		int Green = image(x,y,0,1)*510;
		int Blue = image(x,y,0,2)*475;
		int brightness = (Red+Green+Blue)/3;
		cData[x][y] = brightness;
		//cout << "Average:" << average << endl;
	}


	for (int i = 0 ; i < newHieght-YBOX; i+=YBOX){
		for (int j = 0; j < newWidth-XBOX;j+=XBOX){
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
}


int main(){
	//doTheThing(outFile,imageFile);
	CImgList<unsigned char> imageList;
	imageList.load_ffmpeg_external("Best of skiing.mp4");
	for (int z = 0; z < imageList.size();z++){
		string outFile = "outPut/example" + to_string((_LONGLONG)z) + ".txt";
		CImg <unsigned char> tempImage(imageList.at(z));
		doTheThing(outFile,tempImage);
	}
	//CImg<unsigned char> image();
	//cin >> x;
}