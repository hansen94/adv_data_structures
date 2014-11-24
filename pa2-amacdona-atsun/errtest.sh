#!/bin/bash

mkdir -p ./tmp

for I in `python -c "print '\n'.join(str(i) for i in range(10))"`
do
    touch tmp/`date +%N`
done

for FILE in `ls ./tmp`
do
    PERM=`python -c "import random as r; r = r.randrange;print str(r(0,7)) + str(r(0,7)) + str(r(0,7))"`
    chmod $PERM ./tmp/$FILE
done

mkdir -p ./tmp/.out
for FILE1 in `ls ./tmp`
do
    for FILE2 in `ls ./tmp`
    do
	echo "@@ Permissions"
	ls -lth ./tmp/$FILE1 ./tmp/$FILE2

	echo "@@ Compress"
	echo ./compress ./tmp/$FILE1 ./tmp/$FILE2
	./compress ./tmp/$FILE1 ./tmp/$FILE2 2> ./tmp/.out/$FILE1$FILE2.cmp > ./tmp/.out/$FILE1$FILE2.so.cmp
	echo ./refcompress ./tmp/$FILE1 ./tmp/$FILE2
	./refcompress ./tmp/$FILE1 ./tmp/$FILE2 2> ./tmp/.out/$FILE1$FILE2.cmpr > ./tmp/.out/$FILE1$FILE2.so.cmpr
	diff -y --suppress-common-lines ./tmp/.out/$FILE1$FILE2.cmp ./tmp/.out/$FILE1$FILE2.cmpr
	diff -y --suppress-common-lines ./tmp/.out/$FILE1$FILE2.so.cmp ./tmp/.out/$FILE1$FILE2.so.cmpr

	echo "@@ Uncompress"
	echo ./uncompress ./tmp/$FILE1 ./tmp/$FILE2
	./uncompress ./tmp/$FILE1 ./tmp/$FILE2 2> ./tmp/.out/$FILE1$FILE2.cmp > ./tmp/.out/$FILE1$FILE2.so.cmp
	echo ./refuncompress ./tmp/$FILE1 ./tmp/$FILE2
	./refuncompress ./tmp/$FILE1 ./tmp/$FILE2 2> ./tmp/.out/$FILE1$FILE2.cmpr > ./tmp/.out/$FILE1$FILE2.so.cmpr
	diff -y --suppress-common-lines ./tmp/.out/$FILE1$FILE2.cmp ./tmp/.out/$FILE1$FILE2.cmpr
	diff -y --suppress-common-lines ./tmp/.out/$FILE1$FILE2.so.cmp ./tmp/.out/$FILE1$FILE2.so.cmpr
    done
done

for FILE1 in `ls ./tmp`
do
    echo "@@ Compress"
    echo ./compress ./tmp/$FILE1
    ./compress ./tmp/$FILE1  2> ./tmp/.out/$FILE1.cmp > ./tmp/.out/$FILE1.so.cmp
    echo ./refcompress ./tmp/$FILE1 
    ./refcompress ./tmp/$FILE1  2> ./tmp/.out/$FILE1.cmpr > ./tmp/.out/$FILE1.so.cmpr
    diff -y --suppress-common-lines ./tmp/.out/$FILE1.cmp ./tmp/.out/$FILE1.cmpr 
    diff -y --suppress-common-lines ./tmp/.out/$FILE1.so.cmp ./tmp/.out/$FILE1.so.cmpr 
    
    echo "@@ Uncompress"
    echo ./uncompress ./tmp/$FILE1
    ./uncompress ./tmp/$FILE1  2> ./tmp/.out/$FILE1.cmp > ./tmp/.out/$FILE1.so.cmp
    echo ./refuncompress ./tmp/$FILE1 
    ./refuncompress ./tmp/$FILE1  2> ./tmp/.out/$FILE1.cmpr > ./tmp/.out/$FILE1.so.cmpr
    diff -y --suppress-common-lines ./tmp/.out/$FILE1.cmp ./tmp/.out/$FILE1.cmpr 
    diff -y --suppress-common-lines ./tmp/.out/$FILE1.so.cmp ./tmp/.out/$FILE1.so.cmpr 
done


for I in `python -c "print '\n'.join(str(i) for i in range(3, 100))"`
do
    echo "@@ Compress"
    echo ./compress ...
    ./compress `find ./tmp/ | head -$I`   2> ./tmp/.out/1.cmp > ./tmp/.out/1.so.cmp
    echo ./refcompress ...
    ./refcompress `find ./tmp/ | head -$I`  2> ./tmp/.out/1.cmpr > ./tmp/.out/1.so.cmpr
    diff -y --suppress-common-lines ./tmp/.out/1.cmp ./tmp/.out/1.cmpr
    diff -y --suppress-common-lines ./tmp/.out/1.so.cmp ./tmp/.out/1.so.cmpr
    
    echo "@@ Uncompress"
    echo ./uncompress ...
    ./uncompress `find ./tmp/ | head -$I`   2> ./tmp/.out/1.cmp > ./tmp/.out/1.so.cmp
    echo ./refuncompress ...
    ./refuncompress `find ./tmp/ | head -$I`  2> ./tmp/.out/1.cmpr > ./tmp/.out/1.so.cmpr
    diff -y --suppress-common-lines ./tmp/.out/1.cmp ./tmp/.out/1.cmpr
    diff -y --suppress-common-lines ./tmp/.out/1.so.cmp ./tmp/.out/1.so.cmpr

done