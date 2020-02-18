/****
  SoftVision. Software for Computer Vision

  Gregorio Ambrosio Cestero (goyo@computer.org)
  System Engineering and Automation Department 
  University of Malaga. Spain                   

  $RCSfile: GrayAHgraph.cpp,v $
  $Revision: 1.1 $
  $Date: 2000/01/21 13:04:27 $
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

#include <CVL/CGALgeometry.h>

/**************************************************************************\
*		                                                                   *
*		                    DEFINITIONS                                    *
*                                                                          *
\**************************************************************************/

using namespace GAC;
using namespace std;

/**************************************************************************\
		
  	  
		                   non-member functions


\**************************************************************************/

/********CGALPoint*********************************************************\
		
  	  
		                   class CGALPoint


\**************************************************************************/

/**************************************************************************\
* Name      : CGALPoint
* Member of : CGALPoint
* Purpose   : constructor
* Returns   :    
* Parameters: 
* Notes     :
* Author    : GAC
* Date      : 06.05.00
* Modified  :
\**************************************************************************/
CGALPoint::CGALPoint():Point_2<R>(){

}

/**************************************************************************\
* Name      : ~CGALPoint
* Member of : CGALPoint
* Purpose   : destructor
* Returns   :    
* Parameters: 
* Notes     :
* Author    : GAC
* Date      : 06.05.00
* Modified  :
\**************************************************************************/
CGALPoint::~CGALPoint(){

}

/**************************************************************************\
* Name      : CGALPoint
* Member of : CGALPoint
* Purpose   : copy constructor
* Returns   :    
* Parameters: 
* Notes     :
* Author    : GAC
* Date      : 06.05.00
* Modified  :
\**************************************************************************/
CGALPoint::CGALPoint(const CGALPoint& p):Point_2<R>((Point_2<R>&)p){

}

/**************************************************************************\
* Name      : CGALPoint
* Member of : CGALPoint
* Purpose   : conversion from implementation class object to interface class object
* Returns   :    
* Parameters:
*   p : base point of type Point_2<R>
* Notes     :
* Author    : GAC
* Date      : 06.05.00
* Modified  :
\**************************************************************************/
CGALPoint::CGALPoint(const Point_2<R>& p):Point_2<R>(p){

}

/**************************************************************************\
* Name      : CGALPoint
* Member of : CGALPoint
* Purpose   : constructor
* Returns   :    
* Parameters: 
* Notes     :
* Author    : GAC
* Date      : 06.05.00
* Modified  :
\**************************************************************************/
CGALPoint::CGALPoint(const Origin& o):Point_2<R>(o){

}

/**************************************************************************\
* Name      : CGALPoint
* Member of : CGALPoint
* Purpose   : constructor
* Returns   :    
* Parameters: 
*   hx : x coordinate
*   hy : y coordinate
* Notes     :
* Author    : GAC
* Date      : 06.05.00
* Modified  :
\**************************************************************************/
CGALPoint::CGALPoint(const RT& hx, const RT& hy):Point_2<R>(hx,hy){

}

/**************************************************************************\
* Name      : operator=
* Member of : CGALPoint
* Purpose   : copy constructor
* Returns   :    
* Parameters: 
*   p : source point
* Notes     :
* Author    : GAC
* Date      : 06.05.00
* Modified  :
\**************************************************************************/
CGALPoint& CGALPoint::operator=(const CGALPoint &p){
    Point_2<R>::operator=(p);
    return *this;
}

/**************************************************************************\
* Name      : operator<<
* Member of : CGALPoint
* Purpose   : overload of operator <<
* Returns   :    
* Parameters:
*   os: ostream 
*   p : source point
* Notes     :
* Author    : GAC
* Date      : 06.05.00
* Modified  :
\**************************************************************************/
ostream & GAC::operator<<(ostream &os, CGALPoint &p){
    os << "(" << p.x() << "," << p.y() << ")";
    return os;
}


/********CGALSegment*******************************************************\
		
  	  
		                   class CGALSegment


\**************************************************************************/
/**************************************************************************\
* Name      : CGALSegment
* Member of : CGALSegment
* Purpose   : constructor
* Returns   :    
* Parameters: 
* Notes     :
* Author    : GAC
* Date      : 06.05.00
* Modified  :
\**************************************************************************/
CGALSegment::CGALSegment(): Segment_2<R>(){
    d_label = 0;
}

/**************************************************************************\
* Name      : ~CGALSegment
* Member of : CGALSegment
* Purpose   : destructor
* Returns   :    
* Parameters: 
* Notes     :
* Author    : GAC
* Date      : 06.05.00
* Modified  :
\**************************************************************************/
CGALSegment::~CGALSegment(){

}

/**************************************************************************\
* Name      : CGALSegment
* Member of : CGALSegment
* Purpose   : copy constructor
* Returns   :    
* Parameters: 
* Notes     :
* Author    : GAC
* Date      : 06.05.00
* Modified  :
\**************************************************************************/
CGALSegment::CGALSegment(const CGALSegment& s):Segment_2<R>((Segment_2<R>&)s){
    d_label = s.d_label;
}

/**************************************************************************\
* Name      : CGALSegment
* Member of : CGALSegment
* Purpose   : conversion from implementation class object to interface class object
* Returns   :    
* Parameters:
*   s : base segment of type Segment_2<R>
* Notes     :
* Author    : GAC
* Date      : 06.05.00
* Modified  :
\**************************************************************************/
CGALSegment::CGALSegment(const Segment_2<R>& s):Segment_2<R>(s){
    d_label = 0;
}

/**************************************************************************\
* Name      : CGALSegment
* Member of : CGALSegment
* Purpose   : constructor
* Returns   :    
* Parameters: 
*   sp : source point
*   ep : end point
*   label : label of segment with 0 as default value (optional, see declaration)
* Notes     :
* Author    : GAC
* Date      : 06.05.00
* Modified  :
\**************************************************************************/
CGALSegment::CGALSegment(const CGALPoint &sp, const CGALPoint &ep,unsigned int label):Segment_2<R>(sp,ep){
    d_label = label;
}

/**************************************************************************\
* Name      : operator=
* Member of : CGALSegment
* Purpose   : copy constructor
* Returns   :    
* Parameters: 
*   s : source segment
* Notes     :
* Author    : GAC
* Date      : 06.05.00
* Modified  :
\**************************************************************************/
CGALSegment& CGALSegment::operator=(const CGALSegment &s){
    d_label = s.d_label;
    Segment_2<R>::operator=(s);
    return *this;
}

/**************************************************************************\
* Name      : operator<<
* Member of : CGALSegment
* Purpose   : overload of operator <<
* Returns   :    
* Parameters:
*   os: ostream 
*   s : source segment
* Notes     :
* Author    : GAC
* Date      : 06.05.00
* Modified  :
\**************************************************************************/
ostream & GAC::operator<<(ostream &os, CGALSegment &s){
    CGALPoint sp,ep;

    sp = s.vertex(0);
    ep = s.vertex(1);
    os << s.d_label << ":" << sp << "->" << ep << endl;
    return os;
}
