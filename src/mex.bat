@rem = '--*-Perl-*--';
@rem = '
@echo off  
rem MEX.BAT
rem
rem    Compile and link script used for building MEX-files with
rem    
rem
rem    $Revision: 1.1 $  $Date: 2000/01/21 13:04:54 $
rem
rem
rem -------------------------------------------------------------------
rem   MATLAB root directory
rem -------------------------------------------------------------------
rem   Change this if you move MATLAB without reinstalling.
set MATLAB=D:\apps\MATLAB

rem ------------- Do not modify anything below this line --------------
rem
rem ###################################################################
rem # Set up script location
rem ###################################################################
rem # Allow the full pathname (or current dir.) without an extension,
rem # allow the full pathname (or current dir.) with the .bat extension,
rem # use the installed location of mex.bat,
rem # or allow users to add mex.bat to the path and call mex.
set SCRIPTLOC=%0.bat
if not exist %SCRIPTLOC% set SCRIPTLOC=%0
if not exist %SCRIPTLOC% set SCRIPTLOC="%MATLAB%\bin\nt\mex.bat"
if exist %SCRIPTLOC%\* set SCRIPTLOC="%MATLAB%\bin\nt\mex.bat"
if not exist %SCRIPTLOC% set SCRIPTLOC=-S %0.bat

rem ###################################################################
rem # Set up perl location
rem ###################################################################
rem # Either use the installed location of perl,
rem # or hope it is on the DOS path.
set PERLLOC="%MATLAB%\bin\nt\perl.exe"
if not exist %PERLLOC% set PERLLOC=perl
rem ###################################################################
rem # Set up script arguments (to avoid %9 DOS batch file limit)
rem ###################################################################
rem # Put all arguments into environment variable ARGS.  This
rem # allows us to bypass the 9 parameter limit, but disallows
rem # -DVAR=VALUE and LINKER=mylinker constructions.  These cases
rem # will need to be handled in the mexopts file.
set MEXARGS= 
:getarg
set MEXARGS=%MEXARGS% %1
shift
if not "%1"=="" goto getarg
rem ###################################################################
rem # Call Perl with the script name as an argument
rem ###################################################################
set errlvl=
%PERLLOC% %SCRIPTLOC% %MEXARGS%
if errorlevel 1 set errlvl=1

rem ###################################################################
rem # Cleanup environment and exit
rem ###################################################################
set SCRIPTLOC=
set PERLLOC=
set MEXARGS=
goto endofperl
rem -------------------------------------------------------------------

@rem ';
#######################################################################
# Begin perl code
#######################################################################
#
# MEX builds MEX-files.
#
# $Revision: 1.1 $  $Date: 2000/01/21 13:04:54 $
#
#   Functional overview:
#   1. Define subroutines
#   2. Initialize variables
#   3. Parse input arguments & determine MEX-file name
#   4. Source options file
#   5. Determine final values
#   6. Compile source files
#   7. Perform prelink tasks
#   8. Link files
#
#######################################################################
# Define subroutines
#######################################################################

