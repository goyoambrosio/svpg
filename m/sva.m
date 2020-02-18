function sva(action,in1,in2);
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
%  $RCSfile: sva.m,v $
%  $Revision: 1.1 $
%  $Date: 2000/01/21 13:16:22 $
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

global FILENAME		%Nombre del fichero sva
global PATHNAME		%Path del fichero sva
global I			%Imagen
global E			%Bordes
global S			%Segmentos
global PG			%Perceptual Group
global PGR			%Perceptual Group Relations

global fid			%Manejador del fichero

global Himage		%Handler de axes de la imagen
global Hmsg			%Handler de axes de la zona de mensajes
global Hpgnumber	%Handler del text box para seleccionar el numero de PG

global MaxLRErr		%Maximo error de regresion lineal permitido en la extraccion de segmentos
global MinNoPix		%Minimo numero de pixels exigido en la extraccion de segmentos

global MaxDistBetwProxSegments
global MaxDistBetwParallelSegments
global MaxAngleDiffBetwParallelSegments
global MaxDistBetwColSegments

global IU
global ID
global JL
global JR
global Area
global Perimeter
global Centroid_bi
global Centroid_bj
global Centroid_gi
global Centroid_gj
global m00
global m01
global m10
global m02
global m11
global m20
global m03
global m12
global m21
global m30


