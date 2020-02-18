/****
  SoftVision. Software for Computer Vision

  Gregorio Ambrosio Cestero (goyo@computer.org)
  System Engineering and Automation Department 
  University of Malaga. Spain                   

  $RCSfile: StereoImage.cpp,v $
  $Revision: 1.1 $
  $Date: 2000/01/21 13:05:06 $
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


// StereoImage.cpp: implementation of the StereoImage class.
//
//////////////////////////////////////////////////////////////////////


#include "StereoImage.h"

namespace GAC
{

/**MatchInfo***************************************************************\
		
	                       Class MatchInfo

\**************************************************************************/


/**MatchInfo***************************\
		MatchInfo
\**************************************/
MatchInfo::MatchInfo()
{
	FVDistance = 0.0;
	GCDistance = 0.0;
	BCDistance = 0.0;
	Dispj      = 0.0;
	Dispi      = 0.0;
}

/**MatchInfo***************************\
		~MatchInfo
\**************************************/
MatchInfo::~MatchInfo()
{

}

//Visualization

/**MatchInfo***************************\
		       Show
\**************************************/
void MatchInfo::Show()
{
	printf("FVDistance: %.30g\n",FVDistance);
	printf("GCDistance: %.30g\n",GCDistance);
	printf("BCDistance: %.30g\n",BCDistance);
	printf("Dispj     : %.30g\n",Dispj);
	printf("Dispi     : %.30g\n",Dispi);
}

//Operators

/**MatchInfo***************************\
		       operator==
\**************************************/
bool operator== (const MatchInfo& MI1,const MatchInfo& MI2)
{
	return (MI1.FVDistance == MI2.FVDistance &&
			MI1.GCDistance == MI2.GCDistance &&
			MI1.BCDistance == MI2.BCDistance &&
			MI1.Dispj	   == MI2.Dispj		 &&
			MI1.Dispi      == MI2.Dispi 
		);
}

/**MatchInfo***************************\
		       operator!=
\**************************************/
bool operator!= (const MatchInfo& MI1,const MatchInfo& MI2)
{
	return (MI1.FVDistance != MI2.FVDistance &&
			MI1.GCDistance != MI2.GCDistance &&
			MI1.BCDistance != MI2.BCDistance &&
			MI1.Dispj	   != MI2.Dispj		 &&
			MI1.Dispi      != MI2.Dispi 
			);
}

/**MatchInfo***************************\
		       operator<
\**************************************/
bool operator< (const MatchInfo& MI1,const MatchInfo& MI2)
{
	if (MI1.FVDistance==MI2.FVDistance)
		return (MI1.Dispj<MI2.Dispj);
	else
		return (MI1.FVDistance<MI2.FVDistance);
}

/**MatchInfo***************************\
		       operator+
\**************************************/
MatchInfo & MatchInfo::operator+(double val)
{
	FVDistance+=val;
	return *this;
}







/**Match*******************************************************************\
		
	                       Class Match

\**************************************************************************/

//Operators
/**Match*******************************\
		       operator==
\**************************************/
bool operator== (const Match& M1,const Match& M2)
{
	return (M1.first   == M2.first	&&
			M1.second  == M2.second	&&
			M1.MI      == M2.MI 
		);
}

/**Match*******************************\
		       operator!=
\**************************************/
bool operator!=(const Match& M1,const Match& M2)
{
	return !(M1==M2);
}

/**Match*******************************\
		       operator<
\**************************************/
bool operator< (const Match& M1,const Match& M2)
{
	if (M1.MI == M2.MI) 
		return (M1.first < M2.first);
	else
		return (M1.MI < M2.MI);
}

//Visualization
/**Match*******************************\
		       Show
\**************************************/
void Match::Show()
{
	printf("(L:%i - R:%i):dispj:%4g,dispi:%4g, FVd:%.30g\n",first,second,MI.Dispj,MI.Dispi,MI.FVDistance);
}








/**MatchVector*************************************************************\
		
	                       Class MatchVector

\**************************************************************************/


/**MatchVector*************************\
		       Show
\**************************************/
void MatchVector::Show()
{
	Match M;
	MatchVector::const_iterator it;

	for (it = begin(); it != end(); it++)
	{
		M = *it;
		M.Show();	
	}
	printf("\n");
}









/**StereoImage*************************************************************\
		
  	  
		                    Class StereoImage


\**************************************************************************/



/**StereoImage*************************\
		StereoImage
\**************************************/
StereoImage::StereoImage() 
{
	MIZero.FVDistance = 0.0;
	MIZero.GCDistance = 0.0;
	MIZero.BCDistance = 0.0;
	MIZero.Dispj      = 0.0;
	MIZero.Dispi      = 0.0;

	MIMax.FVDistance = DBL_MAX;
	MIMax.GCDistance = DBL_MAX;
	MIMax.BCDistance = DBL_MAX;
	MIMax.Dispj      = DBL_MAX;
	MIMax.Dispi      = DBL_MAX;

	insert(Error::value_type(0,"No error"));
	insert(Error::value_type(1,"Dimensions must be agree"));
}


