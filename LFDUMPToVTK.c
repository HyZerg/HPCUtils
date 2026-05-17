#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//	0	1		2					  3		4
// .exe <input> <output NO EXTENSION> SizeX SizeY
int main(int ArgCount, char** Args)
{
	FILE* Input;
	char OutputFileName[256];
	int nx, ny;


	{
		if (ArgCount < 5)
			return printf("Usage: <input> <output NO EXTENSION> SizeX SizeY\n");

		Input = fopen(Args[1], "rb");
		if (Input == NULL)
			return printf("Could not open input file.\n");

	
		nx = atoi(Args[3]);
		ny = atoi(Args[4]);
	}

	

	int FrameCounter = 0;
	size_t CountRead = 0;
	double* Frame = malloc(sizeof(double) * nx * ny);
	while (CountRead = fread(Frame, sizeof(double), nx * ny, Input))
	{
		if (CountRead != nx * ny)
			return printf("Invalid size specified. Tried to read frame of size %dx%d but only got %llu values.\n", nx, ny, CountRead);
		
		sprintf(OutputFileName, "%s[%d].vtk", Args[2], FrameCounter);
		FILE* f = fopen(OutputFileName, "w");
		{
			long int i, j;
			fprintf(f, "# vtk DataFile Version 2.0\n");
			fprintf(f, "This is a test file for the vtk format file export\n");
			fprintf(f, "ASCII\n");
			fprintf(f, "DATASET UNSTRUCTURED_GRID\n\n");
			fprintf(f, "POINTS %d double\n", (nx + 1) * (ny + 1));
			for (i = 0;i < ny + 1;i++)
				for (j = 0;j < nx + 1;j++)
					fprintf(f, "%.20lf %.20lf %.20lf\n", (double)i / (double)ny, (double)j / (double)nx, 0.0);
			fprintf(f, "\nCELLS %d %d\n", nx * ny, 5 * (nx * ny));
			for (i = 0;i < ny;i++)
				for (j = 0;j < nx;j++)
					fprintf(f, "4  %ld  %ld  %ld  %ld\n", j + i * nx + i, j + i * nx + i + 1, j + (i + 1) * nx + i + 2, j + (i + 1) * nx + i + 1);
			fprintf(f, "\nCELL_TYPES   %d\n", nx * ny);
			for (i = 0;i < ny * nx;i++)
				fprintf(f, "9 ");
			fprintf(f, "\nCELL_DATA   %d\n", (nx) * (ny));
			fprintf(f, "SCALARS u FLOAT\n");
			fprintf(f, "LOOKUP_TABLE values_table\n");
			for (i = 0;i < ny;i++)
				for (j = 0;j < nx;j++)
					fprintf(f, "%.20lf\n", isnan(Frame[i*nx+j]) ? 0.0: Frame[i * nx + j]);
		}
		fclose(f);
		FrameCounter++;
	}


	return 0;
}