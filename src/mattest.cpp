/****
  SoftVision. Software for Computer Vision

  Gregorio Ambrosio Cestero (goyo@computer.org)
  System Engineering and Automation Department 
  University of Malaga. Spain                   

  $RCSfile: mattest.cpp,v $
  $Revision: 1.1 $
  $Date: 2000/01/21 13:04:53 $
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
#include "TypedMatrix.h"
#include "Globals.h"
void
mexFunction(int nlhs,mxArray *plhs[],int nrhs,const mxArray *prhs[])
{
	mxArray  *mxM;
	size_t	  mxNumRows, mxNumCols;
	size_t    i,j;
	double    val = 0.0;
	DoubleMatrix A;

	/* check for proper number of arguments */
	if(nrhs!=1) {
		mexErrMsgTxt("One input required.");
	} else if(nlhs!=1) {
		mexErrMsgTxt("One output required.");
	}

	if( !mxIsNumeric(prhs[0]) || 
		!mxIsDouble(prhs[0])  ||
		 mxIsEmpty(prhs[0])   ||
		 mxIsComplex(prhs[0])  ){
		mexErrMsgTxt("The Matrix has the incorrect format");
	}

//	mxNumRows = mxGetM(prhs[0]);
//	mxNumCols = mxGetN(prhs[0]);
//	mexPrintf("(M,N):(%i,%i)\n",mxNumRows,mxNumCols);

	mxArray2DoubleMatrix(prhs[0],A);
for (i=0;i<A.Depth();i++)
	for (j=0;j<A.Width();j++)
		A[i][j]=exp(-(cos(A[i][j])/(1-cos(2*QUARTER_PI/2))));

	DoubleMatrix2mxArray(A,mxM);
	plhs[0] = mxM;


}