/**StereoImage*************************\
		GoodInitialConditions
\**************************************/
bool StereoImage::GoodInitialConditions(){
	if (L.Retina.Depth() != R.Retina.Depth() || 
		L.Retina.Width() != R.Retina.Width()    ){
		SetErrorCode(1);
		return false;
	}

	SetErrorCode(0);
	return true;
}

/**StereoImage*************************\
		       LoadPGM
\**************************************/
StereoImage & StereoImage::LoadPGM(char *LeftImageFileName,char *RightImageFileName)
{
	L.LoadPGM(LeftImageFileName);
	R.LoadPGM(RightImageFileName);
	return *this;
}

/**StereoImage*************************\
		       LoadMAT
\**************************************/
StereoImage & StereoImage::LoadMAT(char *LeftImageFileName,char *RightImageFileName)
{
	L.LoadMAT(LeftImageFileName);
	R.LoadMAT(RightImageFileName);
	return *this;
}

/**StereoImage*************************\
		       LoadBMP
\**************************************/
StereoImage & StereoImage::LoadBMP(char *LeftImageFileName,char *RightImageFileName)
{
	L.LoadBMP(LeftImageFileName);
	R.LoadBMP(RightImageFileName);
	return *this;
}

/**StereoImage*************************\
		       CannyS
\**************************************/
StereoImage & StereoImage::CannyS (float Sigma,unsigned char LowH, unsigned char HighH)
{
	if (GoodInitialConditions()){
		L.CannyS(Sigma,LowH,HighH);
		R.CannyS(Sigma,LowH,HighH);
	}
	return *this;
}

/**StereoImage*************************\
		       CannyW
\**************************************/
StereoImage &StereoImage::CannyW (float W,unsigned char LowH, unsigned char HighH)
{
	if (GoodInitialConditions()){
		L.CannyW(W,LowH,HighH);
		R.CannyW(W,LowH,HighH);
	}
	return *this;
}

/**StereoImage*************************\
		       PostCanny
\**************************************/
void StereoImage::PostCanny()
{
	if (GoodInitialConditions()){
		L.PostCanny();
		R.PostCanny();
	}
}

/**StereoImage*************************\
		 SegmentExtractionGAC
\**************************************/
StereoImage & StereoImage::SegmentExtractionGAC (StructSData  SData)
{
	if (GoodInitialConditions()){
		L.SegmentExtractionGAC(SData);
		R.SegmentExtractionGAC(SData);
	}
	return *this;
}

/**StereoImage*************************\
	   SegmentExtractionMerging
\**************************************/
StereoImage & StereoImage::SegmentExtractionMerging (StructSData  SData)
{
	if (GoodInitialConditions()){
		L.SegmentExtractionMerging(SData);
		R.SegmentExtractionMerging(SData);
	}
	return *this;
}

/**StereoImage*************************\
	       PerceptualGrouping
\**************************************/
StereoImage & StereoImage::PerceptualGrouping	(StructPGData   PGData,
												 StructMiscData MiscData,
												 bool DetectProximity,
												 bool DetectParallelism,
												 bool DetectColinearity)
{
	if (GoodInitialConditions()){
		L.PerceptualGrouping(PGData,MiscData,DetectProximity,DetectParallelism,DetectColinearity);
		R.PerceptualGrouping(PGData,MiscData,DetectProximity,DetectParallelism,DetectColinearity);
	}
	return *this;
}

/**StereoImage*************************\
	     ConvexPerceptualGrouping
\**************************************/
StereoImage & StereoImage::ConvexPerceptualGrouping	(StructSData SData, StructPGData PGData, StructMiscData MiscData)
{
	if (GoodInitialConditions()){
		L.ConvexPerceptualGrouping(SData,PGData,MiscData);
		R.ConvexPerceptualGrouping(SData,PGData,MiscData);
	}
	return *this;
}

