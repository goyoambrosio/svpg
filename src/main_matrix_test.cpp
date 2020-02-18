/****
  SoftVision. Software for Computer Vision

  Gregorio Ambrosio Cestero (goyo@computer.org)
  System Engineering and Automation Department 
  University of Malaga. Spain                   

  $RCSfile: main_matrixtest.cpp,v $
  $Revision: 1.1 $
  $Date: 2000/01/21 13:04:46 $
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

#include <iostream> //Necessary with CGAL's stlport. Comment for STL-3.2

#include <CVL/TypedMatrix.h>
#include <CVL/TypedVector.h>
#include <CVL/Globals.h>

#include <time.h>
#include <typeinfo.h>

using namespace GAC;
using namespace std;

void sleep( clock_t wait );

void main( int argc, char *argv[] )
{
	clock_t start, finish;
	double  duration;

    start = clock();   

/*************************************************************************\
 *                       Begin Test                                      *
\*************************************************************************/


/*************************************************************************/	


	DoubleMatrix A(5,5);
	Matrix<double> B(5,5);
	Matrix<double> C(4,3),D(3,4);
	DoubleMatrix E(5,4),F(5,4);
	DoubleMatrix G,H;
	Matrix<bool> T(5,4),U(5,4);
	Matrix<double> V(4,5,3);
	UcharMatrix UC(5,4);
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
	
	UC(1,1) = 2;UC(1,2) = 4;UC(1,3) = 7;UC(1,4) = 2;
	UC(2,1) = 5;UC(2,2) = 3;UC(2,3) = 8;UC(2,4) = 2;
	UC(3,1) = 6;UC(3,2) = 2;UC(3,3) = 9;UC(3,4) = 7;
	UC(4,1) = 0;UC(4,2) = 5;UC(4,3) = 3;UC(4,4) = 0;
	UC(5,1) = 1;UC(5,2) = 6;UC(5,3) = 0;UC(5,4) = 3;

//GetBlock
//	cout <<F<< F.GetBlock(1,1,8,5);

//GetCenteredBlock
//	cout <<F<< F.GetCenteredBlock(1,1,2,2);

//SetAround
//	cout << F << F.SetAround(2,3,100);;

//Row,Col
//	cout << F << F.Row(2) << F.Col(2);
//	cout << F << F.Row(10) << F.Col(10);

//Diag,InvDiag
//	cout << F << F.Diag() << F.InvDiag();

//Depth,Height,Width
//	cout << D.Depth() << D.Height() << D.Width() << endl;

// operator>>
//	DoubleMatrix I(3,4);
//	B >> E >> D >> I;
//	B >> E >> D >> I;
//	cout <<I << D << E;	

// operator+
//	cout << B << B + 5 << B + B;
//	B = (double)6 + B;
//	cout << +B;

// operator-
//	cout << B << B - 5 << B - D;
//	B = (double)6 - B;
//	cout << -B;

// operator*,Mult
//	DoubleMatrix R;
//	R.Load("c:\\Goyo\\Mio\\Svawin32\\temp\\R.mat");
//	R.Resize(500,500);
//	cout << R.Height() << "," << R.Width() << endl;
//	R*R;

//	cout << C*D << B*8;
//	cout << D.Mult(D);
//	B = (double)9*B;
//	cout << B;

// operator /,Div
//	cout << B/100;
//	B = (double)2000/B;
//	cout << B;
//	cout << B.Div(B);

// operator ==
//	D = (B==B);
//	cout << D << endl;
//	cout << (C==C) << endl;
//	cout << (C==1) << endl;
//	cout << (2.0==C) << endl;

// operator !=
//	D = (B!=B);
//	cout << D << endl;
//	cout << (C!=C) << endl;
//	cout << (C!=1) << endl;
//	cout << (2.0!=C) << endl;	

// operator &&
//	cout << (T&&U);
//	cout << (T&&true);
//	cout << (T&&false);
//	cout << (true&&T);

// operator ||
//	cout << (T||U);
//	cout << (T||true);
//	cout << (T||false);
//	cout << (true||T);

// operator Equal
//	cout << B.Equal(A) << endl;
//	cout << C.Equal(C) << endl;
//	cout << C.Equal(D) << endl;
//	cout << B.Equal(10) << endl << B.Equal(5.0) << endl;

