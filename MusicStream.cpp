#include "MusicStream.h"

#include <iostream>

void MusicStream::addProfile(const std::string &email, const std::string &username, SubscriptionPlan plan) {
    /* TODO */
    Profile newProfile(email,username,plan);
    profiles.insertAtTheEnd(newProfile);
}

void MusicStream::deleteProfile(const std::string &email) {
    /* TODO */
    Node<Profile>* current = profiles.getFirstNode();
    while(true)
    {
        if(current->data.getEmail()==email)
        {

            //*** First Step ***///
            if(!(current->data.getFollowers().isEmpty()))
            {
                Node<Profile*>* current_follower = current->data.getFollowers().getFirstNode();
                Node<Profile*>* first_follower = current->data.getFollowers().getFirstNode();
                // Unfollow the profile from all followers but the last one
                while(current_follower->next != first_follower)
                {
                    current_follower->data->unfollowProfile(&(current->data));
                    current_follower = current_follower->next;
                }
                // Unfollow the profile from the last follower
                current_follower->data->unfollowProfile(&(current->data));
                current_follower = NULL;
                first_follower = NULL;
            }
            

            //*** Second Step ***//
            if(!(current->data.getFollowings().isEmpty()))
            {
                Node<Profile*>* current_following = current->data.getFollowings().getFirstNode();
                Node<Profile*>* first_following = current->data.getFollowings().getFirstNode();
                //  Deleting the user from its followings’ list of followers except the last followed profile
                while(current_following->next != first_following)
                {
                    if(!(current_following->data->getFollowers().isEmpty()))
                    {
                        Node<Profile*>* current_follower_of_the_following = current_following->data->getFollowers().getFirstNode();
                        Node<Profile*>* first_follower_of_the_following = current_following->data->getFollowers().getFirstNode();
                        bool isRemoved = false;
                        while(current_follower_of_the_following->next != first_follower_of_the_following)
                        {
                            if(current_follower_of_the_following->data->getEmail() == email)
                            {
                                current_following->data->getFollowers().removeNode(current_follower_of_the_following);
                                first_follower_of_the_following = NULL;
                                current_follower_of_the_following = NULL;
                                isRemoved = true;
                                break;
                            }
                            current_follower_of_the_following = current_follower_of_the_following->next;
                        }
                        if(!isRemoved)
                        {
                            if(current_follower_of_the_following->data->getEmail() == email)
                            {
                                current_following->data->getFollowers().removeNode(current_follower_of_the_following);
                                first_follower_of_the_following = NULL;
                                current_follower_of_the_following = NULL;
                            }
                        }
                    }
                    current_following = current_following->next;
                    
                }

                //  Deleting the user from its last following's list of followers
                if(!(current_following->data->getFollowers().isEmpty()))
                {
                    Node<Profile*>* current_follower_of_the_following = current_following->data->getFollowers().getFirstNode();
                    Node<Profile*>* first_follower_of_the_following = current_following->data->getFollowers().getFirstNode();
                    bool isRemoved = false;
                    while(current_follower_of_the_following->next != first_follower_of_the_following)
                    {
                        if(current_follower_of_the_following->data->getEmail() == email)
                        {
                            current_following->data->getFollowers().removeNode(current_follower_of_the_following);
                            first_follower_of_the_following = NULL;
                            current_follower_of_the_following = NULL;
                            isRemoved = true;
                            break;
                        }
                        current_follower_of_the_following = current_follower_of_the_following->next;
                    }
                    if(!isRemoved)
                    {
                        if(current_follower_of_the_following->data->getEmail() == email)
                        {
                            current_following->data->getFollowers().removeNode(current_follower_of_the_following);
                            first_follower_of_the_following = NULL;
                            current_follower_of_the_following = NULL;
                        }
                    }
                }
            } 

            //*** Third Step **//
            current->data.getFollowers().~LinkedList();
            current->data.getFollowings().~LinkedList();
            current->data.getPlaylists().~LinkedList();
            
            profiles.removeNode(current);

            break;
        }
        current = current->next;
    } 
}

void MusicStream::addArtist(const std::string &artistName) {
    /* TODO */
    Artist newArtist(artistName);
    artists.insertAtTheEnd(newArtist);
}

