#include "Profile.h"

Profile::Profile(const std::string &email, const std::string &username, SubscriptionPlan plan) {
    this->email = email;
    this->username = username;
    this->plan = plan;
}

const std::string &Profile::getUsername() const {
    return this->username;
}

const std::string &Profile::getEmail() const {
    return this->email;
}

SubscriptionPlan Profile::getPlan() const {
    return this->plan;
}

LinkedList<Playlist> &Profile::getPlaylists() {
    return this->playlists;
}

LinkedList<Profile *> &Profile::getFollowings() {
    return this->following;
}

LinkedList<Profile *> &Profile::getFollowers() {
    return this->followers;
}

void Profile::setPlan(SubscriptionPlan plan) {
    this->plan = plan;
}

void Profile::followProfile(Profile *profile) {
    /* TODO */
    following.insertAtTheEnd(profile);
}

void Profile::unfollowProfile(Profile *profile) {
    /* TODO */
    following.removeNode(profile);
}

void Profile::createPlaylist(const std::string &playlistName) {
    /* TODO */
    Playlist newPlaylist(playlistName);
    playlists.insertAtTheEnd(newPlaylist);
}

void Profile::deletePlaylist(int playlistId) {
    /* TODO */
    Playlist to_del = *getPlaylist(playlistId);
    
    to_del.getSongs().~LinkedList();
    playlists.removeNode(to_del);
}

void Profile::addSongToPlaylist(Song *song, int playlistId) {
    /* TODO */
    (this->getPlaylist(playlistId))->addSong(song);
}

void Profile::deleteSongFromPlaylist(Song *song, int playlistId) {
    /* TODO */
    getPlaylist(playlistId)->getSongs().removeNode(song);
}

Playlist *Profile::getPlaylist(int playlistId) {
    /* TODO */
    Node<Playlist>* current = playlists.getFirstNode();
    Playlist* result;
    while(true)
    {
        if(playlistId == current->data.getPlaylistId())
        {
            break;
        }  
        current = current->next;
    }
    result = &(current->data);
    return result;
}

LinkedList<Playlist *> Profile::getSharedPlaylists() {
    /* TODO */
    LinkedList<Playlist *> result;

    if(following.isEmpty())
    {
        return result;
    }
    
    Node<Profile*> *head = following.getFirstNode();
    Node<Profile*> *current = following.getFirstNode();

    if(!following.isEmpty())
    {
        do{
            Node<Playlist>* current_playlist = current->data->playlists.getFirstNode();
            Node<Playlist>* first_playlist = current->data->playlists.getFirstNode();
            if(!current->data->playlists.isEmpty())
            {
                do{
                    if(current_playlist->data.isShared())
                    {
                        result.insertAtTheEnd(&(current_playlist->data));
                    }
                    current_playlist = current_playlist->next;
                } while(current_playlist->next != first_playlist);
                
                if(current_playlist->data.isShared())
                {
                    result.insertAtTheEnd(&(current_playlist->data));
                }
            }
            current = current->next;
        } while(current->next != head);
        
        Node<Playlist>* current_playlist = current->data->playlists.getFirstNode();
        Node<Playlist>* first_playlist = current->data->playlists.getFirstNode();
        if(!current->data->playlists.isEmpty())
        {
            do{
                if(current_playlist->data.isShared())
                {
                    result.insertAtTheEnd(&(current_playlist->data));
                }
                current_playlist = current_playlist->next;
            } while(current_playlist->next != first_playlist);
                
            if(current_playlist->data.isShared())
            {
                result.insertAtTheEnd(&(current_playlist->data));
            }
        }
    }
    return result;
}

void Profile::shufflePlaylist(int playlistId, int seed) {
    /* TODO */
    getPlaylist(playlistId)->shuffle(seed);
}

void Profile::sharePlaylist(int playlistId) {
    /* TODO */
    getPlaylist(playlistId)->setShared(true);
}

void Profile::unsharePlaylist(int playlistId) {
    /* TODO */
    getPlaylist(playlistId)->setShared(false);
}

bool Profile::operator==(const Profile &rhs) const {
    return this->email == rhs.email && this->username == rhs.username && this->plan == rhs.plan;
}

bool Profile::operator!=(const Profile &rhs) const {
    return !(rhs == *this);
}

std::ostream &operator<<(std::ostream &os, const Profile &profile) {
    os << "email: " << profile.email << " |";
    os << " username: " << profile.username << " |";
    if (profile.plan == free_of_charge) {
        os << " plan: " << "free_of_charge" << " |";
    } else if (profile.plan == premium) {
        os << " plan: " << "premium" << " |";
    } else {
        os << " plan: " << "undefined" << " |";
    }

    os << " playlists: [";
    Node<Playlist> *firstPlaylistNode = profile.playlists.getFirstNode();
    Node<Playlist> *playlistNode = firstPlaylistNode;
    if (playlistNode) {
        do {
            os << playlistNode->data;
            if (playlistNode->next != firstPlaylistNode) os << ", ";
            playlistNode = playlistNode->next;
        } while (playlistNode != firstPlaylistNode);
    }
    os << "] |";
    os << " following: [";
    Node<Profile *> *firstProfileNode = profile.following.getFirstNode();
    Node<Profile *> *profileNode = firstProfileNode;
    if (profileNode) {
        do {
            os << profileNode->data->getEmail();
            if (profileNode->next != firstProfileNode) os << ", ";
            profileNode = profileNode->next;
        } while (profileNode != firstProfileNode);
    }
    os << "] |";
    os << " followers: [";
    firstProfileNode = profile.followers.getFirstNode();
    profileNode = firstProfileNode;
    if (profileNode) {
        do {
            os << profileNode->data->getEmail();
            if (profileNode->next != firstProfileNode) os << ", ";
            profileNode = profileNode->next;
        } while (profileNode != firstProfileNode);
    }
    os << "]";

    return os;
}
