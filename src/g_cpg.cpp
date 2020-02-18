/****
  SoftVision. Software for Computer Vision

  Gregorio Ambrosio Cestero (goyo@computer.org)
  System Engineering and Automation Department 
  University of Malaga. Spain                   

  $RCSfile: g_cpg.cpp,v $
  $Revision: 1.1 $
  $Date: 2000/01/21 13:04:09 $
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
#include "Image.h"


/**************************************\
		GetCPGMatrix
\**************************************/

DoubleMatrix GetCPGMatrix(Image I){
	size_t NumSegments;
	size_t NumCPGs;
	DoubleMatrix CPGMatrix;
	ConvexPerceptualGroup CPG;
	ConvexPerceptualGroupMap::iterator CPGMit;
	LabelVector LV;
	LabelVector::iterator LVit;
	Label L;
	size_t i;

	NumSegments = I.ConvexSegmentRetina.size();

	//Compute the number of CPGs without children
	NumCPGs = 0;
	for (CPGMit = I.ConvexPerceptualGroupRetina.begin();CPGMit != I.ConvexPerceptualGroupRetina.end();CPGMit++){
		if (!(*CPGMit).second.GetChildren().size()) NumCPGs++;
	}
	CPGMatrix.Resize(NumCPGs,NumSegments);

	//Build the matrix
	i=0;
	for (CPGMit = I.ConvexPerceptualGroupRetina.begin();CPGMit != I.ConvexPerceptualGroupRetina.end();CPGMit++){
		LV  = (*CPGMit).first;
		CPG = (*CPGMit).second;
		if (!CPG.GetChildren().size()){
			for (LVit=LV.begin();LVit!=LV.end();LVit++){
				L=(*LVit);
				CPGMatrix[i][L-1]=1;
			}
			i++;
		}
	}

	return CPGMatrix;
}


/**************************************\
		GetSMatrix
\**************************************/
DoubleMatrix GetSMatrix(Image I){
	size_t i;
	DoubleMatrix SMatrix;
	SegmentMap::iterator SMit;

	SMatrix.Resize(I.ConvexSegmentRetina.size(),5);

	//Passing to output vars
    i = 0;
	for (SMit=I.ConvexSegmentRetina.begin();SMit!=I.ConvexSegmentRetina.end();SMit++){
		SMatrix[i][0]=(*SMit).first;
		SMatrix[i][1]=(*SMit).second.GetA().i;
		SMatrix[i][2]=(*SMit).second.GetA().j;
		SMatrix[i][3]=(*SMit).second.GetB().i;
		SMatrix[i][4]=(*SMit).second.GetB().j;
		i++;
	}
	return SMatrix;
}

/**************************************\
		GetFMatrix
\**************************************/
DoubleMatrix GetFMatrix(Image I){
	size_t i,j;
	size_t NumCPGs;
	DoubleMatrix FMatrix;
	nCompVector FV;
	nCompVector::iterator FVit;
	ConvexPerceptualGroup CPG;
	ConvexPerceptualGroupMap::iterator CPGMit;
	double F;

	//Compute FMatrix's size
	NumCPGs = 0;
	for (CPGMit = I.ConvexPerceptualGroupRetina.begin();CPGMit != I.ConvexPerceptualGroupRetina.end();CPGMit++)
		if (!(*CPGMit).second.GetChildren().size()) NumCPGs++;
	CPGMit--;
	FV     = (*CPGMit).second.GetFeatureVector();

	FMatrix.Resize(NumCPGs,FV.size());

	i=0;
	for (CPGMit = I.ConvexPerceptualGroupRetina.begin();CPGMit != I.ConvexPerceptualGroupRetina.end();CPGMit++){
		CPG = (*CPGMit).second;
		if (!CPG.PerceptualGroup::GetChildren().size()){
			FV  = CPG.GetFeatureVector();
			j=0;
			for (FVit=FV.begin();FVit!=FV.end();FVit++){
				F=(*FVit);
				FMatrix[i][j]=F;
				j++;
			}
			i++;
		}
	}
	return FMatrix;
}


