#!/bin/sh

CreateTestCommandMessage() {
  local command=$1
  local parameters=$2
  echo "{
    \"messageHeader\": {
      \"messageType\": \"test\",
      \"messageVersion\": \"V1_0\",
      \"messageId\": \"\",
      \"createdAt\": \"\"
    },
    \"messageBody\": {
      \"testCommand\": \"$command\",
      \"parameters\": \"$(echo $parameters | sed 's:":\\\":g')\"
    }
  }"
}

CreateTestCommandMessage AddDevice \
'{"hardware_id":"00:11:22:33:44:02",'\
'"external_device_id":"test_device_id00:11:22:33:FF:01",'\
'"owner":"master.cameraDaemon",'\
'"device_type":"CAMERA",'\
'"pairing_status":"UNPAIRED"}'