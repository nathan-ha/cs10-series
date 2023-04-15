#include <iostream>
#include "Playlist.h"

//I am sleep deprived pls have mercy on my grade

PlaylistNode::PlaylistNode() :
    uniqueID("none"),
    songName("none"),
    artistName("none"),
    songLength(0),
    nextNodePtr(nullptr)
{}

PlaylistNode::PlaylistNode(const std::string &uniqueID, const std::string &songName, const std::string &artistName, int songLength) :
    uniqueID(uniqueID),
    songName(songName),
    artistName(artistName),
    songLength(songLength),
    nextNodePtr(nullptr)
{}

//I'm assuming we're inserting the input node after the "this" object
void PlaylistNode::InsertAfter(PlaylistNode* inputNode) {
    PlaylistNode* newNode = new PlaylistNode(*inputNode); //this shallow copy should be fine since the next pointer is being adjusted after this
    //connects the new node to the nodes around it
    newNode->SetNext(nextNodePtr);
    nextNodePtr = newNode; 
}

void PlaylistNode::SetNext(PlaylistNode* inputNode) {
    nextNodePtr = inputNode;
}

PlaylistNode* PlaylistNode::GetNext() const {
    return nextNodePtr;
}

const std::string &PlaylistNode::GetID() const {
    return uniqueID;
}

const std::string &PlaylistNode::GetSongName() const {
    return songName;
}

const std::string &PlaylistNode::GetArtistName() const {
    return artistName;
}

int PlaylistNode::GetSongLength() const {
    return songLength;
}

void PlaylistNode::PrintPlaylistNode() const {
    std::cout
        << "Unique ID: " + uniqueID << '\n'
        << "Song Name: " + songName << '\n'
        << "Artist Name: " + artistName << '\n'
        << "Song Length (in seconds): " << songLength 
        << std::endl << std::endl;
}

Playlist::Playlist() : head(nullptr), tail(nullptr) {}

Playlist::~Playlist() {
    while (head != nullptr) {
        //deletes each node until end of list is reached
        PlaylistNode* victim = head;
        head = head->GetNext();
        delete victim;
    }
    head = nullptr;
    tail = nullptr;
}

void Playlist::addSong(const std::string &uniqueID, const std::string &songName, const std::string &artistName, int songLength) {
    PlaylistNode* newNode = new PlaylistNode(uniqueID, songName, artistName, songLength);
    if (head == nullptr) { //if list is empty, point head and tail to the new node
        head = newNode;
        tail = newNode;
        return;
    }
    //connect (old) last element with new last element
    tail->SetNext(newNode);
    tail = newNode;
}

void Playlist::removeSong(const std::string &targetID, std::string &songName) {
    if (head == nullptr) return; //edge case: empty
    //edge case: head is the target
    if (head->GetID() == targetID) {
        songName = head->GetSongName(); //make sure to save the name before deleting it
        //remove head
        PlaylistNode* victim = head;
        head = head->GetNext();
        delete victim;
        if (head == nullptr) { //if now empty, set tail to nullptr
            tail = nullptr;
        }
        return;
    }

    //look for target node and delete it
    PlaylistNode* prev = head;
    for (PlaylistNode* p = head->GetNext(); p != nullptr; p = p->GetNext()) {
        if (p->GetID() == targetID) {
            songName = p->GetSongName();
            prev->SetNext(p->GetNext()); //connect nodes around target
            if (p == tail) {
                tail = prev; //before we delete last node, re-point tail
            }
            delete p;
            return; //only deleting one node
        }
        prev = p;
    }

}

void Playlist::outputFullPlaylist() const {
    if (head == nullptr) {
        std::cout << "Playlist is empty\n\n";
        return;
    }
    //print info about every node
    int i = 1;
    for (PlaylistNode* p = head; p != nullptr; p = p->GetNext()) {
        std::cout << i << ".\n";
        p->PrintPlaylistNode();
        i++;
    }
}

void Playlist::changePositionOfSong(int currPosition, int newPosition, std::string &songName, int numNodes) {
    if (currPosition == newPosition ||currPosition < 1 || currPosition > numNodes) return; //don't change anything if they are the same position or currPosition is out of bounds
    //search for node at current positon
    PlaylistNode* currNode = head;
    PlaylistNode* prev = nullptr;
    int i = 1;
    for (PlaylistNode* p = head; p != nullptr; p = p->GetNext()) {
        if (i == currPosition) {
            currNode = p;
            break;
        }
        prev = p;
        i++;
    }
    songName = currNode->GetSongName();

    //detatch currNode so it's floating in memory
    if (currNode == head) { //edge cases: detatching the head or tail
        head = head->GetNext();
        currNode->SetNext(nullptr);
    } else {
        prev->SetNext(currNode->GetNext());
        currNode->SetNext(nullptr);
        if (tail == currNode) tail = prev; //re-point tail if we detatched the tail
    }

    //insert the node back into list at new position
    
    //edge case: new position too small or at head
    if (newPosition <= 1) {
        //move the node to head
        currNode->SetNext(head);
        head = currNode;
        return;
    }
    //edge case: index too big or at tail
    if (newPosition >= numNodes) {
        tail->SetNext(currNode);
        tail = currNode;
        tail->SetNext(nullptr);
        return;
    }
    //general case: insert the input node directly BEfORE the node that is currently at input index
    i = 1;
    for (PlaylistNode* p = head; p->GetNext() != nullptr; p = p->GetNext()) {
        //since we're inserting behind the index, check one index ahead
        if (i + 1 == newPosition) {
            currNode->SetNext(p->GetNext());
            p->SetNext(currNode);
            return;
        }
        i++;
    }
}

void Playlist::outputSongsByArtist(const std::string &inputArtist) const {
    int i = 1;
    for (PlaylistNode* p = head; p != nullptr;  p = p->GetNext()) {
        //same as the other output function except we only output specific ones
        if (p->GetArtistName() == inputArtist) {
            std::cout << i << ".\n"; 
            p->PrintPlaylistNode();
        }
        i++; 
    }
}

void Playlist::outputTotalSeconds() const {
    int totalTime = 0;
    //sums lengths of all songs
    for (PlaylistNode* p = head; p != nullptr; p = p->GetNext()) {
        totalTime += p->GetSongLength();
    }
    std::cout << "Total time: " << totalTime << " seconds\n\n";
}