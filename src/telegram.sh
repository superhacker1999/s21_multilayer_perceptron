#!/bin/bash
TELEGRAM_BOT_TOKEN="5706617053:AAET56DTRQisRKGdtSWjI1gKex0hZ_RGn-k"
TELEGRAM_USER_ID=352059128
TIME=60

URL="https://api.telegram.org/bot$TELEGRAM_BOT_TOKEN/sendMessage"

if ! [ -n "$2" ] ; then
  TEXT="$1 `cat text.txt | tail -n1`"
else
  TEXT="$1 $2"
fi

curl -s --max-time $TIME -d "chat_id=$TELEGRAM_USER_ID&disable_web_page_preview=1&text=$TEXT" $URL > /dev/null
