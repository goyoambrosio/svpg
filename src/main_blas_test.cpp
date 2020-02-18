/****
  SoftVision. Software for Computer Vision

  Gregorio Ambrosio Cestero (goyo@computer.org)
  System Engineering and Automation Department 
  University of Malaga. Spain                   

  $RCSfile: main_blas_test.cpp,v $
  $Revision: 1.1 $
  $Date: 2000/01/21 13:04:43 $
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


/************************************************************\
 *                         SVAWin32                         *
 *----------------------------------------------------------*
 * Temas pendientes:                                        *
 *															*
\************************************************************/

// The debugger can't handle symbols more than 255 characters long.
// STL often creates symbols longer than that.
// When symbols are longer than 255 characters, the warning is disabled.
#pragma warning(disable:4786)

#include "TypedMatrix.h"
#include "Globals.h"
#include "Blas1.h"

#include <time.h>
#include <typeinfo.h>
#include <vector>

using namespace GAC;

void sleep( clock_t wait );

void main( int argc, char *argv[] )
{
	clock_t start, finish;
	double  duration;

    start = clock();   

/*************************************************************************\
 *                       Begin Test                                      *
\*************************************************************************/


/*****************************************\
 *               Blas 1                  *
\*****************************************/
	
	//It's only to demonstrate how to link with blas1 funtions.
	//F77_DASUM(const fi_  *N , const fd_ *dx, const fi_* incx);
	//N    : Number of components to sum (usually is the total number of components)
	//dx   : vector (array)
	//incx : increment
	Fortran_integer N,incx;
	Fortran_double dx[4], result;
	N    = 4;
	dx[0] = 1;
	dx[1] = 2;
	dx[2] = 3;
	dx[3] = 4;


	incx = 0;
	result = F77_DASUM(&N , &dx[0], &incx);
	printf("(array)Result: %.30g\n",result);
	incx = 1;
	result = F77_DASUM(&N , &dx[0], &incx);
	printf("(array)Result: %.30g\n",result);
	incx = 2;
	result = F77_DASUM(&N , &dx[0], &incx);
	printf("(array)Result: %.30g\n",result);


	//Using STL's vector
	vector<double> vx;

	vx.push_back(1);
	vx.push_back(2);
	vx.push_back(3);
	vx.push_back(4);
	incx = 0;
	result = F77_DASUM(&N , vx.begin(), &incx);
	printf("(stl vector)Result: %.30g\n",result);
	incx = 1;
	result = F77_DASUM(&N , vx.begin(), &incx);
	printf("(stl vector)Result: %.30g\n",result);
	incx = 2;
	result = F77_DASUM(&N , vx.begin(), &incx);
	printf("(stl vector)Result: %.30g\n",result);
	
	
	
/*****************************************\
 *               Blas 3                  *
\*****************************************/












/*************************************************************************/	
	DoubleMatrix A(5,5);
	Matrix<double> B(5,5);
	Matrix<double> C(4,3),D(3,4);
	DoubleMatrix E(5,4),F(5,4);
	DoubleMatrix G,H;
	Matrix<bool> T(5,4),U(5,4);
	Matrix<double> V(4,5,3);
//	cout << V;


// operator []
	A[0][0]= 1;A[0][1]=0;A[0][2]=1;A[0][3]=1;A[0][4]=1;
	A[1][0]= 2;A[1][1]=2;A[1][2]=1;A[1][3]=2;A[1][4]=2;
	A[2][0]= 1;A[2][1]=3;A[2][2]=1;A[2][3]=3;A[2][4]=3;
	A[3][0]= 4;A[3][1]=4;A[3][2]=1;A[3][3]=4;A[3][4]=4;
	A[4][0]= 5;A[4][1]=5;A[4][2]=1;A[4][3]=5;A[4][4]=5;

	B[0][0]=10;B[0][1]=10;B[0][2]=10;B[0][3]=10;B[0][4]=10;
	B[1][0]=10;B[1][1]=10;B[1][2]=10;B[1][3]=10;B[1][4]=10;
	B[2][0]=10;B[2][1]=10;B[2][2]=10;B[2][3]=10;B[2][4]=10;
	B[3][0]=10;B[3][1]=10;B[3][2]=10;B[3][3]=10;B[3][4]=10;
	B[4][0]=10;B[4][1]=10;B[4][2]=10;B[4][3]=10;B[4][4]=10;

	C[0][0]=1;C[0][1]=1;C[0][2]=1;
	C[1][0]=2;C[1][1]=2;C[1][2]=2;
	C[2][0]=3;C[2][1]=3;C[2][2]=3;
	C[3][0]=4;C[3][1]=4;C[3][2]=4;

	D[0][0]=4;D[0][1]=5;D[0][2]=6;D[0][3]=7;
	D[1][0]=4;D[1][1]=5;D[1][2]=6;D[1][3]=7;
	D[2][0]=4;D[2][1]=5;D[2][2]=6;D[2][3]=7;


	E[0][0] = 1;E[0][1] = 5;E[0][2] = 7;E[0][3] = 2;
	E[1][0] = 2;E[1][1] = 4;E[1][2] = 8;E[1][3] = 2;
	E[2][0] = 3;E[2][1] = 3;E[2][2] = 9;E[2][3] = 7;
	E[3][0] = 4;E[3][1] = 2;E[3][2] = 3;E[3][3] = 0;
	E[4][0] = 5;E[4][1] = 1;E[4][2] = 0;E[4][3] = 3;

// operator ()

	F(1,1) = 2;F(1,2) = 4;F(1,3) = 7;F(1,4) = 2;
	F(2,1) = 5;F(2,2) = 3;F(2,3) = 8;F(2,4) = 2;
	F(3,1) = 6;F(3,2) = 2;F(3,3) = 9;F(3,4) = 7;
	F(4,1) = 0;F(4,2) = 5;F(4,3) = 3;F(4,4) = 0;
	F(5,1) = 1;F(5,2) = 6;F(5,3) = 0;F(5,4) = 3;

	T(1,1) = 1;T(1,2) = 0;T(1,3) = 1;T(1,4) = 0;
	T(2,1) = 1;T(2,2) = 0;T(2,3) = 1;T(2,4) = 0;
	T(3,1) = 1;T(3,2) = 0;T(3,3) = 1;T(3,4) = 0;
	T(4,1) = 1;T(4,2) = 0;T(4,3) = 1;T(4,4) = 0;
	T(5,1) = 1;T(5,2) = 0;T(5,3) = 1;T(5,4) = 0;

	U(1,1) = 0;U(1,2) = 1;U(1,3) = 0;U(1,4) = 1;
	U(2,1) = 0;U(2,2) = 1;U(2,3) = 0;U(2,4) = 1;
	U(3,1) = 0;U(3,2) = 1;U(3,3) = 0;U(3,4) = 1;
	U(4,1) = 0;U(4,2) = 1;U(4,3) = 0;U(4,4) = 1;
	U(5,1) = 0;U(5,2) = 1;U(5,3) = 0;U(5,4) = 1;
	



/*************************************************************************\
 *                       End Test                                        *
\*************************************************************************/


	//sleep( (clock_t)1 * CLOCKS_PER_SEC );
	finish = clock();
	duration = (double)(finish - start)/ CLOCKS_PER_SEC;
//	cout << start << "\t" << finish << "\t" << duration  << "\n";
	printf("%i\t%i\t%.30g\n",start,finish,duration);

}

/* Pauses for a specified number of milliseconds. */
void sleep( clock_t wait ){
   clock_t goal;
   goal = wait + clock();
   while( goal > clock() )
	   ;
}

// Para obtener el nombre del tipo
//	const type_info& MiTipo = typeid(LoQueSea);
//	cout << MiTipo.name();
