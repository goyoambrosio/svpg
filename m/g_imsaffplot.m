function g_imsaffplot(I,S,Opt,DV,nEV,Thld)
%G_IMSAFFPLOT Display segments which belong to one affinity group
%   G_IMSAFFPLOT(I,S,Opt,DV,nEV,Thld) 
%   
%   I     Image (intensity matrix)
%   S     Segment matrix with the follwing structure:
%			 Column 1    Label of the segment.
%            Column 2    i coor. of the begin point.
%            Column 3    j coor. of the begin point.
%            Column 4    i coor. of the end point.
%            Column 5    j coor. of the end point.
%   OPT   String formed with characters that represents visualization options
%           i Display the image I as background
%           b Display a black background
%           p Display begin and end points of segments
%           l Display segment's labels
%   DV    Eigenmatrix with the following structure
%           Column 1     Eigenvalues in descending order
%           Column 2..n  Eigenvector
%           Each row is composed of an eigenvalue and its corresponding eigenvector.
%           The component's ordinal of the eigenvector correspond to the segment's label.
%   nEV   Number of the affinity group to be displayed (Number of the row)
%   Thld  Threshold number of eigenvector components to be displayed (0..1).
%
%   Example
%   -------
%       I = pgmread('telephone.pgm');
%       E = g_canny(I,2,100,100);
%       S = g_segments(E,20,1.5);
%       G = g_affinitymatrix(double(I),S,12,5,2,0.5,1,1,1); %MaxDistance,d0p,thetap,deltap,C1,C2,C3
%       DV= g_eigaff(G,0);                                    
%       g_imsaffplot(I,S,'i',DV,2,0.00001); %Affinity group formed with the eigenvector corresponding to the 2nd highest eigenvalue
%       plot(DV(1,2:end));    %Plots first eigenvector
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
%  $RCSfile: g_imsaffplot.m,v $
%  $Revision: 1.1 $
%  $Date: 2000/01/21 13:16:02 $
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



if ~isempty(findstr(Opt,'b'))
   imshow(ones(size(I)),[0,255]);
end
if ~isempty(findstr(Opt,'i'))|isempty(Opt)
    imshow(I);
end

x=rot90([S(:,2)+1,S(:,4)+1]);
y=rot90([S(:,3)+1,S(:,5)+1]);
hold on;
H=line(y,x);
set(H,'Color','yellow');

Row = size(DV,1)-nEV+1;
cmap = (hot(512));
G=find(abs(DV(Row,2:size(DV,2)))>Thld);
%EV = abs(DV(Row,2:size(DV,2)));

x=rot90([S(G,2)+1,S(G,4)+1]);
y=rot90([S(G,3)+1,S(G,5)+1]);
hold on;
H=line(y,x);
set(H,'Color','red');

if ~isempty(findstr(Opt,'p'))
   plot(S(:,3)+1,S(:,2)+1,'g.');
   plot(S(:,5)+1,S(:,4)+1,'r.');
end
   
if ~isempty(findstr(Opt,'l'))
   H=text((S(:,3)+S(:,5))/2 - 5,...
      (S(:,2)+S(:,4))/2 - 5,...
      num2str(S(:,1)));
   
   set(H,	'FontName','arial',...
      'FontSize',6,...
      'FontWeight','bold',...
      'Color','red');
end
   
hold off;
