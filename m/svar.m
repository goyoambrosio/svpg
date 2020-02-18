function svar(action,in1,in2);
%SVA: Stereo Vision Architecture
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
%  $RCSfile: svar.m,v $
%  $Revision: 1.1 $
%  $Date: 2000/01/21 13:16:24 $
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



if nargin<1,
    action='start';
end;

global R_FILENAME		%Nombre del fichero svar
global R_PATHNAME		%Path del fichero svar
global R_I			%Imagen
global R_E			%Bordes
global R_S			%Segmentos
global R_PG			%Perceptual Group
global R_PGR			%Perceptual Group Relations

global R_FID			%Manejador del fichero

global R_HIMAGE		%Handler de axes de la imagen
global R_HMSG			%Handler de axes de la zona de mensajes
global R_HPGNUMBER	%Handler del text box para seleccionar el numero de R_PG

global R_MAXLRERR		%Maximo error de regresion lineal permitido en la extraccion de segmentos
global R_MINNOPIX		%Minimo numero de pixels exigido en la extraccion de segmentos

global R_MaxDistBetwProxSegments
global R_MaxDistBetwParallelSegments
global R_MaxAngleDiffBetwParallelSegments
global R_MaxDistBetwColSegments

global R_IU
global R_ID
global R_JL
global R_JR
global R_AREA
global R_PERIMETER
global R_BCI
global R_BCJ
global R_LCI
global R_LCJ
global R_CM00
global R_CM01
global R_CM10
global R_CM02
global R_CM11
global R_CM20
global R_CM03
global R_CM12
global R_CM21
global R_CM30