/**StereoImage*************************\
		CPGMatching
\**************************************/
StereoImage & StereoImage::CPGMatching(double MaxDispi, double MaxDispj, StructMiscData MiscData)
{
	LabelCPGMap LabelCPGM_L,LabelCPGM_R;
	LabelCPGMap::iterator LabelCPGMit,LabelCPGM_Lit,LabelCPGM_Rit;
	ConvexPerceptualGroupMap::iterator CPGMit;
	Point Centroid1,Centroid2;
	Label AuxLabel;
	InterpretationMap InterpretationMapLR, FinalInterpretationMap;
	MatchGraph MatchGraphLR(true,MIMax,MIZero),MatchSubGraph(true,MIMax,MIZero);
	vector<MatchGraph> MGV;
	vector<MatchGraph>::iterator MGVit;
	MatchVector BestInterpretation;

	//Building of tables indexing the CPG's Label with a pointer to the CPG
	AuxLabel = 0;
	for (CPGMit  = L.ConvexPerceptualGroupRetina.begin();
		 CPGMit != L.ConvexPerceptualGroupRetina.end();
		 CPGMit++)
		if (!(*CPGMit).second.GetChildren().size()){
			AuxLabel++;
			LabelCPGM_L[AuxLabel].pCPG = &((*CPGMit).second);
		}
	for (CPGMit  = R.ConvexPerceptualGroupRetina.begin();
		 CPGMit != R.ConvexPerceptualGroupRetina.end();
		 CPGMit++)
		if (!(*CPGMit).second.GetChildren().size()){
			AuxLabel++;
			LabelCPGM_R[AuxLabel].pCPG = &((*CPGMit).second);
		}

	CPGOverlapingProcess(LabelCPGM_L);
	CPGOverlapingProcess(LabelCPGM_R);
	MatchGraphLR = GetCPGMatchGraph(MaxDispi,MaxDispj,LabelCPGM_L,LabelCPGM_R);

//MatchGraphLR.ShowAdjacencyList();
	MatchCandidates = GetMatchCandidates(MatchGraphLR,LabelCPGM_L,LabelCPGM_R);
	MatchGraphLR.RemoveIsolatedVertexes();	
//MatchCandidates.Show();
//MatchGraphLR.ShowAdjacencyList();

	//Divide and conquer principle. I divide the problem in subproblems.
	MatchGraphLR.Subgraphs(MGV);

	for (MGVit = MGV.begin();MGVit != MGV.end();MGVit++){
		MatchSubGraph = (*MGVit);
		InterpretationMapLR = GetInterpretations(MatchSubGraph,LabelCPGM_L,LabelCPGM_R,MaxDispi);
//MatchSubGraph.ShowAdjacencyList();
		BestInterpretation = GetTheBestInterpretation(InterpretationMapLR);
		FinalInterpretationMap[BestInterpretation] = GetInterpretationConsistency(BestInterpretation);
//ShowInterpretationMap(InterpretationMapLR,LabelCPGM_L,LabelCPGM_R);
	}
	MatchFinal = GetMatchFinal(FinalInterpretationMap,LabelCPGM_L,LabelCPGM_R);
	ShowInterpretationMap(FinalInterpretationMap,LabelCPGM_L,LabelCPGM_R);		
	
	return *this;

}


/**StereoImage*************************\
		CPGOverlapingProcess
\**************************************/
void StereoImage::CPGOverlapingProcess(LabelCPGMap &I1)
{
	LabelCPGMap::iterator I1it,I2it;
	LabelCPGMap I2;
	Point Centroid1,Centroid2;
	LabelVector Overlap;
	LabelVector::const_iterator LVit;
	double MaxSalience,Similarity;
	Label CPGwithMaxSalience;
	
	//Building of overlapping vectors
	while (I1.size()>0){
		I1it = I1.begin();
		Overlap.clear();
		Overlap.push_back((*I1it).first);
		Centroid1 = (*I1it).second.pCPG->GetBinCentroid();
		for (I2it = I1.begin();I2it != I1.end();I2it++){
			if (I1it != I2it){
				Centroid2 = (*I2it).second.pCPG->GetBinCentroid();
				if ((*I2it).second.pCPG->Inside(Centroid1)   &&
					(*I1it).second.pCPG->Inside(Centroid2) )
					if (ThereIsSimilarity(Similarity,(*I1it).second.pCPG,(*I2it).second.pCPG))
						Overlap.push_back((*I2it).first);
			}
		}
		MaxSalience=0.0;
		for (LVit = Overlap.begin();LVit != Overlap.end();LVit++){
			if (I1[*LVit].pCPG->GetSalience()>MaxSalience){
				MaxSalience = I1[*LVit].pCPG->GetSalience();
                CPGwithMaxSalience = *LVit;
			}
		}
		I2[CPGwithMaxSalience] = I1[CPGwithMaxSalience];
		I2[CPGwithMaxSalience].Overlap.push_back(CPGwithMaxSalience);
		for (LVit = Overlap.begin();LVit != Overlap.end();LVit++){
			if (I1.find(*LVit)!=I1.end())
				I1.erase(*LVit); //if ((*LVit)!=CPGwithMaxSalience) I1.erase(*LVit);
		}
	}
//Overlap.Show();
	I1 = I2;
//	for (I1it = I1.begin();I1it != I1.end();I1it++){
//		printf ("Overlap:%i(%i) ",(*I1it).first,(*I1it).second.pCPG->Label);
//		(*I1it).second.Overlap.Show();
//	}

}

/**StereoImage*************************\
		ThereIsSimilarity
\**************************************/

