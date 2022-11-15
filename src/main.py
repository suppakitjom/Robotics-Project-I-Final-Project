"""
main file for the Spotify remote
uses pySerial to communicate with ESP32 board
"""

import serial
import time
from spotipyHelper import *

print('\033[92m' + "Starting up..." + '\033[0m')
ser = serial.Serial()

try:
    ser.port = '/dev/cu.usbserial-53220232121'
    ser.baudrate = 115200
    ser.timeout = 1
    ser.open()
    while True:
        text = ser.readline().decode('utf-8').strip()
        if text:
            print(text)
            pass
        else:
            print('\033[91m' + 'No data, retrying...' + '\033[0m')

        print('\33[33m', end='')
        if text == 'Toggle Playback':
            togglePlayback()
            print('Toggled playback')

        elif text == 'Stop':
            stopPlayback()
            print('Stopped playback')
        elif text == 'Toggle Repeat':
            toggleRepeat()
            print('Toggled repeat')
        elif text == 'Toggle Shuffle':
            toggleShuffle()
            print('Toggled shuffle')
        elif text == 'Next':
            nextTrack()
            print('Next track')
        elif text == 'Previous':
            previousTrack()
            print('Previous track')
        elif len(text.split()) and text.split()[0] == 'Volume':
            volume = text.split()[1]
            setVolume(volume)
            print('Set volume to ' + volume)
        print('\33[0m', end='')

        if text == 'ALBUM CHARLIE':
            # https://open.spotify.com/album/2LTqBgZUH4EkDcj8hdkNjK
            playAlbum('spotify:album:2LTqBgZUH4EkDcj8hdkNjK')
        elif text == 'ALBUM CERTIFIED LOVER BOY':
            # https://open.spotify.com/album/3SpBlxme9WbeQdI9kx7KAV
            playAlbum('spotify:album:3SpBlxme9WbeQdI9kx7KAV')
        elif text == 'TRACK NEVER GONNA GIVE YOU UP':
            # https://open.spotify.com/track/4cOdK2wGLETKBW3PvgPWqT
            playTrack('spotify:track:4cOdK2wGLETKBW3PvgPWqT')
        elif text == 'PLAYLIST CHRISTMAS HITS':
            # https://open.spotify.com/playlist/37i9dQZF1DX0Yxoavh5qJV
            playPlaylist('spotify:playlist:37i9dQZF1DX0Yxoavh5qJV')

except serial.SerialException:
    print('\033[91m' + 'ERROR: Check your serial port connection' + '\033[0m')
except KeyboardInterrupt:
    print('\033[92m' + "Exiting..." + '\033[0m')
finally:
    ser.close()
    print('\033[92m' + "Closing serial connection..." + '\033[0m')