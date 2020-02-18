/****
  SoftVision. Software for Computer Vision

  Gregorio Ambrosio Cestero (goyo@computer.org)
  System Engineering and Automation Department 
  University of Malaga. Spain                   

  $RCSfile: main.cpp,v $
  $Revision: 1.1 $
  $Date: 2000/01/21 13:04:42 $
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


// The debugger can't handle symbols more than 255 characters long.
// STL often creates symbols longer than that.
// When symbols are longer than 255 characters, the warning is disabled.
#pragma warning(disable:4786)

//#include <CVL/Globals.h>
#include <CV.h>
#include <OPENCV/Image.h>
#include <OPENCV/macros.inc>
#include <OPENCV/cookroom.h>


#include <time.h>
#include <string>                     //From SGI STL. For ios functions. It's like #include <iostream>
#include <math.h>

//using namespace GAC;
using namespace std;

void sleep( clock_t wait );


char* getUsageStr( char* msg ) {
   sprintf( msg, "%s", "blob [-an] [-tn] [-fname] [-oname]\n"
	  "   -xn origin in x axis (UTM)\n"
	  "   -yn origin in y axis (UTM)\n"
      "   -an area threshold in pixels, n is a positive number (default: 0)\n"
      "   -tn intensity threshold, n is a number between 0 and 255 (default: 0)\n"
      "   -fname name is bmp-file name (default: test.bmp)\n" 
      "   -oname name is output file name (default: out)\n" 
	  " example: blob -x355447 -y82264 -a3 -t10 -ftest.bmp -oout.txt\n"
	);
   return msg;
}

int usage() {
   char msg[1024];
   getUsageStr( msg );
   printf ("%s",msg);
   return 1;
}

void main( int argc, char *argv[] )
{
	clock_t start, finish;
	double  duration;

    start = clock(); 

/***********************************************\
 *                   Test                      *
\***********************************************/

   /// is there request to print usage message 
   if( isKeyUsed( argc, argv, "?" )) usage();
   else exit();

   /// bmp file name
   char filename[128] = "test.bmp";
   getStrArg( argc, argv, "f", filename );

   /// output file name
   char outfilename[128] = "out";
   getStrArg( argc, argv, "o", outfilename );

      /// intensity threshold
   int intensityThreshold = 0;
   getIntArg( argc, argv, "t", &intensityThreshold );

      /// area threshold
   int areaThreshold = 0;
   getIntArg( argc, argv, "a", &areaThreshold );

	  /// x coordinate in UTM
   int oxUtm = 0;
   getIntArg( argc, argv, "x", &oxUtm );

	  /// y coordinate in UTM
   int oyUtm = 0;
   getIntArg( argc, argv, "y", &oyUtm );

   double xUtm;
   double yUtm;

	CImage *I;
	CImage *J;

	I=new CImage;
	J=new CImage;

	FILE *stream;
	FILE *geostream;
	FILE *cemistream;

	char auxchar[128];

	strcpy(auxchar,outfilename);
	strcat(auxchar,".txt");
	stream		= fopen(auxchar,"w");

	strcpy(auxchar,outfilename);
	strcat(auxchar,"_g.txt");
	geostream	= fopen(auxchar,"w");

	strcpy(auxchar,outfilename);
	strcat(auxchar,"_c.txt");
	cemistream	= fopen(auxchar,"w");

	if (I->Load(filename,0) && 
		intensityThreshold >= 0  && 
		intensityThreshold <= 255 &&
		areaThreshold >= 0  &&
		stream && geostream && cemistream
		) {
		
		J->Create(I->Width(),I->Height(),8);

		//printf("Rows: %i, Cols: %i\n",I->Height(),I->Width());

		cvThreshold( I->GetImage(), J->GetImage(), intensityThreshold, 255.0, CV_THRESH_BINARY);
		//iplThreshold( I->GetImage(), J->GetImage(), intensityThreshold); //IPL equivalent function

		//J->Save("out.bmp");

		int				 NumContours;
		CvMemStorage	*mem = cvCreateMemStorage();
		CvSeq			*seq;

		NumContours=cvFindContours(J->GetImage(), mem, &seq, sizeof(CvContour), CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);

		printf("Contours: %i\n",NumContours);

		double area;
		double x, y;
		CvMoments* moments = new CvMoments;


		for( CvSeq* c = seq; c != 0; c = c->h_next )	{
			area = -ceil(cvContourArea(c));

			if (area >= areaThreshold){			
				cvContourMoments(c, moments);
				x = cvGetSpatialMoment(moments, 1, 0) / area;
				y = cvGetSpatialMoment(moments, 0, 1) / area;

				xUtm = oxUtm + x*5.0;
				yUtm = oyUtm - y*5.0;
				
				fprintf(stream, "area (pixels): %.30g \tx: %.3f \ty: %.3f \tx(UTM): %.3f \ty(UTM): %.3f\n",area,x,y,xUtm,yUtm);
				fprintf(geostream, "%.3f \t%.3f\n",x,y);
				fprintf(cemistream, "%.3f \t%.3f \t%.3f\n",area*25.0,xUtm,yUtm);
				//printf("area (pixels): %.3f \tx: %.3f \ty: %.3f \tx(UTM): %.3f \ty(UTM): %.3f\n",area,x,y,xUtm,yUtm);
			}
		}


		// Memory clean
		J->Destroy();
		delete J;
		cvReleaseMemStorage(&mem);
		delete moments;
	}
	else {
		I->Destroy();
		delete I;

		usage();
	}

	fclose (stream);
	fclose (geostream);
	fclose (cemistream);


	//sleep( (clock_t)1 * CLOCKS_PER_SEC );
	finish = clock();
	duration = (double)(finish - start)/ CLOCKS_PER_SEC;
//	printf("%i\t%i\t%.30g\n",start,finish,duration);
	printf("Execution time: %.30g seconds\n",duration);

}

/* Pauses for a specified number of milliseconds. */
void sleep( clock_t wait ){
   clock_t goal;
   goal = wait + clock();
   while( goal > clock() )
	   ;
}
