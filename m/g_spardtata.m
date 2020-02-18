%G_SPARDATA 
%/**********************************************************************\
% This function returns three graphs. Nodes in graphs represent image 
% segments. An edge means there is a parallel relationship between two 
% nodes, i.e., two segments. Edge value are different in each graph. 
% In DistanceGraph edge value is the distance between midpoints of S1Aux
% and S2Aux. 
% In AngleGraph is the angle between 0 and PI radians. 
% Finally, in OverlapGraph is the module of the overlap segment resulted 
% of the projection of S2 over S1.
%
%
%                  S1 
%      <=========================>
%	                    S1Aux
%      <--------------------------------------->
%
%     S1A         S2BinS1       S1B         S2AinS1
%
%      *-------------*-----------*.............*
%
%
%      *.............*-----------*-------------*
%   S1AinS2         S2B       S1BinS2         S2A
%
%      <--------------------------------------->
%	                    S2Aux
%                    <=========================>
%					            S2
%
% Input parameters are:
%  S: a segment set.
%  MaxDistance and MinDistance: Two segments are considered as possible 
%   parallel segments only if the distance that separates them is 
%   between MinDistance and MaxDistance, i.e., 
%   MinDistance >= Distance beetween segments >= MaxDistance
%  MaxAngle: Two segments are considered as possible paralle segments 
%  if they have an angle less than MaxAngle. The angle is measured 
%  in radians.
%\**********************************************************************/
%   [D,A,O] = g_spardata(S,MaxD,MinD,MaxA);
%   Inputs
%   ------
%   S         Segment matrix with the follwing structure:
%			     Column 1    Label of the segment.
%                Column 2    i coor. of the begin point.
%                Column 3    j coor. of the begin point.
%                Column 4    i coor. of the end point.
%                Column 5    j coor. of the end point.
%   MaxD      MaxDistance
%	MinD      MinDistance
%   MaxA      MaxAngle
%   
%   Outputs
%   -------
%
%	D         Adjacency matrix of the DistanceGraph.
%   A         Adjacency matrix of the AngleGraph.
%   O         Adjacency matrix of the OverlapGraph.
%
%   Example
%   -------
%       I = g_pgmload('telephone.pgm');
%       E = g_canny(I,2,100,100);
%       S = g_segments(E,20,1.5);
%       [D,A,O] = g_spardata(S,20,2,5);
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
%  $RCSfile$
%  $Revision$
%  $Date$
%  $Name$
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

