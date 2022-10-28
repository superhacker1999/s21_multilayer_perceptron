#!/bin/bash
TELEGRAM_BOT_TOKEN="5706617053:AAET56DTRQisRKGdtSWjI1gKex0hZ_RGn-k"
TELEGRAM_USER_ID=352059128
TIME=60

URL="https://api.telegram.org/bot$TELEGRAM_BOT_TOKEN/sendMessage"

if [ "$1" == "Tests are done." ] ; then
  TEXT="$1 `cat text.txt | tail -n1`"
elif [ "$1" == "weights" ] ; then
  TEXT="`ls | grep weights`"
elif [ "$1" == "Neuron net has trained." ] ; then
  TEXT="$1 `cat text.txt | tail -n1` U can start tests now."
else
  TEXT="Smth went wrong."
fi


curl -s --max-time $TIME -d "chat_id=$TELEGRAM_USER_ID&disable_web_page_preview=1&text=$TEXT" $URL > /dev/null
