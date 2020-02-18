/****
  SoftVision. Software for Computer Vision

  Gregorio Ambrosio Cestero (goyo@computer.org)
  System Engineering and Automation Department 
  University of Malaga. Spain                   

  $RCSfile: StraightLine.h,v $
  $Revision: 1.1 $
  $Date: 2000/01/21 13:05:10 $
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

#if !defined(_LINE_H_)
#define _LINE_H_

#include <CVL/Point.h>
#include <CVL/Globals.h>

#include <stdio.h>
#include <vector>

using namespace std;

namespace GAC
{

/**************************************************************************\
 * Class Line                     
 * This class implements a Line and the corresponding geometric methods
\**************************************************************************/
class Line
{
public:
	//Constructors
	Line ();
	Line (double m,double n);                         //Forma de ecuación reducida   y = mx+n
	Line (Point2D p1, Point2D p2);                    //Forma de ecuación de la recta que pasa por dos puntos
	Line (double x1,double y1, double x2, double y2); //Forma de ecuación de la recta que pasa por dos puntos
	Line (double a,double b,double c);                //Forma de ecuación parametrica  ax + by + c  = 0
//	Line (double d, double sigma);                    //Forma de ecuación normal   x*cos(sigma)+y*sin(sigma)=d
                                                      //Presenta una ambiguedad con la declaración de la forma reducida Line (double m,double n);

	Line &Set      (double m,double n);                         //Forma de ecuación reducida   y = mx+n
	Line &Set      (Point2D p1, Point2D p2);                    //Forma de ecuación de la recta que pasa por dos puntos
	Line &Set      (double x1,double y1, double x2, double y2); //Forma de ecuación de la recta que pasa por dos puntos
	Line &Set      (double a,double b,double c);                //Forma de ecuación parametrica  ax + by + c  = 0
	Line &SetNormal(double d, double sigma);                    //Forma de ecuación normal   x*cos(sigma)+y*sin(sigma)=d

	virtual ~Line();

	//Operators
	bool operator== (const Line& L1);
	bool operator<  (const Line& L1);

	//Operations
	double y(double x);	//Evalua y para x, es decir, y=f(x)
	double x(double y);	//Evalua x para y

	//Attributes
	//Parámetros de la recta en su forma de ecuación reducida   y = mx+n  m=tan(Fi)
	double m    ();			//Devuelve M
	double n    ();			//Devuelve N
	double Fi   ();			//Devuelve Fi (-PI/2 .. PI/2),es decir, el ángulo que forma con el eje de ordenadas
	double PosFi();			//Devuelve Fi (0 .. PI)
	//Parámetros de la recta portadora en su forma de ecuación normal   x*cos(sigma)+y*sin(sigma)=d
	double Sigma();			//Devuelve Sigma
	double d    ();			//Devuelve D
	//Parámetros de la recta portadora en su forma de ecuación parametrica  ax + by + c  = 0
	double a();				//Devuelve A
	double b();				//Devuelve B
	double c();				//Devuelve C
	
	//Informacion de verticalidad u horizontalidad	
	int   isVertical();		//True si la línea es vertical. Devuelve VERT
	int   isHorizontal();	//True si la línea es horizontal. Devuelve HOR

	//Relaciones con otros elementos
	double		 Distance	        (Point2D P);         //Devuelve la distancia del punto (i,j) a la recta (¡¡¡ojo!!! está mal pero sirve para la detección de segmentos)
	double		 EuclideanDistance	(const Point2D & P); //Devuelve la distancia euclidea del punto (i,j) a la recta
	double		 Angle		        (const Line & L);    //Devuelve el angulo que forma con otra recta (<=PI/2)
	Line         PerpLine	        (Point2D P);		 //Devuelve la recta perpendicular que pasa por el punto P
	bool		 isParallel	        (Line L);            //Devuelve true si es paralela con SLaux, false en caso contario
	Point2D		 Intersection       (Line L);            //Devuelve el punto donde intersecta con SLaux

