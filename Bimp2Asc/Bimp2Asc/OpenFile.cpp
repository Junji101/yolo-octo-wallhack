#include "OpenFile.h"

char imageFile[] = {"duck.bmp"};
char outFile[] = {"example.txt"};
char fileNames[fileNum][20] = {"`.bmp","~.bmp","^.bmp","!.bmp","Colon.bmp",";.bmp","(.bmp","Asterisk.bmp","+.bmp","].bmp","$.bmp","O.bmp","#.bmp", "@.bmp"};
char letters[fileNum] = {'`','~','^','!',':',';','(','*','+',']','$','O','#','@'};
int fileData[fileNum];
int cData[HEIGHT][WIDTH];


void charData(int *cBox){
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
	CImg<unsigned char> image(newImage);
	//CImg<unsigned char> image(imageFileName);
	//CImgDisplay display(newimage,"This is a duck");

	//image.RGBtoHSL();
	//display.wait();
	//cout << "Height: " << image._height << " Width: " << image._width << endl;
	//cout << "Warning: Image resolution must be below 550 x550" << endl;
	//cout << "How many half resize iterations" << endl;
	if (RESIZE){
		while (image.height()*image.width()/(XBOX*YBOX) > HEIGHT*WIDTH){
			image.resize_halfXY();
		}
	}
	//double newHeight = image._height*4/50 + .5;
	//double newWidth = image._width*4/50 + .5;
	cout << " New Height: " << image._height << " New Width: " << image._width << endl;
	int newWidth = image._width;
	int newHieght = image._height;
	//vector<vector<float> > cData(newHieght, vector<float>(newWidth));
	//cout << "Second File: " << fileNames[1] << endl;

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

void renderVideo(string s){
	string str = "ffmpeg -i \"" + s + ".mp4\" -r 1 -f image2 example/image-%3d.bmp";
	int i = system (str.c_str());
}

void loadVideo(string s, CImgList<unsigned char> bear){
	bear.load_video("Best of skiing.mp4");
}

int frames(string Vid){
	bool endImg = false;
	int counter = 0;
	while (endImg == false){
		try{
			//CImg <unsigned char> frame(Vid,counter);
		}
		catch(exception& e){
			cout << "frames in video: "<<counter;
			endImg = true;
		}
	}
	return 0;
}

void decisionMake(int k){
	string name;
	if (k == 0){
		cout << "Name of file: (Without extension)" << endl;
		cin >> name;
		renderVideo(name);
	} else if (k == 1){
		cout << "Name of file: (Without extension)" << endl;
		cin >> name;
		CImgList <unsigned char> imgList(MAXFRAMES);
		loadVideo(name,imgList);
	} else{
		//continue;
	}
}

int main(){
	//doTheThing(outFile,imageFile);
	//CImgList<unsigned char> imageList;
	int ans;
	cout << "Render, Load, or Already processed? (0,1,2)" << endl;
	cin >> ans;
	while (ans < 0 || ans > 3){
		cout << "Incorrect Parameter" << " Try again:" << endl;
		cin >> ans;
	}
	decisionMake(ans);
	cout << "Detecting frames" << endl << "Detecting Failed.." << "How many frames:" << endl;
	int frames;
	cin >> frames;
	//CImgList<unsigned char> imageList(MAXFRAMES);//(name.c_str());

	int* filePnt = &fileData[0];
	charData(filePnt);
	CImgDisplay Display;
	cout << "Got em!!";
	//int frames = 314;
	for (int z = 1; z <= frames;z++){
		string num;
		if(z < 10){
			num = "00" + to_string((_LONGLONG)z);
		}else if( z < 100){
			num = "0" + to_string((_LONGLONG)z);
		} else	{
			num = to_string((_LONGLONG)z);
		}
		cout << "We get num: " << num << endl;
		string inFile = "example/image-" + num + ".bmp";
		string outFile = "outPut/example" + to_string((_LONGLONG)z) + ".txt";
		CImg <unsigned char> tempImage;
		try{
			tempImage.assign(inFile.c_str());
		} catch(exception& e){
			cout << "Can't find file: " << inFile << endl;
		}
		Display.display(tempImage);
		//tempImage.display();
		doTheThing(outFile,tempImage);
	}
	
	//CImg<unsigned char> image();
	//cin >> x;
}

int LoadImage(string name, int frames){
	//doTheThing(outFile,imageFile);
	
	//imageList.load_ffmpeg_external("Best of skiing.mp4");
	/*int i;
	  printf ("Checking if processor is available...");
	  if (system(NULL)) puts ("Ok");
		else exit (EXIT_FAILURE);
	  printf ("Executing command DIR...\n");
	  string str = "ffmpeg -i \"" + name + ".mp4\" -r 1 -f image2 example/image-%3d.bmp";
	  i=system (str.c_str());
	  printf ("The value returned was: %d.\n",i);
	//
	*/
	for (int z = 0; z < frames;z++){
		string inFile = "example/image-" + to_string((_LONGLONG)z) + ".bmp";
		string outFile = "outPut/example" + to_string((_LONGLONG)z) + ".txt";
		//doTheThing(outFile,tempImage);
	}
	return 0;
	//CImg<unsigned char> image();
	//cin >> x;
}
