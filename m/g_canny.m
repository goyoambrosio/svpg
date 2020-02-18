%G_CANNY Find edges in intensity image.
%   BW = G_CANNY(I,SIGMA,LOWHYST,HIGHYST) returns a binary image BW with the same
%   size as I, with 1's where the function finds edges in I and
%   0's elsewhere.
%
%   SIGMA      is the standard deviation of the Laplacian of Gaussian
%   LOWHYST    Low hysteresis. Ignores all edges that are less stronger than LOWHYST
%   HIGHHYST   High hysteresis. Ignores all edges that are more stronger than HIGHHYST
%
%   Example
%   -------
%   Find the edges of the cartl.pgm image using the Canny filter:
%
%       I = pgmread('cartl.pgm');
%       BW = g_canny(I,1,85,106);
%       image(I),colormap(gray(256)), figure, image(BW)
%
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
%  $RCSfile: g_canny.m,v $
%  $Revision: 1.1 $
%  $Date: 2000/01/21 13:15:48 $
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

