<html>
<head>
<title>Random Numbers</title>
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

<form method='post' action='RandomNumbers.php'>
    
<h2>Random Numbers</h2>

This page describes the random-number generator in PYTHIA and 
how it can be replaced by an external one.
 
<h3>Internal random numbers</h3>

The <code>Rndm</code> class generates random numbers, using the 
Marsaglia-Zaman-Tsang algorithm [<a href="Bibliography.php" target="page">Mar90</a>]. 

<p/>
Random numbers <code>R</code> uniformly distributed in 
<code>0 &lt; R &lt; 1</code> are obtained with
<pre>
   Rndm::flat();
</pre>
There are also methods to generate according to an exponential, to 
<i>x * exp(-x)</i>, to a Gaussian, or picked among a set of 
possibilites, which make use of <code>flat()</code>.

<p/>
If the random number generator is not initialized before, it will be
so the first time it is asked to generate a random number, and then
with the default seed, 19780503. This means that, by default, all runs
will use identically the same random number sequence. This is 
convenient for debugging purposes, but dangerous if you intend to
run several "identical" jobs to boost statistics. You can initialize, 
or reinitialize, with your own choice of seed with a 
<pre>
   Rndm::init(seed);
</pre>
Here values <code>0 &lt; seed &lt; 900 000 000</code> gives so many 
different random number sequences, while <code>seed = 0</code> will call 
the <code>Stdlib time(0)</code> function to provide a "random" 
<code>seed</code>, and <code>seed &lt; 0</code> will revert back to 
the default <code>seed</code>.

<p/>
The <code>Pythia</code> class defines <?php $filepath = $_GET["filepath"];
echo "<a href='RandomNumberSeed.php?filepath=".$filepath."' target='page'>";?>a 
flag and a mode</a>, that allows the <code>seed</code> to be set in 
the <code>Pythia::init</code> call. That would be the standard way for a 
user to pick the random number sequence in a run.

<h3>External random numbers</h3>

<code>RndmEngine</code> is a base class for the external handling of 
random-number generation. The user-written derived class is called 
if a pointer to it has been handed in with the 
<code>pythia.rndmEnginePtr()</code> method. Since the default 
Marsaglia-Zaman-Tsang algorithm is quite good, chances are that any 
replacement would be a step down, but this may still be required by 
consistency with other program elements in big experimental frameworks.

<p/>
There is only one pure virtual method in <code>RndmEngine</code>, to 
generate one random number flat in the range between 0 and 1: 
<pre>
  virtual double flat() = 0;
</pre>
Note that methods for initialization are not provided in the base 
class, in part since input parameters may be specific to the generator
used, in part since initialization can as well be taken care of 
externally to the <code>Pythia</code> code.

<p/>
An example illustrating how to run with an external random number
generator is provided in <code>main23.cc</code>.

<h3>The methods</h3>

We here collect a more complete and formal overview of the methods.
   
<a name="method1"></a>
<p/><strong>Rndm::Rndm() &nbsp;</strong> <br/>
construct a random number generator, but does not initialize it.
  
   
<a name="method2"></a>
<p/><strong>Rndm::Rndm(int seed) &nbsp;</strong> <br/>
construct a random number generator, and initialize it for the 
given seed number.
  
   
<a name="method3"></a>
<p/><strong>bool Rndm::rndmEnginePtr( RndmEngine* rndmPtr) &nbsp;</strong> <br/>
pass in pointer for external random number generation.
  
   
<a name="method4"></a>
<p/><strong>void Rndm::init(int seed = 0) &nbsp;</strong> <br/>
initialize, or reinitialize, the random number generator for the given 
seed number. Not necessary if the seed was already set in the constructor. 
  
   
<a name="method5"></a>
<p/><strong>double Rndm::flat() &nbsp;</strong> <br/>
generate next random number uniformly between 0 and 1.
  
   
<a name="method6"></a>
<p/><strong>double Rndm::exp() &nbsp;</strong> <br/>
generate random numbers according to <i>exp(-x)</i>.
  
   
<a name="method7"></a>
<p/><strong>double Rndm::xexp() &nbsp;</strong> <br/>
generate random numbers according to <i>x exp(-x)</i>.
  
   
<a name="method8"></a>
<p/><strong>double Rndm::gauss() &nbsp;</strong> <br/>
generate random numbers according to <i>exp(-x^2/2)</i>.
  
   
<a name="method9"></a>
<p/><strong>pair&lt;double, double&gt; Rndm::gauss2() &nbsp;</strong> <br/>
generate a pair of random numbers according to 
<i>exp( -(x^2 + y^2) / 2)</i>. Is faster than two calls
to <code>gauss()</code>.
  
   
<a name="method10"></a>
<p/><strong>int Rndm::pick(const vector<double>& prob) &nbsp;</strong> <br/>
pick one option among vector of (positive) probabilities.
  
   
<a name="method11"></a>
<p/><strong>bool Rndm::dumpState(string fileName) &nbsp;</strong> <br/>
save the current state of the random number generator to a binary
file. This involves two integers and 100 double-precision numbers.
Intended for debug purposes. Note that binary files may be
platform-dependent and thus not transportable.
  
   
<a name="method12"></a>
<p/><strong>bool Rndm::readState(string fileName) &nbsp;</strong> <br/>
set the state of the random number generator by reading in a binary
file saved by the above command. Comments as above.
  
   
<a name="method13"></a>
<p/><strong>virtual double RndmEngine::flat() &nbsp;</strong> <br/>
if you want to construct an external random number generator 
(or generator interface) then you must implement this method 
in your class derived from the <code>RndmEningen</code> base class,
to give a random number between 0 and 1.
  

</body>
</html>

<!-- Copyright (C) 2012 Torbjorn Sjostrand -->