if strcmp(action,'start'),

	%====================================
	% Vars inicialization
	R_FID = -1;

    %====================================
    % Graphics initialization
    %oldFigNumber = watchon;
    figNumber = figure;
    set(gcf, ...
        'NumberTitle','off', ...
        'Name','RIGHT Image. Stereo Vision Architecture.- Gregorio Ambrosio Cestero (rv.10) 2/12/98', ...
        'backingstore','off',...
        'Units','normalized');

    %====================================
    % Information for all buttons
    labelColor=192/255*[1 1 1];
    top=0.95;
    bottom=0.05;
    left=0.75;
    yInitLabelPos=0.90;
    left = 0.78;
    labelWid=0.15;
    labelHt=0.04;
    btnWid = 0.15;
    btnHt=0.045;
    % Spacing between the label and the button for the same command
    btnOffset=0.003;
    % Spacing between the button and the next command's label
    spacing=0.005;
 

    %====================================
    % COLORMAP

     colormap(gray(256));

	%====================================
    % Axes para visualizar la imagen

    R_HIMAGE=axes('Position',[.1 .35 .6 .6],...
				'XLim',[0 255],...
				'YLim',[0 255],...
				'visible','off');

    %====================================
    % CONSOLA A
    cona_xo = 0.01;
    cona_yo = 0.01;
    cona_xc = 0.99;
    cona_yc = 0.25;

    frmPos=[cona_xo cona_yo cona_xc cona_yc];
    R_HMSG=axes('Position',frmPos,...
				'XLim',[0 1],...
				'YLim',[0 1],...
				'visible','off');
	axis([0 1 0 1]);

    %h=uicontrol( ...
    %    'Style','frame', ...
    %    'Units','normalized', ...
    %    'Position',frmPos, ...
    %    'BackgroundColor',[0.8 0.8 0.8]);
	  
    %====================================
    % CONSOLA B
    conb_xo = 0.81;
    conb_yo = 0.26;
    conb_xc = 0.99;
    conb_yc = 0.99;

    frmPos=[conb_xo conb_yo conb_xc conb_yc];
    h=uicontrol( ...
        'Style','frame', ...
        'Units','normalized', ...
        'Position',frmPos, ...
        'BackgroundColor',[0.5 0.7 0.7]);
 
    %====================================
    % MENU
 
	Hmenu=uimenu('Position',1,...
			'Label','SVA File');
	H=uimenu('Parent',Hmenu,...
			'Position',1,...
			'Label','Open',...
			'Callback','svar(''load'')');
	H=uimenu('Parent',Hmenu,...
			'Position',2,...
			'Label','Exit',...
			'Separator','on',...
			'Callback','svar(''done'')');


	Hmenu=uimenu('Position',2,...
			'Label','Show');
	H=uimenu('Parent',Hmenu,...
			'Position',1,...
			'Label','Image',...
			'Callback','svar(''image'')');
	H=uimenu('Parent',Hmenu,...
			'Position',2,...
			'Label','Edges',...
			'Callback','svar(''edges'')');
	H=uimenu('Parent',Hmenu,...
			'Position',3,...
			'Label','Segments',...
			'Callback','svar(''segments'')');
	H=uimenu('Parent',Hmenu,...
			'Position',4,...
			'Label','Labels',...
			'Callback','svar(''labels'')');
	H=uimenu('Parent',Hmenu,...
			'Position',5,...
			'Label','Pcp. Groups',...
			'Callback','svar(''pgshow'')');
	H=uimenu('Parent',Hmenu,...
			'Position',6,...
			'Label','Relations',...
			'Callback','svar(''rshow'')');
	%get(Hmenu)

   %====================================
   % Boton IMAGE
    uicontrol( ...
        'Style','push', ...
        'Units','normalized', ...
        'Position',[conb_xc-btnWid conb_yc-btnHt btnWid btnHt], ...
        'String','Image', ...
        'Callback','svar(''image'')');

   %====================================
   % Boton EDGES
    uicontrol( ...
        'Style','push', ...
        'Units','normalized', ...
        'Position',[conb_xc-btnWid conb_yc-2*btnHt btnWid btnHt], ...
        'String','Edges', ...
        'Callback','svar(''edges'')');

   %====================================
   % Boton SEGMENTS
    uicontrol( ...
        'Style','push', ...
        'Units','normalized', ...
        'Position',[conb_xc-btnWid conb_yc-3*btnHt btnWid btnHt], ...
        'String','Segments', ...
        'Callback','svar(''segments'')');

   %====================================
   % Boton LABELS
    uicontrol( ...
        'Style','push', ...
        'Units','normalized', ...
        'Position',[conb_xc-btnWid conb_yc-4*btnHt btnWid btnHt], ...
        'String','Labels', ...
        'Callback','svar(''labels'')');

   %====================================
   % Boton PERCEPTUAL GROUPS
    uicontrol( ...
        'Style','push', ...
        'Units','normalized', ...
        'Position',[conb_xc-btnWid conb_yc-5*btnHt btnWid btnHt], ...
        'String','Pcp. Groups', ...
        'Callback','svar(''pgshow'')');

   %====================================
   % Text box PERCEPTUAL GROUP
    R_HPGNUMBER = uicontrol( ...
        'Style','edit', ...
        'Units','normalized', ...
        'Position',[conb_xc-btnWid conb_yc-6*btnHt btnWid btnHt], ...
        'String',' ',...
        'BackgroundColor',[0.6 0.8 0.8],...
        'CallBack','svar(''pgload'')');

   %====================================
   % Boton RELATIONS
    uicontrol( ...
        'Style','push', ...
        'Units','normalized', ...
        'Position',[conb_xc-btnWid conb_yc-7*btnHt btnWid btnHt], ...
        'String','Relations', ...
        'Callback','svar(''rshow'')');

   %====================================
   % Boton LOAD
    uicontrol( ...
        'Style','push', ...
        'Units','normalized', ...
        'Position',[conb_xc-btnWid conb_yc-15*btnHt btnWid btnHt], ...
        'String','Open', ...
        'Callback','svar(''load'')');

   %========================================
   % Boton CLOSE
    H=uicontrol(...
		'Style','Pushbutton', ...
        'Position',[conb_xc-btnWid conb_yc-16*btnHt btnWid btnHt], ...
        'Units','normalized',...
		'String','Exit',...
		'Callback','svar(''done'')');

   % watchoff(oldFigNumber);

