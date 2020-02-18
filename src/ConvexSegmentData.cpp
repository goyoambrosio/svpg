/****
  SoftVision. Software for Computer Vision

  Gregorio Ambrosio Cestero (goyo@computer.org)
  System Engineering and Automation Department 
  University of Malaga. Spain                   

  $RCSfile: ConvexSegmentData.cpp,v $
  $Revision: 1.1 $
  $Date: 2000/01/21 13:04:00 $
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


// Point.cpp: implementation of the Point class.
//
//////////////////////////////////////////////////////////////////////

#include "ConvexSegmentData.h"

namespace GAC
{

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ConvexSegmentData::ConvexSegmentData()
{	//Inicialmente se inicializan las variables a cero.
	Dist  = 0.0;
	Angle = 0.0;
	Label = 0;
	S2A   = Point(0,0);
}

ConvexSegmentData::ConvexSegmentData(double dist, double angle, unsigned int label, Point P)
{
	Dist  = dist;
	Angle = angle;
	Label = label;
	S2A   = P;
}

ConvexSegmentData::~ConvexSegmentData()
{

}

//Setting
ConvexSegmentData &ConvexSegmentData::Set(double dist, double angle, unsigned int label, Point P)
{
	Dist  = dist;
	Angle = angle;
	Label = label;
	S2A   = P;
	return *this;
}

//Operators
bool operator== (const ConvexSegmentData& CSD1,const ConvexSegmentData& CSD2)
{
	return (CSD1.Dist  == CSD2.Dist)&&
		   (CSD1.Angle == CSD2.Angle)&&
		   (CSD1.Label == CSD2.Label)&&
		   (CSD1.S2A   == CSD2.S2A);
}

bool operator<  (const ConvexSegmentData& CSD1,const ConvexSegmentData& CSD2)
{
	return (CSD1.Dist < CSD2.Dist);
}


//Visualization
void ConvexSegmentData::Show()
{
	printf("Dist    : %.30g\n",Dist);
	printf("Angle   : %.30g\n",Angle);
	printf("Label   : %i\n",Label);
	S2A.Show();	
	printf("\n");
}

//Serialize
size_t ConvexSegmentData::Serialize(FILE * stream)
{
	size_t count   = 0;

	count += sizeof(double)*fwrite(&Dist, sizeof(double),1,stream);
	count += sizeof(double)*fwrite(&Angle, sizeof(double),1,stream);
	count += sizeof(unsigned int)*fwrite(&Label, sizeof(unsigned int),1,stream);
	count += S2A.Serialize(stream);

	return count;
}

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ConvexSegmentDataVector::ConvexSegmentDataVector()
{

}

ConvexSegmentDataVector::~ConvexSegmentDataVector()
{

}

//Visualization
void ConvexSegmentDataVector::Show()
{
	ConvexSegmentDataVector::iterator it;
	for (it = begin(); it != end(); it++)
	{
		(*it).Show();	
	}
	cout << endl;
}

//Serialize
size_t ConvexSegmentDataVector::Serialize(FILE * stream)
{
	size_t count  = 0;
	size_t SVsize = 0;

	SVsize = size();
	count += sizeof(size_t)*fwrite(&SVsize, sizeof(size_t),1,stream);

	ConvexSegmentDataVector::iterator it;
	for (it = begin(); it != end(); it++)
	{
		count += (*it).Serialize(stream);	
	}

	return count;
}


} //namespace GAC

