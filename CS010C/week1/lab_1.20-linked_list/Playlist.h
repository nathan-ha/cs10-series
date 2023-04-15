#pragma once
#include <string>

class PlaylistNode {
private:
	std::string uniqueID;
	std::string songName;
	std::string artistName;
	int songLength;
	PlaylistNode* nextNodePtr;
public:
	PlaylistNode();
	PlaylistNode(const std::string &uniqueID, const std::string &songName, const std::string &artistName, int songLength);
	void InsertAfter(PlaylistNode* inputNode);
	void SetNext(PlaylistNode* inputNode);
	const std::string &GetID() const;
	const std::string &GetSongName() const;
	const std::string &GetArtistName() const;
	int GetSongLength() const;
	PlaylistNode* GetNext() const;
	void PrintPlaylistNode() const;
};

class Playlist {
private:
	PlaylistNode* head;
	PlaylistNode* tail;
	//not allowing copies and assignments by making them private
	Playlist(const Playlist &origList);
	Playlist &operator=(const Playlist &rhs);
public:
	Playlist();
	~Playlist();
	void addSong(const std::string &uniqueID, const std::string &songName, const std::string &artistName, int songLength);
	void removeSong(const std::string &targetID, std::string &songName);
	void changePositionOfSong(int currPosition, int newPosition, std::string &songName, int numNodes);
	void outputSongsByArtist(const std::string &inputArtist) const;
	void outputTotalSeconds() const;
	void outputFullPlaylist() const;
};

