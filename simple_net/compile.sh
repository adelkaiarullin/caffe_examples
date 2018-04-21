#!/usr/bin/bash
INC_CAFFE=/home/adel/caffe/include
LIB_Caffe=/home/adel/caffe/build/lib
OPENCV=`pkg-config --libs --cflags opencv`
g++ -std=c++11 -o net net.cpp $OPENCV -I${INC_CAFFE} -L ~/caffe/build/lib/lib*  -lboost_system -lglog
