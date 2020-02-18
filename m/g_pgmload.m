function [X]=g_pgmload(filename)
%G_PGMLOAD Load a matrix in raw fomrat
%   M = G_PGMLOAD(FileName) Read a PGM (Portable Gray Map) file from disk. Only binary 
%	                        encoded PGM images ((P5)are supported.  
%                           If no extension is given for the filename,the extension '.pgm' is assumed.
%
%   Inputs
%   ------
%   FileName     File name with mat extension
%
%   Outputs
%   -------
%   M            Returned matrix
%
%   Example
%   -------
%       I = g_pgmload('MyImage.pgm');
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
%  $RCSfile: g_pgmload.m,v $
%  $Revision: 1.1 $
%  $Date: 2000/01/21 13:16:07 $
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



if (nargin~=1)
        error('Requires a filename as an argument.');
end;
if (isstr(filename)~=1)
        error('Requires a string filename as an argument.');
end;
if (isempty(findstr(filename,'.'))==1)
        filename=[filename,'.pgm'];
end;

fid=fopen(filename,'rb');
if (fid==-1)
        error(['Error opening ',filename,' for input.']);
end;

aux=fgetl(fid);
if (strcmp(aux,'P5')==0)
fclose(fid)
error([filename, ' is not a valid PGM binary encoded image']);
end;

% Below the comments are stripped
comments=1;
while(comments)
	aux=fgets(fid);
	if (aux(1)~='#')
		comments=0;
	end;
end;

% Get the dimensions
[width height]=strtok(aux);
width=str2num(width);
height=str2num(height);

% This strip the number of grays information. Since we know they are 255
% a priori, there isn't need to capture this information
aux=fgets(fid);
X=fread(fid);
fclose(fid);
X=reshape(X,width,height);

% The image is transposed after the read. 
X=X';

