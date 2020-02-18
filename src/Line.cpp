/****
  SoftVision. Software for Computer Vision

  Gregorio Ambrosio Cestero (goyo@computer.org)
  System Engineering and Automation Department 
  University of Malaga. Spain                   

  $RCSfile: StraightLine.cpp,v $
  $Revision: 1.1 $
  $Date: 2000/01/21 13:05:09 $
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


#include <CVL/Line.h>

using namespace GAC;

Line::Line()
{
	//v1 y v2 se inicializan ambos a (0,0) en el constructor de la clase Point2D
	M=N=FI=A=B=C=SIGMA=D=0;
}

//Constructor de la ecuacion reducida de la recta
Line::Line(double m, double n)
{
	Set(m,n);
}

//Constructor de la recta que pasa por dos puntos
Line::Line(Point2D p1, Point2D p2)
{
	Set(p1,p2);
}

Line::Line(double x1,double y1, double x2, double y2)
{
	Set(x1,y1,x2,y2);
}

//Constructor de la ecuacion parametrica de la recta
Line::Line(double a, double b, double c)
{
	Set(a,b,c);
}


Line::~Line()
{

}

//Accesing elements
//Set of Set functions

//Constructor de la ecuacion reducida de la recta
Line &Line::Set(double m, double n)
{
	M=m;
	N=n;
	if (fabs(FLT_MAX-M) < Epsilon) {		//Si es VERTICAL
		VERT	= 1;
		HOR		= 0;
		M		= FLT_MAX;
		FI		= PI/2;
		SIGMA	= 0;
		v1.Set(N,0);v2.Set(N,FLT_MAX);
	} else if (fabs(M)<Epsilon) {			//Si es HORIZONTAL
		VERT	= 0;
		HOR		= 1;
		M		= 0;
		FI		= 0;
		N<0		? SIGMA=-PI/2 : SIGMA=PI/2;		
		v1.Set(0,N);v2.Set(1,N);
	} else {							//Si no es ni HORIZONTAL ni VERTICAL ni todo lo contrario
		VERT	= 0;
		HOR		= 0;
		FI		= atan(M);
		FI<0	? SIGMA	= FI - PI/2 : SIGMA	= FI + PI/2;
		v1.Set(0,N); v2.Set(-N/M,0);
	}

	//Paso a la ecuacion parametrica de la recta
	A= -M;
	B=  1;
	C= -N;

	//Paso a la ecuacion normal de la recta
//	if (SIGMA!=0 && SIGMA/PI/2) SIGMA = acos(A/(sqrt(pow(A,2)+pow(B,2))));
	D	  = v1.x()*cos(SIGMA)+v1.y()*sin(SIGMA);
	return *this;
}

//Constructor de la recta que pasa por dos puntos
Line &Line::Set(double x1,double y1, double x2, double y2)
{
	v1.Set(x1,y1);
	v2.Set(x2,y2);
	EcTwoPoints();

	return *this;
}
Line &Line::Set(Point2D p1, Point2D p2)
{
	v1=p1;
	v2=p2;
	EcTwoPoints();

	return *this;
}

//Constructor de la ecuacion parametrica de la recta
Line &Line::Set(double a, double b, double c)
{
	A=a;
	B=b;
	C=c;
	
	//Paso la ecuacion reducida y generación de dos puntos
	if (fabs(B) < Epsilon) {		//Si es VERTICAL
		VERT	= 1;
		HOR		= 0;
		B		= 0;
		M		= FLT_MAX;
		N		= FLT_MAX;
		FI		= PI/2;
		SIGMA	= 0;
		v1.Set(N,0);v2.Set(N,FLT_MAX);
	} else if (fabs(A)<Epsilon) {			//Si es HORIZONTAL
		VERT	= 0;
		HOR		= 1;
		A		= 0;
		M		= 0;
		N		=-C/B;
		FI		= 0;
		N<0		? SIGMA=-PI/2 : SIGMA=PI/2;
		v1.Set(0,N);v2.Set(1,N);
	} else {							//Si no es ni HORIZONTAL ni VERTICAL ni todo lo contrario
		VERT	= 0;
		HOR		= 0;
		M		=-A/B;
		N		=-C/B;
		FI		= atan(M);
		SIGMA	= acos(A/(sqrt(pow(A,2)+pow(B,2))));
		v1.Set(0,N); v2.Set(-N/M,0);
	}

	//Paso a la ecuacion normal de la recta (angulo sigma y distancia)
	D	  = v1.x()*cos(SIGMA)+v1.y()*sin(SIGMA);

	return *this;
}

//Constructor de la ecuacion normal de la recta
Line &Line::SetNormal(double d, double sigma)
{
	D     = d;
	SIGMA = sigma;

	if (fabs(SIGMA-PI)		< Epsilon || 
		fabs(SIGMA)		    < Epsilon)	{				//Si es VERTICAL
		VERT	=  1;
		HOR		=  0;
		M		=  FLT_MAX;
		FI		=  SIGMA-(PI/2);
		A		= -M;
		B		=  1;
		C		= -(D*sqrt(pow(A,2)+pow(B,2)));
		N		= -C;
		v1.Set(N,0);v2.Set(N,FLT_MAX);
	} else if (fabs(SIGMA-(3*PI/2)) < Epsilon ||
			   fabs(SIGMA-(PI/2))	< Epsilon)	{		//Si es HORIZONTAL
		VERT	=  0;
		HOR		=  1;
		M		=  0;
		FI		=  SIGMA-(PI/2);
		A		= -M;
		B		=  1;
		C		= -(D*sqrt(pow(A,2)+pow(B,2)));
		N		= -C;
		v1.Set(0,N);v2.Set(1,N);
	} else {							//Si no es ni HORIZONTAL ni VERTICAL ni todo lo contrario
		VERT	=  0;
		HOR		=  0;
		FI		=  SIGMA-(PI/2);
		M		=  tan(FI);
		A		= -M;
		B		=  1;
		C		= -(D*sqrt(pow(A,2)+pow(B,2)));
		N		= -C;
		v1.Set(0,N); v2.Set(-N/M,0);
	}

	return *this;
}

//Operators
bool Line::operator== (const Line& L1)
{
	return (M==L1.M)&&(N==L1.N)&&(FI==L1.FI);
}

//Comparison of the line slopes
bool Line::operator<  (const Line& L1)
{
	return (M<L1.M);
}

//Operations
double Line::x(double y)
{
	if (HOR)
		return FLT_MAX; //Por devolver algun valor
	else if (VERT)
        return -C/A;
    else
		return (y-N)/M;
}
double Line::y(double x)
{
	if (VERT)
		return FLT_MAX; //Por devolver algun valor
	else	
		return M*x+N;
}

//Attributes

//Parámetros de la recta en su forma de ecuación reducida   y = mx+n  m=tan(Fi)
double Line::m()
{return M;}
double Line::n()
{return N;}
double Line::Fi()
{return FI;}
double Line::PosFi()
{	
	double POSFI;
	(FI<0) ? POSFI = (PI+FI) : POSFI = FI;
	return POSFI;
}

//Parámetros de la recta portadora en su forma de ecuación normal   x*cos(sigma)+y*sin(sigma)=d
double Line::Sigma()
{return SIGMA;}
double Line::d()
{return D;}

//Parámetros de la recta portadora en su forma de ecuación parametrica  ax + by + c  = 0
double Line::a()
{return A;}
double Line::b()
{return B;}
double Line::c()
{return C;}

int Line::isVertical()
{ return VERT; }
int Line::isHorizontal()
{ return HOR; }

//Distancia de un punto a una recta
//¡¡¡ojo!!! está mal pero sirve para la detección de segmentos
//No devuelve un valor correcto de distancia pero la segmentación y otras
//funciones están echas en base a esta función por lo que si las cambio
//por la función correcta EuclideanDistance no van a funcionar bien.
//De modo que tengo que ir cambiando función por función y comprobando los efectos
//al usar la función correcta.
double Line::Distance(Point2D P)
{
	double val;

	//La distancia sera positiva o negativa segun la potencia de P respecto de
	//la recta, es decir segun este en el semiplano positivo o negativo de la recta
	val = P.x()*cos(SIGMA)+P.y()*sin(SIGMA)-D;
	return val;
}

//Distancia euclidea de un punto a una recta
double Line::EuclideanDistance(const Point2D & P)
{
	double val,xCross;
	Line SL;
	Point2D Paux,Paux1;

	Paux1 = P;

	//Si el punto pertenece a la recta la distancia es cero

	if (VERT){
		xCross = -C/A;
		return abs(Paux1.x()-xCross);
	}
	
	SL = PerpLine(Paux1);
	Paux = Intersection(SL);
	val = Paux1.Distance(Paux);

	return val;
}

//Devuelve el angulo que forma con otra recta (<=PI)
double Line::Angle(const Line & L)
{
	Line SLaux;
	double ang;
	double Ap,Bp;

	SLaux = L;

	if		(!VERT && !SLaux.isVertical()) {
/*
									   ML  = SLaux.m();
									   ang = atan(fabs((M-ML)/(1+M*ML)));
*/
			Ap = SLaux.a();
			Bp = SLaux.b();
			ang = acos((A*Ap + B*Bp)/(sqrt(A*A+B*B)*sqrt(Ap*Ap+Bp*Bp)));
	}
	else if ( VERT &&  SLaux.isVertical()) ang = 0;
	else if ( VERT && !SLaux.isVertical()) ang = (PI/2-fabs(SLaux.Fi()));
	else if (!VERT &&  SLaux.isVertical()) ang = (PI/2-fabs(FI));

	return ang;
}

