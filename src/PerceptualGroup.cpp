/****
  SoftVision. Software for Computer Vision

  Gregorio Ambrosio Cestero (goyo@computer.org)
  System Engineering and Automation Department 
  University of Malaga. Spain                   

  $RCSfile: PerceptualGroup.cpp,v $
  $Revision: 1.1 $
  $Date: 2000/01/21 13:04:55 $
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


// PerceptualGroup.cpp: implementation of the PerceptualGroup class.
//
//////////////////////////////////////////////////////////////////////

#include "PerceptualGroup.h"

namespace GAC
{

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

//Operators
bool operator== (const Relation& R1,const Relation& R2)
{
/*
	if (R1.Significance != R2.Significance){
		cout << "R1.Significance: " << R1.Significance << endl;
		cout << "R2.Significance: " << R2.Significance << endl;
		cout <<	"diff			: " << fabs(R1.Significance - R2.Significance) << endl;
	}
*/
	return	(R1.SALabel		 == R2.SALabel) &&
			(R1.SBLabel		 == R2.SBLabel) &&
			(R1.Property	 == R2.Property);
		//Tengo problemas de precision con los doubles.
		//En principio tendria que ir una linea mas tal como:
		//(R1.Significance	 == R2.Significance);
		//pero no sirve porque si se imprime la diferencia entre los
		//dos valores se observa un error de precion (e-16)
		//Si se usa la linea siguiente da un error en la clase VECTOR
		//(fabs(R1.Significance - R2.Significance)<DoubleEpsilon);
		//Asi que como en la mayoria de los casos cuando dos elementos
		//cumplen una propiedad esta es biounivoca he optado, de momento,
		//por ignorar el valor de la propiedad.
}

bool operator<  (const Relation& R1,const Relation& R2)
{
/*
	if (R1.SALabel == R2.SALabel)
		return (R1.SBLabel < R2.SBLabel);
	else
		return (R1.SALabel < R2.SALabel);
*/
	if (R1.SALabel != R2.SALabel) return (R1.SALabel < R2.SALabel);
	else
		if (R1.SBLabel != R2.SBLabel) return (R1.SBLabel < R2.SBLabel);
		else
			if (R1.Property != R2.Property) return (R1.Property < R2.Property);
			else
				if (R1.Significance != R2.Significance) return (R1.Significance < R2.Significance);
				else return false;
}

//Visualization
void Relation::Show()
{
	printf("R:<%i,%i,%i,%g> Angle: %g\n",SALabel,SBLabel,Property,Significance,Angle);
}

//Serialize
size_t Relation::Serialize(FILE * stream)
{
	size_t count   = 0;

	count += sizeof(unsigned int)*fwrite(&SALabel, sizeof(unsigned int),1,stream);
	count += sizeof(unsigned int)*fwrite(&SBLabel, sizeof(unsigned int),1,stream);
	count += sizeof(unsigned int)*fwrite(&Property, sizeof(unsigned int),1,stream);
	count += sizeof(double)*fwrite(&Significance, sizeof(double),1,stream);

	return count;
}

RelationVector::RelationVector()
{
	//Inicializo las Significancias gloables por propiedad
	SignificanceAcc	[REL_PROP_ITSELF]		= 0;
	SignificanceAcc	[REL_PROP_PROXIMITY]	= 0;
	SignificanceAcc	[REL_PROP_PARALLELISM]	= 0;
	SignificanceAcc	[REL_PROP_COLINEARITY]	= 0;
	SignificanceAcc	[REL_PROP_CONVEXITY]	= 0;
	RelationsCount	[REL_PROP_ITSELF]		= 0;
	RelationsCount	[REL_PROP_PROXIMITY]	= 0;
	RelationsCount	[REL_PROP_PARALLELISM]	= 0;
	RelationsCount	[REL_PROP_COLINEARITY]	= 0;
	RelationsCount	[REL_PROP_CONVEXITY]	= 0;
}

