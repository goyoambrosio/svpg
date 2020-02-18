%G_COPG Extract collinear perceptual groups from an image.
%   [C S]=g_copg(I,E,MaxDistBetwColSegments,MaxParDistBetwColSegments,MaxAngleBetwCollinearSegments,MinNumOfPixels,MaxDistance,TraceData);
%
%   Inputs
%   ------
%   I                                Image matrix
%   E                                Edge matrix (Obtained with g_canny)
%   MaxDistBetwColSegments           Max. euclidean distance between collinear segments
%   MaxParDistBetwColSegments        Max. parallel euclidean distance between collinear segments
%   MaxAngleBetwCollinearSegments    Max. angle between collinear segments
%   MinNumOfPixels                   Min. number of pixels of a segment
%   MaxDistance                      Max. distance between pixels in the edge image and segments
%   TraceData                        Switch (0|1) of trace data.
%   
%   Outputs
%   -------
%
%	C	  Collinear Perceptual Group matrix with the following structure
%            Each row represent a PG and is a binary vector. Each component´s ordinal of the binary
%            vector (eq. each column) means the Label of a segment. 1 means the segment belongs to the PG
%            0 is the opposite.
%   S     Segment matrix with the follwing structure:
%			 Column 1    Label of the segment.
%            Column 2    i coor. of the begin point.
%            Column 3    j coor. of the begin point.
%            Column 4    i coor. of the end point.
%            Column 5    j coor. of the end point.
%
%   Example
%   -------
%       I = pgmread('telephone.pgm');
%       E = g_canny(I,2,100,100);
%       S = g_segments(E,20,1.5);
%       [C S]=g_copg(double(I),double(E),20,5,10,20,1.5,0);
%       g_imsgplot1(I,S,C,'i',[1:55]);
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
%  $RCSfile: g_copg.m,v $
%  $Revision: 1.1 $
%  $Date: 2000/01/21 13:15:52 $
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

