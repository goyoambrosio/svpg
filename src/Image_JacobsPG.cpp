/****
  SoftVision. Software for Computer Vision

  Gregorio Ambrosio Cestero (goyo@computer.org)
  System Engineering and Automation Department 
  University of Malaga. Spain                   

  $RCSfile: Image_JacobsPG.cpp,v $
  $Revision: 1.1 $
  $Date: 2000/01/21 13:04:33 $
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


#include "Image_JacobsPG.h"

namespace GAC
{


SegmentMap SetConvexSegmentMap(	const SegmentMap & InitialSegmentMap, 
								double MaxDistBetwConvexSegments,
								int MinNumOfPixels,
								double MaxDistance,
								double MaxNoConvexityThreshold,
								bool JacobExtension_1,
								bool JacobExtension_2)
{
	unsigned int LastLabel;
	Segment S1,S2,S2AC,S2CB,SO;
	Point S1A,S1B,S2A,S2B,C,S2C1,S2C2;
	SegmentMap BaseSM,ExtendedSM_1,ExtendedSM_2,ConvexSegmentMap;
	SegmentMap::iterator SMit1,SMit2;

	//Asignamos a LastLabel la ultima etiqueta para poder asignar etiquetas 
	//a los nuevos segmentos.
	LastLabel = (*--InitialSegmentMap.end()).first;

	BaseSM = InitialSegmentMap;

//printf("JacobExtension_1---------------------------->BEGIN\n");
	if (JacobExtension_1 || JacobExtension_2){
		//Estudio para cada segmento si su linea portadora se corta con la línea
		//portadora de otro segmento (dentro de una distancia) y si es así
		//genero dos segmentos S2AC y S2CB a partir de S2
		//Entre el extremo B de S2AC y el punto C hay una distancia de 0.01
		//al igual que entre C y el extremo A de S2CB
		//Por otro lado no se admite la generación de ningún segmento con un módulo
		//menor de MinNoOfPixels
		//                                    S2AC         S2CB
		//                S2               S2A   S2C1 C S2C2   S2B
		//       -------------------->     ---------->* --------->
		//                 ^                          ^   
		//                 |                          |
		//               S1|                        S1|

		for (SMit1 = BaseSM.begin();SMit1 != BaseSM.end();SMit1++){
			for (SMit2 = BaseSM.begin();SMit2 != BaseSM.end();SMit2++){
				S1 = (*SMit1).second;
				S1A = S1.GetA();
				S1B = S1.GetB();
				S2 = (*SMit2).second;
				S2A = S2.GetA();
				S2B = S2.GetB();
				if (S1.Label!=S2.Label) {

					//Calculo el punto en que las líneas portadoras de los dos vectores
					//se cortan.
					C = S1.Intersection(S2);


					//Si el punto donde se cortan pertenece al vector S2, es decir, si
					//esta entre sus dos extremos...
					//y no coincide con ningunos de los extremos de los segmentos ...
					//y la distancia entre C y algún extremo de S1 está dentro de la distancia
					//máxima permitida entre segmentos próximos
					if ( S2.BelongToVector(C) &&
						(C != S1A)            &&
						(C != S1B)            &&
						(C != S2A)            &&
						(C != S2B)            &&
					    ((S1A.Distance(C)<=MaxDistBetwConvexSegments) ||
						 (S1B.Distance(C)<=MaxDistBetwConvexSegments)   )
					   )
	
					{

						S2.EquidistantPointsInLine(C, 1,S2C1, S2C2);

						if (S2A.Distance(S2C1)>S2A.Distance(S2C2)){
							S2C1.Swap(S2C2);
						}

						//Si el módulo del segmento S2A->S2C1 es mayor que MinNoOfPixels
						//y el restante módulo del segmento C->S2B es mayor que Threshold
						//entonces acepto la creación del segmento S2A->S2C1
						if ((S2A.Distance(S2C1)>MinNumOfPixels) &&
						    (C.Distance(S2B) > MaxNoConvexityThreshold)
						   )
						{
							S2AC.Set(S2A,S2C1);
							LastLabel++;
							S2AC.Label = LastLabel;
							ExtractPixels (S2, S2AC, MaxDistance);
							ExtendedSM_1.insert(SegmentMap::value_type(S2AC.Label,S2AC));
						}

						//Si el módulo del segmento S2B->S2C2 es mayor que MinNoOfPixels
						//y el restante módulo del segmento C->S2A es mayor que Threshold
						//entonces acepto la creación del segmento S2B->S2C2
						if ((S2B.Distance(S2C2)>MinNumOfPixels) &&
						    (C.Distance(S2A) > MaxNoConvexityThreshold)
						   )
						{
							S2CB.Set(S2C2,S2B);
							LastLabel++;
							S2CB.Label = LastLabel;
							ExtractPixels (S2, S2CB, MaxDistance);
							ExtendedSM_1.insert(SegmentMap::value_type(S2CB.Label,S2CB));
						}
					}
				}
			}
		}

//printf("ExtendedSM_1.Show()------------->BEGIN\n");
//ExtendedSM_1.Show();
//printf("ExtendedSM_1.Show()------------->END\n");

	}
//printf("JacobExtension_1---------------------------->END\n");

	if (JacobExtension_2){
		//Obtengo nuevos vectores resultantes del solapamiento de los existentes
		//con esto y lo anterior implemento otra extensión del algoritmo de Jacob 
		//que me permite obtener lo siguiente:
		//
		//     -------          -------
		//    |       |        |       |
		//    |       |   ->   |       |
		//    |       |        |       |
		//  -------------       -------

		for (SMit1 = ExtendedSM_1.begin();SMit1 != ExtendedSM_1.end();SMit1++){
			for (SMit2 = ExtendedSM_1.begin();SMit2 != ExtendedSM_1.end();SMit2++){
				S1 = (*SMit1).second;
				S2 = (*SMit2).second;
				if ((S1.GetA()!=S2.GetA())&&(S1.GetB()!=S2.GetB()))
					if (S1.Overlap(S2,SO))
						if(SO.GetA()!=SO.GetB()){
								LastLabel++;
								SO.Label = LastLabel;
								ExtractPixels (S2, SO, MaxDistance);
								ExtendedSM_2.insert(SegmentMap::value_type(SO.Label,SO));
							}
			}
		}
//printf("ExtendedSM_2.Show()------------->BEGIN\n");
//ExtendedSM_2.Show();
//printf("ExtendedSM_2.Show()------------->END\n");
	}

	for (SMit1 = ExtendedSM_1.begin();SMit1 != ExtendedSM_1.end();SMit1++)
		BaseSM.insert(*SMit1);

	//Creo un SegmentVector con el conjunto de segmentos duplicados ya que
	//les añado los mismos segmentos pero con el sentido contrario.
	//Para cada segmento genero otro identico con los extremos invertidos.
	//Es decir como cada segmento es un vector creo otro con la misma 
	//direccion y sentido contrario.
	for (SMit1 = BaseSM.begin();SMit1 != BaseSM.end();SMit1++){
		S1 = (*SMit1).second;
		S1A = S1.GetA();
		S1B = S1.GetB();
		//Construyo S2
		S2 = S1;
		S2.Set(S1B,S1A);
		S2.SetPosSideAvgGrayLevel(S1.GetNegSideAvgGrayLevel());
		S2.SetNegSideAvgGrayLevel(S1.GetPosSideAvgGrayLevel());
		S2.SetPointChain(S1.GetPointChain());
		S2.SetPixelChain(S1.GetPixelChain());
		S2.Label = S1.Label + LastLabel;
		//Inserto los dos segmentos
		ConvexSegmentMap.insert(SegmentMap::value_type(S1.Label,S1));
		ConvexSegmentMap.insert(SegmentMap::value_type(S2.Label,S2));
	}

	//Añado ExtendedSM_2 ahora porque el proceso de creación ya me genera
	//los vectores iguales con distinto sentido.
	for (SMit1 = ExtendedSM_2.begin();SMit1 != ExtendedSM_2.end();SMit1++)
		ConvexSegmentMap.insert(*SMit1);

//ConvexSegmentMap.Show();

	return ConvexSegmentMap;
}



void SetMutualConvexSegments(SegmentMap & ConvexSegmentRetina, double MaxDistBetwProxSegments,double MaxNoConvexityThreshold, bool Polarity){

	SegmentMap::iterator SMit1,SMit2;

	for (SMit1 = ConvexSegmentRetina.begin();SMit1 != ConvexSegmentRetina.end();SMit1++){
		//... veo si es mutumente convexo con cada segmento
		//de la imagen.
		for (SMit2 = ConvexSegmentRetina.begin();SMit2 != ConvexSegmentRetina.end();SMit2++){
			//Estudio la convexidad de los dos segmentos
			//Esta funcion me devuelve S1 modificado. Añade a Convexity (en S1) S2 si
			//es mutuamente convexo con S1.
			//ExtendedSM (de momento no se usa) contendra los nuevos segmentos
			//formados por trozos de segmentos mutuamente convexos con S1 y que se
			//constituyen como nuevos Segmentos.
			//              S1
			//        ---------------

			Convexity((*SMit1).second,(*SMit2).second,MaxDistBetwProxSegments,MaxNoConvexityThreshold, Polarity);
		}
		//Ordeno la lista de segmentos en funcion de la distancia
		sort((*SMit1).second.Convexity.begin(),(*SMit1).second.Convexity.end());
//(*SMit1).second.Show();
//(*SMit1).second.Convexity.Show();
	}
}


//En esta funcion tengo que tratar los casos de:
//-pequeñas concavidades
//-Convexidad con trozos de segmentos
//-etc.
void Convexity(Segment & S1, Segment S2, double MaxDistBetwConvexSegments, double MaxNoConvexityThreshold, bool Polarity)
{
	Point PS1A,PS1B,PS2A,PS2B;
	bool AreMutuallyConvex = false,S2IsConvexWithS1,S1IsConvexWithS2,InTheSameLine;
	bool WithTheSamePolarity;
	ConvexSegmentData CSD;

//printf("Convexity ------------------------------> BEGIN\n");
	//Obtengo los extremos de los segmentos.
	PS1A = S1.GetA();
	PS1B = S1.GetB();
	PS2A = S2.GetA();
	PS2B = S2.GetB();


	//Los dos segmentos son mutuamente convexos cuando los extremos
	//de S2 estan a la derecha (semiplano negativo) de S1 y cuando los
	//extremos de S1 estan a la derecha (semiplano negativo) de S2...
	// y cuando no son el mismo segmento ...
	// ni son colinenales

//	S2IsConvexWithS1 = S1.IsNearNegRightSide(PS2A,MaxNoConvexityThreshold) && S1.IsNearNegRightSide(PS2B,MaxNoConvexityThreshold);

//	S1IsConvexWithS2 = S2.IsNearNegRightSide(PS1A,MaxNoConvexityThreshold) && S2.IsNearNegRightSide(PS1B,MaxNoConvexityThreshold);


	if (S1.IsInNegRightSide(PS2A) && S1.IsInNegRightSide(PS2B))
		S2IsConvexWithS1 = true;
	else if (S1.IsInNegRightSide(PS2A) && S1.IsNearNegRightSide(PS2B,MaxNoConvexityThreshold))
		S2IsConvexWithS1 = true;
	else if (S1.IsNearNegRightSide(PS2A,MaxNoConvexityThreshold) && S1.IsInNegRightSide(PS2B))
		S2IsConvexWithS1 = true;
	else
		S2IsConvexWithS1 = false;

	if (S2.IsInNegRightSide(PS1A) && S2.IsInNegRightSide(PS1B))
		S1IsConvexWithS2 = true;
	else if (S2.IsInNegRightSide(PS1A) && S2.IsNearNegRightSide(PS1B,MaxNoConvexityThreshold))
		S1IsConvexWithS2 = true;
	else if (S2.IsNearNegRightSide(PS1A,MaxNoConvexityThreshold) && S2.IsInNegRightSide(PS1B))
		S1IsConvexWithS2 = true;
	else
		S1IsConvexWithS2 = false;


//printf("S1:%i,S2:%i\n",S1.Label,S2.Label);
//printf("S1.BelongToLine(PS2A):%i\n",S1.BelongToLine(PS2A));
//printf("S1.BelongToLine(PS2B):%i\n",S1.BelongToLine(PS2B));
//printf("S1.Pow(PS2A):%.30g\n",S1.Pow(PS2A));
//printf("S1.Pow(PS2B):%.30g\n",S1.Pow(PS2B));
	InTheSameLine = (fabs(S1.Pow(PS2A))<1.0e-5) && (fabs(S1.Pow(PS2B))<1.0e-5);

	//Si el switch de polaridad está activado entonces se tiene en cuenta la polaridad (!Polarity => false)
	//si no (!Polarity => true) entonces ignoro la polaridad
	WithTheSamePolarity = ((S1.GetPolarity() == S2.GetPolarity()) || !Polarity);

	AreMutuallyConvex = ( S2IsConvexWithS1				&&
						  S1IsConvexWithS2				&&
						  !InTheSameLine				&&
						  WithTheSamePolarity
						);


	//Si los dos segmentos son mutuamente convexos ...
	if (AreMutuallyConvex){
		//y la distancia que separa los dos segmentos está dentro del umbral
		if (PS1B.Distance(PS2A)<=MaxDistBetwConvexSegments)
		{
			//Obtengo la informacion necesaria de la relacion de 
			//convexidad.
			CSD.Dist  = PS1B.Distance(PS2A);
			CSD.Angle = S1.ClockwiseAngle(S2);
			CSD.Label = S2.Label;
			CSD.S2A   = PS2A;

//printf("(%i,%i):[%.30g] %.30g\n",S1.Label,S2.Label,MaxDistBetwConvexSegments,PS1B.Distance(PS2A));
//printf("AreMutuallyConvex: %i(%i)-%i(%i):%i\n",S1.Label,S1.GetPolarity(),S2.Label,S2.GetPolarity(),WithTheSamePolarity);
			//Añade la informacion al vector de convexidad de S1
			S1.Convexity.push_back(CSD);
		}
	}
//printf("Convexity ------------------------------> END\n");

	return;
}

RelationVector GetConvexityRelations(const SegmentMap & SM, Relation R, double SalienceFraction)
{
	Label LastSegmentLabel;

	ConvexSegmentDataVector::const_iterator CSDVit;
	SegmentMap::const_iterator AuxSMit;
	RelationVector  AuxRV;
	Relation		NewR;
	Segment			AuxS;

		//El Convex group se extiende por el ultimo segmento
		LastSegmentLabel = R.SBLabel;

		//Busco el segmento por su etiqueta y saco de el los segmentos cerca de su extremo B
		AuxSMit = SM.find(LastSegmentLabel);
		AuxS = (*AuxSMit).second;

		//Para cada segmento mutuamente convexo, creo una relacion si la distancia
		//que lo separa del segmento base (el anterior) es menor que el valor
		//SalienceFraction (algoritmo de Jacob)
		for (CSDVit=AuxS.Convexity.begin() ; CSDVit!=AuxS.Convexity.end() ; CSDVit++){
			if (((*CSDVit).Dist <= SalienceFraction) &&
				((*CSDVit).Label!= R.SALabel)       )
			{
				//La relacion contiene la informacion relativa a los dos segmentos
				//mutuamente convexos (Dist, Angle)
				//La relacion es univoca del segmento A al B por ello el orden es
				//importante.
				NewR.SALabel = LastSegmentLabel;
				NewR.SBLabel = (*CSDVit).Label;

				NewR.Property	  = REL_PROP_CONVEXITY;
				//TODO: De momento la significancia la hago coincidir con la distancia
				//pero tengo pendiente darle el sentido de probabilidad de no accidentalidad
				//que en este caso dependera de las caracteristicas del Convex Group en si mismo.
		Segment SA,SB;
		AuxSMit = SM.find(NewR.SALabel);
		SA = (*AuxSMit).second;
		AuxSMit = SM.find(NewR.SBLabel);
		SB = (*AuxSMit).second;
				NewR.Significance = (SA.GetPolarity()+SB.GetPolarity());
//				NewR.Significance = (*CSDVit).Dist;

				NewR.Dist  = (*CSDVit).Dist;
				NewR.Angle = (*CSDVit).Angle;

				//Añado la nueva relacion al vector que contiene las nuevas relaciones
				AuxRV.push_back(NewR);
			}
		}

	//Devuelvo un vector con las nuevas relaciones encontradas
	return AuxRV;
}

ConvexPerceptualGroupVector GetNewConvexPerceptualGroups(ConvexPerceptualGroup & CPGBase, const RelationVector & NewRelations)
{
	RelationVector::const_iterator RVit;
	Relation NewR,AuxR;
	ConvexPerceptualGroupVector NewCPGVector;
	RelationVector::const_iterator CPGit;
	ConvexPerceptualGroup NewCPG;

	LabelVector LV;
	LabelVector::const_iterator LVit;

	double TotalAngle;

	TotalAngle = CPGBase.GetAngle1n();

	//Combino el CPG base con las nuevas relaciones posibles de forma que 
	//creo un nuevo CPG por cada relación que combino con el CPG base.
	for (RVit=NewRelations.begin();RVit!=NewRelations.end();RVit++){
		//Compruebo que la nueva R (NewR) no existe ya en el PG
		NewR=*RVit;
		CPGit = find(CPGBase.RelationVector::begin(), CPGBase.RelationVector::end(), NewR);
		//Si no existe ya la relacion
		if (CPGit==CPGBase.RelationVector::end()) {
			NewCPG = CPGBase; //Comienzo a formar el NewCPG con el CPG base
			//Compruebo si la primera relación del nuevo CPG es del tipo
			//REL_PROP_ITSELF, en cuyo caso la elimino por ser sólo válida como
			//semilla inicial de la que arrancan las nuevas relaciones.
			AuxR = *NewCPG.RelationVector::begin();
			if (AuxR.Property == REL_PROP_ITSELF)
				NewCPG.clear();
			//Compruebo la restricción (2) del Algortimo de Jacob, es decir, ...
			//... compruebo si la nueva relación no incluye un segmento que ya pertenece al CPG
			//en cuyo caso solo admito la relación si el nuevo segmento es igual que el primero del
			//CPG ya que esto supone que el CPG queda cerrado.
			LV = NewCPG.GetLabels();
			LVit = find(LV.begin(),LV.end(),NewR.SBLabel);
			if ((LVit == LV.end()) || //Si la nueva label no esta en el CPG o...
				((LVit != LV.end()) &&  (NewR.SBLabel == AuxR.SALabel))) { //la nueva label ya esta en el CPG pero es la primera (pudiendo cerrar el CPG)
				//Compruebo la restricción (3) del Algoritmo de Jacon, es decir, ...
				//Si además la suma de los angulo del CPG más el angulo que proporciona la nueva relación
				//no es mayor de 2PI
				if ((TotalAngle + NewR.Angle) <= TWO_PI) {
					//admito la relacion
					NewCPG.push_back(NewR); //El nuevo PG es igual que el origen mas la nueva relacion
					//Antes de añadirlo al vector de nuevos Convex Perceptual Groups
					//tengo que estudiar si con la nueva relacion cumple todas las restricciones
					//del algoritmo de Jacob
					//TODO: Estudiar restricciones del algortimo de Jacob
					NewCPGVector.push_back(NewCPG);
				}
			}
		}
	}
	//Devuelvo un vector con los nuevos CPG que se han creado a partir del base.
	return NewCPGVector;
}


void SetNewConvexPGCandidates(const ConvexPerceptualGroupVector & NewCPGCandidates,
									 ConvexPerceptualGroupVector & CPGV)
{
	ConvexPerceptualGroup NewCPG,ActualCPG;
	ConvexPerceptualGroupVector::const_iterator NewCPGVit;

	//Añado cada nuevo CPG candidato generado al conjunto final de CPGs 
	//Le asigno una Label secuencial a cada uno.
	for (NewCPGVit=NewCPGCandidates.begin();NewCPGVit!=NewCPGCandidates.end();NewCPGVit++){
		NewCPG = *NewCPGVit;
		//Le asigno el Label que le corresponde por si la insercion tiene exito.
		NewCPG.Label = CPGV.size()+1;
		CPGV.push_back(NewCPG);
	}
}

double ComputeSalienceFraction(const SegmentMap & BaseSM, ConvexPerceptualGroup & CPG,double k){
	double SalienceFraction;
	double L1n = 0;
	double G1nminus1 = 0;

	L1n = CPG.GetL1n(BaseSM);
	CPG.GetG1n(&G1nminus1);   //Cuando un grupo esta abierto GetG1n devuelve
							  //la sumatoria de G de 1 a n menos 1 debido a que para
							  //cada relación se almacena la distancia Gi-1 entre los
							  //segmentos Si-1 y Si
							  //Cuando el grupo esta cerrado devuelve la sumatoria de 
							  //G de 1 a n
	SalienceFraction = ((L1n*(1-k))/k)-G1nminus1;

	return SalienceFraction;
}


ConvexPerceptualGroupMap ConvexPGPostProcessing(bool TraceMessages, UcharMatrix Retina, const SegmentMap & SM, const ConvexPerceptualGroupVector & NewCPGV){
	ConvexPerceptualGroup NewCPG,ActualCPG;
	ConvexPerceptualGroupVector::const_iterator NewCPGVit;
	ConvexPerceptualGroupMap CPGM;
	ConvexPerceptualGroupMap::iterator CPGMit;
	pair<ConvexPerceptualGroupMap::iterator, bool> CPGMins;

	//Proceso el conjunto final de CPGs para reducir el conjunto eliminado
	//aquellos CPGs que no me interesan.
	for (NewCPGVit=NewCPGV.begin();NewCPGVit!=NewCPGV.end();NewCPGVit++){
		NewCPG = *NewCPGVit;
		//Si el grupo esta cerrado en principio lo admito como válido
		//si no está cerrado (esta abierto) simplemente lo ignoro y no lo
		//añado al conjunto final.
		//También chequeo que el grupo cerrado tenga más de 2 relaciones.

		if (NewCPG.IsClosed() )//&& NewCPG.size()>2) -> No se generan grupos cerrados con sólo dos relaciones.
		{
			//Le asigno un Label nuevo que indica el orden en el nuevo conjunto
			NewCPG.Label = CPGM.size()+1;
			//Estudio si el CPG se ha añadido ya con otro orden de relaciones.
			//Lo intento insertar en el conjunto final. Si lo consigo es que no habia otro igual y ya he terminado...
			CPGMins = CPGM.insert(ConvexPerceptualGroupMap::value_type(NewCPG.GetLabels(),NewCPG));
			//...pero si no, quiere decir que ya existe y por lo tanto debo comprobar si
			//la Significancia total del nuevo es mayor (es decir, si la probabilidad de 
			//no accidentalidad es mas alta). Si es asi entonces sustituyo el anterior
			//por el nuevo, y si no, lo olvido.
			if (!CPGMins.second){
				ActualCPG = (*(CPGMins.first)).second;
				if(NewCPG.GetSignificanceAcc(REL_PROP_CONVEXITY) <= ActualCPG.GetSignificanceAcc(REL_PROP_CONVEXITY)){
					//Como ya existe un PG que contiene a los mismos segmentos
					//que el NewPG le pongo la misma Label que el PG antiguo.
					NewCPG.Label = (*(CPGMins.first)).second.Label;
					//Cambio el contenido del PG antiguo por el nuevo PG (NewPG)
					(*(CPGMins.first)).second = NewCPG;
				}
			}
		}
	}

	for (CPGMit=CPGM.begin();CPGMit!=CPGM.end();CPGMit++){
		//Si procede visualizo la traza del procesamiento
		if (TraceMessages){
//			printf("PostProcessing CPG no: %i of %i\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b",(*CPGMit).second.Label,CPGM.size());
			printf("PostProcessing CPG no: %i of %i\n",(*CPGMit).second.Label,CPGM.size());
		}
		(*CPGMit).second.SetSalience(SM);
		//Extraigo la información referente al polígono (área, perímetro, vector de características, etc)
		PolygonalFeatures(Retina,SM,(*CPGMit).second);
		(*CPGMit).second.SetPolarity(SM);
	}

	BuildCPGsGraph (CPGM);

	return CPGM;
}

void PolygonalFeatures(UcharMatrix Retina, const SegmentMap & SM, ConvexPerceptualGroup & CPG)
{
	RelationVector::const_iterator RVit;
	SegmentMap::const_iterator SMit;
	Segment S;
//printf("Polygonal Features -----------------------------. BEGIN\n");
	for(RVit = CPG.RelationVector::begin();
	    RVit!= CPG.RelationVector::end();
		RVit++) 
	{
		SMit = SM.find((*RVit).SALabel);
		S = (*SMit).second;
		CPG.Polygon::push_back(S.GetA());
		CPG.Polygon::push_back(S.GetB());
	}

//CPG.Polygon::Show();
	CPG.SetFeatureVector(Retina,SM);

//	CPG.SetPerimeter();
//	CPG.SetArea();
//	CPG.SetBinCentroid();
//	CPG.SetGrayCentroid(Retina);
//	CPG.SetThirdOrderCentralMoments(Retina);
//printf("Polygonal Features -----------------------------. END\n");

}

void BuildCPGsGraph (ConvexPerceptualGroupMap & CPGM){
	ConvexPerceptualGroupMap::iterator CPGMit1, CPGMit2;

	for (CPGMit1=CPGM.begin();CPGMit1!=CPGM.end();CPGMit1++)
		for (CPGMit2=CPGM.begin();CPGMit2!=CPGM.end();CPGMit2++)
			if ((*CPGMit1).first != (*CPGMit2).first)
				if (includes((*CPGMit1).first.begin(),
							 (*CPGMit1).first.end(),
							 (*CPGMit2).first.begin(),
							 (*CPGMit2).first.end())   &&
					(*CPGMit1).first.size() == (*CPGMit2).first.size()+1 ) {
					(*CPGMit1).second.push_back_Father((*CPGMit2).first);
					(*CPGMit2).second.push_back_Child ((*CPGMit1).first);
				}
}


//Esta funcion recibe dos segmentos S y SubS. SubS es un subsegmento de S, es decir,
//S debe contener a SubS y es resposabilidad del programador asegurar que esto sea asi
//ya que la funcion no hace ninguna comprobacion al respecto.
//Lo que hace esta funcion es extraer de la cadena de pixels que contiene S(que seguramente
//deben de venir del borde que ha dado lugar al segmento en el proceso de extraccion de
//segmentos) la subcadena que le debe corresponder a SubS y asignarsela.
//
//NOTA: Esta funcion es llamada por el proceso de generacion de segmentos que aplica las
//      extensiones de Jacobs (SetConvexSegmentMap)

void ExtractPixels (Segment S, Segment & SubS, double MaxDistance)
{
	Point PA1,PA2,PB1,PB2;
	Pixel Paux;
	Polygon POLY;
	PixelVector PVS,PVSubS;
	PixelVector::const_iterator PVit;

	SubS.RectangleAroundLine(SubS.GetA(), SubS.GetB(),MaxDistance,PA1,PA2,PB1,PB2);
	POLY.push_back(PA1);
	POLY.push_back(PB1);
	POLY.push_back(PB2);
	POLY.push_back(PA2);

	PVS = S.GetPixelChain();
	for (PVit=PVS.begin();PVit!=PVS.end();PVit++){
		Paux = *PVit;
		if (POLY.Inside(Paux)){
			PVSubS.push_back(Paux);
		}
	}

	SubS.SetPixelChain(PVSubS);
}

} //namespace GAC




