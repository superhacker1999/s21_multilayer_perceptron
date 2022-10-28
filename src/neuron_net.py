import telebot
import os
bot = telebot.TeleBot('5706617053:AAET56DTRQisRKGdtSWjI1gKex0hZ_RGn-k')

@bot.message_handler(content_types=['text'])

def get_text_messages(message):
  sps = message.text.lower().split(' ')
  if sps[0] == "/test":
    if len(sps) == 2:
      bot.send_message(message.from_user.id, "Please wait...")
      os.system("make test filename=" + sps[1])
    else:
      bot.send_message(message.from_user.id, "Please wait...")
      os.system("make test")
  elif sps[0] == "/learn" and len(sps) == 4:
    bot.send_message(message.from_user.id, "Please wait...")
    os.system("make learn alpha=" + sps[1] + " percent=" + sps[2] + " epochs=" + sps[3]);
  elif sps[0] == "/weights":
    os.system("bash telegram.sh weights");
  elif sps[0] == "/push" and len(sps) > 1:
    os.system("git add " + sps[1] + " && git commit -m 'telegram bot weights push' && git push origin develop");
    bot.send_message(message.from_user.id, "Weight pushed successfully!")
  elif sps[0] == "/help":
     bot.send_message(message.from_user.id, "Use /test [path to weight] to start test.\nUse /learn [alpha]* ['%' of dataset]** [epochs]*** to start learning.\nUse /weights to get existing weights.\n* - should be a number 0.00-1.00\n** - should be 1 - 100%\n*** - should be int")
  else:
    bot.send_message(message.from_user.id, "Dont get it, type /help.")

bot.polling(none_stop=True, interval=0)