sub describe {
# Describe:  Issues messages.  This way lengthy messages do not clutter
#            up the main body of code.
    local($_) = $_[0];
 DESCRIPTION: {
     /^help$/ && print(<<"end_help") && last DESCRIPTION;
 MEX: Create a MEX-file from source code.

  MEX is a script which calls a compiler with the correct compiler and
  linker switches to create a MEX-file from source code.
  The script's execution is affected by both command-line arguments and
  a batch file, $OPTFILE_NAME, which contains all compiler-specific
  information necessary for the script's execution.  This batch file is
  searched for first in the current directory, and then the same directory
  as \"mex.bat\".  The -f switch allows it to be directly specified.

  Switches:
  -argcheck        Perform argument checking on MATLAB API fundtions
  -c               Compile only; do not link
  -D<name>         Define preprocessor symbol <name>
  -f <file>        Use <file> as the options file
  -g               Debug, i.e. use COMPDEBUGFLAGS and LINKDEBUGFLAGS
  -h[elp]          Help; print this message
  -I<pathname>     Include <pathname> in the compiler include path
  -setup           Setup location of installed compiler.  This
                   switch should be the only argument passed
  -output <name>   Name resulting MEX-file <name>.dll
  -O               Optimize, i.e. use COMPOPTIMFLAGS and LINKOPTIMFLAGS
  -U<name>         Undefine symbol <name>
  -V4              Compile MATLAB 4 compatible MEX-file
  -v               Verbose; print all compiler settings
  -inline          Inline mex functions 

end_help
     /^usage$/ && print(<<"end_usage") && last DESCRIPTION;
  Usage:  mex [ -argcheck -c -Dname -f file -g -h[elp] -Ipathname
		-setup -output resultname -O -Uname -V4 -v ]
		sourcefile... [ objectfile ]...  [ library ]...

  Type 'mex -h' for more information, or consult the MATLAB API Guide manual.

end_usage
     /^general_info$/ && print(<<"end_general_info") && last DESCRIPTION;
 This is mex, (c) 1996 - 1997 The MathWorks, Inc.
 

end_general_info
     /^wrong_options_file$/ && print(<<"end_wrong_options_file") && last DESCRIPTION;
    Warning: An invalid options file name was specified.

        Defaulting to $OPTFILE_NAME options file.
        Use mex -v to see what settings are used.

end_wrong_options_file
     /^no_options_file$/ && print(<<"end_no_options_file") && last DESCRIPTION;
    Sorry! No options file was found for mex.  The mex script must
           be able to find an options file to define compiler flags
           and other settings.  The default options file is
           $script_directory\\$OPTFILE_NAME.

           To fix this problem, run the following:

               mex -setup

           This will configure the location of your compiler.

           Please contact:

               MathWorks Technical Support

           for further assistance.

 
end_no_options_file
     /^invalid_options_file$/ && print(<<"end_invalid_options_file") && last DESCRIPTION;
    Sorry! An options file for MEX.BAT was found and sourced, but the
           value for 'COMPILER' was not set.  This could mean that the
           value is not specified within the options file, or it could
           mean that there is a syntax error within the file.

           Please contact:

               MathWorks Technical Support

           for further assistance.

end_invalid_options_file
     /^final_options$/ && print(<<"end_final_options") && last DESCRIPTION;
$sourced_msg
----------------------------------------------------------------
->    Options file           = $OPTFILE_NAME
      MATLAB                 = $MATLAB
->    COMPILER               = $COMPILER
->    Compiler flags:
         COMPFLAGS           = $COMPFLAGS
         OPTIMFLAGS          = $OPTIMFLAGS
         DEBUGFLAGS          = $DEBUGFLAGS
         arguments           = $ARG_FLAGS
->    Pre-linking commands   = $PRELINK_CMDS
->    LINKER                 = $LINKER
->    Link directives:
         LINKFLAGS           = $LINKFLAGS
         Name directive      = $NAME_OUTPUT
         File link directive = $LINK_FILE
         Lib. link directive = $LINK_LIB
->    Resource Compiler      = $RC_COMPILER
->    Resource Linker        = $RC_LINKER
----------------------------------------------------------------

end_final_options
     /^file_not_found$/ && print(<<"end_file_not_found") && last DESCRIPTION;
  $cmd_name:  $filename not a normal file or does not exist.

end_file_not_found
     /^meaningless_output_flag$/ && print(<<"end_meaningless_output_flag")  && last DESCRIPTION;
  Warning: -output ignored (no MEX-file is being created).

end_meaningless_output_flag
     do {
         print "Internal error: Description for $_[0] not implemented\n";
         last DESCRIPTION;
     };
 }
}

