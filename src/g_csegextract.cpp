/****
  SoftVision. Software for Computer Vision

  Gregorio Ambrosio Cestero (goyo@computer.org)
  System Engineering and Automation Department 
  University of Malaga. Spain                   

  $RCSfile: g_csegextract.cpp,v $
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
#include "GrayImage.h"

void
mexFunction(int nlhs,mxArray *plhs[],int nrhs,const mxArray *prhs[])
{
	mxArray  *mxM;
	size_t	  mxNumRows, mxNumCols;
	int nrows,ncols;

	GrayImage I;
	DoubleMatrix S;
	ImgSegmentVector ISV;
	ImgSegmentVector::iterator ISVit;
	size_t i=0;

	double          MaxDistance;
	unsigned int	MinNumOfPixels;
    double          MaxDistBetwConvexSegments;
    double          MaxNoConvexityThreshold;
    bool            JacobExtension_1;
    bool            JacobExtension_2;

	/* check for proper number of arguments */
	if(nrhs==0) {
		mexPrintf("===============================================\n");
		mexPrintf("g_csegextract.dll (c)1999 G.A.C. (rv.1)\n");
		mexPrintf("Gregorio Ambrosio Cestero\n");
		mexPrintf("University of Malaga\n");
		mexPrintf("Department of System Engineering and Automation\n");
		mexPrintf("Email: goyo@computer.org\n");
		mexPrintf("================================================\n");
		mexPrintf("Build: %s\n",__TIMESTAMP__);
		mexPrintf("================================================\n");
		mexErrMsgTxt("Seven inputs required.");
	} else if(nrhs!=7) {
		mexErrMsgTxt("Seven inputs required.");
	} else if(nlhs!=1) {
		mexErrMsgTxt("One output required.");
	}

	//Control the correctness of input arguments
	if( !mxIsNumeric(prhs[0]) || 
		!mxIsDouble(prhs[0])  ||
		 mxIsEmpty(prhs[0])   ||
		 mxIsComplex(prhs[0])  ){
		mexErrMsgTxt("The matrix has the incorrect format");
	}

	for (i=1;i<=6;i++){
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
	MaxDistance				   = *mxGetPr(prhs[1]);
	MinNumOfPixels			   = *mxGetPr(prhs[2]);
    MaxDistBetwConvexSegments  = *mxGetPr(prhs[3]);
    MaxNoConvexityThreshold    = *mxGetPr(prhs[4]);
    JacobExtension_1           = *mxGetPr(prhs[5]);
    JacobExtension_2           = *mxGetPr(prhs[6]);

	mxArray2UcharMatrix(prhs[0],I);

	if (MinNumOfPixels<=2){
		MinNumOfPixels = 2;
		mexWarnMsgTxt("Setting MinLong = 2");
	}
	if (MaxDistance<=0){
		MaxDistance = 0;
		mexWarnMsgTxt("Setting MaxDist = 0");
	}

	//Process	

//ImgSegmentVector GrayImage::ImgSegmentExtractionConvex (double		  MaxDistance,
//									                      unsigned int	  MinNumOfPixels,
//											              double          MaxDistBetwConvexSegments,
//								                          double          MaxNoConvexityThreshold,
//								                          bool            JacobExtension_1,
//								                          bool            JacobExtension_2)
	
	
//	ISV = I.ImgSegmentExtraction(MaxDistance,MinNumOfPixels);
	ISV = I.ImgSegmentExtractionConvex (MaxDistance,
		                                MinNumOfPixels,
								        MaxDistBetwConvexSegments,
								        MaxNoConvexityThreshold,
								        JacobExtension_1,
								        JacobExtension_2);
	S.Resize(ISV.size(),5);

	i = 0;
	for (ISVit=ISV.begin();ISVit!=ISV.end();ISVit++){
		S[i][0]=(*ISVit).Label;
		S[i][1]=(*ISVit).GetA().i;
		S[i][2]=(*ISVit).GetA().j;
		S[i][3]=(*ISVit).GetB().i;
		S[i][4]=(*ISVit).GetB().j;
		i++;
	}

	//Passing to output vars
	DoubleMatrix2mxArray(S,mxM);
	plhs[0] = mxM;
}