bool StereoImage::ThereIsSimilarity(double &Similarity, ConvexPerceptualGroup *pCPG1,ConvexPerceptualGroup *pCPG2)
{
	Similarity = ComputeSimilarity(pCPG1,pCPG2);
	return true;
//	return (abs(pCPG1->Getcm00()-pCPG2->Getcm00()) < pCPG1->Getcm00()*0.1);
//	return (Similarity < abs(pCPG1->Getncm30()*0.5));
}

/**StereoImage*************************\
		ComputeSimilarity
\**************************************/

double StereoImage::ComputeSimilarity(ConvexPerceptualGroup *pCPG1,ConvexPerceptualGroup *pCPG2)
{
	nCompVector FV1,FV2;
	double Similarity;

	//This the key function (with GetFeatureVector) of the algortihm 
	//since it's compute the similarity between CPGs.

	//Using Euclidean Distance
	FV1 = GetFeatureVector(pCPG1);
	FV2 = GetFeatureVector(pCPG2);
	Similarity = FV2.EuclideanDistance(FV1);

//	Similarity = abs(abs(pCPG1->Getcm30()/pCPG1->Getcm00()-(pCPG2->Getncm30()));

	return Similarity;
}


/**StereoImage*************************\
		GetCPGMatchGraph
\**************************************/
Graph<Label,MatchInfo> StereoImage::GetCPGMatchGraph(double MaxDispi,double MaxDispj,LabelCPGMap I1,LabelCPGMap I2)
{
	LabelCPGMap::iterator I1it,I2it;
	MatchInfo MI;
	nCompVector FV1,FV2;
	Point BinCentroid1, BinCentroid2, GrayCentroid1, GrayCentroid2;

	//Declaration of a directed graph with the Max and Zero possible values of weights
	MatchGraph G(true,MIMax,MIZero);

	//Initialization of the Graph introducing Vertexes
	for (I1it = I1.begin();I1it != I1.end();I1it++){
		G.AddVertex(Vertex<Label>((*I1it).first,(*I1it).second.pCPG->Label));
	}
	for (I2it = I2.begin();I2it != I2.end();I2it++){
		G.AddVertex(Vertex<Label>((*I2it).first,(*I2it).second.pCPG->Label));
	}

	//Setting edges
	for (I1it = I1.begin();I1it != I1.end();I1it++){
		for (I2it = I2.begin();I2it != I2.end();I2it++){
			BinCentroid1 = (*I1it).second.pCPG->GetBinCentroid();
			BinCentroid2 = (*I2it).second.pCPG->GetBinCentroid();
			MI.Dispj = BinCentroid2.j - BinCentroid1.j;
			MI.Dispi = BinCentroid2.i - BinCentroid1.i;	
			//We admit a possible Match only when:
			if (CPGStereoCheckPoint1(MI,MaxDispi,MaxDispj)){
				if (ThereIsSimilarity(MI.FVDistance,(*I1it).second.pCPG,(*I2it).second.pCPG)){
					//Getting feature vectors
					GrayCentroid1 = (*I1it).second.pCPG->GetGrayCentroid();
					GrayCentroid2 = (*I2it).second.pCPG->GetGrayCentroid();
					MI.BCDistance = BinCentroid2.Distance(BinCentroid1);
					MI.GCDistance = GrayCentroid2.Distance(GrayCentroid1);
					G.AddEdge((*I1it).first,(*I2it).first,MI);
				}
			}
//			else {
//				printf("Rechazado el %i,%i\n",(*I1it).first,(*I2it).first);
//			}

		}
	}
	return G;
}

/**StereoImage*************************\
		CPGStereoCheckPoint1
\**************************************/
bool StereoImage::CPGStereoCheckPoint1(MatchInfo MI,double MaxDispi,double MaxDispj)
{
	bool CheckPoint = true;
	// CheckPoint is true if:
	//  if the left CPG is inside the epipolar window.

	//- The horizontal disparity is negative
	CheckPoint = CheckPoint && (MI.Dispj <= 0.0);
	//- The horizontal disparity is inside established threshold
	CheckPoint = CheckPoint && (abs(MI.Dispj) <= MaxDispj);
	//- The vertical disparity is inside established threshold
	CheckPoint = CheckPoint && (abs(MI.Dispi) <= MaxDispi);

	return CheckPoint;
}

/**StereoImage*************************\
		GetInterpretations
\**************************************/
StereoImage::InterpretationMap StereoImage::GetInterpretations(MatchGraph MG, LabelCPGMap I1,LabelCPGMap I2,double MaxDispi)
{
	InterpretationGraph IG12;
	InterpretationMap IM;
	MatchVector MV;
	MatchGraph EmptyMatchGraph(true,MIMax,MIZero);

//MG.ShowAdjacencyList();
	IG12.Clear();
	IG12.AddVertex(Vertex<MatchGraph>(1,MG));
	IG12.AddVertex(Vertex<MatchGraph>(2,EmptyMatchGraph));

	IGBuild(IG12,MG,I1,I2);
//IG12.ShowAdjacencyList();
	IM.clear();
	ComputeInterpretations(1,IG12,I1,I2,MV,IM,MaxDispi);

	return IM;
}

