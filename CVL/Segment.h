/****
  SoftVision. Software for Computer Vision

  Gregorio Ambrosio Cestero (goyo@computer.org)
  System Engineering and Automation Department 
  University of Malaga. Spain                   

  $RCSfile: ImgSegment.h,v $
  $Revision: 1.1 $
  $Date: 2000/01/21 13:04:36 $
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


// ImgSegment.h: interface for the ImgSegment class.
//
// (c)1998. Gregorio Ambrosio Cestero
// Build 1 (17.Apr.98)
//////////////////////////////////////////////////////////////////////

#if !defined(_IMGSEGMENT_H_)
#define _IMGSEGMENT_H_

// The debugger can't handle symbols more than 255 characters long.
// STL often creates symbols longer than that.
// When symbols are longer than 255 characters, the warning is disabled.
#pragma warning(disable:4786)

#include <vector>

//#include <stddef.h>					  // for size_t type
//#include "Vector.h"
//#include "AffGraph.h"
//#include "LabelVector.h"

#include <CVL/Vector.h>

namespace GAC
{

class ImgSegment : public Vector  
{
public:
	//Construction
	ImgSegment():Vector(){};
	ImgSegment(float Ai,float Aj, float Bi, float Bj):Vector(Ai,Aj,Bi,Bj){A.Set(Ai,Aj);B.Set(Bi,Bj);};
	ImgSegment(Point PA, Point PB):Vector(PA,PB){A=PA;B=PB;};

	//Operators
	friend bool operator== ( const ImgSegment& S1, const ImgSegment& S2);
	friend bool operator<  ( const ImgSegment& S1, const ImgSegment& S2);

	Point		 GetA();
	Point		 GetB();

	double EndPointDistance(const ImgSegment& S);
	double MidPointDistance(const ImgSegment& S);
	double OverlapMod(const ImgSegment& S);

	//Visualization
	void Show();
	//friend std::ostream &operator<<(std::ostream &s, ImgSegment &Saux);

	//Serialize
	size_t Serialize(FILE * stream);

public:
	//Public data
	unsigned int Label;			//Etiqueta identificativa del segmento

private:
	Point		 A;
	Point		 B;

};

typedef ImgSegment* pImgSegment;

class PerceptualGroup; //Early definition

class ImgSegmentVector : public vector <ImgSegment>
{
public:
	ImgSegmentVector();
	virtual ~ImgSegmentVector();

	AffGraph<pImgSegment> EndPointDistanceGraph();
	AffGraph<pImgSegment> MidPointDistanceGraph();
	AffGraph<pImgSegment> ShortAngleGraph();
	AffGraph<pImgSegment> OverlapModGraph();

	DoubleMatrix EndPointDistanceMatrix();
	DoubleMatrix MidPointDistanceMatrix();
	DoubleMatrix ShortAngleMatrix();
	DoubleMatrix OverlapModMatrix();
	

	void ParallelGraph	(AffGraph<pImgSegment> & DistanceGraph,
						 AffGraph<pImgSegment> & AngleGraph,
						 AffGraph<pImgSegment> & OverlapGraph,
						 double MaxDistance,double MinDistance,double MaxAngle);

	void CollinearGraph (AffGraph<pImgSegment> & DistanceGraph, 
						 double MaxDistance,double MaxAngle,double MaxParallelDistance = 1.0);

	void ConvexGraph    (AffGraph<pImgSegment> & DistanceGraph,
						 AffGraph<pImgSegment> & ClockwiseAngleGraph,
						 AffGraph<pImgSegment> & CircularityGraph, 
						 double MaxDistance,double MaxNoConvexityThreshold = 3.0);

	AffGraph<pImgSegment> ProximityAffGraph (double MaxDistance,double d0p = 0.5);
	AffGraph<pImgSegment> ParallelAffGraph  (double MaxDistance,double MaxAngle);
	AffGraph<pImgSegment> CollinearAffGraph (double MaxDistance,double MaxAngle,double MaxParallelDistance = 1.0);

	ImgSegmentVector ExtractSegmentsFromTJunctions (double          MinMod                  = 20,
												  double          MaxDistBetwConvexSegments = 30,
							                      double          MaxNoConvexityThreshold   = 3.0,
							                      bool            JacobExtension_1 = true,
							                      bool            JacobExtension_2 = true,
												  bool            IncludeOriginal  = true);
	ImgSegmentVector TwoOrientation();

	map <Label,PerceptualGroup> ParallelGrouping(double MaxDistance,double MaxAngle);

	//Visualization
	void Show();

};

class pImgSegmentVector : public vector <pImgSegment>
{
public:
	pImgSegmentVector();
	virtual ~pImgSegmentVector();

	//Visualization
	void Show();

	//Serialize
	size_t Serialize(FILE * stream);
};

class PerceptualGroup : public pImgSegmentVector
{
public:
	PerceptualGroup();
	virtual ~PerceptualGroup();

};


typedef map <unsigned int, ImgSegment> mImgSegment;

class ImgSegmentMap : public mImgSegment
{
public:
	ImgSegmentMap();
	virtual ~ImgSegmentMap();

	//Visualization
	void Show();
	//Serialize
	size_t Serialize(FILE * stream);

};

} //namespace GAC

#endif // !defined(_IMGSEGMENT_H_)
