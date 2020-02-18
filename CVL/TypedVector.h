/****
  SoftVision. Software for Computer Vision

  Gregorio Ambrosio Cestero (goyo@computer.org)
  System Engineering and Automation Department 
  University of Malaga. Spain                   

  $RCSfile: TypedVector.h,v $
  $Revision: 1.1 $
  $Date: 2000/01/21 13:05:20 $
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


#if !defined(_TYPEDVECTOR_H_)
#define _TYPEDVECTOR_H_

#include <stdio.h>
#include <vector>

using namespace std;

namespace GAC
{

/********************************************\
 *    Classes declared in this file         *
\********************************************/

//class IntVector;
//class FloatVector;
//class DoubleVector;
//class UcharVector;
//class BoolVector;
//class CharVector;


/********************************************\
 *                Declarations              *
\********************************************/

	class DoubleVector : public vector<double>  
{
public:
	DoubleVector ():vector<double>(){};
	DoubleVector (size_t Qty):vector<double>(Qty){};

	void Show();

};

class IntVector : public vector<int>  
{
public:
	IntVector ():vector<int>(){};
	IntVector (size_t Qty):vector<int>(Qty){};

	void Show();

};

} //namespace GAC

#endif // !defined(_TYPEDVECTOR_H_)
