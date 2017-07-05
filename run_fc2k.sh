#!/bin/tcsh

####### building FC2K files #######

# runaway indicator (EU-IM)

if (  ( $?ITM_ENVIRONMENT_LOADED) && $ITM_ENVIRONMENT_LOADED == yes) then
    echo "*** Compiler set to ITM ***"
    rmactor runaway_indicator
    fc2k -docfile doc/runaway_indicator.txt -codeversion 1.6.2 fc2k/runaway_indicator.xml 
endif


# runaway indicator (IMAS)

if (  ( $?IMAS_ENVIRONMENT_LOADED) && $IMAS_ENVIRONMENT_LOADED == yes) then
    echo "*** Compiler set to IMAS ***"
    rmactor runaway_indicator
    fc2k -docfile doc/runaway_indicator.txt -codeversion 1.6.2 fc2k_imas/runaway_indicator.xml 
endif
