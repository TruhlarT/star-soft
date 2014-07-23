<html>
<head>
<title>Particle Properties</title>
<link rel="stylesheet" type="text/css" href="pythia.css"/>
<link rel="shortcut icon" href="pythia32.gif"/>
</head>
<body>

<script language=javascript type=text/javascript>
function stopRKey(evt) {
var evt = (evt) ? evt : ((event) ? event : null);
var node = (evt.target) ? evt.target :((evt.srcElement) ? evt.srcElement : null);
if ((evt.keyCode == 13) && (node.type=="text"))
{return false;}
}

document.onkeypress = stopRKey;
</script>
<?php
if($_POST['saved'] == 1) {
if($_POST['filepath'] != "files/") {
echo "<font color='red'>SETTINGS SAVED TO FILE</font><br/><br/>"; }
else {
echo "<font color='red'>NO FILE SELECTED YET.. PLEASE DO SO </font><a href='SaveSettings.php'>HERE</a><br/><br/>"; }
}
?>

<form method='post' action='ParticleProperties.php'>
 
<h2>Particle Properties</h2> 
 
A <code>Particle</code> corresponds to one entry/slot in the 
event record. Its properties therefore is a mix of ones belonging 
to a particle-as-such, like its identity code or four-momentum, 
and ones related to the event-as-a-whole, like which mother it has. 
 
<p/> 
What is stored for each particle is 
<ul> 
<li>the identity code,</li> 
<li>the status code,</li> 
<li>two mother indices,</li> 
<li>two daughter indices,</li> 
<li>a colour and an anticolour index,</li> 
<li>the four-momentum and mass,</li> 
<li>the scale at which the particle was produced (optional),</li> 
<li>the polarization/spin/helicity of the particle (optional),</li> 
<li>the production vertex and proper lifetime (optional),</li> 
<li>a pointer to the particle kind in the particle data table, and</li> 
<li>a pointer to the event the particle belongs to.</li> 
</ul> 
From these, a number of further quantities may be derived. 
 
<h3>Basic output methods</h3> 
 
The following member functions can be used to extract the most important 
information: 
 
<a name="method1"></a>
<p/><strong>int Particle::id() &nbsp;</strong> <br/>
the identity of a particle, according to the PDG particle codes 
[<a href="Bibliography.php" target="page">Yao06</a>]. 
   
 
<a name="method2"></a>
<p/><strong>int Particle::status() &nbsp;</strong> <br/>
status code. The status code includes information on how a particle was 
produced, i.e. where in the program execution it was inserted into the 
event record, and why. It also tells whether the particle is still present 
or not. It does not tell how a particle disappeared, whether by a decay, 
a shower branching, a hadronization process, or whatever, but this is 
implicit in the status code of its daughter(s). The basic scheme is: 
<ul> 
<li>status = +- (10 * i + j)</li> 
<li> +          : still remaining particles</li> 
<li> -          : decayed/branched/fragmented/... and not remaining</li> 
<li> i =  1 - 9 : stage of event generation inside PYTHIA</li> 
<li> i = 10 -19 : reserved for future expansion</li> 
<li> i >= 20    : free for add-on programs</li> 
<li> j = 1 - 9  : further specification</li> 
</ul> 
In detail, the list of used or foreseen status codes is: 
<ul> 
<li>11 - 19 : beam particles</li> 
  <ul> 
  <li>11 : the event as a whole</li> 
  <li>12 : incoming beam</li> 
  <li>13 : incoming beam-inside-beam (e.g. <i>gamma</i> 
           inside <i>e</i>)</li> 
  <li>14 : outgoing elastically scattered</li> 
  <li>15 : outgoing diffractively scattered</li> 
  </ul> 
<li>21 - 29 : particles of the hardest subprocess</li> 
  <ul> 
  <li>21 : incoming</li> 
  <li>22 : intermediate (intended to have preserved mass)</li> 
  <li>23 : outgoing</li> 
  <li>24 : outgoing, nonperturbatively kicked out in diffraction</li> 
  </ul> 
<li>31 - 39 : particles of subsequent subprocesses</li> 
  <ul> 
  <li>31 : incoming</li> 
  <li>32 : intermediate (intended to have preserved mass)</li> 
  <li>33 : outgoing</li> 
  <li>34 : incoming that has already scattered</li> 
  </ul> 
<li>41 - 49 : particles produced by initial-state-showers</li> 
  <ul> 
  <li>41 : incoming on spacelike main branch</li> 
  <li>42 : incoming copy of recoiler</li> 
  <li>43 : outgoing produced by a branching</li> 
  <li>44 : outgoing shifted by a branching</li> 
  <li>45 : incoming rescattered parton, with changed kinematics 
           owing to ISR in the mother system (cf. status 34)</li> 
  <li>46 : incoming copy of recoiler when this is a rescattered 
           parton (cf. status 42)</li> 
  <li>47 : a <i>W</i> or <i>Z</i> gauge boson produced in the 
           shower evolution</li> 
  </ul> 
