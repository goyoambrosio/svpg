/****
  SoftVision. Software for Computer Vision

  Gregorio Ambrosio Cestero (goyo@computer.org)
  System Engineering and Automation Department 
  University of Malaga. Spain                   

  $RCSfile: ConvexPerceptualGroup.h,v $
  $Revision: 1.1 $
  $Date: 2000/01/21 13:03:58 $
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


// ConvexPerceptualGroup.h: interface for the PerceptualGroup class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(_CONVEXPERCEPTUALGROUP_H_)
#define _CONVEXPERCEPTUALGROUP_H_

// The debugger can't handle symbols more than 255 characters long.
// STL often creates symbols longer than that.
// When symbols are longer than 255 characters, the warning is disabled.
#pragma warning(disable:4786)

#include "Segment.h"
#include "LabelVector.h"
#include "PerceptualGroup.h"
#include "Error.h"

namespace GAC
{

class ConvexPerceptualGroup : public PerceptualGroup
{
public:
	ConvexPerceptualGroup();
	virtual ~ConvexPerceptualGroup();

	//Serialize
	size_t Serialize(FILE * stream);
	size_t FeatureVectorSerialize(FILE * stream);

	//Visualization
	void Show(SegmentMap BaseSM);
	void ShowMoments();

	ConvexPerceptualGroup push_back(Relation R);
	ConvexPerceptualGroup pop_back();
	ConvexPerceptualGroup clear();

	double GetL1n (SegmentMap BaseSM);
	void GetG1n (double * G);
//	void GetG1nminus1(double * G);
	double GetAngle1n();
	double GetSalienceFraction(SegmentMap BaseSM);

	bool IsClosed();

	ConvexPerceptualGroup & SetSalience(const SegmentMap &SM);
	ConvexPerceptualGroup & SetPerimeter();
	ConvexPerceptualGroup & SetArea();
	ConvexPerceptualGroup & SetBinCentroid();
	ConvexPerceptualGroup & SetGrayCentroid(UcharMatrix Retina);
	ConvexPerceptualGroup & SetThirdOrderCentralMoments(UcharMatrix Retina); //Momentos centrales de orden 0,1,2,3 en el siguiente orden m00,m01,m10,m02,m11,m20,m03,m12,m21,m30
	ConvexPerceptualGroup & SetFeatureVector(UcharMatrix Retina,SegmentMap SM);
	ConvexPerceptualGroup & SetPolarity(const SegmentMap & SM);

	double GetSalience();
	double GetPerimeter();
	double GetArea();
	Point  GetBinCentroid();
	Point  GetGrayCentroid();

	double Getcm00();
	double Getcm01();
	double Getcm10();
	double Getcm02();
	double Getcm11();
	double Getcm20();
	double Getcm03();
	double Getcm12();
	double Getcm21();
	double Getcm30();

	double Getncm02();
	double Getncm11();
	double Getncm20();
	double Getncm03();
	double Getncm12();
	double Getncm21();
	double Getncm30();
	nCompVector GetFeatureVector();
	int GetPolarity();

//Private Data
private:
	bool   Closed;
	Error CPGError;

	double Perimeter;
	double Area;
	Point  BinCentroid;
	Point  GrayCentroid;
	double cm00,cm01,cm10,cm02,cm11,cm20,cm03,cm12,cm21,cm30; //Central moments
	double ncm02,ncm11,ncm20,ncm03,ncm12,ncm21,ncm30; //Normalized central moments
	int    Polarity; //Polaridad del CPG que es la misma que la polaridad de los segmentos que lo componen
	double Salience; //Salience del CPG

private:
	double m1(double p,double q,UcharMatrix Retina,BoolMatrix BinMatrix, int iIU,int iID,int iJL,int iJR);
	double m2(double p,double q,UcharMatrix Retina,BoolMatrix BinMatrix, int iIU,int iID,int iJL,int iJR,double lic,double ljc);

};

typedef map <LabelVector, ConvexPerceptualGroup> mConvexPerceptualGroup;

class ConvexPerceptualGroupMap : public mConvexPerceptualGroup
{
public:
	ConvexPerceptualGroupMap();
	virtual ~ConvexPerceptualGroupMap();

	//Visualization
	void Show(SegmentMap BaseSM);

	//Serialize
	size_t Serialize(FILE * stream);
	size_t FeatureVectorSerialize(FILE * stream);

};

typedef vector <ConvexPerceptualGroup> vConvexPerceptualGroup;

class ConvexPerceptualGroupVector : public vConvexPerceptualGroup
{
public:
	ConvexPerceptualGroupVector();
	virtual ~ConvexPerceptualGroupVector();

	//Visualization
	void Show(SegmentMap BaseSM);

	//Serialize
	size_t Serialize(FILE * stream);

};

} //namespace GAC




#endif // !defined(_CONVEXPERCEPTUALGROUP_H_)