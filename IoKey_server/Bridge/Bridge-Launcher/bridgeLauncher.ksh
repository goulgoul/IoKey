#!/bin/bash
DIR='/home/ubuntu/mqttBridge/'
CODE='bridge-ttn-v2.3'

echo 'Start Launcher' >> "${DIR}/logs/launcher.log" 2>&1
until ping -c 1 -W 1 8.8.8.8; do sleep 5 ; done

cd "${DIR}" 
source ./bin/activate
echo "Executing python3 ${CODE}.py" >> "${DIR}/logs/launcher.log" 2>&1
python3 "${CODE}.py" >> "${DIR}/logs/launcher.log" 2>&1
deactivate