<li>51 - 59 : particles produced by final-state-showers</li> 
  <ul> 
  <li>51 : outgoing produced by parton branching</li> 
  <li>52 : outgoing copy of recoiler, with changed momentum</li> 
  <li>53 : copy of recoiler when this is incoming parton, 
           with changed momentum</li> 
  <li>54 : copy of a recoiler, when in the initial state of a 
           different system from the radiator</li> 
  <li>55 : copy of a recoiler, when in the final state of a 
           different system from the radiator</li> 
  <li>56 : a <i>W</i> or <i>Z</i> gauge boson produced in a 
           shower branching (special case of 51)</li> 
  </ul> 
<li>61 - 69 : particles produced by beam-remnant treatment</li> 
  <ul> 
  <li>61 : incoming subprocess particle with primordial <i>kT</i> 
           included</li> 
  <li>62 : outgoing subprocess particle with primordial <i>kT</i> 
           included</li> 
  <li>63 : outgoing beam remnant</li> 
  </ul> 
<li>71 - 79 : partons in preparation of hadronization process</li> 
  <ul> 
  <li>71 : copied partons to collect into contiguous colour singlet</li> 
  <li>72 : copied recoiling singlet when ministring collapses to 
           one hadron and momentum has to be reshuffled</li> 
  <li>73 : combination of very nearby partons into one</li> 
  <li>74 : combination of two junction quarks (+ nearby gluons) 
           to a diquark</li> 
  <li>75 : gluons split to decouple a junction-antijunction pair</li> 
  <li>76 : partons with momentum shuffled to decouple a 
           junction-antijunction pair </li> 
  <li>77 : temporary opposing parton when fragmenting first two 
           strings in to junction (should disappear again)</li> 
  <li>78 : temporary combined diquark end when fragmenting last 
           string in to junction (should disappear again)</li> 
  </ul> 
<li>81 - 89 : primary hadrons produced by hadronization process</li> 
  <ul> 
  <li>81 : from ministring into one hadron</li> 
  <li>82 : from ministring into two hadrons</li> 
  <li>83, 84 : from normal string (the difference between the two 
           is technical, whether fragmented off from the top of the 
           string system or from the bottom, useful for debug only)</li> 
  <li>85, 86 : primary produced hadrons in junction fragmentation of 
           the first two string legs in to the junction, 
           in order of treatment</li> 
  </ul> 
<li>91 - 99 : particles produced in decay process, or by Bose-Einstein 
  effects</li> 
  <ul> 
  <li>91 : normal decay products</li> 
  <li>92 : decay products after oscillation <i>B0 &harr; B0bar</i> or 
           <i>B_s0 &harr; B_s0bar</i></li> 
  <li>93, 94 : decay handled by external program, normally 
           or with oscillation</li> 
  <li>99 : particles with momenta shifted by Bose-Einstein effects 
           (not a proper decay, but bookkept as an <i>1 &rarr; 1</i> such, 
           happening after decays of short-lived resonances but before 
           decays of longer-lived particles)</li> 
  </ul> 
<li>101 - 109 : particles in the handling of R-hadron production and 
  decay, i.e. long-lived (or stable) particles containing a very heavy 
  flavour</li> 
  <ul> 
  <li>101 : when a string system contains two such long-lived particles, 
            the system is split up by the production of a new q-qbar 
            pair (bookkept as decay chains that seemingly need not conserve 
            flavour etc., but do when considered together)</li> 
  <li>102 : partons rearranged from the long-lived particle end to prepare 
            for fragmentation from this end</li> 
  <li>103 : intermediate "half-R-hadron" formed when a colour octet particle 
            (like the gluino) has been fragmented on one side, but not yet on 
            the other</li> 
  <li>104 : an R-hadron</li> 
  <li>105 : partons or particles formed together with the R-hadron during 
            the fragmentation treatment</li> 
  <li>106 : subdivision of an R-hadron into its flavour content, with 
           momentum split accordingly, in preparation of the decay of 
           the heavy new particle, if it is unstable</li> 
  <li>107 : two temporary leftover gluons joined into one in the formation 
          of a gluino-gluon R-hadron.</li> 
  </ul> 
<li>111 - 199 : reserved for future expansion</li> 
<li>201 - : free to be used by anybody</li> 
</ul> 
<br/><b>Note:</b> a clarification on the role of the "hardest" vs. the 
"subsequent" subprocesses, the 20'ies and 30'ies status code series, 
respectively. Most events contain exactly one "hardest" 
<i>2 &rarr; n</i> interaction, and then an arbitrary number of 
"subsequent" softer <i>2 &rarr; 2</i> ones generated by the 
MPI framework. In the <code>SoftQCD:nonDiffractive</code> event class 
also the "hardest" is generated by the MPI machinery, and can be 
arbitrarily soft, but still with 20'ies codes. Diffractive systems 
span a broad mass range, where the higher masses admit a perturbative 
description with "hard" and "subsequent" subprocesses, like for 
nondiffractive events. A double diffractive event can contain up to two 
such "hardest" interactions, one per diffractive system. A nonperturbative 
diffractive system does not contain any <i>2 &rarr; n</i> subprocesses, 
but there is a kicked-out quark or gluon with status 24, combined with a 
beam remnant of one or two partons with status 63, that together define 
the mass and longitudinal axis of the diffractive system, for use in the 
subsequent hadronization. An event may also contain two 20'ies 
perturbative subcollisions if you use the 
<?php $filepath = $_GET["filepath"];
echo "<a href='ASecondHardProcess.php?filepath=".$filepath."' target='page'>";?>Second Hard Process</a> 
generation machinery.
   
 
<a name="method3"></a>
<p/><strong>int Particle::mother1() &nbsp;</strong> <br/>
   
