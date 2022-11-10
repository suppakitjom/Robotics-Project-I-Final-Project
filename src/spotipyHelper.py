import spotipy
from spotipy.oauth2 import SpotifyOAuth
from settings import *

sp = spotipy.Spotify(auth_manager=SpotifyOAuth(client_id=CLIENT_ID,
                                               client_secret=CLIENT_SECRET,
                                               redirect_uri=REDIRECT_URI,
                                               scope=SCOPE))


def togglePlayBack():
    if sp.currently_playing()['is_playing']:
        sp.pause_playback(device_id=DEVICE_ID)
    else:
        sp.start_playback(device_id=DEVICE_ID)


def toggleRepeat():
    if sp.current_playback()['repeat_state'] == 'off':
        sp.repeat('context', device_id=DEVICE_ID)
    else:
        sp.repeat('off', device_id=DEVICE_ID)


def toggleShuffle():
    if sp.current_playback()['shuffle_state']:
        sp.shuffle(False, device_id=DEVICE_ID)
    else:
        sp.shuffle(True, device_id=DEVICE_ID)


def nextTrack():
    sp.next_track(device_id=DEVICE_ID)


def previousTrack():
    if sp.currently_playing()['progress_ms'] > 5000:
        sp.seek_track(0, device_id=DEVICE_ID)
    else:
        sp.previous_track(device_id=DEVICE_ID)


def playTrack(track):
    sp.start_playback(device_id=DEVICE_ID, uris=[track])


def playAlbum(album):
    sp.start_playback(device_id=DEVICE_ID, context_uri=album)
