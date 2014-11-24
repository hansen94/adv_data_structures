#!/bin/bash

CPP="./BitInputStream.cpp ./BitOutputStream.cpp ./HCNode.cpp ./HCTree.cpp ./Tester.cpp"

echo g++ -std=c++11 $CPP HCNodeTester.cpp -o hcnodetester
g++ -pg -std=c++11 $CPP HCNodeTester.cpp -o hcnodetester
echo g++ -std=c++11 $CPP HCTreeTester.cpp -o hctreetester
g++ -pg -std=c++11 $CPP HCTreeTester.cpp -o hctreetester
echo g++ -std=c++11 $CPP BitInputOutputTester.cpp -o bitinputoutputtester
g++ -pg -std=c++11 $CPP BitInputOutputTester.cpp -o bitinputoutputtester

echo
echo "#############################"
echo "Running hcnodetester"
./hcnodetester

echo
echo "#############################"
echo "Running hctreetester"
./hctreetester

echo
echo "#############################"
echo "Running bitinputoutputtester"
./bitinputoutputtester

echo
echo "#############################"
echo "Running tests on given input files"
make
for FILE in `ls ./input_files`
do
    echo
    echo 
    echo "##########################"
    echo ./compress ./input_files/$FILE ./input_files/$FILE.cms
    ./compress ./input_files/$FILE ./input_files/$FILE.cms 2> ./comp
    echo ./uncompress ./input_files/$FILE.cms ./input_files/$FILE.cms.dms
    ./uncompress ./input_files/$FILE.cms ./input_files/$FILE.cms.dms 2>> ./comp

    echo "@@@@ REFERENCE @@@@"
    echo ./refcompress ./input_files/$FILE ./input_files/$FILE.cmsr
    ./refcompress ./input_files/$FILE ./input_files/$FILE.cmsr 2> ./rcomp
    echo ./refuncompress ./input_files/$FILE.cmsr ./input_files/$FILE.cms.dmsr
    ./refuncompress ./input_files/$FILE.cmsr ./input_files/$FILE.cms.dmsr 2>> ./rcomp

    diff -y ./comp ./rcomp
    echo cmp ./comp ./rcomp
    cmp ./comp ./rcomp

    echo cmp ./input_files/$FILE ./input_files/$FILE.cms.dms
    cmp ./input_files/$FILE ./input_files/$FILE.cms.dms
    diff -y --suppress-common-lines ./input_files/$FILE ./input_files/$FILE.cms.dms
    echo
    echo "Cleaning up"
    rm ./input_files/$FILE.cms.dms ./input_files/$FILE.cms ./input_files/$FILE.cms.dmsr ./input_files/$FILE.cmsr
done