RelationVector::~RelationVector()
{

}

//Visualization
void RelationVector::Show()
{
	Relation AuxR;
	RelationVector::const_iterator it;

	printf("PG: %i\n",Label);
	for (it = begin(); it != end(); it++)
	{
		AuxR = *it;
		AuxR.Show();	
	}
	printf("\n");
}

void RelationVector::ShowLabels()
{
	LabelVector Labels;

	printf("PG(%i): ",Label);
	Labels = GetLabels();
	Labels.Show();
	printf("Sig:[%g,%g,%g,%g,%g]\n",
		GetSignificance(REL_PROP_ITSELF),
		GetSignificance(REL_PROP_PROXIMITY),
		GetSignificance(REL_PROP_PARALLELISM),
		GetSignificance(REL_PROP_COLINEARITY),
		GetSignificance(REL_PROP_CONVEXITY));
}

//Serialize
size_t RelationVector::Serialize(FILE * stream)
{
	size_t count  = 0;
	size_t RVsize = 0;

	RVsize = size();
	count += sizeof(unsigned int)*fwrite(&Label, sizeof(unsigned int),1,stream);
	count += sizeof(size_t)*fwrite(&RVsize, sizeof(size_t),1,stream);

	RelationVector::iterator it;
	for (it = begin(); it != end(); it++)
	{
		count += (*it).Serialize(stream);	
	}

	return count;
}

LabelVector RelationVector::GetLabels()
{
	LabelVector Labels;
	LabelVector::const_iterator LVit;
	Relation AuxR;
	RelationVector::const_iterator it;

	for (it = begin(); it != end(); it++)
	{
		AuxR = *it;
		LVit = find(Labels.begin(),Labels.end(),AuxR.SALabel);
		if (LVit==Labels.end()) Labels.push_back(AuxR.SALabel);
		LVit = find(Labels.begin(),Labels.end(),AuxR.SBLabel);
		if (LVit==Labels.end()) Labels.push_back(AuxR.SBLabel);
	}
	sort(Labels.begin(),Labels.end());
	return Labels;
}

double RelationVector::GetSignificanceAcc(unsigned int Property)
{
	if (RelationsCount[Property])
		return SignificanceAcc[Property];
	else
		return 0;
}


double RelationVector::GetSignificance(unsigned int Property)
{
	if (RelationsCount[Property])
		return SignificanceAcc[Property]/RelationsCount[Property];
	else
		return 0;
}

double RelationVector::GetTotalSignificance()
{
	double TotalSignificance = 0;
	for (unsigned int i = 0; i < NUM_PROP; i++){
		TotalSignificance += GetSignificance(i);
	}
	TotalSignificance /= NUM_PROP;
	return TotalSignificance;
}

double RelationVector::GetRelationCount(unsigned int Property)
{
	return RelationsCount[Property];
}


void RelationVector::push_back(const Relation & R){
	switch (R.Property) {
	case REL_PROP_ITSELF:
		{
			SignificanceAcc[REL_PROP_ITSELF] += R.Significance;
			RelationsCount[REL_PROP_ITSELF]++;
		}
		break;
	case REL_PROP_PROXIMITY:
		{
			SignificanceAcc[REL_PROP_PROXIMITY] += R.Significance;
			RelationsCount[REL_PROP_PROXIMITY]++;
		}
		break;
	case REL_PROP_PARALLELISM:
		{
			SignificanceAcc[REL_PROP_PARALLELISM] += R.Significance;
			RelationsCount[REL_PROP_PARALLELISM]++;
		}
		break;
	case REL_PROP_COLINEARITY:
		{
			SignificanceAcc[REL_PROP_COLINEARITY] += R.Significance;
			RelationsCount[REL_PROP_COLINEARITY]++;
		}
	case REL_PROP_CONVEXITY:
		{
			SignificanceAcc[REL_PROP_CONVEXITY] += R.Significance;
			RelationsCount[REL_PROP_CONVEXITY]++;
		}
		break;
	}
	vRelation::push_back(R);
}

