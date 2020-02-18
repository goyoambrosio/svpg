function affinity = g_perona(d0,theta0,delta,dij,alfai,alfaj)
%G_PERONA Computes Perona's affinity function;
%
%   g_perona(d0,theta0,delta,dij,alfai,alfaj)
%   
%   Inputs
%   ------
%   d0      : reference distance below which two points are thought to be similar
%             and beyond which two points are thought to be dissimilar
%   theta0  : scaling constant between PI/2 and PI/10
%   delta   : scaling constant between 1/2 and 1/4
%   dij     : Distance between midpoints of segments
%   alfai   : Angle between segment i and the segment between midpoints
%   alfaj   : Angle betwwen segment j and the segment between midpoints
%
%   Outputs
%   -------
%   a      affinity (double scalar)
%
%   Example
%   -------
%	 a = g_perona(30,pi/2,0.5,5,1.57,1.57);
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
%  $RCSfile: g_gauss.m,v $
%  $Revision: 1.1 $
%  $Date: 2000/01/21 13:15:57 $
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

    A = (dij*dij)/(d0*d0)
    B = (2-cos(2*alfai)-cos(2*alfaj))/(1-cos(2*theta0))
    C = (1-cos(2*alfai - 2*alfaj))/(1-cos(2*delta*theta0))

    affinity = g_exp(-A-B-C);