sub describe_mb {
# Describe:  Issues messages.  This way lengthy messages do not clutter
#            up the main body of code.
    local($_) = $_[0];
 DESCRIPTION: {
     /^help$/ && print(<<"end_help_mb") && last DESCRIPTION;
 MBUILD: Create an application using the MATLAB Math library.

  MBUILD is a script which calls a compiler with the correct compiler and
  linker switches to create an application.
  The script's execution is affected by both command-line arguments and
  a batch file, $OPTFILE_NAME, which contains all compiler-specific
  information necessary for the script's execution.  This batch file is
  searched for first in the current directory, and then the same directory
  as \"mbuild.bat\".  The -f switch allows it to be directly specified.

  Switches:
  -c               Compile only; do not link
  -D<name>         Define preprocessor symbol <name>
  -f <file>        Use <file> as the options file
  -g               Debug, i.e. use COMPDEBUGFLAGS and LINKDEBUGFLAGS
  -h[elp]          Help; print this message
  -I<pathname>     Include <pathname> in the compiler include path
  -setup           Setup location of installed compiler.  This
                   switch should be the only argument passed
  -output <name>   Name resulting application <name>.exe
  -O               Optimize, i.e. use COMPOPTIMFLAGS and LINKOPTIMFLAGS
  -U<name>         Undefine symbol <name>
  -v               Verbose; print all compiler settings

end_help_mb
     /^usage$/ && print(<<"end_usage_mb") && last DESCRIPTION;
  Usage:  mbuild [-c -Dname -f file -g -h[elp] -Ipathname
		-setup -output resultname -O -Uname -v ]
		sourcefile... [ objectfile ]...  [ library ]...

  Type 'mbuild -h' for more information, or consult the MATLAB MATH Library Guide manual.

end_usage_mb
     /^general_info$/ && print(<<"end_general_info_mb") && last DESCRIPTION;
 This is mbuild (c) 1996 - 1997 The MathWorks, Inc.
 

end_general_info_mb
     /^wrong_options_file$/ && print(<<"end_wrong_options_file_mb") && last DESCRIPTION;
    Warning: An invalid options file name was specified.

        Defaulting to $OPTFILE_NAME options file.
        Use mbuild -v to see what settings are being used.

end_wrong_options_file_mb
     /^no_options_file$/ && print(<<"end_no_options_file_mb") && last DESCRIPTION;
    Sorry! No options file was found for mbuild.  The mbuild script must
           be able to find an options file to define compiler flags
           and other settings.  The default options file is
           $script_directory\\$OPTFILE_NAME.

           To fix this problem, run the following:

               mbuild -setup

           This will configure the location of your compiler.

           Please contact:

               MathWorks Technical Support

           for further assistance.

 
end_no_options_file_mb
     /^invalid_options_file$/ && print(<<"end_invalid_options_file_mb") && last DESCRIPTION;
    Sorry! An options file for MBUILD.BAT was found but the
           value for 'COMPILER' was not set.  This could mean that the
           value is not specified within the options file, or it could
           mean that there is a syntax error within the file.

           Please contact:

               MathWorks Technical Support

           for further assistance.

end_invalid_options_file_mb
     /^final_options$/ && print(<<"end_final_options_mb") && last DESCRIPTION;
$sourced_msg
----------------------------------------------------------------
->    Options file           = $OPTFILE_NAME
->    COMPILER               = $COMPILER
->    Compiler flags:
         COMPFLAGS           = $COMPFLAGS
         OPTIMFLAGS          = $OPTIMFLAGS
         DEBUGFLAGS          = $DEBUGFLAGS
         arguments           = $ARG_FLAGS
->    Pre-linking commands   = $PRELINK_CMDS
->    LINKER                 = $LINKER
->    Link directives:
         LINKFLAGS           = $LINKFLAGS
         Name directive      = $NAME_OUTPUT
         File link directive = $LINK_FILE
         Lib. link directive = $LINK_LIB
----------------------------------------------------------------

end_final_options_mb
     /^file_not_found$/ && print(<<"end_file_not_found_mb") && last DESCRIPTION;
  $cmd_name:  $filename not a normal file or does not exist.

end_file_not_found_mb
     /^meaningless_output_flag$/ && print(<<"end_meaningless_output_flag_mb")  && last DESCRIPTION;
  Warning: -output ignored (no MBUILD application is being created).

end_meaningless_output_flag_mb
     do {
         print "Internal error: Description for $_[0] not implemented\n";
         last DESCRIPTION;
     };
 }
}



