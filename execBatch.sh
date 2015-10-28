#!/usr/bin/env bash

EXEC="./GA"
NUM_EXECS=30
GA_CONF="gaConf1.gaconf"
REPORTS_PATH="reports/"
STDCOUT_FILE="stdcout.log"
PROBLEM_LIST="$(find . -name "*.ttp")"

i=1;

for ttp in ${PROBLEM_LIST}
do
  $EXEC $ttp $GA_CONF $NUM_EXECS $REPORTS_PATH $STDCOUT_FILE
  $i=$i+1
done

# GA instances/kroA100-ttp/kroA100_n990_uncorr_10.ttp  gaConf1.gaconf 30 reports/ stdcoutr.log
