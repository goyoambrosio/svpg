/****
  SoftVision. Software for Computer Vision

  Gregorio Ambrosio Cestero (goyo@computer.org)
  System Engineering and Automation Department 
  University of Malaga. Spain                   

  $RCSfile: ConvexPerceptualGroup.cpp,v $
  $Revision: 1.1 $
  $Date: 2000/01/21 13:03:57 $
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


// ConvexPerceptualGroup.cpp: implementation of the PerceptualGroup class.
//
//////////////////////////////////////////////////////////////////////

#include "ConvexPerceptualGroup.h"

namespace GAC
{

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ConvexPerceptualGroup::ConvexPerceptualGroup()
{
	//Incializacion de variables
	Closed    = false;

	Perimeter = 0.0;
	Area      = 0.0;
	BinCentroid.Set(0.0,0.0);
	GrayCentroid.Set(0.0,0.0);
	cm00=cm01=cm10=cm02=cm11=cm20=cm03=cm12=cm21=cm30=0.0;

	//Inicializacion de lo codigos y mensajes de error
//	insert(Error::value_type(2000,"The Convex Group is closed"));
//	insert(Error::value_type(2001,"This is not a valid relation"));
}

ConvexPerceptualGroup::~ConvexPerceptualGroup()
{

}

ConvexPerceptualGroup ConvexPerceptualGroup::push_back(Relation R){
	RelationVector::const_iterator RVit;
	unsigned int LastRSBLabel, FirstRSALabel;

	//Si el CPG esta cerrado no admito la nueva relacion y elevo un error
	if (Closed) {
		CPGError.SetErrorCode(2000);
		return *this;
	}

	//Si todavia no contiene ninguna relacion la primera relacion
	//probablemente sera del tipo REL_PROP_ITSELF con lo que inicializo
	//los valores.

	//Si el Convex Group no tiene ninguna relacion ...
	if (RelationVector::size() == 0) {
		//... y si la relacion que se va a introducir es del tipo REL_PROP_ITSELF
		//la añado y dejo el grupo cerrado.
		if (R.Property == REL_PROP_ITSELF) {
			RelationVector::push_back(R);
			Closed = false; //Considero que un grupo con un solo segmento esta cerrado
			return *this;
		}
		//... en cambio, si la relacion no es del tipo REL_PROP_ITSELF
		//la añado y dejo el grupo abierto.
		else {
			RelationVector::push_back(R);
			Closed = false; //Considero que un grupo con un solo segmento esta cerrado
			return *this;
		}
	}
	else { //Si es la segunda o posterior relacion ...
		//... y si esta cerrado.
		if (Closed) {
			CPGError.SetErrorCode(2000); //elevo el error y termino.
			return *this;
		}
		//... y si, en cambio, esta abierto
		else {
			RVit = RelationVector::end();
			LastRSBLabel = (*--RVit).SBLabel;
			RVit = RelationVector::begin();
			FirstRSALabel = (*RVit).SALabel;
			//Si el segundo segmento de la ultima relacion es igual al
			//primer segmento de la nueva relacion que queremos añadir entonces
			//admito la relacion porque mantiene la cadena de segmentos.
			if (LastRSBLabel == R.SALabel) {
				Closed = (R.SBLabel == FirstRSALabel); //Veo si este segmento cierra el grupo
				RelationVector::push_back(R);
				return *this;
			}
			//Si la relacion no continua con la cadena, es decir, si el segundo segmento de
			//la ultima relacion NO es igual al primer segmento de la relacion que queremos añadir
			//entonces no admito la relacion y elevo un error.
			else {
				CPGError.SetErrorCode(2001); //elevo el error y termino.
				return *this;
			}
		}
	}
}

ConvexPerceptualGroup ConvexPerceptualGroup::pop_back(){
	//En el caso de borrar una relacion el grupo siempre
	//se va a quedar abierto.
	Closed = false;
	RelationVector::pop_back();
	return *this;
}

ConvexPerceptualGroup ConvexPerceptualGroup::clear(){
	//En el caso de borrar todas las relaciones
	//el grupo se queda abierto.
	Closed = false;
	RelationVector::clear();
	return *this;
}

			
double ConvexPerceptualGroup::GetL1n(SegmentMap BaseSM){
	Segment S;
	double L = 0.0;
	unsigned int SLabel;
	SegmentMap::const_iterator SMit;
	LabelVector LV;
	LabelVector::const_iterator LVit;

	//Obtengo las etiquetas de todos los segmentos que componen el grupo
	LV = GetLabels();
	//Sumo en L las longitudes de todos los segmentos.
	for (LVit = LV.begin(); LVit != LV.end(); LVit++) {
		SLabel = (*LVit);
		SMit = BaseSM.find(SLabel);
		S = (*SMit).second;
		L += S.Mod();
	}
	return L;
}

void ConvexPerceptualGroup::GetG1n(double *G){
	RelationVector::iterator RVit;

	//Como cada relacion almacena la distancia (segun el algoritmo de Jacob) 
	//entre los dos segmentos que la componen, simplemente recorro las relaciones
	//con un bucle.
	for (RVit = RelationVector::begin(); RVit != RelationVector::end(); RVit++) {
		*G += (*RVit).Dist;
	}
}


double ConvexPerceptualGroup::GetAngle1n(){
	double Angle = 0;
	RelationVector::iterator RVit;

	//Como cada relacion almacena el angulo (segun el algoritmo de Jacob) 
	//entre los dos segmentos que la componen, simplemente recorro las relaciones
	//con un bucle.
	for (RVit = RelationVector::begin(); RVit != RelationVector::end(); RVit++) {
		Angle += (*RVit).Angle;
	}
	return Angle;
}

double ConvexPerceptualGroup::GetSalienceFraction(SegmentMap BaseSM){
	double L1n,G1n;
	L1n = 0;
	G1n = 0;

	L1n = GetL1n(BaseSM);
	GetG1n(&G1n);
	return (L1n/(L1n+G1n));
}

bool ConvexPerceptualGroup::IsClosed(){
	return Closed;
}

//Serialize
size_t ConvexPerceptualGroup::Serialize(FILE * stream)
{
	size_t count  = 0;
	double Perimeter,Area,bic,bjc,gic,gjc,cm00,cm01,cm10,cm02,cm11,cm20,cm03,cm12,cm21,cm30;
	Point bCentroid, gCentroid;

	Perimeter = GetPerimeter();
	Area = GetArea();
	bCentroid = GetBinCentroid();
	bic = bCentroid.i;
	bjc = bCentroid.j;
	gCentroid = GetGrayCentroid();
	gic = gCentroid.i;
	gjc = gCentroid.j;
	cm00 = Getcm00();
	cm01 = Getcm01();
	cm10 = Getcm10();
	cm02 = Getcm02();
	cm11 = Getcm11();
	cm20 = Getcm20();
	cm03 = Getcm03();
	cm12 = Getcm12();
	cm21 = Getcm21();
	cm30 = Getcm30();


	//TODO:Serializar las propiedades particulares del ConvexPerceptualGroup
	count += PerceptualGroup::Serialize(stream);
	count += sizeof(double)*fwrite(&Area, sizeof(double),1,stream);
	count += sizeof(double)*fwrite(&Perimeter, sizeof(double),1,stream);
	count += sizeof(double)*fwrite(&bic, sizeof(double),1,stream);
	count += sizeof(double)*fwrite(&bjc, sizeof(double),1,stream);
	count += sizeof(double)*fwrite(&gic, sizeof(double),1,stream);
	count += sizeof(double)*fwrite(&gjc, sizeof(double),1,stream);
	count += sizeof(double)*fwrite(&cm00, sizeof(double),1,stream);
	count += sizeof(double)*fwrite(&cm01, sizeof(double),1,stream);
	count += sizeof(double)*fwrite(&cm10, sizeof(double),1,stream);
	count += sizeof(double)*fwrite(&cm02, sizeof(double),1,stream);
	count += sizeof(double)*fwrite(&cm11, sizeof(double),1,stream);
	count += sizeof(double)*fwrite(&cm20, sizeof(double),1,stream);
	count += sizeof(double)*fwrite(&cm03, sizeof(double),1,stream);
	count += sizeof(double)*fwrite(&cm12, sizeof(double),1,stream);
	count += sizeof(double)*fwrite(&cm21, sizeof(double),1,stream);
	count += sizeof(double)*fwrite(&cm30, sizeof(double),1,stream);

	return count;
}

size_t ConvexPerceptualGroup::FeatureVectorSerialize(FILE * stream)
{
	size_t count  = 0;
	double Perimeter,Area,bic,bjc,gic,gjc,cm00,cm01,cm10,cm02,cm11,cm20,cm03,cm12,cm21,cm30;
	Point bCentroid, gCentroid;
	double CPGLabel,FathersSize,ChildrenSize;

	CPGLabel     = Label;
	FathersSize  = GetFathers().size();
	ChildrenSize = GetChildren().size();

	Perimeter = GetPerimeter();
	Area = GetArea();
	bCentroid = GetBinCentroid();
	bic = bCentroid.i;
	bjc = bCentroid.j;
	gCentroid = GetGrayCentroid();
	gic = gCentroid.i;
	gjc = gCentroid.j;
	cm00 = Getcm00();
	cm01 = Getcm01();
	cm10 = Getcm10();
	cm02 = Getcm02();
	cm11 = Getcm11();
	cm20 = Getcm20();
	cm03 = Getcm03();
	cm12 = Getcm12();
	cm21 = Getcm21();
	cm30 = Getcm30();

	count += sizeof(double)*fwrite(&CPGLabel,  sizeof(double),1,stream);
	count += sizeof(double)*fwrite(&FathersSize,  sizeof(double),1,stream);
	count += sizeof(double)*fwrite(&ChildrenSize, sizeof(double),1,stream);
	count += sizeof(double)*fwrite(&Area, sizeof(double),1,stream);
	count += sizeof(double)*fwrite(&Perimeter, sizeof(double),1,stream);
	count += sizeof(double)*fwrite(&bic, sizeof(double),1,stream);
	count += sizeof(double)*fwrite(&bjc, sizeof(double),1,stream);
	count += sizeof(double)*fwrite(&gic, sizeof(double),1,stream);
	count += sizeof(double)*fwrite(&gjc, sizeof(double),1,stream);
	count += sizeof(double)*fwrite(&cm00, sizeof(double),1,stream);
	count += sizeof(double)*fwrite(&cm01, sizeof(double),1,stream);
	count += sizeof(double)*fwrite(&cm10, sizeof(double),1,stream);
	count += sizeof(double)*fwrite(&cm02, sizeof(double),1,stream);
	count += sizeof(double)*fwrite(&cm11, sizeof(double),1,stream);
	count += sizeof(double)*fwrite(&cm20, sizeof(double),1,stream);
	count += sizeof(double)*fwrite(&cm03, sizeof(double),1,stream);
	count += sizeof(double)*fwrite(&cm12, sizeof(double),1,stream);
	count += sizeof(double)*fwrite(&cm21, sizeof(double),1,stream);
	count += sizeof(double)*fwrite(&cm30, sizeof(double),1,stream);

	return count;
}
//Visualization
void ConvexPerceptualGroup::Show(SegmentMap BaseSM)
{
	vector <LabelVector>::iterator vRVit;
	vector <LabelVector> Fathers,Children;

	printf("Total Angle: %g (%g)\n",grad(GetAngle1n()),GetAngle1n());
	printf("Total Salience Fraction: %g\n",GetSalienceFraction(BaseSM));
	printf("Polarity    : %i\n",GetPolarity());
	printf("Area        : %.30g\n",GetArea());
	printf("Perimeter   : %.30g\n",GetPerimeter());
	printf("BinCentroid : ");GetBinCentroid().Show();
	printf("GrayCentroid: ");GetGrayCentroid().Show();
	printf("Central moment(00) : %.30g\n",Getcm00());
	printf("Central moment(01) : %.30g\n",Getcm01());
	printf("Central moment(10) : %.30g\n",Getcm10());
	printf("Central moment(02) : %.30g\n",Getcm02());
	printf("Central moment(11) : %.30g\n",Getcm11());
	printf("Central moment(20) : %.30g\n",Getcm20());
	printf("Central moment(03) : %.30g\n",Getcm03());
	printf("Central moment(12) : %.30g\n",Getcm12());
	printf("Central moment(21) : %.30g\n",Getcm21());
	printf("Central moment(30) : %.30g\n",Getcm30());
	printf("Normalized Central moment(02) : %.30g\n",Getncm02());
	printf("Normalized Central moment(11) : %.30g\n",Getncm11());
	printf("Normalized Central moment(20) : %.30g\n",Getncm20());
	printf("Normalized Central moment(03) : %.30g\n",Getncm03());
	printf("Normalized Central moment(12) : %.30g\n",Getncm12());
	printf("Normalized Central moment(21) : %.30g\n",Getncm21());
	printf("Normalized Central moment(30) : %.30g\n",Getncm30());

	
	Fathers = GetFathers();
	printf("Fathers:\n");
	for (vRVit=Fathers.begin();vRVit!=Fathers.end();vRVit++){
		(*vRVit).Show();
		printf("\n");
	}

	Children = GetChildren();
	printf("Children:\n");
	for (vRVit=Children.begin();vRVit!=Children.end();vRVit++){
		(*vRVit).Show();
		printf("\n");
	}

	PerceptualGroup::Show();

}

void ConvexPerceptualGroup::ShowMoments()
{
	vector <LabelVector>::iterator vRVit;
	vector <LabelVector> Fathers,Children;

	printf("Total Angle: %g (%g)\n",grad(GetAngle1n()),GetAngle1n());
	printf("Polarity    : %i\n",GetPolarity());
	printf("Area        : %.30g\n",GetArea());
	printf("Perimeter   : %.30g\n",GetPerimeter());
	printf("BinCentroid : ");GetBinCentroid().Show();
	printf("GrayCentroid: ");GetGrayCentroid().Show();
	printf("Central moment(00) : %.30g\n",Getcm00());
	printf("Central moment(01) : %.30g\n",Getcm01());
	printf("Central moment(10) : %.30g\n",Getcm10());
	printf("Central moment(02) : %.30g\n",Getcm02());
	printf("Central moment(11) : %.30g\n",Getcm11());
	printf("Central moment(20) : %.30g\n",Getcm20());
	printf("Central moment(03) : %.30g\n",Getcm03());
	printf("Central moment(12) : %.30g\n",Getcm12());
	printf("Central moment(21) : %.30g\n",Getcm21());
	printf("Central moment(30) : %.30g\n",Getcm30());
	printf("Normalized Central moment(02) : %.30g\n",Getncm02());
	printf("Normalized Central moment(11) : %.30g\n",Getncm11());
	printf("Normalized Central moment(20) : %.30g\n",Getncm20());
	printf("Normalized Central moment(03) : %.30g\n",Getncm03());
	printf("Normalized Central moment(12) : %.30g\n",Getncm12());
	printf("Normalized Central moment(21) : %.30g\n",Getncm21());
	printf("Normalized Central moment(30) : %.30g\n",Getncm30());

	
	Fathers = GetFathers();
	printf("Fathers:\n");
	for (vRVit=Fathers.begin();vRVit!=Fathers.end();vRVit++){
		(*vRVit).Show();
		printf("\n");
	}

	Children = GetChildren();
	printf("Children:\n");
	for (vRVit=Children.begin();vRVit!=Children.end();vRVit++){
		(*vRVit).Show();
		printf("\n");
	}

	PerceptualGroup::Show();

}

ConvexPerceptualGroup & ConvexPerceptualGroup::SetSalience(const SegmentMap &SM)
{
	Salience = GetSalienceFraction(SM);
	return *this;
}

ConvexPerceptualGroup & ConvexPerceptualGroup::SetPerimeter()
{
	Perimeter = PerceptualGroup::Perimeter();
	return *this;
}

ConvexPerceptualGroup & ConvexPerceptualGroup::SetArea()
{
	Area = PerceptualGroup::Area();
	return *this;
}

ConvexPerceptualGroup & ConvexPerceptualGroup::SetBinCentroid()
{
	BinCentroid = PerceptualGroup::BinCentroid();
	return *this;
}

ConvexPerceptualGroup & ConvexPerceptualGroup::SetGrayCentroid(UcharMatrix Retina)
{
	GrayCentroid = PerceptualGroup::GrayCentroid(Retina);
	return *this;
}

ConvexPerceptualGroup &  ConvexPerceptualGroup::SetThirdOrderCentralMoments(UcharMatrix Retina)
{
	nCompVector nCV;
	double m00,m01,m10,m02,m11,m20,m03,m12,m21,m30;
	double ic,jc;

	m00 = PerceptualGroup::m1(0,0,Retina);
	m01 = PerceptualGroup::m1(0,1,Retina);
	m10 = PerceptualGroup::m1(1,0,Retina);
	m02 = PerceptualGroup::m1(0,2,Retina);
	m11 = PerceptualGroup::m1(1,1,Retina);
	m20 = PerceptualGroup::m1(2,0,Retina);
	m03 = PerceptualGroup::m1(0,3,Retina);
	m12 = PerceptualGroup::m1(1,2,Retina);
	m21 = PerceptualGroup::m1(2,1,Retina);
	m30 = PerceptualGroup::m1(3,0,Retina);

	ic = m10/m00;
	jc = m01/m00;

//printf("n02:%.30g\n",n02);
//printf("n03:%.30g\n",n03);
//printf("n11:%.30g\n",n11);
//printf("n12:%.30g\n",n12);
//printf("n20:%.30g\n",n20);
//printf("n21:%.30g\n",n21);
//printf("n30:%.30g\n",n30);
//printf("n32:%.30g\n",n32);

	//n00
	cm00 = m00;

	//n01
	cm01 = 0;

	//n10
	cm10 = 0;

	//n02
	cm02 = m02 - jc*m01;

	//n11
	cm11 = m11 - jc*m10;

	//n20
	cm20 = m20 - ic*m10;

	//n03
	cm03 = m03 -3*jc*m02 + 2*jc*jc*m01;

	//n12
	cm12 = m12 - 2*jc*m11 - ic*m02 + 2*jc*jc*m10;

	//n21
	cm21 = m21 - 2*ic*m11 - jc*m20 + 2*ic*ic*m01;

	//n30
	cm30 = m30 -3*ic*m20 + 2*m10*ic*ic;

	//Compute the normalized central moments
	//NCMpq = CMpq / (CM00^l);  l = (p+q)/2 + 1  for p+q >= 2
	ncm02 = cm02 / (pow(cm00,2));
	ncm11 = cm11 / (pow(cm00,2));
	ncm20 = cm20 / (pow(cm00,2));
	ncm03 = cm03 / (pow(cm00,2.5));
	ncm12 = cm12 / (pow(cm00,2.5));
	ncm21 = cm21 / (pow(cm00,2.5));
	ncm30 = cm30 / (pow(cm00,2.5));


//	vector <double>::const_iterator Vit;
//	for (Vit=n.begin();Vit!=n.end();Vit++)
//		printf("n:%.30g\n",*Vit);


	return *this;

}

ConvexPerceptualGroup & ConvexPerceptualGroup::SetFeatureVector(UcharMatrix Retina, SegmentMap SM)
{
	BoolMatrix BinMatrix;
	double IU,ID,JL,JR;
	int    iIU,iID,iJL,iJR;
	int i,j;
	double bic,bjc; //Binary Centroid coordinates
	double lic,ljc; //Gray level Centroid coordinates
	double m00,m01,m10,m02,m11,m20,m03,m12,m21,m30; //Moments to 3 degree

//printf("SetFeatureVector -----------------------------. BEGIN\n");

	//Obtengo las coordenadas del rectángulo en el que está inscrito
	//el polígono y las paso a enteros.
	Rectangle(IU,ID,JL,JR);
    iIU=IU;
	iID=ID;
	iJL=JL;
	iJR=JR;

//	printf("IU:%.30g,ID:%.30g,JL:%.30g,JR:%.30g\n",IU,ID,JL,JR);


	//Obtengo la matriz binaria (1:el pixel pertenece al CPG 0:el pixel no pertenece al CPG)
	BinMatrix = PerceptualGroup::binMatrix();

	//Calculo el perimetro
	Perimeter = PerceptualGroup::Perimeter();

	//Inicializo a cero las coordenadas del centroide
	bic=bjc=0;
	lic=ljc=0;

	//Calculo el área y las coordenadas del centroide binario
	//Recorro los puntos horizontalmente que pertenecen al rectángulo
	//Aquellos que pertenezcan al polígono suman uno.
	for (i=iIU;i<=iID;i++)
		for (j=iJL;j<=iJR;j++){
				Area+=BinMatrix[i-iIU][j-iJL];
				bic += i*BinMatrix[i-iIU][j-iJL];
				bjc += j*BinMatrix[i-iIU][j-iJL];
		}

	bic /= Area;
	bjc /= Area;

	BinCentroid.Set(bic,bjc);

	//Calculo los momentos de hasta orden tres
	m00 = ConvexPerceptualGroup::m1(0,0,Retina,BinMatrix,iIU,iID,iJL,iJR);
	m01 = ConvexPerceptualGroup::m1(0,1,Retina,BinMatrix,iIU,iID,iJL,iJR);
	m10 = ConvexPerceptualGroup::m1(1,0,Retina,BinMatrix,iIU,iID,iJL,iJR);
	m02 = ConvexPerceptualGroup::m1(0,2,Retina,BinMatrix,iIU,iID,iJL,iJR);
	m11 = ConvexPerceptualGroup::m1(1,1,Retina,BinMatrix,iIU,iID,iJL,iJR);
	m20 = ConvexPerceptualGroup::m1(2,0,Retina,BinMatrix,iIU,iID,iJL,iJR);
	m03 = ConvexPerceptualGroup::m1(0,3,Retina,BinMatrix,iIU,iID,iJL,iJR);
	m12 = ConvexPerceptualGroup::m1(1,2,Retina,BinMatrix,iIU,iID,iJL,iJR);
	m21 = ConvexPerceptualGroup::m1(2,1,Retina,BinMatrix,iIU,iID,iJL,iJR);
	m30 = ConvexPerceptualGroup::m1(3,0,Retina,BinMatrix,iIU,iID,iJL,iJR);

	//Calculo las coordenadas del centroide basado en niveles de grises
	lic = m10/m00;
	ljc = m01/m00;

	GrayCentroid.Set(lic,ljc);

	//Calculo los momentos centrales de hasta orden 3
	//n00
	cm00 = m00;

	//n01
	cm01 = 0;

	//n10
	cm10 = 0;

	//n02
	cm02 = m02 - ljc*m01;

	//n11
	cm11 = m11 - ljc*m10;

	//n20
	cm20 = m20 - lic*m10;

	//n03
	cm03 = m03 - 3*ljc*m02 + 2*ljc*ljc*m01;

	//n12
	cm12 = m12 - 2*ljc*m11 - lic*m02 + 2*ljc*ljc*m10;

	//n21
	cm21 = m21 - 2*lic*m11 - ljc*m20 + 2*lic*lic*m01;

	//n30
	cm30 = m30 - 3*lic*m20 + 2*m10*lic*lic;

	//Compute the normalized central moments
	//NCMpq = CMpq / (CM00^l);  l = (p+q)/2 + 1  for p+q >= 2
	ncm02 = cm02 / (pow(cm00,2));
	ncm11 = cm11 / (pow(cm00,2));
	ncm20 = cm20 / (pow(cm00,2));
	ncm03 = cm03 / (pow(cm00,2.5));
	ncm12 = cm12 / (pow(cm00,2.5));
	ncm21 = cm21 / (pow(cm00,2.5));
	ncm30 = cm30 / (pow(cm00,2.5));

//printf("SetFeatureVector -----------------------------. END\n");

	return *this;
}

double ConvexPerceptualGroup::m1(double p,double q,UcharMatrix Retina,BoolMatrix BinMatrix, int iIU,int iID,int iJL,int iJR)
{
	size_t i,j;
	double m = 0.0;

	for (i=iIU;i<=iID;i++)
		for (j=iJL;j<=iJR;j++)
//			m += pow(i,p)*pow(j,q)*BinMatrix[i-iIU][j-iJL]*Retina[i][j];
			m += pow(i,p)*pow(j,q)*BinMatrix[i-iIU][j-iJL];
	return m;
}

double ConvexPerceptualGroup::m2(double p,double q,UcharMatrix Retina,BoolMatrix BinMatrix, int iIU,int iID,int iJL,int iJR,double lic,double ljc)
{
	size_t i,j;
	double m = 0.0;

	for (i=iIU;i<=iID;i++)
		for (j=iJL;j<=iJR;j++)
			m += pow(i-lic,p)*pow(j-ljc,q)*BinMatrix[i-iIU][j-iJL]*Retina[i][j];
	return m;
}

ConvexPerceptualGroup & ConvexPerceptualGroup::SetPolarity(const SegmentMap & SM)
{
	RelationVector::const_iterator RVit;
	SegmentMap::const_iterator SMit;
	Segment S;
	int CPGPolarity;
	bool PolarityIntegrity;

	RVit = RelationVector::begin();
	SMit = SM.find((*RVit).SALabel);
	S = (*SMit).second;
	CPGPolarity = S.GetPolarity();

	for(RVit++;RVit!= RelationVector::end();RVit++)
	{
		SMit = SM.find((*RVit).SALabel);
		S = (*SMit).second;
		if (!(PolarityIntegrity = (CPGPolarity == S.GetPolarity()))){
			CPGPolarity = 0;
			break;
		}
	}
	Polarity = CPGPolarity;

	return *this;
}

double ConvexPerceptualGroup::GetSalience()		{return Salience;}
double ConvexPerceptualGroup::GetArea()			{return Area;}
double ConvexPerceptualGroup::GetPerimeter()	{return Perimeter;}
Point  ConvexPerceptualGroup::GetBinCentroid()	{return BinCentroid;}
Point  ConvexPerceptualGroup::GetGrayCentroid()	{return GrayCentroid;}
double ConvexPerceptualGroup::Getcm00()			{return cm00;}
double ConvexPerceptualGroup::Getcm01()			{return cm01;}
double ConvexPerceptualGroup::Getcm10()			{return cm10;}
double ConvexPerceptualGroup::Getcm02()			{return cm02;}
double ConvexPerceptualGroup::Getcm11()			{return cm11;}
double ConvexPerceptualGroup::Getcm20()			{return cm20;}
double ConvexPerceptualGroup::Getcm03()			{return cm03;}
double ConvexPerceptualGroup::Getcm12()			{return cm12;}
double ConvexPerceptualGroup::Getcm21()			{return cm21;}
double ConvexPerceptualGroup::Getcm30()			{return cm30;}
double ConvexPerceptualGroup::Getncm02()		{return ncm02;}
double ConvexPerceptualGroup::Getncm11()		{return ncm11;}
double ConvexPerceptualGroup::Getncm20()		{return ncm20;}
double ConvexPerceptualGroup::Getncm03()		{return ncm03;}
double ConvexPerceptualGroup::Getncm12()		{return ncm12;}
double ConvexPerceptualGroup::Getncm21()		{return ncm21;}
double ConvexPerceptualGroup::Getncm30()		{return ncm30;}

nCompVector ConvexPerceptualGroup::GetFeatureVector()
{
	nCompVector FV;

	FV.push_back(Area);
	FV.push_back(Perimeter);
	FV.push_back(BinCentroid.i);
	FV.push_back(BinCentroid.j);
	FV.push_back(GrayCentroid.i);
	FV.push_back(GrayCentroid.j);
	FV.push_back(cm00);
	FV.push_back(cm01);
	FV.push_back(cm10);
	FV.push_back(cm02);
	FV.push_back(cm11);
	FV.push_back(cm20);
	FV.push_back(cm03);
	FV.push_back(cm12);
	FV.push_back(cm21);
	FV.push_back(cm30);
	FV.push_back(ncm02);
	FV.push_back(ncm11);
	FV.push_back(ncm20);
	FV.push_back(ncm03);
	FV.push_back(ncm12);
	FV.push_back(ncm21);
	FV.push_back(ncm30);

	return FV;
}

int ConvexPerceptualGroup::GetPolarity(){return Polarity;}

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ConvexPerceptualGroupMap::ConvexPerceptualGroupMap()
{

}

ConvexPerceptualGroupMap::~ConvexPerceptualGroupMap()
{

}

//Visualization
void ConvexPerceptualGroupMap::Show(SegmentMap BaseSM)
{
	ConvexPerceptualGroup AuxCPG;
	LabelVector AuxLV;
	ConvexPerceptualGroupMap::iterator it;

	for (it = begin(); it != end(); it++)
	{
		AuxLV = (*it).first;
		AuxCPG = (*it).second;
		AuxLV.Show();
		printf("\n");
		AuxCPG.Show(BaseSM);
	}
}

//Serialize
size_t ConvexPerceptualGroupMap::Serialize(FILE * stream)
{
	size_t count  = 0;
	size_t CPGMsize = 0;

	LabelVector		lv;
	ConvexPerceptualGroup	cpg;
	ConvexPerceptualGroupMap::iterator it;

	CPGMsize = size();

	count += sizeof(size_t)*fwrite(&CPGMsize, sizeof(size_t),1,stream);

	for (it = begin(); it != end(); it++)
	{
		lv = (*it).first;
		cpg = (*it).second;
		count += lv.Serialize(stream);
		count += cpg.Serialize(stream);
	}

	return count;
}

//Serialize
size_t ConvexPerceptualGroupMap::FeatureVectorSerialize(FILE * stream)
{
	size_t count  = 0;
	size_t CPGMsize = 0;

	LabelVector		lv;
	ConvexPerceptualGroup	cpg;
	ConvexPerceptualGroupMap::iterator it;

	CPGMsize = size();

	count += sizeof(size_t)*fwrite(&CPGMsize, sizeof(size_t),1,stream);

	for (it = begin(); it != end(); it++)
	{
		//lv = (*it).first;
		cpg = (*it).second;
		//count += lv.Serialize(stream);
		count += cpg.FeatureVectorSerialize(stream);
	}

	return count;
}

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ConvexPerceptualGroupVector::ConvexPerceptualGroupVector()
{

}

ConvexPerceptualGroupVector::~ConvexPerceptualGroupVector()
{

}

//Visualization
void ConvexPerceptualGroupVector::Show(SegmentMap BaseSM)
{
	ConvexPerceptualGroup AuxCPG;
	ConvexPerceptualGroupVector::const_iterator it;

	for (it = begin(); it != end(); it++)
	{
		AuxCPG = *it;
		AuxCPG.Show(BaseSM);
		AuxCPG.ShowLabels();
	}
}

//Serialize
size_t ConvexPerceptualGroupVector::Serialize(FILE * stream)
{
	size_t count  = 0;
	size_t CPGVsize = 0;

	CPGVsize = size();
	count += sizeof(size_t)*fwrite(&CPGVsize, sizeof(size_t),1,stream);

	ConvexPerceptualGroupVector::iterator it;
	for (it = begin(); it != end(); it++)
	{
		count += (*it).Serialize(stream);	
	}

	return count;
}


} //namespace GAC

