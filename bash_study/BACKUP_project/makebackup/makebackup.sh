#!/bin/bash
FLAG=0
# POINT A:
# create and check backup directory

ERRORFILE=make_backup.errors

CURRENT_DATE=`date +"%F"`
VALID_DATE=`echo $CURRENT_DATE | sed "s/-//g" | sed "s/ //g"`
BACKUP_NAME="backup-$CURRENT_DATE"
PATH_BACKUP_DIR="$HOME/$BACKUP_NAME"

echo "[*] Creating back-up directory by next path: $PATH_BACKUP_DIR"

CHECK_DIR=`ls $HOME | grep "backup-" | sed "s/\n//"`
BACKUP_DATE=`echo "$CHECK_DIR" | sed "s/[a-Z]*-//" | sed "s/-//g" | sed "s/ //g"`

DEV=$(($VALID_DATE-$BACKUP_DATE)) 2>>$ERRORFILE
DEAD_DAYS=7

FROM_DIR="$HOME/listtask/" # its standart

if [[ $CHECK_DIR == "" || $DEV > $DEAD_DAYS ]]; then
	echo "[!] Date of past backup was be more then 7 days"; echo "Creating new backup.."
	mkdir $PATH_BACKUP_DIR; echo "[+] New Directory was be created. Check it: $PATH_BACKUP_DIR"
	FLAG=1
else
	echo "[+] Backup dir is ACTUAL now."
	echo "[*] Process of refresh backup was be started !"
	PATH_BACKUP_DIR="$HOME/$CHECK_DIR"
	BACKUP_NAME=$CHECK_DIR
fi

# POINT B:
# copying files from $HOME/listtask/ and reporting about it in $HOME/backup-report.log (or .txt)

if [[ $FLAG == 1 ]]; then

	cp -R $FROM_DIR* -t $PATH_BACKUP_DIR

	# PUT INFO ABOUT CHANGES IN THE LOG FILE IN HOME DIRECTORY
	echo "[!] New backup dir was be created. Path: $PATH_BACKUP_DIR" >> $HOME/backup_report.txt
	echo "[!] Date of create: $CURRENT_DATE" >> $HOME/backup_report.txt

	echo "`file $PATH_BACKUP_DIR/*`" > pipe.txt

	while read line; do
		echo "[+] New File: $line" >> $HOME/backup_report.txt
	done<./pipe.txt; rm pipe.txt
fi

# POINT C:
# REFRESH OLD BACKUP DIRECTORY.
# Follow rules: compare weight. Next - watch in the code.

if [[ $FLAG == 0 ]]; then
	echo "[*] Checking the weight of files in Backup and standart directories.."
	filesize_standart=$(stat -c%s "") 2>>$ERRORFILE
	
	echo "`file $FROM_DIR*`" | sed "s/:.*//" > pipe.txt

	while read line; do
		if [[ $line == "" ]]; then
			continue
		fi

		standart_file_size=$(stat -c%s "$line" 2>>$ERRORFILE)
		comparable_file=`echo $line | sed "s/listtask/$BACKUP_NAME/"`
		comparable_file_size=$(stat -c%s "$comparable_file" 2>>$ERRORFILE)

		st_fname=`echo "$line" | sed "s/\/.*\///"`
		operation=`find "$PATH_BACKUP_DIR/$st_fname"`

		if [[ "$operation" != "$PATH_BACKUP_DIR/$st_fname" ]]; then
			cp "$FROM_DIR/$st_fname" -t "$PATH_BACKUP_DIR/$st_fname" 2>>$ERRORFILE
			echo "[+] Copy new file: $st_fname from $FROM_DIR directory to backup: $PATH_BACKUP_DIR" >> $HOME/backup_report.txt

			echo "[!] New files in 'standart' directory was be detected ! Copying to BACKUP dir!"
		fi

		if [[ $standart_file_size -ne $comparable_file_size ]]; then
			new_name_stand_f=`echo "$comparable_file.$CURRENT_DATE"`
			mv $comparable_file $new_name_stand_f 2>>$ERRORFILE
			cp $line -t $PATH_BACKUP_DIR 2>>$ERRORFILE
			echo "[+] Add new version of $comparable_file (as new version) on $new_name_stand_f (as old version)" >> $HOME/backup_report.txt
			
			echo "[!] Weights by $line aren't equals. Was be create a new version of changed file!"
		else
			echo "[*] Weights of copy and original by $line are equals."
		fi

        done<./pipe.txt; rm pipe.txt
fi

echo "[+] Complete successfully!"
exit 0
