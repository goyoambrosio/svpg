function g_imsgplot1(I,S,SG,Opt,n);
%G_IMSGPLOT1 Display a group of segments over an image
%   g_imsgplot1(I,S,C,Opt,n) 
%   
%   I     Image (intensity matrix)
%   S     Segment matrix obtained with g_segments function (use "help g_segments" to see the structure of this matrix)
%   SG    Segment Groups matrix with the following structure
%            Each row represent a SG and is a binary vector. Each component´s ordinal of the binary
%            vector (eq. each column) means the Label of a segment. 1 means the segment belongs to the PG
%            0 is the opposite.
%   OPT   String formed with characters that represents visualization options
%           i Displays the image I as background
%           b Displays a black background
%           p Displays begin and end points of segments
%           l Displays segment's labels
%   n     Vector with group numbers to be displayed
%
%   Example
%   -------
%   I  = g_pgmload('telephonel.pgm');
%   E  = uint8(g_canny(double(I),1,100,100));
%   S  = g_segments(double(E),1.5,10);
%   G  = g_ppg(S,10,5);
%   g_imsgplot1(I,S,G,'b',1);
%   g_imsgplot1(I,S,G,'b',[2:4,7]);
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


if ~isempty(findstr(Opt,'b'))
   imshow(ones(size(I)),[0,255]);
end
if ~isempty(findstr(Opt,'i'))|isempty(Opt)
    imshow(I);
end
axis on;
zoom;

x=rot90([S(:,2)+1,S(:,4)+1]);
y=rot90([S(:,3)+1,S(:,5)+1]);
hold on;
H=line(y,x);
set(H,'Color','yellow');

for i=1:size(n,2),
   G=find(SG(n(i),:));
   x=rot90([S(G,2)+1,S(G,4)+1]);
   y=rot90([S(G,3)+1,S(G,5)+1]);
   hold on;
   H=line(y,x);
   set(H,'Color','red');
   if ~isempty(findstr(Opt,'p'))
      plot(S(G,3)+1,S(G,2)+1,'g.');
      plot(S(G,5)+1,S(G,4)+1,'r.');
   end
   if ~isempty(findstr(Opt,'l'))
      H=text((S(G,3)+S(G,5))/2 - 5,...
         (S(G,2)+S(G,4))/2 - 5,...
         num2str(S(G,1)));
      
      set(H,	'FontName','arial',...
         'FontSize',6,...
         'FontWeight','bold',...
         'Color','red');
   end
end

   
   
hold off;
