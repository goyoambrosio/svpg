/****
  SoftVision. Software for Computer Vision

  Gregorio Ambrosio Cestero (goyo@computer.org)
  System Engineering and Automation Department 
  University of Malaga. Spain                   

  $RCSfile: Polygon.h,v $
  $Revision: 1.1 $
  $Date: 2000/01/21 13:05:01 $
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

#if !defined(_POLYGON_H_)
#define _POLYGON_H_

#include <CVL/DirectedLineSegment.h>

#include <stdio.h>

#include <map>

using namespace std;

namespace GAC
{

class Polygon : public Point2DVector
{
public:
	Polygon();
	virtual ~Polygon();

   	void push_back(const Point2D & P);
	void pop_back();
    //True si la secuencia de puntos PointVector forma un polígono correcto
	bool isValid();
	//Devuelve un vector con los puntos de las cuatro esquinas del rectángulo 
    //en el que está inscrito el polígono
	Point2DVector Rectangle(double & IU, //IU : coor i up
		                    double & ID, //ID : coor i down
						    double & JL, //IU : coor j left
						    double & JR);//IU : coor j right 
    //Devuelve el perímetro del polígono.
	double Perimeter();
    //True si el punto P está dentro de del polígono
	bool Inside(Point2D P);

   	//Visualization
	void Show();


private:
    class DirectedLineSegmentMap:public map <unsigned int, DirectedLineSegment>{
    public:
	    DirectedLineSegmentMap();
	    virtual ~DirectedLineSegmentMap();
	    //Visualization
	    void Show();
	    //Serialize
//	    size_t Serialize(FILE * stream);
     };

private:
    bool CheckVBase(Point2D P,DirectedLineSegment VBase);

private:
    DirectedLineSegmentMap Sides;


};


} //namespace GAC

#endif // !defined(_POLYGON_H_)
