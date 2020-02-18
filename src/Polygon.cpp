/****
  SoftVision. Software for Computer Vision

  Gregorio Ambrosio Cestero (goyo@computer.org)
  System Engineering and Automation Department 
  University of Malaga. Spain                   

  $RCSfile: Polygon.cpp,v $
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

// The debugger can't handle symbols more than 255 characters long.
// STL often creates symbols longer than that.
// When symbols are longer than 255 characters, the warning is disabled.
#pragma warning(disable:4786)

#include <CVL/Polygon.h>

#include <algorithm>

using namespace GAC;

Polygon::Polygon(){}

Polygon::~Polygon(){}

void Polygon::push_back(const Point2D & P)
{
	DirectedLineSegmentMap::iterator   VMit;
	Point2DVector::iterator PVit;
	unsigned int LastLabel;
	Point2D PA,PBegin,PEnd;
	DirectedLineSegment V;

	PVit = find(begin(),end(),P);
	if (PVit == end()){
		//Si hay 2 o más puntos ...
		if (size()>=2) {
			//Quito el ultimo vector ya que es el que cierra el polígono
			VMit      = Sides.end();
			Sides.erase(--VMit); 
			//Obtengo cual es la última Label
			VMit      = Sides.end();
			--VMit;
			LastLabel = (*VMit).first;//Obtengo cual es la última Label
			//Obtengo el primer y último punto del polígono
			PBegin    = *begin();
			PVit      = end();
			PEnd      = *(--PVit);
			//Inserto el vector formado por el último y el nuevo punto
			Sides.insert(DirectedLineSegmentMap::value_type(LastLabel+1,DirectedLineSegment(PEnd,P)));
			//Inserto el vector que cierra el polígono
			Sides.insert(DirectedLineSegmentMap::value_type(LastLabel+2,DirectedLineSegment(P,PBegin)));
			//Inserto el nuevo punto P
			Point2DVector::push_back(P); 
		}
		else if (size()==1) {
			PBegin    = *begin();
			LastLabel = 0;
			//Inserto el vector formado por el único punto existente hasta ahora
			//y el nuevo punto
			Sides.insert(DirectedLineSegmentMap::value_type(LastLabel+1,DirectedLineSegment(PBegin,P)));
			//Inserto el vector que cierra el polígono que en este caso, con sólo dos
			//puntos, es el mismo vector con sentido contrario. Esto lo hago por
			//coherencia con el algoritmo.
			Sides.insert(DirectedLineSegmentMap::value_type(LastLabel+2,DirectedLineSegment(P,PBegin)));
			//Inserto el nuevo punto P
			Point2DVector::push_back(P); //Inserto el nuevo punto P
		}
		else if (size()==0) {
			Point2DVector::push_back(P); //Inserto el nuevo punto P
		}
	}
}

void Polygon::pop_back()
{
	DirectedLineSegmentMap::iterator   VMit;
	Point2DVector::iterator PVit;
	unsigned int LastLabel;
	Point2D PA,PBegin,PEnd;

	//Si hay más de un punto ...
	if (size()>2) {
		//Primero quito el vector que cierra el polígono
		VMit = Sides.end();
		Sides.erase(--VMit);
		//Quito el último vector
		VMit = Sides.end();
		Sides.erase(--VMit);
		//Elimino el último punto P
		Point2DVector::pop_back(); 
		//Obtengo la última Label
		VMit = Sides.end();
		--VMit;
		LastLabel = (*VMit).first;
		//Obtengo el primer y el último punto del polígono
		PBegin    = *begin();
		PVit      = end();
		--PVit;
		PEnd      = *PVit;
		//Inserto el vector que cierra el polígono
		Sides.insert(DirectedLineSegmentMap::value_type(LastLabel+1,DirectedLineSegment(PEnd,PBegin)));
	}
	else if (size()==2) {
		//Primero quito el vector que cierra el polígono
		VMit = Sides.end();
		//Quito el último vector
		Sides.erase(--VMit);
		VMit = Sides.end();
		Sides.erase(--VMit); 
		//Elimino el último punto P
		Point2DVector::pop_back();
	}
	else if (size()==1) {
		//Elimino el último y único punto P
		Point2DVector::pop_back(); //Elimino el último y único punto P
	}
	
}

bool Polygon::isValid()
{
	DirectedLineSegmentMap::iterator VMit1, VMit2;
	DirectedLineSegment V1,V2;
	Point2D P;

	if (Sides.size()<3)
		return false;
	for (VMit1 = Sides.begin(); VMit1 != Sides.end(); VMit1++)
		for (VMit2 = Sides.begin(); VMit2 != Sides.end(); VMit2++) {
			if ((*VMit1).first!=(*VMit2).first) {
				V1 = (*VMit1).second;
				V2 = (*VMit2).second;
				P = V1.Intersection(V2);
				if (V1.Contains(P) &&
					V2.Contains(P) &&
					(P.Distance(V1.p())>1.0e-10) &&		//Debería ser P != V1.GetA() y P != V1.GetB() pero se hace con la distancia
					(P.Distance(V1.q())>1.0e-10)  )   {	//debido a los errores de precisión que se cometen al obtener la intersección.
						return false;
				}
			}
		}

	return true;
}

Point2DVector Polygon::Rectangle(double & XL,double & XR,double & YD,double & YU)
{
	Point2D P;
	Point2DVector::iterator PVit;
	Point2DVector Rectangle;

	PVit = begin();
	P    = *PVit;
	XL   = P.x();
	XR   = P.x();
	YD   = P.y();
	YU   = P.y();

	for (PVit++; PVit != end(); PVit++) {
		P = *PVit;
		if (P.x() < XL) XL = P.x(); 
		if (P.x() > XR) XR = P.x(); 
		if (P.y() < YD) YD = P.y(); 
		if (P.y() > YU) YU = P.y(); 
	}

	Rectangle.push_back(Point2D(XL,YD)); //A
	Rectangle.push_back(Point2D(XL,YU)); //B
	Rectangle.push_back(Point2D(XR,YU)); //C
	Rectangle.push_back(Point2D(XR,YD)); //D

	return Rectangle;
}

double Polygon::Perimeter()
{
	DirectedLineSegmentMap::iterator VMit;
	Vector2D V;
	double Perimeter = 0.0;

	//El perímetro es la suma de los módulos de los lados del polígono
	for (VMit=Sides.begin();VMit!=Sides.end();VMit++){
		V = (*VMit).second;
		Perimeter += V.Mod();
	}
	return Perimeter;
}

//True si el punto P está dentro del polígono
bool Polygon::Inside(Point2D P) {
	//Para saber si el un punto está dentro del polígono:
	//- se traza un vector horizontal de P a infinito (en vez de usar el infinito
	//  uso la coordenada j mas a la derecha mas uno para evitar que la funcion Contains
	//  se desborde.
	//- se obtienen los puntos de corte con los segmentos que forman el polígono
	//- si el número de cortes es impar entonces está dentro si no está fuera

	DirectedLineSegment VBase;
	double XL,XR,YD,YU;

    Rectangle(XL,XR,YD,YU);
//printf("XL:%.30g,XR:%.30g,YD:%.30g,YU:%.30g\n",XL,XR,YD,YU);

    //Realizo el proceso haciendolo dos veces:
    //- La primera trazando un vector horizontal de P al infinito derecho (XR+1)
    //- La segunda trazando un vector vertical   de P al infinito superior (YU+1)
    //Hago el OR con los dos resultados.
    //De esta forma el unico punto para el que el resultado es erroneo es el centro
    //de un rombo.

    return CheckVBase(P,DirectedLineSegment(P,Point2D(XR+1,P.y()))) || 
           CheckVBase(P,DirectedLineSegment(P,Point2D(P.x(),YU+1)));

}

bool Polygon::CheckVBase(Point2D P,DirectedLineSegment VBase)
{
	DirectedLineSegment V1;
    DirectedLineSegmentMap::iterator VMit1;
	Point2D PCross,PUp,PDown,PLeft,PRight;
	unsigned int CrossCount = 0;
	bool isVertex;
	Point2DVector::iterator PVit;

//printf("P(x,y):");P.Show();
	
	//Si P es un vértice entonces está en el conjunto de puntos
	//que forman el polígono.
	PVit = find(begin(),end(),P);
	if (PVit != end()){
//printf("P es un vertice\n");
        return true;
	}
	
    //Si pertenece a un vector entonces está dentro del
    //polígono
	for (VMit1 = Sides.begin(); VMit1 != Sides.end(); VMit1++) {
		V1 = (*VMit1).second;
		if (V1.Contains(P)){
//printf("P es pertenece al vector: %i\n",(*VMit1).first);
			return true;		  
		}
	}

	for (VMit1 = Sides.begin(); VMit1 != Sides.end(); VMit1++) {
		V1 = (*VMit1).second;
		PCross = VBase.Intersection(V1);
//printf("PCross(x,y):");PCross.Show();
//VBase.p().Show();
//VBase.q().Show();
//printf("VBase.Contains(PCross): %i\n",VBase.Contains(PCross));
//V1.p().Show();
//V1.q().Show();
//printf("V1.Contains(PCross)   : %i\n",V1.Contains(PCross));
//printf("\n");

		if (VBase.Contains(PCross) &&    //Si el punto de corte pertenece al vector y a la recta base ...
				 V1.Contains(PCross)      ) {
			//Estudio si el punto de corte es un vértice
			PVit = find(begin(),end(),PCross);
			isVertex = (PVit != end());
			//Si el punto de corte es un vértice entonces la determinación de si el punto está 
			//dentro del polígono se hace viendo si lo están los de alrededor. Esto es así
			//porque aquí no se llega si el punto de corte pertenece al vector.
			if (isVertex){
//printf("PCross isVertex\n");
                return false;
            }
			//Si no es un vértice sumo uno a la cuenta de cortes.
			else {
					CrossCount++;
			}
		}
//printf("CrossCount:%i\n",CrossCount);
	}
		
	//Si el número de cortes es impar entonces el punto está dentro del polígono.
	if ((CrossCount % 2) == 1){
//printf("El numero de cortes es impar\n");
		return true;
	}
	else //Repito el proceso
        return false;
}



void Polygon::Show()
{
	double XL,XR,YD,YU;
	Point2DVector PV;

	printf("isValid(): %i\n",isValid());
	Point2DVector::Show();
	if (isValid()){
		PV = Rectangle(XL,XR,YD,YU);
		printf("XL:%.30g,XR:%.30g,YD:%.30g,YU:%.30g\n",XL,XR,YD,YU);
		Sides.Show();
	//	PV.Show();
	}
}













Polygon::DirectedLineSegmentMap::DirectedLineSegmentMap(){}

Polygon::DirectedLineSegmentMap::~DirectedLineSegmentMap(){}

//Visualization
void Polygon::DirectedLineSegmentMap::Show()
{
	DirectedLineSegmentMap::iterator it;
	Vector V;
	for (it = begin(); it != end(); it++)
	{
		printf("%i:",(*it).first);
		V = (*it).second;
		V.Show();
	}
}

/*
size_t Polygon::DirectedLineSegmentMap::Serialize(FILE * stream)
{
	size_t count  = 0;
	size_t VMsize = 0;

	unsigned int	ui;
	Vector			v;

	VMsize = size();
	count += sizeof(size_t)*fwrite(&VMsize, sizeof(size_t),1,stream);

	DirectedLineSegmentMap::iterator it;
	for (it = begin(); it != end(); it++)
	{
		ui = (*it).first;
		v = (*it).second;
		count += sizeof(unsigned int) *fwrite(&ui, sizeof(unsigned int)   ,1,stream);
		count += v.Serialize(stream);
	}

	return count;
}
*/

