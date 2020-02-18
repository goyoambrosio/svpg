/****
  SoftVision. Software for Computer Vision

  Gregorio Ambrosio Cestero (goyo@computer.org)
  System Engineering and Automation Department 
  University of Malaga. Spain                   

  $RCSfile: TypedMatrix.h,v $
  $Revision: 1.1 $
  $Date: 2000/01/21 13:05:18 $
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


#if !defined(_TYPEDMATRIX_H_)
#define _TYPEDMATRIX_H_

#include <CVL/Matrix.h>
#include <CVL/TypedVector.h>

namespace GAC
{

/********************************************\
 *    Classes declared in this file         *
\********************************************/

class IntMatrix;
class FloatMatrix;
class DoubleMatrix;
class UcharMatrix;
class BoolMatrix;
class CharMatrix;


/********************************************\
 *                Declarations              *
\********************************************/

class IntMatrix : public Matrix<int>  
{
public:

	IntMatrix ():Matrix<int>(){};
	IntMatrix (size_t Rows, size_t Cols):Matrix<int>(Rows,Cols){};
	IntMatrix (Matrix<int>           &Maux):Matrix<int>(Maux){};
	IntMatrix (Matrix<float>         &Maux);
	IntMatrix (Matrix<double>        &Maux);
	IntMatrix (Matrix<unsigned char> &Maux);
	IntMatrix (Matrix<char>          &Maux);

	operator FloatMatrix();
	operator DoubleMatrix();
	operator UcharMatrix();
	operator CharMatrix();
};

class FloatMatrix : public Matrix<float>  
{
public:
	FloatMatrix ():Matrix<float>(){};
	FloatMatrix (size_t Rows, size_t Cols):Matrix<float>(Rows,Cols){};
	FloatMatrix (Matrix<float>         &Maux):Matrix<float>(Maux){};
	FloatMatrix (Matrix<int>           &Maux);
	FloatMatrix (Matrix<double>        &Maux);
	FloatMatrix (Matrix<unsigned char> &Maux);
	FloatMatrix (Matrix<char>          &Maux);

	operator IntMatrix();
	operator DoubleMatrix();
	operator UcharMatrix();
	operator CharMatrix();
};

class UcharMatrix : public Matrix<unsigned char>  
{
public:
	UcharMatrix ():Matrix<unsigned char>(){};
	UcharMatrix (size_t Rows, size_t Cols):Matrix<unsigned char>(Rows,Cols){};
	UcharMatrix (Matrix<unsigned char> &Maux):Matrix<unsigned char>(Maux){};
	UcharMatrix (Matrix<int>           &Maux);
	UcharMatrix (Matrix<double>        &Maux);
	UcharMatrix (Matrix<float>         &Maux);
	UcharMatrix (Matrix<char>          &Maux);

	operator IntMatrix();
	operator FloatMatrix();
	operator DoubleMatrix();
	operator CharMatrix();
};

class CharMatrix : public Matrix<char>  
{
public:
	CharMatrix ():Matrix<char>(){};
	CharMatrix (size_t Rows, size_t Cols):Matrix<char>(Rows,Cols){};
	CharMatrix (Matrix<char>          &Maux):Matrix<char>(Maux){};
	CharMatrix (Matrix<int>           &Maux);
	CharMatrix (Matrix<double>        &Maux);
	CharMatrix (Matrix<float>         &Maux);
	CharMatrix (Matrix<unsigned char> &Maux);

	operator IntMatrix();
	operator FloatMatrix();
	operator DoubleMatrix();
	operator UcharMatrix();
};

class BoolMatrix : public Matrix<bool>  
{
public:
	BoolMatrix ():Matrix<bool>(){};
	BoolMatrix (size_t Rows, size_t Cols):Matrix<bool>(Rows,Cols){};
	BoolMatrix (Matrix<bool> &Maux):Matrix<bool>(Maux){};
};

class DoubleMatrix : public Matrix<double>  
{
public:
	DoubleMatrix ():Matrix<double>(){};
	DoubleMatrix (size_t Rows, size_t Cols):Matrix<double>(Rows,Cols){};
	DoubleMatrix (Matrix<double>        &Maux):Matrix<double>(Maux){};
	DoubleMatrix (Matrix<int>           &Maux);
	DoubleMatrix (Matrix<float>         &Maux);
	DoubleMatrix (Matrix<unsigned char> &Maux);
	DoubleMatrix (Matrix<char>          &Maux);

	operator IntMatrix();
	operator FloatMatrix();
	operator UcharMatrix();
	operator CharMatrix();


	// GAC_LAPACK based functions
/*
	DoubleMatrix &SetRand (char Dist,char Sym, double Sparse, int Kl, int Ku, double Anorm, int &INFO);
	DoubleMatrix  LU      (int &INFO);
	DoubleMatrix  Inv     (int &INFO);
	DoubleVector  SymEig  (char Jobz,char Uplo,DoubleMatrix &A,int &INFO);
	DoubleVector  SymEig  (char Jobz,char Range,char Uplo,double Vl,double Vu,int Il, int Iu,int &M,DoubleMatrix &Z,int &INFO);
*/

	// Intel PLSuite MKL's CBLAS based functions
	DoubleMatrix & operator=(DoubleMatrix Mr);
	DoubleMatrix & operator*(DoubleMatrix Mr);

};

} //namespace GAC

#endif // !defined(_TYPEDMATRIX_H_)