//Devuelve la potencia de un punto respecto a la recta
double Line::Pow(Point2D P) {return (A*P.x() + B*P.y() + C);}

//Devuelve 1, 0, -1 segun si el punto P se encuentra en el semiplano positivo, en la recta o en el semiplano negativo
//Si la potencia de P respecto a la recta es positiva entonces se encuentra en el semiplano positivo
//Si la potencia de P respecto a la recta es negativa entonces se encuentra en el semiplano negativo
//Si la potencia de P respecto a la recta es cero     entonces P pertenece a la recta
int	Line::Side(Point2D P)
{
	double val;
	int sign;
	//Aqui podria hacer una llamada a Pow(P) pero entonces tendria que declarar la funcion Pow pasando de parametro un puntero "Pow(Point2D &P)". No se porque, misterio misterioso
	// val = Pow(P); Supongo que el llamarse dentro de la clase es lo que origina el problema
	val = A*P.x() + B*P.y() + C;
    if		(val>0) sign= 1;
	else if (val<0) sign=-1;
	else			sign= 0;

	return sign;
}

bool Line::IsInPosLeftSide (Point2D P)  { return (Side(P)>= 0);}
bool Line::IsInNegRightSide (Point2D P) { return (Side(P)<= 0);}
bool Line::Contains(Point2D P)      { return (Side(P)== 0);}

