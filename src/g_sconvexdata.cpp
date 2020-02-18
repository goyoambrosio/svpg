/****
  SoftVision. Software for Computer Vision

  Gregorio Ambrosio Cestero (goyo@computer.org)
  System Engineering and Automation Department 
  University of Malaga. Spain                   

  $RCSfile: g_sconvexdata.cpp,v $
  $Revision: 1.1 $
  $Date: 2000/01/21 13:04:13 $
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


#include "gacmex.h"
#include "ImgSegment.h"

void
mexFunction(int nlhs,mxArray *plhs[],int nrhs,const mxArray *prhs[])
{
	mxArray  *mxM;
	size_t	  mxNumRows, mxNumCols;
	int nrows,ncols;

	DoubleMatrix ImgSegmentsMatrix;
	DoubleMatrix AdjacencyMatrix;
	ImgSegment S;
	ImgSegmentVector ISV;
	AffGraph<pImgSegment> DistanceGraph,ClockwiseAngleGraph,CircularityGraph;

	size_t i;

	double MaxDistance,MaxNoConvexityThreshold;

	/* check for proper number of arguments */
	if(nrhs==0) {
		mexPrintf("===============================================\n");
		mexPrintf("g_sconvexdata.dll (c)1999 G.A.C. (rv.4)\n");
		mexPrintf("Gregorio Ambrosio Cestero\n");
		mexPrintf("University of Malaga\n");
		mexPrintf("Department of System Engineering and Automation\n");
		mexPrintf("Email: goyo@computer.org\n");
		mexPrintf("================================================\n");
		mexPrintf("Build: %s\n",__TIMESTAMP__);
		mexPrintf("================================================\n");
		mexErrMsgTxt("Three inputs required.");
	} else if(nrhs!=3) {
		mexErrMsgTxt("Three inputs required.");
	} else if(nlhs!=3) {
		mexErrMsgTxt("Three outputs required.");
	}

	//Control the correctness of input arguments

	if( !mxIsNumeric (prhs[0])    || 
		!mxIsDouble  (prhs[0])    ||
		 mxIsEmpty   (prhs[0])    ||
		 mxIsComplex (prhs[0])    ||
		 mxGetN      (prhs[0])!=5 ){
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

	//Extraction of the input values
	MaxDistance				= *mxGetPr(prhs[1]);
	MaxNoConvexityThreshold	= *mxGetPr(prhs[2]);

	//Process
	mxArray2DoubleMatrix(prhs[0],ImgSegmentsMatrix);
	for (i=0;i<ImgSegmentsMatrix.Depth();i++){
		S=ImgSegment(ImgSegmentsMatrix[i][1],
			         ImgSegmentsMatrix[i][2],
				     ImgSegmentsMatrix[i][3],
				     ImgSegmentsMatrix[i][4]);
		S.Label = ImgSegmentsMatrix[i][0];
		ISV.push_back(S);
	}

	ISV.ConvexGraph(DistanceGraph,ClockwiseAngleGraph,CircularityGraph,MaxDistance,MaxNoConvexityThreshold);

	AdjacencyMatrix = DistanceGraph.GetAdjacencyMatrix();

	//Passing to output vars
	DoubleMatrix2mxArray(AdjacencyMatrix,mxM);
	plhs[0] = mxM;

	AdjacencyMatrix = ClockwiseAngleGraph.GetAdjacencyMatrix();

	//Passing to output vars
	DoubleMatrix2mxArray(AdjacencyMatrix,mxM);
	plhs[1] = mxM;

	AdjacencyMatrix = CircularityGraph.GetAdjacencyMatrix();

	//Passing to output vars
	DoubleMatrix2mxArray(AdjacencyMatrix,mxM);
	plhs[2] = mxM;

}
