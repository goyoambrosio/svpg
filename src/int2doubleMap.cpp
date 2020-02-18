/****
  SoftVision. Software for Computer Vision

  Gregorio Ambrosio Cestero (goyo@computer.org)
  System Engineering and Automation Department 
  University of Malaga. Spain                   

  $RCSfile: int2doubleMap.cpp,v $
  $Revision: 1.1 $
  $Date: 2000/01/21 13:04:37 $
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


// int2doubleMap.cpp: implementation of the int2doubleMap class.
//
//////////////////////////////////////////////////////////////////////

#include "int2doubleMap.h"

namespace GAC
{

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

int2doubleMap::int2doubleMap()
{

}

int2doubleMap::~int2doubleMap()
{

}

//Visualization
void int2doubleMap::Show()
{
	int2doubleMap::iterator it;
	for (it = begin(); it != end(); it++)
	{
		cout << "(" << (*it).first << " : " << (*it).second << ")";
	}
	cout << endl;
}

//Serialize
size_t int2doubleMap::Serialize(FILE * stream)
{
	size_t count  = 0;
	size_t IDMsize = 0;

	int		i;
	double	d;

	IDMsize = size();
	count += sizeof(size_t)*fwrite(&IDMsize, sizeof(size_t),1,stream);

	int2doubleMap::iterator it;
	for (it = begin(); it != end(); it++)
	{
		i = (*it).first;
		d = (*it).second;
		count += sizeof(int)   *fwrite(&i, sizeof(int)   ,1,stream);
		count += sizeof(double)*fwrite(&d, sizeof(double),1,stream);
	}

	return count;
}

} //namespace GAC