/*
//Serialize
size_t Polygon::Serialize(FILE * stream)
{
	double IU,ID,JL,JR;
	double perimeter;
	PointVector PV;
	nCompVector nCV;
	
	size_t count  = 0;

	PV        = Rectangle(IU,ID,JL,JR);
	perimeter = Perimeter();
//	nCV		  = m4();

	//count += PointVector::Serialize(stream);
	count += sizeof(double)*fwrite(&IU, sizeof(double),1,stream);
	count += sizeof(double)*fwrite(&ID, sizeof(double),1,stream);
	count += sizeof(double)*fwrite(&JL, sizeof(double),1,stream);
	count += sizeof(double)*fwrite(&JR, sizeof(double),1,stream);
	count += sizeof(double)*fwrite(&perimeter, sizeof(double),1,stream);
//	count += nCV.Serialize(stream);

	return count;
}

void Polygon::Show()
{
	double IU,ID,JL,JR;
	PointVector PV;

	printf("isValid(): %i\n",isValid());
	if (isValid()){
		PV = Rectangle(IU,ID,JL,JR);
		printf("IU:%.30g,ID:%.30g,JL:%.30g,JR:%.30g\n",IU,ID,JL,JR);
		PointVector::Show();
		Sides.Show();
	//	PV.Show();
	}
}

void Polygon::push_back(const Point & P)
{
	DirectedSegmentMap::iterator   VMit;
	PointVector::iterator PVit;
	unsigned int LastLabel;
	Point PA,PBegin,PEnd;
	Vector V;

	PVit = find(begin(),end(),P);
	if (PVit == end()){
		//Si hay 2 o más puntos ...
		if (size()>=2) {
			//Quito el ultimo vector ya que es el que cierra el polígono
			VMit      = Sides.end();
			Sides.erase(--VMit); 
			//Obtengo cual es la última Label
			VMit      = Sides.end();
			--VMit;
			LastLabel = (*VMit).first;//Obtengo cual es la última Label
			//Obtengo el primer y último punto del polígono
			PBegin    = *begin();
			PVit      = end();
			PEnd      = *(--PVit);
			//Inserto el vector formado por el último y el nuevo punto
			Sides.insert(DirectedSegmentMap::value_type(LastLabel+1,Vector(PEnd,P)));
			//Inserto el vector que cierra el polígono
			Sides.insert(DirectedSegmentMap::value_type(LastLabel+2,Vector(P,PBegin)));
			//Inserto el nuevo punto P
			PointVector::push_back(P); 
		}
		else if (size()==1) {
			PBegin    = *begin();
			LastLabel = 0;
			//Inserto el vector formado por el único punto existente hasta ahora
			//y el nuevo punto
			Sides.insert(DirectedSegmentMap::value_type(LastLabel+1,Vector(PBegin,P)));
			//Inserto el vector que cierra el polígono que en este caso, con sólo dos
			//puntos, es el mismo vector con sentido contrario. Esto lo hago por
			//coherencia con el algoritmo.
			Sides.insert(DirectedSegmentMap::value_type(LastLabel+2,Vector(P,PBegin)));
			//Inserto el nuevo punto P
			PointVector::push_back(P); //Inserto el nuevo punto P
		}
		else if (size()==0) {
			PointVector::push_back(P); //Inserto el nuevo punto P
		}
	}
}

void Polygon::pop_back()
{
	DirectedSegmentMap::iterator   VMit;
	PointVector::iterator PVit;
	unsigned int LastLabel;
	Point PA,PBegin,PEnd;

	//Si hay más de un punto ...
	if (size()>2) {
		//Primero quito el vector que cierra el polígono
		VMit = Sides.end();
		Sides.erase(--VMit);
		//Quito el último vector
		VMit = Sides.end();
		Sides.erase(--VMit);
		//Elimino el último punto P
		PointVector::pop_back(); 
		//Obtengo la última Label
		VMit = Sides.end();
		--VMit;
		LastLabel = (*VMit).first;
		//Obtengo el primer y el último punto del polígono
		PBegin    = *begin();
		PVit      = end();
		--PVit;
		PEnd      = *PVit;
		//Inserto el vector que cierra el polígono
		Sides.insert(DirectedSegmentMap::value_type(LastLabel+1,Vector(PEnd,PBegin)));
	}
	else if (size()==2) {
		//Primero quito el vector que cierra el polígono
		VMit = Sides.end();
		//Quito el último vector
		Sides.erase(--VMit);
		VMit = Sides.end();
		Sides.erase(--VMit); 
		//Elimino el último punto P
		PointVector::pop_back();
	}
	else if (size()==1) {
		//Elimino el último y único punto P
		PointVector::pop_back(); //Elimino el último y único punto P
	}
	
}

bool Polygon::isValid(){
	DirectedSegmentMap::iterator VMit1, VMit2;
	Vector V1,V2;
	Point P;

	if (Sides.size()<3)
		return false;
	for (VMit1 = Sides.begin(); VMit1 != Sides.end(); VMit1++)
		for (VMit2 = Sides.begin(); VMit2 != Sides.end(); VMit2++) {
			if ((*VMit1).first!=(*VMit2).first) {
				V1 = (*VMit1).second;
				V2 = (*VMit2).second;
				P = V1.Intersection(V2);
//printf("P.Distance(V1.GetA()):%.30g\n",P.Distance(V1.GetA()));
//printf("P.Distance(V1.GetB()):%.30g\n",P.Distance(V1.GetB()));
				if (V1.BelongToVector(P) &&
					V2.BelongToVector(P) &&
					(P.Distance(V1.GetA())>1.0e-10) &&		//Debería ser P != V1.GetA() y P != V1.GetB() pero se hace con la distancia
					(P.Distance(V1.GetB())>1.0e-10)  )   {	//debido a los errores de precisión que se cometen al obtener la intersección.
						return false;
				}
			}
		}

	return true;
}

//True si el punto P está dentro del polígono
bool Polygon::Inside(Point P) {
	//Para saber si el un punto está dentro del polígono:
	//- se traza un vector horizontal de P a infinito (en vez de usar el infinito
	//  uso la coordenada j mas a la derecha mas uno para evitar que la funcion BelongToVector
	//  se desborde.
	//- se obtienen los puntos de corte con los segmentos que forman el polígono
	//- si el número de cortes es impar entonces está dentro si no está fuera

	Vector V1,VBase;
	DirectedSegmentMap::iterator VMit1;
	Point PCross,PUp,PDown,PLeft,PRight;
	unsigned int CrossCount = 0;
	bool isVertex;
	PointVector::iterator PVit;
	double IU,ID,JL,JR;

//printf("P(i,j):");P.Show();
	
	Rectangle(IU,ID,JL,JR);
	VBase.Set(P,Point(P.i,JR+1));

	//Si P es un vértice entonces está en el conjunto de puntos
	//que forman el polígono.
	PVit = find(begin(),end(),P);
	if (PVit != end()){
//printf("P es un vertice\n");
		return true;
	}
	
	for (VMit1 = Sides.begin(); VMit1 != Sides.end(); VMit1++) {
		V1 = (*VMit1).second;
		if (V1.BelongToVector(P)){ //Si pertenece a un vector entonces está dentro del
//printf("P es pertenece al vector: %i\n",(*VMit1).first);
			return true;		   //polígono
		}
	}


	for (VMit1 = Sides.begin(); VMit1 != Sides.end(); VMit1++) {
		V1 = (*VMit1).second;
		PCross = VBase.Intersection(V1);
//printf("PCross(i,j):");PCross.Show();
//VBase.Show();
//printf("VBase.BelongToVector(PCross): %i\n",VBase.BelongToVector(PCross));
//V1.Show();
//printf("V1.BelongToVector(PCross)   : %i\n",V1.BelongToVector(PCross));
//printf("\n");

		if (VBase.BelongToVector(PCross) &&    //Si el punto de corte pertenece al vector y a la recta base ...
				 V1.BelongToVector(PCross)      ) {
			//Estudio si el punto de corte es un vértice
			PVit = find(begin(),end(),PCross);
			isVertex = (PVit != end());
			//Si el punto de corte es un vértice entonces la determinación de si el punto está 
			//dentro del polígono se hace viendo si lo están los de alrededor. Esto es así
			//porque aquí no se llega si el punto de corte pertenece al vector.
			if (isVertex){
				return false;
			}
			//Si no es un vértice sumo uno a la cuenta de cortes.
			else {
					CrossCount++;
			}
		}
//printf("CrossCount:%i\n",CrossCount);
	}
		
	//Si el número de cortes es impar entonces el punto está dentro del polígono.
	if ((CrossCount % 2) == 1){
//printf("El numero de cortes es impar\n");
		return true;
	}
	else 
		return false;
}

PointVector Polygon::Rectangle(double & IU,double & ID,double & JL,double & JR)
{
	Point RecPA;	//Coordenadas del rectángulo en el que está inscrito
	Point RecPB;	//     ---------- j
	Point RecPC;	//    |           
	Point RecPD;	//    |  A---B 
					//    |  |   |
	                //    |  D---C
	                //    |
	                //    |i

	Point P;
	PointVector::iterator PVit;
	PointVector Rectangle;

	PVit = begin();
	P    = *PVit;
	IU   = P.i;
	ID   = P.i;
	JL   = P.j;
	JR   = P.j;

	for (PVit++; PVit != end(); PVit++) {
		P = *PVit;
		if (P.i < IU) IU = P.i; 
		if (P.i > ID) ID = P.i; 
		if (P.j < JL) JL = P.j; 
		if (P.j > JR) JR = P.j; 
	}

	Rectangle.push_back(Point(IU,JL)); //A
	Rectangle.push_back(Point(IU,JR)); //B
	Rectangle.push_back(Point(ID,JR)); //C
	Rectangle.push_back(Point(ID,JL)); //D

	return Rectangle;
}


double Polygon::Perimeter()
{
	DirectedSegmentMap::iterator VMit;
	Vector V;
	double Perimeter = 0.0;

	//El perímetro es la suma de los módulos de los lados del polígono
	for (VMit=Sides.begin();VMit!=Sides.end();VMit++){
		V = (*VMit).second;
		Perimeter += V.Mod();
	}
	return Perimeter;
}

*/

/*
DirectedSegmentMap::DirectedSegmentMap()
{

}

DirectedSegmentMap::~DirectedSegmentMap()
{

}

//Visualization
void DirectedSegmentMap::Show()
{
	DirectedSegmentMap::iterator it;
	Vector V;
	for (it = begin(); it != end(); it++)
	{
		printf("%i:",(*it).first);
		V = (*it).second;
		V.Show();
	}
}

size_t DirectedSegmentMap::Serialize(FILE * stream)
{
	size_t count  = 0;
	size_t VMsize = 0;

	unsigned int	ui;
	Vector			v;

	VMsize = size();
	count += sizeof(size_t)*fwrite(&VMsize, sizeof(size_t),1,stream);

	DirectedSegmentMap::iterator it;
	for (it = begin(); it != end(); it++)
	{
		ui = (*it).first;
		v = (*it).second;
		count += sizeof(unsigned int) *fwrite(&ui, sizeof(unsigned int)   ,1,stream);
		count += v.Serialize(stream);
	}

	return count;
}
*/



