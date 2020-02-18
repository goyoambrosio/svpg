/****
  SoftVision. Software for Computer Vision

  Gregorio Ambrosio Cestero (goyo@computer.org)
  System Engineering and Automation Department 
  University of Malaga. Spain                   

  $RCSfile: CompVector.cpp,v $
  $Revision: 1.1 $
  $Date: 2000/01/21 13:03:55 $
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


#include <CVL/Vector.h>

#include <stdarg.h>
#include <algorithm>

using namespace GAC;

/***********************************************\
 *                  Vector                     *
\***********************************************/

//This function copies input vectors i1,i2 into output vectors o1,o2.
//Output vectors have the same size as the longest input vector.
//The output vector corresponding with the shortest input vector is zero-padded
//It's useful to let operations among vectors with non equal sizes.
void Vector::SizeEqualize (Vector i1, Vector i2, Vector &o1, Vector &o2)
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


Vector::Vector()
{

}

Vector::Vector(unsigned int dim, ...)
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

Vector &Vector::Set(unsigned int dim, ...)
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

Vector::~Vector()
{

}


//Operators
bool Vector::operator== (Vector V)
{
	Vector::iterator Vit1,Vit2;
	bool equal = true;

	if (size()!=V.size()) 
		return false;

	for (Vit1=begin(),Vit2=V.begin();
		 Vit1!=end();
		 Vit1++,Vit2++){
		equal = equal&&(*Vit1==*Vit2);
	}
	return equal;
}

bool Vector::operator!= (Vector V)
{
	return !((*this)==V);
}

bool Vector::operator<  (Vector V)
{
	return (Mod()<V.Mod());
}

bool Vector::operator>  (Vector V)
{
	return (Mod()>V.Mod());
}

bool Vector::operator<=  (Vector V)
{
	return (Mod()<=V.Mod());
}

bool Vector::operator>=  (Vector V)
{
	return (Mod()>=V.Mod());
}

double GAC::operator* (Vector Vl, Vector Vr){
	return Vl.Dot(Vr);
}


Vector GAC::operator* (Vector V, double val){
	Vector::iterator Vit1;
	Vector V1;

	for (Vit1=V.begin();Vit1!=V.end();Vit1++){
		V1.push_back((*Vit1)*val);
	}

	return V1;
}

Vector GAC::operator* (double val, Vector V){
	Vector::iterator Vit1;
	Vector V1;

	for (Vit1=V.begin();Vit1!=V.end();Vit1++){
		V1.push_back(val*(*Vit1));
	}

	return V1;
}

Vector GAC::operator/ (Vector V, double val){
	Vector::iterator Vit1;
	Vector V1;

	for (Vit1=V.begin();Vit1!=V.end();Vit1++){
		V1.push_back((*Vit1)/val);
	}

	return V1;
}

Vector GAC::operator/ (double val, Vector V){
	Vector::iterator Vit1;
	Vector V1;

	for (Vit1=V.begin();Vit1!=V.end();Vit1++){
		V1.push_back(val/(*Vit1));
	}

	return V1;
}

Vector Vector::operator+ (Vector V){
	iterator Vit1,Vit2;
	Vector Vtotal,V1,V2;

	SizeEqualize (*this,V,V1,V2);

	for (Vit1=V1.begin(),Vit2=V2.begin();
		 Vit1 != V1.end();
		 Vit1++,Vit2++){
		Vtotal.push_back((*Vit1)+(*Vit2));
	}

	return Vtotal;
}

Vector Vector::operator- (Vector V){
	iterator Vit1,Vit2;
	Vector Vtotal,V1,V2;

	SizeEqualize (*this,V,V1,V2);

	for (Vit1=V1.begin(),Vit2=V2.begin();
		 Vit1 != V1.end();
		 Vit1++,Vit2++){
		Vtotal.push_back((*Vit1)-(*Vit2));
	}

	return Vtotal;
}

double Vector::Dot(Vector V){
	iterator Vit1,Vit2;
	Vector V1,V2;
	double total = 0;

	SizeEqualize (*this,V,V1,V2);

	for (Vit1=V1.begin(),Vit2=V2.begin();
		 Vit1!=V1.end();
		 Vit1++,Vit2++){
		total += (*Vit1)*(*Vit2);
	}

	return (total);
}