sub query_info {
# queries and verifies that the 'var_value' is between the
# 'lower_limit' and the 'upper_limit'.  if not, then query for the
# 'request', citing the 'problem' as the reason.
# (this is used by 'setup')
    $lower_limit=$_[0];
    $upper_limit=$_[1];
    $problem=$_[2];
    $request=$_[3];

    $var_value=<STDIN>;
# verify that the value is with in the boundaries
    while ($var_value<$lower_limit|$var_value>$upper_limit) {
	print "$problem\n";
	print "$request";
	$var_value=<STDIN>;
    }

    $var_value;
}
sub setup {
# (1) query for the compiler
# (2) get the location of the compiler
# (3) copy over the compiler options file to "mexopts.bat"
#     editing the variable of the location of the compiler

# intro
    print "Welcome to the utility for setting up compilers\n";
	if ($mbuild eq "no") {
		print "for building external interface files.\n\n";
	} else {
		print "for building math library applications files.\n\n";
	}
	$file_end = "opts";
	if ($mbuild eq "yes") {
		print "\nWhich math library do you want to build with C or C++ ?\n";
		print "C ? ([y]/n) : ";
		$status=<STDIN>;
		chop $status;
		if ($status eq "n"){
			$file_end = "compp";
		} else {
			$file_end = "comp";
  		}
	}

# select a compiler
    print "\nC compilers\n";
    print "[1] Microsoft Visual C++\n";
    print "[2] Borland C/C++\n";
    print "[3] Watcom C/C++\n\n";
if ($mbuild eq "no") {
    print "Fortran compilers\n";
    print "[4] Microsoft PowerStation\n";
	print "[5] DIGITAL Visual Fortran\n\n";
}
    print "[0] None\n\n";
    print "compiler: ";

if ($mbuild eq "no") {    
    $compiler=&query_info(0,5,"Please select from 0-5","compiler: ");
	}
else {
	$compiler=&query_info(0,3,"Please select from 0-3","compiler: ");
	}


# check that a compiler was set
    if ($compiler==0) {
       &expire("No compiler was set");
    }
    
# set the language choosen
    if ($compiler =~ /4|5/) {
       $language="Fortran";
    } else {
       $language="C";
    }

# setup the "compiler environment variable" and the source options file
    if (($compiler==1) | ($compiler==4)) {
       # microsoft
       if ($compiler==1) {
          # C compiler
	  # set the version of microsoft we're to use
	  print "\nWhich version\n";
	  print "[1] Microsoft Visual C++ 4.x\n";
	  print "[2] Microsoft Visual C++ 5.x\n";
	  print "version: ";
	  
	  $compiler_version=&query_info(1,2,"Please select from 1 or 2","version: ");
	
	  if ($compiler_version==1) {
	     # version 4.x
	     $compiler_environment_variable="MSDevDir";
	     $srcOptsFile=$script_directory."\\msvc".$file_end.".bat";
	     $version_number="4.x";
	  } elsif ($compiler_version==2) {
	     # version 5.x
	     $compiler_environment_variable="MSVC_ROOT";
	     $srcOptsFile="$script_directory\\msvc50$file_end.bat";
	     $version_number="5.x";
	  }
	  $compiler_name="Micrsoft Visual C++";
       } else {
	  # Fortran compiler
	  $compiler_environment_variable="MSDevDir";
	  $srcOptsFile="$script_directory\\msfopts.bat";
	  $compiler_name="Micrsoft Fortran PowerStation";
       }
       $default_location="c:\\msdev";
    } elsif ($compiler==2) {
       # borland
       $compiler_environment_variable="BORLAND";
       $srcOptsFile=$script_directory."\\bcc".$file_end.".bat";
       $default_location="c:\\borland";
       $compiler_name="Borland C/C++";
    } elsif ($compiler==3) {
       # watcom
       # set the version of watcom we're to use
       print "\nWhich version\n";
       print "[1] Watcom C/C++ 10.x\n";
       print "[2] Watcom C/C++ 11.x\n";
       print "version: ";
       
       $compiler_version=&query_info(1,2,"Please select from 1 or 2","version: ");

       $compiler_environment_variable="WATCOM";
       if ($compiler_version==1) {
	  $srcOptsFile="$script_directory\\watc$file_end.bat";
	  $version_number="10.x";
       } else {
	  $srcOptsFile="$script_directory\\wat11c$file_end.bat";
	  $version_number="11.x";
       }
       $default_location="c:\\watcom";
       $compiler_name="Watcom C/C++";
	} elsif ($compiler==5) {
		# DEC Fortran
		#Only 1 version, so set up stuff.
		$compiler_environment_variable="DF_ROOT";
		$srcOptsFile="$script_directory\\df50opts.bat";
		$default_location="c:\\devStudio";
		$compiler_name="DIGITAL Visual Fortran";
    }

	
    print "Please enter the location of your $language compiler: [$default_location] ";
    $location_of_compiler=<STDIN>;
    chop $location_of_compiler;
    if ($location_of_compiler eq "") {
	$location_of_compiler=$default_location;
    }
    

    # before making the edits, verify from the user all the information is correct
    print "\nPlease verify\n";
    print "Compiler: $compiler_name $version_number\n";
    print "Location: $location_of_compiler\n";
	if ($file_end eq "comp") {
		print "Library: C math library\n";
	} elsif ($file_end eq "compp") {
		print "Library: C++ math library\n";
	}
    print "Ok?([y]/n): ";
    $status=<STDIN>;
    chop $status;
    &expire("No compiler was set") unless ($status ne "n");

# edit the variable in the destOptsFile
    print "\nDefault options file is being updated...\n";

	if ($mbuild eq "no")	{
		$destOptsFile="$script_directory\\mexopts.bat";
	} else {
    	$destOptsFile="$script_directory\\compopts.bat";
	}
    open (OPTIONSFILE, "<$srcOptsFile") || &expire("Can't open $srcOptsFile");
    @OptionsFile = <OPTIONSFILE>;
    close(OPTIONSFILE);
    
    open (OPTIONSFILE, ">$destOptsFile") || &expire("Can't open $destOptsFile");
    $done=0;
    foreach (@OptionsFile) {
	if (!$done && /^\s*set $compiler_environment_variable=/) {
	   s/%\w+%/$location_of_compiler/;
	   $done=1;
	}	  
	
	print OPTIONSFILE "$_";
    }
    
    close(OPTIONSFILE);

# done
    exit(0);
}

