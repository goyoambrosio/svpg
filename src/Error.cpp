/****
  SoftVision. Software for Computer Vision

  Gregorio Ambrosio Cestero (goyo@computer.org)
  System Engineering and Automation Department 
  University of Malaga. Spain                   

  $RCSfile: Error.cpp,v $
  $Revision: 1.1 $
  $Date: 2000/01/21 13:04:02 $
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


// Error.cpp: implementation of the int2doubleMap class.
//
//////////////////////////////////////////////////////////////////////

#include <CVL/Error.h>
#include <stdio.h>

using namespace std;

namespace GAC
{

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Error::Error()
{
	ErrorCode = 0;
}

Error::~Error()
{

}

//Previamene a la utilizacion de los metodos de este objeto
//se ha tenido que inicializar con los codigo de error adecuados
//y sus strings asociados.
//En el momento de señalar un error hay que llamar a la funcion
//SetErrorCode con el codigo de error deseado. La funcion comprueba
//que el codigo existe. Si existe devuelve True y establece a la 
//variable privada ErrorCode con el codigo de error elegido.
//Si no existe devuelve False y resetea a la variable privada ErrorCode
//a cero.
bool Error::SetErrorCode(int Code){
	iterator Eit;
	Eit = find(ErrorCode);
	if (Eit!=end())
		ErrorCode = Code;
	else
		ErrorCode = 0;
	return (Eit!=end());
}

void Error::ResetErrorCode(){
	ErrorCode = 0;
}

int Error::GetErrorCode(){
	return ErrorCode;
}

char * Error::GetStrError(){
	iterator Eit;
	Eit = find(ErrorCode);

	return (*Eit).second;
}

void  Error::Abort(int Code) {
	SetErrorCode(Code);
	printf("Error %i : %s\n",Code,GetStrError());
	exit (-1);
}



} //namespace GAC

