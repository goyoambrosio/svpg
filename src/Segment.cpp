/****
  SoftVision. Software for Computer Vision

  Gregorio Ambrosio Cestero (goyo@computer.org)
  System Engineering and Automation Department 
  University of Malaga. Spain                   

  $RCSfile: ImgSegment.cpp,v $
  $Revision: 1.1 $
  $Date: 2000/01/21 13:04:35 $
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


// ImgSegment.cpp: implementation of the ImgSegment class.
//
//////////////////////////////////////////////////////////////////////

#include <CVL/Segment.h>

using namespace GAC;

/**ImgSegment**************************\
		       operator==
\**************************************/
bool operator== ( const ImgSegment& S1, const ImgSegment& S2)
{
	return	(S1.A==S2.A)&&
			(S1.B==S2.B);
}

/**ImgSegment**************************\
		       operator<
\**************************************/
bool operator<  ( const ImgSegment& S1, const ImgSegment& S2)
{
	return	true; //(S1.Mod()==S2.Mod());
}

/**ImgSegment**************************\
		          Show
\**************************************/
void ImgSegment::Show()
{
	printf("\nLabel:%i\n",Label);
	printf("(%.30g,%.30g)->(%.30g,%.30g)\n",GetA().i,GetA().j,GetB().i,GetB().j);
}



/**ImgSegment**************************\
		       Serialize
\**************************************/
size_t ImgSegment::Serialize(FILE * stream)
{
	size_t count  = 0;
	size_t PVsize = 0;

	count += sizeof(unsigned int)*fwrite(&Label, sizeof(unsigned int),1,stream);
	count += Vector::Serialize(stream);
	return count;
}

/**ImgSegment**************************\
		   GetA, GetB
\**************************************/
Point		 ImgSegment::GetA()						{return Vector::GetA();}
Point		 ImgSegment::GetB()						{return Vector::GetB();}

/**ImgSegment**************************\
		   EndPointDistance
\**************************************/
// Computes the minimum distance between the nearest endpoints of segments

double ImgSegment::EndPointDistance(const ImgSegment& S)
{
	vector<double> DistVector;
	vector<double>::iterator Dit;
	double Distance;

	DistVector.clear();
	DistVector.push_back(A.Distance(S.A));
	DistVector.push_back(A.Distance(S.B));
	DistVector.push_back(B.Distance(S.A));
	DistVector.push_back(B.Distance(S.B));
	Dit = min_element(DistVector.begin(), DistVector.end()) ;
	Distance = *Dit;
	return Distance;
}

/**ImgSegment**************************\
		   MidPointDistance
\**************************************/
// Computes the minimum distance between midpoint of segments

double ImgSegment::MidPointDistance(const ImgSegment& S)
{
	double Distance;
	ImgSegment SS = S;

	Distance = MidPoint().Distance(SS.MidPoint());
	return Distance;
}

/**ImgSegment**************************\
		   OverlapMod
\**************************************/
//Computes the module of the overlapping between this segment and the perpendicular 
//projection of S over this segment

double ImgSegment::OverlapMod(const ImgSegment& S)
{
	ImgSegment Saux,SOverlap;
	Point CutA;
	Point CutB;

	Saux = S;

	CutA = Intersection(Saux.PerpLine(Saux.GetA()));
	CutB = Intersection(Saux.PerpLine(Saux.GetB()));

	if (Overlap(ImgSegment(CutA,CutB),SOverlap))
		return SOverlap.Mod();
	else 
		return 0.0;
}


/**ImgSegmentVector********************\
		   ImgSegmentVector
\**************************************/
ImgSegmentVector::ImgSegmentVector()
{

}

ImgSegmentVector::~ImgSegmentVector()
{

}

/**ImgSegmentVector********************\
		   EndPointDistanceGraph
\**************************************/
AffGraph<pImgSegment> ImgSegmentVector::EndPointDistanceGraph()
{
	AffGraph<pImgSegment> EndPointDistanceGraph;
	ImgSegmentVector::iterator ISVit1,ISVit2;
	ImgSegment S1,S2;
	leda_node u,v;
	leda_edge e;
	map<size_t,leda_node> MNode;


	EndPointDistanceGraph.del_all_nodes();
	EndPointDistanceGraph.del_all_edges();

	//Node creation process
	for (ISVit1 = begin(); ISVit1 != end(); ISVit1++){
		S1  = (*ISVit1);
		u = EndPointDistanceGraph.new_node();
		EndPointDistanceGraph.assign(u,ISVit1);
		MNode[S1.Label]=u;
	}

	//Edge creation process
	for (ISVit1 = begin(); ISVit1 != end(); ISVit1++){
		S1  = (*ISVit1);
		for (ISVit2 = ISVit1+1; ISVit2 != end(); ISVit2++){
				S2  = (*ISVit2);

				u = MNode[S1.Label];
				v = MNode[S2.Label];
				e = EndPointDistanceGraph.new_edge(u,v);
				EndPointDistanceGraph.assign(e,S1.EndPointDistance(S2));
		}
	}

	return EndPointDistanceGraph;

}


