function DV=g_heigaff(G,n)
%G_HEIGAFF Compute a number of eigenvalues of the graph's spectrum represented by an affinity matrix
%   G_HEIGAFF(G,n)
%   
%   Inputs
%   ------
%   G     Affinity matrix (Sparse symetric matrix)
%   n     Number of eigenvalues to be computed
%
%   Outputs
%   -------
%   DV    Eigenmatrix with the following structure
%           Column 1     Eigenvalues in descending order
%           Column 2..n  Eigenvector
%           Each row is composed of an eigenvalue and its corresponding eigenvector.
%           The component's ordinal of the eigenvector correspond to the segment's label.
%
%   Example
%   -------
%   I=uint8(pgmread('telephonel.pgm'));
%   E=uint8(canny(double(I),1,100,100));
%   S=segments(double(E),5,1.5);
%   G=affinitymatrix(double(I),S,12,5,2,0.5,1,1,1); %MaxDistance,d0p,thetap,deltap,C1,C2,C3
%   DV=g_heigaff(G,5);
%   plot(DV(:,1));
%   g_imsaffplot(I,S,'i',DV,1,0);
%   plot(DV(1,2:end));    %Plots first eigenvector
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
%  $RCSfile: g_heigaff.m,v $
%  $Revision: 1.1 $
%  $Date: 2000/01/21 13:15:58 $
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

OPTIONS.disp=0;
[V,D] = eigs(G,n,OPTIONS);
V=V';
D=diag(D);
DV=[D V];
DV=sortrows(DV,[1]);


