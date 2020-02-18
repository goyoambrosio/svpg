function [state]=g_pgmsave(X,filename)
%G_PGMWRITE Load a matrix in raw fomrat
%   s = G_PGMSAVE(M,FileName) Write a PGM  (Portable Gray Map) file from disk. Only binary 
%	                           encoded PGM images ((P5)are supported.
%
%   Inputs
%   ------
%   M            Image matrix
%   FileName     File name with mat extension
%
%   Outputs
%   -------
%   s            Final operation state
%
%   Example
%   -------
%       state = g_pgmsave(I,'MyImage.pgm');
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
%  $RCSfile: g_pgmsave.m,v $
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


if (nargin~=2)
        error('Requires two arguments.');
end;

if (isstr(filename)~=1)
        error('Requires a string filename as the second argument.');
end;

if (isempty(findstr(filename,'.'))==1)
        filename=[filename,'.pgm'];
end;

fid=fopen(filename,'wb');
if (fid==-1)
        error(['Error opening ',filename,' for output.']);
end;

[width height]=size(X');
fprintf(fid,'P5\n');
fprintf(fid,'# CREATOR: g_pgmsave.m Version 1.0\n');
v=version;
fprintf(fid,'#          m-file for Matlab %s\n',v);
fprintf(fid,'#          By Gregorio Ambrosio Cestero (goyo@computer.org)\n');
fprintf(fid,'%d %d\n',width ,height);
fprintf(fid,'%d\n',255);
AUX=X';
fwrite(fid,AUX);
fclose(fid);