elseif strcmp(action,'image'),
	%Si la imagen no está vacia
	if size(R_I,1)~=0
		axes(R_HIMAGE);
		image(R_I);
	end;

elseif strcmp(action,'edges'),
	%Si la imagen no está vacia
	if size(R_E,1)~=0
		image(full(R_E));
	end;

elseif strcmp(action,'segments'),
	%Si la imagen no está vacia
	if size(R_S,1)~=0
		x=rot90([R_S(:,2),R_S(:,4)])+1;
		y=rot90([R_S(:,3),R_S(:,5)])+1;
		hold on;
		H=line(y,x);
		set(H,	'Color','blue');
		%plot(R_S(:,3)+1,R_S(:,2)+1,'g.');
		%plot(R_S(:,5)+1,R_S(:,4)+1,'r.');
		hold off;
	end

elseif strcmp(action,'labels'),
	%Si la imagen no está vacia
	if size(R_S,1)~=0
		hold on;
		for i=1:size(R_S,1)
		    if R_S(i,1) <= size(R_S,1)/2
				H=text(	(R_S(i,3)+R_S(i,5))/2 - 5,...
						(R_S(i,2)+R_S(i,4))/2 - 5,...
                  num2str(R_S(i,1)));
          end
			%else
			%	H=text(	(R_S(i,3)+R_S(i,5))/2 + 5,...
			%			(R_S(i,2)+R_S(i,4))/2 + 5,...
			%			num2str(R_S(i,1)));
			%end

			set(H,	'FontName','arial',...
					'FontSize',6,...
					'FontWeight','bold',...
					'Color','red',...
					'ButtonDownFcn','svar(''textdown'')');
		end
		hold off;
	end

elseif strcmp(action,'textdown'),
	
	Label = str2num(get(gco,'String'));
	axes(R_HMSG);
	cla;
	text(0.01,1,'SEGMENT INFO   ',...
			'FontName','arial',...
			'FontSize',7,...
			'FontWeight','bold',...
			'Color','red');

	text(0.01,0.90,['MaxLRerror: ' num2str(R_MAXLRERR)],...
			'FontName','arial',...
			'FontSize',7,...
			'FontWeight','normal',...
			'Color','red');

	text(0.2,0.90,['MinNoPix: ' num2str(R_MINNOPIX)],...
			'FontName','arial',...
			'FontSize',7,...
			'FontWeight','normal',...
			'Color','red');

	text(0.01,0.80,['Label:' num2str(Label)],...
			'FontName','arial',...
			'FontSize',7,...
			'FontWeight','normal',...
			'Color','white');
	text(0.01,0.70,['(' num2str(R_S(Label,3)) ',' num2str(R_S(Label,2)) ')->(' num2str(R_S(Label,5)) ',' num2str(R_S(Label,4)) ')'],...
			'FontName','arial',...
			'FontSize',7,...
			'FontWeight','normal',...
			'Color','white');
	text(0.01,0.60,['LR error:' num2str(R_S(Label,6))],...
			'FontName','arial',...
			'FontSize',7,...
			'FontWeight','normal',...
			'Color','white');
	text(0.01,0.50,['Mean Int (+):' num2str(R_S(Label,7))],...
			'FontName','arial',...
			'FontSize',7,...
			'FontWeight','normal',...
			'Color','white');
	text(0.01,0.40,['Mean Int (-):' num2str(R_S(Label,8))],...
			'FontName','arial',...
			'FontSize',7,...
			'FontWeight','normal',...
			'Color','white');

	axes(R_HIMAGE);

