#ITER=1

N_SEQ="1 2 4 6 8 10 12 14 16 18 20"
BNAME=bench.x

#for i in $(seq $FIRST_MAT_SIZE $LAST_MAT_SIZE); do
echo "N;RANDOM;BALANCED;STD_MAP"
for i in $N_SEQ; do       
        N=$((i*1000000))
	./$BNAME $N ciao
done

exit
