/****
  SoftVision. Software for Computer Vision

  Gregorio Ambrosio Cestero (goyo@computer.org)
  System Engineering and Automation Department 
  University of Malaga. Spain                   

  $RCSfile: main.cpp,v $
  $Revision: 1.1 $
  $Date: 2000/01/21 13:04:42 $
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


// The debugger can't handle symbols more than 255 characters long.
// STL often creates symbols longer than that.
// When symbols are longer than 255 characters, the warning is disabled.
#pragma warning(disable:4786)
// Redefinicion de macros por Mil.h y Leda
//#pragma warning(disable:6311)

#include <CVL/Image_lpr.h>
//#include <conio.h>						//Añadido por Juan Antonio



#include <time.h>
#include <string>						//From SGI STL. For ios functions. It's like #include <iostream>

using namespace GAC;
using namespace std;


#define _USE_INTEL_IPL_					//For use Intel Ipl Image Performace Suite

void main( int argc, char *argv[] )
{
	clock_t start, finish;
	double  duration;

    start = clock(); 


	/***********************************************\
	 *                   Image_lpr                 *
	\***********************************************/

	
	cout << "***********************************************" << endl << "*                  Image_lpr                  *" << endl << "***********************************************" << endl;

	// Constructor
	cout << "Constructor Image_lpr I1,I2" << endl;
	Image_lpr I1,I2;
	int umbral=0;
	
	/*
	//////////////////
	// Error en pow //
	//////////////////
	I1.LoadBMP("laura.bmp");
	unsigned char std = I1.Std();
	//Curiosamente ya no me da el error que te mencionaba, no se porqué, posiblemente sea por lo
	//de la configuración de Debug o Release.
	printf("Desviacion estandar: %d\n",std);
	//*/
	
	
	
		
	if (argc>1) I1.LoadBMP(argv[1]);
	//else I1.LoadBMP("\\home\\ISA\\imagenes\\coche07e.bmp");
	//else I1.LoadBMP("\\home\\ISA\\imagenes\\coche36c.bmp");
	//else I1.LoadBMP("\\home\\ISA\\imagenes\\coche09g.bmp");
	else I1.LoadBMP("\\home\\ISA\\imagenes\\coche10p.bmp");
	int NumRows=I1.Height();
	int NumCols=I1.Width();

	
	if (argc>2) {
		printf("\n\nArgumento 2: %s\n\n",argv[2]);
		if (!strcmp(argv[2],"th")) {
			///*
			/////////////
			//Threshold//
			/////////////
			cout << "Threshold example" << endl;
			I2 = I1.GlobalThreshold(50);
			I2.Show();
			
			////////////////
			//Connectivity//
			////////////////
			cout << "Connectivity example" << endl;
			IntMatrix C1(I1.Height(),I1.Width());
			C1=I2.iplGetConnectivity();
			I2 = (UcharMatrix)C1;
			I2.Show();
			//*/
		}
		else if (!strcmp(argv[2],"rg")) {
			///*
			//////////////
			//GetRegions//
			//////////////
			cout << "Get Regions example" << endl;
			I2 = I1.GlobalThreshold(50);
			Image_lpr::RegionVector REG;
			REG = I2.iplGetImageRegions(0,50,200);
			
			//REG.Show();
			for (int i=0;i<REG.size();i++) {
				Image_lpr::Region R=REG[i];
				float error = (float(R.OffsetX() / R.OffsetY())-4.78)*100/4.78;
				error*=(error<0)?-1:1;
				if (error<20.0) 
					//cout << "+ PROB(M) = " << 100.0-prob << " ";
					printf("+ ERROR(M) = %4.3f ",error);
				else
					//cout << "- PROB(M) = " << 100.0-prob << " ";
					printf("  ERROR(M) = %4.3f ",error);
				R.Show();
			}
			//I2.Show();
			//*/
		}
		else if (!strcmp(argv[2],"gth")) {
			///*
			////////////////
			//GetThreshold//
			////////////////
			cout << "GetThreshold example" << endl;
			
			umbral = I1.iplGetThreshold();
			cout << "\nUmbral optimo: " << umbral << endl;
			//I2.Show();
			//*/
		}
		else if (!strcmp(argv[2],"brg")) {
			//////////////
			//GetRegions//
			//////////////
			//Este trozo de codigo saca de  la imagen todos los digitos de la
			//matricula marcados como regiones
			cout << "Get Regions example" << endl;
			
			I2 = I1.GlobalThreshold(53);
			//I2.Show();
			Image_lpr::RegionVector REG;
			double factor=(I2.Width()*I2.Height())/(384*286);
			REG = I2.iplGetImageRegions(0,50*factor,700*factor);
			
			//REG.Show();
			for (int i=0;i<REG.size();i++) {
				Image_lpr::Region R=REG[i];
				float error;
				if (R.OffsetY()) error = (float(R.OffsetX() / R.OffsetY())-4.78)*100/4.78;
				else error=100.0;
				error*=(error<0)?-1:1;
				if (error<20.0) 
					//cout << "+ PROB(M) = " << 100.0-prob << " ";
					printf("+ ERROR(M) = %4.3f ",error);
				else
					//cout << "- PROB(M) = " << 100.0-prob << " ";
					printf("  ERROR(M) = %4.3f ",error);
				R.Show();
			}
			//I2.Show();
		}
		else if (!strcmp(argv[2],"gpl")) {
			I1.iplGetPlate();
		}
	}
	

	
	/*
	//////////////
	//GetRegions//
	//////////////
	//Este trozo de codigo saca de  la imagen todos los digitos de la
	//matricula marcados como regiones
	cout << "Get Regions example" << endl;
	
	I2 = I1.GlobalThreshold(53);
	//I2.Show();
	Image_lpr::RegionVector REG;
	double factor=(I2.Width()*I2.Height())/(384*286);
	REG = I2.iplGetImageRegions(0,50*factor,700*factor);
	
	//REG.Show();
	for (int i=0;i<REG.size();i++) {
		Image_lpr::Region R=REG[i];
		float error;
		if (R.OffsetY()) error = (float(R.OffsetX() / R.OffsetY())-4.78)*100/4.78;
		else error=100.0;
		error*=(error<0)?-1:1;
		if (error<20.0) 
			//cout << "+ PROB(M) = " << 100.0-prob << " ";
			printf("+ ERROR(M) = %4.3f ",error);
		else
			//cout << "- PROB(M) = " << 100.0-prob << " ";
			printf("  ERROR(M) = %4.3f ",error);
		R.Show();
	}
	//I2.Show();
	//*/
			
	///////////////////////	
	//iplGetPlate example
	///////////////////////
	I1.iplGetPlate3();


	//////////////////
	//Median example
	//////////////////
	/*
	long v[] = {9, 1, 8, 3, 6, 4, 5, 2, 7,14};
	MedianResult Median;;
	median((void *)v,10,32,&Median);
	printf("\n\nEl valor mediana de v es %d",Median.lg);
	//*/

		

	////////////////////////
	// HoughtLines example
	////////////////////////
	//I1.LoadBMP("\\home\\ISA\\imagenes\\lineas.bmp");
	//I1.Show();
	//I1.houghtLinesP(0,I1.Width(),0,I1.Height(),-800,800,-95,95,1,1,3,3,1,20);
	
	cout << endl;
		
	
	////////////////////////
	// getSegment example
	////////////////////////
	//I1.LoadBMP("\\home\\ISA\\imagenes\\lineas.bmp");
	//I1.Show();
	//I1.getSegment(0,640,0,480,298,-2,2,4,20).Show();
	


	///////////////////////////////
	// getGradient example
	///////////////////////////////
	//I1.LoadBMP("\\home\\ISA\\imagenes\\lineas.bmp");
	//NumRows=I1.Height();
	//NumCols=I1.Width();
	//FloatMatrix Angle(NumRows,NumCols);
	//UcharMatrix Mod(NumRows,NumCols);
	//I1.getGradient(Angle,Mod);
	//Image_lpr I3(Angle);
	//I3.Show();
	//Angle.Show();
	
	///////////////////////////////
	// Image_lpr::Segment example
	///////////////////////////////
	//Image_lpr::Segment S1(1,2,3,4,5,6,7),S2;
	//S1.ShowN();
	//S2=S1;
	//S2.ShowN();

		
		
	finish = clock();
	duration = (double)(finish - start)/ CLOCKS_PER_SEC;
	//cout << start << "\t" << finish << "\t" << duration  << "\n";
	printf("\n%i\t%i\t%.30g\n",start,finish,duration);

	//while (!_kbhit());
	getchar();

}

// Para obtener el nombre del tipo
//	const type_info& MiTipo = typeid(LoQueSea);
//	cout << MiTipo.name();