<strong>int Particle::mother2() &nbsp;</strong> <br/>
the indices in the event record where the first and last mothers are 
stored, if any. There are six allowed combinations of <code>mother1</code> 
and <code>mother2</code>: 
<ol> 
<li><code>mother1 = mother2 = 0</code>: for lines 0 - 2, where line 0 
represents the event as a whole, and 1 and 2 the two incoming 
beam particles; </li> 
<li><code>mother1 = mother2 > 0</code>: the particle is a "carbon copy" 
of its mother, but with changed momentum as a "recoil"  effect, 
e.g. in a shower;</li> 
<li><code>mother1 > 0, mother2 = 0</code>: the "normal" mother case, where 
it is meaningful to speak of one single mother to several products, 
in a shower or decay;</li> 
<li><code>mother1 &lt; mother2</code>, both > 0, for 
<code>abs(status) = 81 - 86</code>: primary hadrons produced from the 
fragmentation of a string spanning the range from <code>mother1</code> 
to <code>mother2</code>, so that all partons in this range should be 
considered mothers; and analogously for 
<code>abs(status) = 101 - 106</code>, the formation of R-hadrons;</li> 
<li><code>mother1 &lt; mother2</code>, both > 0, except case 4: particles 
with two truly different mothers, in particular the particles emerging 
from a hard <i>2 &rarr; n</i> interaction.</li> 
<li><code>mother2 &lt; mother1</code>, both > 0: particles with two truly 
different mothers, notably for the special case that two nearby partons are 
joined together into a status 73 or 74 new parton, in the 
<i>g + q &rarr; q</i> case the <i>q</i> is made first mother 
to simplify flavour tracing.</li> 
</ol> 
<br/><b>Note 1:</b> in backwards evolution of initial-state showers, 
the mother may well appear below the daughter in the event record. 
<br/><b>Note 2:</b> the <code>motherList()</code> method below returns 
a vector of all the mothers, providing a uniform representation for all 
six cases. 
   
 
<a name="method4"></a>
<p/><strong>int Particle::daughter1() &nbsp;</strong> <br/>
   
<strong>int Particle::daughter2() &nbsp;</strong> <br/>
the indices in the event record where the first and last daughters 
are stored, if any. There are five allowed combinations of 
<code>daughter1</code> and <code>daughter2</code>: 
<ol> 
<li><code>daughter1 = daughter2 = 0</code>: there are no daughters 
(so far);</li> 
<li><code>daughter1 = daughter2 > 0</code>: the particle has a 
"carbon copy" as its sole daughter, but with changed momentum 
as a "recoil" effect, e.g. in a shower;</li> 
<li><code>daughter1 > 0, daughter2 = 0</code>: each of the incoming beams 
has only (at most) one daughter, namely the initiator parton of the 
hardest interaction; further, in a <i>2 &rarr; 1</i> hard interaction, 
like <i>q qbar &rarr; Z^0</i>, or in a clustering of two nearby partons, 
the initial partons only have this one daughter;</li> 
<li><code>daughter1 &lt; daughter2</code>, both > 0: the particle has 
a range of decay products from <code>daughter1</code> to 
<code>daughter2</code>;</li> <li><code>daughter2 &lt; daughter1</code>, 
both > 0: the particle has two separately stored decay products (e.g. 
in backwards evolution of initial-state showers).</li> 
</ol> 
<br/><b>Note 1:</b> in backwards evolution of initial-state showers, the 
daughters may well appear below the mother in the event record. 
<br/><b>Note 2:</b> the mother-daughter relation normally is reciprocal, 
but not always. An example is hadron beams (indices 1 and 2), where each 
beam remnant and the initiator of each multiparton interaction has the 
respective beam as mother, but the beam itself only has the initiator 
of the hardest interaction as daughter. 
<br/><b>Note 3:</b> the <code>daughterList()</code> method below 
returns a vector of all the daughters, providing a uniform representation 
for all five cases. With this method, also all the daughters of the beams 
are caught, with the initiators of the basic process given first,  while 
the rest are in no guaranteed order (since they are found by a scanning 
of the event record for particles with the beam as mother, with no further 
information). 
   
 
<a name="method5"></a>
<p/><strong>int Particle::col() &nbsp;</strong> <br/>
   
<strong>int Particle::acol() &nbsp;</strong> <br/>
the colour and anticolour tags, Les Houches Accord [<a href="Bibliography.php" target="page">Boo01</a>] 
style (starting from tag 101 by default, see below). 
<br/><b>Note:</b> in the preliminary implementation of colour sextets 
(exotic BSM particles) that exists since PYTHIA 8.150, a negative 
anticolour tag is interpreted as an additional positive colour tag, 
and vice versa. 
   
 
<a name="method6"></a>
<p/><strong>double Particle::px() &nbsp;</strong> <br/>
   
<strong>double Particle::py() &nbsp;</strong> <br/>
   
<strong>double Particle::pz() &nbsp;</strong> <br/>
   
