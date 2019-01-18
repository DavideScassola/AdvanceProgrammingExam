N_SEQ="1 2 4 6 8 10 12 14 16 18 20"
BNAME=bench.x
FIRST=1
LAST=10

echo "N;RANDOM;BALANCED;STD_MAP"
for i in $(seq $FIRST $LAST); do
	for i in $N_SEQ; do       
        	N=$((i*1000000))
		./$BNAME $N ciao
	done
done
exit