/**ImgSegmentVector********************\
		   EndPointDistanceMatrix
\**************************************/
DoubleMatrix ImgSegmentVector::EndPointDistanceMatrix()
{
	DoubleMatrix EndPointDistanceMatrix(size(),size());
	ImgSegmentVector::iterator ISVit1,ISVit2;
	ImgSegment S1,S2;
	double Val;

	EndPointDistanceMatrix.Init();

	//Edge creation process
	for (ISVit1 = begin(); ISVit1 != end(); ISVit1++){
		S1  = (*ISVit1);
		for (ISVit2 = ISVit1+1; ISVit2 != end(); ISVit2++){
			S2  = (*ISVit2);
			Val = S1.EndPointDistance(S2);
			EndPointDistanceMatrix[S1.Label-1][S2.Label-1]=Val;
			EndPointDistanceMatrix[S2.Label-1][S1.Label-1]=Val;
		}
	}

	return EndPointDistanceMatrix;
}


/**ImgSegmentVector********************\
		   MidPointDistanceGraph
\**************************************/
AffGraph<pImgSegment> ImgSegmentVector::MidPointDistanceGraph()
{
	AffGraph<pImgSegment> MidPointDistanceGraph;
	ImgSegmentVector::iterator ISVit1,ISVit2;
	ImgSegment S1,S2;
	leda_node u,v;
	leda_edge e;
	map<size_t,leda_node> MNode;


	MidPointDistanceGraph.del_all_nodes();
	MidPointDistanceGraph.del_all_edges();

	//Node creation process
	for (ISVit1 = begin(); ISVit1 != end(); ISVit1++){
		S1  = (*ISVit1);
		u = MidPointDistanceGraph.new_node();
		MidPointDistanceGraph.assign(u,ISVit1);
		MNode[S1.Label]=u;
	}

	//Edge creation process
	for (ISVit1 = begin(); ISVit1 != end(); ISVit1++){
		S1  = (*ISVit1);
		for (ISVit2 = ISVit1+1; ISVit2 != end(); ISVit2++){
				S2  = (*ISVit2);

				u = MNode[S1.Label];
				v = MNode[S2.Label];
				e = MidPointDistanceGraph.new_edge(u,v);
				MidPointDistanceGraph.assign(e,S1.MidPointDistance(S2));
		}
	}

	return MidPointDistanceGraph;

}

/**ImgSegmentVector********************\
		   MidPointDistanceMatrix
\**************************************/
DoubleMatrix ImgSegmentVector::MidPointDistanceMatrix()
{
	DoubleMatrix MidPointDistanceMatrix(size(),size());
	ImgSegmentVector::iterator ISVit1,ISVit2;
	ImgSegment S1,S2;
	double Val;

	MidPointDistanceMatrix.Init();

	//Edge creation process
	for (ISVit1 = begin(); ISVit1 != end(); ISVit1++){
		S1  = (*ISVit1);
		for (ISVit2 = ISVit1+1; ISVit2 != end(); ISVit2++){
			S2  = (*ISVit2);
			Val = S1.MidPointDistance(S2);
			MidPointDistanceMatrix[S1.Label-1][S2.Label-1]=Val;
			MidPointDistanceMatrix[S2.Label-1][S1.Label-1]=Val;
		}
	}

	return MidPointDistanceMatrix;
}


/**ImgSegmentVector********************\
		   ShortAngleGraph
\**************************************/
AffGraph<pImgSegment> ImgSegmentVector::ShortAngleGraph()
{
	AffGraph<pImgSegment> ShortAngleGraph;
	ImgSegmentVector::iterator ISVit1,ISVit2;
	ImgSegment S1,S2;
	leda_node u,v;
	leda_edge e;
	map<size_t,leda_node> MNode;


	ShortAngleGraph.del_all_nodes();
	ShortAngleGraph.del_all_edges();

	//Node creation process
	for (ISVit1 = begin(); ISVit1 != end(); ISVit1++){
		S1  = (*ISVit1);
		u = ShortAngleGraph.new_node();
		ShortAngleGraph.assign(u,ISVit1);
		MNode[S1.Label]=u;
	}

	//Edge creation process
	for (ISVit1 = begin(); ISVit1 != end(); ISVit1++){
		S1  = (*ISVit1);
		for (ISVit2 = ISVit1+1; ISVit2 != end(); ISVit2++){
				S2  = (*ISVit2);

				u = MNode[S1.Label];
				v = MNode[S2.Label];
				e = ShortAngleGraph.new_edge(u,v);
				ShortAngleGraph.assign(e,S1.ShortAngle(S2));
		}
	}

	return ShortAngleGraph;
}

/**ImgSegmentVector********************\
		   ShortAngleMatrix
\**************************************/
DoubleMatrix ImgSegmentVector::ShortAngleMatrix()
{
	DoubleMatrix ShortAngleMatrix(size(),size());
	ImgSegmentVector::iterator ISVit1,ISVit2;
	ImgSegment S1,S2;
	double Val;

	ShortAngleMatrix.Init();

	//Edge creation process
	for (ISVit1 = begin(); ISVit1 != end(); ISVit1++){
		S1  = (*ISVit1);
		for (ISVit2 = ISVit1+1; ISVit2 != end(); ISVit2++){
			S2  = (*ISVit2);
			Val = S1.ShortAngle(S2);
			ShortAngleMatrix[S1.Label-1][S2.Label-1]=Val;
			ShortAngleMatrix[S2.Label-1][S1.Label-1]=Val;
		}
	}

	return ShortAngleMatrix;
}


