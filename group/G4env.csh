#! /usr/local/bin/tcsh -f
         #SNiFF+
switch ($STAR_SYS)
	    case "sun4*":
#     ====================
	setenv G4SYSTEM SUN-CC
	breaksw 
	    case "i386_*":
#     ====================
	setenv G4SYSTEM Linux-g++
	export G4SYSTEM Linux-g++
	setenv G4INSTALL /afs/rhic/usatlas/software/geant4/geant4.0.1
	setenv G4WORKDIR $HOME/geant4
	setenv CLHEP_BASE_DIR /afs/rhic/usatlas/software/geant4/Linux/CLHEP/Linux-g++/1.3
	setenv RWBASE /afs/rhic/usatlas/software/geant4/Linux/rogue
	setenv G4VIS_USE_DAWN 1
	setenv G4DAWN_MULTI_WINDOW 1
	setenv G4DAWN_HOME /afs/rhic/usatlas/software/geant4/Linux/DAWN
	setenv DAWN_HOME /afs/rhic/usatlas/software/geant4/Linux/DAWN
	setenv PATH $PATH:$G4DAWN_HOME
	breaksw
    default:
endsw 
 
