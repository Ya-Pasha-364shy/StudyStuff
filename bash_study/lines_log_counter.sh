#!/bin/bash

touch files.txt
sudo find /var/log/*.log > files.txt

while IFS= read -r line; do
	echo -n "Full path: $line"
	STROKES=`sudo wc $line | sed 's/\(\ \)*//' | sed 's/\(\ \(.\)\{1,\}\)//'`
	echo ";Number of strokes: $STROKES"
done<./files.txt

echo "DONE"; exit 0