/**StereoImage*************************\
		IGBuild
\**************************************/
void StereoImage::IGBuild(InterpretationGraph & IG,MatchGraph & MG, LabelCPGMap & I1,LabelCPGMap & I2)
{
	LabelCPGMap::const_iterator I1it,I2it;

	MatchGraph::VertexEdgeMMap::iterator      VEMMit;
	MatchGraph::VertexEdgeVertexMap::iterator VEVMit;
	MatchGraph::VertexEdgeMMap VEMM;
	MatchGraph::VertexEdgeVertexMap MGAdjacencyList;
	MatchGraph SubMG;
	Label IGu,IGv,MGu,MGv;
	Match M,Maux;
	Label Fu;
	LabelVector FuOverlap;
	LabelVector::iterator LVit;

	MGAdjacencyList = MG.GetAdjacencyList();

	VEVMit = MGAdjacencyList.begin();
	Fu     = (*VEVMit).first;
	FuOverlap = I1[Fu].Overlap;

	for (VEVMit=MGAdjacencyList.begin();VEVMit!=MGAdjacencyList.end();VEVMit++){
		MGu   = (*VEVMit).first;
		VEMM  = (*VEVMit).second;

		//In this level I only consider overlapped CPGs which can originate others
		//interpretations.
		for (LVit=FuOverlap.begin();LVit!=FuOverlap.end();LVit++)
			if(MGu==(*LVit)) break;
		if (LVit != FuOverlap.end()) 
			for (VEMMit=VEMM.begin();VEMMit!=VEMM.end();VEMMit++){
				MGv = (*VEMMit).first;
				//w = (*VEMMit).second;
//printf("(u,v):%i,%i\n",MGu,MGv);
					SubMG = MG;
					SubMG.RemoveVertex(MGu);
					SubMG.RemoveVertex(MGv);
					//Uniqueness constraint
					SubMG.RemoveVertex(I1[MGu].Overlap);
					SubMG.RemoveVertex(I2[MGv].Overlap);

					SubMG.RemoveIsolatedVertexes();
					if (!IG.GetVertex(MG,IGu)){
						IGu = IG.Size().first+1;
						IG.AddVertex(Vertex<MatchGraph>(IGu,MG));
					}
					if (!IG.GetVertex(SubMG,IGv)){
						IGv = IG.Size().first+1;
						IG.AddVertex(Vertex<MatchGraph>(IGv,SubMG));
//printf(">>>>>>>>>>>>>>>>>>>>>>>>>>>\n");
//printf("Graph:%i\n",IGv);
//SubMG.ShowAdjacencyList();
//printf("<<<<<<<<<<<<<<<<<<<<<<<<<<<\n");
					}
					M.first  = MGu;
					M.second = MGv;
					M.pCPG1  = I1[MGu].pCPG;
					M.pCPG2  = I2[MGv].pCPG;
					MG.GetWeight(MGu,MGv,M.MI);
					//Minimization of the edge's weight (we are choosing the best match)
					if (IG.GetWeight(IGu,IGv,Maux)){
						if (M < Maux) {
							IG.RemoveEdge(IGu,IGv);
							IG.AddEdge(IGu,IGv,M);
						}
					}
					else 
						IG.AddEdge(IGu,IGv,M);

					IGBuild(IG,SubMG,I1,I2);
			}
	}
}


/**StereoImage*************************\
		ComputeInterpretations
\**************************************/
void StereoImage::ComputeInterpretations(Label s, InterpretationGraph & IG,LabelCPGMap & I1,LabelCPGMap & I2,MatchVector & MV,InterpretationMap & IM,double MaxDispi)
{
	Match M,Maux;
	MatchVector MVAux;
	double Cost;
	LabelVector Children;
	LabelVector::const_iterator LVit;

	Children = IG.GetChildren(s);
	for (LVit=Children.begin();LVit!=Children.end();LVit++){
		IG.GetWeight(s,(*LVit),M);
		MV.push_back(M); //Add Match to the current interpretation
		ComputeInterpretations((*LVit),IG,I1,I2,MV,IM,MaxDispi);
		MV.pop_back();
	}

	//If the interpretation is complete (we are at the graph's end) we push it in the
	//interpretation map IM. Due to characteristics of the map template we have only one 
	//instantiation of the interpretation.
	if (Children.size() == 0) {
		MVAux = MV;
		if (CPGStereoCheckPoint2(MVAux,I1,I2,Cost,MaxDispi)){
			Cost = GetInterpretationConsistency(MVAux);
			IM.insert(InterpretationMap::value_type(MVAux,Cost));
		}
	}
}

