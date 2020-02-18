function fvvfcn(action,feature)
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
%  $RCSfile: fvvfcn.m,v $
%  $Revision: 1.1 $
%  $Date: 2000/01/21 13:15:46 $
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

global L_FILENAME		%Nombre del fichero sva
global L_PATHNAME		%Path del fichero sva
global LFV
global R_FILENAME		%Nombre del fichero sva
global R_PATHNAME		%Path del fichero sva
global RFV
global OLDX
global OLDY
global FX
global FY
global FZ

switch action
   
case 'start'
   H_Radiobutton3D       = findobj(gcbf,'Tag','Radiobutton3D');
   Radiobutton3D         = get(H_Radiobutton3D,'Value');
   if Radiobutton3D
		set(gcbf,'WindowButtonMotionFcn','fvvfcn move')
		set(gcbf,'WindowButtonUpFcn','fvvfcn stop')
   	currentPoint = get(gcbf,'CurrentPoint');
   	OLDX = currentPoint(1,1);
   	OLDY = currentPoint(1,2);
      fvvfcn move
   end
case 'move'
	   currentPoint = get(gcbf,'CurrentPoint');
   	newX = currentPoint(1,1);
   	newY = currentPoint(1,2);
   	[AZ EL] = view;
   	view(AZ-(newX-OLDX),EL-(newY-OLDY));
   	OLDX = newX;
   	OLDY = newY;
case 'stop'
	set(gcbf,'WindowButtonMotionFcn','');
   set(gcbf,'WindowButtonUpFcn','');
case 'LoadLfv'
   [L_FILENAME, L_PATHNAME] = uigetfile('*.fv', 'Feature Vector Visualizer',1, 1);
   if L_FILENAME~=0 
      [fid message] = fopen([L_PATHNAME L_FILENAME],'r');
		if fid==-1
			errordlg(message,'FV file load error',1);
		else
			Size = fread(fid,1,'uint');
         LFV = fread(fid,[19,Size],'double');
      end
   end
   FX=4;
   FY=5;
   FZ=6;
   set(gca,'XLimMode','auto');
   set(gca,'YLimMode','auto');
   set(gca,'ZLimMode','auto');
   PlotFV;
case 'LoadRfv'
   [R_FILENAME, R_PATHNAME] = uigetfile('*.fv', 'Feature Vector Visualizer',1, 1);
   if R_FILENAME~=0 
      [fid message] = fopen([R_PATHNAME R_FILENAME],'r');
		if fid==-1
			errordlg(message,'FV file load error',1);
		else
			Size = fread(fid,1,'uint');
         RFV = fread(fid,[19,Size],'double');
      end
   end
   FX=4;
   FY=5;
   FZ=6;
   set(gca,'XLimMode','auto');
   set(gca,'YLimMode','auto');
   set(gca,'ZLimMode','auto');
   PlotFV;
case 'Plot'
   PlotFV;
case '2D'
   H_Radiobutton3D = findobj(gcbf,'Tag','Radiobutton3D');
   set(H_Radiobutton3D,'Value',0);
   view(2);
   PlotFV;
case '3D'
   H_Radiobutton2D = findobj(gcbf,'Tag','Radiobutton2D');
   set(H_Radiobutton2D,'Value',0);
   view(3);
   PlotFV;
case 'Clear'
	clear global L_FILENAME		%Nombre del fichero sva
	clear global L_PATHNAME		%Path del fichero sva
	clear global LFV;
	clear global R_FILENAME		%Nombre del fichero sva
	clear global R_PATHNAME		%Path del fichero sva
	clear global RFV
	clear global OLDX
	clear global OLDY
	FX = 4;
	FY = 5;
	FZ = 6;
   cla;
case 'Panic'
   LFV = [];
   RFV = [];
   FX=4;
   FY=5;
   FZ=6;
   set(gca,'XLimMode','auto');
   set(gca,'YLimMode','auto');
   set(gca,'ZLimMode','auto');
   cla;
   