//The Unit vector is obtained of dividing a vector by its norm.
Vector Vector::Unit(){
	return (*this)/Norm();
}

double Vector::Norm(){
	iterator Vit;
	double total = 0;

	for (Vit=begin();Vit!=end();Vit++){
		total += pow((*Vit),2);
	}

	return (sqrt(total));
}

double Vector::Mod(){
	return Norm();
}

double Vector::Length(){
	return Norm();
}

/*
double Vector::EuclideanDistance (Vector V){
	const_iterator Vit1,Vit2;
	Vector V1,V2;
	double total = 0;

	SizeEqualize (*this,V,V1,V2);

	for (Vit1=V1.begin(),Vit2=V2.begin();
		 Vit1!=V1.end();
		 Vit1++,Vit2++){
		total += pow((*Vit1)-(*Vit2),2);
	}

	return (total);
}
*/


//Visualization
void Vector::Show(){
	iterator Vit;

    if (size()>0){
	    Vit = begin();
	    printf("(%.30g",*Vit);
	    Vit++;
	    for (;Vit!=end();Vit++){
		    printf(",%.30g",*Vit);
	    }
	    printf(")\n");
    }
}


ostream &GAC::operator<<(ostream &s, const Vector &V)
{
    Vector::const_iterator Vit;

    if (V.size()>0){
	    Vit = V.begin();
        s << "(" << *Vit;
	    Vit++;
	    for (;Vit!=V.end();Vit++){
            s << "," << *Vit;
	    }
        s << ")";
    }
	return s;
};


/*
//Serialize
size_t Vector::Serialize(FILE * stream)
{
	const_iterator Vit;
	size_t count   = 0;

	for (Vit=begin();Vit!=end();Vit++){
		count += sizeof(double)*fwrite(Vit, sizeof(double),1,stream);
	}

	return count;
}
*/

/***********************************************\
 *                Vector2D                   *
\***********************************************/

/*
Vector2D::Vector2D()
{	//Inicialmente el punto se inicializa a (0,0)
	push_back(0.0);
	push_back(0.0);
}

Vector2D::Vector2D(double d1, double d2)
{
	push_back(d1);
	push_back(d2);
}
*/

Vector2D::Vector2D(Vector V)
{
	resize(V.size());
	copy(V.begin(),V.end(),begin());
}



//Setting
Vector2D &Vector2D::Set(double x, double y)
{
	clear();
	push_back(x);
	push_back(y);
	return *this;
}

Vector2D::~Vector2D()
{

}

	//Accesors
double Vector2D::x(){
	return (*this)[0];
}

double Vector2D::y(){
	return (*this)[1];
}


//This function returns the magnitude of the vector resulting of cross product
double Vector2D::Cross(Vector2D V){
	return (Mod()*V.Mod()*sin(ClockwiseAngle(V)));
}

//The normal vector to vector (x,y) is (y,-x)
Vector2D Vector2D::Normal(){
	return Vector2D((*this)[1],-(*this)[0]);
}


//Between 0 and PI
double Vector2D::Angle(Vector2D V){
	double ang;

	Vector2D V1;
	V1 = *this;
	ang = acos((V1*V)/(V1.Mod()*V.Mod()));
	return ang;
}

//Between  0 and PI/2
//Necessary smaller angle to take to the vector V to the same direction of this vector
//(independently of the orientation),i.e., to align the two vectors.
//
//Angulo más pequeño necesario para llevar al vector CV a la misma dirección
//de este vector (independientemente del sentido). Es decir, menor ángulo necesario
//para alinear los dos vectores.
double Vector2D::ShortAngle(Vector2D V)
{
	double ShortAngle;
	Vector2D V1;

	V1 = V;
	ShortAngle = Angle(V1);
	if (ShortAngle>HALF_PI) ShortAngle = PI-ShortAngle;
	return ShortAngle;
}

