/****
  SoftVision. Software for Computer Vision

  Gregorio Ambrosio Cestero (goyo@computer.org)
  System Engineering and Automation Department 
  University of Malaga. Spain                   

  $RCSfile: Matrix.h,v $
  $Revision: 1.1 $
  $Date: 2000/01/21 13:04:50 $
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


#if !defined(_MATRIX_H_)
#define _MATRIX_H_

#include <string>                     //From SGI STL. For ios functions. It's like #include <iostream>
#include <cassert>
#include <stdio.h>					  // for standard i/o functions
#include <Typeinfo>                   // For type_info in Show() function

/********************************************\
 *          Repeated pieces of code         *
\********************************************/

#define _OP(RHS)                        \
	size_t i,j;                         \
	Matrix<TYPE> M(NumRows,NumCols);    \
	for (i=0;i<M.NumRows;i++)           \
		for (j=0;j<M.NumCols;j++)       \
			M.pM[i*M.NumCols + j]=RHS;  \
	return M			

#define _OP2(RHS)							\
	size_t i,j;								\
	Matrix<TYPE> M(Mr.Depth(),Mr.Width());	\
	for (i=0;i<M.Depth();i++)				\
		for (j=0;j<M.Width();j++)			\
			M.pM[i*M.NumCols + j]=RHS;		\
	return M	

#define _OP3(RHS)                         \
	size_t i;                             \
	size_t NumItems = NumRows*NumCols;    \
	for (i=0;i<NumItems;i++)              \
		pM[i] RHS;                        \
	return *this

#define _OP4(RHS)						\
	size_t i,j;							\
	Matrix<TYPE> M(NumRows,NumCols);	\
	for (i=0;i<NumRows;i++)		        \
		for (j=0;j<NumCols;j++)      	\
			M.pM[i*M.NumCols + j]=RHS;	\
	return M;

#define _OP5(RHS)							\
  	size_t i,j;								\
	Matrix<TYPE> M(Mr.NumRows,Mr.NumCols);	\
	for (i=0;i<M.Depth();i++)				\
		for (j=0;j<M.Width();j++)			\
			M.pM[i*M.NumCols + j]=RHS;		\
	return M;					

using namespace std;

