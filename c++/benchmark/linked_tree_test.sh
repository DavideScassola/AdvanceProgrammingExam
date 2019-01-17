#ITER=1

N_SEQ="10000 20000 40000 60000 80000 100000 120000 140000 160000"
BNAME=bench_ll.x

#for i in $(seq $FIRST_MAT_SIZE $LAST_MAT_SIZE); do
echo "N;LINKED_LIST_TREE"
for i in $N_SEQ; do       
        N=$i
	./$BNAME $N
done

exit