elseif strcmp(action,'pgshow'),
	%Si la imagen no está vacia
	if ~isempty(R_PG)
		hold on;
      R_PG(find(R_PG>size(R_S,1)))=R_PG(find(R_PG>size(R_S,1)))-size(R_S,1);
      for i = 1:size(R_PG,1)
         H=line([R_S(R_PG(i),3),R_S(R_PG(i),5)]+1,[R_S(R_PG(i),2),R_S(R_PG(i),4)]+1);
	    	set(H,	'Color','green');
			plot(R_S(R_PG(i),3)+1,R_S(R_PG(i),2)+1,'g.');
			plot(R_S(R_PG(i),5)+1,R_S(R_PG(i),4)+1,'r.');
      end
      plot(R_BCJ+1,R_BCI+1,'yx');
      plot(R_LCJ+1,R_LCI+1,'rx');
      %plot([R_JL,R_JL]+1,[R_IU,R_ID]+1,'y.:');   
     	%plot([R_JR,R_JR]+1,[R_IU,R_ID]+1,'y.:');      
		%plot([R_JL,R_JR]+1,[R_IU,R_IU]+1,'y.:');      
		%plot([R_JL,R_JR]+1,[R_ID,R_ID]+1,'y.:');      
      
      R_AREA
      R_PERIMETER
      R_BCI
      R_BCJ
      R_LCI
      R_LCJ
      %R_IU
      %R_ID
      %R_JL
      %R_JR
      
		hold off;

		axes(R_HMSG);
		cla;

		text(0.5,1,'PG INFO   ',...
				'FontName','arial',...
				'FontSize',7,...
				'FontWeight','bold',...
				'Color','red');

		text(0.5,0.90,['Label:' num2str(str2num(get(R_HPGNUMBER,'string')))],...
				'FontName','arial',...
				'FontSize',7,...
				'FontWeight','normal',...
				'Color','red');

		text(0.5,0.80,['cm00: ' num2str(R_CM00)],...
				'FontName','arial',...
				'FontSize',7,...
				'FontWeight','normal',...
				'Color','red');
		text(0.5,0.70,['cm02: ' num2str(R_CM02)],...
				'FontName','arial',...
				'FontSize',7,...
				'FontWeight','normal',...
				'Color','red');
		text(0.5,0.60,['cm11: ' num2str(R_CM11)],...
				'FontName','arial',...
				'FontSize',7,...
				'FontWeight','normal',...
				'Color','red');
		text(0.5,0.50,['cm20: ' num2str(R_CM20)],...
				'FontName','arial',...
				'FontSize',7,...
				'FontWeight','normal',...
				'Color','red');
		text(0.5,0.40,['cm03: ' num2str(R_CM03)],...
				'FontName','arial',...
				'FontSize',7,...
				'FontWeight','normal',...
				'Color','red');
		text(0.5,0.30,['cm12: ' num2str(R_CM12)],...
				'FontName','arial',...
				'FontSize',7,...
				'FontWeight','normal',...
				'Color','red');
		text(0.5,0.20,['cm21: ' num2str(R_CM21)],...
				'FontName','arial',...
				'FontSize',7,...
				'FontWeight','normal',...
				'Color','red');
		text(0.5,0.10,['cm30: ' num2str(R_CM30)],...
				'FontName','arial',...
				'FontSize',7,...
				'FontWeight','normal',...
				'Color','red');

		axes(R_HIMAGE);
	end


elseif strcmp(action,'rshow'),
	if ~isempty(R_PGR)
		relStr2 = ...
			[	'R:<SA,SB,P,R_S>      '
				'SA -> Segment A    '
				'SB -> Segment B    '
				'P  -> Property     '
				' 0:itself          '
				' 1:proximity       '
				' 2:paralellism     '
				' 3:colinearity     '
				' 4:convexity       '
				'S  -> Significance '
				' Prob:[0..1]       '];

		R_PGR
		ttlStr = 'Relations';
		helpfun(ttlStr, relStr2);
	end

