*--#[ log:
*	$Id: ffcrr.f,v 1.1 2016/09/23 18:39:42 jwebb Exp $
*	$Log: ffcrr.f,v $
*	Revision 1.1  2016/09/23 18:39:42  jwebb
*	Initial commit of Tauola
*	
c Revision 1.5  1995/11/10  19:04:23  gj
c Added nicer logging header...
c
c Revision 1.4  1995/10/17  06:55:07  gj
c Fixed ieps error in ffdcrr (ffcxs4.f), added real case in ffcrr, debugging
c info in ffxd0, and warned against remaining errors for del2=0 in ffrot4
c (ffxd0h.f)
c
c Revision 1.3  1995/10/06  09:17:20  gj
c Found stupid typo in ffxc0p which caused the result to be off by pi^2/3 in
c some equal-mass cases.  Added checks to ffcxs4.f ffcrr.f.
c
*--#] log: 


*###[ ffcrr:
	subroutine ffcrr(crr,ipi12,cy,cy1,cz,cz1,cdyz,ld2yzz,cd2yzz,czz,
     +					czz1,isoort,ieps,ier)
***#[*comment:***********************************************************
*									*
*	calculates R as defined in appendix b:				*
*									*
*			/1   log(y-y1+ieps) - log(y0-y1+ieps)		*
*	r(y0,y1,iesp) = \ dy --------------------------------		*
*			/0		y-y0				*
*									*
*	    = li2(c1) - li2(c2) 					*
*		+ eta(-y1,1/(y0-y1))*log(c1)				*
*		- eta(1-y1,1/(y0-y1))*log(c2)				*
*	with								*
*	    c1 = y0 / (y0-y1), c2 = (y0-1) / (y0-y1)			*
*									*
*	the factors pi^2/12 are passed separately in the integer ipi12	*
*	ier is a status flag: 0=ok, 1=numerical problems, 2=error	*
*									*
*	Input:	cy	(complex)					*
*		cy1	(complex)	1-y				*
*		cz	(complex)					*
*		cz1	(complex)	1-z				*
*		cdyz	(complex)	y-z				*
*		ieps	(integer)	denotes sign imaginary part of	*
*					argument logs (0: don't care;	*
*					+/-1: add -ieps to z; +/-2:	*
*					direct in dilogs, no eta's)	*
*									*
*	Output	crr	(complex)	R modulo factors pi^2/12	*
*		ipi12	(integer)	these factors			*
*		ier	(integer)	lost ier digits, >100: error	*
*									*
***#]*comment:***********************************************************
*  #[ declarations:
	implicit none
*
*	arguments
*
	integer ipi12,isoort,ieps,ier
	logical ld2yzz,lreal
	DOUBLE COMPLEX crr(7),cy,cy1,cz,cz1,cdyz,cd2yzz,czz,czz1
*
*	local variables
*
	DOUBLE COMPLEX cfact,cc1,cc2,cc1p,cc2p,carg1,carg2,carg3,
     +		cli1,cli2,cli3,clo1,clo2,clo3,clog1p,clog2p,chill,
     +		cd2,cd21,cd2n,cd21n1,cc1n,cterm,ctot,zfflo1,clog1,clog2,
     +		cc,cli4,clo4
	DOUBLE COMPLEX ctroep,zfflog
	DOUBLE PRECISION xa,xr,absc,xprec,bndtay,ffbnd
	DOUBLE PRECISION y,y1,z,z1,dyz,d2yzz,zz,zz1
	integer i,nffeta,nffet1,iclas1,iclas2,n1,n2,n3,ntot,
     +		i2pi,n3p
	external zfflog,zfflo1,ffbnd,nffeta,nffet1
	save xprec,bndtay
*
*	common blocks
*
	include 'ff.h'
*
*	statement function
*
	absc(cc) = abs(DBLE(cc)) + abs(DIMAG(cc))
*  #] declarations:
*  #[ initialisations:
	data xprec /-1D0/
	if ( xprec .ne. precx ) then
	    xprec = precx
	    bndtay = ffbnd(2,18,xn2inv)
*	    print *,'bndtay = ',bndtay
	endif
*  #] initialisations:
*  #[ real case:
	if ( DIMAG(cy).eq.0 .and. DIMAG(cy1).eq.0 .and. DIMAG(cz).eq.0
     +		.and. DIMAG(cz1).eq.0 ) then
	    y  = DBLE(cy)
	    y1 = DBLE(cy1)
	    z  = DBLE(cz)
	    z1 = DBLE(cz1)
	    dyz = DBLE(cdyz)
	    d2yzz = DBLE(cd2yzz)
	    zz = DBLE(czz)
	    zz1 = DBLE(czz1)
	    call ffcxr(crr,ipi12,y,y1,z,z1,dyz,ld2yzz,d2yzz,zz,zz1,
     +		.FALSE.,0D0,ieps,ier)
	    return
	endif
*  #] real case:
*  #[ arguments:
*
*	get the arguments
*
	xa = absc(cdyz)
	if ( xa .eq. 0 ) then
	    return
*	This line is for 68000 compilers that have a limited range for
*	complex division (Absoft, Apollo, Gould NP1):
	elseif ( DBLE(cdyz) .lt. xclogm .or. DIMAG(cdyz) .lt. xclogm
     +		.or. 1/xa .lt. xclogm ) then
	    ctroep = cdyz*DBLE(1/xa)
	    cfact = 1/ctroep
	    cfact = DBLE(1/xa)*cfact
	else
	    cfact = 1/cdyz
	endif
	cc1 = cy * cfact
	cc2 = - cy1 * cfact
*
*	see if we just need the real part
*
	lreal = mod(isoort,5) .eq. 0
*  #] arguments:
*  #[ which area?:
*
*	determine the area:	1={|x|<=1,Re(x)<=1/2},
*				2={|1-x|<=1,Re(x)>1/2}
*				3={|x|>1,|1-x|>1}
*
	xr = DBLE(cc1)
	xa = absc(cc1)
	if ( xa .gt. 1 .and. xa .lt. 1+sqrt(2.) ) then
*	    we need a more accurate estimate
	    xa = xr**2 + DIMAG(cc1)**2
	endif
	if ( ld2yzz .and. absc(cc1+1) .lt. xloss/2 ) then
	    iclas1 = 4
	    cc1p = cc1
	elseif ( xa .le. 1 .and. xr .le. 0.5 ) then
	    iclas1 = 1
	    cc1p = cc1
	elseif ( xa .lt. 1+sqrt(2.) .and. xa .lt. 2*xr ) then
	    iclas1 = 2
	    cc1p = -cz * cfact
	    if ( abs(DIMAG(cc1p)) .lt. precc*abs(DBLE(cc1p)) )
     +		cc1p = DBLE(cc1p)
	else
	    iclas1 = 3
	    if ( 1/xa .lt. xclogm ) then
		ctroep = cc1*DBLE(1/xa)
		ctroep = 1/ctroep
		cc1p = ctroep*DBLE(1/xa)
	    else
		cc1p = 1/cc1
	    endif
	endif
	xr = DBLE(cc2)
	xa = absc(cc2)
	if ( xa .gt. 1 .and. xa .lt. 1+sqrt(2.) ) then
	    xa = xr**2 + DIMAG(cc2)**2
	endif
	if ( ld2yzz .and. absc(cc2+1) .lt. xloss ) then
	    iclas2 = 4
	    cc2p = cc2
	elseif ( xa .le. 1 .and. xr .le. 0.5 ) then
	    iclas2 = 1
	    cc2p = cc2
	elseif ( xa .lt. 1+sqrt(2.) .and. xa .lt. 2*xr ) then
	    iclas2 = 2
	    cc2p = cz1 * cfact
	    if ( abs(DIMAG(cc2p)) .lt. precc*abs(DBLE(cc2p)) )
     +		cc2p = DBLE(cc2p)
	else
	    iclas2 = 3
	    if ( 1/xa .lt. xclogm ) then
		ctroep = cc2*DBLE(1/xa)
		ctroep = 1/ctroep
		cc2p = ctroep*DBLE(1/xa)
	    else
		cc2p = 1/cc2
	    endif
	endif
*
*	throw together if they are close
*
	if ( iclas1 .ne. iclas2 .and. absc(cc1-cc2) .lt. 2*xloss )
     +		then
*	    we don't want trouble with iclasn = 4
	    if ( iclas1 .eq. 4 ) iclas1 = 1
	    if ( iclas2 .eq. 4 ) iclas2 = 1
	    if ( iclas1 .eq. iclas2 ) goto 5
*	    go on
	    if ( iclas1 .le. iclas2 ) then
		iclas2 = iclas1
		if ( iclas1 .eq. 1 ) then
		    cc2p = cc2
		else
		    cc2p = cz1*cfact
		endif
	    else
		iclas1 = iclas2
		if ( iclas1 .eq. 1 ) then
		    cc1p = cc1
		else
		    cc1p = -cz*cfact
		endif
	    endif
	endif
    5	continue
*  #] which area?:
*  #[ eta's:
*
*	get eta1 and eta2
*
	if ( abs(ieps) .ge. 2 .or. isoort .eq. -2 ) then
	    n1 = 0
	    n2 = 0
	else
	if ( DIMAG(cz) .eq. 0 .or. DIMAG(cz1) .eq. 0 ) then
	    if ( DIMAG(cz1) .eq. 0 ) then
		if ( DIMAG(cz) .eq. 0 ) then
*		    cz is really real, the hard case:
		    if ( cz .eq. 0 ) then
*			multiplied with log(1), so don't care:
			n1 = 0
*			look at ieps for guidance
*			n2 = nffet1(DCMPLX(DBLE(0),DBLE(ieps)),cfact,cfact,ier) = 0
			n2 = 0
		    elseif ( cz1 .eq. 0 ) then
			n1 = nffet1(DCMPLX(DBLE(0),DBLE(ieps)),cfact,
     +				-cfact,ier)
			n2 = 0
		    else
			n1 = nffet1(DCMPLX(DBLE(0),DBLE(ieps)),cfact,
     +				-cz*cfact,ier)
			n2 = nffet1(DCMPLX(DBLE(0),DBLE(ieps)),cfact,
     +				cz1*cfact,ier)
		    endif
		else
		    n1 = nffet1(-cz,cfact,-cz*cfact,ier)
		    n2 = nffet1(-cz,cfact,cz1*cfact,ier)
		endif
	    else
		n1 = nffet1(cz1,cfact,-cz*cfact,ier)
		n2 = nffet1(cz1,cfact,cz1*cfact,ier)
	    endif
	else
*	    the imaginary part of cc1, cc1p is often very unstable.
*	    make sure it agrees with the actual sign used.
	    if ( iclas1 .eq. 2 ) then
		if ( DIMAG(cc1p) .eq. 0 ) then
*		    if y (or y1 further on) is purely imaginary
*		    give a random shift, this will also be used in
*		    the transformation terms.  Checked 7-mar-94 that it
*		    is independent of the sign used.
		    if ( DBLE(cy).eq.0 ) cy = cy +
     +			isgnal*DBLE(precc)*DIMAG(cy)
		    n1 = nffet1(-cz,cfact,DCMPLX(DBLE(0),ieps*DBLE(cy)),
     +			ier)
		else
		    n1 = nffet1(-cz,cfact,cc1p,ier)
		endif
	    else
		if ( DIMAG(cc1) .eq. 0 ) then
		    if ( DBLE(cy1).eq.0 ) cy1 = cy1 +
     +			isgnal*DBLE(precc)*DIMAG(cy)
		    n1 = nffet1(-cz,cfact,DCMPLX(DBLE(0),
     +					-ieps*DBLE(cy1)),ier)
		else
		    n1 = nffet1(-cz,cfact,-cc1,ier)
		endif
	    endif
	    if ( iclas2 .eq. 2 ) then
		if ( DIMAG(cc2p) .eq. 0 ) then
		    if ( DBLE(cy).eq.0 ) cy = cy +
     +			isgnal*DBLE(precc)*DIMAG(cy)
		    n2 = nffet1(cz1,cfact,DCMPLX(DBLE(0),ieps*DBLE(cy)),
     +			ier)
		else
		    n2 = nffet1(cz1,cfact,cc2p,ier)
		endif
	    else
		if ( DIMAG(cc2) .eq. 0 ) then
		    if ( DBLE(cy1).eq.0 ) cy1 = cy1 +
     +			isgnal*DBLE(precc)*DIMAG(cy)
		    n2 = nffet1(cz1,cfact,DCMPLX(DBLE(0),
     +					-ieps*DBLE(cy1)),ier)
		else
		    n2 = nffet1(cz1,cfact,-cc2,ier)
		endif
	    endif
	endif
	endif
*  #] eta's:
*  #[ calculations:
*	3-oct-1995 changed code to only use second criterium if the
*	Taylor expansion is used - otherwise the Hill identity will
*	only make things worse
	if ( iclas1 .eq. iclas2 .and. isoort .ne. -2 .and.
     +		( absc(cc1p-cc2p) .lt. 2*xloss*absc(cc1p)
     +		.or. lreal .and. abs(DBLE(cc1p-cc2p)) .lt. 2*xloss*
     +			abs(DBLE(cc1p)) .and. (abs(DBLE(cc2p)) +
     +			DIMAG(cc2p)**2/4) .lt. xloss .and.
     +			abs(DIMAG(cc2p)) .lt. bndtay ) ) then
*	    Close together:
* -#[	    handle dilog's:
	    if ( .not. lreal .and. absc(cc2p) .gt. xloss
     +		 .or. lreal .and. ( (abs(DBLE(cc2p)) + DIMAG(cc2p)**2/4)
     +			.gt. xloss .or. abs(DIMAG(cc2p)) .gt. bndtay ) )
     +		then
*--#[		Hill identity:
*
*		Use the Hill identity to get rid of the cancellations.
*
*
*	    first get the arguments:
*
		if ( iclas1 .eq. 1 .or. iclas1 .eq. 4 ) then
		    carg1 = 1/cy
		    carg2 = 1/cz1
		    carg3 = carg2/cc1p
		elseif ( iclas1 .eq. 2 ) then
		    carg1 = 1/cz
		    carg2 = 1/cy1
		    carg3 = carg2/cc1p
		elseif ( iclas1 .eq. 3 ) then
		    carg1 = 1/cy1
		    carg3 = 1/cz1
		    carg2 = carg3*cc1p
		endif
		call ffzli2(cli1,clo1,carg1,ier)
		call ffzli2(cli2,clo2,carg2,ier)
		call ffzli2(cli3,clo3,carg3,ier)
		if ( absc(cc2p) .lt. xloss ) then
		    clog2p = zfflo1(cc2p,ier)
		else
		    clog2p = zfflog(1-cc2p,0,czero,ier)
		endif
		chill = clo1*clog2p
*--#]		Hill identity:
	    else
*--#[		Taylor expansion:
*
*		if the points are close to zero do a Taylor
*		expansion of the first and last dilogarithm
*
*			Li2(cc1p) - Li2(cc2p)
*			  = sum cc1p^i ( 1-(1-cd2)^i ) /i^2
*
*		with cd2 = 1-cc2p/cc1p = ...
*
		if ( iclas1 .eq. 1 .or. iclas1 .eq. 4 ) then
		    cd2 = 1/cy
		elseif ( iclas1 .eq. 2 ) then
		    cd2 = 1/cz
		elseif ( iclas1 .eq. 3 ) then
		    cd2 = 1/cy1
		endif
		cd21 = 1-cd2
		cd21n1 = 1
		cc1n = cc1p
		cd2n = cd2
		ctot = cc1p*cd2
		do 50 i=2,20
		    cc1n = cc1n*cc1p
		    cd21n1 = cd21n1*cd21
		    cd2n = cd2n + cd2*cd21n1
		    cterm = cc1n*cd2n*DBLE(xn2inv(i))
		    ctot = ctot + cterm
		    if ( absc(cterm) .le. precc*absc(ctot) .or.
     +			 lreal .and. abs(DBLE(cterm)) .le. precc*
     +				abs(DBLE(ctot)) ) goto 51
   50		continue
   51		continue
		cli1 = ctot
		cli2 = 0
		cli3 = 0
		chill = 0
*		for the eta+transformation section we also need
		if ( iclas1.ne.1 .or. n1.ne.0 .or. n2.ne.0 )
     +			clo1 = zfflo1(cd2,ier)
		if ( iclas1.eq.2 ) clo2 = zfflo1(1/cy1,ier)
*--#]		Taylor expansion:
	    endif
*
* -#]	    handle dilog's:
* -#[	    handle eta + transformation terms:
	    if ( iclas1.eq.1 .or. iclas1.eq.4 ) then
*--#[		no transformation:
*
*		no transformation was made.
*
*		crr(5) = 0
		if ( n1 .ne. n2 ) then
		    if ( absc(cc1) .lt. xclogm ) then
			call fferr(23,ier)
		    else
*			imaginary part not checked
			ier = ier + 50
			crr(5) = (n1-n2)*c2ipi*zfflog(cc1,ieps,-cy,ier)
		    endif
		endif
*		crr(6) = 0
*		crr(7) = 0
		if ( n2.ne.0 ) then
		    crr(6) = - n2*c2ipi*clo1
		    n3 = nffeta(cc2,1/cc1,ier)
		    if ( n3 .ne. 0 ) then
			crr(7) = n2*n3*c2ipi**2
*		    else
*			crr(7) = 0
		    endif
		endif
*--#]		no transformation:
	    elseif ( iclas1 .eq. 2 ) then
*--#[		transform 1-x:
*
*		we tranformed to 1-x for both dilogs
*
		if ( absc(cc1p) .lt. xloss ) then
		    clog1 = zfflo1(cc1p,ier)
		else
		    clog1 = zfflog(cc1,ieps,-cy,ier)
		endif
		if ( DIMAG(cc2p).eq.0 ) then
		    if ( DIMAG(cc1p).eq.0 ) then
*			use the ieps instead
			n3 = 0
		    else
			n3 = nffet1(DCMPLX(DBLE(0),ieps*DBLE(cy)),
     +				1/cc1p,cc2p/cc1p,ier)
		    endif
		else
		    if ( DIMAG(cc1p).eq.0 ) then
			n3 =nffet1(cc2p,DCMPLX(DBLE(0),-ieps*DBLE(cy1)),
     +				cc2p/cc1p,ier)
		    else
			n3 = nffet1(cc2p,1/cc1p,cz,ier)
		    endif
		endif
		ntot = n1-n2-n3
		crr(5) = (ntot*c2ipi + clo1)*clog1
		clog2p = zfflog(cc2p,ieps,cy,ier)
		crr(6) = clo2*(n2*c2ipi - clog2p)
*--#]		transform 1-x:
	    elseif ( iclas1 .eq. 3 ) then
*--#[		transform 1/x:
*
*		we transformed to 1/x for both dilogs
*
		clog2p = zfflog(-cc2p,ieps,cy1,ier)
		if ( DIMAG(cc2p).eq.0 .or. DIMAG(cc1).eq.0 ) then
*		    we chose the eta's already equal, no worry.
		    n3 = 0
		    n3p = 0
		else
		    n3 = nffet1(-cc2p,-cc1,-cy/cy1,ier)
		    n3p = nffet1(cc2p,cc1,-cy/cy1,ier)
		endif
		if ( n3.ne.0 .or. n3p.ne.0 .or. n1.ne.n2 ) then
*		    for the time being the normal terms, I'll have to think of
*		    something smarter one day
		    clog1p = zfflog(-cc1p,ieps,-cy,ier)
		    crr(5) = -clog1p**2/2
		    crr(6) = +clog2p**2/2
		    crr(7) = (n1*zfflog(cc1,ieps,cy,ier) -
     +				n2*zfflog(cc2,ieps,-cy1,ier))*c2ipi
		else
		    crr(5) = clo1*(n2*c2ipi + clog2p - clo1/2)
		endif
*--#]		transform 1/x:
	    endif
* -#]	    handle eta + transformation terms:
* -#[	    add up:
	    if ( iclas1 .eq. 1 .or. iclas1 .eq. 4 ) then
		crr(1) = cli1
		crr(2) = cli2
		crr(3) = - cli3
		crr(4) = chill
	    else
		crr(1) = - cli1
		crr(2) = - cli2
		crr(3) = cli3
		crr(4) = - chill
	    endif
* -#]	    add up:
	else
*	    Normal case:
* -#[	    handle dilogs:
*
*	    the dilogs will not come close together so just go on
*	    only the special case cc1p ~ (-1,0) needs special attention
*
	    if ( iclas1 .ne. 4 .or. .not. ld2yzz ) then
		call ffzli2(cli1,clo1,cc1p,ier)
	    else
		cd2 = cd2yzz + czz
		if ( absc(cd2) .lt. xloss*absc(cd2yzz) ) then
		    cd2 = cy + cdyz
		endif
		cd2 = cd2/cdyz
		cfact = 1/(2-cd2)
		call ffzli2(cli1,clo1,cd2*cfact,ier)
		call ffzli2(cli3,clo3,-cd2*cfact,ier)
		call ffzli2(cli4,clo4,cd2,ier)
	    endif
	    if ( iclas2 .ne. 4 .or. .not. ld2yzz ) then
		call ffzli2(cli2,clo2,cc2p,ier)
	    else
		if ( iclas1 .eq. 4 ) call fferr(26,ier)
		cd2 = cd2yzz - czz1
		if ( absc(cd2) .lt. xloss*absc(cd2yzz) ) then
		    cd2 = cdyz - cy1
		endif
		cd2 = cd2/cdyz
		cfact = 1/(2-cd2)
		call ffzli2(cli2,clo2,cd2*cfact,ier)
		call ffzli2(cli3,clo3,-cd2*cfact,ier)
		call ffzli2(cli4,clo4,cd2,ier)
	    endif
* -#]	    handle dilogs:
* -#[	    handle eta terms:
*
*	    the eta's
*
	    if ( n1 .ne. 0 ) then
		if ( iclas1 .ne. 2 .or. absc(cc1p) .gt. xloss ) then
		    if ( DBLE(cc1) .gt. -abs(DIMAG(cc1)) ) then
			clog1 = zfflog(cc1,ieps,cy,ier)
		    else
*			take apart the factor i*pi^2
			if ( iclas1 .eq. 4 ) then
			    clog1 = zfflo1(cd2,ier)
			else
			    clog1 = zfflog(-cc1,0,cy,ier)
			endif
			if ( DIMAG(cc1) .lt. 0 ) then
			    i2pi = -1
			elseif ( DIMAG(cc1) .gt. 0 ) then
			    i2pi = +1
			elseif ( DBLE(cy)*ieps .lt. 0 ) then
			    i2pi = -1
			elseif ( DBLE(cy)*ieps .gt. 0 ) then
			    i2pi = +1
			else
			    call fferr(51,ier)
			    i2pi = 0
			endif
			ipi12 = ipi12 - n1*24*i2pi
		    endif
		else
		    clog1 = zfflo1(cc1p,ier)
		endif
		crr(5) = n1*c2ipi*clog1
*	    else
*		crr(5) = 0
	    endif
	    if ( n2 .ne. 0 ) then
		if ( iclas2 .ne. 2 .or. absc(cc2p) .gt. xloss ) then
		    if ( DBLE(cc2) .gt. -abs(DIMAG(cc2)) ) then
			clog2 = zfflog(cc2,ieps,cy,ier)
		    else
*			take apart the factor i*pi^2
			if ( iclas2 .eq. 4 ) then
			    clog2 = zfflo1(cd2,ier)
			else
			    clog2 = zfflog(-cc2,0,czero,ier)
			endif
			if ( DIMAG(cc2) .lt. 0 ) then
			    i2pi = -1
			elseif ( DIMAG(cc2) .gt. 0 ) then
			    i2pi = +1
			elseif ( DBLE(cy)*ieps .lt. 0 ) then
			    i2pi = -1
			elseif ( DBLE(cy)*ieps .gt. 0 ) then
			    i2pi = +1
			else
			    call fferr(51,ier)
			    i2pi = 0
			endif
			ipi12 = ipi12 + n2*24*i2pi
		    endif
		else
		    clog2 = zfflo1(cc2p,ier)
		endif
		crr(6) = n2*c2ipi*clog2
*	    else
*		crr(6) = 0
	    endif
* -#]	    handle eta terms:
* -#[	    handle transformation terms:
*
*	    transformation of cc1
*
	    if ( iclas1 .eq. 1 ) then
*		crr(3) = 0
	    elseif( iclas1 .eq. 2 ) then
		cli1 = -cli1
		ipi12 = ipi12 + 2
		crr(3) = - clo1*zfflog(cc1p,ieps,cy,ier)
	    elseif ( iclas1 .eq. 3 ) then
		cli1 = -cli1
		ipi12 = ipi12 - 2
		clog1p = zfflog(-cc1p,ieps,cy1,ier)
		crr(3) = - clog1p**2/2
	    elseif ( iclas1 .eq. 4 ) then
*		Note that this sum does not cause problems as d2<<1
		crr(3) = -cli3 - cli4 + clo4*zfflog(cfact,0,czero,ier)
		ipi12 = ipi12 - 1
	    else
		call fferr(25,ier)
	    endif
*
*	    transformation of cc2
*
	    if ( iclas2 .eq. 1 ) then
	    elseif( iclas2 .eq. 2 ) then
		cli2 = -cli2
		ipi12 = ipi12 - 2
		crr(4) = clo2*zfflog(cc2p,ieps,cy,ier)
	    elseif ( iclas2 .eq. 3 ) then
		cli2 = -cli2
		ipi12 = ipi12 + 2
		clog2p = zfflog(-cc2p,ieps,cy1,ier)
		crr(4) = clog2p**2/2
	    elseif ( iclas2 .eq. 4 ) then
*		Note that this sum does not cause problems as d2<<1
		crr(4) = cli3 + cli4 - clo4*zfflog(cfact,0,czero,ier)
		ipi12 = ipi12 + 1
	    else
		call fferr(27,ier)
	    endif
* -#]	    handle transformation terms:
* -#[	    sum:
	    crr(1) = cli1
	    crr(2) = - cli2
	    crr(6) = - crr(6)
*	    crr(7) = 0
* -#]	    sum:
	endif
*  #] calculations:
*###] ffcrr:
	end
