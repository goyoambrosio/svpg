/****
  SoftVision. Software for Computer Vision

  Gregorio Ambrosio Cestero (goyo@computer.org)
  System Engineering and Automation Department 
  University of Malaga. Spain                   

  $RCSfile: g_stcorr.cpp,v $
  $Revision: 1.1 $
  $Date: 2000/01/21 13:04:22 $
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
#include "StereoImage.h"

void
mexFunction(int nlhs,mxArray *plhs[],int nrhs,const mxArray *prhs[])
{
	mxArray  *mxM;
	size_t	  mxNumRows, mxNumCols;
	size_t    i,j;
	double    val = 0.0;
	int nrows,ncols,nrows1,ncols1;

	StereoImage S;
	Image DI;
	unsigned char M = 2;
	unsigned char N = 2;
	unsigned char D = 10;
	StructMiscData MiscData;

	/* check for proper number of arguments */
	if(nrhs==0) {
		mexPrintf("===============================================\n");
		mexPrintf("stcorr.dll (c)1999 G.A.C. (rv.1)\n");
		mexPrintf("Gregorio Ambrosio Cestero\n");
		mexPrintf("University of Malaga\n");
		mexPrintf("Department of System Engineering and Automation\n");
		mexPrintf("Email: goyo@computer.org\n");
		mexPrintf("================================================\n");
		mexPrintf("Build: %s\n",__TIMESTAMP__);
		mexPrintf("================================================\n");
		mexErrMsgTxt("Six inputs required.");
	} else if(nrhs!=6) {
		mexErrMsgTxt("Six inputs required.");
	} else if(nlhs!=1) {
		mexErrMsgTxt("One output required.");
	}

	//Control the correctness of input arguments
	if( !mxIsNumeric(prhs[0]) || 
		!mxIsDouble(prhs[0])  ||
		 mxIsEmpty(prhs[0])   ||
		 mxIsComplex(prhs[0])  ){
		mexErrMsgTxt("The Left matrix has the incorrect format");
	}

	if( !mxIsNumeric(prhs[1]) || 
		!mxIsDouble(prhs[1])  ||
		 mxIsEmpty(prhs[1])   ||
		 mxIsComplex(prhs[1])  ){
		mexErrMsgTxt("The Right matrix has the incorrect format");
	}

	nrows = mxGetM(prhs[0]);
	ncols = mxGetN(prhs[0]);
	nrows1 = mxGetM(prhs[1]);
	ncols1 = mxGetN(prhs[1]);

	if (!((nrows==nrows1)&&(ncols==ncols1)))
		mexErrMsgTxt("The image dimensions must agree");


	nrows = mxGetM(prhs[2]);
	ncols = mxGetN(prhs[2]);
	if( !mxIsNumeric(prhs[2]) || !mxIsDouble(prhs[2])  ||
	     mxIsEmpty(prhs[2])   ||  mxIsComplex(prhs[2]) ||
		!(nrows==1 && ncols==1) ) {
	mexErrMsgTxt("Input M must be a scalar.");
	}
	nrows = mxGetM(prhs[3]);
	ncols = mxGetN(prhs[3]);
	if( !mxIsNumeric(prhs[3]) || !mxIsDouble(prhs[3])  ||
	     mxIsEmpty(prhs[3])   ||  mxIsComplex(prhs[3]) ||
		!(nrows==1 && ncols==1) ) {
	mexErrMsgTxt("Input N must be a scalar.");
	}
	nrows = mxGetM(prhs[4]);
	ncols = mxGetN(prhs[4]);
	if( !mxIsNumeric(prhs[4]) || !mxIsDouble(prhs[4])  ||
	     mxIsEmpty(prhs[4])   ||  mxIsComplex(prhs[4]) ||
		!(nrows==1 && ncols==1) ) {
	mexErrMsgTxt("Input MaxDisp must be a scalar.");
	}

	nrows = mxGetM(prhs[5]);
	ncols = mxGetN(prhs[5]);
	if( !mxIsNumeric(prhs[5]) || !mxIsDouble(prhs[5])  ||
	     mxIsEmpty(prhs[5])   ||  mxIsComplex(prhs[5]) ||
		!(nrows==1 && ncols==1) ) {
	mexErrMsgTxt("Input Trace must be a scalar.");
	}

	//Extraction of the input values
	M = *mxGetPr(prhs[2]);
	N = *mxGetPr(prhs[3]);
	D = *mxGetPr(prhs[4]);
	MiscData.TraceMessages = *mxGetPr(prhs[5]);

	mxArray2UcharMatrix(prhs[0],S.L.Retina);
	mxArray2UcharMatrix(prhs[1],S.R.Retina);

	if (M<=0){
		M = 1;
		mexWarnMsgTxt("Setting M = 1");
	}
	if (N<=0){
		N = 1;
		mexWarnMsgTxt("Setting N = 1");
	}
	if (D<=0){
		D = 1;
		mexWarnMsgTxt("Setting D = 1");
	}

	//Process	
	DI = S.CorrelationStereo(M,N,D,MiscData);

	//Passing to output vars
	UcharMatrix2mxArray(DI.Retina,mxM);
	plhs[0] = mxM;


}
