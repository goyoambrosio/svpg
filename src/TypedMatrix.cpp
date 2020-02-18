/****
  SoftVision. Software for Computer Vision

  Gregorio Ambrosio Cestero (goyo@computer.org)
  System Engineering and Automation Department 
  University of Malaga. Spain                   

  $RCSfile: TypedMatrix.cpp,v $
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


// The debugger can't handle symbols more than 255 characters long.
// STL often creates symbols longer than that.
// When symbols are longer than 255 characters, the warning is disabled.
#pragma warning(disable:4786)

#include <limits>
#include <time.h>

#include <CVL/Globals.h>
#include <CVL/Lapack.h>
#include <CVL/TypedMatrix.h>

#include <cblas.h> //Intel PL suite

#define _CAST_OP(CLASS,TYPE)			     \
	size_t i,j;                              \
	CLASS Maux(NumRows,NumCols);		     \
    for (i=0;i<Maux.Depth();i++){            \
        for (j=0;j<Maux.Width();j++){        \
		    Maux[i][j]=(TYPE)pM[i*NumCols + j];    \
        }                                    \
	}                                        \
	return Maux;

#define _CONST(TYPE)				         \
	size_t i,j;                              \
    Destroy();                               \
	Initialize(Maux.Depth(),Maux.Width());   \
    for (i=0;i<Maux.Depth();i++){            \
        for (j=0;j<Maux.Width();j++){        \
		    pM[i*NumCols + j]=(TYPE)Maux[i][j];    \
        }                                    \
	}                                        

using namespace GAC;

/********************************************\
 *                Definitions               *
\********************************************/

// <int>

IntMatrix::IntMatrix (Matrix<float>   &Maux)
{_CONST(int)}

IntMatrix::IntMatrix (Matrix<double>   &Maux)
{_CONST(int)}

IntMatrix::IntMatrix (Matrix<unsigned char>   &Maux)
{_CONST(int)}

IntMatrix::IntMatrix (Matrix<char>   &Maux)
{_CONST(int)}

IntMatrix::operator FloatMatrix()
{_CAST_OP(FloatMatrix,float);}

IntMatrix::operator DoubleMatrix()
{_CAST_OP(DoubleMatrix,double);}

IntMatrix::operator UcharMatrix()
{_CAST_OP(UcharMatrix,unsigned char);}

IntMatrix::operator CharMatrix()
{_CAST_OP(CharMatrix,char);}

// <float>

FloatMatrix::FloatMatrix (Matrix<int>   &Maux)
{_CONST(float)}

FloatMatrix::FloatMatrix (Matrix<double>   &Maux)
{_CONST(float)}

FloatMatrix::FloatMatrix (Matrix<unsigned char>   &Maux)
{_CONST(float)}

FloatMatrix::FloatMatrix (Matrix<char>   &Maux)
{_CONST(float)}

FloatMatrix::operator IntMatrix()
{_CAST_OP(IntMatrix,int);}

FloatMatrix::operator DoubleMatrix()
{_CAST_OP(DoubleMatrix,double);}

FloatMatrix::operator UcharMatrix()
{_CAST_OP(UcharMatrix,unsigned char);}

FloatMatrix::operator CharMatrix()
{_CAST_OP(CharMatrix,char);}

// <unsigned char>

UcharMatrix::UcharMatrix (Matrix<int>   &Maux)
{_CONST(unsigned char)}

UcharMatrix::UcharMatrix (Matrix<double>   &Maux)
{_CONST(unsigned char)}

UcharMatrix::UcharMatrix (Matrix<float>   &Maux)
{_CONST(unsigned char)}

UcharMatrix::UcharMatrix (Matrix<char>   &Maux)
{_CONST(unsigned char)}

UcharMatrix::operator IntMatrix()
{_CAST_OP(IntMatrix,int);}

UcharMatrix::operator DoubleMatrix()
{_CAST_OP(DoubleMatrix,double);}

UcharMatrix::operator FloatMatrix()
{_CAST_OP(FloatMatrix,float);}

UcharMatrix::operator CharMatrix()
{_CAST_OP(CharMatrix,char);}

// <char>

CharMatrix::CharMatrix (Matrix<int>   &Maux)
{_CONST(char)}

CharMatrix::CharMatrix (Matrix<double>   &Maux)
{_CONST(char)}

CharMatrix::CharMatrix (Matrix<float>   &Maux)
{_CONST(char)}

CharMatrix::CharMatrix (Matrix<unsigned char>   &Maux)
{_CONST(char)}

CharMatrix::operator IntMatrix()
{_CAST_OP(IntMatrix,int);}

CharMatrix::operator DoubleMatrix()
{_CAST_OP(DoubleMatrix,double);}

CharMatrix::operator FloatMatrix()
{_CAST_OP(FloatMatrix,float);}

CharMatrix::operator UcharMatrix()
{_CAST_OP(UcharMatrix,unsigned char);}



// <double>

DoubleMatrix::DoubleMatrix (Matrix<int>   &Maux)
{_CONST(double)}