void RelationVector::clear(){
	//Inicializo las Significancias gloables por propiedad
	SignificanceAcc	[REL_PROP_ITSELF]		= 0;
	SignificanceAcc	[REL_PROP_PROXIMITY]	= 0;
	SignificanceAcc	[REL_PROP_PARALLELISM]	= 0;
	SignificanceAcc	[REL_PROP_COLINEARITY]	= 0;
	SignificanceAcc	[REL_PROP_CONVEXITY]	= 0;
	RelationsCount	[REL_PROP_ITSELF]		= 0;
	RelationsCount	[REL_PROP_PROXIMITY]	= 0;
	RelationsCount	[REL_PROP_PARALLELISM]	= 0;
	RelationsCount	[REL_PROP_COLINEARITY]	= 0;
	RelationsCount	[REL_PROP_CONVEXITY]	= 0;
	vRelation::clear();
}


PerceptualGroup::PerceptualGroup()
{

}

PerceptualGroup::~PerceptualGroup()
{

}

//Serialize
size_t PerceptualGroup::Serialize(FILE * stream)
{
	size_t count  = 0;
//	double area;
//	Point P;

//	area  = Area();
//	P     = Centroid();

	count += RelationVector::Serialize(stream);
//	count += Polygon::Serialize(stream);
//	count += sizeof(double)*fwrite(&area, sizeof(double),1,stream);
//	count += P.Serialize(stream);

	return count;
}

//Visualization
void PerceptualGroup::Show()
{
	RelationVector::Show();
//	Polygon::Show();

	printf("--------------------------------------\n");
}

double PerceptualGroup::Area()
{
	double IU,ID,JL,JR;
	int i,j;
	double Area = 0;

	//Obtengo las coordenadas del rectángulo en el que está inscrito
	//el polígono
	Rectangle(IU,ID,JL,JR);

	//Recorro los puntos horizontalmente que pertenecen al rectángulo
	//Aquellos que pertenezcan al polígono suman uno.
	for (i=IU;i<=ID;i++)
		for (j=JL;j<=JR;j++)
			if (Inside(Point(i,j)))
				Area++;

	return Area;
}

Point PerceptualGroup::BinCentroid()
{
	double IU,ID,JL,JR;
	int i,j;
	double ic = 0,jc = 0;
	double Area = 0;

	//Obtengo las coordenadas del rectángulo en el que está inscrito
	//el polígono
	Rectangle(IU,ID,JL,JR);

	//Recorro los puntos horizontalmente que pertenecen al rectángulo
	for (i=IU;i<=ID;i++)
		for (j=JL;j<=JR;j++)
			if (Inside(Point(i,j))){
//printf("Inside: ");
//Point(i,j).Show();
				Area++;
				ic += i;
				jc += j;
			}

	ic /= Area;
	jc /= Area;

	return Point(ic,jc);
}

Point PerceptualGroup::GrayCentroid(UcharMatrix Retina)
{
	double m00,m01,m10;
	double ic = 0,jc = 0;

	m00 = m1(0,0,Retina);
	m01 = m1(0,1,Retina);
	m10 = m1(1,0,Retina);

	ic = m10/m00;
	jc = m01/m00;

	return Point(ic,jc);
}

BoolMatrix PerceptualGroup::binMatrix()
{
	BoolMatrix M;
	double IU,ID,JL,JR;
	int    iIU,iID,iJL,iJR;
	int i,j;
	double ic = 0,jc = 0;
	double Area = 0;

	//Obtengo las coordenadas del rectángulo en el que está inscrito
	//el polígono
	Rectangle(IU,ID,JL,JR);
    iIU=IU;
	iID=ID;
	iJL=JL;
	iJR=JR;

//printf("IU:%.30g,ID:%.30g,JL:%.30g,JR:%.30g\n",IU,ID,JL,JR);
//printf("iIU:%i,iID:%i,iJL:%i,iJR:%i\n",iIU,iID,iJL,iJR);

	M.Resize(iID-iIU+1,iJR-iJL+1);

//Sides.Show();

	//Recorro los puntos horizontalmente que pertenecen al rectángulo
	for (i=iIU;i<=iID;i++)
		for (j=iJL;j<=iJR;j++)
			M[i-iIU][j-iJL] = Inside(Point(i,j));
		
	return M;
}

