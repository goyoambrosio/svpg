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

#include <CVL/Vector.h>
#include <CVL/Point.h>
#include <CVL/Line.h>
#include <CVL/DirectedLineSegment.h>
#include <CVL/Polygon.h>

#include <string>                     //From SGI STL. For ios functions. It's like #include <iostream>
#include <time.h>

using namespace GAC;
using namespace std;

void sleep( clock_t wait );

void main( int argc, char *argv[] )
{
	clock_t start, finish;
	double  duration;

    start = clock();


	
//NOTE: Uncomment the section you wish to test. !!!




    
/***********************************************\
 *                     Vector                  *
\***********************************************/
/*
cout << "***********************************************" << endl << "*                     Vector                  *" << endl << "***********************************************" << endl;

// Constructor
cout << "Constructor" << endl;
Vector nV1(4,2.0,3.0,4.0,5.0),nV2,nV3(3,1.0,2.0,3.0),nV4,nV5,nVtemp;
nV2.Set(3,5.0,6.0,7.0);
nV2.Set(4,8.0,9.0,10.0,11.0);
nV4.Set(2,1.0,1.0);
nV5=nV4;

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

//Operator !=
cout << endl << "Operator !=" << endl;
cout << (nV1!=nV2) << endl << (nV1!=nV1) << endl <<(nV1!=nV3) << endl;

//Operator <
cout << endl << "Operator <" << endl;
cout << (nV1<nV2) << endl << (nV1<nV1) << endl << (nV3<nV1) << endl;

//Operator >
cout << endl << "Operator >" << endl;
cout << (nV1>nV2) << endl << (nV1>nV1) << endl << (nV3>nV1) << endl;

//Operator <=
cout << endl << "Operator <=" << endl;
cout << (nV1<=nV2) << endl << (nV1<=nV1) << endl << (nV3<=nV1) << endl;

//Operator >=
cout << endl << "Operator >=" << endl;
cout << (nV1>=nV2) << endl << (nV1>=nV1) << endl << (nV3>=nV1) << endl;

//Operator *
cout << endl << "Operator *" << endl;
cout << (nV1*nV2) << endl;
cout << (nV1*nV4) << endl;

//Operator *
cout << endl << "Operator *" << endl;
cout << (nV1*3) << endl;
cout << (3*nV1) << endl;

//Operator /
cout << endl << "Operator /" << endl;
cout << (nV1/3) << endl;
cout << (3/nV1) << endl;

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

//Norm
cout << endl << "Norm" << endl;
cout << nV1.Norm() << endl;

//Mod
cout << endl << "Mod" << endl;
cout << nV1.Mod() << endl;

//Length
cout << endl << "Length" << endl;
cout << nV1.Length() << endl;

//EuclideanDistance
//cout << endl << "EuclideanDistance" << endl;
//cout << (nV1.EuclideanDistance(nV2)) << endl;
//cout << (nV1.EuclideanDistance(nV4)) << endl;



/***********************************************\
 *                   Vector2D                  *
\***********************************************/
/*

cout << "***********************************************" << endl << "*                   Vector2D                  *" << endl << "***********************************************" << endl;

// Constructor
cout << "Constructor" << endl;
Vector2D V1(2,3), V2(6,5),V3,V4,Vtemp;
V3.Set(8,7);

//x,y
cout << endl << "x,y" << endl;
cout << V1.x() << "," << V1.y() << endl;

//Show
cout << endl << "Show" << endl;
V1.Show();V2.Show();V3.Show();V4.Show();

//Operator <<
cout << endl << "Operator <<" << endl;
cout << V1 << endl;

//Operator ==
cout << endl << "Operator ==" << endl;
cout << (V1==V2) << endl << (V1==V1) << endl;

//Operator !=
cout << endl << "Operator !=" << endl;
cout << (V1!=V2) << endl << (V1!=V1) << endl;

//Operator <
cout << endl << "Operator <" << endl;
cout << (V1<V2) << endl << (V1<V1) << endl;

//Operator >
cout << endl << "Operator >" << endl;
cout << (V1>V2) << endl << (V1>V1) << endl;

//Operator <=
cout << endl << "Operator <=" << endl;
cout << (V1<=V2) << endl << (V1<=V1) << endl;

//Operator >
cout << endl << "Operator >=" << endl;
cout << (V1>=V2) << endl << (V1>=V1) << endl;

//Operator *
cout << endl << "Operator *" << endl;
cout << (V1*3) << endl;
cout << (3*V1) << endl;

//Operator /
cout << endl << "Operator /" << endl;
cout << (V1/3) << endl;
cout << (3/V1) << endl;

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
cout << endl << "Cross" << endl;
cout << V1.Cross(V2) << endl;

//Normal
cout << endl << "Normal" << endl;
cout << V1.Normal() << endl;

//Unit
cout << endl << "Unit" << endl;
cout << V1.Unit() << endl;

//Norm
cout << endl << "Norm" << endl;
cout << V1.Norm() << endl;

//Mod
cout << endl << "Mod" << endl;
cout << V1.Mod() << endl;

//Length
cout << endl << "Length" << endl;
cout << V1.Length() << endl;

//EuclideanDistance
//cout << endl << "EuclideanDistance" << endl;
//cout << (V1.EuclideanDistance(V2)) << endl;
//cout << (V1.EuclideanDistance(V4)) << endl;

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
 *                     Point                   *
\***********************************************/
/*
cout << "***********************************************" << endl << "*                     Point                   *" << endl << "***********************************************" << endl;

// Constructor
cout << "Constructor" << endl;
Point P1(4,2.0,3.0,4.0,5.0),P2,P3(3,1.0,2.0,3.0),P4,P5,Ptemp;
P2.Set(3,5.0,6.0,7.0);
P2.Set(4,8.0,9.0,10.0,11.0);
P4.Set(2,1.0,1.0);

//Show
cout << endl << "Show" << endl;
P1.Show();
P2.Show();
P3.Show();
P4.Show();
P5.Show();

//Operator <<
cout << endl << "Operator <<" << endl;
cout << P1 << endl;

//Operator ==
cout << endl << "Operator ==" << endl;
cout << (P1==P2) << endl << (P1==P1) << endl <<(P1==P3) << endl;

//Operator !=
cout << endl << "Operator !=" << endl;
cout << (P1!=P2) << endl << (P1!=P1) << endl <<(P1!=P3) << endl;

//Operator <
cout << endl << "Operator <" << endl;
cout << (P1<P2) << endl << (P1<P1) << endl << (P3<P1) << endl;

//Distance
cout << endl << "Distance" << endl;
cout << (P1.Distance(P2)) << endl;
cout << (P1.Distance(P4)) << endl;

//Swap
cout << endl << "Swap" << endl;
cout << P2 << P3 << endl;
P2.Swap(P3);
cout << P2 << P3 << endl;
P2.Swap(P3);
cout << P2 << P3 << endl;


/***********************************************\
 *                   Point2D                   *
\***********************************************/
/*
cout << "***********************************************" << endl << "*                   Point2D                   *" << endl << "***********************************************" << endl;

// Constructor
cout << "Constructor" << endl;
Point2D P2D1(2,3), P2D2(6,5),P2D3,P2D4,P2D5,P2Dtemp;
P2D3.Set(8,7);
P2D4.Setx(4);
P2D5.Sety(9);

//x,y
cout << endl << "i,j" << endl;
cout << P2D1.x() << "," << P2D1.y() << endl;

//Show
cout << endl << "Show" << endl;
P2D1.Show();
P2D2.Show();
P2D3.Show();
P2D4.Show();
P2D5.Show();

//Operator <<
cout << endl << "Operator <<" << endl;
cout << P2D1 << endl;

//Operator ==
cout << endl << "Operator ==" << endl;
cout << (P2D1==P2D2) << endl << (P2D1==P2D1) << endl <<(P2D1==P2D3) << endl;

//Operator !=
cout << endl << "Operator !=" << endl;
cout << (P2D1!=P2D2) << endl << (P2D1!=P2D1) << endl <<(P2D1!=P2D3) << endl;

//Operator <
cout << endl << "Operator <" << endl;
cout << (P2D1<P2D2) << endl << (P2D1<P2D1) << endl << (P2D3<P2D1) << endl;

//Distance
cout << endl << "Distance" << endl;
cout << (P2D1.Distance(P2D2)) << endl;
cout << (P2D1.Distance(P2D4)) << endl;

//Swap
cout << endl << "Swap" << endl;
cout << P2D2 << P2D3 << endl;
P2D2.Swap(P2D3);
cout << P2D2 << P2D3 << endl;
P2D2.Swap(P2D3);
cout << P2D2 << P2D3 << endl;

//Rot
cout << endl << "Rot" << endl;
cout << PI << endl;
cout << P2D1 << endl;
P2D1.Rot(PI/2);
cout << P2D1 << endl;
P2D1.Rot(-PI/2);
cout << P2D1 << endl;


/***********************************************\
 *                   Globals                   *
\***********************************************/
/*
cout << "***********************************************" << endl << "*                   Globals                   *" << endl << "***********************************************" << endl;

cout << GAC::Round(1.56) << endl;


/***********************************************\
 *                   Line                   *
\***********************************************/
/*
cout << "***********************************************" << endl << "*                   Line                      *" << endl << "***********************************************" << endl;

Line L1(1,0);
Line L2(Point2D(0,0),Point2D(4,0));
Line L3(0,0,0,4);
Line L4; L4.Set(4,4,0);
Line L5(1,0,1,4);
Line L6(0,1,4,1);
Line Ltemp;
Point2D P,Q,P2D1,P2D2;
Point2D A1,A2,B1,B2;

L1.Show();
L2.Show();
L3.Show();
L4.Show();
L5.Show();
L6.Show();
Ltemp.Show();

//Operator ==
cout << endl << "Operator ==" << endl;
cout << (L1==L2) << endl << (L1==L1) << endl <<(L1==L3) << endl;

//Operator <
cout << endl << "Operator <" << endl;
cout << (L1<L2) << endl << (L1<L1) << endl <<(L1<L3) << endl;

//y(x)
cout << endl << "y(x)" << endl;
cout << L1.y(5) << endl << L2.y(3) << endl <<L3.y(6) << endl << L4.y(2)<< endl;

//x(y)
cout << endl << "x(y)" << endl;
cout << L1.x(5) << endl << L2.x(0) << endl <<L3.x(6) << endl << L4.x(2)<< endl;

//m,n,Fi,posFi
cout << endl << "m,n,Fi,posFi" << endl;
cout << L1.m() << "," << L1.n() << "," <<L1.Fi() << "," << L1.PosFi()<< endl;
cout << L2.m() << "," << L2.n() << "," <<L2.Fi() << "," << L2.PosFi()<< endl;
cout << L3.m() << "," << L3.n() << "," <<L3.Fi() << "," << L3.PosFi()<< endl;
cout << L4.m() << "," << L4.n() << "," <<L4.Fi() << "," << L4.PosFi()<< endl;

//Sigma,D
cout << endl << "Sigma,D" << endl;
cout << L1.Sigma() << "," << L1.d() << endl;
cout << L2.Sigma() << "," << L2.d() << endl;
cout << L3.Sigma() << "," << L3.d() << endl;
cout << L4.Sigma() << "," << L4.d() << endl;

//a,b,c
cout << endl << "a,b,c" << endl;
cout << L1.a() << "," << L1.b() << "," << L1.c() << endl;
cout << L2.a() << "," << L2.b() << "," << L2.c() << endl;
cout << L3.a() << "," << L3.b() << "," << L3.c() << endl;
cout << L4.a() << "," << L4.b() << "," << L4.c() << endl;

//isVertical, isHorizontal
cout << endl << "isVertical, isHorizontal" << endl;
cout << L1.isVertical() << "," << L1.isHorizontal() << endl;
cout << L2.isVertical() << "," << L2.isHorizontal() << endl;
cout << L3.isVertical() << "," << L3.isHorizontal() << endl;
cout << L4.isVertical() << "," << L4.isHorizontal() << endl;

//EuclideanDistance
cout << endl << "EuclideanDistance" << endl;
P.Set(0,4);
cout << L1.EuclideanDistance(P) << endl;
cout << L2.EuclideanDistance(P) << endl;
cout << L3.EuclideanDistance(P) << endl;
cout << L4.EuclideanDistance(P) << endl;
cout << L5.EuclideanDistance(P) << endl;
cout << L6.EuclideanDistance(P) << endl;

//Angle
cout << endl << "Angle" << endl;
cout << L1.Angle(L2) << endl;
cout << L1.Angle(L3) << endl;
cout << L1.Angle(L4) << endl;
cout << L1.Angle(L5) << endl;
cout << L1.Angle(L6) << endl;

//PerpLine
cout << endl << "PerpLine" << endl;
P.Set(0,0);
L1.PerpLine(P).Show();
L2.PerpLine(P).Show();
L3.PerpLine(P).Show();
L4.PerpLine(P).Show();
L5.PerpLine(P).Show();
L6.PerpLine(P).Show();

//isParallel
cout << endl << "isParallel" << endl;
cout << L1.isParallel(L1) << endl;
cout << L1.isParallel(L2) << endl;
cout << L1.isParallel(L3) << endl;
cout << L1.isParallel(L4) << endl;
cout << L1.isParallel(L5) << endl;
cout << L1.isParallel(L6) << endl;
cout << L3.isParallel(L5) << endl;
cout << L2.isParallel(L6) << endl;

//Intersection
cout << endl << "Intersection" << endl;
cout << L1.Intersection(L1) << endl;
cout << L1.Intersection(L2) << endl;
cout << L1.Intersection(L3) << endl;
cout << L1.Intersection(L4) << endl;
cout << L1.Intersection(L5) << endl;
cout << L1.Intersection(L6) << endl;

//EquidistantPointsInLine
cout << endl << "EquidistantPointsInLine" << endl;
P.Set(0,0);
L1.EquidistantPointsInLine(P,2,P2D1,P2D2);
cout <<P2D1<<","<<P2D2<<endl;
L2.EquidistantPointsInLine(P,2,P2D1,P2D2);
cout <<P2D1<<","<<P2D2<<endl;
L3.EquidistantPointsInLine(P,2,P2D1,P2D2);
cout <<P2D1<<","<<P2D2<<endl;
L4.EquidistantPointsInLine(P,2,P2D1,P2D2);
cout <<P2D1<<","<<P2D2<<endl;
P.Set(1,0);
L5.EquidistantPointsInLine(P,2,P2D1,P2D2);
cout <<P2D1<<","<<P2D2<<endl;
P.Set(0,1);
L6.EquidistantPointsInLine(P,2,P2D1,P2D2);
cout <<P2D1<<","<<P2D2<<endl;

//RectangleAroundLine
cout << endl << "RectangleAroundLine" << endl;
P.Set(0,0);Q.Set(4,4);
L1.RectangleAroundLine(P,Q,2,A1,A2,B1,B2);
cout <<A1<<","<<A2<<":"<<B1<<","<<B2<<endl;
P.Set(0,0);Q.Set(4,0);
L2.RectangleAroundLine(P,Q,2,A1,A2,B1,B2);
cout <<A1<<","<<A2<<":"<<B1<<","<<B2<<endl;
P.Set(0,0);Q.Set(0,4);
L3.RectangleAroundLine(P,Q,2,A1,A2,B1,B2);
cout <<A1<<","<<A2<<":"<<B1<<","<<B2<<endl;

//Pow
cout << endl << "Pow" << endl;
P.Set(0,4);
cout << L1.Pow(P) << endl;
cout << L2.Pow(P) << endl;
cout << L3.Pow(P) << endl;
cout << L4.Pow(P) << endl;
cout << L5.Pow(P) << endl;
cout << L6.Pow(P) << endl;

//Side
cout << endl << "Side" << endl;
P.Set(0,4);
cout << L1.Side(P) << endl;
cout << L2.Side(P) << endl;
cout << L3.Side(P) << endl;
cout << L4.Side(P) << endl;
cout << L5.Side(P) << endl;
cout << L6.Side(P) << endl;
P.Set(0,-4);
cout << L1.Side(P) << endl;
cout << L2.Side(P) << endl;
cout << L3.Side(P) << endl;
cout << L4.Side(P) << endl;
cout << L5.Side(P) << endl;
cout << L6.Side(P) << endl;

//IsInPosLeftSide,IsInNegRightSide
cout << endl << "IsInPosLeftSide,IsInNegRightSide" << endl;
P.Set(0,4);
cout << L1.IsInPosLeftSide(P) << "," << L1.IsInNegRightSide(P) <<endl;
cout << L2.IsInPosLeftSide(P) << "," << L2.IsInNegRightSide(P) << endl;
cout << L3.IsInPosLeftSide(P) << "," << L3.IsInNegRightSide(P) << endl;
cout << L4.IsInPosLeftSide(P) << "," << L4.IsInNegRightSide(P) << endl;
cout << L5.IsInPosLeftSide(P) << "," << L5.IsInNegRightSide(P) << endl;
cout << L6.IsInPosLeftSide(P) << "," << L6.IsInNegRightSide(P) << endl;
P.Set(0,-4);
cout << L1.IsInPosLeftSide(P) << "," << L1.IsInNegRightSide(P) << endl;
cout << L2.IsInPosLeftSide(P) << "," << L2.IsInNegRightSide(P) << endl;
cout << L3.IsInPosLeftSide(P) << "," << L3.IsInNegRightSide(P) << endl;
cout << L4.IsInPosLeftSide(P) << "," << L4.IsInNegRightSide(P) << endl;
cout << L5.IsInPosLeftSide(P) << "," << L5.IsInNegRightSide(P) << endl;
cout << L6.IsInPosLeftSide(P) << "," << L6.IsInNegRightSide(P) << endl;

//IsNearPosLeftSide,IsNearNegRightSide
cout << endl << "IsNearPosLeftSide,IsNearNegRightSide" << endl;
P.Set(0.5,4);
cout << L1.IsNearPosLeftSide(P,1) << "," << L1.IsNearNegRightSide(P,1) <<endl;
cout << L2.IsNearPosLeftSide(P,1) << "," << L2.IsNearNegRightSide(P,1) << endl;
cout << L3.IsNearPosLeftSide(P,1) << "," << L3.IsNearNegRightSide(P,1) << endl;
cout << L4.IsNearPosLeftSide(P,1) << "," << L4.IsNearNegRightSide(P,1) << endl;
cout << L5.IsNearPosLeftSide(P,1) << "," << L5.IsNearNegRightSide(P,1) << endl;
cout << L6.IsNearPosLeftSide(P,1) << "," << L6.IsNearNegRightSide(P,1) << endl;

//Contains
cout << endl << "Contains" << endl;
cout << L1.Contains(Point2D(5,5)) << endl;
cout << L1.Contains(Point2D(5,5.1)) << endl;
cout << L2.Contains(Point2D(3,0)) << endl;
cout << L2.Contains(Point2D(3,0.0001)) << endl;
cout << L3.Contains(Point2D(0,5)) << endl;
cout << L3.Contains(Point2D(0.00000000000001,5)) << endl;
cout << L4.Contains(Point2D(-2,2)) << endl;
cout << L4.Contains(Point2D(-1,0.999999999999)) << endl;


/***********************************************\
 *                   Point2DVector             *
\***********************************************/
/*
cout << "***********************************************" << endl << "*                Point2DVector                *" << endl << "***********************************************" << endl;

Point2DVector PV1;
double Error;
PV1.push_back(Point2D(0,-0.1));
PV1.push_back(Point2D(1.1,1));
PV1.push_back(Point2D(2.2,2));
PV1.push_back(Point2D(3.001,3));
PV1.push_back(Point2D(4,3.999));

PV1.LinearRegression(Error).Show();
cout << "Error:" << Error << endl;

/***********************************************\
 *             DirectedLineSegment             *
\***********************************************/
/*
cout << "***********************************************" << endl << "*            DirectedLineSegment              *" << endl << "***********************************************" << endl;

DirectedLineSegment S1(1,1,4,5);
DirectedLineSegment S2(Point2D(1,0),Point2D(4,0));
DirectedLineSegment S3(0,1,0,5);
DirectedLineSegment S4(-4,4,1,-1);
DirectedLineSegment S5(1,-2,1,5);
DirectedLineSegment S6(0,1,4,1);
DirectedLineSegment Stemp;
Vector2D V;

Vector2D V1(2,3), V2(6,5),V3,V4,Vtemp;
V3.Set(8,7);

Line L1(1,0);
Line L2(Point2D(0,0),Point2D(4,0));
Line L3(0,0,0,4);
Line L4; L4.Set(4,4,0);
Line L5(1,0,1,4);
Line L6(0,1,4,1);
Line Ltemp;

Point2D P,Q,P2D1,P2D2,A1,A2,B1,B2;

//p,q
cout << endl << "p,q" << endl;
cout << S1.p() << S1.q() << endl;
cout << S2.p() << S2.q() << endl;

//Set
cout << endl << "Set" << endl;
S1.Set(1,1,4,5);
S2.Set(Point2D(1,0),Point2D(4,0));
cout << S1.p() << S1.q() << "->" << S1 << endl;
cout << S2.p() << S2.q() << "->" << S2 << endl;

//SetP
cout << endl << "SetP" << endl;
S1.SetP(Point2D(2,2));
cout << S1.p() << S1.q() << "->" << S1 << endl;
S1.SetP(1,1);
cout << S1.p() << S1.q() << "->" << S1 << endl;

//SetQ
cout << endl << "SetQ" << endl;
S2.SetQ(Point2D(6,-2));
cout << S2.p() << S2.q() << "->" << S2 << endl;
S2.SetQ(4,0);
cout << S2.p() << S2.q() << "->" << S2 << endl;

//MidPoint
cout << endl << "MidPoint" << endl;
cout << S1.MidPoint() << endl;

//Contains
cout << endl << "Contains" << endl;
S6.Set(1,1,5,5);
cout << S6.Contains(Point2D(2,2)) << endl;             //DirectedLineSegment::Contains
cout << S6.Contains(Point2D(2,2.1)) << endl;
cout << S6.Contains(Point2D(6,6)) << endl;
cout << S6.Line::Contains(Point2D(2,2)) << endl;       //Line::Constains
cout << S6.Line::Contains(Point2D(2,2.1)) << endl;
cout << S6.Line::Contains(Point2D(6,6)) << endl;  

//Reverse
cout << endl << "Reverse" << endl;
cout << S1 << S1.Reverse() << endl;

//Overlap
cout << endl << "Overlap" << endl;
S1.Set(1,1,5,5);
S2.Set(2,2,4,4);
if (S1.Overlap(S2,S3)) cout << S3.p() << S3.q() << S1.Vector2D::Angle(S3) << endl;
S2.Set(0,0,5,5);
if (S1.Overlap(S2,S3)) cout << S3.p() << S3.q() << S1.Vector2D::Angle(S3) << endl;
S2.Set(4,4,2,2);
if (S1.Overlap(S2,S3)) cout << S3.p() << S3.q() << S1.Vector2D::Angle(S3) << endl;
S2.Set(5,5,0,0);
if (S1.Overlap(S2,S3)) cout << S3.p() << S3.q() << S1.Vector2D::Angle(S3) << endl;




//DirectedLineSegment with Lines

//isParallel
cout << endl << "isParallel" << endl;
cout << S1.isParallel(L1) << endl;
cout << S1.isParallel(L2) << endl;
cout << S1.isParallel(L3) << endl;
cout << S1.isParallel(L4) << endl;
cout << S1.isParallel(L5) << endl;
cout << S1.isParallel(L6) << endl;
cout << S3.isParallel(L5) << endl;
cout << S2.isParallel(L6) << endl;

//DirectedLineSegment with Vector2D

//Angle
cout << endl << "Angle" << endl;
cout << S1.Vector2D::Angle(V2) << endl;
cout << S2.Vector2D::Angle(V1) << endl;
cout << V1.Angle(S2) << endl;
cout << V2.Angle(S1) << endl;



//Methods of Vector2D

//x,y
cout << endl << "x,y" << endl;
cout << S1.Vector2D::x() << "," << S1.Vector2D::y() << endl;

//Show
cout << endl << "Show" << endl;
S1.Vector2D::Show();S2.Vector2D::Show();S3.Vector2D::Show();S4.Vector2D::Show();

//Operator <<
cout << endl << "Operator <<" << endl;
cout << S1 << endl;

//Operator ==
cout << endl << "Operator ==" << endl;
cout << (S1==S2) << endl << (S1==S1) << endl; //There is not ambiguity because this operator
                                              //is defined (overloaded) in this class.

//Operator !=
cout << endl << "Operator !=" << endl;
cout << (S1!=S2) << endl << (S1!=S1) << endl;

//Operator <
cout << endl << "Operator <" << endl;
cout << (S1<S2) << endl;  //Vector2D::operator< is used by default because of the order 
                          //in the declaration of inherited classes:
                          //class DirectedLineSegment : public Vector2D,public Line   
//This is an example of selection of adecuated "<" operator.
cout << (S1.Vector2D::operator<(S2)) << endl << (S1.Line::operator<(S1)) << endl;

//Operator >
cout << endl << "Operator >" << endl;
cout << (S1>S2) << endl;   

//Operator <=
cout << endl << "Operator <=" << endl;
cout << (S1<=S1) << endl << (S1<=S2) << endl;  
 
//Operator >=
cout << endl << "Operator >=" << endl;
cout << (S1>=S1) << endl << (S1>=S2) << endl;   

//Operator *
cout << endl << "Operator *" << endl;
cout << (S1*3) << endl;
cout << (3*S1) << endl;

//Operator /
cout << endl << "Operator /" << endl;
cout << (S1/3) << endl;
cout << (3/S1) << endl;

//Operator *
cout << endl << "Operator *" << endl;
cout << (S1*S2) << endl;

//Operator +
cout << endl << "Operator +" << endl;
//V = (S1+S2);             //+ operation between segments results in a Vector2D
//cout << V << endl;

//Operator -
cout << endl << "Operator -" << endl;
cout << (S1-S2) << endl; //- operation between segments results in a Vector2D

//Dot
cout << endl << "Dot" << endl;
cout << S1.Dot(S2) << endl;

//Vect
cout << endl << "Cross" << endl;
cout << S1.Cross(S2) << endl;

//Normal
cout << endl << "Normal" << endl;
cout << S1.Normal() << endl;

//Unit
cout << endl << "Unit" << endl;
cout << S1.Unit() << endl;

//Norm
cout << endl << "Norm" << endl;
cout << S1.Norm() << endl;

//Mod
cout << endl << "Mod" << endl;
cout << S1.Mod() << endl;

//Length
cout << endl << "Length" << endl;
cout << S1.Length() << endl;

//EuclideanDistance
//cout << endl << "EuclideanDistance" << endl;
//cout << (S1.EuclideanDistance(S2)) << endl;
//cout << (S1.EuclideanDistance(S4)) << endl;

//Angle
cout << endl << "Angle" << endl;
cout << S1.Vector2D::Angle(S2) << endl;
cout << S1.Line::Angle(S2) << endl;
cout << S2.Vector2D::Angle(S1) << endl;
cout << S2.Line::Angle(S1) << endl;
cout << S3.Vector2D::Angle(S5) << endl;
cout << S3.Line::Angle(S5) << endl;
cout << S4.Vector2D::Angle(S6) << endl;
cout << S4.Line::Angle(S6) << endl;
cout << S5.Vector2D::Angle(S1) << endl;
cout << S5.Line::Angle(S1) << endl;
cout << S6.Vector2D::Angle(S6) << endl;
cout << S6.Line::Angle(S6) << endl;

//ShortAngle
cout << endl << "ShortAngle" << endl;
cout << S1.ShortAngle(S2) << endl;

//ClockwiseAngle
cout << endl << "ClockwiseAngle" << endl;
cout << S1.ClockwiseAngle(S2) << endl;

//OrderedAngle
cout << flush << endl << "OrderedAngle" << endl;
cout << S1.OrderedAngle(S2) << endl<<endl;


//Methods of Line

//y(x)
cout << endl << "y(x)" << endl;
cout << S1.Line::y(5) << endl << S2.Line::y(3) << endl <<S3.Line::y(6) << endl << S4.Line::y(2)<< endl;

//x(y)
cout << endl << "x(y)" << endl;
cout << S1.Line::x(5) << endl << S2.Line::x(0) << endl <<S3.Line::x(6) << endl << S4.Line::x(2)<< endl;

//m,n,Fi,posFi
cout << endl << "m,n,Fi,posFi" << endl;
cout << S1.m() << "," << S1.n() << "," <<S1.Fi() << "," << S1.PosFi()<< endl;
cout << S2.m() << "," << S2.n() << "," <<S2.Fi() << "," << S2.PosFi()<< endl;
cout << S3.m() << "," << S3.n() << "," <<S3.Fi() << "," << S3.PosFi()<< endl;
cout << S4.m() << "," << S4.n() << "," <<S4.Fi() << "," << S4.PosFi()<< endl;

//Sigma,D
cout << endl << "Sigma,D" << endl;
cout << S1.Sigma() << "," << S1.d() << endl;
cout << S2.Sigma() << "," << S2.d() << endl;
cout << S3.Sigma() << "," << S3.d() << endl;
cout << S4.Sigma() << "," << S4.d() << endl;

//a,b,c
cout << endl << "a,b,c" << endl;
cout << S1.a() << "," << S1.b() << "," << S1.c() << endl;
cout << S2.a() << "," << S2.b() << "," << S2.c() << endl;
cout << S3.a() << "," << S3.b() << "," << S3.c() << endl;
cout << S4.a() << "," << S4.b() << "," << S4.c() << endl;

//isVertical, isHorizontal
cout << endl << "isVertical, isHorizontal" << endl;
cout << S1.isVertical() << "," << S1.isHorizontal() << endl;
cout << S2.isVertical() << "," << S2.isHorizontal() << endl;
cout << S3.isVertical() << "," << S3.isHorizontal() << endl;
cout << S4.isVertical() << "," << S4.isHorizontal() << endl;

//EuclideanDistance
cout << endl << "EuclideanDistance" << endl;
P.Set(0,4);
cout << S1.EuclideanDistance(P) << endl;
cout << S2.EuclideanDistance(P) << endl;
cout << S3.EuclideanDistance(P) << endl;
cout << S4.EuclideanDistance(P) << endl;
cout << S5.EuclideanDistance(P) << endl;
cout << S6.EuclideanDistance(P) << endl;

//Angle
cout << endl << "Angle" << endl;
cout << S1.Vector2D::Angle(S2) << endl;
cout << S1.Line::Angle(S2) << endl;
cout << S2.Vector2D::Angle(S1) << endl;
cout << S2.Line::Angle(S1) << endl;
cout << S3.Vector2D::Angle(S5) << endl;
cout << S3.Line::Angle(S5) << endl;
cout << S4.Vector2D::Angle(S6) << endl;
cout << S4.Line::Angle(S6) << endl;
cout << S5.Vector2D::Angle(S1) << endl;
cout << S5.Line::Angle(S1) << endl;
cout << S6.Vector2D::Angle(S6) << endl;
cout << S6.Line::Angle(S6) << endl;

//PerpLine
cout << endl << "PerpLine" << endl;
P.Set(0,0);
S1.PerpLine(P).Show();
S2.PerpLine(P).Show();
S3.PerpLine(P).Show();
S4.PerpLine(P).Show();
S5.PerpLine(P).Show();
S6.PerpLine(P).Show();

//isParallel
cout << endl << "isParallel" << endl;
cout << S1.isParallel(S1) << endl;
cout << S1.isParallel(S2) << endl;
cout << S1.isParallel(S3) << endl;
cout << S1.isParallel(S4) << endl;
cout << S1.isParallel(S5) << endl;
cout << S1.isParallel(S6) << endl;
cout << S3.isParallel(S5) << endl;
cout << S2.isParallel(S6) << endl;

//Intersection
cout << endl << "Intersection" << endl;
cout << S1.Intersection(S1) << endl;
cout << S1.Intersection(S2) << endl;
cout << S1.Intersection(S3) << endl;
cout << S1.Intersection(S4) << endl;
cout << S1.Intersection(S5) << endl;
cout << S1.Intersection(S6) << endl;

//EquidistantPointsInLine
cout << endl << "EquidistantPointsInLine" << endl;
P.Set(0,0);
S1.EquidistantPointsInLine(P,2,P2D1,P2D2);
cout <<P2D1<<","<<P2D2<<endl;
S2.EquidistantPointsInLine(P,2,P2D1,P2D2);
cout <<P2D1<<","<<P2D2<<endl;
S3.EquidistantPointsInLine(P,2,P2D1,P2D2);
cout <<P2D1<<","<<P2D2<<endl;
S4.EquidistantPointsInLine(P,2,P2D1,P2D2);
cout <<P2D1<<","<<P2D2<<endl;
P.Set(1,0);
S5.EquidistantPointsInLine(P,2,P2D1,P2D2);
cout <<P2D1<<","<<P2D2<<endl;
P.Set(0,1);
S6.EquidistantPointsInLine(P,2,P2D1,P2D2);
cout <<P2D1<<","<<P2D2<<endl;

//RectangleAroundLine
cout << endl << "RectangleAroundLine" << endl;
P.Set(0,0);Q.Set(4,4);
S1.RectangleAroundLine(P,Q,2,A1,A2,B1,B2);
cout <<A1<<","<<A2<<":"<<B1<<","<<B2<<endl;
P.Set(0,0);Q.Set(4,0);
S2.RectangleAroundLine(P,Q,2,A1,A2,B1,B2);
cout <<A1<<","<<A2<<":"<<B1<<","<<B2<<endl;
P.Set(0,0);Q.Set(0,4);
S3.RectangleAroundLine(P,Q,2,A1,A2,B1,B2);
cout <<A1<<","<<A2<<":"<<B1<<","<<B2<<endl;

//Pow
cout << endl << "Pow" << endl;
P.Set(0,4);
cout << S1.Pow(P) << endl;
cout << S2.Pow(P) << endl;
cout << S3.Pow(P) << endl;
cout << S4.Pow(P) << endl;
cout << S5.Pow(P) << endl;
cout << S6.Pow(P) << endl;

//Side
cout << endl << "Side" << endl;
P.Set(0,4);
cout << S1.Side(P) << endl;
cout << S2.Side(P) << endl;
cout << S3.Side(P) << endl;
cout << S4.Side(P) << endl;
cout << S5.Side(P) << endl;
cout << S6.Side(P) << endl;
P.Set(0,-4);
cout << S1.Side(P) << endl;
cout << S2.Side(P) << endl;
cout << S3.Side(P) << endl;
cout << S4.Side(P) << endl;
cout << S5.Side(P) << endl;
cout << S6.Side(P) << endl;

//IsInPosLeftSide,IsInNegRightSide
cout << endl << "IsInPosLeftSide,IsInNegRightSide" << endl;
P.Set(0,4);
cout << S1.IsInPosLeftSide(P) << "," << S1.IsInNegRightSide(P) <<endl;
cout << S2.IsInPosLeftSide(P) << "," << S2.IsInNegRightSide(P) << endl;
cout << S3.IsInPosLeftSide(P) << "," << S3.IsInNegRightSide(P) << endl;
cout << S4.IsInPosLeftSide(P) << "," << S4.IsInNegRightSide(P) << endl;
cout << S5.IsInPosLeftSide(P) << "," << S5.IsInNegRightSide(P) << endl;
cout << S6.IsInPosLeftSide(P) << "," << S6.IsInNegRightSide(P) << endl;
P.Set(0,-4);
cout << S1.IsInPosLeftSide(P) << "," << S1.IsInNegRightSide(P) << endl;
cout << S2.IsInPosLeftSide(P) << "," << S2.IsInNegRightSide(P) << endl;
cout << S3.IsInPosLeftSide(P) << "," << S3.IsInNegRightSide(P) << endl;
cout << S4.IsInPosLeftSide(P) << "," << S4.IsInNegRightSide(P) << endl;
cout << S5.IsInPosLeftSide(P) << "," << S5.IsInNegRightSide(P) << endl;
cout << S6.IsInPosLeftSide(P) << "," << S6.IsInNegRightSide(P) << endl;

//IsNearPosLeftSide,IsNearNegRightSide
cout << endl << "IsNearPosLeftSide,IsNearNegRightSide" << endl;
P.Set(0.5,4);
cout << S1.IsNearPosLeftSide(P,1) << "," << S1.IsNearNegRightSide(P,1) <<endl;
cout << S2.IsNearPosLeftSide(P,1) << "," << S2.IsNearNegRightSide(P,1) << endl;
cout << S3.IsNearPosLeftSide(P,1) << "," << S3.IsNearNegRightSide(P,1) << endl;
cout << S4.IsNearPosLeftSide(P,1) << "," << S4.IsNearNegRightSide(P,1) << endl;
cout << S5.IsNearPosLeftSide(P,1) << "," << S5.IsNearNegRightSide(P,1) << endl;
cout << S6.IsNearPosLeftSide(P,1) << "," << S6.IsNearNegRightSide(P,1) << endl;

//Contains
cout << endl << "Contains" << endl;
cout << S1.Contains(Point2D(5,5)) << endl;
cout << S1.Contains(Point2D(5,5.1)) << endl;
cout << S2.Contains(Point2D(3,0)) << endl;
cout << S2.Contains(Point2D(3,0.0001)) << endl;
cout << S3.Contains(Point2D(0,5)) << endl;
cout << S3.Contains(Point2D(0.00000000000001,5)) << endl;
cout << S4.Contains(Point2D(-2,2)) << endl;
cout << S4.Contains(Point2D(-1,0.999999999999)) << endl;

/***********************************************\
 *                   Polygon                   *
\***********************************************/
/*
cout << "***********************************************" << endl;
cout << "*                  Polygon                    *" << endl;
cout << "***********************************************" << endl;

Polygon P1;
Point2D P2D1(0,3), P2D2(3,6),P2D3(6,3),P2D4(3,0),P2D5,P2Dtemp;
Point2DVector PV;
double XL,XR,YD,YU;

//push_back
cout << "push_back" << endl;
P1.push_back(P2D1);
P1.push_back(P2D2);
P1.push_back(P2D3);
P1.push_back(P2D4);

//Show
cout << "Show" << endl;
P1.Show();

//pop_back
cout << "pop_back" << endl;
P1.pop_back();
P1.Show();
P1.pop_back();
P1.Show();
P1.pop_back();
P1.Show();
P1.pop_back();
P1.Show();
P1.pop_back();
P1.Show();

//Rectangle
cout << "Rectangle" << endl;
P1.push_back(P2D1);
P1.push_back(P2D2);
P1.push_back(P2D3);
P1.push_back(P2D4);
PV = P1.Rectangle(XL,XR,YD,YU); //(xl,xr,yd,yu)
printf("XL:%.30g,XR:%.30g,YD:%.30g,YU:%.30g\n",XL,XR,YD,YU);
PV.Show();

//Perimeter
cout << "Perimeter" << endl;
printf("%.30g\n",P1.Perimeter());

//Inside
cout << "Inside" << endl;
printf("%i\n",P1.Inside(Point2D(3,4)));
printf("%i\n",P1.Inside(Point2D(3,3)));
printf("%i\n",P1.Inside(Point2D(2,3)));
printf("%i\n",P1.Inside(Point2D(1,5)));
printf("%i\n",P1.Inside(Point2D(1,1)));
printf("%i\n",P1.Inside(Point2D(5,5)));
printf("%i\n",P1.Inside(Point2D(3,0)));
printf("%i\n",P1.Inside(Point2D(4,1)));
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

