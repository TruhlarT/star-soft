<?php

@(include "refSetup.php") or die("Problems (0).");

$topic = 0;
getPassedInt("topic",1);

headR("QA Reference Histograms Help");

body();

function mkHelpRef($topic,$txt,$li=0) {
  if ($li) { print "<li>"; }
  mkhref("refHelp.php?topic=${topic}",$txt,"");
  if ($li) { print "</li>\n"; }
}

?>
<p align=right><font size=-1>
<a href="javascript:window.close()">Close Window</a>
</font></p>
<h3>QA Reference Histograms Help</h3>
<?php
if ($topic > 0) { mkHelpRef(0,"(full topic list)"); }
  
switch ($topic) {

#####################################
case (1) : # Selections
?>
<h4>Selecting a Reference Histogram Set</h4>
<dl>

<dt>General</dt>
<dd>If you are not interested in a reference histogram analysis,
just click on the "Plots Only" button and plots will be generated
without performing an analysis. Otherwise...<br>

Different sets of reference histograms can be used for the purposes of
histogram comparisons. These are categorized by the Run Year (e.g. data taken
during the calendar year 2011 is from Run Year 11), trigger setup (whose
name usually indicates a collision setup as well, e.g. "AuAu200_production"),
and a version number for updates that occur to a reference set.
The entry date is placed in parentheses beside the version number
to help identify how recent each version is.<br>

Note that the option to analyze the data will not appear until a
version has been selected. On some browsers, the buttons appear
automatically, while on other browsers, the arrows must be clicked.</dd>

<dt>Triggers</dt>
<dd>It can be confusing, but <i>trigger setups</i> are different from <i>trigger types</i>
Trigger types are categories of individual event triggers, such as minimum bias and
high tower triggers. In Offline QA, we can choose to show plots for all trigger types
within any given file integrated, or we can separate plots for the differen trigger
types. Note that a single event may even satisfy multiple trigger types, and may thus
be added to the statistics for multiple trigger type groups. On the other hand,
trigger setups are groupings of multiple triggers meant to satisfy particular goals
for any individual run. These often have names like <i>production20xx</i> and
differentiate between different purposes for acquiring any given run.</dd>

<dt>Selected runs and files</dt>
<dd>Clicking on this will simply expose a list of the run(s) (linked to any
RunLog and Electronic Shift Log entries [from the current year]
via "RL" and "ESL" respectively)
and data files which will be used in the analysis. Clicking again will hide
the list.</dd>

<dt>Plotting options</dt>
<dd>Clicking on this will expose a couple menus allowing a choice of
full output format (e.g. PDF or PostScript)
if the users wants to view all
the histograms collected into multi-page files (see the help for
<?php mkHelpRef(3,"List of Output"); ?>), and allowing a
choice of which histograms to plot
(the QA Shift generally views the "QA Shift" histograms, while experts
may select a different option). Choosing "none" for the full output format
skips generating the full output and makes the processing notably faster.</dd>

<dt>How to proceed</dt>
<dd>If selecting a reference, the Run Year and Trigger Setup of the data
being examined will be shown in <font color="red">red</font> next to
the selection menus, and an appropriate reference will be <i>guessed</i>
from these. If the system is unable to determine these things or make a
good guess, you will need to manually select what you believe is the best
choice for a reference.<br>

Once a reference set has been chosen, you will be offered a choice of
seeing all the details of the reference set (via the "Show Set Info" button),
and proceeding with the analysis via the "Analyze" button. The analysis will
generate graphics plot files (which will be listed at the top right of the page),
and will also generate analysis output of quantitative comparisons between the
data histograms and the reference histograms. You can find additional help when
you reach those steps of the procedure.</dd>

<dt>Go back to QA selections</dt>
<dd>Because not all web browsers handle using their "back" buttons in the same
manner, it is recommended not to use that feature of your web browser here.
Instead, please select one of the "Go back" options (in the Controls Panel,
which pops up when either hovering over "Controls..." or clicking on it)
when ready to return to the selection of
data for QA. Usually these buttons are unnecessary as the option will also be
provided via a pop-up dialog when the files are marked as examined.</dd>

</dl>
<?php
break;

  #####################################
case (3) : # Output plots
  ?>
<h4>List of Output</h4>
<dl>

<dt>General</dt>
<dd>Provided here (in the Output Panel, which pops up when
either hovering over "Output..." or clicking on it)
are links to the full graphics output plot files and logs generated
from the data processing. It is expected that users will generally
view the individual plots by using the "Examine" buttons available
in the Analysis Results section, but the option to view the full
files is available anyhow.<dd>

<dt>Links</dt>
<dd>There may be several links provided if Offline QA is separating
by trigger types.
Additionally, if reference plots are available, links will also be provided,
as denoted by the text "Ref" in parentheses. Links will be shown for
the stdout and stderr of plot generation (if the files exist), and for
the filelist and output of the histogram combining process if they exist.</dd>

<dt>How to proceed</dt>
<dd>Generally, users will not access these links. If you choose to do so, the
links open into separate windows by default. If you are having problems
such that files open in the small frame of the window where the links are,
you may wish to either open these links in a different web browser tab or
window, or even download the files to your own computer manually. These
options are usually available from a menu which appears by "right-clicking"
or "control-clicking" on any of
the links. Please try to avoid using the "back" button of your web browser,
which can cause the need to re-do certain steps. If you get stuck,
consider re-clicking the "Analyze" button to try again.</dd>

</dl>
<?php
break;
  
#####################################
case (11) : # Analysis
?>
<h4>Analysis Results</h4>
<dl>

<dt>General</dt>
<dd>This frame shows a summary of the reference historam analysis results.
By default, all histograms are listed. Clicking on the "All + Plots" button
on the left will show all of the histogram images too. In the future, the
default will be to show only histograms which fail their analyses.
Failed analyses will be highlighted in red, while passed analyses will be highlighted
in green. If a result is within the lower 10% of its passing range (e.g. between
0.80 and 0.82 if the cut is 0.80), then it will be highlighted in yellow to
indicate it as questionable. Histograms without a defined analysis will be
highlighted in grey. In principle, only the histograms failing their analyses need
to be reported for the QA Shift.<br>
Note that when only viewing plots from a data or reference without analyzing,
all histograms will
be listed, and there will only be "All" and "All + Plots" button on the left.<dd>

<dt>Trigger type sections</dt>
<dd>Histograms may or may not be separated into trigger type groups (the
default group is simply <i>General Histograms</i>). The number of events
in each group with found vertices is shown, as well as the total number
of events in that group. Clicking on the trigger type heading will collapse
and expand the histogram list for each group, and if the total number of events
is below 100, the list will be collapsed by default.<br>
For users on QA Shift, the "New report entry" simplifies transfering basic
information about a run (and trigger type) into an open QA Shift Report.</dd>

<dt>Names, titles, and descriptions</dt>
<dd>Histogram names are generally in a shorthand notation which is not
always easily interpreted. To help with this,
double-clicking on the name of a histogram will reveal
its title (which appears in the upper left of each histogram plot),
and clicking on "<font size=-1>(more)</font>" will bring up a longer description.
Double-clicking again will hide these details.</dd>

<dt>How to proceed</dt>
<dd>If "All + Plots" was used, then the plots are shown and you can
scroll down through the plots, examining them. Note that these are
low resolution images, but clicking on any of them will lead to a
high resolution, vector graphics version of the image. Most browsers
will pop up a new window for SVG graphics file and allow zooming via
control+ and control- (command+/- on Macs), enabling a closer look
at details in the plot.<br>
You may select the "Examine" button next to the summary for any individual
histogram to see the details of the analysis, and view the individual plots
(it may take a few seconds for the page to advance and the plot to appear
on the screen - please have patience as the retrieval takes a moment).
Alternatively, navigation to individual histograms can be made using the
graphical menu on the left. Note that if a multi-page output format was
chosen, then the navigation includes locations of plots (pages and cells)
within the full graphics files where one can find each histogram.</dd>

<dt>When finished...</dt>
<dd>Mark the data as examined by selecting either the "Good" or "Bad" buttons
on the left. In addition to marking the run status,
this will also record the results of the
analysis into a database for trend plotting.</dd>

</dl>
<?php
break;

#####################################
case (12) : # Cuts
?>
<h4>Examining (&amp; Editing) Analyses &amp; Cuts</h4>
<dl>

<dt>General</dt>
<dd>This section should show the
all the details regarding the cuts used as well as the individual plots
(both data and reference) themselves.
The cuts define a quantitative means by which to determine whether
two histograms are sufficiently similar.
All the information regarding cuts, the stored reference histogram,
and the descriptions of the histograms can be edited/updated by selecting
the "Edit (experts only!)" button near the bottom of the panel. Please
do not update anything unless you are a subsystem or QA expert.
A ref dashed border on the panel will clearly indicate when the user is
in the editing mode intended for experts.</dd>

<dt>How to proceed</dt>
<dd>One can return to the list of analysis results by selecting either
the "Failed" or "All" or "All + Plots" buttons on the far left. One can also select the
"Prev" or "Next" buttons on the left to navigate forward or backward through
the histogram list. Or one can
use the graphical
navigation menu to examine other individual plots if their location in
the full graphics files is known
(note that the location of the plot which is being examined is shown and can
 be useful in orientation for further navigation).
Please be patient as it sometimes takes a couple seconds for plots to
appear on-screen. Help for experts follows here, but there are
<?php mkhref2("http://drupal.star.bnl.gov/STAR/comp/qa/offline/currentqadocs/configuring-autoqa-subsystems",
              "more detailed instructions","new"); ?> elsewhere.</dd>

<dt>Defaults</dt>
<dd>When no cut exists, defaults are used in the analysis. The default mode
is Kolmogorov Maximum Distance with no options. The default cut value is 0.</dd>

<dt>Updating and choosing a cut value</dt>
<dd>A value of 0 is equivalent to no cut (i.e. all analyses pass). And cuts
for specific trigger types (i.e. which are not 'General') will take precedence
over any 'General' cut for any specific histogram. Thus, setting a cut value
to 0 is <i>not exactly the same</i> as deleting a cut, as a 0 value for a
specific trigger type cut will still take precedence over a 'General' cut.<br>

It is also important to understand
that changing anything about an analysis (e.g. the cut value) will
<b>not take immediate effect</b>, but will be used
the next time an analysis is run! You will not even see the changes just
committed when editing the analysis again until re-running. The page
only shows what was run for the current analysis. That being said,
please do not be afraid to simply re-select the "Analyze" button near
the top of the window to re-run the analysis.</dd>

<dt>Updating reference histograms</dt>
<dd>After marking histograms for updating the reference (from the current data),
an additional button will appear next to the "Failed" and "All" buttons
for viewing the list of reference histograms to update. Clicking on that button
will allow selection of the datasets for which the new reference will apply,
which should only be done when the full list of histograms to update has been
completed (i.e. updating one histogram at a time will create numerous and unuseful
versions of the reference set). An option will also be given at that stage to
use the full set of data histograms for a new reference instead of updating
individual histograms.</dd>

</dl>
<?php
  break;
  
#####################################
case (13) : # Trends
  ?>
<h4>Trend Plotting</h4>
<dl>

<dt>General</dt>
<dd>These plots show the results of the reference analyses plotted against
other quantities, such as time. The goal is to elucidate possible correlations
which may help understand issues and identify their causes.
Blue points and lines represent the analysis results, and ref lines denote
the cut values used when each recorded analysis was made. Note that results
are only available for these plots if the analyses are recorded, which occurs
when the user marks the data as examined.<br>
Blue markers represent analysis results, connected by blue lines. Red lines
denote the cut values used for each analysis, and green ticks at the top
and bottom indicate when the reference set used for the analysis was changed
(though the individual reference histogram used for <i>this</i> particular
histogram may have been preserved accross multiple reference sets).
</dd>

</dl>
<?php
  break;
  
#####################################
case (20) : # Images
  ?>
<h4>Attaching a Histogram Image to an Issue</h4>
<dl>

<dt>Make sure the issue exists</dt>
<dd>You can only attach images to existing issues.
Using the <?php mkhref("issueEditor.php","Issue Editor","QAifr"); ?>
to create and save an issue describing the problem <u>before</u>
trying to attach an image!
</dd>

<dt>The easy way: automatically through the QA browser</dt>
<dd>When viewing histograms in the QA browser, an "Attach to Issue" button
appears above each histogram image. Clicking this button will prompt
for the ID number of an issue to which you would like the image attached.
The selected issue will be loaded in the
<?php mkhref("issueEditor.php","Issue Editor","QAifr"); ?> (unless it
does not exist) with the same image now attached. Note that this is
the low resolution image, not the high resolution vector graphics image.
</dd>

<dt>The only-slightly-harder way: saving an image and uploading it</dt>
<dd>
<dl>
<dt>Obtaining an Image</dt>
<dd>Use the QA browser as you normally would to generate and view plots.
If you view plots in the QA browser, it is a simple matter to save these
plots to your own computer by either of the following methods:
<ol>
<li>Save the image directly from your web browser, often achieved by
"right-clicking" or "control-clicking" over the image and selecting
something like "Save Image As..." from a contextual menu.</li>
<li>Use a screen capture tool to select the portion of your screen
which contains the image.</li>
</ol>
You may have other means at your disposal, and it may be worthwile
to crop an image once it is on your computer to what you feel is the
relevant portion of the image for the issue.
</dd>

<dt>Attaching the Image</dt>
<dd>With the <?php mkhref("issueEditor.php","Issue Editor","QAifr"); ?>
open to the Issue to which you want to attach the image, scroll down to
the "Image Attachments" section and, if necessary, click on the arrow
such that it is pointing downwards and the section for Image Attachments is
displayed. Click on the "Choose File" button in this section, and navigate
to and select the desired image you just saved on your computer. After selecting
the file, click the "Upload File" button in the Image Attachments section.
The image should now be available in the Issue, and the direct link for the
Issue (shown near the top of the Issue Editor window) can be sent to anyone
to whom you wish to see the Issue.
</dd>
</dl>
</dd>

</dl>
<?php
  break;
  
  #####################################
case (21) : # Vertex Count
  ?>
<h4>Determining the number of events and found vertices</h4>
<dl>

<dt>Finding the correct plot</dt>
<dd>After using the QA Browser to generate plots or analyze a given
dataset, the list of plots should include some histograms labeled
<i>*QaNullPrimVtxMult</i>. If these do not show up among the Failed histograms,
please look under the full set by clicking on the "All" button.
There should be one general version of this histogram, and one for each
trigger group in the dataset (e.g. MinBias, Central, etc.). Click on
the "Examine" button next to each of these histograms to view them.
</dd>

<dt>Finding the numbers</dt>
<dd>The shown plot for "Data" should indicate the total number of events
in red text (written sideways on the left), and the found vertices just
to the right of that in green text. Please enter
these in your QA Shift Report at the appropriate place for each
<i>Data Entry</i> you make. The more detailed breakdown in blue text
is not needed for this purpose.
</dd>

</dl>
<?php
  break;
  
#####################################

default : # Topic list

  print "<h4>Available Topics</h4>\n<ul>\n";
  mkHelpRef( 1,"Selecting a Reference Histogram Set",1);
  mkHelpRef( 3,"List of Output",1);
  mkHelpRef(11,"Analysis Results",1);
  mkHelpRef(12,"Examining (&amp; Editing) Analyses &amp; Cuts",1);
  mkHelpRef(13,"Trend Plotting",1);
  mkHelpRef(20,"Attaching a Histogram Image to an Issue",1);
  mkHelpRef(21,"Determining the number of events and found vertices",1);
  print "</ul>\n";

  mkhref2("http://drupal.star.bnl.gov/STAR/comp/qa/offline/currentqadocs/star-qa-documentation",
          "Offline QA Documentation","new");
  linebreak();
  mkhref2("http://drupal.star.bnl.gov/STAR/comp/qa/offline/currentqadocs/configuring-autoqa-subsystems",
          "Configuring AutoQA for Subsystems","new");
  linebreak();
  mkhref2("mailto:gene@bnl.gov","Ask questions about the QA Reference Histograms system...","");
  break;

}

foot(); ?>