case 'FeatureX'
   H_RadiobuttonArea      = findobj(gcbf,'Tag','RadiobuttonXArea');
	H_RadiobuttonPerimeter = findobj(gcbf,'Tag','RadiobuttonXPerimeter');
   H_Radiobuttoncm00      = findobj(gcbf,'Tag','RadiobuttonXcm00');
	H_Radiobuttoncm02      = findobj(gcbf,'Tag','RadiobuttonXcm02');
   H_Radiobuttoncm11      = findobj(gcbf,'Tag','RadiobuttonXcm11');
	H_Radiobuttoncm20      = findobj(gcbf,'Tag','RadiobuttonXcm20');
   H_Radiobuttoncm03      = findobj(gcbf,'Tag','RadiobuttonXcm03');
	H_Radiobuttoncm12      = findobj(gcbf,'Tag','RadiobuttonXcm12');
   H_Radiobuttoncm21      = findobj(gcbf,'Tag','RadiobuttonXcm21');
   H_Radiobuttoncm30      = findobj(gcbf,'Tag','RadiobuttonXcm30');
   H_Radiobuttonbci       = findobj(gcbf,'Tag','RadiobuttonXbci');
   H_Radiobuttonbcj       = findobj(gcbf,'Tag','RadiobuttonXbcj');
   H_Radiobuttonlci       = findobj(gcbf,'Tag','RadiobuttonXlci');
   H_Radiobuttonlcj       = findobj(gcbf,'Tag','RadiobuttonXlcj');
   
   set(H_RadiobuttonArea,'Value',0);
   set(H_RadiobuttonPerimeter,'Value',0);
   set(H_Radiobuttoncm00,'Value',0);
   set(H_Radiobuttoncm02,'Value',0);
   set(H_Radiobuttoncm11,'Value',0);
   set(H_Radiobuttoncm20,'Value',0);
   set(H_Radiobuttoncm03,'Value',0);
   set(H_Radiobuttoncm12,'Value',0);
   set(H_Radiobuttoncm21,'Value',0);
   set(H_Radiobuttoncm30,'Value',0);
   set(H_Radiobuttonbci,'Value',0);
   set(H_Radiobuttonbcj,'Value',0);
   set(H_Radiobuttonlci,'Value',0);
   set(H_Radiobuttonlcj,'Value',0);
   
	switch feature
	case 4
   	set(H_RadiobuttonArea,'Value',1);
	case 5
	   set(H_RadiobuttonPerimeter,'Value',1);
	case 6
	   set(H_Radiobuttonbci,'Value',1);
	case 7
	   set(H_Radiobuttonbcj,'Value',1);
	case 8
	   set(H_Radiobuttonlci,'Value',1);
	case 9
	   set(H_Radiobuttonlcj,'Value',1);
	case 10
   	set(H_Radiobuttoncm00,'Value',1);
	case 13
   	set(H_Radiobuttoncm02,'Value',1);
	case 14
   	set(H_Radiobuttoncm11,'Value',1);
	case 15
   	set(H_Radiobuttoncm20,'Value',1);
	case 16
   	set(H_Radiobuttoncm03,'Value',1);
	case 17
   	set(H_Radiobuttoncm12,'Value',1);
	case 18
   	set(H_Radiobuttoncm21,'Value',1);
	case 19
   	set(H_Radiobuttoncm30,'Value',1);
	end
	FX = feature;
   PlotFV;
   
case 'FeatureY'
   H_RadiobuttonArea      = findobj(gcbf,'Tag','RadiobuttonYArea');
	H_RadiobuttonPerimeter = findobj(gcbf,'Tag','RadiobuttonYPerimeter');
   H_Radiobuttoncm00      = findobj(gcbf,'Tag','RadiobuttonYcm00');
	H_Radiobuttoncm02      = findobj(gcbf,'Tag','RadiobuttonYcm02');
   H_Radiobuttoncm11      = findobj(gcbf,'Tag','RadiobuttonYcm11');
	H_Radiobuttoncm20      = findobj(gcbf,'Tag','RadiobuttonYcm20');
   H_Radiobuttoncm03      = findobj(gcbf,'Tag','RadiobuttonYcm03');
	H_Radiobuttoncm12      = findobj(gcbf,'Tag','RadiobuttonYcm12');
   H_Radiobuttoncm21      = findobj(gcbf,'Tag','RadiobuttonYcm21');
   H_Radiobuttoncm30      = findobj(gcbf,'Tag','RadiobuttonYcm30');
   H_Radiobuttonbci       = findobj(gcbf,'Tag','RadiobuttonYbci');
   H_Radiobuttonbcj       = findobj(gcbf,'Tag','RadiobuttonYbcj');
   H_Radiobuttonlci       = findobj(gcbf,'Tag','RadiobuttonYlci');
   H_Radiobuttonlcj       = findobj(gcbf,'Tag','RadiobuttonYlcj');
   
   set(H_RadiobuttonArea,'Value',0);
   set(H_RadiobuttonPerimeter,'Value',0);
   set(H_Radiobuttoncm00,'Value',0);
   set(H_Radiobuttoncm02,'Value',0);
   set(H_Radiobuttoncm11,'Value',0);
   set(H_Radiobuttoncm20,'Value',0);
   set(H_Radiobuttoncm03,'Value',0);
   set(H_Radiobuttoncm12,'Value',0);
   set(H_Radiobuttoncm21,'Value',0);
   set(H_Radiobuttoncm30,'Value',0);
   set(H_Radiobuttonbci,'Value',0);
   set(H_Radiobuttonbcj,'Value',0);
   set(H_Radiobuttonlci,'Value',0);
   set(H_Radiobuttonlcj,'Value',0);
   
	switch feature
	case 4
   	set(H_RadiobuttonArea,'Value',1);
	case 5
	   set(H_RadiobuttonPerimeter,'Value',1);
	case 6
	   set(H_Radiobuttonbci,'Value',1);
	case 7
	   set(H_Radiobuttonbcj,'Value',1);
	case 8
	   set(H_Radiobuttonlci,'Value',1);
	case 9
	   set(H_Radiobuttonlcj,'Value',1);
	case 10
   	set(H_Radiobuttoncm00,'Value',1);
	case 13
   	set(H_Radiobuttoncm02,'Value',1);
	case 14
   	set(H_Radiobuttoncm11,'Value',1);
	case 15
   	set(H_Radiobuttoncm20,'Value',1);
	case 16
   	set(H_Radiobuttoncm03,'Value',1);
	case 17
   	set(H_Radiobuttoncm12,'Value',1);
	case 18
   	set(H_Radiobuttoncm21,'Value',1);
	case 19
   	set(H_Radiobuttoncm30,'Value',1);
	end
	FY = feature;
   PlotFV;
   
