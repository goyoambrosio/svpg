/****
  SoftVision. Software for Computer Vision

  Gregorio Ambrosio Cestero (goyo@computer.org)
  System Engineering and Automation Department 
  University of Malaga. Spain                   

  $RCSfile: Point.cpp,v $
  $Revision: 1.1 $
  $Date: 2000/01/21 13:04:59 $
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


#include <CVL/Point.h>

#include <stdarg.h>
#include <algorithm>

using namespace GAC;

/***********************************************\
 *                  Point                     *
\***********************************************/
//This function copies input Points i1,i2 into output Points o1,o2.
//Output Points have the same size as the longest input Point.
//The output Point corresponding with the shortest input Point is zero-padded
//It's useful to let operations among Points with non equal sizes.
void Point::SizeEqualize (Point i1, Point i2, Point &o1, Point &o2)
{

	if (i1.size() == i2.size()){
		o1.resize(i1.size());
		o2.resize(i2.size());
		copy(i1.begin(),i1.end(),o1.begin());
		copy(i2.begin(),i2.end(),o2.begin());
	}
	else if (i1.size() > i2.size()){
		o1.resize(i1.size());
		o2.resize(i1.size());
		copy(i1.begin(),i1.end(),o1.begin());
		fill(o2.begin(),o2.end(),0.0);
		copy(i2.begin(),i2.end(),o2.begin());
	}
	else if (i1.size() < i2.size()){
		o1.resize(i2.size());
		o2.resize(i2.size());
		copy(i2.begin(),i2.end(),o2.begin());
		fill(o1.begin(),o1.end(),0.0);
		copy(i1.begin(),i1.end(),o1.begin());
	}
}



Point::Point()
{

}

Point::Point(unsigned int dim, ...)
{
    double       val;
    unsigned int i;
    va_list      marker;

    va_start( marker, dim );     /* Initialize variable arguments. */
    for (i=0;i<dim;++i)
    {
      val = va_arg(marker, double);
      push_back(val);
    }
    va_end( marker );              /* Reset variable arguments.      */
   
}

Point &Point::Set(unsigned int dim, ...)
{
    double       val;
    unsigned int i;
    va_list      marker;

    clear();

    va_start( marker, dim );     /* Initialize variable arguments. */
    for (i=0;i<dim;++i)
    {
      val = va_arg(marker, double);
      push_back(val);
    }
    va_end( marker );              /* Reset variable arguments.      */
    return *this;
}

Point::~Point()
{

}


//Operators
bool Point::operator== (Point P)
{
	Point::iterator Pit1,Pit2;
	bool equal = true;

	if (size()!=P.size()) 
		return false;

	for (Pit1=begin(),Pit2=P.begin();
		 Pit1!=end();
		 Pit1++,Pit2++){
		equal = equal&&(*Pit1==*Pit2);
	}
	return equal;
}

bool Point::operator!= (Point P)
{
	return !((*this)==P);
}

//Needed due to the implementation as a specialization of the <vector> class
bool Point::operator<  (Point P)
{
	Point::iterator Pit1,Pit2;
	Point P1,P2;
	bool less = true;

	SizeEqualize (*this,P,P1,P2);

	for (Pit1=P1.begin(),Pit2=P2.begin();
		 Pit1!=P1.end();
		 Pit1++,Pit2++){
		less = less&&(*Pit1<*Pit2);
	}

	return less;
}

double Point::Distance (Point P){
	iterator Pit1,Pit2;
	Point P1,P2;
	double total = 0;

	SizeEqualize (*this,P,P1,P2);

	for (Pit1=P1.begin(),Pit2=P2.begin();
		 Pit1!=P1.end();
		 Pit1++,Pit2++){
		total += pow((*Pit1)-(*Pit2),2);
	}

	return sqrt(total);
}

Point &Point::Swap(Point &P){
	Point PAux;
	PAux = *this;
	*this = P;
	P = PAux;
	return *this;
}

//Visualization
void Point::Show(){
	iterator Pit;

    if (size()>0){
	    Pit = begin();
	    printf("(%.30g",*Pit);
	    Pit++;
	    for (;Pit!=end();Pit++){
		    printf(",%.30g",*Pit);
	    }
	    printf(")\n");
    }
}


ostream &GAC::operator<<(ostream &s, const Point &P)
{
    Point::const_iterator Pit;

    if (P.size()>0){
	    Pit = P.begin();
        s << "(" << *Pit;
	    Pit++;
	    for (;Pit!=P.end();Pit++){
            s << "," << *Pit;
	    }
        s << ")";
    }
	return s;
};

/*
//Serialize
size_t Point::Serialize(FILE * stream)
{
	const_iterator Pit;
	size_t count   = 0;

	for (Pit=begin();Pit!=end();Pit++){
		count += sizeof(double)*fwrite(Pit, sizeof(double),1,stream);
	}

	return count;
}
*/

/***********************************************\
 *                  Point2D                     *
\***********************************************/
//Setting
Point2D &Point2D::Set(double x, double y)
{
	clear();
	push_back(x);
	push_back(y);
	return *this;
}

Point2D &Point2D::Setx(double x)
{
	double y;
    y = (*this)[1];

	clear();
	push_back(x);
	push_back(y);
	return *this;
}

Point2D &Point2D::Sety(double y)
{
	double x;
    x = (*this)[0];

	clear();
	push_back(x);
	push_back(y);
	return *this;
}

Point2D::~Point2D()
{

}

//Accesors
double Point2D::x(){
	return (*this)[0];
}

double Point2D::y(){
	return (*this)[1];
}



Point2D &Point2D::Rot(double ang)
{
	double x,y,nx,ny;
	x = (*this)[0];
	y = (*this)[1];
	nx = x*cos(ang) - y*sin(ang);
	ny = x*sin(ang) + y*cos(ang);
	(*this)[0] = nx;
	(*this)[1] = ny;
	return *this;
}
