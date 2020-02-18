/****
  SoftVision. Software for Computer Vision

  Gregorio Ambrosio Cestero (goyo@computer.org)
  System Engineering and Automation Department 
  University of Malaga. Spain                   

  $RCSfile: PerceptualGroup.h,v $
  $Revision: 1.1 $
  $Date: 2000/01/21 13:04:56 $
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


// PerceptualGroup.h: interface for the PerceptualGroup class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(_PERCEPTUALGROUP_H_)
#define _PERCEPTUALGROUP_H_

// The debugger can't handle symbols more than 255 characters long.
// STL often creates symbols longer than that.
// When symbols are longer than 255 characters, the warning is disabled.
#pragma warning(disable:4786)

#include <float.h>
#include <iostream.h>
#include <vector>
#include <algorithm>
#include "LabelVector.h"
#include "Polygon.h"
#include "Globals.h"

namespace GAC
{

//Valores de Relation::Property
//Tipos de propiedades que se cumplen en la relacion
#define NUM_PROP				5 //OJO Total del numero de procedimientos
#define REL_PROP_ITSELF			0
#define REL_PROP_PROXIMITY		1
#define REL_PROP_PARALLELISM	2
#define REL_PROP_COLINEARITY	3
#define REL_PROP_CONVEXITY   	4

class Relation
{
public:
	//Operators
	friend bool operator== (const Relation& R1,const Relation& R2);
	friend bool operator<  (const Relation& R1,const Relation& R2);

	//Visualization
	void Show();

	//Serialize
	size_t Serialize(FILE * stream);

public:
	unsigned int SALabel;		//Label del primer segmento
	unsigned int SBLabel;		//Label del segundo segmento
	unsigned int Property;		//Tipo de relacion que mantienen
	double		 Significance;	//Grado de significancia de la relacion
								//Este valor es inversamente proporcional a la probabilidad de que sea accidental en origen
	double		 Dist;			//Distancia entre los dos segmentos (este valor dependera
								//del metodo empleado para medirla)
	double		 Angle;			//Angulo que forman los dos segmentos

};

typedef vector<Relation> vRelation;

class RelationVector : public vRelation
{
public:
	RelationVector();
	virtual ~RelationVector();

	//Visualization
	void Show();
	void ShowLabels();

	//Serialize
	size_t Serialize(FILE * stream);

	LabelVector GetLabels();
	double GetSignificanceAcc(unsigned int Property);
	double GetSignificance(unsigned int Property);
	double GetRelationCount(unsigned int Property);
	double GetTotalSignificance();

	//Sobrecarga de funciones de vRelation
	//La sobrecarga la hago para controlar las variables contadoras
	//y acumuladoras referentes a las propiedades como SignificanceAcc
	//y RelationsCount. 
	//Tendria que hacer lo mismo con pop_back, erase, etc. Pero por falta de
	//tiempo lo hare segun me surja la necesidad.
	//Tambien tendria que heredar con private de vRelation lo que me
	//obligaria a sobrecargar todos las funciones.
	void push_back(const Relation & R);
	void clear();

public:
	unsigned int Label;

private:
	//Array de Significancias globales por propiedades:
	//SignificanceAcc[0]->Significance[REL_PROP_ITSELF]
	//SignificanceAcc[1]->Significance[REL_PROP_PROXIMITY]
	//SignificanceAcc[2]->Significance[REL_PROP_PARALLELISM]
	//SignificanceAcc[3]->Significance[REL_PROP_COLINEARITY]
	//Estas Significancias acumulan la suma de las significancias
	//por propiedad. Para acceder a este valor se usa la funcion
	//GetSignificance(Property) que devuelve la Significancia media
	//para esa propiedad.
	double SignificanceAcc	[NUM_PROP]; //Suma de las significancias por tipo propiedad
	double RelationsCount	[NUM_PROP]; //Numero de relaciones por propiedad

};


class PerceptualGroup : public RelationVector, public Polygon
{
public:
	PerceptualGroup();
	virtual ~PerceptualGroup();

	//Serialize
	size_t Serialize(FILE * stream);

	//Visualize
	void Show();

	double Area();		//Devuelve el área del polígono que forma el PG
	Point  BinCentroid();  //Devuelve el punto cuyas coordenadas son las del centroide (o Centro De Masa CDM) del polígono
	Point  GrayCentroid(UcharMatrix Retina);  //Devuelve el punto cuyas coordenadas son las del centroide (o Centro De Masa CDM) del polígono

	BoolMatrix binMatrix(); //Devuelve una matriz binaria del tamaño del rectángulo donde está inscrito el polígono
						      //Los valores a 1 indican puntos que están dentro del polígono
	double      m1(double p,double q,UcharMatrix Retina); //Momentos de orden p+q
	double      m2(double p,double q,UcharMatrix Retina); //Momentos centrales de orden p+q (invariantes a traslaciones)
	double      m3(double p,double q,UcharMatrix Retina); //Momentos centrales normalizados de orden p+q (invariantes a traslaciones y escalados)
	nCompVector m4(UcharMatrix Retina);   //Momentos invariantes a traslaciones, rotaciones y cambios de escala.

	PerceptualGroup &push_back_Father(LabelVector LV);
	PerceptualGroup &push_back_Child (LabelVector LV);
	vector<LabelVector> GetFathers();
	vector<LabelVector> GetChildren();

private:
	vector <LabelVector> Fathers;
	vector <LabelVector> Children;

};

typedef map <LabelVector, PerceptualGroup> mPerceptualGroup;

class PerceptualGroupMap : public mPerceptualGroup
{
public:
	PerceptualGroupMap();
	virtual ~PerceptualGroupMap();

	//Visualization
	void Show();

	//Serialize
	size_t Serialize(FILE * stream);

};

typedef vector <PerceptualGroup> vPerceptualGroup;

class PerceptualGroupVector : public vPerceptualGroup
{
public:
	PerceptualGroupVector();
	virtual ~PerceptualGroupVector();

	//Visualization
	void Show();

	//Serialize
	size_t Serialize(FILE * stream);

};


} //namespace GAC

#endif // !defined(_PERCEPTUALGROUP_H_)