case 'FeatureZ'
   H_RadiobuttonArea      = findobj(gcbf,'Tag','RadiobuttonZArea');
	H_RadiobuttonPerimeter = findobj(gcbf,'Tag','RadiobuttonZPerimeter');
   H_Radiobuttoncm00      = findobj(gcbf,'Tag','RadiobuttonZcm00');
	H_Radiobuttoncm02      = findobj(gcbf,'Tag','RadiobuttonZcm02');
   H_Radiobuttoncm11      = findobj(gcbf,'Tag','RadiobuttonZcm11');
	H_Radiobuttoncm20      = findobj(gcbf,'Tag','RadiobuttonZcm20');
   H_Radiobuttoncm03      = findobj(gcbf,'Tag','RadiobuttonZcm03');
	H_Radiobuttoncm12      = findobj(gcbf,'Tag','RadiobuttonZcm12');
   H_Radiobuttoncm21      = findobj(gcbf,'Tag','RadiobuttonZcm21');
   H_Radiobuttoncm30      = findobj(gcbf,'Tag','RadiobuttonZcm30');
   H_Radiobuttonbci       = findobj(gcbf,'Tag','RadiobuttonZbci');
   H_Radiobuttonbcj       = findobj(gcbf,'Tag','RadiobuttonZbcj');
   H_Radiobuttonlci       = findobj(gcbf,'Tag','RadiobuttonZlci');
   H_Radiobuttonlcj       = findobj(gcbf,'Tag','RadiobuttonZlcj');
   
   set(H_RadiobuttonArea,'Value',0);
   set(H_RadiobuttonPerimeter,'Value',0);
   set(H_Radiobuttoncm00,'Value',0);
   set(H_Radiobuttoncm02,'Value',0);
   set(H_Radiobuttoncm11,'Value',0);
   set(H_Radiobuttoncm20,'Value',0);
   set(H_Radiobuttoncm03,'Value',0);
   set(H_Radiobuttoncm12,'Value',0);
   set(H_Radiobuttoncm21,'Value',0);
   set(H_Radiobuttoncm30,'Value',0);
   set(H_Radiobuttonbci,'Value',0);
   set(H_Radiobuttonbcj,'Value',0);
   set(H_Radiobuttonlci,'Value',0);
   set(H_Radiobuttonlcj,'Value',0);
  
	switch feature
	case 4
   	set(H_RadiobuttonArea,'Value',1);
	case 5
	   set(H_RadiobuttonPerimeter,'Value',1);
	case 6
	   set(H_Radiobuttonbci,'Value',1);
	case 7
	   set(H_Radiobuttonbcj,'Value',1);
	case 8
	   set(H_Radiobuttonlci,'Value',1);
	case 9
	   set(H_Radiobuttonlcj,'Value',1);
	case 10
   	set(H_Radiobuttoncm00,'Value',1);
	case 13
   	set(H_Radiobuttoncm02,'Value',1);
	case 14
   	set(H_Radiobuttoncm11,'Value',1);
	case 15
   	set(H_Radiobuttoncm20,'Value',1);
	case 16
   	set(H_Radiobuttoncm03,'Value',1);
	case 17
   	set(H_Radiobuttoncm12,'Value',1);
	case 18
   	set(H_Radiobuttoncm21,'Value',1);
	case 19
   	set(H_Radiobuttoncm30,'Value',1);
	end
	FZ = feature;
	PlotFV;

