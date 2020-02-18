/****
  SoftVision. Software for Computer Vision

  Gregorio Ambrosio Cestero (goyo@computer.org)
  System Engineering and Automation Department 
  University of Malaga. Spain                   

  $RCSfile: Vector.cpp,v $
  $Revision: 1.1 $
  $Date: 2000/01/21 13:05:21 $
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

#include <CVL/DirectedLineSegment.h>

using namespace GAC;

DirectedLineSegment::~DirectedLineSegment()
{

}

DirectedLineSegment &DirectedLineSegment::Set (Point2D P, Point2D Q)
{
	Line::Set(P,Q);
	Vector2D::Set(Q.x()-P.x(),Q.y()-P.y());
	DirectedLineSegment::P=P;
	DirectedLineSegment::Q=Q;
	return *this;
}

DirectedLineSegment &DirectedLineSegment::Set  (double Pi,double Pj, double Qi, double Qj)
{
	Line::Set(Pi,Pj,Qi,Qj);
	Vector2D::Set(Qi-Pi,Qj-Pj);
	P.Set(Pi,Pj);
	Q.Set(Qi,Qj);
	return *this;
}

DirectedLineSegment &DirectedLineSegment::SetP (Point2D P)
{
	Line::Set(P,Q);
	Vector2D::Set(Q.x()-P.x(),Q.y()-P.y());
	DirectedLineSegment::P=P;
	return *this;
}

DirectedLineSegment &DirectedLineSegment::SetP (double Pi,double Pj)
{
    Point2D P(Pi,Pj);
	Line::Set(P,Q);
	Vector2D::Set(Q.x()-P.x(),Q.y()-P.y());
	DirectedLineSegment::P=P;
	return *this;
}

DirectedLineSegment &DirectedLineSegment::SetQ (Point2D Q)
{
	Line::Set(P,Q);
	Vector2D::Set(Q.x()-P.x(),Q.y()-P.y());
	DirectedLineSegment::Q=Q;
	return *this;
}

DirectedLineSegment &DirectedLineSegment::SetQ (double Qi, double Qj)
{
    Point2D Q(Qi,Qj);
	Line::Set(P,Q);
	Vector2D::Set(Q.x()-P.x(),Q.y()-P.y());
	DirectedLineSegment::Q=Q;
	return *this;
}

Point2D DirectedLineSegment::p(){return P;};
Point2D DirectedLineSegment::q(){return Q;};

//Operators
bool DirectedLineSegment::operator==(DirectedLineSegment S){
	return(P==S.P && Q==S.Q);
}

bool DirectedLineSegment::operator!=(DirectedLineSegment S){
	return(P!=S.P || Q!=S.Q);
}

//Punto medio del DirectedLineSegment
Point2D DirectedLineSegment::MidPoint()
{
	Point2D M;
	M.Setx((P.x()+Q.x())/2.0);
	M.Sety((P.y()+Q.y())/2.0);
	return M;
}

bool DirectedLineSegment::Contains(Point2D R)
{
	double DistRP, DistRQ, DistPQ;

	DistRP = P.Distance(R); //P.Distance(A);
	DistRQ = Q.Distance(R); //P.Distance(B);
	DistPQ = P.Distance(Q); //Mod();
	return fabs((DistPQ-(DistRP+DistRQ)))<1.0e-10;
}

DirectedLineSegment DirectedLineSegment::Reverse(){
    DirectedLineSegment S(Q,P);
    return S;
}

bool DirectedLineSegment::Overlap(DirectedLineSegment S, DirectedLineSegment & OS){

    Point2D AuxP,PA,PB,PSA,PSB;
	DirectedLineSegment AuxS;

	PA = P;
	PB = Q;
	PSA = S.P;
	PSB = S.Q;

	if (Line::Contains(PSA)&&Line::Contains(PSB)){
		if (Contains(PSA) && Contains(PSB))
			AuxS = S;
		else if (S.Contains(PA) && S.Contains(PB))
			AuxS = *this;
		else if (Contains(PSA) && !Contains(PSB)){
			if (S.Contains(PA))
				AuxS.Set(PSA,PA);
			else if (S.Contains(PB))
				AuxS.Set(PSA,PB);
		}
		else if (Contains(PSB) && !Contains(PSA)){
			if (S.Contains(PA))
				AuxS.Set(PSB,PA);
			else if (S.Contains(PB))
				AuxS.Set(PSB,PB);
		}
		else return false;
	}
	else {
		return false;
	}
	
    if (abs(Vector2D::Angle(AuxS)-PI) < Epsilon) 
        OS = AuxS.Reverse();
    else
	    OS = AuxS;
	return true;
}