DoubleMatrix::DoubleMatrix (Matrix<float>   &Maux)
{_CONST(double)}

DoubleMatrix::DoubleMatrix (Matrix<unsigned char>  &Maux)
{_CONST(double)}

DoubleMatrix::DoubleMatrix (Matrix<char>   &Maux)
{_CONST(double)}

DoubleMatrix::operator IntMatrix()
{_CAST_OP(IntMatrix,int);}

DoubleMatrix::operator FloatMatrix()
{_CAST_OP(FloatMatrix,float);}

DoubleMatrix::operator UcharMatrix()
{_CAST_OP(UcharMatrix,unsigned char);}

DoubleMatrix::operator CharMatrix()
{_CAST_OP(CharMatrix,char);}


/***************************************\
 *      GAC_LAPACK based functions     *
\***************************************/
/*
DoubleMatrix & DoubleMatrix::SetRand (char Dist,char Sym, F_double Sparse, F_integer Kl, F_integer Ku, F_double Anorm, F_integer & INFO)
{
	F_integer		M       = NumRows;
	F_integer		N       = NumCols;
	char			DIST    = Dist;
	vector<int>		ISEED;
	char			SYM     = Sym;
	vector<double>	D(min(M,N));
	F_integer		MODE    = 6;
	F_double		COND    = 2.0;
	F_double		DMAX    = 1.0;
	char			RSIGN   = 'F';
	char			GRADE   = 'N';
//	vector<double>	DL;
	F_integer		MODEL   = 6;
	F_double		CONDL   = 2.0;
//	vector<double>	DR;
	F_integer		MODER   = 6;
	F_double		CONDR   = 3.0;
	char			PIVTNG  = 'N';
	vector<int>		IPIVOT;
	F_integer		KL      = Kl;
	F_integer		KU      = Ku;
	F_double		SPARSE  = Sparse;
	F_double		ANORM   = Anorm;
	char			PACK    = 'N';
//	TYPE*			A;
	F_integer		LDA		= M;
	vector<int>		IWORK(M);
//	F_integer		INFO;

	F_integer Result;


	//ISEED inicialization
	srand( (unsigned)time( NULL ) );

	int ISEED4;
	ISEED4 = rand()%4096;
	if (!(ISEED4%2)) ++ISEED4;
	ISEED.push_back(rand()%4096);
	ISEED.push_back(rand()%4096);
	ISEED.push_back(rand()%4096);
	ISEED.push_back(ISEED4);

	Result = dlatmr_(
		&M,&N,
		&DIST,
		ISEED.begin(), //Doesn´t work with stlport. It works with STL-3.2
		&SYM,
		D.begin(),&MODE,&COND,
		&DMAX,
		&RSIGN,
		&GRADE,
		D.begin(),&MODEL,&CONDL,
		D.begin(),&MODER,&CONDR,
		&PIVTNG,IPIVOT.begin(),
		&KL,
		&KU,
		&SPARSE,
		&ANORM,
		&PACK,
		pM,
		&LDA,
		IWORK.begin(),
		&INFO);

	return *this;
}


DoubleMatrix DoubleMatrix::LU (F_integer &INFO)
{
	F_integer		M       = NumRows;
	F_integer		N       = NumCols;
	F_integer		LDA		= M;
	vector<int>     IPIV(min(M,N));

	F_integer Result;
	DoubleMatrix LU(*this);

	size_t minMN = min(M,N);
	for (size_t i=0;i<minMN;i++) IPIV[i]=i+1;

    Result = dgetrf_(
		&M,
		&N,
		LU.pM,
		&LDA,
		IPIV.begin(),
		&INFO);

	return LU;
}


DoubleMatrix  DoubleMatrix::Inv (F_integer &INFO)
{
	assert(IsSquare());
	
	F_integer  NB;
 	F_integer  ISPEC    = 1;
	char      *NAME     = "DGETRI";
	char      *OPTS     = "";
	F_integer  N1       = NumRows;
	F_integer  N2       = -1;
	F_integer  N3       = -1;
	F_integer  N4       = -1;
	F_integer  NAME_LEN = 6;
	F_integer  OPTS_LEN = 0;

   NB = ilaenv_(
		&ISPEC,
		NAME,
		OPTS,
		&N1,
		&N2,
		&N3,
		&N4,
		&NAME_LEN,
		&OPTS_LEN);

	F_integer        M         = NumRows;
	F_integer        N         = NumCols;
	F_integer        LDA       = M;
	vector<double>   WORK(NB);
	F_integer        LWORK     = NB;
	vector<int>      IPIV(M);

	for (size_t i=0;i<M;i++) IPIV[i]=i+1;

	
	F_integer Result;
	DoubleMatrix Inv(*this);

    Result = dgetrf_(
		&M,
		&N,
		Inv.pM,
		&LDA,
		IPIV.begin(),
		&INFO);

	Result = dgetri_(
		&M,
		Inv.pM,
		&LDA,
		IPIV.begin(),
		WORK.begin(),
		&LWORK,
		&INFO);

	return Inv;
}

DoubleVector DoubleMatrix::SymEig (char Jobz,char Uplo,DoubleMatrix &A,F_integer &INFO)
{
	assert(IsSquare());

	F_integer  NB;
 	F_integer  ISPEC    = 1;
	char      *NAME     = "DSYTRD";
	char      *OPTS     = "U";
	F_integer  N1       = NumRows;
	F_integer  N2       = -1;
	F_integer  N3       = -1;
	F_integer  N4       = -1;
	F_integer  NAME_LEN = 6;
	F_integer  OPTS_LEN = 1;

   NB = ilaenv_(
		&ISPEC,
		NAME,
		OPTS,
		&N1,
		&N2,
		&N3,
		&N4,
		&NAME_LEN,
		&OPTS_LEN);
	
	char             JOBZ  = Jobz;
	char             UPLO  = Uplo;
	F_integer        N     = NumRows;
				     A     = *this;
	F_integer        LDA   = N;
	DoubleVector     W(N);
	DoubleVector     WORK((NB+2)*N);
	F_integer        LWORK = (NB+2)*N;

	F_integer        Result;

	Result = dsyev_(
		&JOBZ,
		&UPLO,
		&N,
		A.pM,
		&LDA,
		W.begin(),
		WORK.begin(),
		&LWORK,
		&INFO);

	return W;
}

DoubleVector DoubleMatrix::SymEig (char Jobz,char Range,char Uplo,
								   F_double Vl,F_double Vu,
								   F_integer Il, F_integer Iu,
								   F_integer &M,DoubleMatrix &Z,
								   F_integer &INFO)
{
	assert(IsSquare());

	F_integer  NB;
 	F_integer  ISPEC    = 1;
	char      *NAME     = "DSYTRD";
	char      *OPTS     = "U";
	F_integer  N1       = NumRows;
	F_integer  N2       = -1;
	F_integer  N3       = -1;
	F_integer  N4       = -1;
	F_integer  NAME_LEN = 6;
	F_integer  OPTS_LEN = 1;

   NB = ilaenv_(
		&ISPEC,
		NAME,
		OPTS,
		&N1,
		&N2,
		&N3,
		&N4,
		&NAME_LEN,
		&OPTS_LEN);
	
	char             JOBZ   = Jobz;
	char             RANGE  = Range;
	char             UPLO   = Uplo;
	F_integer        N      = NumRows;
	DoubleMatrix	 A      = *this;
	F_integer        LDA    = N;
	F_double         VL     = Vl;
	F_double         VU     = Vu;
	F_integer        IL     = Il;
	F_integer        IU     = Iu;
	F_double         ABSTOL = 2*DBL_EPSILON;
//	F_integer        M;
	DoubleVector     W(N);
	F_integer        LDZ    = N;
				     Z.Resize(LDZ,N);
	DoubleVector     WORK(max((8*N),(NB+3)*N));
	F_integer        LWORK = max((8*N),(NB+3)*N);
	IntVector        IWORK(5);
	IntVector        IFAIL(N);

	F_integer        Result;

	Result = dsyevx_(
		&JOBZ,
		&RANGE,
		&UPLO,
		&N,
		A.pM,
		&LDA,
		&VL,
		&VU,
		&IL,
		&IU,
		&ABSTOL,
		&M,
		W.begin(),
		Z.pM,
		&LDZ,
		WORK.begin(),
		&LWORK,
		IWORK.begin(),
		IFAIL.begin(),
		&INFO);

	return W;
}


/*********************************************************\
 *        Intel PLSuite MKL CBLAS based functions        *
\*********************************************************/

