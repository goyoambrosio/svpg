/****
  SoftVision. Software for Computer Vision

  Gregorio Ambrosio Cestero (goyo@computer.org)
  System Engineering and Automation Department 
  University of Malaga. Spain                   

  $RCSfile: GrayImage.h,v $
  $Revision: 1.1 $
  $Date: 2000/01/21 13:04:28 $
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
/**************************************************************************\
* Name      :
* Member of : 
* Purpose   : 
* Returns   :    
* Parameters: 
* Notes     :
* Author    : 
* Date      : 
* Modified  :
\**************************************************************************/


#if !defined(_CGALSEGMENT_H_)
#define _CGALSEGMENT_H_

#include <CVL/Image.h>
#include <CVL/CGALgeometry.h>
#include <CVL/CGALpoint.h>

#include <CGAL/Segment_2.h>

using namespace CGAL;
using namespace std;

namespace GAC
{

///////////////////////////////////
// Class CGALSegment
//////////////////////////////////
class CGALSegment : public Segment_2<R> 
{
public:
	//Constructors
    CGALSegment();
    CGALSegment(const CGALSegment& s);
    CGALSegment(const Segment_2<R>& s);
    CGALSegment(const CGALPoint &sp, const CGALPoint &ep,unsigned int label = 0,leda_color color = leda_black);
    CGALSegment& operator=(const CGALSegment &s);

    virtual ~CGALSegment();

    CGALPoint p();
    CGALPoint q();

    Image::Segment GetImageSegment();

    //Operators
	bool operator< (const CGALSegment &s);
    friend std::ostream & operator<<(std::ostream &os, CGALSegment &s);
    friend leda_window  & operator<<(leda_window& w, const CGALSegment& s);
/*
    // Computes the minimum distance between the nearest endpoints of segments
	double EndPointDistance(Segment& S);
    // Computes the minimum distance between midpoint of segments
	double MidPointDistance(Segment& S);
    //Computes the module of the overlapping between this segment and the perpendicular 
    //projection of S over this segment
	double OverlapMod      (Segment& S);

	//Visualization
	void Show();
//        friend ostream &operator<<(std::ostream &s, Segment &S);

    friend std::ostream & operator<<(std::ostream &os, CGALSegment &s){
        os << s.Label << ":" << s.vertex(0) << "->" << s.vertex(1) << std::endl;
        return os;
    }
*/

public:
	//Public data
	unsigned int d_label;			//Etiqueta identificativa del segmento
    leda_color   d_color;

};


///////////////////////////////////
// Class CGALSegmentVector
//////////////////////////////////
class CGALSegmentVector : public vector <CGALSegment>
{
public:
    //Constructor
    CGALSegmentVector();
    virtual ~CGALSegmentVector();

	//Visualization
    friend ostream     &operator<<(ostream &s, CGALSegmentVector &sv);
    friend leda_window &operator<<(leda_window& w, CGALSegmentVector& sv);
};

///////////////////////////////////
// Class CGALpSegmentVector
//////////////////////////////////
class CGALpSegmentVector : public vector <CGALSegment*>
{
public:
    //Constructor
    CGALpSegmentVector();
    virtual ~CGALpSegmentVector();

	//Visualization
    friend ostream     &operator<<(ostream &s, CGALpSegmentVector &sv);
    friend leda_window &operator<<(leda_window& w, CGALpSegmentVector& sv);
};

} //namespace GAC

#endif // !defined(_CGALSEGMENT_H_)