void MusicStream::addAlbum(const std::string &albumName, int artistId) {
    /* TODO */
    Album newAlbum(albumName);
    Node<Artist>* current = artists.getFirstNode();
    albums.insertAtTheEnd(newAlbum);
    
    while(true)
    {
        if(current->data.getArtistId()==artistId)
        {
            current->data.addAlbum(&(albums.getNode(newAlbum)->data));
            break;
        }
        current = current->next;
    }
    
    
}

void MusicStream::addSong(const std::string &songName, int songDuration, int albumId) {
    /* TODO */
    Song newSong(songName,songDuration);
    Node<Album>* current = albums.getFirstNode();
    songs.insertAtTheEnd(newSong);
    
    while(true)
    {
        if(current->data.getAlbumId()==albumId)
        {
            current->data.addSong(&(songs.getNode(newSong)->data));
            break;
        }
        current = current->next;
    }
    
    
}

void MusicStream::followProfile(const std::string &email1, const std::string &email2) {
    /* TODO */
    Node<Profile>* p1 = profiles.getFirstNode();
    Node<Profile>* p2 = profiles.getFirstNode();

    while(true)
    {
        if(p1->data.getEmail()==email1)
        {
            break;
        }
        p1 = p1->next;
    }
    while(true)
    {
        if(p2->data.getEmail()==email2)
        {
            break;
        }
        p2 = p2->next;
    }
    p1->data.followProfile(&(p2->data));
    p2->data.getFollowers().insertAtTheEnd(&(p1->data));
}

void MusicStream::unfollowProfile(const std::string &email1, const std::string &email2) {
    /* TODO */
    Node<Profile>* p1 = profiles.getFirstNode();
    Node<Profile>* p2 = profiles.getFirstNode();

    while(true)
    {
        if(p1->data.getEmail()==email1)
        {
            break;
        }
        p1 = p1->next;
    }
    while(true)
    {
        if(p2->data.getEmail()==email2)
        {
            break;
        }
        p2 = p2->next;
    }
    p1->data.unfollowProfile(&(p2->data));
    p2->data.getFollowers().removeNode(&(p1->data));
}

void MusicStream::createPlaylist(const std::string &email, const std::string &playlistName) {
    /* TODO */
    Node<Profile>* current_profile = profiles.getFirstNode();
    while(true)
    {
        if(current_profile->data.getEmail()==email)
        {
            break;
        }
        current_profile = current_profile->next;
    }    

    current_profile->data.createPlaylist(playlistName);
}

void MusicStream::deletePlaylist(const std::string &email, int playlistId) {
    /* TODO */
    
    Node<Profile>* current_profile = profiles.getFirstNode();
    while(true)
    {
        if(current_profile->data.getEmail()==email)
        {
            break;
        }
        current_profile = current_profile->next;
    }    
    
    current_profile->data.deletePlaylist(playlistId);
}

void MusicStream::addSongToPlaylist(const std::string &email, int songId, int playlistId) {
    /* TODO */
    
    Node<Profile>* current_profile = profiles.getFirstNode();
    while(true)
    {
        if(current_profile->data.getEmail()==email)
        {
            break;
        }
        current_profile = current_profile->next;
    }
    Node<Song> *newSong = songs.getFirstNode();
    while(true)
    {
        if(newSong->data.getSongId() == songId)
        {
            break;
        }
        newSong = newSong->next;
    }

    current_profile->data.getPlaylist(playlistId)->addSong(&(newSong->data));  
    
}

void MusicStream::deleteSongFromPlaylist(const std::string &email, int songId, int playlistId) {
    /* TODO */
    
    Node<Profile>* current_profile = profiles.getFirstNode();
    while(true)
    {
        if(current_profile->data.getEmail()==email)
        {
            break;
        }
        current_profile = current_profile->next;
    }
    Node<Song> *newSong = songs.getFirstNode();
    while(true)
    {
        if(newSong->data.getSongId() == songId)
        {
            break;
        }
        newSong = newSong->next;
    }
    current_profile->data.deleteSongFromPlaylist(&(newSong->data),playlistId);
    
}

