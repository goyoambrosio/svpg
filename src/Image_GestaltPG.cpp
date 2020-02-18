/****
  SoftVision. Software for Computer Vision

  Gregorio Ambrosio Cestero (goyo@computer.org)
  System Engineering and Automation Department 
  University of Malaga. Spain                   

  $RCSfile: Image_GestaltPG.cpp,v $
  $Revision: 1.1 $
  $Date: 2000/01/21 13:04:32 $
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


#include "Image_GestaltPG.h"

namespace GAC
{

void SetSegmentsAffinity(double MaxDistance,
						 double d0p, 
						 double thetap, 
						 double deltap, 
						 double C1, 
						 double C2, 
						 double C3, 
						 SegmentMap & SegmentRetina){
	SegmentMap AuxSM;
	SegmentMap::iterator SMit1,SMit2;
	Point S1A,S1B,S2A,S2B;
	vector<double> DistVector;
	vector<double>::iterator Dit;
	double Distance,Significance;
	unsigned int Label;
	Segment S1,S2,AuxS;

	Segment SbetwnMidPoints;
	double alfa1,alfa2,d12;
	double d0,theta,delta;
	double DistanceAffinity, CollinearAffinity, ConvexAffinity;

//	d0    = 0.1*MaxDistance;
//	theta = PI/10;
//	delta = 0.25;
	d0    = d0p*MaxDistance;
	theta = PI/thetap;
	delta = deltap;

	for (SMit1 = SegmentRetina.begin(); SMit1 != SegmentRetina.end(); SMit1++){
		S1  = (*SMit1).second;
		S1A = S1.GetA();
		S1B = S1.GetB();
		for (SMit2 = SegmentRetina.begin(); SMit2 != SegmentRetina.end(); SMit2++){
			if (SMit2!=SMit1){
				S2  = (*SMit2).second;
				S2A = S2.GetA();
				S2B = S2.GetB();

				DistVector.clear();
				DistVector.push_back(S1A.Distance(S2A));
				DistVector.push_back(S1A.Distance(S2B));
				DistVector.push_back(S1B.Distance(S2A));
				DistVector.push_back(S1B.Distance(S2B));

				Dit = min_element(DistVector.begin(), DistVector.end()) ;
				Distance = *Dit;
				if (Distance <= MaxDistance){
					Label = S2.Label;

					// Affinity computation
					SbetwnMidPoints.Set(S1.MidPoint(),S2.MidPoint());
					alfa1=S1.ClockwiseAngle(SbetwnMidPoints);
					alfa2=SbetwnMidPoints.ClockwiseAngle(S2);
//					if (alfa1>PI/2) alfa1-=PI/2;
//					if (alfa2>PI/2) alfa2-=PI/2;
					d12 = SbetwnMidPoints.Mod();
					DistanceAffinity  = ((d12*d12)/(d0*d0));
					CollinearAffinity = ((2-cos(2*alfa1)-cos(2*alfa2))/(1-cos(2*theta)));
					ConvexAffinity    = ((1-cos((2*alfa1)-(2*alfa2)))/(1-cos(2*delta*theta)));
					if (DistanceAffinity<DoubleEpsilon)  DistanceAffinity  = 0.0;
					if (ConvexAffinity<DoubleEpsilon)    ConvexAffinity    = 0.0;
					if (CollinearAffinity<DoubleEpsilon) CollinearAffinity = 0.0;
					Significance = exp(-C1*DistanceAffinity-C2*CollinearAffinity-C3*ConvexAffinity);
//printf("Significance:%.30g\n",CollinearAffinity);
					S1.Proximity[S2.Label]=Significance;
				}
			}
			else {
				S1.Proximity[S1.Label]=1;
			}
		}
		//Segun voy procesando cada segmento lo añado al mapa de segmentos
		//auxiliar que despues va a ser copiado sobre la retina de segmentos
		AuxSM[S1.Label]=S1;
	}
	SegmentRetina = AuxSM;
}

void SetNearSegments(double MaxDistance,SegmentMap & SegmentRetina){
	SegmentMap AuxSM;
	SegmentMap::iterator SMit1,SMit2;
	Point S1A,S1B,S2A,S2B;
	vector<double> DistVector;
	vector<double>::iterator Dit;
	double Distance,Significance;
	unsigned int Label;
	Segment S1,S2,AuxS;

	for (SMit1 = SegmentRetina.begin(); SMit1 != SegmentRetina.end(); SMit1++){
		S1  = (*SMit1).second;
		S1A = S1.GetA();
		S1B = S1.GetB();
		for (SMit2 = SegmentRetina.begin(); SMit2 != SegmentRetina.end(); SMit2++){
			if (SMit2!=SMit1){
				S2  = (*SMit2).second;
				S2A = S2.GetA();
				S2B = S2.GetB();

				DistVector.clear();
				DistVector.push_back(S1A.Distance(S2A));
				DistVector.push_back(S1A.Distance(S2B));
				DistVector.push_back(S1B.Distance(S2A));
				DistVector.push_back(S1B.Distance(S2B));

				Dit = min_element(DistVector.begin(), DistVector.end()) ;
				Distance = *Dit;
				if (Distance <= MaxDistance){
					Label = S2.Label;
					//Convierto la distancia a significancia (probabilidad de no accidentalidad)
					//Cuanto menor sea la distancia mayor es la probabilidad de que la
					//proximidad no sea accidental (significancia). Es decir si la distancia es 0 la 
					//significancia es 1, y si la distancia es la maxima permitida la siginificancia es 0.
					//Esto genera una recta cuya ecuacion es y=-(1/MaxDist)x+1.
					//Donde x es la distancia e y la significancia.
					//Se puede variar esta relacion en funcion de experimentos futuros.
					Significance = -(1/MaxDistance)*Distance + 1;	
					S1.Proximity[S2.Label]=Significance;
				}
			}
		}
		//Segun voy procesando cada segmento lo añado al mapa de segmentos
		//auxiliar que despues va a ser copiado sobre la retina de segmentos
		AuxSM[S1.Label]=S1;
	}
	SegmentRetina = AuxSM;
}

void SetParallelSegments(double MaxDistance,double MaxAngle,SegmentMap & SegmentRetina)
{
	SegmentMap AuxSM;
	SegmentMap::iterator SMit1,SMit2;
	Point S1A,S1B,S2A,S2B;
	double Distance;
	double DstSignificance = 0,ParSignificance = 0;
	double Significance = 0;
	Segment S1,S2;
	Point S2MidPoint,S2AinS1,S2BinS1,S1AinS2,S1BinS2;
	double Angle;

	//El proceso es el siguiente:
	//Se comprueba si S2 es casi paralelo a S1. 
	//Para ello se mira que la diferencia de sus angulos (PosFi) no sea
	//mayor que MaxAngle.
	//Si son casi paralelo procedemos a comprobar la distancia que los separa.
	//Para ello calculo el punto medio de S2 y calculo la distancia de
	//PmS2 a S1. Si esta distancia es inferior a MaxDistance entonces es que esta
	//proximo.
	//Si S2 esta proximo a S1 procedo a estudiar si se solapan.
	//Para ello trazo la perpendicular a cada extremo de S2 y obtengo
	//los puntos de corte con S1 y observo si esos puntos de corte estan
	//dentro de S1.
	//Si alguno de ellos esta admito la relacion de paralelismo entre S1 y S2.

	for (SMit1 = SegmentRetina.begin(); SMit1 != SegmentRetina.end(); SMit1++){
		S1  = (*SMit1).second;
		S1A = S1.GetA();
		S1B = S1.GetB();
		for (SMit2 = SegmentRetina.begin(); SMit2 != SegmentRetina.end(); SMit2++){
			if (SMit2!=SMit1){
				S2  = (*SMit2).second;
				S2A = S2.GetA();
				S2B = S2.GetB();
				
				//Si S1 y S2 forman un angulo menor que MaxAngle ...
				Angle = S1.Angle(S2);
			    if (Angle>HALF_PI) Angle = PI-Angle;

				if (Angle<MaxAngle){
					//Calculo el punto medio de S2 y su distancia con S1
					S2MidPoint = S2.MidPoint();
					Distance = fabs(S1.EuclideanDistance(S2MidPoint));
					//Si la distancia es menor que MaxDistance ...
					if (Distance < MaxDistance){
						//Trazo la perpendicular a S2 por cada uno de sus extremos
						//y obtengo los puntos de corte con S1
						//Hago lo mismo con S1 sobre S2
						S2AinS1 = S1.Intersection(S2.PerpLine(S2A));
						S2BinS1 = S1.Intersection(S2.PerpLine(S2B));
						S1AinS2 = S2.Intersection(S1.PerpLine(S1A));
						S1BinS2 = S2.Intersection(S1.PerpLine(S1B));
						//Estudio si alguna de las proyecciones de los dos extremos de S2 
						//estan entre los extremos de S1
						//o si alguna de las proyecciones de los dos extremos de S1 estan
						//entre los extremos de S2
						//y si es así admito al segmento S2 como paralelo y cercano a S1
						if ((S1.BelongToVector(S2AinS1) &&
							 S1.BelongToVector(S2BinS1)  ) || 
							(S2.BelongToVector(S1AinS2) &&
							 S2.BelongToVector(S1BinS2)	 )) {
							//Convierto la distancia a significancia (probabilidad de no accidentalidad)
							//Cuanto menor sea la distancia mayor es la probabilidad de que la
							//proximidad no sea accidental (significancia). Es decir si la distancia es 0 la 
							//significancia es 1, y si la distancia es la maxima permitida la siginificancia es 0.
							//Esto genera una recta cuya ecuacion es y=-(1/MaxDist)x+1.
							//Donde x es la distancia e y la significancia.
							//Lo mismo ocurre con la diferencia entre los angulos de los segmentos.
							//Se puede variar esta relacion en funcion de experimentos futuros.
							DstSignificance = (-(1.0/MaxDistance)*Distance + 1.0);
							ParSignificance = (-(1.0/MaxAngle)*Angle + 1.0);
							//La Significancia es la media de las significancias de distancia y paralelismo
							Significance = ((DstSignificance + ParSignificance)/2.0);
							//Añado el segmento al conjunto de segmentos paralelos a S1
							S1.Parallelism[S2.Label]=(Significance);
						}
					}
				}
			}
		}
		//Segun voy procesando cada segmento lo añado al mapa de segmentos
		//auxiliar que despues va a ser copiasdo sobre la retina de segmentos
		AuxSM[S1.Label]=S1;
	}
	SegmentRetina = AuxSM;
}

void SetColinearSegments(double MaxDistBetwColSegments,
						 double MaxParDistBetwColSegments,
						 double MaxAngleBetwCollinearSegments,
						 SegmentMap & SegmentRetina)
{
	SegmentMap AuxSM;
	SegmentMap::iterator SMit1,SMit2;
	Point S1A,S1B,S2A,S2B;
	vector<double> DistVector;
	vector<double>::iterator Dit;
	double Distance;
	double Significance = 0;
	Segment S1,S2;
	Point S2MidPoint,S2AinS1,S2BinS1,S1AinS2,S1BinS2;
	double Angle;
	double MaxAngle;
	double MaxParallelDistance; //Admito una distancia de la recta base de 1

	//El proceso es el siguiente:
	//Se comprueba si S2 es casi paralelo a S1. 
	//Para ello se mira que la diferencia de sus angulos (PosFi) no sea
	//mayor que MaxAngle.
	//Si son casi paralelo procedemos a comprobar la distancia que los separa.
	//Para ello calculo el punto medio de S2 y calculo la distancia de
	//PmS2 a S1. Si esta distancia es inferior a MaxParallelDistance entonces es que esta
	//proximo.
	//Si S2 esta proximo a S1 procedo a estudiar si se solapan.
	//Para ello trazo la perpendicular a cada extremo de S2 y obtengo
	//los puntos de corte con S1 y observo si esos puntos de corte estan
	//dentro de S1.
	//Si ninguno de ellos se solapan compruebo si la separacion de los extremos es menor
	//que PGData.MaxDistBetwColSegments y si es asi admito la relacion de paralelismo
	//entre S1 y S2.

	MaxAngle = MaxAngleBetwCollinearSegments;

	MaxParallelDistance = MaxParDistBetwColSegments;

	for (SMit1 = SegmentRetina.begin(); SMit1 != SegmentRetina.end(); SMit1++){
		S1  = (*SMit1).second;
		S1A = S1.GetA();
		S1B = S1.GetB();
//		for (SMit2 = SegmentRetina.begin(); SMit2 != SegmentRetina.end(); SMit2++){
		for (SMit2 = SMit1; SMit2 != SegmentRetina.end(); SMit2++){
			if (SMit2!=SMit1){
				S2  = (*SMit2).second;
				S2A = S2.GetA();
				S2B = S2.GetB();
				
				//Si S1 y S2 forman un angulo menor que MaxAngle ...
				Angle = S1.Angle(S2);
			    if (Angle>HALF_PI) Angle = PI-Angle;

				if (Angle<MaxAngle){
					//Calculo el punto medio de S2 y su distancia con S1
					S2MidPoint = S2.MidPoint();
					Distance = fabs(S1.EuclideanDistance(S2MidPoint));
					//Si la distancia es menor que PGData.MaxDistBetwColSegments ...
					if (Distance < MaxParallelDistance){
						//Trazo la perpendicular a S2 por cada uno de sus extremos
						//y obtengo los puntos de corte con S1
						//Hago lo mismo con S1 sobre S2
						S2AinS1 = S1.Intersection(S2.PerpLine(S2A));
						S2BinS1 = S1.Intersection(S2.PerpLine(S2B));
						S1AinS2 = S2.Intersection(S1.PerpLine(S1A));
						S1BinS2 = S2.Intersection(S1.PerpLine(S1B));
						//Estudio si alguna de las proyecciones de los dos extremos de S2 
						//estan entre los extremos de S1
						//o si alguna de las proyecciones de los dos extremos de S1 estan
						//entre los extremos de S2
						//Si no se solapan los segmentos ...
						if (!(S1.BelongToVector(S2AinS1) ||
							  S1.BelongToVector(S2BinS1) || 
							  S2.BelongToVector(S1AinS2) ||
							  S2.BelongToVector(S1BinS2) )) {
							DistVector.clear();
							DistVector.push_back(fabs(S1A.Distance(S2A)));
							DistVector.push_back(fabs(S1A.Distance(S2B)));
							DistVector.push_back(fabs(S1B.Distance(S2A)));
							DistVector.push_back(fabs(S1B.Distance(S2B)));

							Dit = min_element(DistVector.begin(), DistVector.end()) ;
							Distance = *Dit;
							//Compruebo que la distancia entre los extremos es menor a una dada ...
							if (Distance < MaxDistBetwColSegments) {
								//Convierto la distancia a significancia (probabilidad de no accidentalidad)
								//Cuanto menor sea la distancia mayor es la probabilidad de que la
								//proximidad no sea accidental (significancia). Es decir si la distancia es 0 la 
								//significancia es 1, y si la distancia es la maxima permitida la siginificancia es 0.
								//Esto genera una recta cuya ecuacion es y=-(1/MaxDist)x+1.
								//Donde x es la distancia e y la significancia.
								//Se puede variar esta relacion en funcion de experimentos futuros.
//								Significance = (-(1.0/MaxDistBetwColSegments)*Distance + 1.0);
								Significance = (S1.Mod()+S2.Mod())/(S1.Mod()+S2.Mod()+Distance);
								//Añado el segmento al conjunto de segmentos paralelos a S1
								SegmentRetina[S1.Label].Colinearity[S2.Label]=Significance;
								SegmentRetina[S2.Label].Colinearity[S1.Label]=Significance;
							}
						}
					}
				}
			}
		}
	}
}


RelationVector GetProximityRelations(LabelVector Labels,SegmentMap SegmentRetina)
{
	LabelVector::iterator LVit;
	Label NewSLabel,SLabel;

	int2doubleMap::iterator I2DMit;
	SegmentMap::iterator AuxSMit;
	RelationVector  AuxRV;
	Relation		NewR;
	Segment			AuxS;
	double			NewSSignificance;

	//Para un conjunto de segmentos representados por sus etiquetas
	for (LVit = Labels.begin();LVit!=Labels.end();LVit++){
		SLabel = *LVit;

		//Busco el segmento por su etiqueta y saco de el los segmentos cerca de su extremo A
		AuxSMit = SegmentRetina.find(SLabel);
		AuxS = (*AuxSMit).second;
		//Para cada segmento proximo, creo una relacion
		for (I2DMit=AuxS.Proximity.begin() ; I2DMit!=AuxS.Proximity.end() ; I2DMit++){
			NewSLabel		  = (*I2DMit).first;
			NewSSignificance  = (*I2DMit).second; 

			//Ordeno la tupla por etiquetas de forma que siempre SALable < SBLabel
			if (NewSLabel<SLabel) {
				NewR.SALabel = NewSLabel;
				NewR.SBLabel = SLabel;
			}
			else {
				NewR.SALabel = SLabel;
				NewR.SBLabel = NewSLabel;
			}
			NewR.Property	  = REL_PROP_PROXIMITY;
			NewR.Significance = NewSSignificance;

			//Añado la nueva relacion al vector que contiene las nuevas relaciones
			AuxRV.push_back(NewR);
		}
	}

	//Devuelvo un vector con las nuevas relaciones encontradas
	return AuxRV;
}

RelationVector GetParallelismRelations(LabelVector Labels,SegmentMap SegmentRetina)
{
	LabelVector::iterator LVit;
	Label NewSLabel,SLabel;

	int2doubleMap::iterator I2DMit;
	SegmentMap::iterator AuxSMit;
	RelationVector  AuxRV;
	Relation		NewR;
	Segment			AuxS;
	double			NewSSignificance;

	//Para un conjunto de segmentos representados por sus etiquetas
	for (LVit = Labels.begin();LVit!=Labels.end();LVit++){
		SLabel = *LVit;

		//Busco el segmento por su etiqueta y saco de el los segmentos paralelos cercanos
		AuxSMit = SegmentRetina.find(SLabel);
		AuxS = (*AuxSMit).second;
		//Para cada segmento proximo, creo una relacion
		for (I2DMit=AuxS.Parallelism.begin() ; I2DMit!=AuxS.Parallelism.end() ; I2DMit++){
			NewSLabel		  = (*I2DMit).first;
			NewSSignificance  = (*I2DMit).second; 

			//Ordeno la tupla por etiquetas de forma que siempre SALable < SBLabel
			if (NewSLabel<SLabel) {
				NewR.SALabel = NewSLabel;
				NewR.SBLabel = SLabel;
			}
			else {
				NewR.SALabel = SLabel;
				NewR.SBLabel = NewSLabel;
			}
			NewR.Property	  = REL_PROP_PARALLELISM;
			NewR.Significance = NewSSignificance;

			//Añado la nueva relacion al vector que contiene las nuevas relaciones
			AuxRV.push_back(NewR);
		}
	}

	//Devuelvo un vector con las nuevas relaciones encontradas
	return AuxRV;
}

RelationVector GetColinearityRelations(LabelVector Labels,SegmentMap SegmentRetina)
{
	LabelVector::iterator LVit,LV1it;
	Label NewSLabel,SLabel,S1Label;

	int2doubleMap::iterator I2DMit;
	SegmentMap::iterator AuxSMit;
	RelationVector  AuxRV;
	Relation		NewR;
	Segment			AuxS,AuxS1,AuxS2;
	double			NewSSignificance;
	bool			Overlap;
	Vector			Vaux;
	Point S2AinS1,S2BinS1,S1AinS2,S1BinS2;
	Point S1A,S1B,S2A,S2B;


	//Para un conjunto de segmentos representados por sus etiquetas
	for (LVit = Labels.begin();LVit!=Labels.end();LVit++){
		SLabel = *LVit;

		//Busco el segmento por su etiqueta y saco de el los segmentos con los que es colineal
		AuxSMit = SegmentRetina.find(SLabel);
		AuxS = (*AuxSMit).second;

		//Si además este segmento es colineal con el resto de los segmentos que forman el PG
		//,es decir, no se superpone con ninguno
		//Para cada segmento colineal, creo una relacion
		for (I2DMit=AuxS.Colinearity.begin() ; I2DMit!=AuxS.Colinearity.end() ; I2DMit++){
			NewSLabel		  = (*I2DMit).first;
			NewSSignificance  = (*I2DMit).second; 

			//Estudio si alguna de las proyecciones de los dos extremos de AuxS2 
			//estan entre los extremos de AuxS1
			//o si alguna de las proyecciones de los dos extremos de AuxS1 estan
			//entre los extremos de AuxS2
			Overlap = false;

			//Obtengo el segmento candidato
			AuxSMit = SegmentRetina.find(NewSLabel);
			AuxS2 = (*AuxSMit).second;

			//Estudio el solapamiento con cada segmento del PG
			for (LV1it = Labels.begin();LV1it!=Labels.end();LV1it++){
				S1Label = *LV1it;

				AuxSMit = SegmentRetina.find(S1Label);
				AuxS1 = (*AuxSMit).second;

				//Obtengo los cuatro extremos
				S1A = AuxS1.GetA();
				S1B = AuxS1.GetB();
				S2A = AuxS2.GetA();
				S2B = AuxS2.GetB();

				//Obtengo las intersecciones de los extremos de un segmento
				//en la linea portadora del otro.
				S2AinS1 = AuxS1.Intersection(AuxS2.PerpLine(S2A));
				S2BinS1 = AuxS1.Intersection(AuxS2.PerpLine(S2B));
				S1AinS2 = AuxS2.Intersection(AuxS1.PerpLine(S1A));
				S1BinS2 = AuxS2.Intersection(AuxS1.PerpLine(S1B));

				//Observo si alguno de las intersecciones anteriores están dentro del segmento.
				Overlap =	Overlap ||
							AuxS1.BelongToVector(S2AinS1) ||
							AuxS1.BelongToVector(S2BinS1) || 
							AuxS2.BelongToVector(S1AinS2) ||
							AuxS2.BelongToVector(S1BinS2) ;			
			}
		

			//Si no se solapan los segmentos ...
			if (!Overlap) {
				//Ordeno la tupla por etiquetas de forma que siempre SALabel < SBLabel
				if (NewSLabel<SLabel) {
					NewR.SALabel = NewSLabel;
					NewR.SBLabel = SLabel;
				}
				else {
					NewR.SALabel = SLabel;
					NewR.SBLabel = NewSLabel;
				}
				NewR.Property	  = REL_PROP_COLINEARITY;
				NewR.Significance = NewSSignificance;

				//Añado la nueva relacion al vector que contiene las nuevas relaciones
				AuxRV.push_back(NewR);
			}
		}
	}

	//Devuelvo un vector con las nuevas relaciones encontradas
	return AuxRV;
}




PerceptualGroupVector GetNewPerceptualGroups(PerceptualGroup PGBase, RelationVector NewRelations)
{
	RelationVector::iterator RVit;
	Relation NewR,AuxR;
	PerceptualGroupVector NewPGVector;
	RelationVector::iterator PGit;
	PerceptualGroup NewPG;

	for (RVit=NewRelations.begin();RVit!=NewRelations.end();RVit++){
		//Compruebo que la nueva R (NewR) no existe ya en el PG
		NewR=*RVit;
		PGit = find(PGBase.RelationVector::begin(), PGBase.RelationVector::end(), NewR);
		if (PGit==PGBase.RelationVector::end()) { //Si no existe ya la relacion
			NewPG = PGBase;
			AuxR = *NewPG.RelationVector::begin();
			if (AuxR.Property == REL_PROP_ITSELF)
				NewPG.RelationVector::clear();
			NewPG.RelationVector::push_back(NewR); //El nuevo PG es igual que el origen mas la nueva relacion
			sort(NewPG.RelationVector::begin(),NewPG.RelationVector::end());
			NewPGVector.push_back(NewPG);
		}
	}
	return NewPGVector;
}

void SetNewPGCandidates(PerceptualGroupVector  NewPGCandidates,
							   PerceptualGroupMap    &PGM)
{
	PerceptualGroup NewPG,ActualPG;
	PerceptualGroupVector::iterator NewPGVit;
	pair<PerceptualGroupMap::iterator, bool> PGMins;

	//Para cada PG candidato compruebo que no ha sido previamente
	//generado.
	for (NewPGVit=NewPGCandidates.begin();NewPGVit!=NewPGCandidates.end();NewPGVit++){
		//Compruebo que el nuevo PG no existe ya en el PGM
		NewPG = *NewPGVit;
		//Le asigno el Label que le corresponde por si la insercion tiene exito.
		NewPG.Label = PGM.size()+1;
		//Lo intento insertar. Si lo consigo ya he terminado...
		PGMins = PGM.insert(PerceptualGroupMap::value_type(NewPG.GetLabels(),NewPG));

		//...pero si no, quiere decir que ya existe y por lo tanto debo comprobar si
		//la Significancia total del nuevo es mayor (es decir, si la probabilidad de 
		//no accidentalidad es mas alta). Si es asi entonces sustituyo el anterior
		//por el nuevo, y si no, lo olvido.
		if (!PGMins.second){
			ActualPG = (*(PGMins.first)).second;
			if(ActualPG.GetTotalSignificance() > NewPG.GetTotalSignificance()){
				//Como ya existe un PG que contiene a los mismos segmentos
				//que el NewPG le pongo la misma Label que el PG antiguo.
				NewPG.Label = (*(PGMins.first)).second.Label;
				//Cambio el contenido del PG antiguo por el nuevo PG (NewPG)
				(*(PGMins.first)).second = NewPG;
			}
//NewPG.Show();
		}

	}
}


PerceptualGroupMap GestaltPGPostProcessing(PerceptualGroupMap & NewPGM){
	PerceptualGroup NewPG,ActualPG;
	PerceptualGroupMap::iterator NewPGMit;
	PerceptualGroupMap PGM;
	pair<PerceptualGroupMap::iterator, bool> PGMins;
	LabelVector LV;

	//Proceso el conjunto final de CPGs para reducir el conjunto eliminado
	//aquellos CPGs que no me interesan.
	for (NewPGMit=NewPGM.begin();NewPGMit!=NewPGM.end();NewPGMit++){
		LV = (*NewPGMit).first;
		NewPG = (*NewPGMit).second;
		if (LV.size() > 1 )//No se generan grupos de un solo segmento.
		{
			//Le asigno un Label nuevo que indica el orden en el nuevo conjunto
			NewPG.Label = PGM.size()+1;
			//Estudio si el CPG se ha añadido ya con otro orden de relaciones.
			//Lo intento insertar en el conjunto final. Si lo consigo es que no habia otro igual y ya he terminado...
			PGMins = PGM.insert(PerceptualGroupMap::value_type(NewPG.GetLabels(),NewPG));
			//...pero si no, quiere decir que ya existe y por lo tanto debo comprobar si
			//la Significancia total del nuevo es mayor (es decir, si la probabilidad de 
			//no accidentalidad es mas alta). Si es asi entonces sustituyo el anterior
			//por el nuevo, y si no, lo olvido.
			if (!PGMins.second){
				ActualPG = (*(PGMins.first)).second;
				if(NewPG.GetSignificanceAcc(REL_PROP_CONVEXITY) <= ActualPG.GetSignificanceAcc(REL_PROP_CONVEXITY)){
					//Como ya existe un PG que contiene a los mismos segmentos
					//que el NewPG le pongo la misma Label que el PG antiguo.
					NewPG.Label = (*(PGMins.first)).second.Label;
					//Cambio el contenido del PG antiguo por el nuevo PG (NewPG)
					(*(PGMins.first)).second = NewPG;
				}
			}
		}
	}
	BuildPGsGraph (PGM);
	return PGM;
}

void BuildPGsGraph (PerceptualGroupMap & PGM){
	PerceptualGroupMap::iterator PGMit1, PGMit2;

	for (PGMit1=PGM.begin();PGMit1!=PGM.end();PGMit1++)
		for (PGMit2=PGM.begin();PGMit2!=PGM.end();PGMit2++)
			if ((*PGMit1).first != (*PGMit2).first)
				if (includes((*PGMit1).first.begin(),
							 (*PGMit1).first.end(),
							 (*PGMit2).first.begin(),
							 (*PGMit2).first.end())   &&
					(*PGMit1).first.size() == (*PGMit2).first.size()+1 ) {
					(*PGMit1).second.push_back_Father((*PGMit2).first);
					(*PGMit2).second.push_back_Child ((*PGMit1).first);
				}
}

} //namespace GAC