double PerceptualGroup::m1(double p,double q,UcharMatrix Retina)
{
	BoolMatrix M;
	size_t i,j;
	size_t NumRows,NumCols;
	double m = 0.0;
	double IU,ID,JL,JR;
	int    iIU,iID,iJL,iJR;

	//Obtengo las coordenadas del rectángulo en el que está inscrito
	//el polígono
	Rectangle(IU,ID,JL,JR);

	M       = binMatrix();
	NumRows = M.Depth();
	NumCols = M.Width();

    iIU=IU;
	iID=ID;
	iJL=JL;
	iJR=JR;

	for (i=0;i<NumRows;i++)
		for (j=0;j<NumCols;j++)
			m += pow(iIU+i,p)*pow(iJL+j,q)*M[i][j]*Retina[iIU+i][iJL+j];
	return m;
}

double PerceptualGroup::m2(double p,double q,UcharMatrix Retina)
{
	BoolMatrix M;
	size_t i,j;
	size_t NumRows,NumCols;
	double m = 0.0;
	int ic,jc;
	Point PCentroid;
	double IU,ID,JL,JR;
	int    iIU,iID,iJL,iJR;

	//Obtengo las coordenadas del rectángulo en el que está inscrito
	//el polígono
	Rectangle(IU,ID,JL,JR);

    iIU=IU;
	iID=ID;
	iJL=JL;
	iJR=JR;

//printf("IU,ID,JL,JR:%.30g,%.30g,%.30g,%.30g\n",IU,ID,JL,JR);
	PCentroid = GrayCentroid(Retina);
	ic = PCentroid.i;
	jc = PCentroid.j;

	M       = binMatrix();
	NumRows = M.Depth();
	NumCols = M.Width();

	for (i=0;i<NumRows;i++)
		for (j=0;j<NumCols;j++){
			m += pow((iIU+i-ic),p)*pow((iJL+j-jc),q)*M[i][j]*Retina[iIU+i][iJL+j];
//printf("(%i,%i):%.30g\n",(int)IU+i,(int)JL+j,pow((IU+i-ic),p)*pow((JL+j-jc),q)*M[i][j]);
		}
	return m;
}

double PerceptualGroup::m3(double p,double q, UcharMatrix Retina)
{
	double m;

	m = m2(p,q,Retina)/pow(m2(0,0,Retina),((p+q)/2)+1);

	return m;
}

nCompVector PerceptualGroup::m4(UcharMatrix Retina)
{
	nCompVector m4;
	double m;
	double n02,n03,n11,n12,n20,n21,n30,n32;

	n02 = m3(0,2,Retina);
	n03 = m3(0,3,Retina);
	n11 = m3(1,1,Retina);
	n12 = m3(1,2,Retina);
	n20 = m3(2,0,Retina);
	n21 = m3(2,1,Retina);
	n30 = m3(3,0,Retina);
	n32 = m3(3,2,Retina);

//printf("n02:%.30g\n",n02);
//printf("n03:%.30g\n",n03);
//printf("n11:%.30g\n",n11);
//printf("n12:%.30g\n",n12);
//printf("n20:%.30g\n",n20);
//printf("n21:%.30g\n",n21);
//printf("n30:%.30g\n",n30);
//printf("n32:%.30g\n",n32);

	m = n20 + n20;
	m4.push_back(m);

//printf("m:%.30g\n",m);

	m = pow(n20-n02,2) + 4*pow(n11,2);
	m4.push_back(m);

//printf("m:%.30g\n",m);

	m = pow(n30-3*n12,2)+pow(3*n21-n03,2);
	m4.push_back(m);

	m = pow(n30+n12,2) + pow(n21+n03,2);
	m4.push_back(m);

	m = (n30-3*n12)*(n30+n12)*((n32+n12)-3*(n21-n03))+
		(3*n21-n03)*(n21+n03)+
		(3*pow(n30+n12,2)-pow(n21+n03,2));
	m4.push_back(m);

	m = (n20-n02)*(pow(n30+n12,2)-pow(n21+n03,2))+
		4*n11*(n30+n12)*(n21+n03);
	m4.push_back(m);

	m = (3*n21-n30)*(n30+n12)*(pow(n30+n12,2)-3*pow(n21+n03,2))+
		(3*n21-n30)*(n21+n03)+
		(3*pow(n30+n12,2)-pow(n21+n03,2));
	m4.push_back(m);


//	vector <double>::const_iterator Vit;
//	for (Vit=m.begin();Vit!=m.end();Vit++)
//		printf("m:%.30g\n",*Vit);


	return m4;

}

