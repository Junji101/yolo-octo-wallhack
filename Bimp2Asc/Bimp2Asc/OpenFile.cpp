#include "Headers\CImg.h"
#include <iostream>
#include <fstream>
#include <vector>
using namespace cimg_library;
using namespace std;

int twobytwo[2][2];
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

int main(){
	ofstream myfile;
	myfile.open("example.txt");
	myfile.clear();
	CImg<unsigned char> image("duck.bmp");
	CImgDisplay main_disp(image,"Click a point");
	//image.RGBtoHSL();
	main_disp.wait();
	cout << "Height: " << image._height << " Width: " << image._width << endl;
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
	int cData[500][500];

	cimg_forXY(image,x,y){
		int Red =  image(x,y,0,0);
		int Green = image(x,y,0,1);
		int Blue = image(x,y,0,2);
		int average = (Red+Green+Blue)/3;
		cData[x][y] = average;
	}

	for (int i = 0 ; i < newHieght; i+=2){
		for (int j = 0; j < newWidth-2;j+=2){
			int z = (cData[j][i] + cData[j+1][i] + cData[j][i+1] + cData[j+1][i+1])/4;
			cout << z;
			myfile << yes(z);
		}
		myfile << endl;
	}
	myfile.close();
	cin >> x;
}