/**StereoImage*************************\
		CPGStereoCheckPoint2
\**************************************/
bool OnTheLeft(Match M1,Match M2)
{
	Point P1,P2;
	P1 = M1.pCPG1->GetBinCentroid();
	P2 = M2.pCPG1->GetBinCentroid();

	return P1.j < P2.j;
}
bool StereoImage::CPGStereoCheckPoint2(MatchVector &MV,LabelCPGMap &I1,LabelCPGMap &I2,double &Cost,double MaxDispi)
{
	//- Ordering constraint
	//- We compute the total cost of the Interpretation

	bool CheckPoint = true;
	MatchVector MV1,MV2,MVaux;
	MatchVector::const_iterator MV1it,MV2it;
	Directions Order1,Order2;
	Match M,M1,Mold;
	Point Centroid1, Centroid2, Centroid1old, Centroid2old;

	MV1 = MV;
	MV.clear();

	while (MV1.size()!=0){
		//For each match ...
		MV1it=MV1.begin();
		M = (*MV1it);
		MV2.clear();
		MVaux.clear();
		//I obtain the others matchs produced in the same epipolar line (window)
		for (MV1it=MV1.begin();MV1it != MV1.end();MV1it++){
			M1= (*MV1it);
			if ((M1.pCPG1->GetBinCentroid().i - M.pCPG1->GetBinCentroid().i) <= abs(MaxDispi))
				MV2.push_back(M1);
			else
				MVaux.push_back(M1);
		}

		//I subtract those matchs from the original set.
		//set_difference(MV1.begin(),MV1.end(),MV2.begin(),MV2.end(),MVaux.begin()); //Compiler bug: this function doesn't work properly with vectors with different sizes
		MV1 = MVaux;

		//With those matchs I check the ordering constraint.
		//I order matchs respect the Left Image's CPGs in order to check if the ordering
		//constraint is satisfied.
		sort(MV2.begin(),MV2.end(),OnTheLeft); 

		Cost = 0.0;
		MV2it = MV2.begin();
		Mold = (*MV2it);
		Cost = Mold.MI.FVDistance;

		for (;MV2it != MV2.end();MV2it++){
			M = (*MV2it);
			Cost += M.MI.FVDistance;

			Centroid1old = I1[Mold.first ].pCPG->GetBinCentroid();
			Centroid2old = I2[Mold.second].pCPG->GetBinCentroid();
			Centroid1    = I1[M.first    ].pCPG->GetBinCentroid();
			Centroid2    = I2[M.second   ].pCPG->GetBinCentroid();

			if      ((Centroid1.j-Centroid1old.j) >  0) Order1 = right;
			else if ((Centroid1.j-Centroid1old.j) <  0) Order1 = left;
			else if ((Centroid1.j-Centroid1old.j) == 0) Order1 = center;

			if      ((Centroid2.j-Centroid2old.j) >  0) Order2 = right;
			else if ((Centroid2.j-Centroid2old.j) <  0) Order2 = left;
			else if ((Centroid2.j-Centroid2old.j) == 0) Order2 = center;

			if ((Order1==right && Order2==left ) ||
				(Order1==left  && Order2==right) ){
				return false;
			}
			Mold  = M;

		}
		MV.insert(MV.end(),MV2.begin(),MV2.end());
	}

	return true;
}

/**StereoImage*************************\
		GetTheBestInterpretation
\**************************************/
MatchVector StereoImage::GetTheBestInterpretation(InterpretationMap &IM)
{
	InterpretationMap IMaux;
	InterpretationMap::iterator IMit;
	MatchVector MV,MVaux;
	double InterpretationCost,InterpretationCostAux;
	
	IMit = IM.begin();
	MV                 = (*IMit).first;
	InterpretationCost = (*IMit).second;

	for (;IMit != IM.end();IMit++){
		MVaux = (*IMit).first;
		InterpretationCostAux = GetInterpretationConsistency(MVaux);
		if (MVaux.size()>MV.size()){
			MV                 = MVaux;
			InterpretationCost = InterpretationCostAux;
		}
		else 
			if (MVaux.size()==MV.size())
				if(InterpretationCostAux < InterpretationCost){
					MV                 = MVaux;
					InterpretationCost = InterpretationCostAux;
				}
	}
	return MV;
}

/**StereoImage*************************\
		GetInterpretationConsistency
\**************************************/
double StereoImage::GetInterpretationConsistency(MatchVector &MV)
{
	double InterpretationConsistency;
	double InterpretationCost;

	MatchVector::const_iterator MVit;

	InterpretationCost = 0.0;

	for (MVit = MV.begin();MVit != MV.end();MVit++){
		InterpretationCost +=(*MVit).MI.FVDistance;
	}		
	InterpretationConsistency = InterpretationCost/MV.size();

	return InterpretationConsistency;
}