<strong>double Particle::e() &nbsp;</strong> <br/>
the particle four-momentum components. 
   
 
<a name="method7"></a>
<p/><strong>Vec4 Particle::p() &nbsp;</strong> <br/>
the particle four-momentum vector, with components as above. 
   
 
<a name="method8"></a>
<p/><strong>double Particle::m() &nbsp;</strong> <br/>
the particle mass, stored with a minus sign (times the absolute value) 
for spacelike virtual particles. 
   
 
<a name="method9"></a>
<p/><strong>double Particle::scale() &nbsp;</strong> <br/>
the scale at which a parton was produced, which can be used to restrict 
its radiation to lower scales in subsequent steps of the shower evolution. 
Note that scale is linear in momenta, not quadratic (i.e. <i>Q</i>, 
not <i>Q^2</i>). 
   
 
<a name="method10"></a>
<p/><strong>double Particle::pol() &nbsp;</strong> <br/>
the polarization/spin/helicity of a particle. Currently Pythia does not 
use this variable for any internal operations, so its meaning is not 
uniquely defined. The LHA standard sets <code>SPINUP</code> to be the 
cosine of the angle between the spin vector and the 3-momentum of the 
decaying particle in the lab frame, i.e. restricted to be between +1 
and -1. A more convenient choice could be the same quantity in the rest 
frame of the particle production, either the hard subprocess or the 
mother particle of a decay. Unknown or unpolarized particles should 
be assigned the value 9. 
   
 
<a name="method11"></a>
<p/><strong>double Particle::xProd() &nbsp;</strong> <br/>
   
<strong>double Particle::yProd() &nbsp;</strong> <br/>
   
<strong>double Particle::zProd() &nbsp;</strong> <br/>
   
<strong>double Particle::tProd() &nbsp;</strong> <br/>
the production vertex coordinates, in mm or mm/c. 
   
 
<a name="method12"></a>
<p/><strong>Vec4 Particle::vProd() &nbsp;</strong> <br/>
The production vertex four-vector. Note that the components of a 
<code>Vec4</code> are named <code>px(), py(), pz() and e()</code> 
which of course then should be reinterpreted as above. 
   
 
<a name="method13"></a>
<p/><strong>double Particle::tau() &nbsp;</strong> <br/>
the proper lifetime, in mm/c. It is assigned for all hadrons with 
positive nominal <i>tau</i>, <i>tau_0 > 0</i>, because it can be used 
by PYTHIA to decide whether a particle should or should not be allowed 
to decay, e.g. based on the decay vertex distance to the primary interaction 
vertex. 
   
 
<h3>Input methods</h3> 
 
The same method names as above are also overloaded in versions that 
set values. These have an input argument of the same type as the 
respective output above, and are of type <code>void</code>. 
 
<p/> 
There are also a few alternative methods for input: 
 
<a name="method14"></a>
<p/><strong>void Particle::statusPos() &nbsp;</strong> <br/>
   
<strong>void Particle::statusNeg() &nbsp;</strong> <br/>
sets the status sign positive or negative, without changing the absolute 
value. 
   
 
<a name="method15"></a>
<p/><strong>void Particle::statusCode(int code) &nbsp;</strong> <br/>
changes the absolute value but retains the original sign. 
   
 
<a name="method16"></a>
<p/><strong>void Particle::mothers(int mother1, int mother2) &nbsp;</strong> <br/>
sets both mothers in one go. 
   
 
<a name="method17"></a>
<p/><strong>void Particle::daughters(int daughter1, int daughter2) &nbsp;</strong> <br/>
sets both daughters in one go. 
   
 
<a name="method18"></a>
<p/><strong>void Particle::cols(int col, int acol) &nbsp;</strong> <br/>
sets both colour and anticolour in one go. 
   
 
<a name="method19"></a>
<p/><strong>void Particle::p(double px, double py, double pz, double e) &nbsp;</strong> <br/>
sets the four-momentum components in one go. 
   
 
<a name="method20"></a>
<p/><strong>void Particle::vProd(double xProd, double yProd, double zProd, double tProd) &nbsp;</strong> <br/>
sets the production vertex components in one go. 
   
 
<h3>Further output methods</h3> 
 
In addition, a number of derived quantities can easily be obtained, 
but cannot be set, such as: 
 
<a name="method21"></a>
<p/><strong>int Particle::idAbs() &nbsp;</strong> <br/>
the absolute value of the particle identity code. 
   
 
<a name="method22"></a>
<p/><strong>int Particle::statusAbs() &nbsp;</strong> <br/>
the absolute value of the status code. 
   
 
<a name="method23"></a>
<p/><strong>bool Particle::isFinal() &nbsp;</strong> <br/>
true for a remaining particle, i.e. one with positive status code, 
else false. Thus, after an event has been fully generated, it 
separates the final-state particles from intermediate-stage ones. 
(If used earlier in the generation process, a particle then 
considered final may well decay later.) 
   
 
<a name="method24"></a>
<p/><strong>bool Particle::isRescatteredIncoming() &nbsp;</strong> <br/>
true for particles with a status code -34, -45, -46 or -54, else false. 
This singles out partons that have been created in a previous 
scattering but here are bookkept as belonging to the incoming state 
of another scattering. 
   
 
<a name="method25"></a>
<p/><strong>bool Particle::hasVertex() &nbsp;</strong> <br/>
production vertex has been set; if false then production at the origin 
is assumed. 
   
 
<a name="method26"></a>
<p/><strong>double Particle::m2() &nbsp;</strong> <br/>
squared mass, which can be negative for spacelike partons. 
   
 
<a name="method27"></a>
<p/><strong>double Particle::mCalc() &nbsp;</strong> <br/>
   