sub find_options_file {
  if (-e ".\\$OPTFILE_NAME") {
     chop($source_dir = `cd`);
  } elsif (-e "$script_directory\\$OPTFILE_NAME") {
     $source_dir = "$script_directory";
  } else {
	if ($mbuild eq "no") {
		&describe("no_options_file");
	} else {
		&describe_mb("no_options_file");
    }
     &expire("Can not continue without options file.");
  }   
  $OPTFILE_NAME = "$source_dir\\$OPTFILE_NAME";
  $sourced_msg = "-> Default options filename found in $source_dir";
}

sub expire {
# Expire: Issue message and exit.  This is like "die" except that
#         it cleans up intermediate files before exiting.
#         &expire("normally") exits normally (doesn't die).

# Clean up compiled files, unless we're only compiling
  foreach $filename (@FILES_TO_REMOVE) {
     unlink "$filename" if (-e "$filename");
  }
# clean up _lib? files in any case.
  opendir(DIR,".") || die " Can't open dir\n";
  while ($file = readdir(DIR)) {
      if ($file =~ /^_lib*.*/) {
          unlink($file);
      } 
  }
  closedir(DIR);
  die "\n  $cmd_name: $_[0]\n\n" unless ($_[0] eq "normally");
  exit(0);
}

#######################################################################
# Initialize variables
#######################################################################

$| = 1;                         # Force immediate output flushing
open(STDERR,">&STDOUT");		# redirect stderr to stdout for matlab
select((select(STDERR), $|=1 )[0]);  # force immediate flushing for STDERR

# Correct how the $cmd_name variable looks so that it is presentable
# to DOS users (i.e., trade / with \).
($cmd_name) = $0;
($cmd_name) =~ s/\//\\/g;
($cmd_name) =~ tr/a-z/A-Z/;

($script_directory) = ($cmd_name =~ /(.*)\\.*/);
$script_directory = '.' if (!($script_directory));

$OPTFILE_NAME = "mexopts.bat";
$sourced_msg = 'none';
$mex_include_dir = "extern\\include";
$mbuild = "no";

# Trap case where an invalid options file is used, by checking the
# value of the compiler
$COMPILER = "none";

# $$ should be the pid, but this is not defined for Windows perl
# We'll use a random integer instead.  This is only an issue
# if you build more than one mex file in the same directory at
# the same time, and this way there's a pretty low chance of
# failure.
srand;
$$ = int(rand(10000));
# Create a unique name for the created import library
$ENV{'LIB_NAME'} = "_lib$$";

#######################################################################
# Parse input arguments & determine MEX-file name from 1st source file
#######################################################################