bool Line::IsNearPosLeftSide  (Point2D P,double Threshold)
{
	return (((Pow(P)<=0)&&(fabs(EuclideanDistance(P)<Threshold)) || (Side(P)>= 0)));
//	return (((Pow(P)<=0)&&(fabs(Pow(P)<Threshold)) || (Side(P)>= 0)));
}
bool Line::IsNearNegRightSide (Point2D P,double Threshold)
{
	return (((Pow(P)>=0)&&(fabs(EuclideanDistance(P)<Threshold)) || (Side(P)<= 0)));
//	return (((Pow(P)>=0)&&(fabs(Pow(P)<Threshold)) || (Side(P)<= 0)));
}

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
// Las dos soluciones son las coordenadas de los dos puntos equidistantes
void Line::EquidistantPointsInLine(Point2D P, double D,Point2D &P1, Point2D &P2)
{
	double a,b,c;
	double r1,r2;
	double x,y;

	x = P.x();
	y = P.y();

	if (!VERT && !HOR) {
		y=M*x+N;

		a = 1 + pow(M,2);
		b = 2*M*N - 2*x - 2*M*y;
		c = pow(x,2) + pow(y,2) + pow(N,2) - 2*N*y - pow(D,2);

		r1 = 0;
		r2 = 0;
        CuadRoot(a,b,c,r1,r2);
		P1.Setx(r1);
		P2.Setx(r2);
		P1.Sety(M*P1.x() + N);
		P2.Sety(M*P2.x() + N);
	} else if (VERT) {
		P1.Set(x,y-D);
		P2.Set(x,y+D);
	} else if (HOR) {
		P1.Set(x-D,y);
		P2.Set(x+D,y);
	}
}

//Retorna la linea perpendicular que pasa por el punto P
Line Line::PerpLine(Point2D P)
{
	double MP,NP;
	Line SLaux;
	if (!VERT && !HOR) {
		//Calculo la recta perpendicular que pasa por el punto P
		MP = -1/M;
		NP = P.x()/M + P.y();
		SLaux.Set(MP,NP);
	} else if (VERT) {
		SLaux.Set(P,Point2D(P.x()+1,P.y()));
	} else if (HOR) {
		SLaux.Set(P,Point2D(P.x(),P.y()+1));
	}
	return SLaux;
}

