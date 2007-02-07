<?php

###########################
# Form for entering shift info
#

include "setup.php";
incl("loadSession.php");

getPassedVarStrict("work");

if (!defd($work)) {
  header("location: ${webdir}sessions.php");
  exit;
}

getPassedVarStrict("mode");

#Set the session
loadSes($work);

#Check where to route the user:
# possibilities include
# a) new session (mode = Edit)            => info
# b) new copied session (mode=CopyX)      => contents
# c) old session (mode=View)              => contents
# d) from menu to edit (mode = Edit)      => info
# e) from info with error (mode = ErrorX) => info

if (substr($mode,0,1) != "E") {
  header("location: ${webdir}contents.php?mode=" . $mode);
  exit;
}



#Continue with Shift Info form
head("STAR QA Shift Report Basic Info");

body();

fstart("basicInfo","saveEntry.php");
?>

<h3>QA Shift Report Form: Shift Info</h3>

<?php
if (substr($mode,0,5) == "Error") {
  $err = substr($mode,5);
  print "<font color=\"red\">You have an invalid entry for ${err}! Please correct!</font><br>\n";
}
?>


Name:
<input name=name size=54 maxlength=60>
<br>

Affiliation:
<input name=affiliation size=54 maxlength=60>
<br>

Shift Date: 
<select name=datem>
<option value="01">01 (Jan)</option>
<option value="02">02 (Feb)</option>
<option value="03">03 (Mar)</option>
<option value="04">04 (Apr)</option>
<option value="05">05 (May)</option>
<option value="06">06 (Jun)</option>
<option value="07">07 (Jul)</option>
<option value="08">08 (Aug)</option>
<option value="09">09 (Sep)</option>
<option value="10">10 (Oct)</option>
<option value="11">11 (Nov)</option>
<option value="12">12 (Dec)</option>
</select>/<select name=dated>
<option value="01">01</option>
<option value="02">02</option>
<option value="03">03</option>
<option value="04">04</option>
<option value="05">05</option>
<option value="06">06</option>
<option value="07">07</option>
<option value="08">08</option>
<option value="09">09</option>
<option value="10">10</option>
<option value="11">11</option>
<option value="12">12</option>
<option value="13">13</option>
<option value="14">14</option>
<option value="15">15</option>
<option value="16">16</option>
<option value="17">17</option>
<option value="18">18</option>
<option value="19">19</option>
<option value="20">20</option>
<option value="21">21</option>
<option value="22">22</option>
<option value="23">23</option>
<option value="24">24</option>
<option value="25">25</option>
<option value="26">26</option>
<option value="27">27</option>
<option value="28">28</option>
<option value="29">29</option>
<option value="30">30</option>
<option value="31">31</option>
</select>/<select name=datey>
<option value="04">2004</option>
<option value="05">2005</option>
<option value="06">2006</option>
<option value="07">2007</option>
<option value="08">2008</option>
<option value="09">2009</option>
<option value="10">2010</option>
<option value="11">2011</option>
<option value="12">2012</option>
</select>
(mm/dd/yy, e.g. 04/30/01, <b>NOT</b> 30/04/01)<br>

Shift Time:
Start: <input name=start size=6 maxlength=5> 
End: <input name=end size=6 maxlength=5> 
(hh:mm, e.g. 16:30)<br>
<font size=-1>
PLEASE ENTER THE START AND END TIMES OF THE SHIFT ACCORDING
TO THE TIME AT BNL (U.S. EASTERN TIME)!
(current time and date at BNL is: <b>
<?php print date("H:i m/d/y T"); ?>
</b>)
</font><br>

Shift Location:
<input name=location size=54 maxlength=60>
(e.g. BNL, Kent State Univ., Subatech)
<br>



<?php

print "<center>\n";
holine(20);
fsubmit("Save/Continue");
freset("Reset");
fhidden("type","Info");
fhidden("work",$work);
print "</center>\n";
fend();

incl("fillform.php");
fillform($shift);
reloadMenu();

foot(); ?>