<strong>double Particle::m2Calc() &nbsp;</strong> <br/>
(squared) mass calculated from the four-momentum; should agree 
with <code>m(), m2()</code> up to roundoff. Negative for spacelike 
virtualities. 
   
 
<a name="method28"></a>
<p/><strong>double Particle::eCalc() &nbsp;</strong> <br/>
energy calculated from the mass and three-momentum; should agree 
with <code>e()</code> up to roundoff. For spacelike partons a 
positive-energy  solution is picked. This need not be the correct 
one, so it is recommended not to use the method in such cases. 
   
 
<a name="method29"></a>
<p/><strong>double Particle::pT() &nbsp;</strong> <br/>
   
<strong>double Particle::pT2() &nbsp;</strong> <br/>
(squared) transverse momentum. 
   
 
<a name="method30"></a>
<p/><strong>double Particle::mT() &nbsp;</strong> <br/>
   
<strong>double Particle::mT2() &nbsp;</strong> <br/>
(squared) transverse mass. If <i>m_T^2</i> is negative, which can happen 
for a spacelike parton, then <code>mT()</code> returns 
<i>-sqrt(-m_T^2)</i>, by analogy with the negative sign used to store 
spacelike masses. 
   
 
<a name="method31"></a>
<p/><strong>double Particle::pAbs() &nbsp;</strong> <br/>
   
<strong>double Particle::pAbs2() &nbsp;</strong> <br/>
(squared) three-momentum size. 
   
 
<a name="method32"></a>
<p/><strong>double Particle::eT() &nbsp;</strong> <br/>
   
<strong>double Particle::eT2() &nbsp;</strong> <br/>
(squared) transverse energy, 
<i>eT = e * sin(theta) = e * pT / pAbs</i>. 
   
 
<a name="method33"></a>
<p/><strong>double Particle::theta() &nbsp;</strong> <br/>
   
<strong>double Particle::phi() &nbsp;</strong> <br/>
polar and azimuthal angle. 
   
 
<a name="method34"></a>
<p/><strong>double Particle::thetaXZ() &nbsp;</strong> <br/>
angle in the <i>(p_x, p_z)</i> plane, between <i>-pi</i> and 
<i>+pi</i>, with 0 along the <i>+z</i> axis 
   
 
<a name="method35"></a>
<p/><strong>double Particle::pPos() &nbsp;</strong> <br/>
   
<strong>double Particle::pNeg() &nbsp;</strong> <br/>
<i>E +- p_z</i>. 
   
 
<a name="method36"></a>
<p/><strong>double Particle::y() &nbsp;</strong> <br/>
   
<strong>double Particle::eta() &nbsp;</strong> <br/>
rapidity and pseudorapidity. 
   
 
<a name="method37"></a>
<p/><strong>double Particle::xDec() &nbsp;</strong> <br/>
   
<strong>double Particle::yDec() &nbsp;</strong> <br/>
   
<strong>double Particle::zDec() &nbsp;</strong> <br/>
   
<strong>double Particle::tDec() &nbsp;</strong> <br/>
   
<strong>Vec4 Particle::vDec() &nbsp;</strong> <br/>
the decay vertex coordinates, in mm or mm/c. This decay vertex is 
calculated from the production vertex, the proper lifetime and the 
four-momentum assuming no magnetic field or other detector interference. 
It can be used to decide whether a decay should be performed or not, 
and thus is defined also for particles which PYTHIA did not let decay. 
   
 
<p/> 
Not part of the <code>Particle</code> class proper, but obviously tightly 
linked, are the two methods 
 
<a name="method38"></a>
<p/><strong>double m(const Particle& pp1, const Particle& pp2) &nbsp;</strong> <br/>
   
<strong>double m2(const Particle& pp1, const Particle& pp2) &nbsp;</strong> <br/>
the (squared) invariant mass of two particles. 
   
 
<h3>Properties of the particle species</h3> 
 
Each Particle contains a pointer to the respective 
<code>ParticleDataEntry</code> object in the 
<?php $filepath = $_GET["filepath"];
echo "<a href='ParticleDataScheme.php?filepath=".$filepath."' target='page'>";?>particle data tables</a>. 
This gives access to properties of the particle species as such. It is 
there mainly for convenience, and should be thrown if an event is 
written to disk, to avoid any problems of object persistency. Should 
an event later be read back in, the pointer will be recreated from the 
<code>id</code> code if the normal input methods are used. (Use the 
<code><?php $filepath = $_GET["filepath"];
echo "<a href='EventRecord.php?filepath=".$filepath."' target='page'>";?>Event::restorePtrs()</a></code> method 
if your persistency scheme bypasses the normal methods.) This pointer is 
used by the following member functions: 
 
