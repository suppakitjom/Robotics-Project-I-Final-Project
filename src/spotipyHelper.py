"""
File for handling the Spotify API using spotipy
Automaticaly initiates the spotipy client using 
the credentials in the settings.py file
"""

import spotipy
from spotipy.oauth2 import SpotifyOAuth
from settings import *

sp = spotipy.Spotify(auth_manager=SpotifyOAuth(client_id=CLIENT_ID,
                                               client_secret=CLIENT_SECRET,
                                               redirect_uri=REDIRECT_URI,
                                               scope=SCOPE))


def togglePlayBack():
    '''
    Checks if the playback is paused and resumes it.
    Otherwise pauses the playback.
    '''
    if sp.currently_playing()['is_playing']:
        sp.pause_playback(device_id=DEVICE_ID)
    else:
        sp.start_playback(device_id=DEVICE_ID)


def toggleRepeat():
    '''
    Toggles the repeat state of the playback.
    '''
    if sp.current_playback()['repeat_state'] == 'off':
        sp.repeat('context', device_id=DEVICE_ID)
    else:
        sp.repeat('off', device_id=DEVICE_ID)


def toggleShuffle():
    '''
    Toggles the shuffle state of the playback.
    '''
    if sp.current_playback()['shuffle_state']:
        sp.shuffle(False, device_id=DEVICE_ID)
    else:
        sp.shuffle(True, device_id=DEVICE_ID)


def nextTrack():
    '''
    Plays the next track in the queue.
    '''
    sp.next_track(device_id=DEVICE_ID)


def previousTrack():
    '''
    Checks if the current song is more than 5 seconds in, 
    if so restarts the song. 
    Otherwise plays the previous song in the queue.
    '''
    if sp.currently_playing()['progress_ms'] > 5000:
        sp.seek_track(0, device_id=DEVICE_ID)
    else:
        sp.previous_track(device_id=DEVICE_ID)


def playTrack(track):
    '''
    Plays a track.
    '''
    sp.start_playback(device_id=DEVICE_ID, uris=[track])


def playAlbum(album):
    '''
    Plays an album.
    '''
    sp.start_playback(device_id=DEVICE_ID, context_uri=album)
