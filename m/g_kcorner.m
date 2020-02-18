function fp = g_kcorner(I,w);
%G_KCORNER Kanade corner detector
%   G_KCORNER(I,w)
%   
%   Inputs
%   ------
%   I     Image matrix
%   w     Determine width of the window (2*w + 1)
%
%   Outputs
%   -------
%   fp    Feature point vector
%
%   Example
%   -------
%   I  = uint8(pgmread('telephonel.pgm'));
%   fp = g_kcorner(I,9);
%   g_implot(I,fp);
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
%  $RCSfile: g_kcorner.m,v $
%  $Revision: 1.1 $
%  $Date: 2000/01/21 13:16:04 $
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

%% Kanade-Lucas-Tomasi tracker using corners as features
%% Find features by using best corners

imsize = size(I);
[m n] = size(I);

num_wins = 0;   % the number of feature windows

% calculate gradient using a derivative of a gaussian and a standard deviation of .5 pixels
[Idy Idx] = g_gradim(I,.5);

win_size = w;  			% pixels on either side
win_width = 2*win_size + 1; 	% width of the window
tau = (win_width ^ 2)*10; 	% lower threshold for the eigenvalue lambda2 used to detect features

% calculate components of A in A d = e.
onerow = ones(1, win_width);
A1 = conv2(conv2(Idx .^2, onerow, 'same')   , onerow', 'same');
A2 = conv2(conv2(Idy .^2, onerow, 'same')   , onerow', 'same');
A3 = conv2(conv2(Idx .* Idy, onerow, 'same'), onerow', 'same');

% trace and determinant are used to calculate eigenvalues
tr = A1 + A2;
dt = A1 .* A2 - A3 .^ 2;

% eigenvalues, only the smaller eigenvalue, lambda2 is needed to detect corners
% lambda1 = 0.5 * (tr + sqrt(abs(tr .^2 - 4 * dt)));
lambda2 = 0.5 * (tr - sqrt(abs(tr .^2 - 4 * dt)));

% mask out the eigenvalues on the borders 
mask = zeros(m, n);
mask(win_size+1:m-win_size, win_size+1:n-win_size) = ones(m - 2*win_size, n - 2*win_size);
lambda2 = lambda2 .* mask;

temp = lambda2 > tau;

fp = [];

% find the best corner features
for i = win_size+1:m-win_size, 
  for j = win_size+1:n-win_size,
		if temp(i, j);
			if lambda2(i, j) == max(max(lambda2(i-win_size:i+win_size, j-win_size:j+win_size)))
            num_wins = num_wins + 1;
				fp(num_wins,1)=i;
				fp(num_wins,2)=j;
				% non max supression
				temp(i-win_size:i+win_size, j-win_size:j+win_size) = zeros(win_width);
				temp(i, j) = 1;
			else 
				temp(i, j) = 0;
			end
		end
	end
end