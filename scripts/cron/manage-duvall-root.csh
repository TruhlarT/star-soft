#!/usr/local/bin/tcsh
#
# manage-duvall-root.csh
#
# Nightly Linux mgmt tasks for root
#
echo duvall root management job

####### Pickford backup to duvall
setenv ARCHIVE /home/archive
setenv SOLARCHIVE /star/sol4/duvall/archive

echo "Backup pickford users to $ARCHIVE"
setenv TFILE $ARCHIVE/pickford-users.tar
[ -f $TFILE ] && rm -f $TFILE
cd /pickford
tar cf $TFILE --ignore-failed-read \
  --exclude "users/*/.ssh" \
  --exclude "users/*/.Xauthority" \
  --exclude "users/*/.history" \
users

#setenv TFILE $ARCHIVE/pickford.tar
#[ -f $TFILE ] && rm -f $TFILE
#cd /pickford
#time tar cf $TFILE --ignore-failed-read \
#  --exclude "egcs-1.1.1/*" \
#  --exclude "share/usr.local/share/texmf/*" \
#  --exclude "afsws_old/*" \
#  --exclude "users/*" \
#  *

echo "Backup mysql to $SOLARCHIVE"
setenv TFILE $ARCHIVE/mysql.tar.gz
[ -f $TFILE ] && rm -f $TFILE
cd /usr/local/mysql
time tar czf $TFILE --ignore-failed-read *
# copy to sol
su wenaus <<EOF
echo "Move old backup out of way"
mv $SOLARCHIVE/mysql.tar.gz $SOLARCHIVE/mysql-old.tar.gz
echo "Copy new backup to sol"
cp $TFILE $SOLARCHIVE
EOF

echo "Listing of $ARCHIVE"
ls -al $ARCHIVE
echo "Listing of $SOLARCHIVE"
ls -al $SOLARCHIVE