elseif strcmp(action,'load'),
	 [R_FILENAME, R_PATHNAME] = uigetfile('*.sva', 'Stereo Visual Architecture',1, 1);
    if R_FILENAME~=0 
       	[R_FID message] = fopen([R_PATHNAME R_FILENAME],'r');
			%========================
			%Esto pasa en el ordenador de mi casa
			%[R_FID message] = fopen([R_PATHNAME(1:length(R_PATHNAME)-2) R_FILENAME],'r'); %Lo de la composicion del nombre es una chapucilla porque el uigetfile no funciona demasiado bien y mete dos caracteres del R_FILENAME en el R_PATHNAME
			%========================
		if R_FID==-1
			errordlg(message,'SVA file load error',1);
		else
			%Cargo la imagen en R_I
			Shape =fread(R_FID,2,'uint');
			R_I=fread(R_FID,[Shape(1),Shape(2)],'uchar');

			%Cargo los bordes en R_E
			Shape =fread(R_FID,2,'uint');
			R_E=sparse(fread(R_FID,[Shape(1),Shape(2)],'uchar'));

			R_MAXLRERR =fread(R_FID,1,'double');
			R_MINNOPIX =fread(R_FID,1,'long');

			%Cargo los segmentos
			%SegmentMap
			%Numero de segmentos del SegmentMap
			SegCount =fread(R_FID,1,'uint')

			%Recorro el SegmentMap
			if SegCount ~= 0
				R_S=zeros(SegCount,8);
				for i1 = 1:SegCount
					%Key del SegmentMap
					Label =fread(R_FID,1,'uint');

					%Segment
					SLabel =fread(R_FID,1,'uint');
						%Vector (Straight Line)
							%Coordenadas de los extremos
							Ai =fread(R_FID,1,'double');   
							Aj =fread(R_FID,1,'double');  
							Bi =fread(R_FID,1,'double');  
							Bj =fread(R_FID,1,'double');  

							%M,N,Fi
						%	M  =fread(R_FID,1,'double');  
						%	N  =fread(R_FID,1,'double');  
						%	Fi =fread(R_FID,1,'double');  

							%A,B,C
						%	A  =fread(R_FID,1,'double');  
						%	B  =fread(R_FID,1,'double');  
						%	C  =fread(R_FID,1,'double');  

							%D,Sigma
						%	D	  =fread(R_FID,1,'double');
						%	Sigma =fread(R_FID,1,'double');  

							%HOR,VERT
						%	HOR	  =fread(R_FID,1,'int');
						%	VERT  =fread(R_FID,1,'int');

						%Con esto avanzo 72 bytes (8 doubles + 2 int)
						fseek(R_FID,72,0);

						%Proximity
						ProxCount =fread(R_FID,1,'uint');
						if ProxCount ~= 0
							%Con esto avanzo ProxCount*12 bytes(1 int + 1 double)
							fseek(R_FID,12*ProxCount,0);

							%Prox=zeros(ProxCount,2);
							%for i2 = 1:ProxCount
							%	Prox(i2,1) = fread(R_FID,1,'int');
							%	Prox(i2,2) = fread(R_FID,1,'double');
							%end
						end
						%Parallelism
						ParCount =fread(R_FID,1,'uint');
						if ParCount ~= 0
							%Con esto avanzo ParCount*12 bytes(1 int + 1 double)
							fseek(R_FID,12*ParCount,0);

							%Par=zeros(ParCount,2);
							%for i2 = 1:ParCount
							%	Par(i2,1) = fread(R_FID,1,'int');
							%	Par(i2,2) = fread(R_FID,1,'double');
							%end
						end
						%Colinearity
						ColCount =fread(R_FID,1,'uint');
						if ColCount ~= 0
							%Con esto avanzo ColCount*12 bytes(1 int + 1 double)
							fseek(R_FID,12*ColCount,0);

							%Col=zeros(ColCount,2);
							%for i2 = 1:ColCount
							%	Col(i2,1) = fread(R_FID,1,'int');
							%	Col(i2,2) = fread(R_FID,1,'double');
							%end
						end


						%POINTCHAIN
						Count =fread(R_FID,1,'uint');
						if Count ~= 0
							%Con esto avanzo Count*32 bytes(2 double)
							fseek(R_FID,16*Count,0);

							%Points=zeros(Count,2);
							%for i2 = 1:Count
							%	Points(i2,1) = fread(R_FID,1,'double');
							%	Points(i2,2) = fread(R_FID,1,'double');
							%end
							%Points
						end

						%LINE
							%Con esto avanzo 104 bytes (4 doubles + 8 doubles + 2 int)
							fseek(R_FID,104,0);


						%LINEARREGRESSIONERROR,
						%POSSIDEAVGGRAYLEVEL,
						%NEGSIDEAVGGRAYLEVEL
						LRError  =fread(R_FID,1,'double');
						PGrayLev =fread(R_FID,1,'double');
						NGrayLev =fread(R_FID,1,'double');
							%Con esto avanzo 24 bytes (3 doubles)
							%fseek(R_FID,24,0);

						%Compongo el segmento
						R_S(i1,:)=[Label,Ai,Aj,Bi,Bj,LRError,PGrayLev,NGrayLev];

					end %for i1
				end %if SegCount ~= 0

			fclose(R_FID);

			svar('image');
			%image(R_I);
		end
	end

