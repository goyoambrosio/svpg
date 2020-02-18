/****
  SoftVision. Software for Computer Vision

  Gregorio Ambrosio Cestero (goyo@computer.org)
  System Engineering and Automation Department 
  University of Malaga. Spain                   

  $RCSfile: Point.h,v $
  $Revision: 1.1 $
  $Date: 2000/01/21 13:05:00 $
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


#if !defined(_POINT_H_)
#define _POINT_H_

#include <stdio.h>
#include <math.h>
#include <vector>
#include <string>                     //From SGI STL. For ios functions. It's like #include <iostream>

using namespace std;

#define PO		Point(0,0)

namespace GAC
{

/**************************************************************************\
 * Class Point                     
 * This class implements a Point in the n-dimensional plane
\**************************************************************************/
class Point:public vector<double>  
{
public:
	//Construction
	Point      ();
    Point      (unsigned int dim, ...);
   	Point &Set (unsigned int dim, ...);

	virtual ~Point();

	//Operations
	bool   operator== (Point P);
	bool   operator!= (Point P);
	bool   operator<  (Point P);
    double Distance   (Point P);    //Euclidean distance
    Point &Swap       (Point &P);

	//Visualization
	void	Show();
	friend  ostream &operator<<(ostream &s,const Point &P);

	//Serialize
//	virtual size_t Serialize(FILE * stream);
private:
	void SizeEqualize (Point i1, Point i2, Point &o1, Point &o2);
};



/**************************************************************************\
 * Class Point2D                     
 * This class implements a Point in xy plane
             ^
             |
             |
           y |
             |
             |
             *---------->
        (0,0)     x
\**************************************************************************/
class Point2D:public Point 
{
public:
	//Construction
	Point2D          ()                  :Point(2,0.0,0.0){};
	Point2D          (double x, double y):Point(2,x,y)    {};
	Point2D          (Point V);
	Point2D &Set     (double x, double y);
	Point2D &Setx    (double x);
	Point2D &Sety    (double y);
	virtual ~Point2D ();

	//Accesors
	double x();
	double y();

	//Operations
	Point2D &Rot      (double ang);	 //Non-clockwise rotation in radians. It modifies this Point
};

} //namespace GAC

#endif // !defined(_POINT_H_)
