# $Id: group_aliases.csh,v 1.6 1998/07/27 20:24:16 fisyak Exp $
# $Log: group_aliases.csh,v $
# Revision 1.6  1998/07/27 20:24:16  fisyak
# remove frozen
#
# Aliases to switch between different STAR Library levels
alias starold    'source ${GROUP_DIR}/.starold'
alias starpro    'source ${GROUP_DIR}/.starpro'
alias starnew    'source ${GROUP_DIR}/.starnew'
alias stardev    'source ${GROUP_DIR}/.stardev'
alias starver    'source ${GROUP_DIR}/.starver'
alias makes      "gmake -f $STAR/mgr/MakePam.mk"
alias makel      "gmake -f $STAR/mgr/Makeloop.mk"