/**************************************\
		mexFunction
\**************************************/
void
mexFunction(int nlhs,mxArray *plhs[],int nrhs,const mxArray *prhs[])
{
	mxArray  *mxM1,*mxM2,*mxM3;
	size_t	  mxNumRows, mxNumCols;
	int nrows,ncols;

	Image I;

	DoubleMatrix CPGMatrix;
	DoubleMatrix SMatrix;
	DoubleMatrix FMatrix;

	StructSData SData;
	StructPGData PGData;
	StructMiscData MiscData;
	size_t i=0;

	/* check for proper number of arguments */
	if(nrhs==0) {
		mexPrintf("===============================================\n");
		mexPrintf("cpg.dll (c)1999 G.A.C. (rv.1)\n");
		mexPrintf("Gregorio Ambrosio Cestero\n");
		mexPrintf("University of Malaga\n");
		mexPrintf("Department of System Engineering and Automation\n");
		mexPrintf("Email: goyo@computer.org\n");
		mexPrintf("================================================\n");
		mexPrintf("Build: %s\n",__TIMESTAMP__);
		mexPrintf("================================================\n");
		mexErrMsgTxt("Ten inputs required.");
	} else if(nrhs!=10) {
		mexErrMsgTxt("Ten inputs required.");
	} else if(nlhs!=3) {
		mexErrMsgTxt("Three outputs required.");
	}

	//Control the correctness of input arguments
	if( !mxIsNumeric (prhs[0])    || 
		!mxIsDouble  (prhs[0])    ||
		 mxIsEmpty   (prhs[0])    ||
		 mxIsComplex (prhs[0])    ){
		mexErrMsgTxt("The image matrix has the incorrect format");
	}
	if( !mxIsNumeric (prhs[1])    || 
		!mxIsDouble  (prhs[1])    ||
		 mxIsEmpty   (prhs[1])    ||
		 mxIsComplex (prhs[1])    ){
		mexErrMsgTxt("The segment matrix has the incorrect format");
	}

	for (i=2;i<=9;i++){
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

	mxArray2UcharMatrix(prhs[0],I.Retina);
	mxArray2UcharMatrix(prhs[1],I.EdgeRetinaMag);

//	PGData.MaxDistBetwParallelSegments		= 10;
//	PGData.MaxAngleDiffBetwParallelSegments = 10;
//	PGData.MaxDistBetwColSegments			= 10;
	PGData.k								= *mxGetPr(prhs[2]);
	PGData.MaxDistBetwProxSegments			= *mxGetPr(prhs[3]);
	PGData.MaxNoConvexityThreshold          = *mxGetPr(prhs[4]);
	PGData.JacobExtension_1					= *mxGetPr(prhs[5]);
	PGData.JacobExtension_2					= *mxGetPr(prhs[6]);
//	PGData.Polarity							= *mxGetPr(prhs[9]);

//	SData.MaxLinearRegressionError			= 0.5;
	SData.MinNumOfPixels					= *mxGetPr(prhs[7]);
	SData.MaxDistance						= *mxGetPr(prhs[8]); //Para la extraccion de segmentos

	MiscData.TraceMessages					= *mxGetPr(prhs[9]);

	if (SData.MinNumOfPixels<=2){
		SData.MinNumOfPixels = 2;
		mexWarnMsgTxt("Setting MinLong = 2");
	}
	if (SData.MaxDistance<=0){
		SData.MaxDistance = 0;
		mexWarnMsgTxt("Setting MaxDist = 0");
	}

	//Process
	I.SegmentExtractionGAC(SData);
	I.ConvexPerceptualGrouping(SData, PGData, MiscData);
	CPGMatrix = GetCPGMatrix(I);
	SMatrix   = GetSMatrix(I);
	FMatrix   = GetFMatrix(I);

	DoubleMatrix2mxArray(CPGMatrix,mxM1);
	plhs[0] = mxM1;
	DoubleMatrix2mxArray(SMatrix,mxM2);
	plhs[1] = mxM2;
	DoubleMatrix2mxArray(FMatrix,mxM3);
	plhs[2] = mxM3;


}