if strcmp(action,'start'),

	%====================================
	% Vars inicialization
	fid = -1;

    %====================================
    % Graphics initialization
    oldFigNumber = watchon;
    figNumber = figure;
    set(gcf, ...
        'NumberTitle','off', ...
        'Name','Stereo Vision Architecture.- Gregorio Ambrosio Cestero (rv.10) 2/12/98', ...
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

    Himage=axes('Position',[.1 .35 .6 .6],...
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
    Hmsg=axes('Position',frmPos,...
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
			'Callback','sva(''load'')');
	H=uimenu('Parent',Hmenu,...
			'Position',2,...
			'Label','Exit',...
			'Separator','on',...
			'Callback','sva(''done'')');


	Hmenu=uimenu('Position',2,...
			'Label','Show');
	H=uimenu('Parent',Hmenu,...
			'Position',1,...
			'Label','Image',...
			'Callback','sva(''image'')');
	H=uimenu('Parent',Hmenu,...
			'Position',2,...
			'Label','Edges',...
			'Callback','sva(''edges'')');
	H=uimenu('Parent',Hmenu,...
			'Position',3,...
			'Label','Segments',...
			'Callback','sva(''segments'')');
	H=uimenu('Parent',Hmenu,...
			'Position',4,...
			'Label','Labels',...
			'Callback','sva(''labels'')');
	H=uimenu('Parent',Hmenu,...
			'Position',5,...
			'Label','Pcp. Groups',...
			'Callback','sva(''pgshow'')');
	H=uimenu('Parent',Hmenu,...
			'Position',6,...
			'Label','Relations',...
			'Callback','sva(''rshow'')');
	%get(Hmenu)

   %====================================
   % Boton IMAGE
    uicontrol( ...
        'Style','push', ...
        'Units','normalized', ...
        'Position',[conb_xc-btnWid conb_yc-btnHt btnWid btnHt], ...
        'String','Image', ...
        'Callback','sva(''image'')');

   %====================================
   % Boton EDGES
    uicontrol( ...
        'Style','push', ...
        'Units','normalized', ...
        'Position',[conb_xc-btnWid conb_yc-2*btnHt btnWid btnHt], ...
        'String','Edges', ...
        'Callback','sva(''edges'')');

   %====================================
   % Boton SEGMENTS
    uicontrol( ...
        'Style','push', ...
        'Units','normalized', ...
        'Position',[conb_xc-btnWid conb_yc-3*btnHt btnWid btnHt], ...
        'String','Segments', ...
        'Callback','sva(''segments'')');

   %====================================
   % Boton LABELS
    uicontrol( ...
        'Style','push', ...
        'Units','normalized', ...
        'Position',[conb_xc-btnWid conb_yc-4*btnHt btnWid btnHt], ...
        'String','Labels', ...
        'Callback','sva(''labels'')');

   %====================================
   % Boton PERCEPTUAL GROUPS
    uicontrol( ...
        'Style','push', ...
        'Units','normalized', ...
        'Position',[conb_xc-btnWid conb_yc-5*btnHt btnWid btnHt], ...
        'String','Pcp. Groups', ...
        'Callback','sva(''pgshow'')');

   %====================================
   % Text box PERCEPTUAL GROUP
    Hpgnumber = uicontrol( ...
        'Style','edit', ...
        'Units','normalized', ...
        'Position',[conb_xc-btnWid conb_yc-6*btnHt btnWid btnHt], ...
        'String',' ',...
        'BackgroundColor',[0.6 0.8 0.8],...
        'CallBack','sva(''pgload'')');

   %====================================
   % Boton RELATIONS
    uicontrol( ...
        'Style','push', ...
        'Units','normalized', ...
        'Position',[conb_xc-btnWid conb_yc-7*btnHt btnWid btnHt], ...
        'String','Relations', ...
        'Callback','sva(''rshow'')');

   %====================================
   % Boton LOAD
    uicontrol( ...
        'Style','push', ...
        'Units','normalized', ...
        'Position',[conb_xc-btnWid conb_yc-15*btnHt btnWid btnHt], ...
        'String','Open', ...
        'Callback','sva(''load'')');

   %========================================
   % Boton CLOSE
    H=uicontrol(...
		'Style','Pushbutton', ...
        'Position',[conb_xc-btnWid conb_yc-16*btnHt btnWid btnHt], ...
        'Units','normalized',...
		'String','Exit',...
		'Callback','sva(''done'')');

    watchoff(oldFigNumber);

elseif strcmp(action,'image'),
	%Si la imagen no está vacia
	if size(I,1)~=0
		axes(Himage);
		image(I);
	end;

elseif strcmp(action,'edges'),
	%Si la imagen no está vacia
	if size(E,1)~=0
		image(full(E));
	end;

elseif strcmp(action,'segments'),
	%Si la imagen no está vacia
	if size(S,1)~=0
		x=rot90([S(:,2),S(:,4)])+1;
		y=rot90([S(:,3),S(:,5)])+1;
		hold on;
		H=line(y,x);
		set(H,	'Color','blue');
		%plot(S(:,3)+1,S(:,2)+1,'g.');
		%plot(S(:,5)+1,S(:,4)+1,'r.');
		hold off;
	end

elseif strcmp(action,'labels'),
	%Si la imagen no está vacia
	if size(S,1)~=0
		hold on;
		for i=1:size(S,1)
		    %if S(i,1) <= size(S,1)/2
				H=text(	(S(i,3)+S(i,5))/2 - 5,...
						(S(i,2)+S(i,4))/2 - 5,...
                  num2str(S(i,1)));
          %end
			%else
			%	H=text(	(S(i,3)+S(i,5))/2 + 5,...
			%			(S(i,2)+S(i,4))/2 + 5,...
			%			num2str(S(i,1)));
			%end

			set(H,	'FontName','arial',...
					'FontSize',6,...
					'FontWeight','bold',...
					'Color','red',...
					'ButtonDownFcn','sva(''textdown'')');
		end
		hold off;
	end

elseif strcmp(action,'textdown'),
	
	Label = str2num(get(gco,'String'));
	axes(Hmsg);
	cla;
	text(0.01,1,'SEGMENT INFO   ',...
			'FontName','arial',...
			'FontSize',7,...
			'FontWeight','bold',...
			'Color','red');

	text(0.01,0.90,['MaxLRerror: ' num2str(MaxLRErr)],...
			'FontName','arial',...
			'FontSize',7,...
			'FontWeight','normal',...
			'Color','red');

	text(0.2,0.90,['MinNoPix: ' num2str(MinNoPix)],...
			'FontName','arial',...
			'FontSize',7,...
			'FontWeight','normal',...
			'Color','red');

	text(0.01,0.80,['Label:' num2str(Label)],...
			'FontName','arial',...
			'FontSize',7,...
			'FontWeight','normal',...
			'Color','white');
	text(0.01,0.70,['(' num2str(S(Label,3)) ',' num2str(S(Label,2)) ')->(' num2str(S(Label,5)) ',' num2str(S(Label,4)) ')'],...
			'FontName','arial',...
			'FontSize',7,...
			'FontWeight','normal',...
			'Color','white');
	text(0.01,0.60,['LR error:' num2str(S(Label,6))],...
			'FontName','arial',...
			'FontSize',7,...
			'FontWeight','normal',...
			'Color','white');
	text(0.01,0.50,['Mean Int (+):' num2str(S(Label,7))],...
			'FontName','arial',...
			'FontSize',7,...
			'FontWeight','normal',...
			'Color','white');
	text(0.01,0.40,['Mean Int (-):' num2str(S(Label,8))],...
			'FontName','arial',...
			'FontSize',7,...
			'FontWeight','normal',...
			'Color','white');

	axes(Himage);

elseif strcmp(action,'pgshow'),
	%Si la imagen no está vacia
	if ~isempty(PG)
		hold on;
      PG(find(PG>size(S,1)))=PG(find(PG>size(S,1)))-size(S,1);
      for i = 1:size(PG,1)
         H=line([S(PG(i),3),S(PG(i),5)]+1,[S(PG(i),2),S(PG(i),4)]+1);
	    	set(H,	'Color','green');
			plot(S(PG(i),3)+1,S(PG(i),2)+1,'g.');
			plot(S(PG(i),5)+1,S(PG(i),4)+1,'r.');
      end
      plot(Centroid_bj+1,Centroid_bi+1,'yx');
      plot(Centroid_gj+1,Centroid_gi+1,'rx');
      %plot([JL,JL]+1,[IU,ID]+1,'y.:');   
     	%plot([JR,JR]+1,[IU,ID]+1,'y.:');      
		%plot([JL,JR]+1,[IU,IU]+1,'y.:');      
		%plot([JL,JR]+1,[ID,ID]+1,'y.:');      
      
      Area
      Perimeter
      Centroid_bi
      Centroid_bj
      Centroid_gi
      Centroid_gj
      %IU
      %ID
      %JL
      %JR
      
		hold off;

		axes(Hmsg);
		cla;

		text(0.5,1,'PG INFO   ',...
				'FontName','arial',...
				'FontSize',7,...
				'FontWeight','bold',...
				'Color','red');

		text(0.5,0.90,['Label:' num2str(str2num(get(Hpgnumber,'string')))],...
				'FontName','arial',...
				'FontSize',7,...
				'FontWeight','normal',...
				'Color','red');

		text(0.5,0.80,['m1: ' num2str(m00)],...
				'FontName','arial',...
				'FontSize',7,...
				'FontWeight','normal',...
				'Color','red');
		text(0.5,0.70,['m2: ' num2str(m02)],...
				'FontName','arial',...
				'FontSize',7,...
				'FontWeight','normal',...
				'Color','red');
		text(0.5,0.60,['m3: ' num2str(m11)],...
				'FontName','arial',...
				'FontSize',7,...
				'FontWeight','normal',...
				'Color','red');
		text(0.5,0.50,['m4: ' num2str(m20)],...
				'FontName','arial',...
				'FontSize',7,...
				'FontWeight','normal',...
				'Color','red');
		text(0.5,0.40,['m5: ' num2str(m03)],...
				'FontName','arial',...
				'FontSize',7,...
				'FontWeight','normal',...
				'Color','red');
		text(0.5,0.30,['m6: ' num2str(m12)],...
				'FontName','arial',...
				'FontSize',7,...
				'FontWeight','normal',...
				'Color','red');
		text(0.5,0.20,['m7: ' num2str(m21)],...
				'FontName','arial',...
				'FontSize',7,...
				'FontWeight','normal',...
				'Color','red');
		text(0.5,0.10,['m7: ' num2str(m30)],...
				'FontName','arial',...
				'FontSize',7,...
				'FontWeight','normal',...
				'Color','red');

		axes(Himage);
	end


elseif strcmp(action,'rshow'),
	if ~isempty(PGR)
		relStr2 = ...
			[	'R:<SA,SB,P,S>      '
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

		PGR
		ttlStr = 'Relations';
		helpfun(ttlStr, relStr2);
	end

elseif strcmp(action,'load'),
	 [FILENAME, PATHNAME] = uigetfile('*.sva', 'Stereo Visual Architecture',1, 1);
    if FILENAME~=0 
       	[fid message] = fopen([PATHNAME FILENAME],'r');
			%========================
			%Esto pasa en el ordenador de mi casa
			%[fid message] = fopen([PATHNAME(1:length(PATHNAME)-2) FILENAME],'r'); %Lo de la composicion del nombre es una chapucilla porque el uigetfile no funciona demasiado bien y mete dos caracteres del FILENAME en el PATHNAME
			%========================
		if fid==-1
			errordlg(message,'SVA file load error',1);
		else
			%Cargo la imagen en I
			Shape =fread(fid,2,'uint');
			I=fread(fid,[Shape(1),Shape(2)],'uchar');

			%Cargo los bordes en E
			Shape =fread(fid,2,'uint');
			E=sparse(fread(fid,[Shape(1),Shape(2)],'uchar'));

			MaxLRErr =fread(fid,1,'double');
			MinNoPix =fread(fid,1,'long');

			%Cargo los segmentos
			%SegmentMap
			%Numero de segmentos del SegmentMap
			SegCount =fread(fid,1,'uint')

			%Recorro el SegmentMap
			if SegCount ~= 0
				S=zeros(SegCount,8);
				for i1 = 1:SegCount
					%Key del SegmentMap
					Label =fread(fid,1,'uint');

					%Segment
					SLabel =fread(fid,1,'uint');
						%Vector (Straight Line)
							%Coordenadas de los extremos
							Ai =fread(fid,1,'double');   
							Aj =fread(fid,1,'double');  
							Bi =fread(fid,1,'double');  
							Bj =fread(fid,1,'double');  

							%M,N,Fi
						%	M  =fread(fid,1,'double');  
						%	N  =fread(fid,1,'double');  
						%	Fi =fread(fid,1,'double');  

							%A,B,C
						%	A  =fread(fid,1,'double');  
						%	B  =fread(fid,1,'double');  
						%	C  =fread(fid,1,'double');  

							%D,Sigma
						%	D	  =fread(fid,1,'double');
						%	Sigma =fread(fid,1,'double');  

							%HOR,VERT
						%	HOR	  =fread(fid,1,'int');
						%	VERT  =fread(fid,1,'int');

						%Con esto avanzo 72 bytes (8 doubles + 2 int)
						fseek(fid,72,0);

						%Proximity
						ProxCount =fread(fid,1,'uint');
						if ProxCount ~= 0
							%Con esto avanzo ProxCount*12 bytes(1 int + 1 double)
							fseek(fid,12*ProxCount,0);

							%Prox=zeros(ProxCount,2);
							%for i2 = 1:ProxCount
							%	Prox(i2,1) = fread(fid,1,'int');
							%	Prox(i2,2) = fread(fid,1,'double');
							%end
						end
						%Parallelism
						ParCount =fread(fid,1,'uint');
						if ParCount ~= 0
							%Con esto avanzo ParCount*12 bytes(1 int + 1 double)
							fseek(fid,12*ParCount,0);

							%Par=zeros(ParCount,2);
							%for i2 = 1:ParCount
							%	Par(i2,1) = fread(fid,1,'int');
							%	Par(i2,2) = fread(fid,1,'double');
							%end
						end
						%Colinearity
						ColCount =fread(fid,1,'uint');
						if ColCount ~= 0
							%Con esto avanzo ColCount*12 bytes(1 int + 1 double)
							fseek(fid,12*ColCount,0);

							%Col=zeros(ColCount,2);
							%for i2 = 1:ColCount
							%	Col(i2,1) = fread(fid,1,'int');
							%	Col(i2,2) = fread(fid,1,'double');
							%end
						end


						%POINTCHAIN
						Count =fread(fid,1,'uint');
						if Count ~= 0
							%Con esto avanzo Count*32 bytes(2 double)
							fseek(fid,16*Count,0);

							%Points=zeros(Count,2);
							%for i2 = 1:Count
							%	Points(i2,1) = fread(fid,1,'double');
							%	Points(i2,2) = fread(fid,1,'double');
							%end
							%Points
						end

						%LINE
							%Con esto avanzo 104 bytes (4 doubles + 8 doubles + 2 int)
							fseek(fid,104,0);


						%LINEARREGRESSIONERROR,
						%POSSIDEAVGGRAYLEVEL,
						%NEGSIDEAVGGRAYLEVEL
						LRError  =fread(fid,1,'double');
						PGrayLev =fread(fid,1,'double');
						NGrayLev =fread(fid,1,'double');
							%Con esto avanzo 24 bytes (3 doubles)
							%fseek(fid,24,0);

						%Compongo el segmento
						S(i1,:)=[Label,Ai,Aj,Bi,Bj,LRError,PGrayLev,NGrayLev];

					end %for i1
				end %if SegCount ~= 0

			fclose(fid);

			sva('image');
			%image(I);
		end
	end

elseif strcmp(action,'pgload'),
	 if ~isempty(FILENAME) 
		[fid message] = fopen([PATHNAME FILENAME],'r');
			%========================
			%Esto pasa en el ordenador de mi casa
			%[fid message] = fopen([PATHNAME(1:length(PATHNAME)-2) FILENAME],'r'); %Lo de la composicion del nombre es una chapucilla porque el uigetfile no funciona demasiado bien y mete dos caracteres del FILENAME en el PATHNAME
			%========================
		if fid==-1
			errordlg(message,'SVA file load error',1);
		else

			%leo todo hasta llegar a la zona de perceptual groups
			%leo la imagen
			Shape =fread(fid,2,'uint');
			fseek(fid,Shape(1)*Shape(2)*1,0);

			%Leo los bordes
			Shape =fread(fid,2,'uint');
			fseek(fid,Shape(1)*Shape(2)*1,0);

			%leo MaxLRErr y MinNoPix
			fseek(fid,8+4,0);

			%Cargo los segmentos
			%SegmentMap
			%Numero de segmentos del SegmentMap
			SegCount =fread(fid,1,'uint');

			%Recorro el SegmentMap
			if SegCount ~= 0
				for i1 = 1:SegCount
					%Leo Label + Slabel + Vector
					fseek(fid,1*4 + 1*4 + 12*8 + 2*4,0);

					%Proximity
					ProxCount =fread(fid,1,'uint');
					if ProxCount ~= 0
						%Con esto avanzo ProxCount*12 bytes(1 int + 1 double)
						fseek(fid,12*ProxCount,0);
					end
					%Parallelism
					ParCount =fread(fid,1,'uint');
					if ParCount ~= 0
						%Con esto avanzo ParCount*12 bytes(1 int + 1 double)
						fseek(fid,12*ParCount,0);
					end
					%Colinearity
					ColCount =fread(fid,1,'uint');
					if ColCount ~= 0
						%Con esto avanzo ColCount*12 bytes(1 int + 1 double)
						fseek(fid,12*ColCount,0);
					end


					%POINTCHAIN
					Count =fread(fid,1,'uint');
					if Count ~= 0
						%Con esto avanzo Count*32 bytes(2 double)
						fseek(fid,16*Count,0);
					end

					%LINE
						%Con esto avanzo 104 bytes (4 doubles + 8 doubles + 2 int)
						fseek(fid,104,0);


					%LINEARREGRESSIONERROR,
					%POSSIDEAVGGRAYLEVEL,
					%NEGSIDEAVGGRAYLEVEL
					%Con esto avanzo 24 bytes (3 doubles)
					fseek(fid,3*8,0);

				end %for i1
			end %if SegCount ~= 0

			%PERCEPTUAL GROUP SECTION
			MaxDistBetwProxSegments				= fread(fid,1,'double');
			MaxDistBetwParallelSegments			= fread(fid,1,'double');
			MaxAngleDiffBetwParallelSegments	= fread(fid,1,'double');
			MaxDistBetwColSegments				= fread(fid,1,'double');

			%PerceptualGroupRetina (PerceptualGroupMap)
			%Numero de PG del PGMap
			PGCount =fread(fid,1,'uint');

			%Leo el pgnumber que quiero extraer del fichero
			pgnumber = str2num(get(Hpgnumber,'string'))
			if isempty(pgnumber),   % handle the non-numeric case
				set(Hpgnumber,'string',num2str(' 1'));
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
					LVCount =fread(fid,1,'uint');

					%Recorro el LabelVector
 					if LVCount ~= 0
                   LV = fread(fid,LVCount,'uint');
               end

               %item del PGMap
               %PerceptualGroup (RelationVector)
					%Numero de Relations del RelationVector
					PGLabel	= fread(fid,1,'uint');
					RVCount 	= fread(fid,1,'uint');

					%Recorro el RelationVector
					if RVCount ~= 0
						RV=zeros(RVCount,4);
						for i2 = 1:RVCount
							%PERCEPTUAL GROUP SECTION
							SALabel			= fread(fid,1,'uint');
							SBLabel			= fread(fid,1,'uint');
							Property			= fread(fid,1,'uint');
							Significance	= fread(fid,1,'double');
							RV(i2,:)=[SALabel SBLabel Property Significance];
						end %for  i2 = 1:RVCount
					end %if RVCount ~= 0
               
               %Obtengo la información de características del polígono
    				%IU        	= fread(fid,1,'double');
    				%ID	         = fread(fid,1,'double');
    				%JL	         = fread(fid,1,'double');
    				%JR	         = fread(fid,1,'double');
      			Area	      = fread(fid,1,'double');
    				Perimeter	= fread(fid,1,'double');
    				Centroid_bi	= fread(fid,1,'double');
    				Centroid_bj	= fread(fid,1,'double');
    				Centroid_gi	= fread(fid,1,'double');
    				Centroid_gj	= fread(fid,1,'double');
    				m00        	= fread(fid,1,'double');
    				m01       	= fread(fid,1,'double');    
    				m10        	= fread(fid,1,'double');
    				m02        	= fread(fid,1,'double');
    				m11       	= fread(fid,1,'double');
    				m20        	= fread(fid,1,'double');
    				m03        	= fread(fid,1,'double');
    				m12       	= fread(fid,1,'double');
    				m21        	= fread(fid,1,'double');
    				m30        	= fread(fid,1,'double');
                
                
               if PGLabel == pgnumber
						PG		= LV;
						PGR 	= RV;
					end					
				end %while
				sva('pgshow');
			end %if PGCount ~= 0
			fclose(fid);
		end
	end


elseif strcmp(action,'done'),


    clear global FILENAME;
    clear global PATHNAME;
    clear global I;
    clear global E;
    clear global S;
    clear global PG;
    clear global PGR;

	clear Himage;
	clear Hmsg;

	clear MaxLRErr;
	clear MinNoPix;

	clear MaxDistBetwProxSegments;
	clear MaxDistBetwParallelSegments;
	clear MaxAngleDiffBetwParallelSegments;
	clear MaxDistBetwColSegments;

    close(gcf);

end