elseif strcmp(action,'pgload'),
	 if ~isempty(R_FILENAME) 
		[R_FID message] = fopen([R_PATHNAME R_FILENAME],'r');
			%========================
			%Esto pasa en el ordenador de mi casa
			%[R_FID message] = fopen([R_PATHNAME(1:length(R_PATHNAME)-2) R_FILENAME],'r'); %Lo de la composicion del nombre es una chapucilla porque el uigetfile no funciona demasiado bien y mete dos caracteres del R_FILENAME en el R_PATHNAME
			%========================
		if R_FID==-1
			errordlg(message,'SVA file load error',1);
		else

			%leo todo hasta llegar a la zona de perceptual groups
			%leo la imagen
			Shape =fread(R_FID,2,'uint');
			fseek(R_FID,Shape(1)*Shape(2)*1,0);

			%Leo los bordes
			Shape =fread(R_FID,2,'uint');
			fseek(R_FID,Shape(1)*Shape(2)*1,0);

			%leo R_MAXLRERR y R_MINNOPIX
			fseek(R_FID,8+4,0);

			%Cargo los segmentos
			%SegmentMap
			%Numero de segmentos del SegmentMap
			SegCount =fread(R_FID,1,'uint');

			%Recorro el SegmentMap
			if SegCount ~= 0
				for i1 = 1:SegCount
					%Leo Label + Slabel + Vector
					fseek(R_FID,1*4 + 1*4 + 12*8 + 2*4,0);

					%Proximity
					ProxCount =fread(R_FID,1,'uint');
					if ProxCount ~= 0
						%Con esto avanzo ProxCount*12 bytes(1 int + 1 double)
						fseek(R_FID,12*ProxCount,0);
					end
					%Parallelism
					ParCount =fread(R_FID,1,'uint');
					if ParCount ~= 0
						%Con esto avanzo ParCount*12 bytes(1 int + 1 double)
						fseek(R_FID,12*ParCount,0);
					end
					%Colinearity
					ColCount =fread(R_FID,1,'uint');
					if ColCount ~= 0
						%Con esto avanzo ColCount*12 bytes(1 int + 1 double)
						fseek(R_FID,12*ColCount,0);
					end


					%POINTCHAIN
					Count =fread(R_FID,1,'uint');
					if Count ~= 0
						%Con esto avanzo Count*32 bytes(2 double)
						fseek(R_FID,16*Count,0);
					end

					%LINE
						%Con esto avanzo 104 bytes (4 doubles + 8 doubles + 2 int)
						fseek(R_FID,104,0);


					%LINEARREGRESSIONERROR,
					%POSSIDEAVGGRAYLEVEL,
					%NEGSIDEAVGGRAYLEVEL
					%Con esto avanzo 24 bytes (3 doubles)
					fseek(R_FID,3*8,0);

				end %for i1
			end %if SegCount ~= 0

			%PERCEPTUAL GROUP SECTION
			R_MaxDistBetwProxSegments				= fread(R_FID,1,'double');
			R_MaxDistBetwParallelSegments			= fread(R_FID,1,'double');
			R_MaxAngleDiffBetwParallelSegments	= fread(R_FID,1,'double');
			R_MaxDistBetwColSegments				= fread(R_FID,1,'double');

			%PerceptualGroupRetina (PerceptualGroupMap)
			%Numero de R_PG del PGMap
			PGCount =fread(R_FID,1,'uint');

			%Leo el pgnumber que quiero extraer del fichero
			pgnumber = str2num(get(R_HPGNUMBER,'string'))
			if isempty(pgnumber),   % handle the non-numeric case
				set(R_HPGNUMBER,'string',num2str(' 1'));
			elseif pgnumber > PGCount
				pgnumber = PGCount;
			end;

			PGLabel = 0;
			%Recorro el SegmentMap
			if PGCount ~= 0
				%for i1 = 1:PGCount
				while (PGLabel ~= pgnumber),
					%Key del PGMap
					%Label Vector
					%Numero de Labels del LabelVector
					LVCount =fread(R_FID,1,'uint');

					%Recorro el LabelVector
 					if LVCount ~= 0
                   LV = fread(R_FID,LVCount,'uint');
               end

               %item del PGMap
               %PerceptualGroup (RelationVector)
					%Numero de Relations del RelationVector
					PGLabel	= fread(R_FID,1,'uint');
					RVCount 	= fread(R_FID,1,'uint');

					%Recorro el RelationVector
					if RVCount ~= 0
						RV=zeros(RVCount,4);
						for i2 = 1:RVCount
							%PERCEPTUAL GROUP SECTION
							SALabel			= fread(R_FID,1,'uint');
							SBLabel			= fread(R_FID,1,'uint');
							Property			= fread(R_FID,1,'uint');
							Significance	= fread(R_FID,1,'double');
							RV(i2,:)=[SALabel SBLabel Property Significance];
						end %for  i2 = 1:RVCount
					end %if RVCount ~= 0
               
               %Obtengo la información de características del polígono
    				%R_IU        	= fread(R_FID,1,'double');
    				%R_ID	         = fread(R_FID,1,'double');
    				%R_JL	         = fread(R_FID,1,'double');
    				%R_JR	         = fread(R_FID,1,'double');
      			R_AREA	      = fread(R_FID,1,'double');
    				R_PERIMETER	= fread(R_FID,1,'double');
    				R_BCI	= fread(R_FID,1,'double');
    				R_BCJ	= fread(R_FID,1,'double');
    				R_LCI	= fread(R_FID,1,'double');
    				R_LCJ	= fread(R_FID,1,'double');
    				R_CM00        	= fread(R_FID,1,'double');
    				R_CM01       	= fread(R_FID,1,'double');    
    				R_CM10        	= fread(R_FID,1,'double');
    				R_CM02        	= fread(R_FID,1,'double');
    				R_CM11       	= fread(R_FID,1,'double');
    				R_CM20        	= fread(R_FID,1,'double');
    				R_CM03        	= fread(R_FID,1,'double');
    				R_CM12       	= fread(R_FID,1,'double');
    				R_CM21        	= fread(R_FID,1,'double');
    				R_CM30        	= fread(R_FID,1,'double');
                
                
               if PGLabel == pgnumber
						R_PG		= LV;
						R_PGR 	= RV;
					end					
				end %while
				svar('pgshow');
			end %if PGCount ~= 0
			fclose(R_FID);
		end
	end


elseif strcmp(action,'done'),


    clear global R_FILENAME;
    clear global R_PATHNAME;
    clear global R_I;
    clear global R_E;
    clear global R_S;
    clear global R_PG;
    clear global R_PGR;

	clear R_HIMAGE;
	clear R_HMSG;

	clear R_MAXLRERR;
	clear R_MINNOPIX;

	clear R_MaxDistBetwProxSegments;
	clear R_MaxDistBetwParallelSegments;
	clear R_MaxAngleDiffBetwParallelSegments;
	clear R_MaxDistBetwColSegments;

    close(gcf);

end

