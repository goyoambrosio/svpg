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
%  $RCSfile: articulo.m,v $
%  $Revision: 1.1 $
%  $Date: 2000/01/21 13:15:42 $
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

M = g_load('mapa_reina.raw','double'); %Cargar el mapa
g_splot(M,'','blue'); %Visualizar el mapa
[D,A,C] = g_sconvexdata(M,2.0,2.0); %Sacar información de circularidad
CC = C/max(max(C)); %Normalizo entre 0 y 1
DV = g_eigaff(CC,0); %Saco los autovalores/autovectores ordenado ascendentemente por autovalor
plot(DV(:,1)); %Visualizo los autovalores
plot(DV(size(DV,1),2:end)); %Visualizo el último autovector (el de mayor autovalor)
g_saffplot(M,'',DV,1,0.0000001); %Visualizo el autovector del mayor autovalor


/****************Convexidad*******************/
E = g_pgmload('af1.pgm');
S = g_segments(E,1.5,10);
g_splot(S,'p','blue');
[D,A,C] = g_sconvexdata(S,10.0,2.0); %Sacar información de circularidad
AfC = exp(C);
Av = g_eigaff(AfC,0);
plot(Av(:,1));
plot(Av(size(Av,1),2:end));
g_saffplot(S,'',Av,1,0.36);



/****************Proximidad*******************/
E = g_pgmload('af1.pgm');
S = g_segments(E,1.5,10);
g_splot(S,'p','blue');
D1 = g_sproxdata  (S,100);
AfD = exp(-D1/max(max(D1)));
Av = g_eigaff(AfD,0);
plot(Av(size(Av,1),2:end));
g_saffplot(S,'',Av,1,0.35);
d0 = 0.3;AfD = exp(-(D.*D)/(d0*d0));Av = g_eigaff(AfD,0);plot(Av(size(Av,1)-0,2:end));

clear M;
Row = 1;
for i=0.1:0.1:10,
   d0 = i;AfD = exp(-(D.*D)/(d0*d0));Av = g_eigaff(AfD,0);M(Row,:)=Av(size(Av,1)-0,2:end);
   Row = Row+1;
end
surf(M);
shading interp;


d0 = 0.1;AfD = exp(-(D.*D)/(d0*d0));surf(AfD);

   


