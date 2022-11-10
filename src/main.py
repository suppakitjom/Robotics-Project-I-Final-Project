"""
main file for the spotify remote
uses pySerial to communicate with ESP32 board
"""

import serial
import time
from spotipyHelper import *

ser = serial.Serial('/dev/cu.usbserial-53220232121', 115200, timeout=1)

while True:
    text = ser.readline().decode('utf-8').strip()
    if text:
        print(text)
    else:
        print('No data, retrying...')

    if text == 'Toggle Playback':
        togglePlayBack()
    elif text == 'Toggle Repeat':
        toggleRepeat()
    elif text == 'Toggle Shuffle':
        toggleShuffle()
    elif text == 'Next':
        nextTrack()
    elif text == 'Previous':
        previousTrack()

    if text == 'ALBUM CHARLIE':
        # https://open.spotify.com/album/2LTqBgZUH4EkDcj8hdkNjK
        playAlbum('spotify:album:2LTqBgZUH4EkDcj8hdkNjK')
    elif text == 'ALBUM CERTIFIED LOVER BOY':
        # https://open.spotify.com/album/3SpBlxme9WbeQdI9kx7KAV
        playAlbum('spotify:album:3SpBlxme9WbeQdI9kx7KAV')
    elif text == 'TRACK NEVER GONNA GIVE YOU UP':
        # https://open.spotify.com/track/4cOdK2wGLETKBW3PvgPWqT
        playTrack('spotify:track:4cOdK2wGLETKBW3PvgPWqT')