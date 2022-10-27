#!/bin/bash
TELEGRAM_BOT_TOKEN="5706617053:AAET56DTRQisRKGdtSWjI1gKex0hZ_RGn-k"
TELEGRAM_USER_ID=352059128
TIME=60

URL="https://api.telegram.org/bot$TELEGRAM_BOT_TOKEN/sendMessage"
TEXT="Нейронка обучилась, можно запускать тесты"

curl -s --max-time $TIME -d "chat_id=$TELEGRAM_USER_ID&disable_web_page_preview=1&text=$TEXT" $URL > /dev/null