/**ImgSegmentVector********************\
		   OverlapModGraph
\**************************************/
AffGraph<pImgSegment> ImgSegmentVector::OverlapModGraph()
{
	AffGraph<pImgSegment> OverlapModGraph;
	ImgSegmentVector::iterator ISVit1,ISVit2;
	ImgSegment S1,S2;
	leda_node u,v;
	leda_edge e;
	map<size_t,leda_node> MNode;


	OverlapModGraph.del_all_nodes();
	OverlapModGraph.del_all_edges();

	//Node creation process
	for (ISVit1 = begin(); ISVit1 != end(); ISVit1++){
		S1  = (*ISVit1);
		u = OverlapModGraph.new_node();
		OverlapModGraph.assign(u,ISVit1);
		MNode[S1.Label]=u;
	}

	//Edge creation process
	for (ISVit1 = begin(); ISVit1 != end(); ISVit1++){
		S1  = (*ISVit1);
		for (ISVit2 = ISVit1+1; ISVit2 != end(); ISVit2++){
				S2  = (*ISVit2);

				u = MNode[S1.Label];
				v = MNode[S2.Label];
				e = OverlapModGraph.new_edge(u,v);
				OverlapModGraph.assign(e,S1.OverlapMod(S2));
		}
	}

	return OverlapModGraph;
}

/**ImgSegmentVector********************\
		   OverlapModMatrix
\**************************************/
DoubleMatrix ImgSegmentVector::OverlapModMatrix()
{
	DoubleMatrix OverlapModMatrix(size(),size());
	ImgSegmentVector::iterator ISVit1,ISVit2;
	ImgSegment S1,S2;
	double Val;

	OverlapModMatrix.Init();

	//Edge creation process
	for (ISVit1 = begin(); ISVit1 != end(); ISVit1++){
		S1  = (*ISVit1);
		for (ISVit2 = ISVit1+1; ISVit2 != end(); ISVit2++){
			S2  = (*ISVit2);
			Val = S1.OverlapMod(S2);
			OverlapModMatrix[S1.Label-1][S2.Label-1]=Val;
			OverlapModMatrix[S2.Label-1][S1.Label-1]=Val;
		}
	}

	return OverlapModMatrix;
}



/**ImgSegmentVector********************\
		   ProximityAffGraph
\**************************************/
AffGraph<pImgSegment> ImgSegmentVector::ProximityAffGraph(double MaxDistance,double d0p)
{
	AffGraph<pImgSegment> AffProximityGraph;
	ImgSegmentVector::iterator ISVit1,ISVit2;
	Point S1A,S1B,S2A,S2B;
	vector<double> DistVector;
	vector<double>::iterator Dit;
	double Distance,AffProximity, d0;
	ImgSegment S1,S2,AuxS,SbetwnMidPoints;
	leda_node u,v;
	leda_edge e;
	map<size_t,leda_node> MNode;

	d0  = d0p*MaxDistance;

	//Node creation process
	for (ISVit1 = begin(); ISVit1 != end(); ISVit1++){
		S1  = (*ISVit1);
		u = AffProximityGraph.new_node();
		AffProximityGraph.assign(u,ISVit1);
		MNode[S1.Label]=u;
	}


	//Edge creation process
	for (ISVit1 = begin(); ISVit1 != end(); ISVit1++){
		S1  = (*ISVit1);
		S1A = S1.GetA();
		S1B = S1.GetB();
		for (ISVit2 = ISVit1+1; ISVit2 != end(); ISVit2++){
				S2  = (*ISVit2);
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
					SbetwnMidPoints.Set(S1.MidPoint(),S2.MidPoint());
					Distance = SbetwnMidPoints.Mod();
					AffProximity  = ((Distance*Distance)/(d0*d0));
					if (AffProximity<DoubleEpsilon)  AffProximity  = 0.0;
					AffProximity = exp(-AffProximity);
					u = MNode[S1.Label];
					v = MNode[S2.Label];
					e = AffProximityGraph.new_edge(u,v);
					AffProximityGraph.assign(e,AffProximity);
			}
		}
	}

	return AffProximityGraph;
}

/**ImgSegmentVector********************\
		   ParallelGraph
\**************************************/
/**********************************************************************\
This function returns three graphs. Nodes in graphs represent image 
segments. An edge means there is a parallel relationship between two 
nodes, i.e., two segments. Edge value are different in each graph. 
In DistanceGraph edge value is the distance between midpoints of S1Aux
and S2Aux. 
In AngleGraph is the angle between 0 and PI radians. 
Finally, in OverlapGraph is the module of the overlap segment resulted 
of the projection of S2 over S1.


                  S1 
      <=========================>
	                    S1Aux
	  <--------------------------------------->

     S1A         S2BinS1       S1B         S2AinS1

      *-------------*-----------*.............*


      *.............*-----------*-------------*
   S1AinS2         S2B       S1BinS2         S2A

      <--------------------------------------->
	                    S2Aux
                    <=========================>
					            S2

Input parameter are:
 MaxDistance and MinDistance: Two segments are considered as possible 
  parallel segments only if the distance that separates them is 
  between MinDistance and MaxDistance, i.e., 
  MinDistance >= Distance beetween segments >= MaxDistance
 MaxAngle: Two segments are considered as possible paralle segments 
 if they have an angle less than MaxAngle. The angle is measured 
 in radians.
\**********************************************************************/


