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


#if !defined(_CGALPOINT_H_)
#define _CGALPOINT_H_

#include <CVL/Point.h>
#include <CVL/CGALgeometry.h>

#include <CGAL/Point_2.h>

using namespace CGAL;

namespace GAC
{

///////////////////////////////////
// Class CGALPoint
//////////////////////////////////
class CGALPoint : public Point_2<R> 
{
public:
	//Constructors

    CGALPoint();
    CGALPoint(const CGALPoint& p);
    CGALPoint(const Point_2<R>& p);
    CGALPoint(const Origin& o);
    CGALPoint(const RT& hx, const RT& hy);

    virtual ~CGALPoint();

    CGALPoint& operator=(const CGALPoint &p);

    friend std::ostream & operator<<(std::ostream &os, CGALPoint &p);
};


} //namespace GAC

#endif // !defined(_CGALPOINT_H_)
