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

#include <CVL/CompVector.h>

#include <iostream>
#include <time.h>

using namespace GAC;
using namespace std;

void sleep( clock_t wait );

void main( int argc, char *argv[] )
{
	clock_t start, finish;
	double  duration;

    start = clock();
    
/***********************************************\
 *                CompVector                   *
\***********************************************/

// Constructor
cout << "Constructor" << endl;
CompVector V1(2,3), V2(6,5),V3,V4,Vtemp;
V3.Set(8,7);

//Show
cout << endl << "Show" << endl;
V1.Show();V2.Show();V3.Show();V4.Show();

//Operator <<
cout << endl << "Operator <<" << endl;
cout << V1 << endl;

//Operator ==
cout << endl << "Operator ==" << endl;
cout << (V1==V2) << endl << (V1==V1) << endl;

//Operator <
cout << endl << "Operator <" << endl;
cout << (V1<V2) << endl << (V1<V1) << endl;

//Operator *
cout << endl << "Operator *" << endl;
cout << (V1*3) << endl;

//Operator *
cout << endl << "Operator *" << endl;
cout << (V1*V2) << endl;

//Operator +
cout << endl << "Operator +" << endl;
Vtemp = (V1+V2);
cout << Vtemp << endl;

//Operator -
cout << endl << "Operator -" << endl;
cout << (V1-V2) << endl;

//Dot
cout << endl << "Dot" << endl;
cout << V1.Dot(V2) << endl;

//Vect
cout << endl << "Vect" << endl;
cout << V1.Vect(V2) << endl;

//Normal
cout << endl << "Normal" << endl;
cout << V1.Normal() << endl;

//Unit
cout << endl << "Unit" << endl;
cout << V1.Unit() << endl;

//Mod
cout << endl << "Mod" << endl;
cout << V1.Mod() << endl;

//Angle
cout << endl << "Angle" << endl;
cout << V1.Angle(V2) << endl;

//ShortAngle
cout << endl << "ShortAngle" << endl;
cout << V1.ShortAngle(V2) << endl;

//ClockwiseAngle
cout << endl << "ClockwiseAngle" << endl;
cout << V1.ClockwiseAngle(V2) << endl;

//OrderedAngle
cout << endl << "OrderedAngle" << endl;
cout << V1.OrderedAngle(V2) << endl<<endl;


/***********************************************\
 *                nCompVector                  *
\***********************************************/

cout << "class nCompVector" << endl;

// Constructor
cout << "Constructor" << endl;
nCompVector nV1(4,2.0,3.0,4.0,5.0),nV2,nV3(3,1.0,2.0,3.0),nV4,nV5,nVtemp;
nV2.Set(3,5.0,6.0,7.0);
nV2.Set(4,8.0,9.0,10.0,11.0);
nV4.Set(2,1.0,1.0);

//Show
cout << endl << "Show" << endl;
nV1.Show();
nV2.Show();
nV3.Show();
nV4.Show();
nV5.Show();

//Operator <<
cout << endl << "Operator <<" << endl;
cout << nV1 << endl;

//Operator ==
cout << endl << "Operator ==" << endl;
cout << (nV1==nV2) << endl << (nV1==nV1) << endl <<(nV1==nV3) << endl;

//Operator <
cout << endl << "Operator <" << endl;
cout << (nV1<nV2) << endl << (nV1<nV1) << endl << (nV3<nV1) << endl;

//Operator *
cout << endl << "Operator *" << endl;
cout << (nV1*nV2) << endl;
cout << (nV1*nV4) << endl;

//Operator *
cout << endl << "Operator *" << endl;
cout << (nV1*3) << endl;

//Operator +
cout << endl << "Operator +" << endl;
nVtemp = nV1+nV2;
cout << nVtemp << endl;
nVtemp = nV1+nV4;
cout << nVtemp << endl;
nVtemp = nV4+nV1;
cout << nVtemp << endl;

//Operator -
cout << endl << "Operator -" << endl;
nVtemp = nV1-nV2;
cout << nVtemp << endl;
nVtemp = nV1-nV4;
cout << nVtemp << endl;
nVtemp = nV4-nV1;
cout << nVtemp << endl;

//Dot
cout << endl << "Dot" << endl;
cout << (nV1.Dot(nV2)) << endl;
cout << (nV1.Dot(nV4)) << endl;

//Unit
cout << endl << "Unit" << endl;
cout << nV1.Unit() << endl;

//Mod
cout << endl << "Mod" << endl;
cout << nV1.Mod() << endl;

//EuclideanDistance
cout << endl << "EuclideanDistance" << endl;
cout << (nV1.EuclideanDistance(nV2)) << endl;
cout << (nV1.EuclideanDistance(nV4)) << endl;


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

