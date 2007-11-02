<?php

@(include "setup.php") or die("Problems (0).");

head("STAR QA Shift Report Header");
body();
?>


<!-- Header material -->
<table border=0 cellpadding=5 cellspacing=0 width="100%">
        <tr bgcolor="#ffdc9f">
        <td align=left> <font size="-1">
        <a href="/">STAR</a>
        &nbsp; <a href="/STAR/comp/">Computing</a> 
        </font>
        </td>
        <td align=right> <font size="-1">
        &nbsp;  <!-- top right corner  --> </font></td>
        </tr>
        <tr bgcolor="#ffdc9f"><td align=center colspan=2><font size="+2"> <b>
        STAR QA Shift Report
        </b></font></td></tr>
        <tr bgcolor="#ffdc9f">
        <td><font size=-1><a href="/STAR/comp/qa/">QA</a></font></td>
        <td align="right"><a href="/STAR/html/ofl_l/prodinfo.html">
        <font size="2" face="verdana,arial,helvetica,sans-serif">Maintained</font>
        </a> 
         <font size="-1">
         by <a href="mailto:gene@bnl.gov">G. Van Buren</a>
         </font> </td> 
        </tr>

        <tr>
        <td align=left><b>Instructions</b></td>
        <td align=right><font size=-1><a href="instruct.php" target="QAinstruct">
        (Open In Separate Window)
        </a></font></td>
        </tr>

</table>

<ul>
<li>If you know that <b>the experiment is taking data, but no fast offline
    data is appearing</b> in the QA Browser, please make an effort
    to understand why there is no data (look at the
    <a href="http://www.star.bnl.gov/HyperNews-star/get/starprod.html?maxm=100">
    production hypernews</a>, for example) and post this issue to the
    <a href="http://online.star.bnl.gov/apps/shiftLog2005/">Electronic
    Shift Log</a> (under the <b>QA</b> subdetector)
    if it has not already been posted. Please also remember to close
    any such opened issues if the problem is resolved.
<li>The report is best filled out <b>DURING</b> your shift, not after.
    This is simply because it is easiest to fill out the form while
    looking at the data.
<li>The plan is: one report per shift, many data entries per report.
<li>You should never select the <u>Back</u> button of your
    web browser during the report process (and you should never need to do so).
<li>Do not be afraid to try things out. Until you submit the full report,
    everything can be modified.
<li>If you are experiencing problems, try clearing your browser's cache
    and reloading this page. Additionally, be sure that cookies
    and javascript are enabled in your browser. If problems persist,
    please contact Gene Van Buren at
    <a href="mailto:gene@bnl.gov"><i>gene@bnl.gov</i></a> or (631-344-7953).
</ul>

<dl>
<dt><b>Choose a session name</b>
<dd>You can also continue a session
    which was started earlier. This name has no meaning other than to
    identify one QA Shift Report from another in case more than one
    person is working on a report simultaneously, and to allow one to
    restore a report that they have already started if their browser
    or computer crashes. Your chosen session name should appear
    next to <u>Session</u> in the <b>Menu</b>.
    You can also make a copy of another session.
<dd>If you do not see a session name in the <b>Menu</b>, or the name Unknown
    appears, please try selecting a session again. Problems will arise otherwise.
<dt><b>Fill out the Shift Info form</b>.
<dd>Select the <u>Save/Continue</u> button at the bottom of the form
    when finished. If you are unsure about an item, it can be edited later.
<dt><b>Add data entries</b>
<dd>Do so for each QA job (histogram set) examined by making the
    appropriate selection from the <u>Add A Data Entry For...</u> submenu.
    Again, select <u>Save/Continue</u> when finished with each data entry.
    And again, these items can be edited later if necessary.
<dt><b>Focus on issues</b>
<dd>Issues are maintained with the Issue Browser/Editor, which can be
    reached via <u>Open Issue Browser/Editor</u> in the
    <b>Menu</b>, or from the data entry forms (where only issues
    for that data type are listed). Issues can then
    be made <i>active</i> for a given data entry to indicate that the
    issue was seen there. The intent here is that opened/created issues may be
    used repeatedly and can be modified or appended later (if
    more detail is learned, for example) until they are eventually
    closed/resolved. A name serves as a brief
    description of each issue, and a detailed description is available
    via the Browser/Editor. To be listed in the data entry form of
    a given data type, an issue must be <i>allowed</i> for that type.
<dd>You may need to <u>Refresh Issues</u> when working on an entry for
    any newly created issues to appear.
<dt><b>Maintain the contents</b>
<dd>After entering each portion of the report, a current contents
    listing is shown. Each portion may be <b>viewed</b>
    (by clicking on the item), <b>deleted</b> (by marking the checkbox
    beside the item and clicking on the <u>Delete</u> button),
     <b>edited</b>, or <b>copied</b>.
<dt><b>Submit the QA Shift Report</b>
<dd>When ready to submit,
    select <u>Finish &amp; Submit</u>.
    This takes you to the final information to
    be entered for the report. You can save this information and
    submit later if you decide you are not yet ready to submit the
    full report. You can also choose not to delete the session after
    submitting, so that it can be reused and modified another time.
</dl>
At any time, you may (using the <b>Menu</b>):
<ul>
<li>Browse or edit issues by selecting
    <u>Open Issue Browser/Editor</u> in the <b>Menu</b>.
<li>View the currently entered portions of the report by
    selecting <u>View Current Contents</u>.<br>
    You may subsequently edit these files or copy their contents
    into a new data report<!--, or even to a different session-->.
<li>Re-enter the Shift Info by
    selecting <u>Re-Enter Shift Info</u>.
<li>Erase the entire report and start over by
    selecting <u>Erase Sesson &amp; Start Over</u>.
<li>Stop the current session and choose to start a new one, or continue
    a different one, by selecting <u>Session</u>.
</ul>


<?php foot(); ?>
