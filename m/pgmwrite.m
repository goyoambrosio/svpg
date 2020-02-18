function [state]=pgmwrite(X,filename)
% PGMWRITE Write a PGM  (Portable Gray Map) file from disk. Only binary 
%	 encoded PGM images ((P5)are supported. 
%        PGMWRITE(X,'filename') writes a PGM file containing the
%        indexed image X to a disk file called 'filename'. If no file 
%        extension is given with the filename, the extension '.pgm' 
%        is assumed.
% 
%       Marcelo Neira Eid  12/13/96
%	mne@puc.cl
%       Last revision: Mon Dec  9 15:32:46 PST 1996

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
fprintf(fid,'# CREATOR: g_pgmwrite.m Version 1.0\n');
v=version;
fprintf(fid,'#          m-file for Matlab %s\n',v);
fprintf(fid,'#          By Gregorio Ambrosio Cestero <goyo@computer.org>\n');
fprintf(fid,'%d %d\n',width ,height);
fprintf(fid,'%d\n',255);
AUX=X';
fwrite(fid,AUX);
fclose(fid);