<a name="method39"></a>
<p/><strong>string Particle::name() &nbsp;</strong> <br/>
the name of the particle. 
   
 
<a name="method40"></a>
<p/><strong>string Particle::nameWithStatus() &nbsp;</strong> <br/>
as above, but for negative-status particles the name is given in 
brackets to emphasize that they are intermediaries. 
   
 
<a name="method41"></a>
<p/><strong>int Particle::spinType() &nbsp;</strong> <br/>
<i>2 *spin + 1</i> when defined, else 0. 
   
 
<a name="method42"></a>
<p/><strong>double Particle::charge() &nbsp;</strong> <br/>
   
<strong>int Particle::chargeType() &nbsp;</strong> <br/>
charge, and three times it to make an integer. 
   
 
<a name="method43"></a>
<p/><strong>bool Particle::isCharged() &nbsp;</strong> <br/>
   
<strong>bool Particle::isNeutral() &nbsp;</strong> <br/>
charge different from or equal to 0. 
   
 
<a name="method44"></a>
<p/><strong>int Particle::colType() &nbsp;</strong> <br/>
0 for colour singlets, 1 for triplets, 
-1 for antitriplets and 2 for octets. (A preliminary implementation of 
colour sextets also exists, using 3 for sextets and -3 for antisextets.) 
   
 
<a name="method45"></a>
<p/><strong>double Particle::m0() &nbsp;</strong> <br/>
the nominal mass of the particle, according to the data tables. 
   
 
<a name="method46"></a>
<p/><strong>double Particle::mWidth() &nbsp;</strong> <br/>
   
<strong>double Particle::mMin() &nbsp;</strong> <br/>
   
<strong>double Particle::mMax() &nbsp;</strong> <br/>
the width of the particle, and the minimum and maximum allowed mass value 
for particles with a width, according to the data tables. 
   
 
<a name="method47"></a>
<p/><strong>double Particle::mSel() &nbsp;</strong> <br/>
the mass of the particle, picked according to a Breit-Wigner 
distribution for particles with width. It is different each time called, 
and is therefore only used once per particle to set its mass 
<code>m()</code>. 
   
 
<a name="method48"></a>
<p/><strong>double Particle::constituentMass() &nbsp;</strong> <br/>
will give the constituent masses for quarks and diquarks, 
else the same masses as with <code>m0()</code>. 
   
 
<a name="method49"></a>
<p/><strong>double Particle::tau0() &nbsp;</strong> <br/>
the nominal lifetime <i>tau_0 > 0</i>, in mm/c, of the particle species. 
It is used to assign the actual lifetime <i>tau</i>. 
   
 
<a name="method50"></a>
<p/><strong>bool Particle::mayDecay() &nbsp;</strong> <br/>
flag whether particle has been declared unstable or not, offering 
the main user switch to select which particle species to decay. 
   
 
<a name="method51"></a>
<p/><strong>bool Particle::canDecay() &nbsp;</strong> <br/>
flag whether decay modes have been declared for a particle, 
so that it could be decayed, should that be requested. 
   
 
<a name="method52"></a>
<p/><strong>bool Particle::doExternalDecay() &nbsp;</strong> <br/>
particles that are decayed by an external program. 
   
 
<a name="method53"></a>
<p/><strong>bool Particle::isResonance() &nbsp;</strong> <br/>
particles where the decay is to be treated as part of the hard process, 
typically with nominal mass above 20 GeV (<i>W^+-, Z^0, t, ...</i>). 
   
 
<a name="method54"></a>
<p/><strong>bool Particle::isVisible() &nbsp;</strong> <br/>
particles with strong or electric charge, or composed of ones having it, 
which thereby should be considered visible in a normal detector. 
   
 
<a name="method55"></a>
<p/><strong>bool Particle::isLepton() &nbsp;</strong> <br/>
true for a lepton or an antilepton (including neutrinos). 
   
 
<a name="method56"></a>
<p/><strong>bool Particle::isQuark() &nbsp;</strong> <br/>
true for a quark or an antiquark. 
   
 
<a name="method57"></a>
<p/><strong>bool Particle::isGluon() &nbsp;</strong> <br/>
true for a gluon. 
   
 
<a name="method58"></a>
<p/><strong>bool Particle::isDiquark() &nbsp;</strong> <br/>
true for a diquark or an antidiquark. 
   
 
<a name="method59"></a>
<p/><strong>bool Particle::isParton() &nbsp;</strong> <br/>
true for a gluon, a quark or antiquark up to the b (but excluding top), 
and a diquark or antidiquark consisting of quarks up to the b. 
   
 
<a name="method60"></a>
<p/><strong>bool Particle::isHadron() &nbsp;</strong> <br/>
true for a hadron (made up out of normal quarks and gluons, 
i.e. not for R-hadrons and other exotic states). 
   
 
<a name="method61"></a>
<p/><strong>ParticleDataEntry& particleDataEntry() &nbsp;</strong> <br/>
a reference to the ParticleDataEntry. 
   
 
<h3>Methods that may access the event the particle belongs to</h3> 
 
A particle can be created on its own. When inserted into an event record, 
it obtains a pointer to that event-as-a-whole. It is then possible to 
use methods that do not make sense for a particle in isolation. These 
methods are listed below. Whenever the pointer to the event is not 
defined, these will return an appropriate "null" value, this being -1 
for an integer, false for a bool, and empty for a vector, unless otherwise 
specified. 
 
