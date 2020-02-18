/****
  SoftVision. Software for Computer Vision

  Gregorio Ambrosio Cestero (goyo@computer.org)
  System Engineering and Automation Department 
  University of Malaga. Spain                   

  $RCSfile: main_stcorr.cpp,v $
  $Revision: 1.1 $
  $Date: 2000/01/21 13:04:47 $
  $Name:  $

****/

/******************************************************************************\                                                                          *
* SoftVision Toolbox. Software for Computer Vision                             *
*                                                                              *
* Author  : Gregorio Ambrosio Cestero (goyo@computer.org)                      *
*           System Engineering and Automation Department                       *
*           University of Malaga. Spain                                        *
*                                                                              *
*               Copyright (c) 2000, Gregorio Ambrosio cestero                  *
*                          All Rights Reserved                                 *
*                                                                              *
* Permission to use, copy, modify, and distribute this software and its        *
* associated documentation for non-commercial purposes is hereby granted,      *
* provided that the above copyright notice appears in all copies, derivative   *
* works or modified versions of the software and any portions thereof, and     *
* that both the copyright notice and this permission notice appear in the      *
* documentation.  Gregorio Ambrosio Cestero (GAC for short) shall be given     *
* a copy of any such derivative work or modified version of the software and   *
* GAC shall be granted permission to use, copy, modify and distribute the      *
* software for his own use and research. This software is experimental.        *
* GAC does not make any representations regarding the suitability of this      *
* software for any purpose and GAC will not support the software.              *
*                                                                              *
* THE SOFTWARE IS PROVIDED AS IS.  GAC DOES NOT MAKE ANY WARRANTIES            *
* EITHER EXPRESS OR IMPLIED WITH REGARD TO THE SOFTWARE. GAC ALSO              *
* DISCLAIMS ANY WARRANTY THAT THE SOFTWARE IS FREE OF INFRINGEMENT OF ANY      *
* INTELLECTUAL PROPERTY RIGHTS OF OTHERS.  NO OTHER LICENSE EXPRESS OR         *
* IMPLIED IS HEREBY GRANTED. GAC SHALL NOT BE LIABLE FOR ANY DAMAGES,          *
* INCLUDING GENERAL, SPECIAL, INCIDENTAL, OR CONSEQUENTIAL DAMAGES, ARISING    *
* OUT OF THE USE OR INABILITY TO USE THE SOFTWARE.                             *
*                                                                              *
\******************************************************************************/


/************************************************************\
 *                         StCorr                           *
 *----------------------------------------------------------*
 *															*
\************************************************************/

// The debugger can't handle symbols more than 255 characters long.
// STL often creates symbols longer than that.
// When symbols are longer than 255 characters, the warning is disabled.
#pragma warning(disable:4786)

#include <time.h>
#include <typeinfo.h>

#include "StereoImage.h"

//using namespace std;

void sleep( clock_t wait );

