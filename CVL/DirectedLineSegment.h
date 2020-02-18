/****
  SoftVision. Software for Computer Vision

  Gregorio Ambrosio Cestero (goyo@computer.org)
  System Engineering and Automation Department 
  University of Malaga. Spain                   

  $RCSfile: Vector.h,v $
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

#if !defined(_DIRECTEDLINESEGMENT_H_)
#define _DIRECTEDLINESEGMENT_H_

#include <CVL/Line.h>
#include <CVL/Vector.h>

#include <stddef.h>					  // for size_t type
#include <map>
#include <vector>

using namespace std;

namespace GAC
{

/**************************************************************************\
 * Class DirectedLineSegment                     
\**************************************************************************/
class DirectedLineSegment : public Vector2D,public Line   
{
public:
	//Construction
	DirectedLineSegment():Line(),Vector2D(){};
	DirectedLineSegment(double Pi,double Pj, double Qi, double Qj):Line(Pi,Pj,Qi,Qj),Vector2D(Qi-Pi,Qj-Pj){P=Point2D(Pi,Pj);Q=Point2D(Qi,Qj);};
	DirectedLineSegment(Point2D P, Point2D Q):Line(P,Q),Vector2D(Q.x()-P.x(),Q.y()-P.y()){DirectedLineSegment::P=P;DirectedLineSegment::Q=Q;};
    virtual ~DirectedLineSegment();

	DirectedLineSegment &Set  (Point2D P, Point2D Q);
	DirectedLineSegment &Set  (double Pi,double Pj, double Qi, double Qj);
    DirectedLineSegment &SetP (Point2D P);
    DirectedLineSegment &SetP (double Pi,double Pj);
    DirectedLineSegment &SetQ (Point2D Q);
    DirectedLineSegment &SetQ (double Qi, double Qj);

	
	//Accesors
	Point2D p();
	Point2D q();

	//Operators
	bool operator==(DirectedLineSegment S);
	bool operator!=(DirectedLineSegment S);

	Point2D MidPoint();
    //Returns true if the point R belong to the segment.
    bool    Contains(Point2D R);
    //Returns the segment in the reverse direction
    //(P,Q) -> (Q,P)
    DirectedLineSegment Reverse();
    //Returns true if this segment overlaps with S.
    //If true, OS is the overlapped segment with the orientation
    //of this segment.
    bool    Overlap (DirectedLineSegment S, DirectedLineSegment & OS);


private:
	Point2D P,Q;
};

} //namespace GAC

#endif // !defined(_DIRECTEDLINESEGMENT_H_)
