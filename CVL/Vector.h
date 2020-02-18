/****
  SoftVision. Software for Computer Vision

  Gregorio Ambrosio Cestero (goyo@computer.org)
  System Engineering and Automation Department 
  University of Malaga. Spain                   

  $RCSfile: CompVector.h,v $
  $Revision: 1.1 $
  $Date: 2000/01/21 13:03:56 $
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


#if !defined(_VECTOR_H_)
#define _VECTOR_H_

#include <CVL/Globals.h>

#include <stdio.h>
#include <vector>
#include <string>                     //From SGI STL. For ios functions. It's like #include <iostream>

using namespace std;

namespace GAC
{

/**************************************************************************\
 * Class Vector                     
 * This class implements Vectors by components, i.e. n-dimensional vectors
\**************************************************************************/

class Vector:public vector<double>  
{
public:
	//Construction
	Vector      ();
    Vector      (unsigned int dim, ...);
   	Vector &Set (unsigned int dim, ...);

	virtual ~Vector();

	//Operations
	bool          operator==  (Vector V);
	bool          operator!=  (Vector V);
	bool          operator<   (Vector V);                  //Magnitude comparison
	bool          operator>   (Vector V);                  //Magnitude comparison
	bool          operator<=  (Vector V);                  //Magnitude comparison
	bool          operator>=  (Vector V);                  //Magnitude comparison
    friend double operator*   (Vector Vl,Vector Vr);       //Same as Dot function
	friend Vector operator*   (Vector V, double val);      //Product by a scalar
	friend Vector operator*   (double val, Vector V);      //Product by a scalar
	friend Vector operator/   (Vector V, double val);      //Division by a scalar
	friend Vector operator/   (double val, Vector V);      //Division by a scalar
	Vector	      operator+   (Vector V);
	Vector	      operator-   (Vector V);
    double		  Dot         (Vector V);        //Dot product/Scalar product
	Vector	      Unit        ();                //Base vector
	double		  Norm        ();                //Norm/Magnitude/Length/Module
	double		  Mod         ();                //Norm/Magnitude/Length/Module
	double		  Length      ();                //Norm/Magnitude/Length/Module
//	double		  EuclideanDistance (Vector V);  


	//Visualization
	void	Show();
	friend  ostream &operator<<(ostream &s,const Vector &V);

	//Serialize
//	virtual size_t Serialize(FILE * stream);
private:
	void SizeEqualize (Vector i1, Vector i2, Vector &o1, Vector &o2);

};


/**************************************************************************\
 * Class Vector2D                     
 * This class implements two dimensional Vectors in xy-plane (xi + yj):(x,y)
\**************************************************************************/
class Vector2D:public Vector  
{
public:
	//Construction
	Vector2D          ()                  :Vector(2,0.0,0.0){};
	Vector2D          (double x, double y):Vector(2,x,y)    {};
	Vector2D          (Vector V);
	Vector2D &Set     (double x, double y);
	virtual ~Vector2D ();

	//Accesors
	double x();
	double y();

	//Operations
	double      Cross          (Vector2D V);  //Vectorial product
	Vector2D    Normal         ();            //Normal vector
	double		Angle          (Vector2D V);  // 0 <= angle <= PI
	double		ShortAngle     (Vector2D V);  // 0 <= angle <= PI/2 Smallest angle needed to set V in the same direction of current vector.
	double		ClockwiseAngle (Vector2D V);  // 0 <= angle <= PI   Angle needed to rotate current vector in a clockwise fashion to reach angle V
	double		OrderedAngle   (Vector2D V);  //-PI<= angle <= PI   Angle needed to rotate current vector to reach V vector. When angle is negative we are doing it in a anticlockwise fashion. Clockwise if angle is positive.
};

} //namespace GAC

#endif // !defined(_VECTOR_H_)