double Vector2D::ClockwiseAngle(Vector2D V){
	double Angle,AngleU1,AngleU2, BaseAngle;
	Vector2D V1,U1,U2;
	
	//Para obtener el ángulo que tiene que rotar V1 en el sentido horario
	//para llegar a V lo que se hace es:
	//- en primer lugar se obtienen los vectores base (de modulo 1) de V1 y V,
	//  estos son U1 y U2. Las componentes de estos vectores son los cosenos directores
	//- en segundo lugar calculo el angulo que forma cada uno con el eje x en el sentido tradicional (antihorario)
	//  para ello tengo en cuanta el cuadrante en el que se encuentra gracias a que el segundo coseno director
	//  (coseno de beta) es igual al seno de alfa. Asi mediante el seno y el coseno de alfa obtengo el cuadrante
	//  También tengo en cuenta si se encuentra sobre un eje.
	//  (sin/cos)->(+/+)->cuadrante 1->Angulo final = Angulo Base + 0
	//  (sin/cos)->(+/-)->cuadrante 2->Angulo final = Angulo Base + PI/2
	//  (sin/cos)->(-/-)->cuadrante 3->Angulo final = Angulo Base + PI
	//  (sin/cos)->(-/+)->cuadrante 4->Angulo final = Angulo Base + 3PI/2
	//  En los casos en que el ángulo cae sobre un eje, es decir que el seno o el coseno
	//  sea cero se tratan de forma particular.
	//- Para terminar resto los dos ángulos y ese es el resultado

	U1 = Unit();
	U2 = V.Unit();

//Calculo el angulo de U1
	if		((U1[1]>0) && (U1[0]>0)){
		BaseAngle=0;
		AngleU1 = acos(fabs(U1[0]))+BaseAngle;
	}
	else if ((U1[1]>0) && (U1[0]<0)){
		BaseAngle=PI/2;
		AngleU1 = acos(fabs(U1[1]))+BaseAngle;
	}
	else if ((U1[1]<0) && (U1[0]<0)){
		BaseAngle=PI;
		AngleU1 = acos(fabs(U1[0]))+BaseAngle;
	}
	else if ((U1[1]<0) && (U1[0]>0)){
		BaseAngle=3*PI/2;
		AngleU1 = acos(fabs(U1[1]))+BaseAngle;
	}

	if      (U1[0]==0)
		if	  (U1[1]>0)
				AngleU1 = PI/2;
		else
			    AngleU1 = 3*PI/2;
	else if (U1[1]==0)
		if    (U1[0]>0)
			    AngleU1 = 0;
		else
				AngleU1 = PI;

//Calculo el angulo de U2
	if		((U2[1]>0) && (U2[0]>0)){
		BaseAngle=0;
		AngleU2 = acos(fabs(U2[0]))+BaseAngle;
	}
	else if ((U2[1]>0) && (U2[0]<0)){
		BaseAngle=PI/2;
		AngleU2 = acos(fabs(U2[1]))+BaseAngle;
	}
	else if ((U2[1]<0) && (U2[0]<0)){
		BaseAngle=PI;
		AngleU2 = acos(fabs(U2[0]))+BaseAngle;
	}
	else if ((U2[1]<0) && (U2[0]>0)){
		BaseAngle=3*PI/2;
		AngleU2 = acos(fabs(U2[1]))+BaseAngle;
	}

	if      (U2[0]==0)
		if	  (U2[1]>0)
				AngleU2 = PI/2;
		else
			    AngleU2 = 3*PI/2;
	else if (U2[1]==0)
		if    (U2[0]>0)
			    AngleU2 = 0;
		else
				AngleU2 = PI;

//Calculo en angulo que tiene que recorrer U1 en el sentido horario para llegar
//a U2
	if (AngleU1 > AngleU2)
		Angle = AngleU1-AngleU2;
	else
		Angle = 2*PI-(AngleU2-AngleU1);

	return Angle;
}

//Between -PI and PI
//This function returns the angle that the vector has to rotate to align with the vector V 
//When the angle is negative the rotation is non-clockwise and when it is positive the rotation
//is clockwise. It is based on the function ClockwiseAngle.
//
//Esta función devuelve el ángulo que tiene que rotar el vector  para situarse sobre
//el vector V. Cuando el ángulo es negativo la rotación es en el sentido antihorario
//y cuando es positivo el sentido es horario.
//Se basa en la función Clockwise Angle.
double Vector2D::OrderedAngle(Vector2D V){
	double Angle;
	Angle = ClockwiseAngle(V);
	if (Angle > PI) Angle -= 2*PI;
	return Angle;
}