void ImgSegmentVector::ParallelGraph(AffGraph<pImgSegment> & DistanceGraph,
									 AffGraph<pImgSegment> & AngleGraph,
									 AffGraph<pImgSegment> & OverlapGraph,
									 double MaxDistance,double MinDistance,double MaxAngle)
{
	ImgSegment S1,S2,S1aux,S2aux,S1S2,AuxS;
	ImgSegmentVector::iterator ISVit1,ISVit2;
	Point S1A,S1B,S2A,S2B;
	Point S2AinS1,S2BinS1,S1AinS2,S1BinS2;
	double Distance,Angle,Overlap;
	leda_node u,v;
	leda_edge e;
	map<size_t,leda_node> DistanceMNode,AngleMNode,OverlapMNode;

	DistanceGraph.del_all_nodes();
	DistanceGraph.del_all_edges();
	AngleGraph.del_all_nodes();
	AngleGraph.del_all_edges();
	OverlapGraph.del_all_nodes();
	OverlapGraph.del_all_edges();

	//Node creation process
	for (ISVit1 = begin(); ISVit1 != end(); ISVit1++){
		S1  = (*ISVit1);
		//DistanceGraph
		u = DistanceGraph.new_node();
		DistanceGraph.assign(u,ISVit1);
		DistanceMNode[S1.Label]=u;
		//AngleGraph
		u = AngleGraph.new_node();
		AngleGraph.assign(u,ISVit1);
		AngleMNode[S1.Label]=u;
		//OverlapGraph
		u = OverlapGraph.new_node();
		OverlapGraph.assign(u,ISVit1);
		OverlapMNode[S1.Label]=u;
	}

	//Edge creation process
	for (ISVit1 = begin(); ISVit1 != end(); ISVit1++){
		S1  = (*ISVit1);
		S1A = S1.GetA();
		S1B = S1.GetB();
		for (ISVit2 = ISVit1+1; ISVit2 != end(); ISVit2++){
			S2  = (*ISVit2);
			S2A = S2.GetA();
			S2B = S2.GetB();

			//Si S1 y S2 forman un angulo menor que MaxAngle ...
			Angle = S1.Angle(S2);
			if (Angle>HALF_PI) Angle = PI-Angle;

			if (Angle<MaxAngle){

				//Trazo la perpendicular a S2 por cada uno de sus extremos
				//y obtengo los puntos de corte con S1
				//Hago lo mismo con S1 sobre S2
				S2AinS1 = S1.Intersection(S2.PerpLine(S2A));
				S2BinS1 = S1.Intersection(S2.PerpLine(S2B));
				S1AinS2 = S2.Intersection(S1.PerpLine(S1A));
				S1BinS2 = S2.Intersection(S1.PerpLine(S1B));

				S1aux = S1;
				if (S1A.Distance(S2AinS1) > S1aux.Mod()) S1aux = ImgSegment(S1A,S2AinS1);
				if (S1A.Distance(S2BinS1) > S1aux.Mod()) S1aux = ImgSegment(S1A,S2BinS1);
				if (S1B.Distance(S2AinS1) > S1aux.Mod()) S1aux = ImgSegment(S1B,S2AinS1);
				if (S1B.Distance(S2BinS1) > S1aux.Mod()) S1aux = ImgSegment(S1B,S2BinS1);

				S2aux = S2;
				if (S2A.Distance(S1AinS2) > S2aux.Mod()) S2aux = ImgSegment(S2A,S1AinS2);
				if (S2A.Distance(S1BinS2) > S2aux.Mod()) S2aux = ImgSegment(S2A,S1BinS2);
				if (S2B.Distance(S1AinS2) > S2aux.Mod()) S2aux = ImgSegment(S2B,S1AinS2);
				if (S2B.Distance(S1BinS2) > S2aux.Mod()) S2aux = ImgSegment(S2B,S1BinS2);

				//Calculo la distancia entre los puntos medios de S1aux y S2aux
				Distance = fabs(S1aux.MidPoint().Distance(S2aux.MidPoint()));

				//Si la distancia es menor que MaxDistance ...
				if (Distance <= MaxDistance &&
					Distance >= MinDistance ){

					//Calculo el solapamiento entre S1 y la proyección de S2 sobre S1
					S1.Overlap(ImgSegment(S2AinS1,S2BinS1),S1S2);
					Overlap = S1S2.Mod();

					//DistanceGraph
					u = DistanceMNode[S1.Label];
					v = DistanceMNode[S2.Label];
					e = DistanceGraph.new_edge(u,v);
					DistanceGraph.assign(e,Distance);
					//AngleGraph
					u = AngleMNode[S1.Label];
					v = AngleMNode[S2.Label];
					e = AngleGraph.new_edge(u,v);
					AngleGraph.assign(e,Angle);
					//OverlapGraph
					u = OverlapMNode[S1.Label];
					v = OverlapMNode[S2.Label];
					e = OverlapGraph.new_edge(u,v);
					OverlapGraph.assign(e,Overlap);

				}
			}
		}
	}
}


/**ImgSegmentVector********************\
		   ParallelAffGraph
\**************************************/
AffGraph<pImgSegment> ImgSegmentVector::ParallelAffGraph(double MaxDistance,double MaxAngle)
{
	AffGraph<pImgSegment> AffParallelGraph;
	ImgSegmentVector::iterator ISVit1,ISVit2;
	Point S1A,S1B,S2A,S2B;
	double Distance,Affinity;
	ImgSegment S1,S2,AuxS;

	double DstSignificance = 0,ParSignificance = 0;
	double Significance = 0;
	Point S2MidPoint,S2AinS1,S2BinS1,S1AinS2,S1BinS2;
	double Angle;
	
	leda_node u,v;
	leda_edge e;
	map<size_t,leda_node> MNode;

	//Node creation process
	for (ISVit1 = begin(); ISVit1 != end(); ISVit1++){
		S1  = (*ISVit1);
		u = AffParallelGraph.new_node();
		AffParallelGraph.assign(u,ISVit1);
		MNode[S1.Label]=u;
	}

	//Edge creation process
	for (ISVit1 = begin(); ISVit1 != end(); ISVit1++){
		S1  = (*ISVit1);
		S1A = S1.GetA();
		S1B = S1.GetB();
		for (ISVit2 = ISVit1+1; ISVit2 != end(); ISVit2++){
			S2  = (*ISVit2);
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

						Affinity = Significance;
						u = MNode[S1.Label];
						v = MNode[S2.Label];
						e = AffParallelGraph.new_edge(u,v);
						AffParallelGraph.assign(e,Affinity);
					}
				}
			}
		}
	}

	return AffParallelGraph;
}