int main( int argc, char *argv[] )
{
	StereoImage SI;

	//Timing data
	clock_t start, finish;
	double  duration;

	//Aux data
	int i;

	//Error data
	int ErrorCode=0;

	//Flags
	bool OK_LeftImageFileName      = false;
	bool OK_RightImageFileName     = false;
	bool OK_DisparityOutputFileName  = false;
	bool ON_TraceOutput			   = false;

	//Input parameter data
	char Parameter[10];
	char Data[256];
	char LeftFileExt[256];
	char RightFileExt[256];
	char *pchar;
	int ichar;
	char *StopString;

	//File data
	char LeftImageFileName[256];
	char RightImageFileName[256];
	char DisparityOutputFileName[256];
	FILE * DisparityOutputFile;

	//Default data initialization
	//Stereo
	size_t M		= 3;
	size_t N		= 3;
	size_t MaxDisp  = 10;
	Image D;
	//Misc data
	StructMiscData MiscData;
	MiscData.TraceMessages          = false;


	// Elimino argv[0] que es el propio comando:
	argv++;
	argc--;

	if (!argc) {
		printf("Stereo with Correlation (rv.1)\n");
		printf("=============================================\n\n");
		printf("stcorr -il:<string> [-ir:<string>] [-o:<string>] \n"
			   "         [-M:<int>] [-N:<int>] [-D:<int>]\n"
			   "         [-d] \n\n");
		printf("input/output parameters\n");
		printf("=======================\n");
		printf("-il Left image file name\n");
		printf("-ir Right image file name\n");
		printf("-o   Output file name\n");
		printf("\nStereo parameters\n");
		printf("=====================\n");
		printf("-M   Num. of corr. window's rows (2M+1):[%i]\n",M);
		printf("-N   Num. of corr. window's rows (2N+1):[%i]\n",N);
		printf("-D   Max disparity                     :[%i]\n",MaxDisp);
		printf("\nDebug data parameters\n");
		printf("=====================\n");
		printf("-d Outputs trace data\n");
		printf("\nOthers\n");
		printf("======\n");
		printf("-gac Author info\n");
		printf("-v   Version info\n");
		printf("\nExample\n");
		printf("=======\n");
		printf("stereo -il:left.bmp -ir:right.bmp -o:myoutput -M:2 -N:3 -d\n");
	}
	else {
		for( i = 0; i < argc; ++i ){
			pchar = strchr(argv[i],':');
			if (pchar){
				ichar = pchar - argv[i] + 1;
				sprintf(Parameter,"%.*s",ichar-1,argv[i]);
				sprintf(Data,"%.*s",strlen(argv[i])-ichar,argv[i]+ichar);
				if (strlen(Data)==0){
					ErrorCode = 6;
					break;
				}
			}
			else
				sprintf(Parameter,"%s",argv[i]);

			//Others
			if (strcmp(Parameter,"-gac")==0) {
				printf("===================================\n");
				printf("Gregorio Ambrosio Cestero\n");
				printf("University of Malaga\n");
				printf("Department of System Engineering and Automation\n");
				printf("Email: goyo@computer.org\n");
				printf("===================================\n");
				ErrorCode = 100;
				break;
			}
			else if (strcmp(Parameter,"-v")==0) {
				printf("Stereo with Correlation (rv.1)\n");
				printf("Win32 version\n");
				ErrorCode = 100;
				break;
			}
			//Input data file
			else if (strcmp(Parameter,"-il")==0) {
				pchar = strrchr(Data,'.');
				if (pchar){
					ichar = pchar - Data + 1;
					sprintf(LeftFileExt,"%.*s",strlen(Data)-ichar,Data+ichar);
					if ((strcmp(LeftFileExt,"mat") && strcmp(LeftFileExt,"bmp") && strcmp(LeftFileExt,"pgm"))){
						ErrorCode = 7;
						break;
					}
					else {
						strcpy(LeftImageFileName,Data);
						OK_LeftImageFileName = true;
					}

				}
				else{
					ErrorCode = 7;
					break;
				}
			}
			else if (strcmp(Parameter,"-ir")==0) {
				pchar = strrchr(Data,'.');
				if (pchar){
					ichar = pchar - Data + 1;
					sprintf(RightFileExt,"%.*s",strlen(Data)-ichar,Data+ichar);
					if ((strcmp(RightFileExt,"mat") && strcmp(RightFileExt,"bmp") && strcmp(RightFileExt,"pgm"))){
						ErrorCode = 7;
						break;
					}
					else {
						strcpy(RightImageFileName,Data);
						OK_RightImageFileName = true;
					}

				}
				else{
					ErrorCode = 7;
					break;
				}
			}
			//Output data file
			else if (strcmp(Parameter,"-o")==0) {
				strcpy(DisparityOutputFileName,Data);

				if (((DisparityOutputFile  = fopen(DisparityOutputFileName ,"a"))==NULL)){
					ErrorCode = 2;
					break;
				}
				else {
					fclose(DisparityOutputFile);
					OK_DisparityOutputFileName  = true;
				}
			}

			//Processing parameters
			else if (strcmp(Parameter,"-d")==0) {
				ON_TraceOutput = true;
			}

			//Edge detection data
			else if (strcmp(Parameter,"-M")==0) {
				M	= strtod(Data,&StopString);
				if (M>100)
					M = 100;
				if (M<1)
					M = 1;
			}
			else if (strcmp(Parameter,"-N")==0) {
				N	= strtod(Data,&StopString);
				if (N>100)
					N = 100;
				if (N<1)
					N = 1;
			}
			else if (strcmp(Parameter,"-D")==0) {
				MaxDisp	= strtod(Data,&StopString);
				if (MaxDisp>1000)
					MaxDisp = 1000;
				if (MaxDisp<1)
					MaxDisp = 1;
			}
			else {
			}

		}


		//Flags test
		if(!ErrorCode){
			if      (!OK_LeftImageFileName)      ErrorCode = 3;
			else if (!OK_RightImageFileName)     ErrorCode = 4;
			else if (!OK_DisparityOutputFileName)  ErrorCode = 5;
		}

		if (!ErrorCode) {
			printf("\n");
			printf("Stereo with Correlation (rv.1)\n");
			printf("==============================\n\n");
			printf("Processing with following data input: \n");
			printf("-M   Num. of corr. window's rows (2M+1):[%i]\n",2*M+1);
			printf("-N   Num. of corr. window's rows (2N+1):[%i]\n",2*N+1);
			printf("-D   Max disparity                     :[%i]\n",MaxDisp);
			printf("\n");

			//Process
		    start = clock();
			if (!strcmp(LeftFileExt,"mat"))
				SI.L.LoadMAT(LeftImageFileName);
			else if (!strcmp(LeftFileExt,"bmp"))
				SI.L.LoadBMP(LeftImageFileName);
			else if (!strcmp(LeftFileExt,"pgm"))
				SI.L.LoadPGM(LeftImageFileName);

			if (!strcmp(RightFileExt,"mat"))
				SI.R.LoadMAT(RightImageFileName);
			else if (!strcmp(RightFileExt,"bmp"))
				SI.R.LoadBMP(RightImageFileName);
			else if (!strcmp(RightFileExt,"pgm"))
				SI.R.LoadPGM(RightImageFileName);

			MiscData.TraceMessages  = ON_TraceOutput;

			if (!SI.L.GetErrorCode() && !SI.R.GetErrorCode()){
				D = SI.CorrelationStereo(M,N,MaxDisp,MiscData);
				printf("\nProcess finished. Status: %s\n\n",SI.GetStrError());

				//sleep( (clock_t)1 * CLOCKS_PER_SEC );
				finish = clock();
				duration = (double)(finish - start)/ CLOCKS_PER_SEC;

				int count1 = 0;
				count1 += D.SavePGM(DisparityOutputFileName);

				//Output data
				printf ("Disparity image output file: %s (%i bytes)\n",DisparityOutputFileName,count1);

				printf ("\nProcessing time        : %g seconds\n\n",duration);

			}
			else {
				printf("Left image error: %s\n",SI.L.GetStrError());
				printf("Right image error: %s\n",SI.R.GetStrError());
			}
		}
	}

	//ErrorCode
	switch (ErrorCode) {
	case 0:
		break;
	case 1: 
		printf("Error: %i File input error \n",ErrorCode);
		break;
	case 2: 
		printf("Error: %i File output error \n",ErrorCode);
		break;
	case 3: 
//		printf("Error: %i Left image file name must be provided\n",ErrorCode);
		printf("Error: %i Image file name must be provided\n",ErrorCode);
		break;
	case 4: 
		printf("Error: %i Right image file name must be provided\n",ErrorCode);
		break;
	case 5: 
		printf("Error: %i Output file name must be provided\n",ErrorCode);
		break;
	case 6: 
		printf("Error: %i Parameter error\n",ErrorCode);
		break;
	case 7: 
		printf("Error: %i Only (*.bmp), (*.pgm) and (*.mat) files are supported\n",ErrorCode);
		break;
	case 100: 
		ErrorCode = 0;
		break;
	default: 
		printf("Unknown error\n");
		break;
	}

	return ErrorCode;

}

/* Pauses for a specified number of milliseconds. */
void sleep( clock_t wait ){
   clock_t goal;
   goal = wait + clock();
   while( goal > clock() )
	   ;
}