// Max,Min
//	A[2][3] =  1000;
//	A[3][3] = -1000;
//	cout << A.Max() << endl << A.Min() <<endl;

// Trans
//	cout << D << D.Trans();

// Fortran
//	cout << D << D.Fortran();

// Rot90,Flipud,Fliplr
//	cout << D << D.Rot90() << D.Flipud() << D.Fliplr() <<endl;
//	cout << A << A.Flipud() <<endl;

// Abs, Sign
//	A[2][3] = -5;
//	A[3][3] = -6;
//	cout << A << A.Abs() << A.Sign();

// Sum, SumRows, SumCols
//	cout << A << A.Sum() << endl;
//	cout << A << A.SumRows() << A.SumCols();
//	cout << D << D.Sum() << endl << D.SumRows() << D.SumCols();

// Mean, MeanRows, MeanCols
//	cout << A.Mean() << endl;
//	cout << A << A.MeanRows() << A.MeanCols();
//	cout << D << D.Mean() << endl << D.MeanRows() << D.MeanCols();

// Std, StdRows, StdCols
//	cout << A.StdCols().Std() << endl; //Equivalent in Matlab to std(std(A))
//	cout << A << A.StdRows() << A.StdCols();
//	cout << D << D.Std() << endl << D.StdRows() << D.StdCols();

// Corr
//	cout << A.Corr(A) << endl;

// Conv
//	Matrix<double> R(4,3),S(4,5);

//	R(1,1) = 1;R(1,2) = 1;R(1,3) = 1;
//	R(2,1) = 1;R(2,2) = 1;R(2,3) = 1;
//	R(3,1) = 1;R(3,2) = 1;R(3,3) = 1;
//	R(4,1) = 1;R(4,2) = 1;R(4,3) = 1;

//	S(1,1) = 10;S(1,2) = 10;S(1,3) = 10;S(1,4) = 10;S(1,5) = 10;
//	S(2,1) = 10;S(2,2) = 10;S(2,3) = 10;S(2,4) = 10;S(2,5) = 10;
//	S(3,1) = 10;S(3,2) = 10;S(3,3) = 10;S(3,4) = 10;S(3,5) = 10;
//	S(4,1) = 10;S(4,2) = 10;S(4,3) = 10;S(4,4) = 10;S(4,5) = 10;
	
//	cout << S.Conv(R,1);
//	cout << R.Conv(S,1);

// Gauss
//	cout << A.Gauss(1);

// Show()

//	A.Show();
//	B.Show();
//	C.Show();
//	D.Show();
//	E.Show();
//	F.Show();

//Serialize

//	FILE * stream = OpenSerialize("c:\\Goyo\\Mio\\Svawin32\\temp\\F.mat") ;
//	int count1 = 0;
//	count1 += F.Serialize(stream);
//	CloseSerialize(stream);
//	F.Load("c:\\Goyo\\Mio\\Svawin32\\temp\\F.mat");
//	cout << F << endl;

//Save/Load
//	A.Save("c:\\Goyo\\Mio\\Svawin32\\temp\\A.mat");
//	B.Save("c:\\Goyo\\Mio\\Svawin32\\temp\\B.mat");
//	C.Save("c:\\Goyo\\Mio\\Svawin32\\temp\\C.mat");
//	D.Save("c:\\Goyo\\Mio\\Svawin32\\temp\\D.mat");
//	E.Save("c:\\Goyo\\Mio\\Svawin32\\temp\\E.mat");
//	F.Save("c:\\Goyo\\Mio\\Svawin32\\temp\\F.mat");

//	A.Load("c:\\Goyo\\Mio\\Svawin32\\temp\\A.mat");
//	B.Load("c:\\Goyo\\Mio\\Svawin32\\temp\\B.mat");
//	C.Load("c:\\Goyo\\Mio\\Svawin32\\temp\\C.mat");
//	D.Load("c:\\Goyo\\Mio\\Svawin32\\temp\\D.mat");
//	E.Load("c:\\Goyo\\Mio\\Svawin32\\temp\\E.mat");
//	F.Load("c:\\Goyo\\Mio\\Svawin32\\temp\\F.mat");

//	A.Show();
//	B.Show();
//	C.Show();
//	D.Show();
//	E.Show();
//	F.Show();

// frDepth,frWidth
//	cout << frDepth(D) << endl << frWidth(D) << endl ;