/**ImgSegmentVector********************\
		   CollinearGraph
\**************************************/
void ImgSegmentVector::CollinearGraph(AffGraph<pImgSegment> & DistanceGraph,double MaxDistance,double MaxAngle,double MaxParallelDistance)
{
	ImgSegmentVector::iterator ISVit1,ISVit2;
	vector<double> DistVector;
	vector<double>::iterator Dit;
	Point S1A,S1B,S2A,S2B;
	double Distance,Affinity;
	ImgSegment S1,S2,AuxS;

	Point S2MidPoint,S2AinS1,S2BinS1,S1AinS2,S1BinS2;
	double Angle;
	
	leda_node u,v;
	leda_edge e;
	map<size_t,leda_node> MNode;

	DistanceGraph.del_all_nodes();
	DistanceGraph.del_all_edges();

	//Node creation process
	for (ISVit1 = begin(); ISVit1 != end(); ISVit1++){
		S1  = (*ISVit1);
		u = DistanceGraph.new_node();
		DistanceGraph.assign(u,ISVit1);
		MNode[S1.Label]=u;
	}

	//Edge creation process
	for (ISVit1 = begin(); ISVit1 != end(); ISVit1++){
		S1  = (*ISVit1);
		S1A = S1.GetA();
		S1B = S1.GetB();
		for (ISVit2 = ISVit1+1; ISVit2 != end(); ISVit2++){
			S2  = (*ISVit2);
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
						if (Distance < MaxDistance) {
							Affinity = Distance;
							//Añado el segmento al conjunto de segmentos paralelos a S1
							u = MNode[S1.Label];
							v = MNode[S2.Label];
							e = DistanceGraph.new_edge(u,v);
							DistanceGraph.assign(e,Affinity);
						}
					}
				}
			}
		}
	}
}

/**ImgSegmentVector********************\
		   CollinearAffGraph
\**************************************/
AffGraph<pImgSegment> ImgSegmentVector::CollinearAffGraph(double MaxDistance,double MaxAngle,double MaxParallelDistance)
{
	AffGraph<pImgSegment> AffCollinearGraph;
	ImgSegmentVector::iterator ISVit1,ISVit2;
	vector<double> DistVector;
	vector<double>::iterator Dit;
	Point S1A,S1B,S2A,S2B;
	double Distance,Affinity;
	ImgSegment S1,S2,AuxS;

	Point S2MidPoint,S2AinS1,S2BinS1,S1AinS2,S1BinS2;
	double Angle;
	
	leda_node u,v;
	leda_edge e;
	map<size_t,leda_node> MNode;

	//Node creation process
	for (ISVit1 = begin(); ISVit1 != end(); ISVit1++){
		S1  = (*ISVit1);
		u = AffCollinearGraph.new_node();
		AffCollinearGraph.assign(u,ISVit1);
		MNode[S1.Label]=u;
	}

	//Edge creation process
	for (ISVit1 = begin(); ISVit1 != end(); ISVit1++){
		S1  = (*ISVit1);
		S1A = S1.GetA();
		S1B = S1.GetB();
		for (ISVit2 = ISVit1+1; ISVit2 != end(); ISVit2++){
			S2  = (*ISVit2);
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
						if (Distance < MaxDistance) {
							//Convierto la distancia a significancia (probabilidad de no accidentalidad)
							//Cuanto menor sea la distancia mayor es la probabilidad de que la
							//proximidad no sea accidental (significancia). Es decir si la distancia es 0 la 
							//significancia es 1, y si la distancia es la maxima permitida la siginificancia es 0.
							//Esto genera una recta cuya ecuacion es y=-(1/MaxDist)x+1.
							//Donde x es la distancia e y la significancia.
							//Se puede variar esta relacion en funcion de experimentos futuros.
//								Affinity = (-(1.0/MaxDistBetwColSegments)*Distance + 1.0);
							Affinity = (S1.Mod()+S2.Mod())/(S1.Mod()+S2.Mod()+Distance);
							//Añado el segmento al conjunto de segmentos paralelos a S1
							u = MNode[S1.Label];
							v = MNode[S2.Label];
							e = AffCollinearGraph.new_edge(u,v);
							AffCollinearGraph.assign(e,Affinity);
						}
					}
				}
			}
		}
	}
	return AffCollinearGraph;
}

