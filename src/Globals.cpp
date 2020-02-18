/****
  SoftVision. Software for Computer Vision

  Gregorio Ambrosio Cestero (goyo@computer.org)
  System Engineering and Automation Department 
  University of Malaga. Spain                   

  $RCSfile: Globals.cpp,v $
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


#include <CVL/Globals.h>

//using namespace GAC; //No funciona, tengo que poner el cualificador GAC:: delante.
                       //No estoy seguro si es una inconsistencia del compilador o es
                       //algo de C++ que no conozco.

double GAC::Round(double n) {
	double a,b,c;
	a = floor(n);
	b = n-a;
	(b<0.5) ? (c=a) : (c=a+1);
	return c;
}

double GAC::RoundDouble(double n) {
	double a,b,c;
	a = floor(n);
	b = n-a;
	(b<0.00005) ? (c=a) : (c=a+0.0001);
	return c;
}

// Resuelve la ecuación cuadratica ax^2 + bx + c = 0
// r1 es la raiz positiva
// r2 es la raiz negativa
void GAC::CuadRoot(double a, double b, double c, double &r1, double &r2) {
	r1 = (-b + sqrt(pow(b,2) - 4*a*c))/(2*a);
	r2 = (-b - sqrt(pow(b,2) - 4*a*c))/(2*a);
}

//Funcion Gaussiana centrada en el origen e ignorando el factor
// 1/(Sigma*sqrt(2*PI))
double GAC::Gauss(double n, double Sigma)
{
	return exp((-n*n)/(2*Sigma*Sigma));
}

//Funcion para el calculo de la hipotenusa
double GAC::MyHypot(double x, double y)
{
	if (x==0.0 && y==0.0) return 0.0;
	else return(hypot(x,y));
}