for (;$_=shift(@ARGV);) {
    # Perl-style case construct
	#print "DEBUG input argument is $_\n";
  ARGTYPE: {
      /^-argcheck$/ && do {
          $ARG_FLAGS = "$ARG_FLAGS -DARGCHECK";
          $argcheck = "yes";
          last ARGTYPE;
      };
      /^-c$/ && do {
          $compile_only = "yes";
          last ARGTYPE;
      };
      /^-[DIU]\S*$/ && do {
          if ($_ eq "-DV4_COMPAT") {
              &expire("Plese use -V4 rather than directly passing in -DV4_COMPAT.");
          } elsif ($_ eq "-DARRAY_ACCESS_INLINING") {
              &expire("Please use -inline rather than directly passing in -DARRAY_ACCESS_INLINING.");
          } else {
              $ARG_FLAGS = "$ARG_FLAGS $_";
              last ARGTYPE;
          }
      };
      /^-f$/ && do {
          $filename = shift(@ARGV);
          if (!(-e $filename)) {
			if ($mbuild eq "no") {
				&describe("file_not_found");
				&describe("wrong_options_file");
			} else {
				&describe_mb("file_not_found");
				&describe_mb("wrong_options_file");
			}
         #     &describe("file_not_found");
         #     &describe("wrong_options_file");
          } else {
              $OPTFILE_NAME =  "$filename";
              $sourced_msg = '-> Options file specified on command line';
          }
          last ARGTYPE;
      };
      /^-g$/ && do {
          $debug = "yes";
          last ARGTYPE;
      };
      /^[-\/](h(elp)?)|\?$/ && do {
			if ($mbuild eq "no") {
				&describe("help");
			} else {
				&describe_mb("help");
			}
         # &describe("help");
          &expire("normally");
          last ARGTYPE;
      };
      /^-inline$/ && do {
          $inline = "yes";
          last ARGTYPE;
      };
      /^-setup$/ && do {
          $setup = "yes";
          last ARGTYPE;
      };
      /^-output$/ && do {
          $output_flag = "yes";
          $ENV{'MEX_NAME'}=shift(@ARGV);
          last ARGTYPE;
      };
      /^-O$/ && do {
          $optimize = "yes";
          last ARGTYPE;
      };
      /^-v$/ && do {	
			if ($mbuild eq "no") {
				&describe("general_info");
			} else {
				&describe_mb("general_info");
			}
        #  &describe("general_info");
          $verbose = "yes";
          last ARGTYPE;
      };
      /^-V4$/ && do {
          $v4 = "yes";
          $ARG_FLAGS = "$ARG_FLAGS -DV4_COMPAT";
          last ARGTYPE;
      };
	  /^-matlab$/ && do {
          $matlab = shift(@ARGV);
          $ENV{'MATLAB'} = $matlab;
          last ARGTYPE;
      };
	  /^-mb$/ && do {
          $mbuild = "yes";
		  $OPTFILE_NAME = "compopts.bat";
		  $cmd_name = "MBUILD.BAT";
          last ARGTYPE;
      };

      /^\S*=\S*$/ && do {
          push(@ASSIGNMENTS, $_);
          last ARGTYPE;
      };
      /^-.*$/ && do {
			if ($mbuild eq "no") {
				&describe("usage");
			} else {
				&describe_mb("usage");
			}
          &expire("Unrecognized switch: $_.");
          last ARGTYPE;
      };
	    do {
          if (!(-e "$_")) {
             if (!(/.dll$/)) {
                &expire("'$_' not found.");
             }
          }
		  push(@FILES, $_);
          last ARGTYPE;
     };
  };
}

# it doesn't mean anything to redirect the output if we aren't creating a MEX-file
if ($compile_only && $output_flag){
	if ($mbuild eq "no") {
		&describe("meaningless_output_flag");
	} else {
		&describe_mb("meaningless_output_flag");
	}
}
#&describe("meaningless_output_flag") if ($compile_only && $output_flag);

# check to see if we're only setting up the compiler locations
&setup() if $setup;

# get mex-file name and source file type from 1st file argument
($derived_name, $EXTENSION) = ($FILES[0] =~ /(\w*)\.(\w*)$/);
$ENV{'MEX_NAME'} = $derived_name if (!($ENV{'MEX_NAME'}));
$fortran = "yes" if ($EXTENSION eq 'f' || $EXTENSION eq 'F');

#Set up the DLL_NAME environment variable, so it can be filled in
# later when it is known.
 
$ENV{'DLL_NAME'}  = "none";

$RC_LINKER = " ";
$RC_COMPILER = " ";

#######################################################################
# Source options file
#######################################################################

# If we don't already know what to use as the options file, search
# default locations.
if ($sourced_msg eq 'none') {
   &find_options_file;
}

# The DOS batch language is too limited for our purposes.
# Instead, we will parse the batch files on our own.
open (OPTIONSFILE, $OPTFILE_NAME) || expire("Can't open $OPTFILE_NAME");
while ($_ = <OPTIONSFILE>) {
    chop;
    next if (!(/^\s*set /));      # Ignore everything but set commands
    s/^\s*set //;                 # Remove "set " command itself
    s/\\$//g;                     # Remove trailing \'s
    s/\\/\\\\/g;                  # Escape all other \'s with another \
    s/%(\w+)%/'.\$ENV{'\1'}.'/g;  # Replace %VAR% with $ENV{'VAR'}
    s/%%/%/g;                     # Replace %%s with %s
    $perlvar = '$'.$_."';";
    $perlvar =~ s/=/='/;
    $dosvar = '$ENV{'."'".$_."';";
    $dosvar =~ s/=/'}='/;
    eval($perlvar);
    eval($dosvar);
}

