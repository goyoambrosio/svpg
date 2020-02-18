/****
  SoftVision. Software for Computer Vision

  Gregorio Ambrosio Cestero (goyo@computer.org)
  System Engineering and Automation Department 
  University of Malaga. Spain                   

  $RCSfile: ConvexSegmentData.h,v $
  $Revision: 1.1 $
  $Date: 2000/01/21 13:04:01 $
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


// ConvexSegmentData.h: interface for the ConvexSegmentData class.
//
// (c)1998. Gregorio Ambrosio Cestero
// Rv.1 (31.Aug.98)
//////////////////////////////////////////////////////////////////////

#if !defined(_CONVEXSEGMENTDATA_H_)
#define _CONVEXSEGMENTDATA_H_

#include <iostream.h>                 // for i/o functions
#include <stdio.h>
#include "Point.h"
#include <vector>

namespace GAC
{

class ConvexSegmentData  
{
public:
	//Construction
	ConvexSegmentData();
	ConvexSegmentData(double dist, double angle, unsigned int label, Point P);
	virtual ~ConvexSegmentData();

	//Operators
	friend bool operator== (const ConvexSegmentData& CSD1,const ConvexSegmentData& CSD2);
	friend bool operator<  (const ConvexSegmentData& CSD1,const ConvexSegmentData& CSD2);

	//Setting
	ConvexSegmentData &Set(double dist, double angle, unsigned int label, Point P);

	//Visualization
	void Show();

	//Serialize
	virtual size_t Serialize(FILE * stream);


public:
	//Public data
	double       Dist;
	double       Angle;
	unsigned int Label;
	Point	     S2A;
};

typedef vector <ConvexSegmentData> vConvexSegmentData;

class ConvexSegmentDataVector : public vConvexSegmentData 
{
public:
	ConvexSegmentDataVector();
	virtual ~ConvexSegmentDataVector();

	//Visualization
	void Show();

	//Serialize
	size_t Serialize(FILE * stream);
};

} //namespace GAC

#endif // !defined(_CONVEXSEGMENTDATA_H_)
