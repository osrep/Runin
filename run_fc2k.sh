#!/bin/tcsh

####### building FC2K files #######

# runaway indicator (EU-IM)

if ($ITM_ENVIRONMENT_LOADED == yes) then
    fc2k -docfile doc/runaway_indicator.txt -codeversion 1.6.2 fc2k/runaway_indicator.xml 
else
    fc2k -docfile doc/runaway_indicator.txt -codeversion 1.6.2 fc2k_imas/runaway_indicator.xml 
endif