<a name="method62"></a>
<p/><strong>void Particle::index() &nbsp;</strong> <br/>
the index of the particle itself in the event record. 
   
 
<a name="method63"></a>
<p/><strong>int Particle::statusHepMC() &nbsp;</strong> <br/>
returns the status code according to the HepMC conventions agreed in 
February 2009. This convention does not preserve the full information 
provided by the internal PYTHIA status code, as obtained by 
<code>Particle::status()</code>, but comes reasonably close. 
The allowed output values are: 
<ul> 
<li>0 : an empty entry, with no meaningful information and therefore 
to be skipped unconditionally;</li> 
<li>1 : a final-state particle, i.e. a particle that is not decayed 
further by the generator (may also include unstable particles that 
are to be decayed later, as part of the detector simulation);</li> 
<li>2 : a decayed Standard Model hadron or tau or mu lepton, excepting 
virtual intermediate states thereof (i.e. the particle must undergo 
a normal decay, not e.g. a shower branching);</li> 
<li>3 : a documentation entry (not used in PYTHIA);</li> 
<li>4 : an incoming beam particle;</li> 
<li>11 - 200 : an intermediate (decayed/branched/...) particle that does 
not fulfill the criteria of status code 2, with a generator-dependent 
classification of its nature; in PYTHIA the absolute value of the normal 
status code is used.</li> 
</ul> 
<br/><b>Note:</b> for a particle without a properly set pointer to its 
event, codes 1 and 4 can still be inferred from its status code, while 
everythg else is assigned code 0. 
   
 
<a name="method64"></a>
<p/><strong>int Particle::iTopCopy() &nbsp;</strong> <br/>
   
<strong>int Particle::iBotCopy() &nbsp;</strong> <br/>
are used to trace carbon copies of the particle up to its top mother 
or down to its bottom daughter. If there are no such carbon copies, 
the index of the particle itself will be returned. A carbon copy is 
when the "same" particle appears several times in the event record, but 
with changed momentum owing to recoil effects. 
   
 
<a name="method65"></a>
<p/><strong>int Particle::iTopCopyId() &nbsp;</strong> <br/>
   
<strong>int Particle::iBotCopyId() &nbsp;</strong> <br/>
also trace top mother and bottom daughter, but do not require carbon 
copies, only that one can find an unbroken chain, of mothers or daughters, 
with the same flavour <code>id</code> code. When it encounters ambiguities, 
say a <i>g &rarr; g g</i> branching or a <i>u u &rarr; u u</i> hard 
scattering, it will stop the tracing and return the current position. 
It can be confused by nontrivial flavour changes, e.g. a hard process 
<i>u d &rarr; d u</i> by <i>W^+-</i> exchange will give the wrong 
answer. These methods therefore are of limited use for common particles, 
in particular for the gluon, but should work well for "rare" particles. 
   
 
<a name="method66"></a>
<p/><strong>vector&lt;int&gt; Particle::sisterList(bool traceTopBot = false) &nbsp;</strong> <br/>
returns a vector of all the sister indices of the particle, i.e. all the 
daughters of the first mother, except the particle itself. If the argument 
<code>traceTopBot = true</code> the particle is first traced up with 
<code>iTopCopy()</code> before its mother is found, and then all the 
particles in the <code>daughterList()</code> of this mother are traced down 
with <code>iBotCopy()</code>, omitting the original particle itself. 
The method is not meaningful for the 0 entry, with status code -11, and 
there returns an empty list. 
   
 
<a name="method67"></a>
<p/><strong>bool Particle::isAncestor(int iAncestor) &nbsp;</strong> <br/>
traces the particle upwards through mother, grandmother, and so on, until 
either <i>iAncestor</i> is found or the top of the record is reached. 
Normally one unique mother is required, as is the case e.g. in decay chains 
or in parton showers, so that e.g. the tracing through a hard scattering 
would not work. For hadronization, first-rank hadrons are identified with 
the respective string endpoint quark, which may be useful e.g. for 
<i>b</i> physics, while higher-rank hadrons give <code>false</code>. 
Currently also ministrings that collapsed to one single hadron and 
junction topologies give <code>false</code>. 
   
 
<a name="method68"></a>
<p/><strong>bool Particle::undoDecay() &nbsp;</strong> <br/>
removes the decay chain of the particle and thus restores 
it to its undecayed state. It is only intended for "normal" particle 
decay chains, and will return false in other cases, notably if 
the particle is coloured. The procedure would not work if non-local 
momentum shifts have been performed, such as with a Bose-Einstein 
shift procedure (or for a dipole shower recoiler). As the decay products 
are erased from the event record, mother and daughter indices are 
updated to retain a correct history for the remaining particles. 
   
 
<h3>Methods that perform operations</h3> 
 
There are some further methods, some of them inherited from 
<code>Vec4</code>, to modify the properties of a particle. 
They are of little interest to the normal user. 
 
