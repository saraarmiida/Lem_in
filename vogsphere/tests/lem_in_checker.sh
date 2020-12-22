#!/bin/bash
trap "exit" INT
MINARGS=1
if [ $# -lt $MINARGS ]; then
	echo "Usage: sh script.sh --flow-one\n --flow-ten\n --flow-thousand\n --big\n --big-superposition"
	exit $E_NOARGS
fi
REQ_LINES=0
OWN_LINES=0
ARG=$1
slow=0
i=0
printf "REQUIRED	OUTPUT		DIFFERENCE	TIME	\n"
while [ $i -lt 50 ]
do
	./generator $ARG > argFILE
	(time -p ../lem-in < argFILE > outFILE) &> "timeFILE"
	TIME=$(grep real "timeFILE" | awk '{print $2}')
	OUTNUM=$(wc -l "outFILE" | awk '{print $1}')
	ARGNUM=$(wc -l "argFILE" | awk '{print $1}')
	REQ=$(head -5 'argFILE' |  grep 'require' | awk '{print $8}')
	REQ_LINES=$(( $REQ_LINES + $REQ ))
	OWN=$(tail -5 'outFILE' |  grep 'lines' | awk '{print $2}')
	OWN_LINES=$(( $OWN_LINES + $OWN ))
	DIF=$(($OWN - $REQ))
	printf "$REQ		"
	printf "$OWN		"
	printf "$DIF		"
	printf "$TIME\n"
	if (( $(echo "$TIME > 3.00" |bc -l) )); then
		slow=$(( $slow + 1 ))
	fi
	if (( $OWN < $REQ - 5 ))
	then
		cp -rf outFILE outProblem
		cp -rf argFILE inProblem
	fi
	rm -rf timeFILE
	rm -rf outFILE
	rm -rf argFILE
	i=$(( $i + 1 ))
done
REQ_AVERAGE=$(( $REQ_LINES / $i))
OWN_AVERAGE=$(( $OWN_LINES / $i))
AV_DIF=$(( $OWN_AVERAGE - $REQ_AVERAGE ))
printf "\nOur average difference per $i tests: $AV_DIF \n"
exit 0