/**StereoImage*************************\
		GetFeatureVector
\**************************************/
nCompVector StereoImage::GetFeatureVector(ConvexPerceptualGroup *pCPG){
	nCompVector FV;

	//FV.push_back(Area);
	//FV.push_back(Perimeter);
	//FV.push_back(BinCentroid.i);
	//FV.push_back(BinCentroid.j);
	//FV.push_back(GrayCentroid.i);
	//FV.push_back(GrayCentroid.j);

//	FV.push_back(pCPG->Getcm00());
//	FV.push_back(pCPG->Getcm01());
//	FV.push_back(pCPG->Getcm10());
//	FV.push_back(pCPG->Getcm02());
//	FV.push_back(pCPG->Getcm11());
	FV.push_back(pCPG->Getcm20());
//	FV.push_back(pCPG->Getcm03());
//	FV.push_back(pCPG->Getcm12());
//	FV.push_back(pCPG->Getcm21());
	FV.push_back(pCPG->Getcm30());


//	FV.push_back(pCPG->Getncm02());
//	FV.push_back(pCPG->Getncm11());
	FV.push_back(pCPG->Getncm20());
//	FV.push_back(pCPG->Getncm03());
//	FV.push_back(pCPG->Getncm12());
//	FV.push_back(pCPG->Getncm21());
	FV.push_back(pCPG->Getncm30());

	return FV;
}


/**StereoImage*************************\
		GetMatchCandidates
\**************************************/
MatchVector StereoImage::GetMatchCandidates(Graph<Label,MatchInfo> MatchGraph,LabelCPGMap I1,LabelCPGMap I2)
{
	LabelCPGMap::iterator I1it,I2it;
	MatchVector MatchCandidates;
	Match       M;
	MatchInfo   MI;

	MatchCandidates.clear();
	for (I1it = I1.begin();I1it != I1.end();I1it++){
		for (I2it = I2.begin();I2it != I2.end();I2it++){
			if (MatchGraph.GetWeight((*I1it).first,(*I2it).first,MI)){
				M.first		= (*I1it).second.pCPG->Label;
				M.second	= (*I2it).second.pCPG->Label;
				M.MI		= MI;
				MatchCandidates.push_back(M);
			}
		}
	}
	return MatchCandidates;
}

/**StereoImage*************************\
		GetMatchFinal
\**************************************/
MatchVector StereoImage::GetMatchFinal(InterpretationMap &IM,LabelCPGMap &I1,LabelCPGMap &I2)
{
	InterpretationMap::iterator IMit;
	MatchVector MV,MVaux,MatchFinal;
	MatchVector::const_iterator MVit;
	Match M;
	double InterpretationCost;

	MatchFinal.clear();
	for (IMit = IM.begin();IMit != IM.end();IMit++){
		MV = (*IMit).first;
		InterpretationCost = (*IMit).second;
		for (MVit = MV.begin();MVit != MV.end();MVit++){
			M = (*MVit);
			M.first  =  I1[M.first ].pCPG->Label;//M.first;
			M.second =  I2[M.second].pCPG->Label;//M.second;
			MatchFinal.push_back(M);
		}
	}
	return MatchFinal;
}

/**StereoImage*************************\
		ShowMatches
\**************************************/
void StereoImage::ShowMatches()
{
	printf("==================\n");
	printf("Candidates matches\n");
	printf("==================\n");
	MatchCandidates.Show();
	printf("=============\n");
	printf("Final matches\n");
	printf("=============\n");
	MatchFinal.Show();
}

/**StereoImage*************************\
		ShowInterpretationMap
\**************************************/
void StereoImage::ShowInterpretationMap(InterpretationMap &IM,LabelCPGMap &I1,LabelCPGMap &I2)
{
	InterpretationMap::iterator IMit;
	MatchVector MV,MVaux;
	MatchVector::const_iterator MVit;
	Match M;
	double InterpretationCost;

	printf("Visualization of the Interpretation Map\n");
	printf("%i subproblems:\n\n",IM.size());

	for (IMit = IM.begin();IMit != IM.end();IMit++){
		MV = (*IMit).first;
		InterpretationCost = (*IMit).second;
		MVaux.clear();
		for (MVit = MV.begin();MVit != MV.end();MVit++){
			M = (*MVit);
			M.first  =  I1[M.first ].pCPG->Label;//M.first;
			M.second =  I2[M.second].pCPG->Label;//M.second;
			MVaux.push_back(M);
		}
		printf("Total Cost: %.30g\n", InterpretationCost);
		MVaux.Show();
	}
}