<a name="method69"></a>
<p/><strong>void Particle::rescale3(double fac) &nbsp;</strong> <br/>
multiply the three-momentum components by <code>fac</code>. 
   
 
<a name="method70"></a>
<p/><strong>void Particle::rescale4(double fac) &nbsp;</strong> <br/>
multiply the four-momentum components by <code>fac</code>. 
   
 
<a name="method71"></a>
<p/><strong>void Particle::rescale5(double fac) &nbsp;</strong> <br/>
multiply the four-momentum components and the mass by <code>fac</code>. 
   
 
<a name="method72"></a>
<p/><strong>void Particle::rot(double theta, double phi) &nbsp;</strong> <br/>
rotate three-momentum and production vertex by these polar and azimuthal 
angles. 
   
 
<a name="method73"></a>
<p/><strong>void Particle::bst(double betaX, double betaY, double betaZ) &nbsp;</strong> <br/>
boost four-momentum and production vertex by this three-vector. 
   
 
<a name="method74"></a>
<p/><strong>void Particle::bst(double betaX, double betaY, double betaZ, double gamma) &nbsp;</strong> <br/>
as above, but also input the <i>gamma</i> value, to reduce roundoff errors. 
   
 
<a name="method75"></a>
<p/><strong>void Particle::bst(const Vec4& pBst) &nbsp;</strong> <br/>
boost four-momentum and production vertex by 
<i>beta = (px/e, py/e, pz/e)</i>. 
   
 
<a name="method76"></a>
<p/><strong>void Particle::bst(const Vec4& pBst, double mBst) &nbsp;</strong> <br/>
as above, but also use <i>gamma> = e/m</i> to reduce roundoff errors. 
   
 
<a name="method77"></a>
<p/><strong>void Particle::bstback(const Vec4& pBst) &nbsp;</strong> <br/>
   
<strong>void Particle::bstback(const Vec4& pBst, double mBst) &nbsp;</strong> <br/>
as above, but with sign of boost flipped. 
   
 
<a name="method78"></a>
<p/><strong>void Particle::rotbst(const RotBstMatrix& M) &nbsp;</strong> <br/>
combined rotation and boost of the four-momentum and production vertex. 
   
 
<a name="method79"></a>
<p/><strong>void Particle::offsetHistory( int minMother, int addMother, int minDaughter, int addDaughter)) &nbsp;</strong> <br/>
add a positive offset to the mother and daughter indices, i.e. 
if <code>mother1</code> is above <code>minMother</code> then 
<code>addMother</code> is added to it, same with <code>mother2</code>, 
if <code>daughter1</code> is above <code>minDaughter</code> then 
<code>addDaughter</code> is added to it, same with <code>daughter2</code>. 
   
 
<a name="method80"></a>
<p/><strong>void Particle::offsetCol( int addCol) &nbsp;</strong> <br/>
add a positive offset to colour indices, i.e. if <code>col</code> is 
positive then <code>addCol</code> is added to it, same with <code>acol</code>. 
   
 
<h3>Constructors and operators</h3> 
 
Normally a user would not need to create new particles. However, if 
necessary, the following constructors and methods may be of interest. 
 
<a name="method81"></a>
<p/><strong>Particle::Particle() &nbsp;</strong> <br/>
constructs an empty particle, i.e. where all properties have been set 0 
or equivalent. 
   
 
<a name="method82"></a>
<p/><strong>Particle::Particle(int id, int status = 0, int mother1 = 0, int mother2 = 0, int daughter1 = 0, int daughter2 = 0, int col = 0, int acol = 0, double px = 0., double py = 0., double pz = 0., double e = 0., double m = 0., double scale = 0., double pol = 9.) &nbsp;</strong> <br/>
constructs a particle with the input properties provided, and non-provided 
ones set 0 (9 for <code>pol</code>). 
   
 
<a name="method83"></a>
<p/><strong>Particle::Particle(int id, int status, int mother1, int mother2, int daughter1, int daughter2, int col, int acol, Vec4 p, double m = 0., double scale = 0., double pol = 9.) &nbsp;</strong> <br/>
constructs a particle with the input properties provided, and non-provided 
ones set 0 (9 for <code>pol</code>). 
   
 
<a name="method84"></a>
<p/><strong>Particle::Particle(const Particle& pt) &nbsp;</strong> <br/>
constructs an particle that is a copy of the input one. 
   
 
<a name="method85"></a>
<p/><strong>Particle& Particle::operator=(const Particle& pt) &nbsp;</strong> <br/>
copies the input particle. 
   
 
<a name="method86"></a>
<p/><strong>void Particle::setEvtPtr(Event* evtPtr) &nbsp;</strong> <br/>
sets the pointer to the <code>Event</code> object the particle 
belongs to. This method is automatically called when a particle 
is appended to an event record. Also calls <code>setPDEPtr</code> below. 
   
 
<a name="method87"></a>
<p/><strong>void Particle::setPDEPtr(ParticleDataEntry* pdePtr = 0) &nbsp;</strong> <br/>
sets the pointer to the <code>ParticleDataEntry</code> object of the 
particle, based on its current <code>id</code> code. If the particle 
belongs to an event there is no need to provide the input argument. 
As explained above, a valid <code>ParticleDataEntry</code> pointer 
is needed for the methods that provide information generic to the 
particle species. 
   
 
</body>
</html>
 
<!-- Copyright (C) 2014 Torbjorn Sjostrand --> 
 