void Line::RectangleAroundLine(Point2D A, Point2D B, 
							   double Distance,
							   Point2D & A1, Point2D & A2,
							   Point2D & B1, Point2D & B2){
	Line PerpA, PerpB;

	PerpA = PerpLine(A);
	PerpB = PerpLine(B);
	PerpA.EquidistantPointsInLine(A,Distance,A1,A2);
	PerpB.EquidistantPointsInLine(B,Distance,B1,B2);
	if (Side(A2) > 0) A1.Swap(A2);
	if (Side(B2) > 0) B1.Swap(B2);
}


//Retorna True si las rectas son paralelas
bool Line::isParallel(Line SLaux)
{
	bool Parallel;
	if (!VERT && !SLaux.isVertical()) {
		Parallel = fabs(SLaux.m() - M) < Epsilon;
	} else if (VERT && !SLaux.isVertical()) {
		Parallel = false;
	} else if (!VERT && SLaux.isVertical()) {
		Parallel = false;
	} else if (VERT && SLaux.isVertical()) {
		Parallel = true;
	}
	return Parallel;
}

//Retorna el punto donde las dos rectas intersectan
Point2D Line::Intersection(Line SLaux)
{
	double num, den, x, y;
	Point2D  P;
	num = N - SLaux.n();
	den = SLaux.m() - M;
	if (!VERT && !SLaux.isVertical()) {
		if (fabs(den) < Epsilon) { //Si son paralelas
			x = FLT_MAX;
			y = FLT_MAX;
		} else {
			x = num/den;
			y = SLaux.y(x);
		}
	} else if (VERT && !SLaux.isVertical()) {
		x = v1.x();
		y = SLaux.y(x);
	} else if (!VERT && SLaux.isVertical()) {
		x = SLaux.v1.x();
		y = M*x+N;
	} else if (VERT && SLaux.isVertical()) {
		x = FLT_MAX;
		y = FLT_MAX;
	}
				
	P.Set(x,y);
	return P;
}


//Visualization
void Line::Show() {
	printf ("(%g,%g)->(%g,%g)\n",v1.x(),v1.y(),v2.x(),v2.y());
	printf ("Ecuacion reducida    (y=Mx+N)                 : y=(%g)x+(%g), Fi=%g (PI/%g) (grados:%g)\n",M,N,FI,PI/FI,grad(FI));
	printf ("Ecuacion parametrica (Ax+By+C=0)              : A:%g,B:%g,C:%g\n",A,B,C);
	printf ("Ecuacion normal      xcos(sigma)+ysen(sigma)=d: sigma:%g (PI/%g) (grados:%g), d:%g\n",SIGMA,PI/SIGMA,grad(SIGMA),D);
}

/*
	//Serialize
size_t Line::Serialize(FILE * stream)
{
	size_t count   = 0;

	count += v1.Serialize(stream);
	count += v2.Serialize(stream);

	count += sizeof(double)*fwrite(&M,  sizeof(double),1,stream);
	count += sizeof(double)*fwrite(&N,  sizeof(double),1,stream);
	count += sizeof(double)*fwrite(&FI, sizeof(double),1,stream);

	count += sizeof(double)*fwrite(&A, sizeof(double),1,stream);
	count += sizeof(double)*fwrite(&B, sizeof(double),1,stream);
	count += sizeof(double)*fwrite(&C, sizeof(double),1,stream);

	count += sizeof(double)*fwrite(&D,	   sizeof(double),1,stream);
	count += sizeof(double)*fwrite(&SIGMA, sizeof(double),1,stream);

	count += sizeof(int)*fwrite(&HOR,  sizeof(int),1,stream);
	count += sizeof(int)*fwrite(&VERT, sizeof(int),1,stream);

	return count;
}
*/

//Private functions

//EcTwoPoints()
//Se llama cada vez que se establece o cambian los puntos de vector (v1,v2).
//Tiene en cuenta los casos particulares donde la recta es vertical u horizontal
//Esta funcion obtiene primero la ecuacion parametrica de la recta y despues las demas.
//De las dos ecuaciones parametricas posibles para una recta (ax + by + c = 0 o -ax -by -c = 0)
//obtiene la que resulta de resolver el determinante:
//    |x  y  1|
//    |x1 y1 1| = 0
//    |x2 y2 1|
//la cual tiene el signo de forma que el semiplano negativo es siempre el de la derecha
//recorriendo la recta de v1 a v2, y el semiplano positivo es siempre el de la izquierda recorriendo
//la recta de v1 a v2. Es decir, la potencia de un punto sera negativa o positiva segun se encuentre
//en el lado derecho o izquierdo de la recta en el sentido v1->v2.