/**ImgSegmentVector********************\
		   ConvexGraph
\**************************************/
void ImgSegmentVector::ConvexGraph(AffGraph<pImgSegment> & DistanceGraph,
								   AffGraph<pImgSegment> & ClockwiseAngleGraph, 
								   AffGraph<pImgSegment> & CircularityGraph, 
								   double MaxDistance, double MaxNoConvexityThreshold)
{
	ImgSegmentVector TSV;
	ImgSegmentVector::iterator ISVit1,ISVit2;
	Point S1A,S1B,S2A,S2B;
	double AffConvexity;
	ImgSegment S1,S2,AuxS;
	leda_node u,v;
	leda_edge e;
	map<size_t,leda_node> DistanceMNode,ClockwiseAngleMNode,CircularityMNode;
	bool AreMutuallyConvex = false,S2IsConvexWithS1,S1IsConvexWithS2,InTheSameLine;
	size_t LastLabel,S1Label,S2Label;
	double Distance;


	TSV = TwoOrientation();
	LastLabel = size();



	DistanceGraph.del_all_nodes();
	DistanceGraph.del_all_edges();
	ClockwiseAngleGraph.del_all_nodes();
	ClockwiseAngleGraph.del_all_edges();
	CircularityGraph.del_all_nodes();
	CircularityGraph.del_all_edges();

	//Node creation process
	for (ISVit1 = begin(); ISVit1 != end(); ISVit1++){
		S1  = (*ISVit1);
		//DistanceGraph
		u = DistanceGraph.new_node();
		DistanceGraph.assign(u,ISVit1);
		DistanceMNode[S1.Label]=u;
		//ClockwiseAngleGraph
		u = ClockwiseAngleGraph.new_node();
		ClockwiseAngleGraph.assign(u,ISVit1);
		ClockwiseAngleMNode[S1.Label]=u;
		//CircularityGraph
		u = CircularityGraph.new_node();
		CircularityGraph.assign(u,ISVit1);
		CircularityMNode[S1.Label]=u;
	}

	//Edge creation process
	for (ISVit1 = TSV.begin(); ISVit1 != TSV.end(); ISVit1++){
		S1  = (*ISVit1);
		S1A = S1.GetA();
		S1B = S1.GetB();
		for (ISVit2 = ISVit1+1; ISVit2 != TSV.end(); ISVit2++){
			S2  = (*ISVit2);
			S2A = S2.GetA();
			S2B = S2.GetB();

			//Los dos segmentos son mutuamente convexos cuando los extremos
			//de S2 estan a la derecha (semiplano negativo) de S1 y cuando los
			//extremos de S1 estan a la derecha (semiplano negativo) de S2...
			// y cuando no son el mismo segmento ...
			// ni son colinenales


			if (S1.IsInNegRightSide(S2A) && S1.IsInNegRightSide(S2B))
				S2IsConvexWithS1 = true;
			else if (S1.IsInNegRightSide(S2A) && S1.IsNearNegRightSide(S2B,MaxNoConvexityThreshold))
				S2IsConvexWithS1 = true;
			else if (S1.IsNearNegRightSide(S2A,MaxNoConvexityThreshold) && S1.IsInNegRightSide(S2B))
				S2IsConvexWithS1 = true;
			else
				S2IsConvexWithS1 = false;

			if (S2.IsInNegRightSide(S1A) && S2.IsInNegRightSide(S1B))
				S1IsConvexWithS2 = true;
			else if (S2.IsInNegRightSide(S1A) && S2.IsNearNegRightSide(S1B,MaxNoConvexityThreshold))
				S1IsConvexWithS2 = true;
			else if (S2.IsNearNegRightSide(S1A,MaxNoConvexityThreshold) && S2.IsInNegRightSide(S1B))
				S1IsConvexWithS2 = true;
			else
				S1IsConvexWithS2 = false;

			InTheSameLine = (fabs(S1.Pow(S2A))<1.0e-5) && (fabs(S1.Pow(S2B))<1.0e-5);

			AreMutuallyConvex = ( S2IsConvexWithS1				&&
								  S1IsConvexWithS2				&&
								  !InTheSameLine				
								);


			//Si los dos segmentos son mutuamente convexos ...
			if (AreMutuallyConvex){
				//y la distancia que separa los dos segmentos está dentro del umbral
				Distance = S1.MidPoint().Distance(S2.MidPoint());
				if (Distance<=MaxDistance)
				{
					//Obtengo la informacion necesaria de la relacion de 
					//convexidad.
					//CSD.Dist  = S1B.Distance(S2A);
					//CSD.Angle = S1.ClockwiseAngle(S2);
					//CSD.Label = S2.Label;
					//CSD.S2A   = S2A;


					(S1.Label>LastLabel)?(S1Label=S1.Label-LastLabel):(S1Label=S1.Label);
					(S2.Label>LastLabel)?(S2Label=S2.Label-LastLabel):(S2Label=S2.Label);

					AffConvexity = Distance;
					if (AffConvexity == 0.0) AffConvexity = 0.0000001;
					u = DistanceMNode[S1Label];
					v = DistanceMNode[S2Label];
					e = DistanceGraph.new_edge(u,v);
					DistanceGraph.assign(e,AffConvexity);

					AffConvexity = S1.ClockwiseAngle(S2);
					if (AffConvexity == 0.0) AffConvexity = 0.0000001;
					u = ClockwiseAngleMNode[S1Label];
					v = ClockwiseAngleMNode[S2Label];
					e = ClockwiseAngleGraph.new_edge(u,v);
					ClockwiseAngleGraph.assign(e,AffConvexity);

					AffConvexity = pow(2.0*S1.Mod()+2.0*S2.Mod(),2.0)/fabs(S1.Vect(S2)); //perimetro^2/area
					if (AffConvexity == 0.0) AffConvexity = 0.0000001;
					u = CircularityMNode[S1Label];
					v = CircularityMNode[S2Label];
					e = CircularityGraph.new_edge(u,v);
					CircularityGraph.assign(e,AffConvexity);
				}
			}
		}
	}
}



