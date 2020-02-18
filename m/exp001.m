function i = exp001(S);

%Programa para obtener grupos de segmentos paralelos
%/****
%  SoftVision Toolbox. Software for Computer Vision
%
%  Copyright (c) 2000, Gregorio Ambrosio cestero
%               All Rights Reserved
%
%  Gregorio Ambrosio Cestero (goyo@computer.org)
%  System Engineering and Automation Department 
%  University of Malaga. Spain                   
%
%  $RCSfile: exp001.m,v $
%  $Revision: 1.1 $
%  $Date: 2000/01/21 13:15:44 $
%  $Name:  $
%
%****/

%/****************************************************************************\
%* SoftVision Toolbox. Software for Computer Vision                           *
%*                                                                            *
%* Author  : Gregorio Ambrosio Cestero (goyo@computer.org)                    *
%*           System Engineering and Automation Department                     *
%*           University of Malaga. Spain                                      *
%*                                                                            *
%*               Copyright (c) 2000, Gregorio Ambrosio cestero                *
%*                          All Rights Reserved                               *
%*                                                                            *
%* Permission to use, copy, modify, and distribute this software and its      *
%* associated documentation for non-commercial purposes is hereby granted,    *
%* provided that the above copyright notice appears in all copies, derivative *
%* works or modified versions of the software and any portions thereof, and   *
%* that both the copyright notice and this permission notice appear in the    *
%* documentation.  Gregorio Ambrosio Cestero (GAC for short) shall be given   *
%* a copy of any such derivative work or modified version of the software and *
%* GAC shall be granted permission to use, copy, modify and distribute the    *
%* software for his own use and research. This software is experimental.      *
%* GAC does not make any representations regarding the suitability of this    *
%* software for any purpose and GAC will not support the software.            *
%*                                                                            *
%* THE SOFTWARE IS PROVIDED AS IS.  GAC DOES NOT MAKE ANY WARRANTIES          *
%* EITHER EXPRESS OR IMPLIED WITH REGARD TO THE SOFTWARE. GAC ALSO            *
%* DISCLAIMS ANY WARRANTY THAT THE SOFTWARE IS FREE OF INFRINGEMENT OF ANY    *
%* INTELLECTUAL PROPERTY RIGHTS OF OTHERS.  NO OTHER LICENSE EXPRESS OR       *
%* IMPLIED IS HEREBY GRANTED. GAC SHALL NOT BE LIABLE FOR ANY DAMAGES,        *
%* INCLUDING GENERAL, SPECIAL, INCIDENTAL, OR CONSEQUENTIAL DAMAGES, ARISING  *
%* OUT OF THE USE OR INABILITY TO USE THE SOFTWARE.                           *
%*                                                                            *
%\****************************************************************************/

%I  = imread('laura.bmp');
%E  = uint8(g_canny(double(I),1,100,100));
%S  = g_segments(double(E),1.5,30);

MaxMidPointDistance = 10;
MaxShortAngle       = 0.0087 * 5;
MinOverlapMod       = 0;

MPD = g_smpd(S);
SA  = g_ssa(S);
OM  = g_som(S);

A = zeros(size(MPD));
B = zeros(size(SA));
C = zeros(size(OM));

v = find(MPD<MaxMidPointDistance);
A(v) = ones(size(v));

v = find(SA<MaxShortAngle);
B(v) = ones(size(v));

v = find(OM>MinOverlapMod);
C(v) = ones(size(v));

%D = A.*B.*C;
D=tril(B,-1);
[i,j]=find(D);
%i = [i j];
%i=j;
