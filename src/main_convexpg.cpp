/****
  SoftVision. Software for Computer Vision

  Gregorio Ambrosio Cestero (goyo@computer.org)
  System Engineering and Automation Department 
  University of Malaga. Spain                   

  $RCSfile: main_convexpg.cpp,v $
  $Revision: 1.1 $
  $Date: 2000/01/21 13:04:45 $
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
 *                         ConvexPG                         *
 *----------------------------------------------------------*
 * Temas pendientes:                                        *
 *															*
\************************************************************/

// The debugger can't handle symbols more than 255 characters long.
// STL often creates symbols longer than that.
// When symbols are longer than 255 characters, the warning is disabled.
#pragma warning(disable:4786)

#include <time.h>
#include <typeinfo.h>

#include "Image.h"
#include "MatrixOperator.h"

//using namespace std;

void sleep( clock_t wait );

int main( int argc, char *argv[] )
{
	Image I;

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
	bool OK_StereopgOutputFileName = false;
	bool OK_FVOutputFileName       = false;
	bool ON_SegmentsOutput		   = false;
	bool ON_PerceptualGroupsOutput = false;
	bool ON_TraceOutput			   = false;

	//Input parameter data
	char Parameter[10];
	char Data[256];
	char FileExt[256];
	char *pchar;
	int ichar;
	char *StopString;

	//File data
	char LeftImageFileName[256];
	char RightImageFileName[256];
	char StereopgOutputFileName[256];
	char FVOutputFileName[256];
	FILE * LeftImageFile;
	FILE * RightImageFile;
	FILE * StereopgOutputFile;
	FILE * FVOutputFile;

	//Default data initialization
	//Edge detection
	double Sigma           = 1;
	unsigned char HighHyst = 106;
	unsigned char LowHyst  = 85;
	//Segment Extraction
	StructSData SData;
	SData.MaxLinearRegressionError	= 0.5;
	SData.MinNumOfPixels			= 20;
	//Perceptual Grouping
	StructPGData PGData;
	PGData.MaxDistBetwProxSegments			= 50;
	PGData.MaxDistBetwParallelSegments		= 10;
	PGData.MaxAngleDiffBetwParallelSegments = 10;
	PGData.MaxDistBetwColSegments			= 20;
	PGData.k								= 0.7;
	PGData.MaxNoConvexityThreshold          = 15.0;
	PGData.JacobExtension_1					= false;
	PGData.JacobExtension_2					= false;
	//Misc data
	StructMiscData MiscData;
	MiscData.TraceMessages          = false;


	// Elimino argv[0] que es el propio comando:
	argv++;
	argc--;

	if (!argc) {
		printf("Convex Perceptual Grouping (rv.3)\n");
		printf("======================================\n\n");
		printf("convexpg -i:<string> -o:<string> -ofv:<string>\n"
			   "         [-e0:<float>] [-e1:<int>] [-e2:<int>]\n"
			   "         [-s0:<float>] [-s1:<int>]\n"
			   "         [-p0:<float>] [-p4:<float>] [-p5:<float>] [-p6] [-p7]\n"
			   "         [-d0] [-d1]\n\n");
		printf("input/output parameters\n");
		printf("=======================\n");
//		printf("-i0 Left image file name\n");
//		printf("-i1 Right image file name\n");
		printf("-i   Image file name\n");
		printf("-o   Output file name\n");
		printf("-ofv Feature Vector file name\n");
		printf("\nEdge extraction parameters (Canny detector)\n");
		printf("===========================================\n");
		printf("-e0 Sigma                     [%g]\n",Sigma);
		printf("-e1 Low  hysteresis threshold [%i]\n",LowHyst);
		printf("-e2 High hysteresis threshold [%i]\n",HighHyst);
		printf("\nSegment extraction parameters\n");
		printf("=============================\n");
		printf("-s0 Max Linear regression error      [%g]\n",SData.MaxLinearRegressionError);
		printf("-s1 Min lentgh of segments in pixels [%i]\n",SData.MinNumOfPixels);
		printf("\nConvex Perceptual Grouping parameters\n");
		printf("==============================\n");
		printf("-p0 Max euclidean distance between near segments      [%g]\n",PGData.MaxDistBetwProxSegments);
//		printf("-p1 Max euclidean distance between parallel segments  [%g]\n",PGData.MaxDistBetwParallelSegments);
//		printf("-p2 Max angle (grades) between parallel segments      [%g]\n",PGData.MaxAngleDiffBetwParallelSegments);
//		printf("-p3 Max euclidean distance between collinear segments [%g]\n",PGData.MaxDistBetwColSegments);
		printf("-p4 Min salience fraction                             [%g]\n",PGData.k);
		printf("-p5 Max threshold of non convexity                    [%g]\n",PGData.MaxNoConvexityThreshold);
		printf("-p6 Switch of the extensions (1) of the algorithm     [%i]\n",PGData.JacobExtension_1);
		printf("-p7 Switch of the extensions (2) of the algorithm     [%i]\n",PGData.JacobExtension_2);
		printf("\nDebug data parameters\n");
		printf("=====================\n");
		printf("-d0 Outputs segments data\n");
		printf("-d1 Outputs perceptual groups data\n");
		printf("-d2 Outputs trace data\n");
		printf("\nOthers\n");
		printf("======\n");
		printf("-gac Author info\n");
		printf("-v   Version info\n");
		printf("\nExample\n");
		printf("=======\n");
//		printf("stereopg -i0:left.mat -i1:right.mat -o:myoutput.spg -e0:0.85 -p2:10 -d1\n");
		printf("convexpg -i:mydir/image.bmp -o:myoutput.sva -ofv:myfvoutput -e0:0.85 -p4:0.75 -d1\n");
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
				printf("Universidad de Malaga\n");
				printf("Ingenieria de Sistemas y Automatica\n");
				printf("Phone: +34 09 480 133\n");
				printf("Email: goyo@computer.org\n");
				printf("===================================\n");
				ErrorCode = 100;
				break;
			}
			else if (strcmp(Parameter,"-v")==0) {
				printf("Convex Perceptual Grouping (rv.3)\n");
				printf("Win32 version\n");
				ErrorCode = 100;
				break;
			}
			//Input data file
			else if (strcmp(Parameter,"-i")==0) {
				pchar = strrchr(Data,'.');
				if (pchar){
					ichar = pchar - Data + 1;
					sprintf(FileExt,"%.*s",strlen(Data)-ichar,Data+ichar);
					if ((strcmp(FileExt,"mat") && strcmp(FileExt,"bmp") && strcmp(FileExt,"pgm"))){
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
			else if (strcmp(Parameter,"-i0")==0) {
				if ((LeftImageFile = fopen(Data,"r"))==NULL){
					ErrorCode = 1;
					break;
				}
				else {
					fclose(LeftImageFile);
					strcpy(LeftImageFileName,Data);
					OK_LeftImageFileName = true;
				}
			}
			else if (strcmp(Parameter,"-i1")==0) {
				if ((RightImageFile = fopen(Data,"r"))==NULL){
					ErrorCode = 1;
					break;
				}
				else {
					fclose(RightImageFile);
					strcpy(RightImageFileName,Data);
					OK_RightImageFileName = true;
				}
			}
			//Output data file
			else if (strcmp(Parameter,"-o")==0) {
				if ((StereopgOutputFile = fopen(Data,"a"))==NULL){
					ErrorCode = 2;
					break;
				}
				else {
					fclose(StereopgOutputFile);
					strcpy(StereopgOutputFileName,Data);
					OK_StereopgOutputFileName = true;
				}
			}
			//Feature Vector output data file
			else if (strcmp(Parameter,"-ofv")==0) {
				if ((FVOutputFile = fopen(Data,"a"))==NULL){
					ErrorCode = 2;
					break;
				}
				else {
					fclose(FVOutputFile);
					strcpy(FVOutputFileName,Data);
					OK_FVOutputFileName = true;
				}
			}

			//Debug output
			else if (strcmp(Parameter,"-d0")==0) {
				ON_SegmentsOutput = true;
			}
			else if (strcmp(Parameter,"-d1")==0) {
				ON_PerceptualGroupsOutput = true;
			}
			else if (strcmp(Parameter,"-d2")==0) {
				ON_TraceOutput = true;
			}

			//Edge detection data
			else if (strcmp(Parameter,"-e0")==0) {
				Sigma	= strtod(Data,&StopString);
				if (Sigma>100)
					Sigma = 5;
				if (Sigma<0.000001)
					Sigma = 0.000001;
			}
			else if (strcmp(Parameter,"-e1")==0) {
				LowHyst	= strtod(Data,&StopString);
				if (LowHyst>255)
					LowHyst = 255;
				if (LowHyst<0)
					LowHyst = 0;
			}
			else if (strcmp(Parameter,"-e2")==0) {
				HighHyst	= strtod(Data,&StopString);
				if (HighHyst>255)
					HighHyst = 255;
				if (HighHyst<0)
					HighHyst = 0;
			}
			//Segment extraction data
			else if (strcmp(Parameter,"-s0")==0) {
				SData.MaxLinearRegressionError	= strtod(Data,&StopString);
				if (SData.MaxLinearRegressionError>100)
					SData.MaxLinearRegressionError = 100;
				if (SData.MaxLinearRegressionError<0)
					SData.MaxLinearRegressionError = 0;
			}
			else if (strcmp(Parameter,"-s1")==0) {
				SData.MinNumOfPixels	= strtod(Data,&StopString);
				if (SData.MinNumOfPixels<0)
					SData.MinNumOfPixels = 0;
			}
			//Perceptual grouping
			else if (strcmp(Parameter,"-p0")==0) {
				PGData.MaxDistBetwProxSegments	= strtod(Data,&StopString);
				if (PGData.MaxDistBetwProxSegments<0)
					PGData.MaxDistBetwProxSegments = 0;
			}
			else if (strcmp(Parameter,"-p1")==0) {
				PGData.MaxDistBetwParallelSegments	= strtod(Data,&StopString);
				if (PGData.MaxDistBetwParallelSegments<0)
					PGData.MaxDistBetwParallelSegments = 0;
			}
			else if (strcmp(Parameter,"-p2")==0) {
				PGData.MaxAngleDiffBetwParallelSegments	= strtod(Data,&StopString);
				if (PGData.MaxAngleDiffBetwParallelSegments<0)
					PGData.MaxAngleDiffBetwParallelSegments = 0;
			}
			else if (strcmp(Parameter,"-p3")==0) {
				PGData.MaxDistBetwColSegments	= strtod(Data,&StopString);
				if (PGData.MaxDistBetwColSegments<0)
					PGData.MaxDistBetwColSegments = 0;
			}
			else if (strcmp(Parameter,"-p4")==0) {
				PGData.k	= strtod(Data,&StopString);
				if (PGData.k<0)
					PGData.k = 0;
			}
			else if (strcmp(Parameter,"-p5")==0) {
				PGData.MaxNoConvexityThreshold	= strtod(Data,&StopString);
				if (PGData.MaxNoConvexityThreshold<0)
					PGData.MaxNoConvexityThreshold = 0;
			}
			else if (strcmp(Parameter,"-p6")==0) {
				PGData.JacobExtension_1 = true;
			}
			else if (strcmp(Parameter,"-p7")==0) {
				PGData.JacobExtension_2 = true;
			}
			else {
			}

		}


		//Flags test
		if(!ErrorCode){
			if      (!OK_LeftImageFileName)      ErrorCode = 3;
			//else if (!OK_RightImageFileName)     ErrorCode = 4;
			else if (!OK_StereopgOutputFileName) ErrorCode = 5;
			else if (!OK_FVOutputFileName)       ErrorCode = 8;
		}

		if (!ErrorCode) {
			printf("\n");
			printf("Convex Perceptual Grouping (rv.3)\n");
			printf("======================================\n\n");
			printf("Processing with following data input: \n");
			printf("	Edge detection (Canny)\n");
			printf("		Sigma                       : %g\n",Sigma);
			printf("		Low  hysteresis threshold   : %i\n",LowHyst);
			printf("		High hysteresis threshold   : %i\n",HighHyst);
			printf("	Segment extraction\n");
			printf("		Max Linear Regression Error     : %g\n",SData.MaxLinearRegressionError);
			printf("		Min lentgh of segments (pixels) : %i\n",SData.MinNumOfPixels);
			printf("	Perceptual Grouping\n");
			printf("		Max distance between near segments      : %g\n",PGData.MaxDistBetwProxSegments);
//			printf("		Max distance between parallel segments  : %g\n",PGData.MaxDistBetwParallelSegments);
//			printf("		Max angle between parallel segments     : %g\n",PGData.MaxAngleDiffBetwParallelSegments);
//			printf("		Max distance between collinear segments : %g\n",PGData.MaxDistBetwColSegments);
			printf("		Min salience fraction                   : %g\n",PGData.k);
			printf("		Max threshold of non convexity          : %g\n",PGData.MaxNoConvexityThreshold);
			printf("		Switch of the extensions (1) of the algorithm :%i\n",PGData.JacobExtension_1);
			printf("		Switch of the extensions (2) of the algorithm :%i\n",PGData.JacobExtension_2);

			//Process
		    start = clock();
			if (!strcmp(FileExt,"mat"))
				I.LoadMAT(LeftImageFileName);
			else if (!strcmp(FileExt,"bmp"))
				I.LoadBMP(LeftImageFileName);
			else if (!strcmp(FileExt,"pgm"))
				I.LoadPGM(LeftImageFileName);

			MiscData.TraceMessages  = ON_TraceOutput;

			if (!I.GetErrorCode()){
				I.CannyS(Sigma,LowHyst,HighHyst);
				I.PostCanny();
				I.PostCanny();
				I.Segmentation(SData);
				I.ConvexPerceptualGrouping(SData,PGData,MiscData);

				//sleep( (clock_t)1 * CLOCKS_PER_SEC );
				finish = clock();
				duration = (double)(finish - start)/ CLOCKS_PER_SEC;

				FILE * stream = OpenSerialize(StereopgOutputFileName) ;
				int count1 = 0;
				count1 += I.Serialize(stream);
				CloseSerialize(stream);

				stream = OpenSerialize(FVOutputFileName) ;
				int count2 = 0;
				count2 += I.FeatureVectorSerialize(stream);
				CloseSerialize(stream);

				
				//Output data
				printf ("\n");
				printf ("Segments count         : %i \n",I.SegmentRetina.size());
				printf ("Perceptual groups count: %i \n",I.PerceptualGroupRetina.size());
				printf ("Processing time        : %g seconds\n\n",duration);
				printf ("Output file: %s (%i bytes)\n",StereopgOutputFileName,count1);
				printf ("Feature vector output file: %s (%i bytes)\n",FVOutputFileName,count2);

				if (ON_SegmentsOutput) {
					printf ("Segments\n");
					printf ("===========================\n\n");
					I.ConvexSegmentRetina.Show();
				}
				if (ON_PerceptualGroupsOutput) {
					printf ("Perceptual groups\n");
					printf ("===========================\n\n");
		 			I.ConvexPerceptualGroupRetina.Show(I.ConvexSegmentRetina);
				}

				printf("\nProcessing time: %g sec.\n",duration);
			}
			else
				printf("Error: %s\n",I.GetStrError());
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
	case 8: 
		printf("Error: %i Feature Vector output file name must be provided\n",ErrorCode);
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

