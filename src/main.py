"""
Main file for the Spotify remote
uses pySerial to communicate with ESP32 board
"""

import serial
from spotipyHelper import *

print('\033[92m' + "Starting up..." + '\033[0m')
ser = serial.Serial()

try:
    ser.port = '/dev/cu.usbserial-53220232121'
    ser.baudrate = 115200
    ser.timeout = 1  # 1 second timeout
    ser.open()
    while True:
        text = ser.readline().decode('utf-8').strip()
        if text:
            # print(text)
            pass
        else:
            print('\033[91m' + 'No data, retrying...' + '\033[0m')

        print('\33[33m', end='')

        # execute the function called by ESP32
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
        elif (len(text.split()) == 2) and (text.split()[0] == 'Volume'):
            volume = text.split()[1]
            setVolume(volume)
            print('Set volume to ' + volume)
        # else:
        #     print('\033[91m' + 'Invalid command' + '\033[0m')
        print('\33[0m', end='')

        # play tracks called by ESP32
        if text == 'TRACK NEVER GONNA GIVE YOU UP':
            # https://open.spotify.com/track/4cOdK2wGLETKBW3PvgPWqT
            print('Playing track: Never Gonna Give You Up (Rick Astley)')
            playTrack('spotify:track:4cOdK2wGLETKBW3PvgPWqT')
        elif text == 'PLAYLIST CHRISTMAS HITS':
            # https://open.spotify.com/playlist/37i9dQZF1DX0Yxoavh5qJV
            print('Playing playlist: Christmas Hits')
            playPlaylist('spotify:playlist:37i9dQZF1DX0Yxoavh5qJV')
        elif text == 'ALBUM BLUE NEIGHBORHOOD':
            # https://open.spotify.com/album/2mRBvhDWqm8Fj2U0F6mMY4
            print('Playing album: Blue Neighborhood by Troye Sivan')
            playAlbum('spotify:album:2mRBvhDWqm8Fj2U0F6mMY4')
        elif text == 'ALBUM BEINGFUNNYINFOREIGNLANGUAGE':
            # https://open.spotify.com/album/6dVCpQ7oGJD1oYs2fv1t5M
            print('Playing album: BeingFunnyInForeignLanguage by The 1975')
            playAlbum('spotify:album:6dVCpQ7oGJD1oYs2fv1t5M')
        elif text == 'ALBUM SMITHEREENS':
            # https://open.spotify.com/album/2hEnymoejldpuxSdTnkard
            print('Playing album: Smithereens by Joji')
            playAlbum('spotify:album:2hEnymoejldpuxSdTnkard')
        elif text == 'PLAYLIST JOMS ESSENTIALS':
            # https://open.spotify.com/playlist/2IbYQdnmVCr5l8UDR9Jw1l
            print('Playing playlist: essentials')
            playPlaylist('spotify:playlist:2IbYQdnmVCr5l8UDR9Jw1l')
        elif text == 'ALBUM MAKING STEAK':
            # https://open.spotify.com/album/2KR8a0U0f286MuzLaEJhL6
            print('Playing album: Making Steak by HYBS')
            playAlbum('spotify:album:2KR8a0U0f286MuzLaEJhL6')

# error handlings
except serial.SerialException:
    print('\033[91m' + 'ERROR: Check your serial port connection' + '\033[0m')
except KeyboardInterrupt:
    print('\033[92m' + "Exiting..." + '\033[0m')
finally:  # close serial port to clear up resources
    ser.close()
    print('\033[92m' + "Closing serial connection..." + '\033[0m')