end

function PlotFV
   
global LFV
global RFV
global FX
global FY
global FZ

H_CheckboxShowSubL     = findobj(gcbf,'Tag','CheckboxShowSubL');
H_CheckboxShowSubR     = findobj(gcbf,'Tag','CheckboxShowSubR');
H_CheckboxVisibleLeft  = findobj(gcbf,'Tag','CheckboxVisibleLeft');
H_CheckboxVisibleRight = findobj(gcbf,'Tag','CheckboxVisibleRight');
H_CheckboxLabelsLeft   = findobj(gcbf,'Tag','CheckboxLabelsLeft');
H_CheckboxLabelsRight  = findobj(gcbf,'Tag','CheckboxLabelsRight');
H_Radiobutton2D        = findobj(gcbf,'Tag','Radiobutton2D');
H_Radiobutton3D        = findobj(gcbf,'Tag','Radiobutton3D');

CheckboxShowSubL      = get(H_CheckboxShowSubL,'Value');
CheckboxShowSubR      = get(H_CheckboxShowSubR,'Value');
CheckboxVisibleLeft   = get(H_CheckboxVisibleLeft,'Value');
CheckboxVisibleRight  = get(H_CheckboxVisibleRight,'Value');
CheckboxLabelsLeft    = get(H_CheckboxLabelsLeft,'Value');
CheckboxLabelsRight   = get(H_CheckboxLabelsRight,'Value');
Radiobutton2D         = get(H_Radiobutton2D,'Value');
Radiobutton3D         = get(H_Radiobutton3D,'Value');

cla;
hold on;

if (CheckboxVisibleLeft & size(LFV))
   if CheckboxShowSubL == 0
      FV = LFV(:,find(LFV(3,:)==0));
   else
      FV = LFV;
   end
   if CheckboxLabelsLeft
      if Radiobutton2D
         view(2);
         plot (FV(FX,:),FV(FY,:),'w.');
      	for j=1:size(FV,2)
         	H=text(FV(FX,j),FV(FY,j),num2str(FV(1,j)));
      		set(H,'FontName','arial',...
         			'FontSize',8,...
         			'FontWeight','normal',...
         			'Color','red',...
               	'ButtonDownFcn','fvvfcn(''textdown'')');
         end
      else
         view(3);
         plot3 (FV(FX,:),FV(FY,:),FV(FZ,:),'w.');
     		for j=1:size(FV,2)
         	H=text(FV(FX,j),FV(FY,j),FV(FZ,j),num2str(FV(1,j)));
      		set(H,'FontName','arial',...
         			'FontSize',8,...
         			'FontWeight','normal',...
         			'Color','red',...
               	'ButtonDownFcn','fvvfcn(''textdown'')');
         end
      end
   else
     if Radiobutton2D
         view(2);
         plot (FV(FX,:),FV(FY,:),'r.');
      else
      	view(3);
         plot3 (FV(FX,:),FV(FY,:),FV(FZ,:),'r.');
      end
   end
end

if (CheckboxVisibleRight & size(RFV))
   if CheckboxShowSubR == 0
      FV = RFV(:,find(RFV(3,:)==0));
   else
      FV = RFV;
   end
   if CheckboxLabelsRight
      if Radiobutton2D
         view(2);
         plot (FV(FX,:),FV(FY,:),'w.');
       	for j=1:size(FV,2)
         	H=text(FV(FX,j),FV(FY,j),num2str(FV(1,j)));
      		set(H,'FontName','arial',...
         			'FontSize',8,...
         			'FontWeight','normal',...
         			'Color','blue',...
               	'ButtonDownFcn','fvvfcn(''textdown'')');
         end
      else
         view(3);
         plot3 (FV(FX,:),FV(FY,:),FV(FZ,:),'w.');
      	for j=1:size(FV,2)
         	H=text(FV(FX,j),FV(FY,j),FV(FZ,j),num2str(FV(1,j)));
      		set(H,'FontName','arial',...
         			'FontSize',8,...
         			'FontWeight','normal',...
         			'Color','blue',...
               	'ButtonDownFcn','fvvfcn(''textdown'')');
         end
      end
   else
      if Radiobutton2D
         view(2);
         plot (FV(FX,:),FV(FY,:),'b.');
      else
      	view(3);
         plot3 (FV(FX,:),FV(FY,:),FV(FZ,:),'b.');
      end
   end
end

hold off;
     

