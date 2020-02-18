/****
  SoftVision. Software for Computer Vision

  Gregorio Ambrosio Cestero (goyo@computer.org)
  System Engineering and Automation Department 
  University of Malaga. Spain                   

  $RCSfile: StereoImage.h,v $
  $Revision: 1.1 $
  $Date: 2000/01/21 13:05:07 $
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


// StereoImage.h: interface for the StereoImage class.
//
// (c)1998. Gregorio Ambrosio Cestero
// 
//////////////////////////////////////////////////////////////////////

#if !defined(_STEREOIMAGE_H_)
#define _STEREOIMAGE_H_

#include "Image.h"
#include "Graph.h"
#include "Tree.h"

namespace GAC
{

class MatchInfo
{
public: 
	MatchInfo();
	virtual ~MatchInfo();

	double FVDistance;
	double GCDistance;
	double BCDistance;
	double Dispj;
	double Dispi;
	int	   Polarity; // 1 positive, -1 negative, 0 uncoherent

	//Visualization
	void Show();

	//Operators
	friend bool operator== (const MatchInfo& MI1,const MatchInfo& MI2);
	friend bool operator!= (const MatchInfo& MI1,const MatchInfo& MI2);
	friend bool operator<  (const MatchInfo& MI1,const MatchInfo& MI2);

	//Operator + double necessary to use this class like a Weight type in an instance
	//of the Graph class;
	MatchInfo & operator+(double val);
};


class Match
{
public:
	//Operators
	friend bool operator== (const Match& M1,const Match& M2);
	friend bool operator!= (const Match& M1,const Match& M2);
	friend bool operator<  (const Match& M1,const Match& M2);

	//Visualization
	void Show();

public:
	Label first;		//Label del CPG de la imagen izquierda
	Label second;		//Label del CPG de la imagen derecha
	ConvexPerceptualGroup *pCPG1;
	ConvexPerceptualGroup *pCPG2;
	MatchInfo	 MI;
};

typedef vector<Match> vMatch;

class MatchVector : public vMatch
{
public:
	//Visualization
	void Show();
};


class StereoImage : public Error  
{
public:
	StereoImage();
	
//Public data
public:
	Image L;
	Image R;

//Public functions
public:
	//Load functions
	StereoImage& LoadPGM(char *LeftImageFileName,char *RightImageFileName);
	StereoImage& LoadMAT(char *LeftImageFileName,char *RightImageFileName);
	StereoImage& LoadBMP(char *LeftImageFileName,char *RightImageFileName);

	//Edge detection
	StereoImage &CannyS		(float Sigma,unsigned char LowH, unsigned char HighH);
	StereoImage &CannyW		(float W,unsigned char LowH, unsigned char HighH);
	void PostCanny();

	//Segment extraction
	StereoImage &SegmentExtractionGAC     (StructSData  SData);
	StereoImage &SegmentExtractionMerging (StructSData  SData);

	//Perceptual grouping
	StereoImage &PerceptualGrouping	    (StructPGData   PGData,
										 StructMiscData MiscData,
										 bool DetectProximity,
										 bool DetectParallelism,
										 bool DetectColinearity);
	StereoImage &ConvexPerceptualGrouping	(StructSData SData, StructPGData PGData, StructMiscData MiscData);

	//Stereo with Perceptual Grouping
	StereoImage & CPGMatching(double MaxDispi, double MaxDispj, StructMiscData MiscData);
	void ShowMatches();

	//Stereo with Correlation
	Image CorrelationStereo(size_t M,size_t N,size_t MaxDisparity,StructMiscData MiscData);

//Public data types
public:
	typedef double InterpretationCost;
	typedef map<MatchVector,InterpretationCost> InterpretationMap;

//Private data types
private:
	class LabelInfo {
	public:
		ConvexPerceptualGroup* pCPG;
		LabelVector	           Overlap;
	};
	typedef map<Label,LabelInfo> LabelCPGMap;
	typedef Graph<Label,MatchInfo> MatchGraph;
	typedef Graph<MatchGraph,Match> InterpretationGraph;
	typedef enum{left,center,right} Directions;

//Private data
private:
	MatchVector MatchCandidates;
	MatchVector MatchFinal;
	MatchInfo MIZero,MIMax; //For Graph<...,MatchInfo> declarations
//Private functions
private:
	bool GoodInitialConditions();

	//Stereo with Perceptual Grouping
	nCompVector GetFeatureVector(ConvexPerceptualGroup *pCPG);
	MatchVector StereoImage::GetMatchCandidates(Graph<Label,MatchInfo> MatchGraph,LabelCPGMap I1,LabelCPGMap I2);
	MatchVector GetMatchFinal(InterpretationMap &IM,LabelCPGMap &I1,LabelCPGMap &I2);
	Graph<Label,MatchInfo> GetCPGMatchGraph(double MaxDispi,double MaxDispj,
                                            LabelCPGMap I1,LabelCPGMap I2);
	void IGBuild(InterpretationGraph & IG,MatchGraph & MG, LabelCPGMap & I1,LabelCPGMap & I2);
	bool CPGStereoCheckPoint1(MatchInfo MI,double MaxDispi,double MaxDispj);
	bool CPGStereoCheckPoint2(MatchVector &MV,LabelCPGMap &I1,LabelCPGMap &I2,double &Cost, double MaxDispi);
	InterpretationMap GetInterpretations(MatchGraph MG,LabelCPGMap I1,LabelCPGMap I2, double MaxDispi);
	void ShowInterpretationMap(InterpretationMap &IM,LabelCPGMap &I1,LabelCPGMap &I2);
	void ComputeInterpretations(Label s,InterpretationGraph & IG,LabelCPGMap & I1,LabelCPGMap & I2,MatchVector & MV,InterpretationMap & IM, double MaxDispi);
	bool ThereIsSimilarity(double &Similarity,ConvexPerceptualGroup *pCPG1,ConvexPerceptualGroup *pCPG2);
	double ComputeSimilarity(ConvexPerceptualGroup *pCPG1,ConvexPerceptualGroup *pCPG2);
	void CPGOverlapingProcess(LabelCPGMap &I1);
	double GetInterpretationConsistency(MatchVector &MV);
	MatchVector GetTheBestInterpretation(InterpretationMap &IM);

};

} //namespace GAC

#endif // !defined(_STEREOIMAGE_H_)
