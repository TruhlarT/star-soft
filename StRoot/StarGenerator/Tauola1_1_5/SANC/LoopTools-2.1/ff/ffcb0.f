*	$Id: ffcb0.f,v 1.1 2016/09/23 18:39:39 jwebb Exp $
*###[ ffcb0:
	subroutine ffcb0(cb0,cp,cma,cmb,ier)
***#[*comment:***********************************************************
*									*
*	calculates the the two-point function (cf 't Hooft and Veltman)	*
*	we include an overall factor 1/(i*pi^2)	relative to FormF	*
*									*
*	Input:	cp	(complex) k2, in B&D metric			*
*		cma	(complex) mass2, re>0, im<0.			*
*		cmb	(complex) mass2, re>0, im<0.			*
*									*
*	Output:	cb0	(complex) B0, the two-point function,		*
*		ier	(integer) number of digits lost in calculation	*
*									*
*	Calls:	ffcb0p,ffxb0p						*
*									*
***#]*comment:*********************************************************** 
*  #[ declarations:
	implicit none
*
*	arguments
*
	integer ier
	DOUBLE COMPLEX cb0,cp,cma,cmb
*
*	local variables
*
	integer ier0,init,initc,ithres,i,j,nschsa
	logical lreal
	DOUBLE COMPLEX cmamb,cmap,cmbp,cm,c,cb0p,cqi(3),cqiqj(3,3)
	DOUBLE PRECISION absc,xp,xma,xmb,sprec,smax
	save init,initc
*
*	common blocks
*
	include 'ff.h'
*
*	statement function
*
	absc(c) = abs(DBLE(c)) + abs(DIMAG(c))
*
*	data
*
	data init,initc /2*0/
*
*  #] declarations: 
*  #[ the real cases:
*
	if ( DIMAG(cma) .eq. 0 .and. DIMAG(cmb) .eq. 0 .and. 
     +		DIMAG(cp).eq.0 ) then
	    lreal = .TRUE.
	elseif ( nschem.le.4 ) then
	    lreal = .TRUE.
	    if ( init.eq.0 ) then
		init = 1
		print *,'ffcb0: nschem <= 4, ignoring complex masses: ',
     +			nschem
	    endif
	elseif ( nschem.le.6 ) then
	    if ( init.eq.0 ) then
		init = 1
		print *,'ffcb0: nschem = 5,6 complex masses near ',
     +			'threshold: ',nschem
	    endif
	    cqi(1) = cma
	    cqi(2) = cmb
	    cqi(3) = cp
	    cqiqj(1,2) = cma - cmb
	    cqiqj(2,1) = -cqiqj(1,2)
	    cqiqj(1,3) = cma - cp
	    cqiqj(3,1) = -cqiqj(1,3)
	    cqiqj(2,3) = cmb - cp
	    cqiqj(3,2) = -cqiqj(2,3)
	    cqiqj(1,1) = 0
	    cqiqj(2,2) = 0
	    cqiqj(3,3) = 0
	    call ffthre(ithres,cqi,cqiqj,3,1,2,3)
	    if ( ithres.eq.0 .or. ithres.eq.1 .and. nschem.eq.5 ) then
		lreal = .TRUE.
	    else
		lreal = .FALSE.
	    endif
	else
	    lreal = .FALSE.
	endif
	if ( lreal ) then
	    xp = DBLE(cp)
	    xma = DBLE(cma)
	    xmb = DBLE(cmb)
	    sprec = precx
	    precx = precc
	    call ffxb0(cb0,xp,xma,xmb,ier)
	    precx = sprec
	    if ( ldot ) then
		do 120 j=1,3
		    do 110 i=1,3
			cfpij2(i,j) = fpij2(i,j)
  110		    continue
  120		continue
	    endif
	    return
	endif
*
*  #] the real cases: 
*  #[ get differences:
*
	cmamb = cma - cmb
	cmap = cma - cp
	cmbp = cmb - cp
*
*  #] get differences: 
*  #[ calculations:
*
*	no more schem-checking, please...
*
	nschsa = nschem
	nschem = 7
	call ffcb0p(cb0p,cp,cma,cmb,cmap,cmbp,cmamb,ier)
	nschem = nschsa
	if ( cma .eq. 0 ) then
	    if ( cmb .eq. 0 ) then
	    	cm = 1
	    else
	    	cm = cmb**2
	    endif
	elseif ( cmb .eq. 0 ) then
	    cm = cma**2
	else
	    cm = cma*cmb
	endif
	if ( mudim2 .ne. 0 ) cm = cm/DBLE(mudim2)**2
	if ( absc(cm) .gt. xclogm ) then
	    cb0 = DBLE(divergence) - cb0p - log(cm)/2
	    smax = max(abs(divergence),absc(cb0p),absc(log(cm))/2)
	else
	    call fferr(3,ier)
	    cb0 = -cb0p + DBLE(divergence)
	endif
*  #] calculations: 
*###] ffcb0: 
	end
*###[ ffcb0p:
	subroutine ffcb0p(cb0p,cp,cma,cmb,cmap,cmbp,cmamb,ier)
***#[*comment:***********************************************************
*									*
*	calculates the main part of the two-point function (cf 't	*
*	Hooft and Veltman) for all possible cases: masses equal,	*
*	unequal, equal to zero, real or complex (with a negative	*
*	imaginary part). I think it works.				*
*	Has been checked against FormF for all parameter space.		*
*	Only problems with underflow for extreme cases.  VERY OLD CODE.	*
*									*
*	Input:	cp	(complex) k2, in B&D metric			*
*		cma	(complex) mass2, re>0, im<0.			*
*		cmb	(complex) mass2, re>0, im<0.			*
*		cmap/b	(complex) cma/b	- cp				*
*		cmamb	(complex) cma - cmb				*
*									*
*	Output:	cb0p	(complex) B0, the two-point function,		*
*				  minus log(cm/mu), delta and the	*
*				  factor -ipi^2.			*
*		ier	(integer) 0=ok, 1=numerical problems, 2=error	*
*									*
*	Calls:	(z/a)log, atan.						*
*									*
***#]*comment:*********************************************************** 
*  #[ declarations:
	implicit none
*
*	arguments
*
	integer ier
	DOUBLE COMPLEX cb0p,cp,cma,cmb,cmap,cmbp,cmamb
*
*	local variables
*
	integer i,j,initeq,initn1,n1,n2,nffeta,nffet1,ier0,init,
     +		ithres,is1
	logical lwsave,lreal
	DOUBLE PRECISION xp,ax,ay,ffbnd,
     +		xprceq,bdeq01,bdeq05,bdeq11,bdeq17,bdeq25,
     +		xprcn1,bdn101,bdn105,bdn110,bdn115,
     +		xprnn2,bdn201,bdn205,bdn210,bdn215,
     +		xpneq(30),xpnn1(30),
     +		absc,sprec,xma,xmb,dmap,dmbp,dmamb,rloss,smax
	DOUBLE COMPLEX check,cm,cmp,cm1,cm2,cm1m2,
     +		cm1p,cm2p,cs,cs1,cs2,cx,cy,csom,clam,cslam,clogmm,
     +		zfflo1,c,zm,zp,zm1,zp1,zfflog,cb0r,cqi(3),
     +		cqiqj(3,3),cpiDpj(3,3),ck,clamr,cslamr,zmr,zpr,zm1r,zp1r
	save initeq,initn1,xpneq,xpnn1,init,
     +		xprceq,bdeq01,bdeq05,bdeq11,bdeq17,bdeq25,
     +		xprcn1,bdn101,bdn105,bdn110,bdn115,
     +		xprnn2,bdn201,bdn205,bdn210,bdn215
*FOR ABSOFT ONLY
*	DOUBLE COMPLEX csqrt
*	external csqrt
*
*	common blocks
*
	include 'ff.h'
*
*	data
*
	data xprceq /-1./
	data xprcn1 /-1./
	data xprnn2 /-1./
	data initeq /0/
	data initn1 /0/
	data init /0/
*
*	statement function
*
	absc(c) = abs(DBLE(c)) + abs(DIMAG(c))
*
*  #] declarations: 
*  #[ fill some dotproducts:
*
	call ffcot2(cpiDpj,cp,cma,cmb,cmap,cmbp,cmamb,ier)
	if ( ldot ) then
	    do 20 i=1,3
		do 10 j=1,3
		    cfpij2(j,i) = cpiDpj(j,i)
		    fpij2(j,i) = DBLE(cpiDpj(j,i))
   10		continue
   20	    continue
	endif
*
*  #] fill some dotproducts: 
*  #[ the real cases:
*
	if ( DIMAG(cma) .eq. 0 .and. DIMAG(cmb) .eq. 0 .and. 
     +		DIMAG(cp).eq.0 ) then
	    lreal = .TRUE.
	elseif ( nschem.le.4 ) then
	    lreal = .TRUE.
	    if( init.eq.0 ) then
		init = 1
		print *,'ffcb0p: nschem <= 4, ignoring complex masses:',
     +			nschem
	    endif
	elseif ( nschem.le.6 ) then
	    if( init.eq.0 ) then
		init = 1
		print *,'ffcb0p: nschem = 4,6 complex masses near ',
     +			'threshold: ',nschem
	    endif
	    cqi(1) = cma
	    cqi(2) = cmb
	    cqi(3) = cp
	    cqiqj(1,2) = cmamb
	    cqiqj(2,1) = -cqiqj(1,2)
	    cqiqj(1,3) = cmap
	    cqiqj(3,1) = -cqiqj(1,3)
	    cqiqj(2,3) = cmbp
	    cqiqj(3,2) = -cqiqj(2,3)
	    cqiqj(1,1) = 0
	    cqiqj(2,2) = 0
	    cqiqj(3,3) = 0
	    call ffthre(ithres,cqi,cqiqj,3,1,2,3)
	    if ( ithres.eq.0 .or. ithres.eq.1 .and. nschem.eq.5 ) then
		lreal = .TRUE.
	    else
		lreal = .FALSE.
	    endif
	else
	    lreal = .FALSE.
	endif
	if ( lreal ) then
	    xp = DBLE(cp)
	    xma = DBLE(cma)
	    xmb = DBLE(cmb)
	    dmap = DBLE(cmap)
	    dmbp = DBLE(cmbp)
	    dmamb = DBLE(cmamb)
	    sprec = precx
	    precx = precc
	    call ffxb0p(cb0p,xp,xma,xmb,dmap,dmbp,dmamb,ier)
	    precx = sprec
	    if ( ldot ) then
		do 120 j=1,3
		    do 110 i=1,3
			cfpij2(i,j) = fpij2(i,j)
  110		    continue
  120		continue
	    endif
	    return
	endif
*
*  #] the real cases: 
*  #[ which case:
*
*	sort according to the type of mass combination encountered:
*	200: one equal to zero, 300: both equal, 400: rest.
*
	if ( cma .eq. 0 ) then
		if ( cmb .eq. 0 ) then
			goto 100
		endif
		cm = cmb
		cmp = cmbp
		goto 200
	endif
	if ( cmb .eq. 0 ) then
		cm = cma
		cmp = cmap
		goto 200
	endif
	if ( cma .eq. cmb ) then
		cm = cma
		cmp = cmap
		goto 300
	endif
	if ( DBLE(cma) .lt. DBLE(cmb) ) then
		cm2 = cma
		cm1 = cmb
		cm1m2 = -cmamb
		cm1p = cmbp
		cm2p = cmap
		is1 = 2
	else
		cm1 = cma
		cm2 = cmb
		cm1m2 = cmamb
		cm1p = cmap
		cm2p = cmbp
		is1 = 1
	endif
	goto 400
*  #] which case: 
*  #[ both masses equal to zero:
  100	continue
	if ( absc(cp) .gt. xclogm ) then
	    if ( DBLE(cp).gt.0 ) then
	    	cb0p = log(cp) - c2ipi/2 - 2
	    else
	    	cb0p = log(-cp) - 2
	    endif
	else
	    cb0p = 0
	    call fferr(7,ier)
	endif
	return
*  #] both masses equal to zero: 
*  #[ one mass zero:
  200	continue
*
*	special case cp = 0, checked 25-oct-1991
*
	if ( cp .eq. 0 ) then
	    cb0p = -1
	    goto 990
	endif
*
*	Normal case:
*
	cs1 = cp/cm
	cs2 = cmp/cm
*	make sure we get the right Riemann sheet!
	if ( absc(cs1) .lt. xloss ) then
	    cs = zfflo1(cs1,ier)
	elseif ( DBLE(cs2).gt.0 ) then
	    cs = zfflog(cs2,0,czero,ier)
	else
	    cs = zfflog(-cs2,0,czero,ier)
	    cs = cs - c2ipi/2
	endif
	cs = -cs*cmp/cp
	cb0p = cs - 2
	goto 990
*  #] one mass zero: 
*  #[ both masses equal:
  300	continue
*
*	Both masses are equal.	Not only this speeds up things, some
*	cancellations have to be avoided as well.  Checked 25-oct-1991.
* -#[ taylor expansion:
*
*	first this special case
*
	if ( absc(cp) .lt. 8*xloss*absc(cm) ) then
*
*	    a Taylor expansion seems appropriate as the result will go
*	    as k^2 but seems to go as 1/k !!
*
*  #[ data and bounds:
	    if ( initeq .eq. 0 ) then
		initeq = 1
		xpneq(1) = 1/6D0
		do 1 i=2,30
		    xpneq(i) = xpneq(i-1)*DBLE(i-1)/DBLE(2*(2*i+1))
    1		continue
	    endif
	    if (xprceq .ne. precc ) then
*
*		calculate the boundaries for the number of terms to be
*		included in the taylorexpansion
*
		xprceq = precc
		sprec = precx
		precx = precc
		bdeq01 = ffbnd(1,1,xpneq)
		bdeq05 = ffbnd(1,5,xpneq)
		bdeq11 = ffbnd(1,11,xpneq)
		bdeq17 = ffbnd(1,17,xpneq)
		bdeq25 = ffbnd(1,25,xpneq)
		precx = sprec
	    endif
*  #] data and bounds: 
	    cx = cp/cm
	    ax = absc(cx)
	    if ( ax .gt. bdeq17 ) then
		csom = cx*(DBLE(xpneq(18)) + cx*(DBLE(xpneq(19)) +
     +		cx*(DBLE(xpneq(20)) + cx*(DBLE(xpneq(21)) +
     +		cx*(DBLE(xpneq(22)) + cx*(DBLE(xpneq(23)) +
     +		cx*(DBLE(xpneq(24)) + cx*(DBLE(xpneq(25)) ))))))))
	    else
		csom = 0
	    endif
	    if ( ax .gt. bdeq11 ) then
		csom = cx*(DBLE(xpneq(12)) + cx*(DBLE(xpneq(13)) +
     +		cx*(DBLE(xpneq(14)) + cx*(DBLE(xpneq(15)) +
     +		cx*(DBLE(xpneq(16)) + cx*(DBLE(xpneq(17)) + csom ))))
     +		))
	    endif
	    if ( ax .gt. bdeq05 ) then
		csom = cx*(DBLE(xpneq(6)) + cx*(DBLE(xpneq(7)) +
     +		cx*(DBLE(xpneq(8)) + cx*(DBLE(xpneq(9)) +
     +		cx*(DBLE(xpneq(10)) + cx*(DBLE(xpneq(11)) + csom ))))))
	    endif
	    if ( ax .gt. bdeq01 ) then
		csom = cx*(DBLE(xpneq(2)) + cx*(DBLE(xpneq(3)) +
     +		cx*(DBLE(xpneq(4)) + cx*(DBLE(xpneq(5)) + csom ))))
	    endif
	    cb0p = -cx*(DBLE(xpneq(1))+csom)
	    goto 990
	endif
* -#] taylor expansion: 
* -#[ normal case:
*
*	normal case. first determine if the arguments of the logarithm
*	has positive real part: (we assume Re(cm) > Im(cm) )
*
	call ffclmb(clam,-cp,-cm,-cm,cmp,cmp,czero)
	cslam = sqrt(clam)
	call ffcoot(zm,zp,cone,chalf,cm/cp,cslam/(2*cp),ier)
	cs1 = zp/zm
	if ( absc(cs1-1) .lt. xloss ) then
*	    In this case a quicker and more accurate way is to
*	    calculate log(1-cx).
	    cs2 = cp - cslam
	    if ( absc(cs2) .lt. xloss*absc(cp) ) then
		cs2 = -cslam*(cp+cslam)/(4*cp*cm)
	    else
		cs2 = -2*cslam/cs2
	    endif
	    cs = zfflo1(cs2/(2*cm),ier)
	else
*	    finally the normal case
	    cs = zfflog(cs1,0,czero,ier)
	endif
	cs = cslam*cs/cp
	cb0p = cs - 2
*
*	eta terms
*
	n1 = nffet1(zp,1/zm,cs1,ier)
	if ( DIMAG(cp).eq.0 ) then
	    n2 = nffet1(-zp,-1/zm,cs1,ier)
	else
*	    use the onshell expression to get the correct continuation
	    ck = DBLE(cp)
	    call ffclmb(clamr,-ck,-cm,-cm,cm-ck,cm-ck,czero)
	    cslamr = sqrt(clamr)
	    call ffcoot(zmr,zpr,cone,chalf,cm/ck,cslamr/(2*ck),ier)
	    if ( absc(zm-zmr)+absc(zp-zpr).gt.absc(zm-zpr)+absc(zp-zmr) 
     +	    		) then
	    	cs1 = zmr
	    	zmr = zpr
	    	zpr = cs1
	    endif
	    if ( DIMAG(zmr).eq.0 .or. DIMAG(zpr).eq.0 ) then
	    	if ( DBLE(zpr).gt.DBLE(zmr) ) then
	    	    n2 = +1
	    	else
	    	    n2 = -1
	    	endif
	    else
	    	n2 = nffeta(-zpr,-1/zmr,ier)
	    endif
	endif
	if ( n1+n2 .ne. 0 )
     +		cb0p = cb0p - cslam*c2ipi*(n1+n2)/(2*cp)
*	also superfluous - just to make sure
	goto 990
* -#] normal case: 
*
*  #] both masses equal: 
*  #[ unequal nonzero masses:
  400	continue
* -#[	get log(xm2/xm1):
	cx = cm2/cm1
	c = cx-1
	if ( 1/absc(cx) .lt. xclogm ) then
	    call fferr(6,ier)
	    clogmm = 0
	elseif ( absc(c) .lt. xloss ) then
	    clogmm = zfflo1(cm1m2/cm1,ier)
	else
	    clogmm = log(cx)
	endif
* -#]	get log(xm2/xm1): 
* -#[	cp = 0:
*
*	first a special case
*
	if ( cp .eq. 0 ) then
	    cs2 = ((cm2+cm1) / cm1m2)*clogmm
*	    save the factor 1/2 for the end
	    cs = - cs2 - 2
	    if ( absc(cs) .lt. xloss*2 ) then
*		Taylor expansions: choose which one
		cx = cm1m2/cm1
		ax = absc(cx)
		if ( ax .lt. .15 .or. precc .gt. 1.E-8 .and. ax
     +			.lt. .3 ) then
*		#[ taylor 1:
*
*		    This is the simple Taylor expansion 'n1'
*
*--#[		    data and bounds:
*		    get the coefficients of the taylor expansion
		    if ( initn1 .eq. 0 ) then
			initn1 = 1
			do 410 i = 1,30
  410			    xpnn1(i)=DBLE(i)/DBLE((i+1)*(i+2))
		    endif
*		    determine the boundaries for 1,5,10,15 terms
		    if ( xprcn1 .ne. precc ) then
			xprcn1 = precc
			sprec = precx
			precx = precc
			bdn101 = ffbnd(1,1,xpnn1)
			bdn105 = ffbnd(1,5,xpnn1)
			bdn110 = ffbnd(1,10,xpnn1)
			bdn115 = ffbnd(1,15,xpnn1)
			precx = sprec
		    endif
*--#]		    data and bounds: 
*		    calculate:
		    if ( ax .gt. bdn110 ) then
			cs = cx*(DBLE(xpnn1(11)) + cx*(DBLE(xpnn1(12))
     +			   + cx*(DBLE(xpnn1(13)) + cx*(DBLE(xpnn1(14))
     +			   + cx*(DBLE(xpnn1(15))) ))))
		    else
			cs = 0
		    endif
		    if ( ax .gt. bdn105 ) then
			cs = cx*(DBLE(xpnn1(6)) + cx*(DBLE(xpnn1(7)) +
     +			     cx*(DBLE(xpnn1(8)) + cx*(DBLE(xpnn1(9)) +
     +			     cx*(DBLE(xpnn1(10)) + cs)))))
		    endif
		    if ( ax .gt. bdn101 ) then
			cs = cx*(DBLE(xpnn1(2)) + cx*(DBLE(xpnn1(3)) +
     +			     cx*(DBLE(xpnn1(4)) + cx*(DBLE(xpnn1(5)) +
     +			     cs))))
		    endif
		    cs = cx*cx*(DBLE(xpnn1(1)) + cs)
*		#] taylor 1: 
		else
*		#[ taylor 2:
*
*		    This is the more complicated exponential Taylor
*		    expansion 'n2'
*
*  #[		    bounds:
*		    determine the boundaries for 1,5,10,15 terms for this
*		    Taylor expansion (starting at i=4)
*
		    if ( xprnn2 .ne. precc ) then
			xprnn2 = precc
			sprec = precx
			precx = precc
			bdn201 = ffbnd(4,1,xinfac)
			bdn205 = ffbnd(4,5,xinfac)
			bdn210 = ffbnd(4,10,xinfac)
			bdn215 = ffbnd(4,15,xinfac)
			precx = sprec
		    endif
*  #]		    bounds: 
*		    calculate:
		    cy = 2*cx/(2-cx)
		    ay = absc(cy)
		    if ( ay .gt. bdn210 ) then
			cs = cy*(DBLE(xinfac(14)) + cy*(DBLE(xinfac(15))
     +			   + cy*(DBLE(xinfac(16)) + cy*(DBLE(xinfac(17))
     +			   + cy*(DBLE(xinfac(18)))))))
		    else
			cs = 0
		    endif
		    if ( ay .gt. bdn205 ) then
			cs = cy*(DBLE(xinfac(9)) + cy*(DBLE(xinfac(10))
     +			   + cy*(DBLE(xinfac(11)) + cy*(DBLE(xinfac(12))
     +			   + cy*(DBLE(xinfac(13)) + cs)))))
		    endif
		    if ( ay .gt. bdn201 ) then
			cs = cy*(DBLE(xinfac(5)) + cy*(DBLE(xinfac(6))
     +			   + cy*(DBLE(xinfac(7)) + cy*(DBLE(xinfac(8))
     +			   + cs))))
		    endif
		    cs = (1-cx)*cy**4 * (DBLE(xinfac(4)) + cs)
		    cs = cx*cy**2*(1+cy)/12 - cs
		    cs = - 2*zfflo1(cs,ier)/cy
*		#] taylor 2: 
		endif
	    endif
	    cb0p = cs/2
	    goto 990
	endif
* -#]	cp = 0: 
* -#[	normal case:
*
*	(programmed anew 28-oct-1991)
*
	call ffclmb(clam,cm1,cm2,cp,cm1m2,cm1p,cm2p)
	cslam = sqrt(clam)
	if ( is1.eq.1 ) then
	    cs = +cpiDpj(2,3)
	else
	    cs = -cpiDpj(1,3)
	endif
	call ffcoot(zm,zp,cp,cs,cm2,cslam/2,ier)
	zm1 = 1-zm
	zp1 = 1-zp
	if ( absc(zm1) .lt. xloss .or. absc(zp1) .lt. xloss ) then
	    if ( is1.eq.1 )  then
		cs = -cpiDpj(1,3)
	    else
		cs = +cpiDpj(2,3)
	    endif
	    call ffcoot(zp1,zm1,cp,cs,cm1,cslam/2,ier)
	    if ( abs(DIMAG(zm)) .lt. abs(DIMAG(zm1)) ) then
		zm = DCMPLX(DBLE(zm),-DIMAG(zm1))
	    else
		zm1 = DCMPLX(DBLE(zm1),-DIMAG(zm))
	    endif
	    if ( abs(DIMAG(zp)) .lt. abs(DIMAG(zp1)) ) then
		zp = DCMPLX(DBLE(zp),-DIMAG(zp1))
	    else
		zp1 = DCMPLX(DBLE(zp1),-DIMAG(zp))
	    endif
	endif
	if ( DIMAG(cp).ne.0 ) then
*	    compute roots for Im(cp).eq.0 for continuation terms.
	    ck = DBLE(cp)
	    call ffclmb(clamr,cm1,cm2,ck,cm1m2,cm1-ck,cm2-ck)
	    cslamr = sqrt(clamr)
	    if ( absc(cslamr-cslam).gt.absc(cslamr+cslam) ) 
     +	    	cslamr = -cslamr
	    cs = (cm2-cm1+ck)/2
	    call ffcoot(zmr,zpr,ck,cs,cm2,cslamr/2,ier)
	    zm1r = 1-zmr
	    zp1r = 1-zpr
	    if ( absc(zm1r) .lt. xloss .or. absc(zp1r) .lt. xloss ) then
		cs = -(cm2-cm1-ck)/2
		call ffcoot(zp1r,zm1r,ck,cs,cm1,cslamr/2,ier)
		if ( abs(DIMAG(zmr)) .lt. abs(DIMAG(zm1r)) ) then
		    zmr = DCMPLX(DBLE(zmr),-DIMAG(zm1r))
		else
		    zm1r = DCMPLX(DBLE(zm1r),-DIMAG(zmr))
		endif
		if ( abs(DIMAG(zpr)) .lt. abs(DIMAG(zp1r)) ) then
		    zpr = DCMPLX(DBLE(zpr),-DIMAG(zp1r))
		else
		    zp1r = DCMPLX(DBLE(zp1r),-DIMAG(zpr))
		endif
	    endif
	else
	    zmr  = zm
	    zm1r = zm1
	    zpr  = zp
	    zp1r = zp1
	endif
	call ffc1lg(cs1,zm,zm1,zmr,zm1r,-1,ier)
	call ffc1lg(cs2,zp,zp1,zpr,zp1r,+1,ier)
	cb0p = -clogmm/2 + cs1 + cs2
	smax = max(absc(clogmm)/2,absc(cs1),absc(cs2))
	if ( absc(cb0p) .lt. xloss*smax ) then
	    call ffwarn(7,ier,absc(cb0p),smax)
	endif
	goto 990
* -#]	normal case: 
*  #] unequal nonzero masses: 
*  #[ debug:
  990	continue
*  #] debug: 
*###] ffcb0p: 
	end
*###[ ffc1lg:
	subroutine ffc1lg(cs,z,z1,zr,z1r,is,ier)
***#[*comment:***********************************************************
*									*
*	Calculate the potentially unstable combination -1-z*log(1-1/z)	*
*	= sum_{n=1} 1/(n+1) z^{-n}.					*
*									*
*	Input	z,z1	complex		root, z1=1-z			*
*		zr,z1r	complex		root for Im(p^2)=0, z1r=1-zr	*
*		is	integer		-1: roots are z-, +1: z+	*
*									*
*	Output	cs	complex		see above			*
*		ier	integer		usual error flag		*
*									*
***#]*comment:*********************************************************** 
*  #[ declarations:
	implicit none
*
*	arguments
*
	integer is,ier
	DOUBLE COMPLEX cs,z,z1,zr,z1r
*
*	local variables
*
	DOUBLE PRECISION absc
	DOUBLE COMPLEX c,zfflog
*
*	common blocks
*
	include 'ff.h'
*
*	statement function
*
	absc(c) = abs(DBLE(c)) + abs(DIMAG(c))
*
*  #] declarations: 
*  #[ work:
	if ( 1 .lt. xclogm*absc(z) ) then
	    cs = 0
	elseif ( 1 .lt. precc*absc(z) ) then
	    cs = 1/(2*z)
	elseif ( 1 .gt. 2*xloss*absc(z) ) then
*
*	    normal case
*
	    cs = -1 - z*zfflog(-z1/z,0,czero,ier)
*
*	    check analytical continuation for Im(p^2) -> 0
*
	    if ( z.ne.zr .or. z1.ne.z1r ) then
		c = -z1r/zr
		if ( DBLE(c).lt.0 ) then
*		    check whetehr we chose the correct continuation
		    if ( (DIMAG(c).gt.0 .or. DIMAG(c).eq.0 .and.
     +				is.eq.+1) .and. DIMAG(-z1/z).lt.0 ) then
			cs = cs - c2ipi*z
		    elseif ( (DIMAG(c).lt.0 .or. DIMAG(c).eq.0 .and.
     +				is.eq.-1) .and. DIMAG(-z1/z).gt.0 ) then
			cs = cs + c2ipi*z
		    endif
		endif
	    endif
	    if ( absc(cs) .lt. xloss ) call ffwarn(8,ier,absc(cs),1D0)
	else
*
*	    Taylor expansion
*
	    call ffcayl(cs,1/z,xninv(2),29,ier)
	endif
*  #] work: 
*###] ffc1lg: 
	end
*###[ ffcot2:
	subroutine ffcot2(cpiDpj,cp,cma,cmb,cmap,cmbp,cmamb,ier)
***#[*comment:***********************************************************
*									*
*	Store the 3 dotproducts in the common block ffdot.		*
*									*
*	Input:	see ffxc0p						*
*									*
***#]*comment:*********************************************************** 
*  #[ declarations:
	implicit none
*
*	arguments
*
	integer ier
	DOUBLE COMPLEX cpiDpj(3,3),cp,cma,cmb,cmap,cmbp,cmamb
*
*	local variables
*
	integer ier0,ier1
	DOUBLE PRECISION absc,xmax
	DOUBLE COMPLEX c
*
*	common blocks
*
	include 'ff.h'
*
*	statement function
*
	absc(c) = abs(DBLE(c)) + abs(DIMAG(c))
*  #] declarations: 
*  #[ work:
	ier1 = ier
	cpiDpj(1,1) = cma
	cpiDpj(2,2) = cmb
	cpiDpj(3,3) = cp
	if ( absc(cmap) .lt. absc(cmbp) ) then
		cpiDpj(1,2) = (cmap + cmb)/2
	else
		cpiDpj(1,2) = (cmbp + cma)/2
	endif
	cpiDpj(2,1) = cpiDpj(1,2)
	xmax = min(absc(cma),absc(cmb))/2
	if ( absc(cmamb) .lt. absc(cmbp) ) then
		cpiDpj(1,3) = (-cmamb - cp)/2
	else
		cpiDpj(1,3) = (cmbp - cma)/2
	endif
	cpiDpj(3,1) = cpiDpj(1,3)
	xmax = min(absc(cma),absc(cp))/2
	if ( absc(cmamb) .lt. absc(cmap) ) then
		cpiDpj(2,3) = (-cmamb + cp)/2
	else
		cpiDpj(2,3) = (-cmap + cmb)/2
	endif
	cpiDpj(3,2) = cpiDpj(2,3)
	xmax = min(absc(cmb),absc(cp))/2
	ier = ier1
*  #] work: 
*###] ffcot2: 
	end
