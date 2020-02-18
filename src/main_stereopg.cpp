/****
  SoftVision. Software for Computer Vision

  Gregorio Ambrosio Cestero (goyo@computer.org)
  System Engineering and Automation Department 
  University of Malaga. Spain                   

  $RCSfile: main_stereopg.cpp,v $
  $Revision: 1.1 $
  $Date: 2000/01/21 13:04:48 $
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
 *                         StereoPG                         *
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

#include "StereoImage.h"
#include "MatrixOperator.h"

using namespace GAC;

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
	bool OK_LeftSvaOutputFileName  = false;
	bool OK_RightSvaOutputFileName = false;
	bool OK_LeftFVOutputFileName   = false;
	bool OK_RightFVOutputFileName  = false;
	bool ON_SegmentsOutput		   = false;
	bool ON_PerceptualGroupsOutput = false;
	bool ON_TraceOutput			   = false;
	bool ON_BinaryInput			   = false;
	bool ON_SegmentExtraction	   = true;
	bool ON_PerceptualGrouping	   = true;
	bool ON_StereoProcesssing	   = true;

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
	char LeftSvaOutputFileName[256];
	char RightSvaOutputFileName[256];
	char LeftFVOutputFileName[256];
	char RightFVOutputFileName[256];
//	FILE * LeftImageFile;
//	FILE * RightImageFile;
	FILE * LeftSvaOutputFile;
	FILE * RightSvaOutputFile;
	FILE * LeftFVOutputFile;
	FILE * RightFVOutputFile;

	//Default data initialization
	//Edge detection
	double Sigma           = 1;
	unsigned char HighHyst = 106;
	unsigned char LowHyst  = 85;
	//Segment Extraction
	StructSData SData;
	SData.MaxLinearRegressionError	= 0.5;
	SData.MaxDistance				= 1.5 ; //For segment extraction
	SData.MinNumOfPixels			= 20;
	//Perceptual Grouping
	StructPGData PGData;
	PGData.MaxDistBetwProxSegments			= 30;
	PGData.MaxDistBetwParallelSegments		= 10;
	PGData.MaxAngleDiffBetwParallelSegments = 10;
	PGData.MaxDistBetwColSegments			= 20;
	PGData.k								= 0.7;
	PGData.MaxNoConvexityThreshold          = 5.0;
	PGData.JacobExtension_1					= false;
	PGData.JacobExtension_2					= false;
	PGData.Polarity							= false;
	//Stereo
	double MaxDispi		= 5;
	double MaxDispj		= 10;
	//Misc data
	StructMiscData MiscData;
	MiscData.TraceMessages          = false;


	// Elimino argv[0] que es el propio comando:
	argv++;
	argc--;

	if (!argc) {
		printf("Stereo with Convex Perceptual Grouping (rv.8) (%s)\n",__TIMESTAMP__);
		printf("=============================================\n\n");
		printf("sva -il:<string> [-ir:<string>] [-o:<string>] [-bi]\n"
			   "         [-e0:<float>] [-e1:<int>] [-e2:<int>]\n"
			   "         [-s0:<float>] [-s1:<int>]\n"
			   "         [-p0:<float>] [-p4:<float>] [-p5:<float>] [-p6] [-p7]\n"
			   "         [-di:<float>] [-dj:<float>]\n"
			   "         [-r0] [-r1] [-r2]\n"
			   "         [-d0] [-d1]\n\n");
		printf("input/output parameters\n");
		printf("=======================\n");
		printf("-il Left image file name\n");
		printf("-ir Right image file name\n");
//		printf("-i   Image file name\n");
		printf("-o   Output file name\n");
		printf("-bi  The input images are binary\n");
//		printf("-ofv Feature Vector file name\n");
		printf("\nEdge extraction parameters (Canny detector)\n");
		printf("===========================================\n");
		printf("-e0 Sigma                     [%g]\n",Sigma);
		printf("-e1 Low  hysteresis threshold [%i]\n",LowHyst);
		printf("-e2 High hysteresis threshold [%i]\n",HighHyst);
		printf("\nSegment extraction parameters\n");
		printf("=============================\n");
		printf("-s0 Max Linear regression error      [%g]\n",SData.MaxLinearRegressionError);
		printf("-s1 Max distance from segment        [%g]\n",SData.MaxDistance);
		printf("-s2 Min lentgh of segments in pixels [%i]\n",SData.MinNumOfPixels);
		printf("\nConvex Perceptual Grouping parameters\n");
		printf("==============================\n");
		printf("-p0 Max euclidean distance between near segments      [%g]\n",PGData.MaxDistBetwProxSegments);
//		printf("-p1 Max euclidean distance between parallel segments  [%g]\n",PGData.MaxDistBetwParallelSegments);
//		printf("-p2 Max angle (grades) between parallel segments      [%g]\n",PGData.MaxAngleDiffBetwParallelSegments);
//		printf("-p3 Max euclidean distance between collinear segments [%g]\n",PGData.MaxDistBetwColSegments);
		printf("-p4 Min salience fraction                             [%g]\n",PGData.k);
		printf("-p5 Max threshold of non convexity                    [%g]\n",PGData.MaxNoConvexityThreshold);
		printf("-p6 Switch on the extensions (1) of the algorithm     [%i]\n",PGData.JacobExtension_1);
		printf("-p7 Switch on the extensions (2) of the algorithm     [%i]\n",PGData.JacobExtension_2);
		printf("-p8 Switch on integrity of the polarity               [%i]\n",PGData.Polarity);
		printf("\nStereo parameters\n");
		printf("=================\n");
		printf("-di Max vertical   disparity        [%g]\n",MaxDispi);
		printf("-dj Max horizontal disparity        [%g]\n",MaxDispj);
		printf("\nProcessing parameters\n");
		printf("=====================\n");
		printf("-r0 Only edge detection processing\n");
		printf("-r1 Only segment extraction processing\n");
		printf("-r2 Only perceptual grouping\n");
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
		printf("sva -il:left.bmp -ir:right.bmp -o:myoutput -e0:0.85 -p2:10 -d1\n");
//		printf("convexpg -i:mydir/image.bmp -o:myoutput.sva -ofv:myfvoutput -e0:0.85 -p4:0.75 -d1\n");
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
				printf("Stereo Vision Architecture (rv.8) (%s)\n",__TIMESTAMP__);
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
				strcpy(LeftSvaOutputFileName,Data);
				strcpy(RightSvaOutputFileName,Data);
				strcpy(LeftFVOutputFileName,Data);
				strcpy(RightFVOutputFileName,Data);

				strcat(LeftSvaOutputFileName  ,"_l.sva");
				strcat(RightSvaOutputFileName ,"_r.sva");
				strcat(LeftFVOutputFileName   ,"_l.fv");
				strcat(RightFVOutputFileName  ,"_r.fv");

				if (((LeftSvaOutputFile  = fopen(LeftSvaOutputFileName ,"a"))==NULL) ||
					((RightSvaOutputFile = fopen(RightSvaOutputFileName,"a"))==NULL) ||
					((LeftFVOutputFile   = fopen(LeftFVOutputFileName  ,"a"))==NULL) ||
					((RightFVOutputFile  = fopen(RightFVOutputFileName ,"a"))==NULL) ){
					ErrorCode = 2;
					break;
				}
				else {
					fclose(LeftSvaOutputFile);
					fclose(RightSvaOutputFile);
					fclose(LeftFVOutputFile);
					fclose(RightFVOutputFile);
//					strcpy(LeftSvaOutputFileName,Data);
					OK_LeftSvaOutputFileName  = true;
					OK_RightSvaOutputFileName = true;
					OK_LeftFVOutputFileName   = true;
					OK_RightFVOutputFileName  = true;
				}
			}
			//Feature Vector output data file
//			else if (strcmp(Parameter,"-ofv")==0) {
//				if ((LeftFVOutputFile = fopen(Data,"a"))==NULL){
//					ErrorCode = 2;
//					break;
//				}
//				else {
//					fclose(LeftFVOutputFile);
//					strcpy(LeftFVOutputFileName,Data);
//					OK_LeftFVOutputFileName = true;
//				}
//			}

			else if (strcmp(Parameter,"-bi")==0) {
				ON_BinaryInput = true;
			}

			//Processing parameters
			else if (strcmp(Parameter,"-r0")==0) {
				ON_SegmentExtraction  = false;
				ON_PerceptualGrouping = false;
				ON_StereoProcesssing  = false;
			}
			else if (strcmp(Parameter,"-r1")==0) {
				ON_SegmentExtraction  = true;
				ON_PerceptualGrouping = false;
				ON_StereoProcesssing  = false;
			}
			else if (strcmp(Parameter,"-r2")==0) {
				ON_SegmentExtraction  = true;
				ON_PerceptualGrouping = true;
				ON_StereoProcesssing  = false;
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
				SData.MaxDistance	= strtod(Data,&StopString);
				if (SData.MaxDistance>100)
					SData.MaxDistance = 100;
				if (SData.MaxDistance<0)
					SData.MaxDistance = 0;
			}
			else if (strcmp(Parameter,"-s2")==0) {
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
			else if (strcmp(Parameter,"-p8")==0) {
				PGData.Polarity = true;
			}
			else if (strcmp(Parameter,"-di")==0) {
				MaxDispi	= strtod(Data,&StopString);
				if (MaxDispi<0)
					MaxDispi = 0;
			}
			else if (strcmp(Parameter,"-dj")==0) {
				MaxDispj	= strtod(Data,&StopString);
				if (MaxDispj<0)
					MaxDispj = 0;
			}
			else {
			}

		}


		//Flags test
		if(!ErrorCode){
			if      (!OK_LeftImageFileName)      ErrorCode = 3;
			else if (!OK_RightImageFileName)     ErrorCode = 4;
			else if (!OK_LeftSvaOutputFileName)  ErrorCode = 5;
			else if (!OK_LeftFVOutputFileName)   ErrorCode = 8;
		}

		if (!ErrorCode) {
			printf("\n");
			printf("Stereo with Convex Perceptual Grouping (rv.8) (%s)\n",__TIMESTAMP__);
			printf("=============================================\n\n");
			printf("Processing with following data input: \n");
			printf("  Edge detection (Canny)\n");
			printf("    Sigma                                         -e0:%g\n",Sigma);
			printf("    Low  hysteresis threshold                     -e1:%i\n",LowHyst);
			printf("    High hysteresis threshold                     -e2:%i\n",HighHyst);
			printf("  Segment extraction\n");
			printf("    Max Linear Regression Error                   -s0:%g\n",SData.MaxLinearRegressionError);
			printf("    Max distance from segment                     -s1:%g\n",SData.MaxDistance);
			printf("    Min lentgh of segments (pixels)               -s2:%i\n",SData.MinNumOfPixels);
			printf("  Perceptual Grouping\n");
			printf("    Max distance between near segments            -p0:%g\n",PGData.MaxDistBetwProxSegments);
//			printf("    Max distance between parallel segments        -p1:%g\n",PGData.MaxDistBetwParallelSegments);
//			printf("    Max angle between parallel segments           -p2:%g\n",PGData.MaxAngleDiffBetwParallelSegments);
//			printf("    Max distance between collinear segments       -p3:%g\n",PGData.MaxDistBetwColSegments);
			printf("    Min salience fraction                         -p4:%g\n",PGData.k);
			printf("    Max threshold of non convexity                -p5:%g\n",PGData.MaxNoConvexityThreshold);
			printf("    Switch on the extensions (1) of the algorithm -p6:%i\n",PGData.JacobExtension_1);
			printf("    Switch on the extensions (2) of the algorithm -p7:%i\n",PGData.JacobExtension_2);
			printf("    Switch on integrity of the polarity           -p8:%i\n",PGData.Polarity);
			printf("  Stereo\n");
			printf("    Max vertical disparity                        -di:%g\n",MaxDispi);
			printf("    Max horizontal disparity                      -dj:%g\n",MaxDispj);

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

			if (ON_BinaryInput){
				SI.L.EdgeRetinaMag = SI.L.Retina; //Para saltarme la extracción de bordes
				SI.R.EdgeRetinaMag = SI.R.Retina; //Para saltarme la extracción de bordes
			}
			if (!SI.L.GetErrorCode() && !SI.R.GetErrorCode()){
				if (!ON_BinaryInput){
					SI.L.CannyS(Sigma,LowHyst,HighHyst);
					SI.L.PostCanny();
					SI.L.PostCanny();
					SI.R.CannyS(Sigma,LowHyst,HighHyst);
					SI.R.PostCanny();
					SI.R.PostCanny();
				}
				printf("\nEdge detection finished. Status: %s\n",SI.GetStrError());

				if (ON_PerceptualGrouping || ON_StereoProcesssing || ON_SegmentExtraction) {
					SI.L.SegmentExtractionGAC(SData);
					SI.R.SegmentExtractionGAC(SData);
					printf("Segment extraction finished. Status: %s\n",SI.GetStrError());
				}


				if (ON_PerceptualGrouping || ON_StereoProcesssing) {
					SI.L.ConvexPerceptualGrouping(SData,PGData,MiscData);
					SI.R.ConvexPerceptualGrouping(SData,PGData,MiscData);
					printf("Convex Perceptual grouping error status: %s\n",SI.GetStrError());
				}
				if (ON_StereoProcesssing) {
					SI.CPGMatching(MaxDispi,MaxDispj,MiscData);
					SI.ShowMatches();
				}


				//sleep( (clock_t)1 * CLOCKS_PER_SEC );
				finish = clock();
				duration = (double)(finish - start)/ CLOCKS_PER_SEC;

				FILE * stream = OpenSerialize(LeftSvaOutputFileName) ;
				int count1 = 0;
				count1 += SI.L.Serialize(stream);
				CloseSerialize(stream);

				stream = OpenSerialize(LeftFVOutputFileName) ;
				int count2 = 0;
				count2 += SI.L.FeatureVectorSerialize(stream);
				CloseSerialize(stream);

				stream = OpenSerialize(RightSvaOutputFileName) ;
				int count3 = 0;
				count3 += SI.R.Serialize(stream);
				CloseSerialize(stream);
				
				stream = OpenSerialize(RightFVOutputFileName) ;
				int count4 = 0;
				count4 += SI.R.FeatureVectorSerialize(stream);
				CloseSerialize(stream);

				//Output data
				printf ("Left image\n==========\n");
				printf ("Segments count         : %i \n",SI.L.SegmentRetina.size());
				printf ("Perceptual groups count: %i \n",SI.L.PerceptualGroupRetina.size());
				printf ("Output file: %s (%i bytes)\n",LeftSvaOutputFileName,count1);
				printf ("Feature vector output file: %s (%i bytes)\n",LeftFVOutputFileName,count2);

				printf ("Right image\n===========\n");
				printf ("Segments count         : %i \n",SI.R.SegmentRetina.size());
				printf ("Perceptual groups count: %i \n",SI.R.PerceptualGroupRetina.size());
				printf ("Output file: %s (%i bytes)\n",RightSvaOutputFileName,count3);
				printf ("Feature vector output file: %s (%i bytes)\n",RightFVOutputFileName,count4);

				printf ("\nProcessing time        : %g seconds\n\n",duration);

				if (ON_SegmentsOutput) {
					printf ("Segments (Left image)\n");
					printf ("===========================\n\n");
					SI.L.ConvexSegmentRetina.Show();
					printf ("Segments (Right image)\n");
					printf ("===========================\n\n");
					SI.R.ConvexSegmentRetina.Show();
				}
				if (ON_PerceptualGroupsOutput) {
					printf ("Perceptual groups (Left image)\n");
					printf ("===============================\n\n");
		 			SI.L.ConvexPerceptualGroupRetina.Show(SI.L.ConvexSegmentRetina);
					printf ("Perceptual groups (Right image)\n");
					printf ("===============================\n\n");
		 			SI.R.ConvexPerceptualGroupRetina.Show(SI.R.ConvexSegmentRetina);
				}

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

