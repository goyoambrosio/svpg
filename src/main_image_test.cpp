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

#include <CVL/Image.h>

#include <time.h>
#include <string>                     //From SGI STL. For ios functions. It's like #include <iostream>

using namespace GAC;
using namespace std;

void sleep( clock_t wait );

void main( int argc, char *argv[] )
{
	clock_t start, finish;
	double  duration;

    start = clock(); 

/***********************************************\
 *                   Pixel                     *
\***********************************************/
/*
cout << "***********************************************" << endl << "*                  Pixel                      *" << endl << "***********************************************" << endl;

// Constructor
cout << "Constructor" << endl;
Image::Pixel P1(1,1,234),P2(2,2,128),P3(3,3,96),P4;

// Show,cout
cout << "Show,cout" << endl;
cout << P1 << P2 << P3 << endl;
P1.Show();
P2.Show();
P3.Show();

//Set
cout << "Set" << endl;
P4.Set(4,4,100);
P4.Show();
P3.Set(55);
P3.Show();

//operator==
cout << "operator==" << endl;
cout << (P4==P4) << endl << (P4==P3) << endl;

//operator!=
cout << "operator!=" << endl;
cout << (P4!=P4) << endl << (P4!=P3) << endl;

//operator<
cout << "operator<" << endl;
cout << (P1<P2) << endl << (P2<P1) << endl;



/***********************************************\
 *                PixelVector                  *
\***********************************************/
/*
cout << "***********************************************" << endl << "*               PixelVector                   *" << endl << "***********************************************" << endl;

// Constructor
cout << "Constructor" << endl;
Image::PixelVector PV;

PV.push_back(P1);
PV.push_back(P2);
PV.push_back(P3);
PV.push_back(P4);

PV.Show();


/***********************************************\
 *                   Segment                     *
\***********************************************/
/*
cout << "***********************************************" << endl << "*                  Segment                    *" << endl << "***********************************************" << endl;

// Constructor
cout << "Constructor" << endl;
Image::Segment S1(1,0,3,3,6);
Image::Segment S2(2,Point2D(3,0),Point2D(6,3));
Image::Segment S3(3,0,1,0,5);
Image::Segment S4(4,-4,4,1,-1);
Image::Segment S5(5,1,-2,1,5);
Image::Segment S6(6,0,1,4,1);

// Show,cout
cout << "Show,cout" << endl;
cout << S1 << S2 << S3 << S4 << S5 << S6 << endl;
S1.Show();
S2.Vector2D::Show();
S3.Line::Show();

//operator==
cout << "operator==" << endl; //DirectedLineSegment::operator==
cout << (S4==S4) << endl << (S4==S3) << endl;

//operator!=
cout << "operator!=" << endl; //DirectedLineSegment::operator!=
cout << (S4!=S4) << endl << (S4!=S3) << endl;

//operator<
cout << "operator<" << endl;
cout << (S1<S2) << endl << (S2<S1) << endl;

//EndPointDistance
cout << "EndPointDistance" << endl;
cout << S1.EndPointDistance(S2) << endl; //4.24264 = sqrt(3^2+3^2)

//MidPointDistance
cout << "MidPointDistance" << endl;
cout << S1.MidPointDistance(S2) << endl; //4.24264 = sqrt(3^2+3^2)

//OverlapMod
cout << "OverlapMod" << endl;
cout << S1.OverlapMod(S2) << endl; //4.24264 = sqrt(3^2+3^2)
    
/***********************************************\
 *                SegmentGraph                 *
\***********************************************/
/*
//cout << "***********************************************" << endl << "*               SegmentGraph                  *" << endl << "***********************************************" << endl;
Image::SegmentGraph S;
DoubleMatrix M(4,4);
M.Init();

M[0][1]=5;
M[0][2]=4;
M[1][2]=7;
M[2][3]=2;

M[1][0]=9;
M[2][0]=9;
M[2][1]=9;
M[3][2]=9;

//SetAdjacencyMatrix
//cout << "SetAdjacencyMatrix" << endl;
S.SetAdjacencyMatrix(M);

//Edit
//cout << "Edit" << endl;
S.Edit();

//GetAdjacencyMatrix
//cout << "GetAdjacencyMatrix" << endl;
M=S.GetAdjacencyMatrix();
M.Show();
//cout << M << endl;


/***********************************************\
 *                SegmentVector                *
\***********************************************/
/*
cout << "***********************************************" << endl << "*               SegmentVector                 *" << endl << "***********************************************" << endl;

// Constructor
cout << "Constructor" << endl;
Image::SegmentVector SV;

Image::Segment S1(1,0,3,3,6);
Image::Segment S2(2,Point2D(3,0),Point2D(6,3));
Image::Segment S3(3,0,1,0,5);
Image::Segment S4(4,-4,4,1,-1);
Image::Segment S5(5,1,-2,1,5);
Image::Segment S6(6,0,1,4,1);

SV.push_back(S1);
SV.push_back(S2);
SV.push_back(S3);
SV.push_back(S4);
SV.push_back(S5);
SV.push_back(S6);

// Show,cout
cout << "Show,cout" << endl;
copy(SV.begin(), SV.end(), ostream_iterator<Image::Segment>(cout, ","));
cout << endl;
cout << SV << endl;
SV.Show();


/***********************************************\
 *                   Image                     *
\***********************************************/

cout << "***********************************************" << endl << "*                  Image                      *" << endl << "***********************************************" << endl;

// Constructor
cout << "Constructor" << endl;
Image I1,I2;

/*
UcharMatrix U;
I1.LoadBMP("laura.bmp");
U  = I1;
I1 = U;
cout << U.Width() << "," << U.Height() << endl;
I1.SavePGM("laura.sobel3x3.pgm");
*/
/*
//DoubleMatrix type cast
cout << "DoubleMatrix type cast" << endl;
DoubleMatrix M(2,2);
M(1,1)=500;M(1,2)=250;
M(2,1)=125;M(2,2)= 62;
I1=M;                    //Type casting scales M between 0 and 255 (I1(i,j)=M(i,j)/M.Max()*255)
cout << M << I1 << endl; 
*/
/*
//  Load,Save,LoadBMP,LoadPGM,SavePGM
cout << "Load,Save,LoadBMP,LoadPGM,SavePGM" << endl;
I1.LoadBMP("laura.bmp");
I1.SavePGM("laura.out.pgm");
I2.LoadPGM("laura.out.pgm");
I2.SavePGM("laura.out2.pgm");
I1.Save("laura.raw"); //Para recuperar desde Matlab: I=g_load('laura.raw','uchar');
I2.Load("laura.raw");
I2.SavePGM("laura.out3.pgm");
*/

/*
//Sobel3x3
cout << "Sobel3x3" << endl;
DoubleMatrix M;
I1.LoadBMP("laura.bmp");
I2=I1.Sobel3x3(20.0,M);
I2.SavePGM("laura.sobel3x3.binary.pgm");
I2=I1.Sobel3x3(0.0,M);
I2.SavePGM("laura.sobel3x3.module.pgm");
*/
/*
//Sobel5x5
cout << "Sobel5x5" << endl;
DoubleMatrix M;
I1.LoadBMP("laura.bmp");
I2=I1.Sobel5x5(20.0,M);
I2.SavePGM("laura.sobel5x5.binary.pgm");
I2=I1.Sobel5x5(0.0,M);
I2.SavePGM("laura.sobel5x5.module.pgm");
*/
/*
//Prewitt3x3
cout << "Prewitt3x3" << endl;
DoubleMatrix M;
I1.LoadBMP("laura.bmp");
I2=I1.Prewitt3x3(20.0,M);
I2.SavePGM("laura.prewitt3x3.binary.pgm");
I2=I1.Prewitt3x3(0.0,M);
I2.SavePGM("laura.prewitt3x3.module.pgm");
*/
/*
//Prewitt5x5
cout << "Prewitt5x5" << endl;
DoubleMatrix M;
I1.LoadBMP("laura.bmp");
I2=I1.Prewitt5x5(20.0,M);
I2.SavePGM("laura.prewitt5x5.binary.pgm");
I2=I1.Prewitt5x5(0.0,M);
I2.SavePGM("laura.prewitt5x5.module.pgm");
*/
/*
//FreiChen
cout << "FreiChen" << endl;
DoubleMatrix M;
I1.LoadBMP("laura.bmp");
I2=I1.FreiChen(20.0,M);
I2.SavePGM("laura.freichen.binary.pgm");
I2=I1.FreiChen(0.0,M);
I2.SavePGM("laura.freichen.module.pgm");
*/
/*
//Robert
cout << "Robert" << endl;
DoubleMatrix M;
I1.LoadBMP("laura.bmp");
I2=I1.Robert(20.0,M);
I2.SavePGM("laura.robert.binary.pgm");
I2=I1.Robert(0.0,M);
I2.SavePGM("laura.robert.module.pgm");
*/
/*
//DrogS
cout << "DrogS" << endl;
DoubleMatrix M;
I1.LoadBMP("laura.bmp");
I2=I1.DrogS(1.5,0.5,M);
I2.SavePGM("laura.drogs.binary.pgm");
I2=I1.DrogS(1.5,0.0,M);
I2.SavePGM("laura.drogs.module.pgm");
*/
/*
//DrogW
cout << "DrogW" << endl;
DoubleMatrix M;
I1.LoadBMP("laura.bmp");
I2=I1.DrogW(10.0,0.7,M);
I2.SavePGM("laura.drogw.binary.pgm");
I2=I1.DrogW(10.0,0.0,M);
I2.SavePGM("laura.drogw.module.pgm");
*/
/*
//Lap4
cout << "Lap4" << endl;
I1.LoadBMP("laura.bmp");
I2=I1.Lap4();
I2.SavePGM("laura.Lap4.binary.pgm");
*/
/*
//Lap8
cout << "Lap8" << endl;
I1.LoadBMP("laura.bmp");
I2=I1.Lap8();
I2.SavePGM("laura.Lap8.binary.pgm");
*/
/*
cout << "LogS" << endl;
I1.LoadBMP("laura.bmp");
I2=I1.LogS(1.5);
I2.SavePGM("laura.LogS.binary.pgm");
*/
/*
cout << "LogW" << endl;
I1.LoadBMP("laura.bmp");
I2=I1.LogW(10);
I2.SavePGM("laura.LogW.binary.pgm");
*/
/*
cout << "SLogS" << endl;
I1.LoadBMP("laura.bmp");
I2=I1.SLogS(1.5);
I2.SavePGM("laura.SLogS.binary.pgm");
*/
/*
cout << "SLogW" << endl;
I1.LoadBMP("laura.bmp");
I2=I1.SLogW(10);
I2.SavePGM("laura.SLogW.binary.pgm");
*/
/*
cout << "DogS" << endl;
I1.LoadBMP("laura.bmp");
I2=I1.DogS(1.5);
I2.SavePGM("laura.DogS.binary.pgm");
*/
/*
cout << "DogW" << endl;
I1.LoadBMP("laura.bmp");
I2=I1.DogW(10);
I2.SavePGM("laura.DogW.binary.pgm");
*/
/*
// CannyS
cout << "CannyS" << endl;
I1.LoadBMP("laura.bmp");
I2 = I1.CannyS(1.5,100,100);
I2.SavePGM("laura.cannys.binary.pgm");
*/
/*
// Cannyw
cout << "CannyW" << endl;
I1.LoadBMP("laura.bmp");
I2 = I1.CannyW(5,100,100);
I2.SavePGM("laura.cannyw.binary.pgm");
*/
/*
cout << "GaussS" << endl;
I1.LoadBMP("laura.bmp");
I2 = I1.GaussS(1.5);
I2.SavePGM("laura.GaussS.pgm");
*/
/*
cout << "GaussW" << endl;
I1.LoadBMP("laura.bmp");
I2 = I1.GaussW(30);
I2.SavePGM("laura.GaussW.pgm");
*/


cout << "GaussWipl" << endl;
I1.LoadBMP("laura.bmp");
I2 = I1.GaussWipl(30);
I2.SavePGM("laura.GaussWipl.pgm");


/*
//SegmentExtraction
cout << "SegmentExtraction" << endl;
Image::SegmentVector SV;
I1.LoadBMP("laura.bmp");
start = clock(); 
I2 = I1.CannyS(1.5,100,100);
SV=I2.SegmentExtraction(1.5,30);
printf("SV.size() = %i\n",SV.size());
*/



// ImgSegment Class


// EndPointDistanceGraph
//
//	GrayImage I,J;
//	ImgSegmentVector S;
//	AffGraph<pImgSegment> EndPointDistanceGraph;
//	AffGraphw<pImgSegment> AGaux;
//	leda_node u;
//	I.LoadBMP("d:\\goyo\\mio\\svawin32\\temp\\laura.bmp");
//	J = I.CannyS(1,100,100);
//	S = J.ImgSegmentExtraction(1.5,30);
//	EndPointDistanceGraph = S.EndPointDistanceGraph();
//	printf("S.size() = %i\n",S.size());
//	AGaux = EndPointDistanceGraph;
//	AGaux.Edit(0);
//	forall_nodes(u,EndPointDistanceGraph) printf("u->Label:%i\n",EndPointDistanceGraph.inf(u)->Label);

// EndPointDistanceMatrix
//
//	GrayImage I,J;
//	ImgSegmentVector S;
//	DoubleMatrix EndPointDistanceMatrix;
//	AffGraphw<pImgSegment> AGaux;
//	leda_node u;
//	I.LoadBMP("d:\\goyo\\mio\\svawin32\\temp\\laura.bmp");
//	J = I.CannyS(1,100,100);
//	S = J.ImgSegmentExtraction(1.5,30);
//	EndPointDistanceMatrix = S.EndPointDistanceMatrix();
//	printf("S.size() = %i\n",S.size());
//	AGaux.SetAdjacencyMatrix(EndPointDistanceMatrix);
//	AGaux.Edit(0);


// MidPointDistanceGraph
//
//	GrayImage I,J;
//	ImgSegmentVector S;
//	AffGraph<pImgSegment> MidPointDistanceGraph;
//	AffGraphw<pImgSegment> AGaux;
//	leda_node u;
//	I.LoadBMP("d:\\goyo\\mio\\svawin32\\temp\\laura.bmp");
//	J = I.CannyS(1,100,100);
//	S = J.ImgSegmentExtraction(1.5,30);
//	MidPointDistanceGraph = S.MidPointDistanceGraph();
//	printf("S.size() = %i\n",S.size());
//	AGaux = MidPointDistanceGraph;
//	AGaux.Edit(0);
//	forall_nodes(u,MidPointDistanceGraph) printf("u->Label:%i\n",MidPointDistanceGraph.inf(u)->Label);

// MidPointDistanceMatrix
//
//	GrayImage I,J;
//	ImgSegmentVector S;
//	DoubleMatrix MidPointDistanceMatrix;
//	AffGraphw<pImgSegment> AGaux;
//	leda_node u;
//	I.LoadBMP("d:\\goyo\\mio\\svawin32\\temp\\laura.bmp");
//	J = I.CannyS(1,100,100);
//	S = J.ImgSegmentExtraction(1.5,30);
//	MidPointDistanceMatrix = S.MidPointDistanceMatrix();
//	printf("S.size() = %i\n",S.size());
//	AGaux.SetAdjacencyMatrix(MidPointDistanceMatrix);
//	AGaux.Edit(0);

// ShortAngleGraph
//
//	GrayImage I,J;
//	ImgSegmentVector S;
//	AffGraph<pImgSegment> ShortAngleGraph;
//	AffGraphw<pImgSegment> AGaux;
//	leda_node u;
//	I.LoadBMP("d:\\goyo\\mio\\svawin32\\temp\\laura.bmp");
//	J = I.CannyS(1,100,100);
//	S = J.ImgSegmentExtraction(1.5,30);
//	ShortAngleGraph = S.ShortAngleGraph();
//	printf("S.size() = %i\n",S.size());
//	AGaux = ShortAngleGraph;
//	AGaux.Edit(0);
//	forall_nodes(u,ShortAngleGraph) printf("u->Label:%i\n",ShortAngleGraph.inf(u)->Label);

// ShortAngleMatrix
//
//	GrayImage I,J;
//	ImgSegmentVector S;
//	DoubleMatrix ShortAngleMatrix;
//	AffGraphw<pImgSegment> AGaux;
//	leda_node u;
//	I.LoadBMP("d:\\goyo\\mio\\svawin32\\temp\\laura.bmp");
//	J = I.CannyS(1,100,100);
//	S = J.ImgSegmentExtraction(1.5,30);
//	ShortAngleMatrix = S.ShortAngleMatrix();
//	printf("S.size() = %i\n",S.size());
//	AGaux.SetAdjacencyMatrix(ShortAngleMatrix);
//	AGaux.Edit(0);

// OverlapModGraph
//
//	GrayImage I,J;
//	ImgSegmentVector S;
//	AffGraph<pImgSegment> OverlapModGraph;
//	AffGraphw<pImgSegment> AGaux;
//	leda_node u;
//	I.LoadBMP("d:\\goyo\\mio\\svawin32\\temp\\laura.bmp");
//	J = I.CannyS(1,100,100);
//	S = J.ImgSegmentExtraction(1.5,30);
//	OverlapModGraph = S.OverlapModGraph();
//	printf("S.size() = %i\n",S.size());
//	AGaux = OverlapModGraph;
//	AGaux.Edit(0);
//	forall_nodes(u,OverlapModGraph) printf("u->Label:%i\n",OverlapModGraph.inf(u)->Label);

// OverlapModMatrix
//
//	GrayImage I,J;
//	ImgSegmentVector S;
//	DoubleMatrix OverlapModMatrix;
//	AffGraphw<pImgSegment> AGaux;
//	leda_node u;
//	I.LoadBMP("d:\\goyo\\mio\\svawin32\\temp\\laura.bmp");
//	J = I.CannyS(1,100,100);
//	S = J.ImgSegmentExtraction(1.5,30);
//	OverlapModMatrix = S.OverlapModMatrix();
//	printf("S.size() = %i\n",S.size());
//	AGaux.SetAdjacencyMatrix(OverlapModMatrix);
//	AGaux.Edit(0);

// ProximityGraph
//
//	GrayImage I,J;
//	ImgSegmentVector S;
//	AffGraph<pImgSegment> AffProximity;
//	leda_node u;
//1	I.LoadBMP("d:\\goyo\\mio\\svawin32\\temp\\laura.bmp");
//1	J = I.CannyS(1,100,100);
//1	S = J.ImgSegmentExtraction(1.5,30);
//2	J.LoadPGM("d:\\goyo\\mio\\svawin32\\temp\\af1.pgm");
//2	S = J.ImgSegmentExtraction(1.5,5);
//	S.ProximityGraph(AffProximity,100);
//	printf("S.size() = %i\n",S.size());
//	AffProximity.Edit();
//	forall_nodes(u,AffProximity) printf("u->Label:%i\n",AffProximity.inf(u)->Label);

// ParallelAffGraph
//
//	GrayImage I,J;
//	ImgSegmentVector S;
//	AffGraph<pImgSegment> AffParallel;
//	leda_node u;
//	I.LoadBMP("d:\\goyo\\mio\\svawin32\\temp\\laura.bmp");
//	J = I.CannyS(1,100,100);
//	S = J.ImgSegmentExtraction(1.5,30);
//	AffParallel = S.ParallelAffGraph(10,5*ONE_GRADE_IN_RAD);
//	printf("S.size() = %i\n",S.size());
//	AffParallel.Edit();
//	forall_nodes(u,AffParallel) printf("u->Label:%i\n",AffParallel.inf(u)->Label);

// ParallelGraph
//
//	GrayImage I,J;
//	ImgSegmentVector S;
//	AffGraph<pImgSegment> DistanceGraph, AngleGraph, OverlapGraph;
//	leda_node u;
//	I.LoadPGM("d:\\goyo\\mio\\svawin32\\temp\\telephonel.pgm");
//	J = I.CannyS(1,100,100);
//	S = J.ImgSegmentExtraction(1.5,30);
//	S.ParallelGraph(DistanceGraph,AngleGraph,OverlapGraph,10,0,5*ONE_GRADE_IN_RAD);
//	printf("S.size() = %i\n",S.size());
//	DistanceGraph.Edit();
//	forall_nodes(u,DistanceGraph) printf("u->Label:%i\n",DistanceGraph.inf(u)->Label);
//	AngleGraph.Edit();
//	forall_nodes(u,AngleGraph) printf("u->Label:%i\n",AngleGraph.inf(u)->Label);
//	OverlapGraph.Edit();
//	forall_nodes(u,OverlapGraph) printf("u->Label:%i\n",OverlapGraph.inf(u)->Label);


// CollinearAffGraph
//
//	GrayImage I,J;
//	ImgSegmentVector S;
//	AffGraph<pImgSegment> AffCollinear;
//	leda_node u;
//	I.LoadPGM("d:\\goyo\\mio\\svawin32\\temp\\telephonel.pgm");
//	J = I.CannyS(2,100,100);
//	S = J.ImgSegmentExtraction(1.5,20);
//	AffCollinear = S.CollinearAffGraph(10,5*ONE_GRADE_IN_RAD,5.0);
//	printf("S.size() = %i\n",S.size());
//	AffCollinear.Edit();
//	forall_nodes(u,AffCollinear) printf("u->Label:%i\n",AffCollinear.inf(u)->Label);

// CollinearGraph
//
//	GrayImage I,J;
//	ImgSegmentVector S;
//	AffGraph<pImgSegment> AffCollinear;
//	leda_node u;
//	I.LoadPGM("d:\\goyo\\mio\\svawin32\\temp\\telephonel.pgm");
//	J = I.CannyS(2,100,100);
//	S = J.ImgSegmentExtraction(1.5,20);
//	S.CollinearGraph(AffCollinear,10,5*ONE_GRADE_IN_RAD,5.0);
//	printf("S.size() = %i\n",S.size());
//	AffCollinear.Edit();
//	forall_nodes(u,AffCollinear) printf("u->Label:%i\n",AffCollinear.inf(u)->Label);

// ConvexityGraph
//
//	GrayImage I,J;
//	ImgSegmentVector S;
//	AffGraph<pImgSegment> DistanceGraph, ClockwiseAngleGraph, CircularityGraph;
//	leda_node u;
////	I.LoadBMP("d:\\goyo\\mio\\svawin32\\temp\\laura.bmp");
//	I.LoadPGM("d:\\goyo\\mio\\svawin32\\temp\\telephonel.pgm");
//	J = I.CannyS(1,100,100);
////	S = J.ImgSegmentExtraction(1.5,30);
//	J.LoadPGM("d:\\goyo\\mio\\svawin32\\temp\\af1.pgm");
//	S = J.ImgSegmentExtraction(1.5,5);
//	S.ConvexGraph(DistanceGraph,ClockwiseAngleGraph,CircularityGraph,100,3.0);
//	printf("S.size() = %i\n",S.size());
//	DistanceGraph.Edit(0);
//	forall_nodes(u,DistanceGraph) printf("u->Label:%i\n",DistanceGraph.inf(u)->Label);

//	ClockwiseAngleGraph.Edit(0);
//	forall_nodes(u,ClockwiseAngleGraph) printf("u->Label:%i\n",ClockwiseAngleGraph.inf(u)->Label);
//	CircularityGraph.Edit(0);
//	forall_nodes(u,CircularityGraph) printf("u->Label:%i\n",CircularityGraph.inf(u)->Label);

// ParallelGrouping
//	GrayImage I,J;
//	ImgSegmentVector S;
//	AffGraphw<pImgSegment> AffParallel;
//	leda_node u;
//	map<Label,PerceptualGroup> PGMap;
//	map<Label,PerceptualGroup>::iterator PGMit;
//	I.LoadPGM("d:\\goyo\\mio\\svawin32\\temp\\telephonel.pgm");
//	J = I.CannyS(1,100,100);
//	S = J.ImgSegmentExtraction(1.5,10);
//	PGMap = S.ParallelGrouping(10,5*ONE_GRADE_IN_RAD);
//	for (PGMit = PGMap.begin(); PGMit != PGMap.end(); PGMit++)
//	{
//		printf("LabelMap: %i\n",(*PGMit).first);
//		(*PGMit).second.Show();
//	}


/*
ImgSegment S1,S2;
double Circularity;

S1.Set(Point(0,0),Point(0,1));
S2.Set(Point(0,1),Point(1,1));
printf("S1.Mod():%.30g,S2.Mod():%.30g\n",S1.Mod(),S2.Mod());
printf("fabs(S1.Vect(S2)):%.30g\n",fabs(S1.Vect(S2)));
Circularity = pow(2.0*S1.Mod()+2.0*S2.Mod(),2.0)/fabs(S1.Vect(S2)); //perimetro^2/area
printf("Circularity:%.30g\n",Circularity);
*/





// ImgSegmentExtraction
//
//	GrayImage I,J;
//	ImgSegmentVector S;
//	AffGraph<pImgSegment> AffProximity,AffParallel;
//	I.LoadBMP("d:\\goyo\\mio\\svawin32\\temp\\laura.bmp");
//	J = I.CannyS(1,100,100);
//	S = J.ImgSegmentExtraction(1.5,30);
//	printf("S.size() = %i\n",S.size());

// ExtractSegmentsFromTJunctions
//
//	GrayImage I,J;
//	ImgSegmentVector SV1,SV2;
//	J.LoadPGM("d:\\goyo\\mio\\svawin32\\temp\\convex1.pgm");
//	SV1 = J.ImgSegmentExtraction(1.5,10);
//	SV2 = SV1.ExtractSegmentsFromTJunctions(10,30,3.0,true,true,true);
//	printf("SV1.size() = %i\n",SV1.size());
//	printf("SV2.size() = %i\n",SV2.size());

// TwoOrientation
//
//	GrayImage I,J;
//	ImgSegmentVector SV1,SV2;
//	J.LoadPGM("d:\\goyo\\mio\\svawin32\\temp\\convex1.pgm");
//	SV1 = J.ImgSegmentExtraction(1.5,10);
//	SV2 = SV1.TwoOrientation();
//	printf("SV1.size() = %i\n",SV1.size());
//	printf("SV2.size() = %i\n",SV2.size());




	//sleep( (clock_t)1 * CLOCKS_PER_SEC );
	finish = clock();
	duration = (double)(finish - start)/ CLOCKS_PER_SEC;
//	cout << start << "\t" << finish << "\t" << duration  << "\n";
	printf("%i\t%i\t%.30g\n",start,finish,duration);

}

/* Pauses for a specified number of milliseconds. */
void sleep( clock_t wait ){
   clock_t goal;
   goal = wait + clock();
   while( goal > clock() )
	   ;
}

// Para obtener el nombre del tipo
//	const type_info& MiTipo = typeid(LoQueSea);
//	cout << MiTipo.name();
