#!/usr/local/bin/perl
#
# Scan the entire star domain using nslookup.
# Output as html.
#

#
# Configuration Constants.
#
$baseDomain1 = 130;
$baseDomain2 = 199;
$startSub    = 88;
$endSub      = 89;
$startIP     = 1;
$endIP       = 255;
$workDir     = "/afs/rhic.bnl.gov/star/doc_protected/www/comp";

#
# Settings for html.
#
$darkGreen = "#27ff0a";
$lightGreen  = "#bbffb1";
$yellow     = "#f1d73d";
$grey       = "#b6b2b2";

#
# Let's rock...
#

chdir $workDir || die "Could not chdir to $workDir\n";

open (OF,">starsubnet.html.new");

print OF "<!doctype html public \"-//W3C//DTD HTML 3.2//EN\">\n";
print OF "<html>\n";
print OF "<head>\n";
print OF "   <title>Computing Facilities and Environment</title>\n";
print OF "   <meta name=\"Author\" content=\"Matthias Messer\">\n";
print OF "   <meta name=\"Description\" content=\"Auto-created for the STAR computing website.\">\n";
print OF "   <meta name=\"KeyWords\" content=\"STAR RHIC computing software\">\n";
print OF "   <meta name=\"Generator\" content=\"HomeSite 2.5\">\n";
print OF "   <meta http-equiv=\"Reply-to\" content=\"messer\@bnl.gov (Matthias Messer)\">\n";
print OF "</head>\n";
print OF "<body bgcolor=\"cornsilk\" text=\"black\" link=\"navy\" vlink=\"maroon\" alink=\"tomato\">\n";
print OF "<basefont face=\"verdana,arial,helvetica,sans-serif\">\n";
print OF "<!-- Header material -->\n";
print OF "<table border=\"0\" cellpadding=\"5\" cellspacing=\"0\" width=\"100%\">\n";
print OF "<tr bgcolor=\"#ffdc9f\">\n";
print OF "<td align=\"left\"><font size=\"-1\"><a href=\"/STAR/\">STAR</a> &nbsp; <a href=\"/STAR/comp/\">Computing</a></font></td>\n";
print OF "<td align=\"right\"><font size=\"-1\">&nbsp; <!-- top right corner  --></font></td>\n";
print OF "</tr>\n";
print OF "<tr bgcolor=\"#ffdc9f\">\n";
print OF "<td align=\"center\" colspan=\"2\"><font size=\"+2\"><b>The STAR Subnet -- Dead or Alive?</b></font></td>\n";
print OF "</tr>\n";
print OF "<tr bgcolor=\"#ffdc9f\">\n";
print OF "<td align=\"left\"><font size=\"-1\"><!-- lower left text -->&nbsp;</font></td>\n";
print OF "<td align=\"right\"><font size=\"-1\"><a href=\"/STAR/comp/ofl/prodinfo.html\">Maintenance</a> </font></td>\n";
print OF "</tr>\n";
print OF "<tr>\n";
print OF "<td colspan=\"2\" align=\"right\"><font size=\"-1\">\n";
print OF "<script language=\"JavaScript\">\n";
print OF "   <!-- Hide script from old browsers\n";
print OF "   document.write(\"Last modified \"+ document.lastModified)\n";
print OF "   // end of script -->\n";
print OF "</script>\n";
print OF "</font></td>\n";
print OF "</tr>\n";
print OF "</table>\n";
print OF "<p><!-- Content --></p>\n";
print OF "<br>\n";
print OF "<table border=\"2\" cellpadding=\"0\" cellspacing=\"2\" width=\"529\" bgcolor=\"$lightGreen\">\n";
print OF "<tr bgcolor=\"$darkGreen\">\n";
print OF "   <td><div align=\"center\"> Name          </div></td>\n";
print OF "   <td><div align=\"center\"> IP Address    </div></td>\n";
print OF "   <td><div align=\"center\"> Status (ping) </div></td>\n";
print OF "</tr>\n";

for ($i=$startSub; $i<=$endSub; $i++) {
    for ($j=$startIP; $j<=$endIP; $j++) {

	$address = "$baseDomain1.$baseDomain2.$i.$j";
	$cmd     = "nslookup -sil $address | grep \"name = \"";
	$name    = `$cmd`;
	@names   = split(/ = /,$name);
	if ($#names >= 0) {
	    $name    = substr($names[1],0,length($names[1])-1);
	    $cmd     = "ping -w1 -c1 $address | grep \"packets received\"";
	    $_       = `$cmd`;
	    if (/0 packets received/) {
		$rowColor = $yellow;
		$ping     = "dead";
	    }
	    else {
		$rowColor = $lightGreen;
		$ping     = "alive";
	    }
	}
	else {
	    $name     = "-- not assigned --";
	    $rowColor = $grey;
	    $ping     = "n/a";
	}
	print OF "<tr bgcolor=\"$rowColor\"><td>$name</td><td>$address</td><td>$ping</td></tr>\n";
    }
}

print OF "</table>\n";
print OF "<p></p>\n";

print OF "<p><!-- Footer --></p>\n";
print OF "</body>\n";
print OF "</html>\n";

close OF;

system ("rm starsubnet.html");
system ("mv starsubnet.html.new starsubnet.html");
