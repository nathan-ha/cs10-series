#include <iostream>
#include "Playlist.h"
using namespace std;

void PrintMenu(const string &songTitle);

int main() {
	cout << "Enter playlist's title:\n";
	string playlistName;
	if (!getline(cin, playlistName)) return 1; //if getline fails here, then the whole program is probably screwed anyways, so might as well return
	cout << endl;

	int numSongs = 0; //track number of songs added
	char userChoice;
	Playlist playlist;
	
	do {
		PrintMenu(playlistName);

		if (!(cin >> userChoice)) return 1; //I thought about using 'continue' here to try cin again until it works, but prof miller said returning 1 is fine for now

		if (userChoice == 'a') {
			cout << "ADD SONG\n";
			//ask if I should declare string here or above
			string uniqueID, songName, artistName;
			cout << "Enter song's unique ID:\n";
			if (!(cin >> uniqueID)) return 1;
			cout << "Enter song's name:\n";
			cin.ignore(); //ignore whitespace from cin
			if (!getline(cin, songName)) return 1;
			cout << "Enter artist's name:\n";
			if (!getline(cin, artistName)) return 1;
			cout << "Enter song's length (in seconds):\n\n";
			int songLength;
			if (!(cin >> songLength)) return 1;
			playlist.addSong(uniqueID, songName, artistName, songLength);
			numSongs++;
		} else if (userChoice == 'd') {
			cout << "REMOVE SONG\n"
				 << "Enter song's unique ID:\n";
			string targetID;
			if (!(cin >> targetID)) return 1;
			string songName;
			playlist.removeSong(targetID, songName);
			numSongs--;
			cout << '\"' << songName << "\" removed.\n\n";
		} else if (userChoice == 'c') {
			cout << "CHANGE POSITION OF SONG\n";
			cout << "Enter song's current position:\n";
			int currPosition, newPosition;
			if (!(cin >> currPosition)) return 1;
			cout << "Enter new position for song:\n";
			if (!(cin >> newPosition)) return 1;
			string songName;
			playlist.changePositionOfSong(currPosition, newPosition, songName, numSongs);
			cout << '\"' << songName << "\" moved to position " << newPosition << "\n\n";
		} else if (userChoice == 's') {
			cout << "OUTPUT SONGS BY SPECIFIC ARTIST\n";
			string artistName;
			cout << "Enter artist's name:\n";
			cin.ignore();
			if (!(getline(cin, artistName))) return 1;
			cout << endl;
			playlist.outputSongsByArtist(artistName);
		} else if (userChoice == 't') {
			cout << "OUTPUT TOTAL TIME OF PLAYLIST (IN SECONDS)\n";
			playlist.outputTotalSeconds();
		} else if (userChoice == 'o') {
			cout << playlistName + " - OUTPUT FULL PLAYLIST\n";
			playlist.outputFullPlaylist();
		}
	} while(userChoice != 'q'); //it should just keep re-prompting until q is input

	return 0;
}

void PrintMenu(const string &songTitle) {
	cout << songTitle + " PLAYLIST MENU\n"
	     << "a - Add song\n"
	     << "d - Remove song\n"
	     << "c - Change position of song\n"
	     << "s - Output songs by specific artist\n"
	     << "t - Output total time of playlist (in seconds)\n"
	     << "o - Output full playlist\n"
	     << "q - Quit\n\n"
	     << "Choose an option:\n";
}