LinkedList<Song *> MusicStream::playPlaylist(const std::string &email, Playlist *playlist) {
    /* TODO */
    /*
    Node<Profile>* current_profile = profiles.getFirstNode();
    
    while(true)
    {
        if(current_profile->data.getEmail()==email)
        {
            break;
        }
        current_profile = current_profile->next;
    }
    if(current_profile->data.getPlan() == premium )
    {
        return playlist->getSongs();
    }
    else {
        LinkedList<Song *> result = playlist->getSongs();
        result.insertAsEveryKthNode(&(Song::ADVERTISEMENT_SONG),2);
        return result;
    }
    */
    Node<Profile>* current_profile = profiles.getFirstNode();
    
    while(true)
    {
        if(current_profile->data.getEmail()==email)
        {
            break;
        }
        current_profile = current_profile->next;
    }

    LinkedList<Song *> result;
    if(current_profile->data.getPlaylists().getNode(*playlist))
    {
        result = current_profile->data.getPlaylists().getNode(*playlist)->data.getSongs();
    }
    else if(current_profile->data.getSharedPlaylists().getNode(playlist))
    {
        result = current_profile->data.getSharedPlaylists().getNode(playlist)->data->getSongs();
    }


    if(current_profile->data.getPlan() != premium )
    {
        result.insertAsEveryKthNode(&(Song::ADVERTISEMENT_SONG),2);
    }

    return result;
    
}

Playlist *MusicStream::getPlaylist(const std::string &email, int playlistId) {
    /* TODO */
    Node<Profile>* current_profile = profiles.getFirstNode();
    while(true)
    {
        if(current_profile->data.getEmail()==email)
        {
            break;
        }
        current_profile = current_profile->next;
    }

    return current_profile->data.getPlaylist(playlistId);
}

LinkedList<Playlist *> MusicStream::getSharedPlaylists(const std::string &email) {
    /* TODO */
    
    LinkedList<Playlist *> result;
    
    Node<Profile>* current_profile = profiles.getFirstNode();
    while(true)
    {
        if(current_profile->data.getEmail()==email)
        {
            break;
        }
        current_profile = current_profile->next;
    }
    return current_profile->data.getSharedPlaylists();
    
}

void MusicStream::shufflePlaylist(const std::string &email, int playlistId, int seed) {
    /* TODO */
    Node<Profile>* current_profile = profiles.getFirstNode();
    while(true)
    {
        if(current_profile->data.getEmail()==email)
        {
            break;
        }
        current_profile = current_profile->next;
    }
    current_profile->data.getPlaylist(playlistId)->shuffle(seed);
}

void MusicStream::sharePlaylist(const std::string &email, int playlistId) {
    /* TODO */
    
    Node<Profile>* current_profile = profiles.getFirstNode();
    
    while(true)
    {
        if(current_profile->data.getEmail()==email)
        {
            break;
        }
        current_profile = current_profile->next;
    }
    
    current_profile->data.getPlaylist(playlistId)->setShared(true);
}

void MusicStream::unsharePlaylist(const std::string &email, int playlistId) {
    /* TODO */
    
    Node<Profile>* current_profile = profiles.getFirstNode();
    
    while(true)
    {
        if(current_profile->data.getEmail()==email)
        {
            break;
        }
        current_profile = current_profile->next;
    }
    
    current_profile->data.getPlaylist(playlistId)->setShared(false);
}

void MusicStream::subscribePremium(const std::string &email) {
    /* TODO */
    
    Node<Profile>* current_profile = profiles.getFirstNode();
    int size = profiles.getSize();
    for(int i = 0; i<size; i++)
    {
        if(current_profile->data.getEmail()==email)
        {
            break;
        }
        current_profile = current_profile->next;
    }
    if(current_profile->data.getPlan()!=premium)
    {
        current_profile->data.setPlan(premium);
    }
}

void MusicStream::unsubscribePremium(const std::string &email) {
    /* TODO */
    
    Node<Profile>* current_profile = profiles.getFirstNode();
    int size = profiles.getSize();
    for(int i = 0; i<size; i++)
    {
        if(current_profile->data.getEmail()==email)
        {
            break;
        }
        current_profile = current_profile->next;
    }
    
    if(current_profile->data.getPlan()!=free_of_charge)
    {
        current_profile->data.setPlan(free_of_charge);
    }
    
}

void MusicStream::print() const {
    std::cout << "# Printing the music stream ..." << std::endl;

    std::cout << "# Number of profiles is " << this->profiles.getSize() << ":" << std::endl;
    this->profiles.print();

    std::cout << "# Number of artists is " << this->artists.getSize() << ":" << std::endl;
    this->artists.print();

    std::cout << "# Number of albums is " << this->albums.getSize() << ":" << std::endl;
    this->albums.print();

    std::cout << "# Number of songs is " << this->songs.getSize() << ":" << std::endl;
    this->songs.print();

    std::cout << "# Printing is done." << std::endl;
}
