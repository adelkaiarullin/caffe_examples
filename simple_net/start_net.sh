#!/usr/bin/bash
proto_model_path=model_def/deploy.prototxt
model_weights=model_def/net.caffemodel
img=1.jpg
./net $proto_model_path $model_weights $img