void Line::EcTwoPoints()
{
	//Parámetros de la ecuación paramétrica de la recta
	// Ax+By+C=0
	//obtenida mediante la resolución del determinante
	A = v1.y()-v2.y();
	B = v2.x()-v1.x();
	C = v1.x()*v2.y() - v2.x()*v1.y();

	//Determino si la ínea es vertical u horizontal (establezco VERT y HOR)
	if (fabs(B) < Epsilon)	{VERT=1;B=0;}		//Si la línea es VERTICAL	
	else					 VERT=0;
	if (fabs(A) < Epsilon)	{HOR=1;A=0;}		//Si la línea es HORIZONTAL	
	else					HOR=0;

	//Calculo de la pendiente M (y=Mx+N)
	//FLT_MAX es igual que "val =  numeric_limits<double>::max();"  //De la STL #include <limits>

	if (VERT)	M = FLT_MAX;					//Si la línea SI es VERTICAL
	else		M = -A/B;						//Si la línea NO es VERTICAL
		
	//Calculo de la distancia N (y=Mx+N)
	//FLT_MAX es igual que "val =  numeric_limits<double>::max();"  //De la STL #include <limits>
	if (VERT)	N = FLT_MAX;								//Si la línea SI es VERTICAL
	else		N = -C/B;	//Si la línea NO es VERTICAL

	//Calculo del angulo FI (M=tan(FI))
	if (VERT)				//Si la línea SI es VERTICAL
		if (v2.y() > v1.y())			//Si es creciente	
			FI = PI/2;
		else						//Si es decreciente
			FI = -PI/2;
	else					//Si la línea NO es VERTICAL
		FI = atan(M);

	//Parametros de la Ecuacion Normal de la recta
	// x*cos(sigma)+y*sin(sigma)=d

	//Calculo del angulo que forma la perpendicular con la parte positiva del eje X
	if		(VERT)				SIGMA = 0;
	else if (HOR && (v1.y()<0))	SIGMA = -PI/2;
	else if (HOR)				SIGMA =  PI/2;
	else						SIGMA = acos(A/(sqrt(pow(A,2)+pow(B,2))));
	//Calculo la distancia perpendicular al origen
	D	  = v1.x()*cos(SIGMA)+v1.y()*sin(SIGMA);

}

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Point2DVector::Point2DVector()
{

}

Point2DVector::~Point2DVector()
{

}


//Visualization
void Point2DVector::Show()
{
	Point2DVector::iterator it;
	Point2D P;
	for (it = begin(); it != end(); it++)
	{
		P = *it;
		P.Show();	
	}
}

/*
//Serialize
size_t Point2DVector::Serialize(FILE * stream)
{
	size_t count  = 0;
	size_t PVsize = 0;

	PVsize = size();
	count += sizeof(size_t)*fwrite(&PVsize, sizeof(size_t),1,stream);

	Point2DVector::iterator it;
	for (it = begin(); it != end(); it++)
	{
		count += (*it).Serialize(stream);	
	}

	return count;
}
*/

//Operations
Line Point2DVector::LinearRegression(double &Error)
{
	Line Line;
	double SumX,SumY,SumXX,SumXY;
	Point2D P;
	int PixelCount;
	Point2DVector::iterator PVit;


	PixelCount = size();

	//Calculo SumX y SumY
	SumX=0;SumY=0;
	for (PVit = begin(); PVit != end(); PVit++){
		P = *PVit;
		SumX+=P.x();
		SumY+=P.y();
	}
	SumX/=PixelCount;
	SumY/=PixelCount;

	//Calculo SumXX y SumXY
	SumXX=0;SumXY=0;
	for (PVit = begin(); PVit != end(); PVit++){
		P = *PVit;
		SumXX+=pow(P.x()-SumX,2);
		SumXY+=(P.x()-SumX)*(P.y()-SumY);
	}
	
	//Calculo la recta
	if (fabs(SumXX)<Epsilon) 	//Chequeo si la recta es VERTICAL
		Line.SetNormal(P.x(),0);
	else {						//Calculo los parametros de la recta y=M*x + N
		double M,N;
		M=SumXY/SumXX;
		N=SumY-M*SumX;
		Line.Set(M,N);
	}

	//Calculo el error
	Error=0;
	for (PVit = begin(); PVit != end(); PVit++){
		P = *PVit;
		Error += fabs(Line.Distance(P));
	}
	Error/=PixelCount;

	return Line;
}

