import telebot
import os
bot = telebot.TeleBot('5706617053:AAET56DTRQisRKGdtSWjI1gKex0hZ_RGn-k')

@bot.message_handler(content_types=['text'])

def get_text_messages(message):
  sps = message.text.lower().split(' ')
  if sps[0] == "/test":
    os.system("make test filename=" + sps[1])
  elif sps[0] == "/learn":
    os.system("make learn settings=" + sps[1]);
  elif sps[0] == "/weights":
    os.system("bash telegram.sh weights");
  else:
    bot.send_message(message.from_user.id, "Dont get it, type /help.")

bot.polling(none_stop=True, interval=0)