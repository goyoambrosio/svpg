/****
  SoftVision. Software for Computer Vision

  Gregorio Ambrosio Cestero (goyo@computer.org)
  System Engineering and Automation Department 
  University of Malaga. Spain                   

  $RCSfile: mainpru.cpp,v $
  $Revision: 1.1 $
  $Date: 2000/01/21 13:04:49 $
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
 * - Aplicar la separación de la Gaussiana para ir más      *
 *   rápido.												*
\************************************************************/


#include <iostream.h>
#include "Matrix.h"
#include <stdio.h>
#include <time.h>
#include <typeinfo.h>
#include "TypedMatrix.h"
#include "Image.h"
#include "StereoImage.h"
#include "Pixel.h"
#include "Lcde.h"

const char NumLevels = 4;

void sleep( clock_t wait );

void main( int argc, char *argv[] )
{
	clock_t start, finish;
	double  duration;

    start = clock();   


	CharMatrix A(5,5);
	FloatMatrix B(5,5);
	FloatMatrix C(4,3),D(3,4);

	A.SetAt(0,0,-1);A.SetAt(0,1,0);A.SetAt(0,2,1);A.SetAt(0,3,1);A.SetAt(0,4,1);
	A.SetAt(1,0,-2);A.SetAt(1,1,2);A.SetAt(1,2,1);A.SetAt(1,3,2);A.SetAt(1,4,2);
	A.SetAt(2,0,-1);A.SetAt(2,1,3);A.SetAt(2,2,1);A.SetAt(2,3,3);A.SetAt(2,4,3);
	A.SetAt(3,0,4);A.SetAt(3,1,4);A.SetAt(3,2,1);A.SetAt(3,3,4);A.SetAt(3,4,4);
	A.SetAt(4,0,5);A.SetAt(4,1,5);A.SetAt(4,2,1);A.SetAt(4,3,5);A.SetAt(4,4,5);

	B.SetAt(0,0,10);B.SetAt(0,1,0);B.SetAt(0,2,-10);B.SetAt(0,3,10);B.SetAt(0,4,10);
	B.SetAt(1,0,10);B.SetAt(1,1,10);B.SetAt(1,2,10);B.SetAt(1,3,10);B.SetAt(1,4,10);
	B.SetAt(2,0,10);B.SetAt(2,1,10);B.SetAt(2,2,10);B.SetAt(2,3,10);B.SetAt(2,4,10);
	B.SetAt(3,0,10);B.SetAt(3,1,10);B.SetAt(3,2,10);B.SetAt(3,3,10);B.SetAt(3,4,10);
	B.SetAt(4,0,10);B.SetAt(4,1,10);B.SetAt(4,2,10);B.SetAt(4,3,10);B.SetAt(4,4,10);

	C.SetAt(0,0,1);C.SetAt(0,1,1);C.SetAt(0,2,1);
	C.SetAt(1,0,2);C.SetAt(1,1,2);C.SetAt(1,2,2);
	C.SetAt(2,0,3);C.SetAt(2,1,3);C.SetAt(2,2,3);
	C.SetAt(3,0,4);C.SetAt(3,1,4);C.SetAt(3,2,4);

	D.SetAt(0,0,4);D.SetAt(0,1,5);D.SetAt(0,2,6);D.SetAt(0,3,7);
	D.SetAt(1,0,4);D.SetAt(1,1,5);D.SetAt(1,2,6);D.SetAt(1,3,7);
	D.SetAt(2,0,4);D.SetAt(2,1,5);D.SetAt(2,2,6);D.SetAt(2,3,7);

	typedef  Pixel * pPixel;
	Lcde<pPixel> Lista(0);
	
	Pixel P(1,1,67);
	Pixel Q(1,2,98);
	Pixel R(1,3,123);

	Lista.InsertarElemento(&P);
	Lista.InsertarElemento(&Q);
	Lista.InsertarElemento(&R);

	Lista.IrPrincipio();
	cout << *Lista();
	Lista++;
	cout << *Lista();
	Lista++;
	cout << *Lista();

/*
	StereoImage E;
	FloatMatrix FL,FR;
	CharMatrix Z1L,Z1R,Z2L,Z2R;
	E.Left.Retina.Load("d:\\users\\goyo\\desarrollo\\svawin32\\datos\\escalera.mat");
	E.Right.Retina.Load("d:\\users\\goyo\\desarrollo\\svawin32\\datos\\escalera.mat");

	FL=E.Left.DogW(9);
	FR=E.Right.DogW(9);

	E.Left.ZCross(FL,Z1L,Z2L);
	E.Right.ZCross(FR,Z1R,Z2R);

	FL.Save("d:\\users\\goyo\\desarrollo\\svawin32\\datos\\FL.mat");
	FR.Save("d:\\users\\goyo\\desarrollo\\svawin32\\datos\\FR.mat");

	Z1L.Save("d:\\users\\goyo\\desarrollo\\svawin32\\datos\\Z1L.mat");
	Z1R.Save("d:\\users\\goyo\\desarrollo\\svawin32\\datos\\Z1R.mat");
	Z2L.Save("d:\\users\\goyo\\desarrollo\\svawin32\\datos\\Z2L.mat");
	Z2R.Save("d:\\users\\goyo\\desarrollo\\svawin32\\datos\\Z2R.mat");
*/



	//sleep( (clock_t)1 * CLOCKS_PER_SEC );
	finish = clock();
	duration = (double)(finish - start)/ CLOCKS_PER_SEC;
	cout << start << "\t" << finish << "\t" << duration  << "\n";

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