// cout
	cout << F[4][0] << F[4][1] <<F[4][2] <<F[4][3] << endl;
	cout << F(5,1)<< F(5,2)<< F(5,3)<< F(5,4)<<endl;
	cout << F << endl;

// cin
//	G.Resize(2,2);
//	cin >> G;
//	cout << G;

// operator>> (friend)
//	20.0 >> B >> A;
//	cout << A << B;

// operator+ (friend)
//	B = (double)6 + B;
//	cout << B;

// operator- (friend)
//	B = (double)6 - B;
//	cout << B;

// operator* (friend)
//	B = (double)9*B;
//	cout << B;

// operator/ (friend)
//	B = (double)2000/B;
//	cout << B;

// operator== (friend)
//	cout << (2.0==C) << endl;

// operator!= (friend)
//	cout << (2.0!=C) << endl;	

// operator&& (friend)
//	cout << (true&&T);

// operator|| (friend)
//	cout << (true||T);

//Init
//	D.Init();
//	D.Show();

//Resize
//	cout << D;
//	cout << D.Resize(4,5);

//NewSize
//	D.NewSize(6,6);
//	D.Show();

//RemoveAll
//	D.RemoveAll();
//	D.Show();

//SetBlock
//	cout << B.SetBlock(5,5,D);

//SetAll
//	D.SetAll(10);
//	cout << D;

//Load (see Save/Load)

// operator=
//	Matrix<double> I;
//	I = D;
//	cout << I;
//	I = 20.0;
//	cout << I;

// operator<<
//	DoubleMatrix I(3,4);
//	I << D << E << B;
//	cout << I << D << E;	
//	I = D = B;
//	cout << D;	
//	B << C << D << 20;
//	cout << B << C << D;

// operator+=
//	B+=B;
//	cout << B;
//	B+=5;
//	cout << B;

// operator-=
//	B-=1;
//	cout << B;
//	B-=D;
//	cout << B;

// operator*=
//	B*=B;
//	cout << B;
//	B*=2;
//	cout << B;

// operator/=
//	B/=2;
//	cout << B;



/***********************************************\
 *               TypedMatrix                   *
\***********************************************/

//SetRand
//	Matrix<double> R(500,500);
//	DoubleMatrix R(500,500);
//	int Info;
//	R.SetRand('U','S',0.0,2048,2048, 1.0,Info);
//	printf("INFO: %i\n",Info);
//	R.Show();

//LU
//	DoubleMatrix S(2,2);
//	S(1,1)=1;S(1,2)=2;
//	S(2,1)=2;S(2,2)=1;
//	S.LU(Info).Show();
//	printf("INFO: %i\n",Info);

//Inv
//	DoubleMatrix S(2,2);
//	S(1,1)=1;S(1,2)=2;
//	S(2,1)=2;S(2,2)=1;
//	S.Inv(Info).Show();
//	printf("INFO: %i\n",Info);

//	R.Save("c:\\Goyo\\Mio\\Svawin32\\temp\\R.mat");
//	R.Load("c:\\Goyo\\Mio\\Svawin32\\temp\\R.mat");
//	R.Inv(Info).Show();
//	printf("INFO: %i\n",Info);

//SymEig
//	DoubleVector W;
//	DoubleMatrix A;
//	DoubleMatrix Z;
//	int NumEigv;
//	W = R.SymEig('V','U',A,Info);
//	A.Show();
//	W = R.SymEig  ('V','A','U',-0.18,1.5,1,4,NumEigv,Z,Info);
//	printf("NumEigv: %i\n",NumEigv);
//	Z.Show();
//	W.Show();
//	printf("INFO: %i\n",Info);

//operator=
//	A.Resize(1024,2048);
//	C.Resize(1024,2048);
//	start = clock();
//	A=C; // To test DoubleMatrix::operator=
//	C=A; // To test Matrix<double>::operator=
//	finish = clock();
//	C.Show();

//operator= (casting)
//	start = clock();
//	DoubleMatrix(UC).Show();
//	A=UC; // To test casting (UcharMatrix->DoubleMatrix)
//	finish = clock();
//  A.Show();
//  UC.Show();
//  cout << A << UC << endl;

//operator*
//	C.Resize(500,500);
//	start = clock();
//	C=R*R;
//	finish = clock();
//	C.Show();


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