DoubleMatrix & DoubleMatrix::operator=(DoubleMatrix Mr)
{
//void cblas_dcopy(const int N, const double *X, const int incX,
//                double *Y, const int incY);
//	cblas_dcopy(NumRows,Mr.pM,1,pM,1);
	if (pM == Mr.pM) return *this;
	if (NumRows == Mr.NumRows && NumCols==Mr.NumCols) {
		cblas_dcopy(NumCols*NumRows,Mr.pM,1,pM,1);
	}
	else{
		Destroy();
		Initialize(Mr.NumRows,Mr.NumCols);
		cblas_dcopy(NumCols*NumRows,Mr.pM,1,pM,1);
	}
	return *this;
}


DoubleMatrix & DoubleMatrix::operator*(DoubleMatrix Mr)
{
//	void cblas_dgemm(const  CBLAS_ORDER Order, const  CBLAS_TRANSPOSE TransA,
//               const  CBLAS_TRANSPOSE TransB, const int M, const int N,
//               const int K, const double alpha, const double *A,
//               const int lda, const double *B, const int ldb,
//               const double beta, double *C, const int ldc);

	DoubleMatrix          C(NumRows,Mr.NumCols);

	cblas_dgemm(CblasRowMajor,CblasNoTrans,CblasNoTrans,NumRows,Mr.NumCols,NumCols,1.0,pM,NumRows,Mr.pM,NumCols,0.0,C.pM,NumRows);

	*this = C;
	return *this;
}

