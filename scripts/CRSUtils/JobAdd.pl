#!/opt/star/bin/perl -w

#
# Add a run or run sequence to the .lis file.
#

print qq~
  Use an empty line to stop adding runs (i.e. press return)
  Syntax at the prompt is : 
    runnumber                 submits all file sequence for this run
    runnumber Chain           submits all file sequence for this run 
                              use 'Chain'
    runumber \#FSeq Chain     submits up to 'Fseq' file sequence for
                              this run. Chain is MANDATORY.

 You can also use a semi column separated list of the above.
    ~;
print "\n";

$ver = "";
$ver = $ARGV[0] if (@ARGV);

do {
    print "Sequence : ";
    chomp($line = <STDIN>);
    @items= split(";",$line);
    foreach $seq (@items){
	push(@TOADD,$seq);
    }
} while ($line ne "");

$flag =1;
while (-e "FastOff.lock"){
    print "Lock file exists, waiting ... ".localtime()."\n" if ($flag);
    $flag = 0;
    sleep(5);
}


open(FO,">>JobSubmit$ver.lis");
foreach $seq (@TOADD){
    print "Adding [$seq]\n";
    print FO "$seq\n";
}
close(FO);