if ($verbose) {
	if ($mbuild eq "no") {
		&describe("final_options");
	} else {
		&describe_mb("final_options");
    }
}
if ($COMPILER eq "none") {
  if ($mbuild eq "no") {
		&describe("invalid_options_file");
	} else {
		&describe_mb("invalid_options_file");
    }
}

#&describe("final_options") if $verbose;

#&describe("invalid_options_file") if ($COMPILER eq "none");

#######################################################################
# Determine final values
#######################################################################

# Decide how to optimize or debug
if (! $debug) {                                  # Normal case
   $FLAGS = "$OPTIMFLAGS";
   $LINKFLAGS = "$LINKFLAGS $LINKOPTIMFLAGS";
} elsif (! $optimize) {                          # Debug; don't optimize
   $FLAGS = "$DEBUGFLAGS";
   $LINKFLAGS = "$LINKDEBUGFLAGS $LINKFLAGS ";
} else {                                         # Debug and optimize
   $FLAGS = "$DEBUGFLAGS $OPTIMFLAGS";
   $LINKFLAGS = "$LINKDEBUGFLAGS $LINKFLAGS $LINKOPTIMFLAGS ";
}
# Include the simulink include directory if it exists
#
if (-e "$MATLAB\\simulink\\include") {
    $simulink_inc_dir = "-I$MATLAB\\simulink\\include";
} else {
    $simulink_inc_dir = "";
}

# Add the extern\include directory to the dir path
#
$FLAGS = "-I$MATLAB\\$mex_include_dir $simulink_inc_dir $FLAGS" if (!($fortran));

# Add inlining if switch was set
#
unless (! $inline) {
  $FLAGS = "$FLAGS -DARRAY_ACCESS_INLINING"  
}

# If there are no files, then exit.
#
if (@FILES == 0) {
	if ($mbuild eq "no"){
		&describe("usage");
	} else {
		&describe_mb("usage");
    }
    &expire("No file names given.");
}

# If we are checking arguments, add $MATLAB/extern/src/mwdebug.c
# to source file list.
push(@FILES, "$MATLAB\\extern\\src\\mwdebug.c") if ($argcheck eq "yes");

#######################################################################
# Compile source files
#######################################################################

# Loop over @FILES to compile each file.  Keep files we actually
# compile separate from the ones we don't compile but need to link.
# This way, we can later clean up all .obj files we created.
push(@FILES_TO_REMOVE, ("$ENV{'MEX_NAME'}.err"));
for (;$_=shift(@FILES);) {
    ($FILENAME, $EXTENSION) = (/(\w+)\.(\w*)$/);
     if ($EXTENSION =~ /(c|f|cc|cxx|cpp|for)$/i ) {
	     if (/\s/) {
		 	$ENV{'ARGS'} = "$ARG_FLAGS $COMPFLAGS $FLAGS \"$_\"";
		 }
		 else {
			$ENV{'ARGS'} = "$ARG_FLAGS $COMPFLAGS $FLAGS $_";
		 }
          print "--> $COMPILER $ENV{'ARGS'}\n\n" if $verbose;
          $messages = `$COMPILER %ARGS%`;

          push(@FILES_TO_LINK,   "$LINK_FILE $FILENAME.obj");
          push(@FILES_TO_REMOVE, "$FILENAME.err"); 
          push(@FILES_TO_REMOVE, "$FILENAME.obj") unless $compile_only;

          # Check for error; $? doesn't work, so check for resulting file
          if (!(-e "$FILENAME.obj")) {
             print "$messages";
             &expire("Compile of '$_' failed.");
          }
          print $messages if $verbose;
      }
   elsif ($EXTENSION =~ /lib$/i) {
          push(@FILES_TO_LINK,"$LINK_LIB $_");
      }
   elsif ($EXTENSION =~ /dll$/i) {
          push(@DLL_FILES,$FILENAME);
          push(@FILES_TO_LINK,"$LINK_LIB $FILENAME.lib");
          push(@FILES_TO_REMOVE, "$FILENAME.lib"); 
      }
   else {
          push(@FILES_TO_LINK,"$LINK_FILE $_");
      }
  }
#}

&expire("normally") if ($compile_only);

