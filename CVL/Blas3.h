/****
  SoftVision. Software for Computer Vision

  Gregorio Ambrosio Cestero (goyo@computer.org)
  System Engineering and Automation Department 
  University of Malaga. Spain                   

  $RCSfile: Blas3.h,v $
  $Revision: 1.1 $
  $Date: 2000/01/21 13:03:52 $
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


#ifndef BLAS1_H
#define BLAS1_H
#include "fortran.h"


// This file incomplete and included here only to demonstrate the
// basic framework for linking with the Fortran or assembly BLAS.
//

#define fi_ Fortran_integer
#define fd_ Fortran_double
#define ff_ Fortran_float
#define fc_ Fortran_complex 
#define fz_ Fortran_double_complex

// these are the Fortran mapping conventions for function names
// (NOTE: if C++ supported extern "Fortran", this wouldn't be necesary...)
//

#define F77_DASUM       dasum_
#define F77_DAXPY       daxpy_
#define F77_CAXPY       cazpy_
#define F77_DDOT        ddot_

namespace GAC
{

extern "C"
{
    fd_ F77_DASUM(const fi_  *N , const fd_ *dx, const fi_* incx);

}

} //namespace GAC

#undef fi_  
#undef fd_  
#undef ff_  
#undef fc_  
#undef fz_

#endif // BLAS_1H