	//EquidistantPointsInLine
	//Devuelve un punto perteneciente a la recta que esta a una distancia
	//D del punto (x,y).
	//Solo se pasa la coordenada x del punto de referencia para asegurar
	//que pertenece a la recta.
	//Esto se hace resolviendo el sistema entre las ecuaciones:
	// d = sqrt((x2-x1)^2 + (y2-y1)^2) ,  y2 = m*x2 + n 
	// de las que conocemos d,m,n,x1,y1 (x1,y1 es el punto de referencia.
	// De este sistema despejamos x2 y despues calculamos y2 de la siguiente forma
	// a = 1 + m^2
	// b = 2mn - 2x1 - 2mny1
	// c = x1^2 + y1^2 + n^2 -2ny1 - d^2
	// tal que 
	// x2^2·a + x2·b + c = 0
	// x2 = (-b +/- sqrt(b^2 -4ac))/(2ac)
	// y2 = m*x2 + n
	// Las dos soluciones son las coordenadas de los dos puntos equidistantes sobre
	// la misma recta.
	void EquidistantPointsInLine(Point2D P, double D,Point2D &P1, Point2D &P2);

    //RectangleAroundLine
	//Devuelve un rectangulo alrededor de la linea segun el grafico siguiente:
	//
	//          A1----+-----------B1
	//          |     |Distance   |
	//     -----A-----+-----------B-------->
	//          |                 |
	//          A2----------------B2
	//
	// A1 y B1 siempre estan en el semiplano positivo a la izquierda
	void Line::RectangleAroundLine(Point2D A, Point2D B, 
											double Distance,
											Point2D & A1, Point2D & A2,
											Point2D & B1, Point2D & B2);

	//Sobre la inecuacion del semiplano
	double	Pow			       (Point2D P);			           //Devuelve la potencia de un punto respecto a la recta
	int		Side		       (Point2D P);			           //Devuelve 1, 0, -1 segun si el punto P se encuentra en el semiplano positivo, en la recta o en el semiplano negativo
	bool	IsInPosLeftSide    (Point2D P);		               //Si la potencia de P respecto a la recta es positiva entonces se encuentra en el semiplano positivo
	bool	IsInNegRightSide   (Point2D P);		               //Si la potencia de P respecto a la recta es negativa entonces se encuentra en el semiplano negativo
	bool	IsNearPosLeftSide  (Point2D P, double Threshold);  //Si la potencia de P respecto a la recta es negativa pero muy cerca de la recta entonces se encuentra cerca del semiplano positivo
	bool	IsNearNegRightSide (Point2D P, double Threshold);  //Si la potencia de P respecto a la recta es positiva pero muy cerca de la recta entonces se encuentra cerca del semiplano negativo
	bool	Contains           (Point2D P);			           //Si la potencia de P respecto a la recta es cero     entonces P pertenece a la recta

	//Visualization
	void Show();
	//Serialize
//	size_t Serialize(FILE * stream);

private:
	//Private functions
	void EcTwoPoints();
private:
	//Private data
	Point2D v1;	//Punto origen del vector que define a la recta
	Point2D v2;	//Punto destino del vector que define a la recta
	double M;	//Pendiente de la recta y=Mx+N
	double N;	//Distancia en el eje de ordenadas desde el origen
	double FI;	//Angulo que forma la recta con el eje de abcisas (en radianes)
				//(-PI/2 < Fi < PI/2)
	double SIGMA;//Parametros de la Ecuacion Normal de la recta
	double D;	// x*cos(sigma)+y*sin(sigma)=d
				//Calculo del angulo que forma la perpendicular con la parte positiva del eje X
				//Calculo la distancia perpendicular al origen
	double A;	//Valores para la ecuación paramétrica de la recta
	double B;	//Ax+By+C = 0;
	double C;
	
	int   VERT; //True (1) si la línea es VERTICAL,   False (0) si no lo es.
	int	  HOR;	//True (1) si la línea es HORIZONTAL, False (0) si no lo es.


};

/**************************************************************************\
 * Class Line                     
 * This class implements a vector of Point2Ds
\**************************************************************************/
class Point2DVector : public vector <Point2D> 
{
public:
	Point2DVector();
	virtual ~Point2DVector();

	//Operations
	Line LinearRegression(double &Error);

    //Visualization
	void Show();
	//Serialize
//	size_t Serialize(FILE * stream);
};

} //namespace GAC

#endif // !defined(_LINE_H_)