PerceptualGroup & PerceptualGroup::push_back_Father(LabelVector LV){
	LabelVector LVaux;

	LVaux = GetLabels();
	if (includes(LVaux.begin(),LVaux.end(),LV.begin(),LV.end()))
		Fathers.push_back(LV);

	return *this;
}


PerceptualGroup & PerceptualGroup::push_back_Child (LabelVector LV){
	LabelVector LVaux;

	LVaux = GetLabels();
	if (includes(LV.begin(),LV.end(),LVaux.begin(),LVaux.end()))
		Children.push_back(LV);

	return *this;
}

vector<LabelVector> PerceptualGroup::GetFathers(){
	return Fathers;
}

vector<LabelVector> PerceptualGroup::GetChildren(){
	return Children;
}

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

PerceptualGroupMap::PerceptualGroupMap()
{

}

PerceptualGroupMap::~PerceptualGroupMap()
{

}

//Visualization
void PerceptualGroupMap::Show()
{
	PerceptualGroup AuxPG;
	LabelVector AuxLV;
	PerceptualGroupMap::iterator it;

	for (it = begin(); it != end(); it++)
	{
		AuxLV = (*it).first;
		AuxPG = (*it).second;
		printf("PG: %i ",AuxPG.Label);
		AuxLV.Show();
		printf("\n");
		//AuxPG.Show();
	}
}

//Serialize
size_t PerceptualGroupMap::Serialize(FILE * stream)
{
	size_t count  = 0;
	size_t SMsize = 0;

	LabelVector		lv;
	PerceptualGroup	pg;

	SMsize = size();
	count += sizeof(size_t)*fwrite(&SMsize, sizeof(size_t),1,stream);

	PerceptualGroupMap::iterator it;
	for (it = begin(); it != end(); it++)
	{
		lv = (*it).first;
		pg = (*it).second;
		count += lv.Serialize(stream);
		count += pg.Serialize(stream);
	}

	return count;
}

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

PerceptualGroupVector::PerceptualGroupVector()
{

}

PerceptualGroupVector::~PerceptualGroupVector()
{

}

//Visualization
void PerceptualGroupVector::Show()
{
	PerceptualGroup AuxPG;
	PerceptualGroupVector::const_iterator it;

	for (it = begin(); it != end(); it++)
	{
		AuxPG = *it;
		//AuxPG.Show();
		AuxPG.ShowLabels();
	}
}

//Serialize
size_t PerceptualGroupVector::Serialize(FILE * stream)
{
	size_t count  = 0;
	size_t PGVsize = 0;

	PGVsize = size();
	count += sizeof(size_t)*fwrite(&PGVsize, sizeof(size_t),1,stream);

	PerceptualGroupVector::iterator it;
	for (it = begin(); it != end(); it++)
	{
		count += (*it).Serialize(stream);	
	}

	return count;
}


} //namespace GAC

