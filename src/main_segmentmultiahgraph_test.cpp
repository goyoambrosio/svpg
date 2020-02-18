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

#include <CVL/SegmentMultiAHgraph.h>

#include <stdio.h>
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
 *             SegmentMultiAHgraph             *
\***********************************************/

cout << "***********************************************" << endl << "*              SegmentMultiAHgraph            *" << endl << "***********************************************" << endl;

// Constructor
cout << "Constructor" << endl;
SegmentMultiAHgraph G;

// setL0
cout << "setL0" << endl;
Image I1;
Image::SegmentVector SV;
//I1.LoadPGM("all.pgm");
//I1.LoadPGM("col.pgm");
//I1.LoadPGM("par.pgm");
//I1.LoadPGM("convex.pgm");;SV=I1.SegmentExtraction(1.5,5);
I1.LoadPGM("convex1.pgm");SV=I1.SegmentExtraction(1.5,5);
printf("SV.size() = %i\n",SV.size());
//SV.Show();

SegmentMultiAHgraphNodeAnnotation::ParallelParametersStruct  pPar;
SegmentMultiAHgraphNodeAnnotation::CollinearParametersStruct pCol;
SegmentMultiAHgraphNodeAnnotation::ConvexParametersStruct    pConv;
SegmentMultiAHgraphNodeAnnotation::ProximalParametersStruct  pProx;


//Parallel parameters

//Level 0
    pPar.d0     = 20.0;
    pPar.theta0 = PI/2.0;
    pPar.delta  = 0.5;
    G.d_parallelParameters.insert(SegmentMultiAHgraphNodeAnnotation::ParallelParameters(0,pPar)); 
/*
    pPar.d0     = 10.0;
    pPar.theta0 = PI/4.0;
    pPar.delta  = 0.5;
    G.d_parallelParameters.insert(SegmentMultiAHgraphNodeAnnotation::ParallelParameters(0,pPar)); 

//Level 1
    pPar.d0     = 40.0;
    pPar.theta0 = PI/2.0;
    pPar.delta  = 0.5;
    G.d_parallelParameters.insert(SegmentMultiAHgraphNodeAnnotation::ParallelParameters(1,pPar)); 
    pPar.d0     = 30.0;
    pPar.theta0 = PI/4.0;
    pPar.delta  = 0.5;
    G.d_parallelParameters.insert(SegmentMultiAHgraphNodeAnnotation::ParallelParameters(1,pPar)); 
*/

//Collinear parameters

//Level 0
    pCol.d0     = 20.0;
    pCol.theta0 = PI/10.0; //Cuanto más grande sea el denominador mayor discrimina por no ser colineal
                           //Los valores buenos parecen estar entre PI/8 y PI/10
    pCol.delta  = 0.5;
    G.d_collinearParameters.insert(SegmentMultiAHgraphNodeAnnotation::CollinearParameters(0,pCol)); 

//Convex parameters

//Level 0
    pConv.d0     = 20.0;
    pConv.theta0 = PI/2.0;
    pConv.delta  = 0.5;
    G.d_convexParameters.insert(SegmentMultiAHgraphNodeAnnotation::ConvexParameters(0,pConv)); 

//Proximity parameters

//Level 0
    pProx.d0     = 20.0;
    pProx.theta0 = PI/2.0;
    pProx.delta  = 0.5;
    G.d_proximalParameters.insert(SegmentMultiAHgraphNodeAnnotation::ProximalParameters(0,pProx));

G.setL0(SV);

//G.addL0(SV,pPar,pCol,pConv,pProx);
//G.generateAbstraction();

// segmentWindow
/*
cout << "segmentWindow" << endl;
G.segmentWindow();
*/


// edit
cout << "edit" << endl;
G.edit();






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
