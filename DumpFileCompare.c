#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Usage: DumpCmp.exe <file1> <file2> BYTE/FLOAT/DOUBLE <tolerance>
// Example DumpCmp.exe <file1> <file2> DOUBLE 0.00001

#define BUFFER_SIZE	512

char ByteDifAbs(char A, char B)
{
	if (A > B)
		return A - B;
	return B - A;
}

double DoubleDifAbs(double A, double B)
{
	if (A > B)
		return A - B;
	return B - A;
}

int main(int ArgCount, char** Args)
{
	if (ArgCount != 5)
		return printf("Expected: <file1> <file2> BYTE/INT/FLOAT/DOUBLE <tolerance>\n");

	FILE *File1, *File2;
	{
		File1 = fopen(Args[1], "rb");
		if (File1 == NULL)
			return printf("Cannot open file %s.\n", Args[1]);

		File2 = fopen(Args[2], "rb");
		if (File2 == NULL)
			return printf("Cannot open file %s.\n", Args[2]);
	}

	printf("Comparing files [%s] and [%s]\n", Args[1], Args[2]);
	size_t IdenticalValues = 0;
	size_t MatchingValues = 0;
	size_t DifferentValues = 0;


	if (strcmp(Args[3], "BYTE") == 0)
	{
		char Buffer1[BUFFER_SIZE];
		char Buffer2[BUFFER_SIZE];

		size_t Read1;
		size_t Read2;

		char Tolerance = atoi(Args[4]);

		do
		{
			Read1 = fread(Buffer1, sizeof(char), BUFFER_SIZE, File1);
			Read2 = fread(Buffer2, sizeof(char), BUFFER_SIZE, File2);

			if (Read1 != Read2)
				return printf("    Size missmatch between files.\n");

			for (size_t i = 0; i < Read1; i++)
				if (Buffer1[i] == Buffer2[i])
					IdenticalValues++;
				else if (ByteDifAbs(Buffer1[i], Buffer2[i]) <= Tolerance)
					MatchingValues++;
				else DifferentValues++;

		}
		while ((Read1 == BUFFER_SIZE) && (Read2 == BUFFER_SIZE));
	}
	if (strcmp(Args[3], "DOUBLE") == 0)
	{
		double Buffer1[BUFFER_SIZE];
		double Buffer2[BUFFER_SIZE];

		size_t Read1;
		size_t Read2;

		

		double Tolerance = atof(Args[4]);

		do
		{
			Read1 = fread(Buffer1, sizeof(double), BUFFER_SIZE, File1);
			Read2 = fread(Buffer2, sizeof(double), BUFFER_SIZE, File2);

			if (Read1 != Read2)
				return printf("    Size missmatch between files.\n");

			for (size_t i = 0; i < Read1; i++)
				if (Buffer1[i] == Buffer2[i])
					IdenticalValues++;
				else if (DoubleDifAbs(Buffer1[i], Buffer2[i]) <= Tolerance)
					MatchingValues++;
				else DifferentValues++;

		} while ((Read1 == BUFFER_SIZE) && (Read2 == BUFFER_SIZE));
	}
	if (strcmp(Args[3], "FLOAT") == 0)
	{
		float Buffer1[BUFFER_SIZE];
		float Buffer2[BUFFER_SIZE];

		size_t Read1;
		size_t Read2;



		float Tolerance = (float)atof(Args[4]);

		do
		{
			Read1 = fread(Buffer1, sizeof(float), BUFFER_SIZE, File1);
			Read2 = fread(Buffer2, sizeof(float), BUFFER_SIZE, File2);

			if (Read1 != Read2)
				return printf("    Size missmatch between files.\n");

			for (size_t i = 0; i < Read1; i++)
				if (Buffer1[i] == Buffer2[i])
					IdenticalValues++;
				else if (DoubleDifAbs(Buffer1[i], Buffer2[i]) <= Tolerance)
					MatchingValues++;
				else DifferentValues++;

		} while ((Read1 == BUFFER_SIZE) && (Read2 == BUFFER_SIZE));
	}
	

	printf("    IdenticalValues: %llu (These values are identical)\n", IdenticalValues);
	printf("    MatchingValues: %llu (These values met the tolerance)\n", MatchingValues);
	printf("    DifferentValues: %llu (These values are different)\n", DifferentValues);



	return 0;
}