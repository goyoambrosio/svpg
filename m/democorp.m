% Proceso de correlación entre dos imágenes I1 y I2
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
%  $RCSfile: democorp.m,v $
%  $Revision: 1.1 $
%  $Date: 2000/01/21 13:15:43 $
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

[H I1 I2] = showim;

if all(size(I1) ~= size(I2))
	error('Las matrices no tienen las mismas dimensiones');
end

subplot(2,2,1);
image(I1);
axis('image');
title('Imágen Izq.');
subplot(2,2,2);
image(I2);
axis('image');
title('Imágen Dch.');

N=2;
P=2;
Entorno=20;

Mostrar = ['N = str2num(get(EditN,''string''))'];

Correlar = [...
'N = str2num(get(EditN,''string'')); ' ...
'P = str2num(get(EditP,''string'')); ' ...
'Entorno = str2num(get(EditEntorno,''string'')); ' ...
'subplot(2,2,1);' ...
'hold on; ' ...
'[ColPunto FilPunto] = ginput(1);' ...
'ColPunto = round(ColPunto);' ...
'FilPunto = round(FilPunto);' ...
'plot(ColPunto,FilPunto,''y+'');' ...
'hold off; ' ...
'VectorCorrelacion=correlap(ColPunto,FilPunto,I1,I2,N,P,Entorno); ' ...
'[MaxCorrelacion ColumnaMaxCorrelacion] = max(VectorCorrelacion); ' ...
'subplot(2,2,2);' ...
'hold on;' ...
'image(I2);' ...
'plot(ColumnaMaxCorrelacion,FilPunto,''y+'');' ...
'subplot(2,2,4);' ...
'plot(VectorCorrelacion,''g'');' ...
'axis([0 128 0 1]);' ...
'axis(''square'');' ...
'xlabel(''píxels'');' ...
'ylabel(''correlación'');' ...
'Disparidad = abs(ColumnaMaxCorrelacion-ColPunto)' ...
];


Pixel = uicontrol('style','push','units','normal','pos',[.05 .40 .25 .045], ...
        'string','Píxel','call',Correlar);

EditEntorno=uicontrol('Style','edit','Position',[.05 .25 .25 .035], ...
        'Units','normalized','String','20','Fore','white');

EditN=uicontrol('Style','edit','Position',[.05 .15 .25 .035], ...
        'Units','normalized','String','2','Fore','white');
        
EditP=uicontrol('Style','edit','Position',[.05 .05 .25 .035], ...
        'Units','normalized','String','2','Fore','white');


TextEntorno = uicontrol('style','text','units','normal','pos',[.05 .30 .25 .035], ...
     'string','Entorno','fore','green','back','black');
TextN = uicontrol('style','text','units','normal','pos',[.05 .20 .25 .035], ...
     'string','N','fore','green','back','black');
TextP = uicontrol('style','text','units','normal','pos',[.05 .10 .25 .035], ...
     'string','P','fore','green','back','black');

return;