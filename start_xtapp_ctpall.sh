#!/bin/bash
export LD_LIBRARY_PATH=/home/app/xtdeploy/lib/linux64:$LD_LIBRARY_PATH:/usr/lib:/usr/lib64:/usr/local/lib:/usr/local/lib64
export LIBRARY_PATH=/home/app/xtdeploy/lib/linux64:$LIBRARY_PATH:/usr/lib:/usr/lib64:/usr/local/lib:/usr/local/lib64
cd  /home/app/xtdeploy/app_linux64/xtapp_ctpall
./xtapp_ctpall >> /home/app/logs/xtapp_ctpall.log 2>&1 &

