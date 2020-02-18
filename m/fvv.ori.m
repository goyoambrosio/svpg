function fvv(action)
% FVV: Feature Vector Visualizer
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
%  $RCSfile: fvv.ori.m,v $
%  $Revision: 1.1 $
%  $Date: 2000/01/21 13:15:45 $
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

% This is the machine-generated representation of a Handle Graphics object
% and its children.  Note that handle values may change when these objects
% are re-created. This may cause problems with any callbacks written to
% depend on the value of the handle at the time the object was saved.
%
% To reopen this object, just type the name of the M-file at the MATLAB
% prompt. The M-file and its associated MAT-file must be on your path.

load fvv                               

if nargin<1,
    action='start';
end;

global FILENAME		%Nombre del fichero sva
global PATHNAME		%Path del fichero sva

if strcmp(action,'start'),

a = figure('Units','points', ...
	'Color',[0.8 0.8 0.8], ...
	'Colormap',mat0, ...
	'PointerShapeCData',mat1, ...
	'Position',[163.5 81 420 315], ...
	'Tag','Fig1');
b = uicontrol('Parent',a, ...
	'Units','points', ...
	'Callback','fvv(''LoadLfv'');', ...
	'Position',[42 48 84.75 15.75], ...
	'String','Open Left Image', ...
	'Tag','Pushbutton1');
b = uicontrol('Parent',a, ...
	'Units','points', ...
	'Callback','fvv(''LoadRfv'');', ...
	'Position',[42 31.5 84.75 15.75], ...
	'String','Open Right Image', ...
   'Tag','Pushbutton1');

elseif strcmp(action,'LoadLfv'),
	 [L_FILENAME, L_PATHNAME] = uigetfile('*.fv', 'Feature Vector Visualizer',1, 1);
    if L_FILENAME~=0 
       	[fid message] = fopen([L_PATHNAME L_FILENAME],'r');
			%========================
			%Esto pasa en el ordenador de mi casa
			%[fid message] = fopen([PATHNAME(1:length(PATHNAME)-2) FILENAME],'r'); %Lo de la composicion del nombre es una chapucilla porque el uigetfile no funciona demasiado bien y mete dos caracteres del FILENAME en el PATHNAME
			%========================
		if fid==-1
			errordlg(message,'SVA file load error',1);
		else
			Size = fread(fid,1,'uint');
         LFV = fread(fid,[19,Size],'double');
      end
	end
end
