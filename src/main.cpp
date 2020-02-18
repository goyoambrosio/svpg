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

#include <time.h>
//#include <stdio.h>
//#include <stdlib.h>
#include <typeinfo.h>

#include "GrayImage.h"
#include "AffGraph.h"
#include "AffGraphw.h"
#include "ImgSegment.h"

using namespace GAC;

void sleep( clock_t wait );

void main( int argc, char *argv[] )
{
	clock_t start, finish;
	double  duration;

    start = clock(); 
	
// Load,Save,LoadBMP,LoadPGM,SavePGM
//
//	GrayImage I;
//	I.Resize(3,4);
//	I[0][0]=4;I[0][1]=5;I[0][2]=6;I[0][3]=7;
//	I[1][0]=4;I[1][1]=5;I[1][2]=6;I[1][3]=7;
//	I[2][0]=4;I[2][1]=5;I[2][2]=6;I[2][3]=7;

//	I.LoadBMP("d:\\goyo\\mio\\svawin32\\temp\\laura.bmp");
//	I.Load("d:\\goyo\\mio\\svawin32\\temp\\gray.raw");

//	I.SavePGM("d:\\goyo\\mio\\svawin32\\temp\\laura.pgm");
//	I.LoadPGM("d:\\goyo\\mio\\svawin32\\temp\\gray.pgm");
//	I.Save("d:\\goyo\\mio\\svawin32\\temp\\gray.raw");
//	I.Load("d:\\goyo\\mio\\svawin32\\temp\\gray1.raw");
//	cout << I;

// CannyS,CannyW,PostCanny,Hysteresis
//
//	GrayImage I,J;
//	I.LoadBMP("d:\\goyo\\mio\\svawin32\\temp\\laura.bmp");
//	J = I.CannyS(1,100,100);
//	J.SavePGM("d:\\goyo\\mio\\svawin32\\temp\\canny.pgm");

// SegmentExtraction
//
//	GrayImage I,J;
//	ImgSegmentVector S;
//	I.LoadBMP("d:\\goyo\\mio\\svawin32\\temp\\laura.bmp");
//	J = I.CannyS(1,100,100);
//	S = J.ImgSegmentExtraction(1.5,30);
//	printf("S.size() = %i\n",S.size());

// ImgSegment Class

//EndPointDistance,MidPointDistance
//	ImgSegment A(1,1,3,1),B(2,2,2,4);
//	printf("A.EndPointDistance(B) = %.5g\n",A.EndPointDistance(B));
//	printf("A.MidPointDistance(B) = %.5g\n",A.MidPointDistance(B));

//OverlapMod
//	ImgSegment A(1,2,1,4),B(2,3,2,5);
//	ImgSegment A(2,1,4,1),B(3,2,5,2);
//	ImgSegment A(2,1,4,1),B(3,1,5,1);
//	ImgSegment A(1,1,3,3),B(2,1,4,3);
//	printf("A.OverlapMod(B) = %.5g\n",A.OverlapMod(B));
//	printf("B.OverlapMod(A) = %.5g\n",B.OverlapMod(A));

//ShortAngle
//	ImgSegment A(0,0,0,1),B(1,-1,0,0);
//	ImgSegment A(0,0,0,1),B(0,0,1,-1);
//	ImgSegment A(0,0,0,1),B(0,-1,0,0);
//	printf("A.ShortAngle(B) = %.5g\n",A.ShortAngle(B));
//	printf("A.Angle(B) = %.5g\n",A.Angle(B));
//	printf("A.OrderedAngle(B) = %.5g\n",A.OrderedAngle(B));
//	printf("A.ClockwiseAngle(B) = %.5g\n",A.ClockwiseAngle(B));


// ImgSegmentVector Class

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
	GrayImage I,J;
	ImgSegmentVector S;
	AffGraphw<pImgSegment> AffParallel;
	leda_node u;
	map<Label,PerceptualGroup> PGMap;
	map<Label,PerceptualGroup>::iterator PGMit;
	I.LoadPGM("d:\\goyo\\mio\\svawin32\\temp\\telephonel.pgm");
	J = I.CannyS(1,100,100);
	S = J.ImgSegmentExtraction(1.5,10);
	PGMap = S.ParallelGrouping(10,5*ONE_GRADE_IN_RAD);
	for (PGMit = PGMap.begin(); PGMit != PGMap.end(); PGMit++)
	{
		printf("LabelMap: %i\n",(*PGMit).first);
		(*PGMit).second.Show();
	}


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



/*************************************************************************\
 *                       Stereo Vision Architecture                      *
\*************************************************************************/
/*

	printf("*************************\nStereo Vision Architecture\n*************************\n");

	Image IM;
	UcharMatrix AUX;
//	IM.Retina.Load("d:\\users\\goyo\\desarrollo\\svawin32\\datos\\esc256.mat");
//	IM.LoadMAT("d:\\mio\\svawin32\\datos\\esc256.mat");
	IM.LoadPGM("c:\\goyo\\mio\\svawin32\\datos\\pgm\\stereo\\cartl.pgm");
//	IM.LoadBMP("c:\\goyo\\mio\\svawin32\\datos\\pgm\\stereo\\housel.pgm");
//	IM.EdgeRetinaMag = IM.Retina; //Para saltarme la extracción de bordes

//FILE * stream = OpenSerialize("d:\\mio\\svawin32\\datos\\02-256l.sva") ;
//int count = 0;
//count += IM.Serialize(stream);
//printf("count: %i\n",count);
//CloseSerialize(stream);


 	IM.CannyS(1,85,106);
	IM.PostCanny();
	IM.PostCanny();

//	IM.DogW(5);
//	IM.EdgeRetinaMag.Save("d:\\users\\goyo\\desarrollo\\svawin32\\datos\\mag.mat");


	StructMiscData MiscData;
	MiscData.TraceMessages          = true;


//  //Para blocks.sva
//	StructSData SData;
//	SData.MaxLinearRegressionError	= 0.5;
//	SData.MinNumOfPixels			= 20;

//	StructPGData PGData;
//	PGData.MaxDistBetwProxSegments			= 20;
//	PGData.MaxDistBetwParallelSegments		= 10;
//	PGData.MaxAngleDiffBetwParallelSegments = 10;
//	PGData.MaxDistBetwColSegments			= 10;
//	PGData.k								= 0.7;
//	PGData.MaxNoConvexityThreshold          = 15.0;
//	PGData.JacobExtension_1					= false;
//	PGData.JacobExtension_2					= true;


	StructSData SData;
	SData.MaxLinearRegressionError	= 0.5;
	SData.MinNumOfPixels			= 15;
	SData.MaxDistance				= 1.5 ; //Para la extraccion de segmentos

	StructPGData PGData;
	PGData.MaxDistBetwProxSegments			= 10;

	PGData.MaxDistBetwParallelSegments		= 5;
	PGData.MaxAngleDiffBetwParallelSegments = 5*ONE_GRADE_IN_RAD;

	PGData.MaxDistBetwColSegments			= 20;
	PGData.MaxParDistBetwColSegments		= 3;
	PGData.MaxAngleBetwCollinearSegments	= 5*ONE_GRADE_IN_RAD;

	PGData.k								= 0.75;
	PGData.MaxNoConvexityThreshold          = 5;
	PGData.JacobExtension_1					= false;
	PGData.JacobExtension_2					= false;
	PGData.Polarity							= false;


//	IM.Segmentation(SData);
	IM.SegmentExtractionGAC(SData);
printf("Extracción de segmentos terminada\n");
printf("IM.SegmentRetina.size() : %i\n",IM.SegmentRetina.size());
//	IM.SegmentRetina.Show();


////// Gestalt Perceptual Grouping
//	IM.PerceptualGrouping(PGData,MiscData,false,false,true);
//printf("IM.PerceptualGroupRetina.size() : %i\n",IM.PerceptualGroupRetina.size());
// 	IM.PerceptualGroupRetina.Show();


////// Convex Perceptual Grouping
	IM.ConvexPerceptualGrouping(SData,PGData,MiscData);
printf("IM.ConvexPerceptualGroupRetina.size() : %i\n",IM.ConvexPerceptualGroupRetina.size());
 	IM.ConvexPerceptualGroupRetina.Show(IM.ConvexSegmentRetina);

//  IM.ConvexSegmentRetina = IM.SegmentRetina; //Para que funcione bien la función Image::Serialize
//	IM.ConvexSegmentRetina.Show();

	FILE * stream = OpenSerialize("c:\\goyo\\mio\\svawin32\\datos\\cart.sva") ;
	int count = 0;
	count += IM.Serialize(stream);
printf("count: %i\n",count);
	CloseSerialize(stream);

	stream = OpenSerialize("c:\\goyo\\mio\\svawin32\\datos\\cart.fv") ;
	count = 0;
	count += IM.FeatureVectorSerialize(stream);
printf("count: %i\n",count);
	CloseSerialize(stream);


*/


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
