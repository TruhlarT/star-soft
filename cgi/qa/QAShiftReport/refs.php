<?php
  
  @(include "refSetup.php") or die("Problems (0).");

  $basicTitle = "STAR Offline QA Browser";
  headR2($basicTitle);
  ?>

<style type="text/css">
<!--
a.items:link {color: navy; text-decoration: none; }
a.items:visited {color: navy; text-decoration: none; }
a.items:active {color: tomato; text-decoration: none; }
a.items:hover {color: maroon; text-decoration: none; }

.errDiv {position:absolute; bottom:1px; right: 1px; z-index:1021; border: solid 3px red; display: none; background-color: cornsilk; }
.refHelpButton {position:absolute; top:3px; right: 5px; z-index:1020; }
.refDiv {position:relative; width: 99%; background-color: inherit; }
.refNavig {position: absolute; left: 0px; width: 170px; z-index: 100; }
.refContent {position: absolute; top: 0px; left: 180px; right: 0px; }
.refPop {margin:0; padding: 5px; }
.refPopNavig {margin: 5px; z-index: 110; border-radius: 6px 0px 0px 6px; border: solid 0px black; }
.refPopOutline {border-radius: 0px 6px 6px 6px; z-index: 112; background-color: cornsilk; display: none; border: solid 2px black; border-top-width: 0px; border-left-width: 0px; }
.refPopContent {position:relative; border-radius: 0px 6px 6px 6px; z-index: 113; background-color: inherit; border: solid 5px <?php print $myCols["emph"]; ?> }
.refExpert {border: 2px dashed red; }
.refViewerInner {position: absolute; top: 0px; bottom: 0px; left: 0px; right: 0px; overflow: auto; }
.refStatusDiv {position: absolute; margin-top: 225px; }

#controlLabel {top: 30px; }
#outputLabel {top: 65px; }
#refMenu {top: 110px; bottom: 0px; overflow: auto; }
#refViewer {top: 0px; bottom: 0px; }
#mainDiv {position: absolute; z-index: 1; height: 98%; }
#controlDiv {position:relative; z-index: 98; }
#outputDiv {position: relative; z-index: 98; }
#menuDiv {position: absolute; z-index: 98; }
#noDiv {position:relative; display: none; z-index: 0; }

-->
</style>

<?php

  jqry();
  jstart();
  print "  var query_str = '" . $_SERVER['QUERY_STRING'] . "';\n";
?>
  var navig_click = 0;
  var inform = ' Please contact G. Van Buren.';
  if (typeof jQuery == 'undefined') {
    alert('Error loading scripts!' + inform);
  }
  var page_entry = true;
  var err_handle;
  function clear_div(clear_target) {
    div_handle = "#" + clear_target + "Div";
    $(div_handle).html("");
  }
  function post_div(post_url,post_data,post_target) {
    // post a URL to a div
    err_handle.hide();
    clear_div("err");
    div_handle = "#" + post_target + "Div";
    timout = 1360000;
    $.ajax({
      type: 'POST',
      async: (post_url == 'refAnalyze.php'),
      cache: false,
      url: post_url,
      data: post_data,
      dataType: 'html',
      timeout: timout,
      success: function(data) {
        $(div_handle).empty().html(data);
      },
      error: function(tmp, errStatus, errText) {
        txt  = 'ERROR(' + errStatus + '): ' + errText + '<br>';
        txt += 'URL: ' + post_url + '<br>';
        txt += 'TARGET: ' + post_target + '<br>';
        txt += 'TIMEOUT: ' + timout + '<br>';
        txt += inform;
        err_handle.html(txt);
        err_handle.show();
      }
    });
  }
  function post_form() {
    // assign some form field values, then post it to a div
    // usage: post_form(form,field1,value1,field2,value2,...) {
    form = arguments[0];
    frm = document.forms[form];
    if (typeof frm == 'undefined') {
      alert('Error with forms!' + inform);
      return;
    }
    for (var i = 1; (i < arguments.length) && (typeof arguments[i] == 'string'); i+=2) {
      frm.elements[arguments[i]].value = arguments[i+1];
    }
    fhandle = "#" + form;
    post_div($(fhandle).attr("action"),
             $(fhandle).serialize(),
             $(fhandle).attr("target"));
  }
   
  function submit_form() {
    // assign some form field values, then submit it
    // usage: submit_form(form,field1,value1,field2,value2,...) {
    form = arguments[0];
    frm = document.forms[form];
    if (typeof frm == 'undefined') {
      alert('Error with forms!' + inform);
      return;
    }
    for (var i = 1; (i < arguments.length) && (typeof arguments[i] == 'string'); i+=2) {
      frm.elements[arguments[i]].value = arguments[i+1];
    }
    frm.submit();
  }
   

  function hidePops() {
    $('.refDivPop').each( function(i) {
      hidePopContent(this);
    });
  }

  function showPopContent(elem) {
    var navig = $('.refPopNavig',elem);
    var content = $('.refPopOutline',elem);
    var othertop = navig.position().top + 5;
    content.css({ top:othertop });
    navig.css({ 'background-color': '<?php print $myCols["emph"]; ?>', 'z-index': 111, 'border-bottom-width': '2px' });
    content.slideDown(250);
  }

  function hidePopContent(elem) {
    var navig = $('.refPopNavig',elem);
    var content = $('.refPopOutline',elem);
    navig.css({ 'background-color': 'transparent', 'z-index': 110, 'border-bottom-width': '0px' });
    content.hide();
  }

  function assignClicks() {
    $('.refPopNavig').unbind("click");
    $('.refPopNavig').click(
      function() {
        if (page_entry) return;
        if (navig_click == this.id) {
          navig_click = 0;
          hidePopContent($(this).parent()[0]);
        } else {
          navig_click = this.id;
          // hide others first
          hidePops();
          showPopContent($(this).parent()[0]);
        }
      }
    );
  }

  $().ready(function() {
    err_handle = $("#errDiv");
    post_div('refControl.php',query_str,'control');

    $('.refDivPop').hover(
      function() {
        if (! page_entry && navig_click == 0) showPopContent(this);
      },
      function() {
        if (! page_entry && navig_click == 0) hidePopContent(this)
      }
    );

    assignClicks();

    $('.dimHover').hover(
      function() { $(this).fadeTo('fast',1.0); },
      function() { $(this).fadeTo('slow',0.4); }
    );

    showPopContent($('#controlDiv'));

  });

<?php
  print "    function setQATitle(str) { document.title = \"${basicTitle}: \" + str; }\n";
  jsToggleSection();
  jend();
  
  body();
  print "<div id=\"noDiv\"></div>\n";
  print "<div id=\"menuDiv\"><b>Menu</b></div>\n";
  print "<div id=\"controlDiv\" class=\"refDiv refDivPop\"></div>\n";
  #print "<div id=\"outputDiv\" class=\"refDiv refDivPop\"><div class=\"refPopNavig\"></div></div>\n";
  print "<div id=\"outputDiv\" class=\"refDiv refDivPop\"></div>\n";
  print "<div id=\"mainDiv\" class=\"refDiv\"></div>\n";
  print "<div id=\"errDiv\" class=\"errDiv\"></div>\n";

  foot(0,0); ?>
