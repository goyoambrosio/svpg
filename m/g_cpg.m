%G_CPG Extract convex perceptual groups from an image. (Based in D.Jacob's algorithm)
%   [C SC FV]=g_cpg(I,E,k,MaxDistBetwProxSegments,MaxNoConvexityThreshold,
%                   JacobExtension_1,JacobExtension_2,MinNumOfPixels,MaxDistance,TraceData);
%
%   Inputs
%   ------
%   I                          Image matrix
%   E                          Edge matrix (Obtained with g_canny)
%   k                          Saliency
%   MaxDistBetwProxSegments    Max. euclidean distance between segments
%   MaxNoConvexityThreshold    Max. threshold value of no convexity (max.euclidean distance in the non-convex sapce
%   JacobExtension_1           Switch (0|1) the extension 1 of the Jacob's algorithm
%   JacobExtension_2           Switch (0|1) the extension 2 of the Jacob's algorithm
%   MinNumOfPixels             Min. number of pixels of a segment
%   MaxDistance                Max. distance between pixels in the edge image and segments
%   TraceData                  Switch (0|1) of trace data
%   
%   Outputs
%   -------
%
%	C	  Convex Perceptual Group matrix with the following structure
%            Each row represent a CPG and is a binary vector. Each component´s ordinal of the binary
%            vector (eq. each column) means the Label of a segment. 1 means the segment belongs to the CPG
%            0 is the opposite.
%   SC    Segment matrix with the follwing structure:
%			 Column 1    Label of the segment.
%            Column 2    i coor. of the begin point.
%            Column 3    j coor. of the begin point.
%            Column 4    i coor. of the end point.
%            Column 5    j coor. of the end point.
%   FV    Feature Vector matrix. Each row represent a CPG and each column is a feature such as:
%            Column 1: Area
%            Column 1: Perimeter
%            Column 1: i coor. of the Binary Centroid
%            Column 1: j coor. of the Binary Centroid
%            Column 1: i coor. of the Gray Centroid
%            Column 1: j coor. of the Gray Centroid
%            Column 1: Central moment 00
%            Column 1: Central moment 01
%            Column 1: Central moment 10
%            Column 1: Central moment 02
%            Column 1: Central moment 11
%            Column 1: Central moment 20
%            Column 1: Central moment 03
%            Column 1: Central moment 12
%            Column 1: Central moment 21
%            Column 1: Central moment 30
%            Column 1: Normalized central moment 02
%            Column 1: Normalized central moment 11
%            Column 1: Normalized central moment 20
%            Column 1: Normalized central moment 03
%            Column 1: Normalized central moment 12
%            Column 1: Normalized central moment 21
%            Column 1: Normalized central moment 30
%
%   Example
%   -------
%       I = pgmread('telephone.pgm');
%       E = g_canny(I,2,100,100);
%       S = g_segments(E,20,1.5);
%       [C SC FV]=g_cpg(double(I),double(E),0.7,30,3.0,0,0,20,1.5,0);
%       g_imcpgplot(I,SC,C,FV,'i',[1:3]); Display CPGs no. 1,2,and 3
%       g_imsgplot(I,SC,'i',find(C(1,:))); Display CPG number 1 with the g_imsgplot function
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
%  $RCSfile: g_cpg.m,v $
%  $Revision: 1.1 $
%  $Date: 2000/01/21 13:15:54 $
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

