#!/bin/bash

# POINT A:
# Restoring files with some early date in file's name
# In result, we are copyed files (it means old version) in $HOME/listtask

ERRORFILE=restore_backup.errors
CURRENT_DATE=`date +"%F"`

VALID_DATE=`echo $CURRENT_DATE | sed "s/-//g" | sed "s/ //g"`

CURRENT_YEAR=`date +"%Y"`
CURRENT_MONTH=`date +"%m"`

# select backups on current YEAR AND current MONTH
search=`ls $HOME/ | grep -i backup | grep $CURRENT_YEAR | grep $CURRENT_MONTH | sed "s/[a-Z]*//g" | sed "s/-//g"`

echo $search | grep -e "[0-9]*" > pipe.txt; cat pipe.txt | sed "s/ /\n/g" > pipe1.txt; rm pipe.txt


# search more early backup
min=10000
selected=0

while read line; do
	DEV=$(($VALID_DATE-$line)) 2>>$ERRORFILE
	
	if [[ "$DEV" < "$min"  ]]; then
		selected=$line
	fi

done<pipe1.txt; rm pipe1.txt

# validing..
early_year=`echo ${selected:0:4}`
early_month=`echo ${selected:4:2}`
early_day=`echo ${selected: -2}`

EARLY_BACKUP="$HOME/backup-$early_year-$early_month-$early_day"
echo "+--- File in EARLY BACKUP directory ---+"
ls $EARLY_BACKUP
echo "+---             ......             ---+"


read -p "Are u realy want to RESTORE FILES ? [Y/N]:" ch;

if [[ "$ch" == "Y" || "$ch" == "y" ]]; then
        echo " "
elif [[ "$ch" == "N" || "$ch" == "n" ]]; then
        echo "Okey, Goodbye!";exit 0
else
        echo "Try again!"; echo "Exiting...";exit 1
fi


TO_RESTORE="$HOME/listtask"

ls $EARLY_BACKUP | grep "\.txt.[0-9]*-" | sed "s/ /\n/" > pipe.txt

while read line; do

	new_line=`echo $line | sed "s/\.txt.*/.txt/"`
	cd $TO_RESTORE && rm $new_line && cd -
	ln "$EARLY_BACKUP/$line" "$TO_RESTORE/$new_line" 2>>$ERRORFILE
	
	echo "[*] Restoring: $line TO $new_line"

done<pipe.txt;rm pipe.txt

echo "[+] Successfully complete !"
echo "[*] Old versions of the files was being restored"
exit 0