/**StereoImage*************************\
		CorrelationStereo
\**************************************/
Image StereoImage::CorrelationStereo(size_t M, size_t N,size_t MaxDisparity,StructMiscData MiscData)
{

	Image DisparityImage;
	DoubleMatrix CwL,CwR;
	DoubleMatrix LMeanMatrix,LStdMatrix,RMeanMatrix,RStdMatrix;
	size_t NumRows,NumCols;
	size_t i1,j1,j2;
	size_t ja,jb,ia,ib;
	int j2a;
	double Correlation,NewCorrelation;
	double K,BlockSize;
	size_t Disparity;

	NumRows = L.Retina.Depth();
	NumCols = L.Retina.Width();

	DisparityImage.Retina.Resize(NumRows,NumCols);
	LMeanMatrix.Resize(NumRows,NumCols);
	LStdMatrix.Resize(NumRows,NumCols);
	RMeanMatrix.Resize(NumRows,NumCols);
	RStdMatrix.Resize(NumRows,NumCols);

	CwL.Resize(2*M+1,2*N+1);
	CwR.Resize(2*M+1,2*N+1);

	ja = N;
	jb = NumCols - N;
	ia = M;
	ib = NumRows - M;

	BlockSize = (2*M+1)*(2*N+1);

	if (MiscData.TraceMessages)	printf("Precomputing data... ");

	for (i1=0;i1<NumRows;i1++){
//printf("%i\b",i1);
//printf("(i):%i \n",i1);
		for (j1=0;j1<NumCols;j1++){
//printf("(i,j):%i,%i \n",i1,j1);
			CwL = L.Retina.GetCenteredBlock(i1,j1,M,N);
			CwR = R.Retina.GetCenteredBlock(i1,j1,M,N);
			LMeanMatrix[i1][j1] = CwL.Mean();
			RMeanMatrix[i1][j1] = CwR.Mean();
			LStdMatrix[i1][j1] = CwL.Std();
			RStdMatrix[i1][j1] = CwR.Std();
		}
	}

	if (MiscData.TraceMessages)	printf("Ok !!!\n");

	for (i1=ia;i1<=ib;i1++){
		if (MiscData.TraceMessages)	printf("Computing row:%4i\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b",i1);
//		if (MiscData.TraceMessages)	printf("Computing row:%4i\n",i1);
		for (j1=ja;j1<=jb;j1++){
//printf("(i,j):%i,%i \n",i1,j1);
			CwL = L.Retina.GetCenteredBlock(i1,j1,M,N);
			Correlation = 0.0;
			Disparity   = 0;
			j2a=j1-MaxDisparity;
			if (j2a<0) j2a=ja;
			for (j2=j2a;j2<=j1;j2++){
				CwR = R.Retina.GetCenteredBlock(i1,j2,M,N);
				//Computing of NewCorrelation
				K = BlockSize * LStdMatrix[i1][j1] * RStdMatrix[i1][j2];
				NewCorrelation = ((CwL-LMeanMatrix[i1][j1]).Mult(CwR-RMeanMatrix[i1][j2])).Sum();
				NewCorrelation /= K;

				if (NewCorrelation >= Correlation){
					Correlation = NewCorrelation;
					Disparity = ((double)(j1-j2)*255.0/(double)MaxDisparity);
				}
			}
			DisparityImage.Retina[i1][j1]=abs(Disparity);
		}
	}

	return DisparityImage;


/*
	//Another way to do the same less optimal
	Image DisparityImage;
	DoubleMatrix CwL,CwR;
	size_t NumRows,NumCols;
	size_t i1,j1,i2,j2;
	size_t ja,jb,ia,ib;
	int j2a;
	double Correlation,NewCorrelation;
	size_t Disparity;

	NumRows = L.Retina.Depth();
	NumCols = L.Retina.Width();

	DisparityImage.Retina.Resize(NumRows,NumCols);

	ja = N;
	jb = NumCols - N;
	ia = M;
	ib = NumRows - M;

	CwL.Resize(2*M+1,2*N+1);
	CwR.Resize(2*M+1,2*N+1);

	for (i1=ia;i1<=ib;i1++){
printf("(i):%i \n",i1);
		for (j1=ja;j1<=jb;j1++){
//printf("(i,j):%i,%i \n",i1,j1);
			CwL = L.Retina.GetCenteredBlock(i1,j1,M,N);
			Correlation = 0.0;
			Disparity   = 0;
			j2a=j1-MaxDisparity;
			if (j2a<0) j2a=ja;

			for (j2=j2a;j2<=j1;j2++){
				CwR = R.Retina.GetCenteredBlock(i1,j2,M,N);
				NewCorrelation = CwL.Corr(CwR);
				if (NewCorrelation >= Correlation){
					Correlation = NewCorrelation;
					Disparity = j2-j1;
				}
			}
			DisparityImage.Retina[i1][j1]=abs(Disparity);
		}
	}
	return DisparityImage;
*/

}

} //namespace GAC