namespace GAC
{
/********************************************\
 *                Declarations              *
\********************************************/


template <class TYPE> class Matrix
{

public:
	// Creators
		Matrix();
		Matrix(size_t Rows, size_t Cols);
		Matrix(size_t Rows, size_t Cols, TYPE Val);
		Matrix(const Matrix<TYPE> &Maux);
		
		~Matrix();

	//Accesors
		TYPE*         operator  [](size_t i) const;
		TYPE&         operator  ()(size_t i) const;
	    TYPE&         operator  ()(size_t i, size_t j) const;
		Matrix<TYPE>  GetBlock(size_t i0,size_t j0,size_t iplus,size_t jplus) const;
		Matrix<TYPE>  GetCenteredBlock(size_t i0,size_t j0,size_t M,size_t N) const;
		Matrix<TYPE>  SetAround(size_t m, size_t n, TYPE InitVal) const;
		Matrix<TYPE>  Row(size_t i) const;
		Matrix<TYPE>  Col(size_t j) const;
		Matrix<TYPE>  Diag    () const;
		Matrix<TYPE>  InvDiag () const;
		//Attributes
		size_t Depth () const; //Number of Rows
		size_t Height() const; //The same as Depth
		size_t Width () const; //Number of Cols
		bool   IsSquare() const;    //True if square
		//Operations
		Matrix<TYPE>  operator>>(Matrix<TYPE> &Maux);
		Matrix<TYPE>  operator+ () const;
		Matrix<TYPE>  operator+ (const Matrix<TYPE> &Mright) const;
		Matrix<TYPE>  operator+ (const TYPE Val) const;
		Matrix<TYPE>  operator- () const;
		Matrix<TYPE>  operator- (const Matrix<TYPE> &Mright) const;
		Matrix<TYPE>  operator- (const TYPE Val) const;
		Matrix<TYPE>  operator* (const Matrix<TYPE> &Mright) const;
		Matrix<TYPE>  operator* (const TYPE Val) const;
		Matrix<TYPE>  Mult      (const Matrix<TYPE> &Mright) const;
		Matrix<TYPE>  operator/ (const TYPE Val) const;
		Matrix<TYPE>  Div       (const Matrix<TYPE> &Mright) const;
		Matrix<TYPE>  operator==(const Matrix<TYPE> &Mright) const;		
		Matrix<TYPE>  operator==(const TYPE Val) const;		
		Matrix<TYPE>  operator!=(const Matrix<TYPE> &Mright) const;		
		Matrix<TYPE>  operator!=(const TYPE Val) const;		
		Matrix<TYPE>  operator< (const Matrix<TYPE> &Mright) const;		
		Matrix<TYPE>  operator< (const TYPE Val) const;		
		Matrix<TYPE>  operator> (const Matrix<TYPE> &Mright) const;		
		Matrix<TYPE>  operator> (const TYPE Val) const;		
		Matrix<TYPE>  operator<=(const Matrix<TYPE> &Mright) const;		
		Matrix<TYPE>  operator<=(const TYPE Val) const;		
		Matrix<TYPE>  operator>=(const Matrix<TYPE> &Mright) const;		
		Matrix<TYPE>  operator>=(const TYPE Val) const;		
 		Matrix<TYPE>  operator&&(const Matrix<TYPE> &Mright) const;		
		Matrix<TYPE>  operator&&(const TYPE Val) const;		
		Matrix<TYPE>  operator||(const Matrix<TYPE> &Mright) const;		
		Matrix<TYPE>  operator||(const TYPE Val) const;		
		bool         Equal    (const Matrix<TYPE> &Mright) const;
		bool         Equal    (const TYPE Val) const;
		TYPE         Max      () const;
		TYPE         Min      () const;
		Matrix<TYPE> Trans    () const;
		Matrix<TYPE> Fortran  () const;
		Matrix<TYPE> Rot90    () const;
		Matrix<TYPE> Flipud   () const;
		Matrix<TYPE> Fliplr   () const;
		Matrix<TYPE> Abs      () const;
		Matrix<TYPE> Sign     () const;
		TYPE         Sum      () const;
		Matrix<TYPE> SumRows  () const;
		Matrix<TYPE> SumCols  () const;
		TYPE         Mean     () const;
		Matrix<TYPE> MeanRows () const;
		Matrix<TYPE> MeanCols () const;
		TYPE         Std      () const;
		Matrix<TYPE> StdRows  () const;
		Matrix<TYPE> StdCols  () const;
		TYPE         Corr     (Matrix<TYPE> M2) const;
		Matrix<TYPE> Conv     (Matrix<TYPE> &Mright, unsigned char Size) const;
		Matrix<TYPE> Gauss    (float Sigma);  // To pass to MatrixOperators
		//i/o operations
		void		  Show() const;
//		size_t		  Serialize(FILE * stream) const;
		size_t		  Save(char *FileName) const;
		//Friends
		friend	size_t frDepth(const Matrix<TYPE> &Mleft);
		friend	size_t frWidth(const Matrix<TYPE> &Mleft);
        friend  ostream      &operator<<(ostream &s, const Matrix<TYPE> &Maux);
		friend  istream      &operator>>(istream &s, Matrix<TYPE> &Maux);
		friend	Matrix<TYPE>  operator>>(const TYPE Val, Matrix<TYPE> &Mright);
		friend  Matrix<TYPE>  operator+ (const TYPE Val, Matrix<TYPE> &Mright);
		friend  Matrix<TYPE>  operator- (const TYPE Val, const Matrix<TYPE> &Mright);
		friend	Matrix<TYPE>  operator* (const TYPE Val, const Matrix<TYPE> &Mright);
		friend  Matrix<TYPE>  operator/ (const TYPE Val, const Matrix<TYPE> &Mright);
		friend	Matrix<TYPE>  operator==(const TYPE Val, const Matrix<TYPE> &Mright);		
		friend	Matrix<TYPE>  operator!=(const TYPE Val, const Matrix<TYPE> &Mright);
		friend	Matrix<TYPE>  operator< (const TYPE Val, const Matrix<TYPE> &Mright);
		friend	Matrix<TYPE>  operator> (const TYPE Val, const Matrix<TYPE> &Mright);
		friend	Matrix<TYPE>  operator<=(const TYPE Val, const Matrix<TYPE> &Mright);
		friend	Matrix<TYPE>  operator>=(const TYPE Val, const Matrix<TYPE> &Mright);
		friend	Matrix<TYPE>  operator&&(const TYPE Val, const Matrix<TYPE> &Mright);		
		friend	Matrix<TYPE>  operator||(const TYPE Val, const Matrix<TYPE> &Mright);

	//Manipulators
		Matrix<TYPE> &Init      ();	//Initialize a matrix with zeroes
		Matrix<TYPE> &Resize    (size_t Rows, size_t Cols);
		Matrix<TYPE> &NewSize   (size_t Rows, size_t Cols);
		Matrix<TYPE> &SetBlock  (size_t i0,size_t j0,const Matrix<TYPE> &Maux);
		Matrix<TYPE> &SetAll    (const TYPE Val);
		//i/o operations
		Matrix<TYPE> &Load(char *FileName);
		//Operators
		Matrix<TYPE> &operator= (const Matrix<TYPE> &Maux);
		Matrix<TYPE> &operator= (const TYPE Val);
		Matrix<TYPE> &operator<<(Matrix<TYPE> &Maux);
		Matrix<TYPE> &operator<<(TYPE Val);
		Matrix<TYPE> &operator+=(const Matrix<TYPE> &Mright);
		Matrix<TYPE> &operator+=(const TYPE Val);
		Matrix<TYPE> &operator-=(const Matrix<TYPE> &Mright);
		Matrix<TYPE> &operator-=(const TYPE Val);
		Matrix<TYPE> &operator*=(const Matrix<TYPE> &Mright);
		Matrix<TYPE> &operator*=(const TYPE Val);
		Matrix<TYPE> &operator/=(const TYPE Val);

protected:
	size_t NumRows,NumCols;	//Number of Rows and Columns
	TYPE *pM;				//Matrix representation
	TYPE **pRow;
	TYPE *pM1;				//These point to the same data, but are 1-based
	TYPE **pRow1;

	void Initialize(size_t Rows, size_t Cols);
	void Destroy();
	void Copy(const TYPE *M);
	Matrix<TYPE> &RemoveAll (); //Don't use this function. Testing purpose.
};

//This known bug of the compiler obligate me to include definitions inside header file
//Q128789 BUG: LNK2001 on Member Function When Use Nested Class Template

/********************************************\
 *                Definitions               *
\********************************************/

/************************\
 *      Creators        *
\************************/

template <class TYPE> 
Matrix<TYPE>::Matrix():
	NumRows(0),
	NumCols(0),
	pM(0),
	pRow(0),
	pM1(0),
	pRow1(0)
{

}

template <class TYPE> 
Matrix<TYPE>::Matrix(size_t Rows, size_t Cols)
{
	Initialize(Rows,Cols);
}

template <class TYPE> 
Matrix<TYPE>::Matrix(size_t Rows, size_t Cols, TYPE Val)
{
	Initialize(Rows,Cols);
	*this = Val; // Using overloaded operator
}

//copy-intializer
template <class TYPE> 
Matrix<TYPE>::Matrix(const Matrix<TYPE> &M)
{
	Initialize(M.NumRows,M.NumCols);
	Copy(M.pM);
}

template <class TYPE> 
Matrix<TYPE>::~Matrix()
{
	Destroy();
}

/************************\
 *      Accesors        *
\************************/

template <class TYPE>
inline TYPE* Matrix<TYPE>::operator[](size_t i) const 
{ 
	assert(0<=i);
	assert(i<=NumRows);
	return (pRow[i]);
}

template <class TYPE>
inline TYPE& Matrix<TYPE>::operator()(size_t i) const
{ 
	assert(1<=i);
	assert(i<=NumRows*NumCols);
	return (pRow1[i]);
}

template <class TYPE>
inline TYPE& Matrix<TYPE>::operator()(size_t i, size_t j) const
{ 
	assert(1<=i);
	assert(1<=j);
 	assert(i<=NumRows);
	assert(j<=NumCols);
	return (pRow1[i][j]);
}

//if index is out of scope return 0's
template <class TYPE> 
	Matrix<TYPE> Matrix<TYPE>::GetBlock(size_t i0,size_t j0,size_t iplus,size_t jplus) const
{
	size_t i,j;
	Matrix<TYPE> M(iplus,jplus);
	M.SetAll(0); 
	for (i=0;i<iplus;i++)
		for (j=0;j<jplus;j++)
			if (i+i0>NumRows-1 || j+j0>NumCols-1)
				M.pM[i*M.NumCols + j]= 0;
			else
				M.pM[i*M.NumCols + j]= pM[(i0+i)*NumCols + j0+j];
	return M;
}

//if index is out of scope return 0's
template <class TYPE> 
	Matrix<TYPE> Matrix<TYPE>::GetCenteredBlock(size_t i0,size_t j0,size_t m,size_t n) const
{
	int i,j;
	Matrix<TYPE> M; 
		
	M.Resize(2*m+1,2*n+1);
	for (i=(int)(i0-m);i<=(int)(i0+m);i++)
		for (j=(int)(j0-n);j<=(int)(j0+n);j++){
			if (i<0 || i>NumRows-1 || j<0 || j>NumCols-1)
				M.pM[(i-(i0-m))*M.NumCols + (j-(j0-n))] = 0;
			else
				M.pM[(i-(i0-m))*M.NumCols + (j-(j0-n))] = pM[i*NumCols+j];
		}
	return M;
}

template <class TYPE> 
	Matrix<TYPE> Matrix<TYPE>::SetAround(size_t m, size_t n, TYPE Val) const
{
	Matrix<TYPE> M(NumRows+2*m,NumCols+2*n);
	M=Val;
	M.SetBlock(m,n,*this);
	return M;
}

//if index is out of scope return 0's
template <class TYPE> 
	Matrix<TYPE> Matrix<TYPE>::Row(size_t i) const
{
	Matrix<TYPE> M(1,NumCols);
	M = GetBlock(i,0,1,NumCols);
	return M;
}

//if index is out of scope return 0's
template <class TYPE> 
	Matrix<TYPE> Matrix<TYPE>::Col(size_t j) const
{
	Matrix<TYPE> M(NumRows,1);
	M = GetBlock(0,j,NumRows,1);
	return M;
}

template <class TYPE> 
	Matrix<TYPE> Matrix<TYPE>::Diag() const
{
	Matrix<TYPE> M(1,NumCols);
	size_t j;
	for (j=0;j<NumCols;j++)
		M.pM[j]=pM[j*NumCols + j];
	return M;
}

template <class TYPE> 
	Matrix<TYPE> Matrix<TYPE>::InvDiag() const
{
	Matrix<TYPE> M(1,NumCols);
	size_t i;
	for (i=0;i<NumRows;i++)
		M.pM[i]=pM[(NumRows-1-i)*NumCols + i];
	return M;
}


//Attributes 

template <class TYPE> 
size_t Matrix<TYPE>::Depth() const
	{return NumRows;}

template <class TYPE> 
size_t Matrix<TYPE>::Height() const
	{return NumRows;}

template <class TYPE> 
size_t Matrix<TYPE>::Width() const
	{return NumCols;}

template <class TYPE> 
bool Matrix<TYPE>::IsSquare() const
	{return (NumRows == NumCols);}

//Operations

template <class TYPE> 
	 Matrix<TYPE> Matrix<TYPE>::operator>>(Matrix<TYPE> &M)
{
	assert(NumRows == M.NumRows && NumCols == M.NumCols); 
	M = *this;
	return M;
}

template <class TYPE> 
	Matrix<TYPE> Matrix<TYPE>::operator+() const
	{return *this;}

template <class TYPE> 
	Matrix<TYPE> Matrix<TYPE>::operator+(const Matrix<TYPE> &Mr) const
{
	assert(NumRows == Mr.NumRows && NumCols == Mr.NumCols);
	_OP(pM[i*NumCols + j]+Mr.pM[i*Mr.NumCols + j]);
}

template <class TYPE> 
	Matrix<TYPE> Matrix<TYPE>::operator+(const TYPE Val) const
	{_OP(pM[i*NumCols + j]+Val);}

template <class TYPE> 
	Matrix<TYPE> Matrix<TYPE>::operator-() const
	{_OP(-pM[i*NumCols + j]);}

template <class TYPE> 
	Matrix<TYPE> Matrix<TYPE>::operator-(const Matrix<TYPE> &Mr) const
{
	assert(NumRows == Mr.NumRows && NumCols == Mr.NumCols);
	_OP(pM[i*NumCols + j]-Mr.pM[i*Mr.NumCols + j]);
}

template <class TYPE> 
	Matrix<TYPE> Matrix<TYPE>::operator-(const TYPE Val) const
	{_OP(pM[i*NumCols + j]-Val);}

template <class TYPE> 
	Matrix<TYPE> Matrix<TYPE>::operator*(const Matrix<TYPE> &Mr) const
{
	Matrix<TYPE> Maux(NumRows,Mr.NumCols);
	size_t i,j,k;
	TYPE Sum;    //Use this var to save memory acceses

//	if (NumCols != Mr.NumRows) throw Abort(1);
	assert (NumCols == Mr.NumRows);

	for (i=0;i<NumRows;i++)
		for (j=0;j<Mr.NumCols;j++){
			Sum = 0;
			for (k=0;k<NumCols;k++)
				Sum += pM[i*NumCols + k]*Mr.pM[k*Mr.NumCols + j];
			Maux.pM[i*Maux.NumCols + j] = Sum;
		}
	return Maux;
}

template <class TYPE> 
	Matrix<TYPE> Matrix<TYPE>::operator*(const TYPE Val) const
	{_OP(pM[i*NumCols + j]*Val);}

template <class TYPE> 
	Matrix<TYPE> Matrix<TYPE>::Mult(const Matrix<TYPE> &Mr) const
{
	assert(NumRows == Mr.NumRows && NumCols == Mr.NumCols);
	_OP(pM[i*NumCols + j]*Mr.pM[i*Mr.NumCols + j]);
}

template <class TYPE> 
	Matrix<TYPE> Matrix<TYPE>::operator/(const TYPE Val) const
	{_OP(pM[i*NumCols + j]/Val);}

template <class TYPE> 
	Matrix<TYPE> Matrix<TYPE>::Div(const Matrix<TYPE> &Mr) const
{
	assert(NumRows == Mr.NumRows && NumCols == Mr.NumCols);
	_OP(pM[i*NumCols + j]/Mr.pM[i*Mr.NumCols + j]);
}

template <class TYPE> 
	Matrix<TYPE> Matrix<TYPE>::operator==(const Matrix<TYPE> &Mr) const
{
	assert(NumRows == Mr.NumRows && NumCols == Mr.NumCols);
	_OP4((pM[i*NumCols + j]==Mr.pM[i*Mr.NumCols + j]));
}

template <class TYPE> 
	Matrix<TYPE> Matrix<TYPE>::operator==(const TYPE Val) const
	{_OP4((pM[i*NumCols + j]==Val));}

template <class TYPE> 
	Matrix<TYPE> Matrix<TYPE>::operator!=(const Matrix<TYPE> &Mr) const
{
	assert(NumRows == Mr.NumRows && NumCols == Mr.NumCols);
	_OP4((pM[i*NumCols + j]!=Mr.pM[i*Mr.NumCols + j]));
}

template <class TYPE> 
	Matrix<TYPE> Matrix<TYPE>::operator!=(const TYPE Val) const
	{_OP4((pM[i*NumCols + j]!=Val));}

template <class TYPE> 
	Matrix<TYPE> Matrix<TYPE>::operator<(const Matrix<TYPE> &Mr) const
{
	assert(NumRows == Mr.NumRows && NumCols == Mr.NumCols);
	_OP4((pM[i*NumCols + j]<Mr.pM[i*Mr.NumCols + j]));
}

template <class TYPE> 
	Matrix<TYPE> Matrix<TYPE>::operator<(const TYPE Val) const
	{_OP4((pM[i*NumCols + j]<Val));}

template <class TYPE> 
	Matrix<TYPE> Matrix<TYPE>::operator>(const Matrix<TYPE> &Mr) const
{
	assert(NumRows == Mr.NumRows && NumCols == Mr.NumCols);
	_OP4((pM[i*NumCols + j]>Mr.pM[i*Mr.NumCols + j]));
}

template <class TYPE> 
	Matrix<TYPE> Matrix<TYPE>::operator>(const TYPE Val) const
	{_OP4((pM[i*NumCols + j]>Val));}

template <class TYPE> 
	Matrix<TYPE> Matrix<TYPE>::operator<=(const Matrix<TYPE> &Mr) const
{
	assert(NumRows == Mr.NumRows && NumCols == Mr.NumCols);
	_OP4((pM[i*NumCols + j]<=Mr.pM[i*Mr.NumCols + j]));
}

template <class TYPE> 
	Matrix<TYPE> Matrix<TYPE>::operator<=(const TYPE Val) const
	{_OP4((pM[i*NumCols + j]<=Val));}

template <class TYPE> 
	Matrix<TYPE> Matrix<TYPE>::operator>=(const Matrix<TYPE> &Mr) const
{
	assert(NumRows == Mr.NumRows && NumCols == Mr.NumCols);
	_OP4((pM[i*NumCols + j]>=Mr.pM[i*Mr.NumCols + j]));
}

template <class TYPE> 
	Matrix<TYPE> Matrix<TYPE>::operator>=(const TYPE Val) const
	{_OP4((pM[i*NumCols + j]>=Val));}

template <class TYPE> 
	Matrix<TYPE> Matrix<TYPE>::operator&&(const Matrix<TYPE> &Mr) const
{
	assert(NumRows == Mr.NumRows && NumCols == Mr.NumCols);
	_OP4((pM[i*NumCols + j]&&Mr.pM[i*Mr.NumCols + j]));
}

template <class TYPE> 
	Matrix<TYPE> Matrix<TYPE>::operator&&(const TYPE Val) const
	{_OP4((pM[i*NumCols + j]&&Val));}

template <class TYPE> 
	Matrix<TYPE> Matrix<TYPE>::operator||(const Matrix<TYPE> &Mr) const
{
	assert(NumRows == Mr.NumRows && NumCols == Mr.NumCols);
	_OP4((pM[i*NumCols + j]||Mr.pM[i*Mr.NumCols + j]));
}

template <class TYPE> 
	Matrix<TYPE> Matrix<TYPE>::operator||(const TYPE Val) const
	{_OP4((pM[i*NumCols + j]||Val));}

template <class TYPE> 
	bool Matrix<TYPE>::Equal(const Matrix<TYPE> &Mr) const
{
	size_t i,j;							
	if((NumRows != Mr.NumRows) || (NumCols != Mr.NumCols)) return false;
	for (i=0;i<NumRows;i++)		
		for (j=0;j<NumCols;j++)	
			if (pM[i*NumCols + j]!=Mr.pM[i*Mr.NumCols + j])
				return false;
	return true;		
}

template <class TYPE> 
	bool Matrix<TYPE>::Equal(const TYPE Val) const
{
	size_t i,j;							
	for (i=0;i<NumRows;i++)		
		for (j=0;j<NumCols;j++)	
			if (pM[i*NumCols + j]!=Val)
				return false;
	return true;		
}

template <class TYPE> 
	TYPE Matrix<TYPE>::Max() const
{
	TYPE ValMax = pM[0];
	size_t i,j;
	for (i=0;i<NumRows;i++)		
		for (j=0;j<NumCols;j++)	
			if (pM[i*NumCols + j]>ValMax)
				ValMax = pM[i*NumCols + j];
	return ValMax;		
}

template <class TYPE> 
	TYPE Matrix<TYPE>::Min() const
{
	TYPE ValMin = pM[0];
	size_t i,j;
	for (i=0;i<NumRows;i++)		
		for (j=0;j<NumCols;j++)	
			if (pM[i*NumCols + j]<ValMin)
				ValMin = pM[i*NumCols + j];
	return ValMin;		
}

template <class TYPE> 
	Matrix<TYPE> Matrix<TYPE>::Trans() const
{	size_t i,j;
	Matrix<TYPE> M(NumCols,NumRows);
	for (i=0;i<NumRows;i++)
		for (j=0;j<NumCols;j++)
			M.pM[j*M.NumCols + i]=pM[i*NumCols + j];
	return M;
}

template <class TYPE>
Matrix<TYPE> Matrix<TYPE>::Fortran() const
{
	return Trans();
}

template <class TYPE>
Matrix<TYPE> Matrix<TYPE>::Rot90() const
{
	size_t			i,j;
	Matrix<TYPE>	M(NumCols,NumRows);
	for (i=0;i<NumRows;i++)
		for (j=0;j<NumCols;j++)
			M.pM[j*M.NumCols + i] = pM[i*NumCols + (NumCols - j -1)];
	return M;
}

template <class TYPE>
Matrix<TYPE> Matrix<TYPE>::Flipud() const
{
	size_t			i,j;
	Matrix<TYPE>	M(NumRows,NumCols);
	for (i=0;i<NumRows;i++)
		for (j=0;j<NumCols;j++)
			M.pM[(NumRows-1-i)*M.NumCols + j] = pM[i*NumCols + j];
	return M;
}

template <class TYPE>
Matrix<TYPE> Matrix<TYPE>::Fliplr() const
{
	size_t			i,j;
	Matrix<TYPE>	M(NumRows,NumCols);
	for (i=0;i<NumRows;i++)
		for (j=0;j<NumCols;j++)
			M.pM[i*M.NumCols + (NumCols-1-j)] = pM[i*NumCols + j];
	return M;
}

template <class TYPE>
Matrix<TYPE> Matrix<TYPE>::Abs() const
{
	size_t			i,j;
	Matrix<TYPE>	M(NumRows,NumCols);
	for (i=0;i<NumRows;i++)
		for (j=0;j<NumCols;j++)
			if (pM[i*NumCols + j] < 0)
				M.pM[i*M.NumCols + j] = -pM[i*NumCols + j];
			else
				M.pM[i*M.NumCols + j] =  pM[i*NumCols + j];
	return M;
}

template <class TYPE>
Matrix<TYPE> Matrix<TYPE>::Sign() const
{
	size_t			i,j;
	Matrix<TYPE>	M(NumRows,NumCols);
	for (i=0;i<NumRows;i++)
		for (j=0;j<NumCols;j++)
			if (pM[i*NumCols + j] < 0)
				M.pM[i*M.NumCols + j] = (TYPE)-1;
			else if (pM[i*NumCols + j] > 0)
				M.pM[i*M.NumCols + j] = (TYPE) 1;
			else
				M.pM[i*M.NumCols + j] = 0;
	return M;
}

template <class TYPE> 
	TYPE Matrix<TYPE>::Sum() const
{
	TYPE Sum=0;
	size_t i;
	size_t NumItems = NumRows*NumCols;

	for (i=0;i<NumItems;i++)		
			Sum += pM[i];
	return Sum;		
}

template <class TYPE> 
	Matrix<TYPE> Matrix<TYPE>::SumRows() const
{
	TYPE Sum=0;
	size_t i,j;
	Matrix<TYPE> M(NumRows,1);
	for (i=0;i<NumRows;i++){		
		for (j=0;j<NumCols;j++)	
			Sum += pM[i*NumCols + j];
		M.pM[i*M.NumCols]=Sum;
		Sum=0;
	}
	return M;		
}

template <class TYPE> 
	Matrix<TYPE> Matrix<TYPE>::SumCols() const
{
	TYPE Sum=0;
	size_t i,j;
	Matrix<TYPE> M(1,NumCols);
	for (j=0;j<NumCols;j++){
		for (i=0;i<NumRows;i++)		
			Sum += pM[i*NumCols + j];
		M.pM[j]=Sum;
		Sum=0;
	}
	return M;		
}

template <class TYPE> 
	TYPE Matrix<TYPE>::Mean() const
{
	TYPE Mean=0;
	size_t i;
	size_t NumItems = NumRows*NumCols;

	for (i=0;i<NumItems;i++)		
			Mean += pM[i];
	Mean /= NumItems;
	return Mean;		
}

template <class TYPE> 
	Matrix<TYPE> Matrix<TYPE>::MeanRows() const
{
	TYPE Mean=0;
	size_t i,j;
	Matrix<TYPE> M(NumRows,1);
	for (i=0;i<NumRows;i++){		
		for (j=0;j<NumCols;j++)	
			Mean += pM[i*NumCols + j];
		M[i][0]=Mean/NumCols;
		Mean=0;
	}
	return M;
}

template <class TYPE> 
	Matrix<TYPE> Matrix<TYPE>::MeanCols() const
{
	TYPE Mean=0;
	size_t i,j;
	Matrix<TYPE> M(1,NumCols);
	for (j=0;j<NumCols;j++){
		for (i=0;i<NumRows;i++)		
			Mean += pM[i*NumCols + j];
		M[0][j]=Mean/NumRows;
		Mean=0;
	}
	return M;		
}

template <class TYPE> 
	TYPE Matrix<TYPE>::Std() const
{
	TYPE Std =0;
	TYPE Mean=0;
	size_t i;
	size_t NumItems = NumRows*NumCols;

	Mean = Matrix<TYPE>::Mean();

	for (i=0;i<NumItems;i++)		
		Std += pow(pM[i]-Mean,2);
	Std /= NumItems-1;
	return sqrt(Std);		
}

template <class TYPE> 
	Matrix<TYPE> Matrix<TYPE>::StdRows() const
{
	Matrix<TYPE> MeanRows;
	size_t i,j;
	Matrix<TYPE> M(NumRows,1);
	TYPE Std =0;

	MeanRows = Matrix<TYPE>::MeanRows();
	for (i=0;i<NumRows;i++){		
		Std=0;
		for (j=0;j<NumCols;j++)	
			Std += pow(pM[i*NumCols + j]-MeanRows.pM[i*MeanRows.NumCols],2);
		M.pM[i*M.NumCols]=sqrt(Std/(NumCols-1));
	}
	return M;		
}

template <class TYPE> 
	Matrix<TYPE> Matrix<TYPE>::StdCols() const
{
	Matrix<TYPE> MeanCols;
	size_t i,j;
	Matrix<TYPE> M(1,NumCols);
	TYPE Std =0;

	MeanCols = Matrix<TYPE>::MeanCols();
	for (j=0;j<NumCols;j++){
		Std=0;
		for (i=0;i<NumRows;i++)		
			Std += pow(pM[i*NumCols + j]-MeanCols.pM[j],2);
		M.pM[j]=sqrt(Std/(NumRows-1));
	}
	return M;		
}

template <class TYPE> 
	TYPE Matrix<TYPE>::Corr(Matrix<TYPE> M2) const
{
	Matrix<TYPE> M1;
	TYPE Corr = 0;

	assert(NumRows == M2.NumRows && NumCols == M2.NumCols);

	M1 = *this;

	//From Matlab 5.1 Image Toolbox
	M1 -= M1.Mean();
	M2 -= M2.Mean();

	Corr = (M1.Mult(M2)).Sum()/sqrt((M1.Mult(M1)).Sum()*(M2.Mult(M2)).Sum());

	return Corr;		
}

// Size:
//   0 : Return full convolution (NumRows + Mr.NumRows - 1, NumCols + Mr.NumCols - 1)
//   1 : Return the central part of convolution (NumRows,NumCols)
template <class TYPE>
Matrix<TYPE> Matrix<TYPE>::Conv(Matrix<TYPE> &Mr,unsigned char Size) const
{
	int 			i,j,ii,jj;
	size_t			dNumRows,dNumCols;
	TYPE Sum;

	dNumRows=Mr.NumRows/2;
	dNumCols=Mr.NumCols/2;

	Matrix<TYPE>    MConv(NumRows+Mr.NumRows-1,NumCols+Mr.NumCols-1);
	Matrix<TYPE>    M    (*this);
	M=M.SetAround(Mr.NumRows-1,Mr.NumCols-1,0); //Same dimensions as MConv

	for (i=0;i<M.NumRows-Mr.NumRows+1;i++)		
		for (j=0;j<M.NumCols-Mr.NumCols+1;j++)	{
			Sum = 0;
			for (ii=0;ii<Mr.NumRows;ii++)
				for (jj=0;jj<Mr.NumCols;jj++)
					Sum+=Mr.pM[ii*Mr.NumCols + jj] * M.pM[(i+ii)*M.NumCols + (j+jj)];
			MConv.pM[i*MConv.NumCols + j]=Sum;
		}
	if (!Size) return MConv;
	else return MConv.GetBlock(dNumRows,dNumCols,NumRows,NumCols);
}

template <class TYPE>
Matrix<TYPE> Matrix<TYPE>::Gauss(float Sigma)
{
	size_t			i,j;
	Matrix<TYPE>	M(NumRows,NumCols);
	double			Sigma2;
	double			pi = 3.1415926535897;

	Sigma2 = pow(Sigma,2.0);
	for (i=0;i<NumRows;i++)
		for (j=0;j<NumCols;j++)
				M.pM[i*M.NumCols + j] = exp(-pow(pM[i*NumCols + j],2.0)/(2.0*Sigma2))/(2.0*pi*Sigma2);
	return M;
}

//i/o operations

template <class TYPE> 
	void Matrix<TYPE>::Show() const
{

	for (size_t i=0;i<NumRows;i++){
		for (size_t j=0;j<NumCols;j++){
			const type_info& MyType = typeid(TYPE);
//printf("(i,j):%i,%i\n",i,j);
			if (!(strcmp(MyType.name(),"unsigned char") &&
				  strcmp(MyType.name(),"char")          &&
				  strcmp(MyType.name(),"unsigned int")  &&
				  strcmp(MyType.name(),"int")           ))
					printf("%i\t",(int)pM[i*NumCols+j]);
			else if (!(strcmp(MyType.name(),"double")   &&
				       strcmp(MyType.name(),"float")    ))
					printf("%#4.4f\t",pM[i*NumCols+j]);	
		}
		printf("\n");
	}
	printf("\n");
}
/*
template <class TYPE>
	size_t Matrix<TYPE>::Serialize(FILE * stream) const
{
	size_t i,j;
	size_t count   = 0;

	count += sizeof(size_t)*fwrite(&NumRows, sizeof(size_t),1,stream);
	count += sizeof(size_t)*fwrite(&NumCols, sizeof(size_t),1,stream);

	for (j=0;j<NumCols;j++)
		for (i=0;i<NumRows;i++)
		{
			count += sizeof(TYPE)*fwrite(&pM[i*NumCols+j], sizeof(TYPE),1,stream);
			//cout << "(" << i << "," << j << ") = " << M[i][j] << endl;
		}
		
	return count;
}
*/
template <class TYPE> 
	size_t Matrix<TYPE>::Save(char *FileName) const
{
	size_t i,j;
	FILE *stream;
	size_t NumWritten = 0;
	stream = fopen(FileName,"wb");

	NumWritten += fwrite(&NumRows, sizeof(size_t),1,stream);
	NumWritten += fwrite(&NumCols, sizeof(size_t),1,stream);

	for (j=0;j<NumCols;j++)
		for (i=0;i<NumRows;i++)
		{
			NumWritten += fwrite(&pM[i*NumCols+j], sizeof(TYPE),1,stream);
		}
		
	fclose (stream);
	return NumWritten;

}

//Friends

template <class TYPE> 
size_t frDepth(const Matrix<TYPE> &Mleft)
	{return Mleft.NumRows;}

template <class TYPE> 
size_t frWidth(const Matrix<TYPE> &Mleft)
	{return Mleft.NumCols;}

template <class TYPE> 
	ostream &operator<<(ostream &s, Matrix<TYPE> &M)
{

	for (size_t i=0;i<M.Height();i++){
		for (size_t j=0;j<M.Width();j++){
			const type_info& MyType = typeid(TYPE);
			//cout << MyType.name();
			if (!strcmp(MyType.name(),"unsigned char"))  //This is for unsigned char matrix
					s<<(int)M[i][j]<<"\t";	
			else
					s<<M[i][j]<<"\t";	
		}
		s<<endl;
	}
	s<<endl;
	return s;
}

template <class TYPE> 
	istream &operator>>(istream &s, Matrix<TYPE> &M)
{

	for (size_t i=0;i<M.Height();i++){
		for (size_t j=0;j<M.Width();j++){
			s>>M[i][j];
		}
	}
	return s;
}

template <class TYPE> 
	Matrix<TYPE>  operator>> (const TYPE Val, Matrix<TYPE> &Mr)
{
	Mr = Val;
	return Mr;
}

template <class TYPE> 
	Matrix<TYPE> operator+(const TYPE Val, Matrix<TYPE> &Mr)
	{_OP2(Mr.pM[i*Mr.NumCols + j]+Val);}

template <class TYPE> 
	Matrix<TYPE> operator-(const TYPE Val, const Matrix<TYPE> &Mr)
	{_OP2(Val-Mr.pM[i*Mr.NumCols + j]);}

template <class TYPE> 
	Matrix<TYPE> operator*(const TYPE Val, const Matrix<TYPE> &Mr)
	{_OP2(Mr.pM[i*Mr.NumCols + j]*Val);}

template <class TYPE> 
	Matrix<TYPE> operator/(const TYPE Val, const Matrix<TYPE> &Mr)
	{_OP2(Val/Mr.pM[i*Mr.NumCols + j]);}

template <class TYPE> 
	Matrix<TYPE> operator==(const TYPE Val,const Matrix<TYPE> &Mr)
	{_OP5((Val==Mr.pM[i*Mr.NumCols + j]));}

template <class TYPE> 
	Matrix<TYPE> operator!=(const TYPE Val, const Matrix<TYPE> &Mr)
	{_OP5((Val!=Mr.pM[i*Mr.NumCols + j]));}

template <class TYPE> 
	Matrix<TYPE> operator<(const TYPE Val, const Matrix<TYPE> &Mr)
	{_OP5((Val<Mr.pM[i*Mr.NumCols + j]));}

template <class TYPE> 
	Matrix<TYPE> operator>(const TYPE Val, const Matrix<TYPE> &Mr)
	{_OP5((Val>Mr.pM[i*Mr.NumCols + j]));}

template <class TYPE> 
	Matrix<TYPE> operator<=(const TYPE Val, const Matrix<TYPE> &Mr)
	{_OP5((Val<=Mr.pM[i*Mr.NumCols + j]));}

template <class TYPE> 
	Matrix<TYPE> operator>=(const TYPE Val, const Matrix<TYPE> &Mr)
	{_OP5((Val>=Mr.pM[i*Mr.NumCols + j]));}

template <class TYPE> 
	Matrix<TYPE> operator&&(const TYPE Val, const Matrix<TYPE> &Mr)
	{_OP5((Val&&Mr.pM[i*Mr.NumCols + j]));}

template <class TYPE> 
	Matrix<TYPE> operator||(const TYPE Val, const Matrix<TYPE> &Mr)
	{_OP5((Val||Mr.pM[i*Mr.NumCols + j]));}

/************************\
 *      Manipulators    *
\************************/

template <class TYPE>
	Matrix<TYPE> &Matrix<TYPE>::Init()
{
	*this=0; //Using overloaded operator
	return *this;
}

template <class TYPE>
	Matrix<TYPE> &Matrix<TYPE>::Resize(size_t Rows, size_t Cols)
{
	size_t i,j;
	Matrix <TYPE> M(Rows,Cols);

	M.Init();

	if (M.NumRows > NumRows)
		if (M.NumCols > NumCols)
			for (i=0;i<NumRows;i++){
				for (j=0;j<NumCols;j++){
					M.pM[i*M.NumCols + j]=pM[i*NumCols+j];
				}
			}
		else
			for (i=0;i<NumRows;i++)
				for (j=0;j<M.NumCols;j++)
					M.pM[i*M.NumCols + j]=pM[i*NumCols+j];
	else
		if (M.NumCols > NumCols)
			for (i=0;i<M.NumRows;i++)
				for (j=0;j<NumCols;j++)
					M.pM[i*M.NumCols + j]=pM[i*NumCols+j];
		else
			for (i=0;i<M.NumRows;i++)
				for (j=0;j<M.NumCols;j++)
					M.pM[i*M.NumCols + j]=pM[i*NumCols+j];

	*this=M; //Using overloaded operator, i.e. Destroy -> Initialize -> Copy
	return *this;

}

template <class TYPE>
	Matrix<TYPE> &Matrix<TYPE>::NewSize(size_t Rows, size_t Cols)
{
	if (NumRows==Rows && NumCols==Cols) return *this;
	else {
		Destroy();
		Initialize(Rows, Cols);
		return *this;
	}
}

template <class TYPE> 
	Matrix<TYPE> &Matrix<TYPE>::SetBlock(size_t i0,size_t j0,const Matrix<TYPE> &Mr)
{
	size_t i,j;
	size_t NewNumRows,NewNumCols;

	NewNumRows = Mr.NumRows + i0;
	NewNumCols = Mr.NumCols + j0;

	if (NewNumRows > NumRows || NewNumCols > NumCols) Resize(NewNumRows,NewNumCols);

	for (i=0;i<Mr.NumRows;i++)
		for (j=0;j<Mr.NumCols;j++)
			pM[(i0+i)*NumCols + j0+j]=Mr.pM[i*Mr.NumCols + j];
	return *this;
}

template <class TYPE> 
	Matrix<TYPE> &Matrix<TYPE>::SetAll(const TYPE Val)
{
	size_t i;
	size_t NumItems = NumRows*NumCols;
	for (i=0;i<NumItems;i++)
		pM[i]=Val;
	return *this;
}

//i/o operations

template <class TYPE> 
	Matrix<TYPE> &Matrix<TYPE>::Load(char *FileName)
{
	size_t i,j;
	FILE *stream;
	size_t NumRead = 0;
	stream = fopen(FileName,"rb");

	Destroy();

	NumRead += fread(&NumRows, sizeof(size_t),1,stream);
	NumRead += fread(&NumCols, sizeof(size_t),1,stream);

	Initialize(NumRows,NumCols);

	for (j=0;j<NumCols;j++)
		for (i=0;i<NumRows;i++)
			NumRead += fread(&pM[i*NumCols+j], sizeof(TYPE),1,stream);

	fclose (stream);
	return *this;
}	

//Operators

template <class TYPE> 
	Matrix<TYPE> &Matrix<TYPE>::operator=(const Matrix<TYPE> &M)
{
	if (pM == M.pM) return *this;
	if (NumRows == M.NumRows && NumCols==M.NumCols) {
		Copy(M.pM);
	}
	else{
		Destroy();
		Initialize(M.NumRows,M.NumCols);
		Copy(M.pM);
	}
	return *this;
}

template <class TYPE> 
	Matrix<TYPE> &Matrix<TYPE>::operator=(const TYPE Val)
	{_OP3(=Val);}

template <class TYPE> 
	Matrix<TYPE> &Matrix<TYPE>::operator<<(Matrix<TYPE> &M)
{
	*this = M;
	return M;
}

template <class TYPE> 
	Matrix<TYPE> &Matrix<TYPE>::operator<<( TYPE Val)
{
	*this = Val;
	return *this;
}

template <class TYPE> 
	Matrix<TYPE> &Matrix<TYPE>::operator+=(const Matrix<TYPE> &Mr)
{
	assert(NumRows == Mr.NumRows && NumCols == Mr.NumCols);
	_OP3(+=Mr.pM[i]);
}

template <class TYPE> 
	Matrix<TYPE> &Matrix<TYPE>::operator+=(const TYPE Val)
	{_OP3(+=Val);}

template <class TYPE> 
	Matrix<TYPE> &Matrix<TYPE>::operator-=(const Matrix<TYPE> &Mr)
{
	assert(NumRows == Mr.NumRows && NumCols == Mr.NumCols);
	_OP3(-=Mr.pM[i]);
}

template <class TYPE> 
	Matrix<TYPE> &Matrix<TYPE>::operator-=(const TYPE Val)
	{_OP3(-=Val);}

template <class TYPE> 
	Matrix<TYPE> &Matrix<TYPE>::operator*=(const Matrix<TYPE> &Mr)
{
	assert(NumRows == Mr.NumRows && NumCols == Mr.NumCols);
	_OP3(*=Mr.pM[i]);
}

template <class TYPE> 
	Matrix<TYPE> &Matrix<TYPE>::operator*=(const TYPE Val)
	{_OP3(*=Val);}

template <class TYPE> 
	Matrix<TYPE> &Matrix<TYPE>::operator/=(const TYPE Val)
	{_OP3(/=Val);}


/********************************************\
 *         Protected Definitions            *
\********************************************/

template <class TYPE> 
void Matrix<TYPE>::Initialize(size_t Rows, size_t Cols)
{
	size_t NumItems = Rows*Cols;
	TYPE* p;

	NumRows=Rows;
	NumCols=Cols;

	pM    = new TYPE  [NumItems];
	pRow  = new TYPE* [NumRows];
	pRow1 = new TYPE* [NumRows];

	assert(pM    != NULL);
	assert(pRow  != NULL);
	assert(pRow1 != NULL);

	p = pM;
	pM1 = pM -1;

	for (size_t i=0;i<NumRows;i++){
		pRow[i] = p;
		pRow1[i] = p-1;
		p += NumCols;
	}

	pRow1--;

}

template <class TYPE> 
void Matrix<TYPE>::Destroy()
{
	if (pM==NULL) return;
	else{
		delete[] (pM);
		delete[] (pRow);
		pRow1++;
		delete[] (pRow1);
	}
}

template <class TYPE> 
void Matrix<TYPE>::Copy(const TYPE *M)
{
	size_t NumItems = NumRows*NumCols;

	for (size_t i=0;i<NumItems;i++){
		pM[i]=M[i];
	}
}


template <class TYPE>
	Matrix<TYPE> &Matrix<TYPE>::RemoveAll()
{
	Destroy();
	NumRows = NumCols = 0;
	return *this;
}

} //namespace GAC

#undef _OP
#undef _OP1
#undef _OP2
#undef _OP3
#undef _OP4
#undef _OP5


#endif // !defined(_MATRIX_H_)

