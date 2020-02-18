/****
  SoftVision. Software for Computer Vision

  Gregorio Ambrosio Cestero (goyo@computer.org)
  System Engineering and Automation Department 
  University of Malaga. Spain                   

  $RCSfile$
  $Revision$
  $Date$
  $Name$

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


#include "gacmex.h"
#include "ImgSegment.h"

/**************************************\
		GetPGMatrix
\**************************************/
DoubleMatrix GetPGMatrix(map<Label,PerceptualGroup> PGMap, unsigned int NumOfSegments){

	map<Label,PerceptualGroup>::iterator PGMit;
	PerceptualGroup::iterator PGit;
	
	size_t NumOfPGs;
	DoubleMatrix PGMatrix;

	NumOfPGs = PGMap.size();
	PGMatrix.Resize(NumOfPGs,NumOfSegments);

	for (PGMit = PGMap.begin(); PGMit != PGMap.end(); PGMit++)
	{
//		printf("LabelMap: %i\n",(*PGMit).first);
//		(*PGMit).second.Show();
		for (PGit = (*PGMit).second.begin(); PGit != (*PGMit).second.end(); PGit++){
			PGMatrix[(*PGMit).first][(*PGit)->Label-1]=1;
		}
	}

	return PGMatrix;
}



void
mexFunction(int nlhs,mxArray *plhs[],int nrhs,const mxArray *prhs[])
{
	mxArray  *mxM;
	size_t	  mxNumRows, mxNumCols;
	int nrows,ncols;

	DoubleMatrix SegmentsMatrix,AdjacencyMatrix;
	ImgSegment S;
	ImgSegmentVector SV;
	DoubleMatrix PGMatrix;
	double MaxDistance,MaxAngle;
	map<Label,PerceptualGroup> PGMap;
	map<Label,PerceptualGroup>::iterator PGMit;

	size_t i;

	/* check for proper number of arguments */
	if(nrhs==0) {
		mexPrintf("===============================================\n");
		mexPrintf("g_ppg.dll (c)2000 G.A.C. $Revision$\n");
		mexPrintf("$Date$\n");
		mexPrintf("$Name$\n");
		mexPrintf("Gregorio Ambrosio Cestero\n");
		mexPrintf("University of Malaga\n");
		mexPrintf("Department of System Engineering and Automation\n");
		mexPrintf("Email: goyo@computer.org\n");
		mexPrintf("================================================\n");
		mexPrintf("Build: %s\n",__TIMESTAMP__);
		mexPrintf("================================================\n");
		mexErrMsgTxt("Three input required.");
	} else if(nrhs!=3) {
		mexErrMsgTxt("Three input required.");
	} else if(nlhs!=1) {
		mexErrMsgTxt("One output required.");
	}

	//Control the correctness of input arguments
	if( !mxIsNumeric (prhs[0])    || 
		!mxIsDouble  (prhs[0])    ||
		 mxIsEmpty   (prhs[0])    ||
		 mxIsComplex (prhs[0])    ){
		mexErrMsgTxt("The segment matrix has the incorrect format");
	}

	for (i=1;i<=2;i++){
		nrows = mxGetM(prhs[i]);
		ncols = mxGetN(prhs[i]);
		if( !mxIsNumeric(prhs[i]) || !mxIsDouble (prhs[i]) ||
			 mxIsEmpty  (prhs[i]) ||  mxIsComplex(prhs[i]) ||
			!(nrows==1 && ncols==1) ) {
		mexPrintf("Input #%i error\n",i);
		mexErrMsgTxt("Input must be a scalar.");
		}
	}

	MaxDistance	= *mxGetPr(prhs[1]);
	MaxAngle	= *mxGetPr(prhs[2]);

	//Process
	mxArray2DoubleMatrix(prhs[0],SegmentsMatrix);
	for (i=0;i<SegmentsMatrix.Depth();i++){
		S=ImgSegment(SegmentsMatrix[i][1],
			      SegmentsMatrix[i][2],
				  SegmentsMatrix[i][3],
				  SegmentsMatrix[i][4]);
		S.Label = SegmentsMatrix[i][0];
		SV.push_back(S);
	}

	PGMap = SV.ParallelGrouping(MaxDistance,MaxAngle*ONE_GRADE_IN_RAD);

//	for (PGMit = PGMap.begin(); PGMit != PGMap.end(); PGMit++)
//	{
//		printf("LabelMap: %i\n",(*PGMit).first);
//		(*PGMit).second.Show();
//	}

	PGMatrix = GetPGMatrix(PGMap,SV.size());

	//Passing to output vars
	DoubleMatrix2mxArray(PGMatrix,mxM);
	plhs[0] = mxM;

}
