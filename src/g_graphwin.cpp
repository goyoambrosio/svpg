/****
  SoftVision. Software for Computer Vision

  Gregorio Ambrosio Cestero (goyo@computer.org)
  System Engineering and Automation Department 
  University of Malaga. Spain                   

  $RCSfile: g_graphwin.cpp,v $
  $Revision: 1.1 $
  $Date: 2000/01/21 13:04:10 $
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
#include <LEDA/graphwin.h>

void
mexFunction(int nlhs,mxArray *plhs[],int nrhs,const mxArray *prhs[])
{
	mxArray  *mxM;
	size_t	  mxNumRows, mxNumCols;
	size_t    i,j;
	double    val = 0.0;
	int nrows,ncols;

	Image I;
	double Sigma           = 1;
	unsigned char HighHyst = 106;
	unsigned char LowHyst  = 85;

	/* check for proper number of arguments */
	if(nrhs==0) {
		mexPrintf("===============================================\n");
		mexPrintf("g_graphwin.dll (c)1999 G.A.C. (rv.1)\n");
		mexPrintf("Gregorio Ambrosio Cestero\n");
		mexPrintf("University of Malaga\n");
		mexPrintf("Department of System Engineering and Automation\n");
		mexPrintf("Email: goyo@computer.org\n");
		mexPrintf("===============================================\n");
		mexPrintf("Build: %s\n",__TIMESTAMP__);
		mexPrintf("===============================================\n");
//		mexErrMsgTxt("Four input required.");
//	} else if(nrhs!=4) {
//		mexErrMsgTxt("Four input required.");
//	} else if(nlhs!=1) {
//		mexErrMsgTxt("One output required.");
	}

  GraphWin gw;

  gw.set_node_width(28);
  gw.set_node_height(28);

  gw.set_zoom_objects(true);

  gw.display();

  gw.edit();


/*
	//Control the correctness of input arguments
	if( !mxIsNumeric(prhs[0]) || 
		!mxIsDouble(prhs[0])  ||
		 mxIsEmpty(prhs[0])   ||
		 mxIsComplex(prhs[0])  ){
		mexErrMsgTxt("The Matrix has the incorrect format");
	}

	nrows = mxGetM(prhs[1]);
	ncols = mxGetN(prhs[1]);
	if( !mxIsNumeric(prhs[1]) || !mxIsDouble(prhs[1])  ||
	     mxIsEmpty(prhs[1])   ||  mxIsComplex(prhs[1]) ||
		!(nrows==1 && ncols==1) ) {
	mexErrMsgTxt("Input Sigma must be a scalar.");
	}
	nrows = mxGetM(prhs[2]);
	ncols = mxGetN(prhs[2]);
	if( !mxIsNumeric(prhs[2]) || !mxIsDouble(prhs[2])  ||
	     mxIsEmpty(prhs[2])   ||  mxIsComplex(prhs[2]) ||
		!(nrows==1 && ncols==1) ) {
	mexErrMsgTxt("Input LowHyst must be a scalar.");
	}
	nrows = mxGetM(prhs[3]);
	ncols = mxGetN(prhs[3]);
	if( !mxIsNumeric(prhs[3]) || !mxIsDouble(prhs[3])  ||
	     mxIsEmpty(prhs[3])   ||  mxIsComplex(prhs[3]) ||
		!(nrows==1 && ncols==1) ) {
	mexErrMsgTxt("Input HighHyst must be a scalar.");
	}

	//Extraction of the input values
	Sigma    = *mxGetPr(prhs[1]);
	LowHyst  = *mxGetPr(prhs[2]);
	HighHyst = *mxGetPr(prhs[3]);
	mxArray2UcharMatrix(prhs[0],I.Retina);

	if (Sigma<=0){
		Sigma = 0.1;
		mexWarnMsgTxt("Setting Sigma = 0.1");
	}
	if (LowHyst<=0){
		LowHyst = 1;
		mexWarnMsgTxt("Setting LowHyst = 1");
	}
	if (HighHyst<=0){
		HighHyst = 1;
		mexWarnMsgTxt("Setting HighHyst = 1");
	}

    //Process

	I.CannyS(Sigma,LowHyst,HighHyst);
	I.PostCanny();
	I.PostCanny();

	//Passing to output vars
	UcharMatrix2mxArray(I.EdgeRetinaMag,mxM);
	plhs[0] = mxM;
*/



}