/**ImgSegmentVector********************\
	ExtractSegmentsFromTJunctions
\**************************************/
ImgSegmentVector ImgSegmentVector::ExtractSegmentsFromTJunctions (double          MinMod,
																double          MaxDistBetwConvexSegments,
																double          MaxNoConvexityThreshold,
																bool            JacobExtension_1,
																bool            JacobExtension_2,
																bool            IncludeOriginal)
{
	unsigned int LastLabel;
	ImgSegment S1,S2,S2AC,S2CB,SO;
	Point S1A,S1B,S2A,S2B,C,S2C1,S2C2;

	ImgSegmentVector BaseISV,ExtendedISV_1,ExtendedISV_2,ConvexImgSegmentVector;
	ImgSegmentVector::iterator ISVit1,ISVit2;

	//Asignamos a LastLabel la ultima etiqueta para poder asignar etiquetas 
	//a los nuevos segmentos.
	LastLabel = size();

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

		for (ISVit1 = begin();ISVit1 != end();ISVit1++){
			for (ISVit2 = begin();ISVit2 != end();ISVit2++){
				S1 = (*ISVit1);
				S1A = S1.GetA();
				S1B = S1.GetB();
				S2 = (*ISVit2);
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

						//Si el módulo del segmento S2A->S2C1 es mayor que MinMod
						//y el restante módulo del segmento C->S2B es mayor que Threshold
						//entonces acepto la creación del segmento S2A->S2C1
						if ((S2A.Distance(S2C1)>MinMod) &&
						    (C.Distance(S2B) > MaxNoConvexityThreshold)
						   )
						{
							S2AC.Set(S2A,S2C1);
							LastLabel++;
							S2AC.Label = LastLabel;
							//ExtractPixels (S2, S2AC, MaxDistance);
							ExtendedISV_1.push_back(S2AC);
						}

						//Si el módulo del segmento S2B->S2C2 es mayor que MinMod
						//y el restante módulo del segmento C->S2A es mayor que Threshold
						//entonces acepto la creación del segmento S2B->S2C2
						if ((S2B.Distance(S2C2)>MinMod) &&
						    (C.Distance(S2A) > MaxNoConvexityThreshold)
						   )
						{
							S2CB.Set(S2C2,S2B);
							LastLabel++;
							S2CB.Label = LastLabel;
							//ExtractPixels (S2, S2CB, MaxDistance);
							ExtendedISV_1.push_back(S2CB);
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

		for (ISVit1 = ExtendedISV_1.begin();ISVit1 != ExtendedISV_1.end();ISVit1++){
			for (ISVit2 = ISVit1+1;ISVit2 != ExtendedISV_1.end();ISVit2++){
				S1 = (*ISVit1);
				S2 = (*ISVit2);
				if ((S1.GetA()!=S2.GetA())&&(S1.GetB()!=S2.GetB()))
					if (S1.Overlap(S2,SO))
						if(SO.GetA()!=SO.GetB()){
								LastLabel++;
								SO.Label = LastLabel;
								//ExtractPixels (S2, SO, MaxDistance);
								ExtendedISV_2.push_back(SO);
							}
			}
		}
//printf("ExtendedSM_2.Show()------------->BEGIN\n");
//ExtendedSM_2.Show();
//printf("ExtendedSM_2.Show()------------->END\n");
	}

	if (IncludeOriginal)
		for (ISVit1 = begin();ISVit1 != end();ISVit1++)
			BaseISV.push_back(*ISVit1);


	for (ISVit1 = ExtendedISV_1.begin();ISVit1 != ExtendedISV_1.end();ISVit1++)
		BaseISV.push_back(*ISVit1);
	for (ISVit2 = ExtendedISV_2.begin();ISVit2 != ExtendedISV_2.end();ISVit2++)
		BaseISV.push_back(*ISVit2);

	return BaseISV;

}


/**ImgSegmentVector********************\
	         TwoOrientation
\**************************************/
ImgSegmentVector ImgSegmentVector::TwoOrientation()
{
	ImgSegmentVector TwoOrientationISV;
	ImgSegmentVector::iterator ISVit1;
	ImgSegment S1,S2;
	Point S1A,S1B;
	size_t           LastLabel;


	LastLabel = size();

	for (ISVit1 = begin();ISVit1 != end();ISVit1++){
		S1 = (*ISVit1);
		S1A = S1.GetA();
		S1B = S1.GetB();
		//Construyo S2
		S2 = ImgSegment(S1B,S1A);
		S2.Label = S1.Label + LastLabel;
		//Inserto los dos segmentos
		TwoOrientationISV.push_back(S1);
		TwoOrientationISV.push_back(S2);
	}

	return TwoOrientationISV;
}

/**ImgSegmentVector********************\
	         ParallelGrouping
\**************************************/
/*******************************************************************************\ 
    map <Label,PerceptualGroup>
	   ImgSegmentVector::ParallelGrouping(double MaxDistance,double MaxAngle)

  This function finds parallel groups of segments. It's a member of the
ImgSegmentVector class, so it works over a vector of segments and it returns
a map of perceptual groups indexed with labels.

  Input parameter are:

  MaxDistance : Two segments are considered as possible parallel segments only
                if the distance that separates them is less than this parameter
  MaxAngle    : Two segments are considered as possible paralle segments if
                they have an angle less than MaxAngle. The angle is measured 
                in radians.
  
  Output parameter is:

  map <Label,PerceptualGroup>
 
    ----   ---- ---- ----       ----
   |    | |    |    |    | ... |    |
   |    | |    |    |    | ... |   <------- *ImgSegment
    ----   ---- ---- ----       ----
     |    \____________ ____________/
     |	               V
     |				   |
     |            PerceptualGroup = pImgSegmentVector
     V
  Label = unsigned int

\******************************************************************************/

map <Label,PerceptualGroup> ImgSegmentVector::ParallelGrouping(double MaxDistance,double MaxAngle)
{
	AffGraph<pImgSegment> AffParallel;            //Undirected graph whose nodes are pointers to ImgSegments
	                                              //and edges are distances between the midpoint of the shorter
	                                              //segment and the larger segments.
	leda_node u;                                  //Auxiliar node.
	unsigned int NumGroups;                       //Number of parallel groups.
	unsigned int i = 0;                           //Index var.
	unsigned int *NumberOfSegmentsInGroup;        //Variable array to store the number of segments contained in
	                                              //each group
	LabelVector LV;
	LabelVector::const_iterator LVit;
	PerceptualGroup PG;
	map <Label,PerceptualGroup> PGMap;
	map <Label,PerceptualGroup>::iterator PGMit;
	Label l = 0;

	AffParallel = ParallelAffGraph(MaxDistance,MaxAngle);

	leda_node_array<int> compnum(AffParallel);
	
	NumGroups = COMPONENTS(AffParallel, compnum);

//	printf("NumGroups: %i\n",NumGroups);

	NumberOfSegmentsInGroup    = new unsigned int [NumGroups];

	for (i=0;i<NumGroups;i++){
		NumberOfSegmentsInGroup[i]=0;
	}

	forall_nodes(u,AffParallel) {
//		printf("compnum[u]=%i\n",compnum[u]);
		NumberOfSegmentsInGroup[compnum[u]]++;
	}

	
	for (i=0;i<NumGroups;i++){
		if (NumberOfSegmentsInGroup[i]>1){
			LV.push_back(i);
		}
	}

//	for (LVit = LV.begin(); LVit != LV.end(); LVit++){
//			printf("NumberOfSegmentsInGroup[%i]=%i\n",(*LVit),NumberOfSegmentsInGroup[(*LVit)]);
//	}


	for (LVit = LV.begin(); LVit != LV.end(); LVit++){
		PG.clear();
		forall_nodes(u,AffParallel) {
			if(compnum[u]==(*LVit)){
				PG.push_back(AffParallel[u]);
			}
		}
		PGMap[l]=PG;
		l++;
	}

//	for (PGMit = PGMap.begin(); PGMit != PGMap.end(); PGMit++)
//	{
//		printf("LabelMap: %i\n",(*PGMit).first);
//		(*PGMit).second.Show();
//	}


	delete NumberOfSegmentsInGroup;
	
	return PGMap;
}


/**ImgSegmentVector********************\
		        Show
\**************************************/
void ImgSegmentVector::Show()
{
	ImgSegmentVector::const_iterator it;
	ImgSegment S;
	for (it = begin(); it != end(); it++)
	{
		S = *it;
		S.Show();	
	}
}

/**pImgSegmentVector********************\
		   pImgSegmentVector
\**************************************/
pImgSegmentVector::pImgSegmentVector()
{

}

pImgSegmentVector::~pImgSegmentVector()
{

}

/**pImgSegmentVector********************\
		        Show
\**************************************/
void pImgSegmentVector::Show()
{
	pImgSegmentVector::iterator it;
	for (it = begin(); it != end(); it++)
	{
		(*it)->Show();
	}
}

/**pImgSegmentVector********************\
		        Serialize
\**************************************/
size_t pImgSegmentVector::Serialize(FILE * stream)
{
	size_t count  = 0;
	size_t SVsize = 0;

	SVsize = size();
	count += sizeof(size_t)*fwrite(&SVsize, sizeof(size_t),1,stream);

	pImgSegmentVector::iterator it;
	for (it = begin(); it != end(); it++)
	{
		count += (*it)->Serialize(stream);	
	}

	return count;
}

/**PerceptualGroup*********************\
		  PerceptualGroup
\**************************************/
PerceptualGroup::PerceptualGroup()
{

}

PerceptualGroup::~PerceptualGroup()
{

}


/**ImgSegmentMap***********************\
		  ImgSegmentMap
\**************************************/
ImgSegmentMap::ImgSegmentMap()
{

}

ImgSegmentMap::~ImgSegmentMap()
{

}

/**ImgSegmentMap***********************\
		         Show
\**************************************/
void ImgSegmentMap::Show()
{
	ImgSegmentMap::iterator it;
	ImgSegment SAux;
	for (it = begin(); it != end(); it++)
	{
		printf("Label: %i\n",(*it).first);
		SAux = (*it).second;
		SAux.Show();
	}
}

/**ImgSegmentMap***********************\
		       Serialize
\**************************************/
size_t ImgSegmentMap::Serialize(FILE * stream)
{
	size_t count  = 0;
	size_t SMsize = 0;

	unsigned int	ui;
	ImgSegment			s;

	SMsize = size();
	count += sizeof(size_t)*fwrite(&SMsize, sizeof(size_t),1,stream);

	ImgSegmentMap::iterator it;
	for (it = begin(); it != end(); it++)
	{
		ui = (*it).first;
		s = (*it).second;
		count += sizeof(unsigned int)   *fwrite(&ui, sizeof(unsigned int)   ,1,stream);
		count += s.Serialize(stream);
	}

	return count;
}


