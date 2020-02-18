/****
  SoftVision. Software for Computer Vision

  Gregorio Ambrosio Cestero (goyo@computer.org)
  System Engineering and Automation Department 
  University of Malaga. Spain                   

  $RCSfile: Globals.h,v $
  $Revision: 1.1 $
  $Date: 2000/01/21 13:04:25 $
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


#if !defined(_GLOBALS_H_)
#define _GLOBALS_H_

#include <limits>
#include <math.h>

#define			PI				3.1415926535897931 //3.141592653589793238462643
#define			TWO_PI			6.2831853071795862
#define			THREE_HALF_PI	4.7123889803846897
#define			HALF_PI			1.5707963267948966
#define			QUARTER_PI		0.78539816339744828

#define			EPSILON_PI		 0.017453292519943295 // 1 grade
#define			ONE_GRADE_IN_RAD 0.017453292519943295 // 1 grade


#define			Epsilon       FLT_MIN
#define			DoubleEpsilon 1.0e-12
#define rad(x)	(((double) x*PI)/180)
#define grad(x) (((double) x*180)/PI)

#define min(a, b)  (((a) < (b)) ? (a) : (b)) 
#define max(a, b)  (((a) > (b)) ? (a) : (b)) 

namespace GAC
{

double Round	    (double n);
double RoundDouble	(double n);
void   CuadRoot	    (double a, double b, double c, double &r1, double &r2);
double Gauss        (double n, double Sigma);
double MyHypot      (double x, double y);

} //namespace GAC

#endif // !defined(_GLOBALS_H_)