#######################################################################
# Perform prelink tasks
#######################################################################
#
# Note that error checking is not possible; we don't get a return
# status, and there's no way of knowing a priori what each task is
# supposed to do.
(@PRELINK_CMDS) = split(/;/,$PRELINK_CMDS);
while ($PRELINK_CMDS = shift(@PRELINK_CMDS)) {
    # Skip if $PRELINK_CMDS is only whitespace
    next if (!($PRELINK_CMDS =~ /\S/));

    print "\n--> $PRELINK_CMDS\n\n" if $verbose;
    $messages = `$PRELINK_CMDS`;
    print $messages if $verbose;
}

push(@FILES_TO_REMOVE, ("$ENV{'MEX_NAME'}lib.exp"), ("$ENV{'MEX_NAME'}lib.lib"));
push(@FILES_TO_REMOVE, ("$ENV{'MEX_NAME'}.bak"));

#######################################################################
#
#The PRELINK_DLLS command creates an import library from a dll and links 
#to it. 
(@PRELINK_DLLS) = split(/;/,$PRELINK_DLLS);
while ($PRELINK_DLLS = shift(@PRELINK_DLLS)) {
    # Skip if $PRELINK_DLLS is only whitespace
    next if (!($PRELINK_DLLS =~ /\S/));
    
    for (;$dll=shift(@DLL_FILES);) {
	$PRELINK_DLLS =~ s/none/$dll/g; 
	print "\n--> $PRELINK_DLLS\n\n" if $verbose;
	$messages = `$PRELINK_DLLS`;
	print $messages if $verbose;
    }
}

#######################################################################
# If there is a resource compiler, compile resource now

if ($RC_COMPILER =~ /\S/) {
    $rc_line = "$rc_line -DARRAY_ACCESS_INLINING" if ($inline);
    $rc_line = "$rc_line -DV4_COMPAT" if ($v4);
    $rc_line = "$rc_line \"$ENV{'MATLAB'}\\extern\\include\\mexversion.rc\"";
    print "--> $RC_COMPILER $rc_line\n" if $verbose;
    $messages = `$RC_COMPILER $rc_line`;
    # Check for error; $? doesn't work, so check for string "error"
    if ($messages =~ /\b(error|fatal)\b/i) {
        print "$messages";
        &expire("Resource compile of 'mexversion.rc' failed.");
    }
    print $messages if $verbose;
    
    push(@FILES_TO_LINK, "mexversion.res");
    push(@FILES_TO_REMOVE,"mexversion.res");
}

#######################################################################
# Link files
#######################################################################
# 
# NAME_OUTPUT always goes in the list, but it may be blank (in which
# case it's harmless to put it in).  Leaving the variable blank is
# equivalent to assuming that the output will be named after the
# first object file in the list.
$ENV{'ARGS'} = "$NAME_OUTPUT $LINKFLAGS @FILES_TO_LINK";

print "\n--> $LINKER $ENV{'ARGS'}\n\n" if $verbose;
$messages = `$LINKER %ARGS%`;

# Check for error; $? doesn't work, so check for resulting file
if (-e "$ENV{'MEX_NAME'}.dll") {
    $extension = "dll";
} elsif (-e "$ENV{'MEX_NAME'}.exe") {
    $extension = "exe";
} else {
    print "$messages";
    &expire("Link of '$ENV{'MEX_NAME'}.dll' failed.");
}
# If we got a file, make sure there were no errors
if ($messages =~ /\b(error|fatal)\b/i) {
    print "$messages";
    &expire("Link of '$ENV{MEX_NAME}.dll' failed.");
}
print $messages if $verbose;

#
# If a resource linker has been defined, use it
#
if ($RC_LINKER =~ /\S/) {
    $rc_line = "$ENV{'MATLAB'}\\extern\\include\\mexversion.rc $ENV{'MEX_NAME'}.$extension";
    $rc_line = "$rc_line -DARRAY_ACCESS_INLINING" if ($inline);
    $rc_line = "$rc_line -DV4_COMPAT" if ($v4);
    print "--> $RC_LINKER $rc_line\n" if $verbose;
    $messages = `$RC_LINKER $rc_line`;
    # Check for error; $? doesn't work, so check for string "error"
    if ($messages =~ /\b(error|fatal)\b/i) {
        print "$messages";
        &expire("Resource link of 'mexversion.rc' failed.");
    }
    print $messages if $verbose;
   
    push(@FILES_TO_REMOVE,"mexversion.res");
}

#######################################################################
# Clean up files and exit
#######################################################################

&expire("normally");

#######################################################################
# End perl code
#######################################################################
__END__
:endofperl
if X%errlvl% == X1 perl -e "die \"\n\";"
