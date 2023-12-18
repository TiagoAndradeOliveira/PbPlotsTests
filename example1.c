#include "pbPlots.h"
#include "supportLib.h"

double xs [] = {-4, -2, 0, 2, 4, 30}; //Set of coordinates in X axis
double ys [] = {4, -2, -4, -2, 4, 30}; //Set of coordinates in Y axis

#define N 6 //Number of coordinates pairs in the graph

/*
	This function is to turn the main in a single function that 
	draws the graph. It needs to be a type _Bool because thats how
	the PbPlots Library does it in the example 1
*/

_Bool PrintGraphic(double xs[N], double ys[N]){
	
	_Bool success;

	StartArenaAllocator();

	RGBABitmapImageReference *canvasReference = CreateRGBABitmapImageReference();
	StringReference *errorMessage = CreateStringReference(L"", 0);
	success = DrawScatterPlot(canvasReference, 600, 400, xs, N, ys, N, errorMessage);

	if(success){
		size_t length;
		ByteArray *pngdata = ConvertToPNG(canvasReference->image);
		WriteToFile(pngdata, "example1.png");
		DeleteImage(canvasReference->image);
	}else{
		fprintf(stderr, "Error: ");
		for(int i = 0; i < errorMessage->stringLength; i++){
			fprintf(stderr, "%c", errorMessage->string[i]);
		}
		fprintf(stderr, "\n");
	}

	FreeAllocations();

	return success ? 0 : 1;
}

int main(){

	PrintGraphic(xs, ys);
	
}