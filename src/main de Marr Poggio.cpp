/****
  SoftVision. Software for Computer Vision

  Gregorio Ambrosio Cestero (goyo@computer.org)
  System Engineering and Automation Department 
  University of Malaga. Spain                   

  $RCSfile: main\040de\040Marr\040Poggio.cpp,v $
  $Revision: 1.1 $
  $Date: 2000/01/21 13:04:41 $
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

void sleep( clock_t wait );

void main( int argc, char *argv[] )
{
	clock_t start, finish;
	double  duration;

    start = clock();   



/*************************************************************************\
 *                  A Modified Marr Poggio Stereo Matcher                *
\*************************************************************************/

	cout << "A Modified Marr Poggio Stereo Matcher" << endl;

	StereoImage IM;
	FloatMatrix LC[4],RC[4];
	CharMatrix  LP[4],LN[4],LH[4],LZ[4];
	CharMatrix  RP[4],RN[4],RH[4],RZ[4];
	char		wvector[]={33,17,9,5};
	size_t i,j,level,aux1,aux2,aux3;
	const char NumLevels = 4;

	IM.Left.Retina.Load("d:\\users\\goyo\\desarrollo\\svawin32\\datos\\L128.mat");
	IM.Right.Retina.Load("d:\\users\\goyo\\desarrollo\\svawin32\\datos\\R128.mat");

	cout << "Initialization finished" << endl;

	///////////////////////////////////// Algorithm /////////////////////////////////
	//
	// (1) Convolutions. Convolve the images L,R with Laplacian of Gaussian filters
	//                   for different values of w (5,9,17,33)
	for (level=0;level<NumLevels;level++) {
		LC[level]=IM.Left.DogW(wvector[level]);
		RC[level]=IM.Right.DogW(wvector[level]);
	}
	cout << "(1) Convolutions. Finished" << endl;


	// (2) Zero-Crossing. Compute the zero-crossings of the convolved images

	{
		CharMatrix ZCVL,ZCHL,ZCVR,ZCHR;

		for (level=0;level<NumLevels;level++) {
			IM.Left.ZCross(LC[level],ZCVL,ZCHL);
			IM.Right.ZCross(RC[level],ZCVR,ZCHR);
			
			LP[level]=(ZCHL==1);							//Positive zero-crossing of LC
			LN[level]=(ZCHL==-1);							//Negative zero-crossing of LC
			LH[level]=(ZCVL!=0);							//Horizontal zero-crossing of LC
			LZ[level]=(LP[level]&&LN[level]&&LH[level]);	//All zero-crossing of LC

			RP[level]=(ZCHR==1);							//Positive zero-crossing of RC
			RN[level]=(ZCHR==-1);							//Negative zero-crossing of RC
			RH[level]=(ZCVR!=0);							//Horizontal zero-crossing of RC
			RZ[level]=(RP[level]&&RN[level]&&RH[level]);	//All zero-crossing of RC
		}
	}
	cout << "(2) Zero-Crossing. Finished" << endl;

	// (3) Fixation position. Initially chose the alignment of the two images to correspond
	//                        some preset lower limit, and increment by a specified amount until
	//                        the alignment exceeds some preset upper limit
	char d0;
	for (d0=-3;d0<=3;d0++) {
		cout << "(3) Fixation position. d0 = "<< d0 << endl;

		// (4) Matching. The matching algorithm can be subdivided into three sections. First, the 
		//               feature points are matched; then, figural continuity is applied to the resulting
		//               matches; and finally, any ambiguities betwwen matches are resolved.
		//
		// (4.1) Feature point matching. Suppose we are dealing with zero-crossing descriptions corresponding
		//                               to some particular filter of size w0. Given a disparity d0, we
		//                               construct an N x N x 2w0 local disparity array M(x,y,r) 
		//                               where -w<=r<=w
		//                               Each slice of M(x,y,r0) given by a value r0 of r is a set of matched
		//                               feature points, within a vertical range of +-e, for a local disparity
		//                               value r about the current convergence value d0. Note that positive
		//                               zero-crossing are matched to positive ones, and negative to negatives,
		//                               over a vertical range of +-e, and over a horizontal range of +-w
		//                               about the current alignment.


		//************************************************************************
		//							IMPLEMENTACION ORIGINAL
		//Matrix<char*> M[NumLevels];
		//for (level=0;level<NumLevels;level++) {
		//	M[level].Resize(IM.Left.Retina.Depth(),IM.Left.Retina.Width());
		//	for (i=0;i<M[level].Depth();i++){
		//		for (j=0;j<M[level].Width();j++)
		//			M[level][i][j]=new char[2*wvector[level]+1];
		//	}
		//}
		//*************************************************************************
		
		// Adaptación propia donde elimino la tercera dimensión de la matriz
		CharMatrix MT[NumLevels];
		for (level=0;level<NumLevels;level++){
			MT[level].Resize(IM.Left.Retina.Depth(),IM.Left.Retina.Width());
			MT[level]=0;
		}
		// Fin adaptación

		for (level=0;level<NumLevels;level++) {	//Para cada nivel de operador (coarse to fine matching strategy)
			char w; //Ancho del operador utilizado para la extracción de bordes
			char r; //Desplazamiento horizontal
			char v; //Desplazamiento vertical
			char e; //Variación del desplazamiento vertical

			w  = wvector[level] + d0;
			e  = 2;

			for (i=e;i<MT[level].Depth()-e;i++)				//Recorremos la matriz por filas y columnas
				for (j=(w+d0);j<MT[level].Width()-(w+d0);j++) 
					for (r=-w;r<=w;r++){ 					//Para el entorno de disparidad -w <= r <= w
						char RPacc = 0;
						char RNacc = 0;
						for (v=i-e;v<=i+e;v++) {
							RPacc = RPacc && RP[level][v][j+d0+r];
							RNacc = RNacc && RN[level][v][j+d0+r];
						}
						// Implementación original: se marca la tercera dimensión indexada en r
						//M[level][i][j][r] = (LP[level][i][j] || RPacc) && (LN[level][i][j] || RNacc);
						//               |
						//				Esto habría que trasladarlo al segmento positivo.

						//Adaptación propia: Voy realizando la OR de los valores de M[level][i][j][r] en
						//MT[level][i][j] en el mismo proceso de forma que no utilizo la tercera dimensión
						//en r para almacenar los valores y después hacer la OR
						MT[level][i][j] = MT[level][i][j] && (LP[level][i][j] || RPacc) && (LN[level][i][j] || RNacc);
						//Fin adaptación
					}
		}
		cout << "  (4.1) Feature point matching. Finished" << endl;

		// (4.2) Figural continuity. In order to distinguish correct from random feature point matches, we
		//							 apply a figural continuty constraint, by restricting the accepted
		//							 matches to those extended contour segments whose length is sufficiently
		//							 large.

		//*****************************************************************************
		//							IMPLEMENTACION ORIGINAL
		//CharMatrix MT[NumLevels];
		//for (level=0;level<NumLevels;level++){
		//	MT[level].Resize(IM.Left.Retina.Depth(),IM.Left.Retina.Width());
		//	MT[level]=0;
		//	for (i=0;i<M[level].Depth();i++)
		//		for (j=0;j<M[level].Width();j++)
		//			for (r=0;r<=2*w+1;r++){
		//				MT[level][i][j]=MT[level][i][j] && M[level][i][j][r]
		//*****************************************************************************
		
		//Adaptación propia. Ya he generado la matriz MT en el paso anterior
		//Fin adaptación

		CharMatrix SM[NumLevels];
		for (level=0;level<NumLevels;level++){
			SM[level].Resize(IM.Left.Retina.Depth(),IM.Left.Retina.Width());
			SM[level]=0;
		}

		SM = MT; //Esta instrucción sirve la sustituire por la implementación de la Continuidad Figural

		cout << "  (4.2) Figural continuity. Finished" << endl;
		
		// (4.3) Disparity updating. SM contains all the matches for this alignment that pass the figural
		//							 continuity constraint. Now, we need to update the global disparity
		//							 array D(x,y,d)

		//CharMatrix D[NumLevels];		//Disparity array
		//for (level=0;level<NumLevels;level++){
		//	D[level].Resize(IM.Left.Retina.Depth(),IM.Left.Retina.Width());
		//	D[level]=0;
		//}
	}

/*************************************************************************\
 *               End of "A Modified Marr Poggio Stereo Matcher"          *
\*************************************************************************/



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
