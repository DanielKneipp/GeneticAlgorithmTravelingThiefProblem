#!/usr/bin/env bash

EXEC="./GA"
NUM_EXECS=30
GA_CONF="gaConf1.gaconf"
REPORTS_PATH="reports/"
STDCOUT_FILE="stdcout"
PROBLEM_LIST="$(find . -name "*.ttp")"

for ttp in ${PROBLEM_LIST}
do
    ttp_name=$(basename $ttp)
    echo $EXEC "$ttp $GA_CONF $NUM_EXECS $REPORTS_PATH ${STDCOUT_FILE}__${ttp_name}.log"
done

# GA instances/kroA100-ttp/kroA100_n990_uncorr_10.ttp gaConf1.gaconf 30 reports/ stdcout__kroA100_n990_uncorr_10.ttp.log
