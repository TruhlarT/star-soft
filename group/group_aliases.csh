# $Id: group_aliases.csh,v 1.9 1999/11/04 15:38:21 fisyak Exp $
# $Log: group_aliases.csh,v $
# Revision 1.9  1999/11/04 15:38:21  fisyak
# Add ..dev
#
# Revision 1.8  1999/04/24 12:59:06  fisyak
# Add SILENT option to Makefile
#
# Revision 1.7  1998/12/01 01:55:57  fisyak
# Merge with NT
#
# Revision 1.6  1998/07/27 20:24:16  fisyak
# remove frozen
#
# Aliases to switch between different STAR Library levels
alias starold    'source ${GROUP_DIR}/.starold'
alias starpro    'source ${GROUP_DIR}/.starpro'
alias starnew    'source ${GROUP_DIR}/.starnew'
alias stardev    'source ${GROUP_DIR}/.stardev'
alias star.dev   'source ${GROUP_DIR}/star.dev'
alias star..dev   'source ${GROUP_DIR}/star..dev'
alias starver    'source ${GROUP_DIR}/.starver'
if ($?SILENT == 1) then
  alias makes      "gmake --silent -f $STAR/mgr/MakePam.mk"
  alias makel      "gmake --silent -f $STAR/mgr/Makeloop.mk"
else
  alias makes      "gmake -f $STAR/mgr/MakePam.mk"
  alias makel      "gmake -f $STAR/mgr/Makeloop.mk"
endif
# last line
