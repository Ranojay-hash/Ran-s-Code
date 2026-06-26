#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct Song
{
    char title[100];
    struct Song *prev;
    struct Song *next;
};

struct Song *head = NULL;
struct Song *tail = NULL;
struct Song *current = NULL;

// Create New Song Node
struct Song* createSong(char title[])
{
    struct Song *newSong = (struct Song*)malloc(sizeof(struct Song));

    strcpy(newSong->title, title);
    newSong->prev = NULL;
    newSong->next = NULL;

    return newSong;
}

// Count Songs
int getCount()
{
    int count = 0;
    struct Song *temp = head;

    while(temp != NULL)
    {
        count++;
        temp = temp->next;
    }

    return count;
}

// Insert at Beginning
void insertAtBeginning()
{
    char title[100];

    printf("Enter Song Name: ");
    getchar();
    fgets(title, sizeof(title), stdin);
    title[strcspn(title, "\n")] = '\0';

    struct Song *newSong = createSong(title);

    if(head == NULL)
    {
        head = tail = current = newSong;
    }
    else
    {
        newSong->next = head;
        head->prev = newSong;
        head = newSong;
    }
    printf("Song Added at Beginning Successfully!\n");
}


// Insert at End
void insertAtEnd()
{
    char title[100];

    printf("Enter Song Name: ");
    getchar();
    fgets(title, sizeof(title), stdin);
    title[strcspn(title, "\n")] = '\0';

    struct Song *newSong = createSong(title);

    if(head == NULL)
    {
        head = tail = current = newSong;
    }
    else
    {
        tail->next = newSong;
        newSong->prev = tail;
        tail = newSong;
    }

    printf("Song Added at End Successfully!\n");
}

// Insert at Nth Position
void insertAtPosition()
{
    int pos;

    printf("Enter Position: ");
    scanf("%d", &pos);

    int count = getCount();

    if(pos < 1 || pos > count + 1)
    {
        printf("Invalid Position!\n");
        return;
    }

    if(pos == 1)
    {
        insertAtBeginning();
        return;
    }
    if(pos == count + 1)
    {
        insertAtEnd();
        return;
    }

    char title[100];

    printf("Enter Song Name: ");
    getchar();
    fgets(title, sizeof(title), stdin);
    title[strcspn(title, "\n")] = '\0';

    struct Song *newSong = createSong(title);

    struct Song *temp = head;

    for(int i = 1; i < pos - 1; i++)
    {
        temp = temp->next;
    }

    newSong->next = temp->next;
    newSong->prev = temp;

    temp->next->prev = newSong;
    temp->next = newSong;

    printf("Song Inserted Successfully at Position %d!\n", pos);
}

// Display Playlist
void displayPlaylist()
{
    if(head == NULL)
    {
        printf("Playlist Empty!\n");
        return;
    }

    struct Song *temp = head;

    printf("\n----- PLAYLIST -----\n");

    while(temp != NULL)
    {
        printf("%s\n", temp->title);
        temp = temp->next;
    }

    printf("------------------\n");
}

// Search Song
void searchSong()
{
    char title[100];

    printf("Enter Song Name to Search: ");
    getchar();
    fgets(title, sizeof(title), stdin);
    title[strcspn(title, "\n")] = '\0';

    struct Song *temp = head;
    int pos = 1;

    while(temp != NULL)
    {
        if(strcmp(temp->title, title) == 0)
        {
            printf("Song Found at Position %d\n", pos);
            return;
        }

        temp = temp->next;
        pos++;
    }
    printf("Song Not Found!\n");
}


// Delete Song
void deleteSong()
{
    if(head == NULL)
    {
        printf("Playlist Empty!\n");
        return;
    }

    char title[100];

    printf("Enter Song Name to Delete: ");
    getchar();
    fgets(title, sizeof(title), stdin);
    title[strcspn(title, "\n")] = '\0';

    struct Song *temp = head;

    while(temp != NULL)
    {
        if(strcmp(temp->title, title) == 0)
        {
            if(temp == head)
            {
                head = head->next;

                if(head != NULL)
                    head->prev = NULL;
            }
            else
            {
                temp->prev->next = temp->next;
            }

            if(temp == tail)
            {
                tail = temp->prev;

                if(tail != NULL)
                    tail->next = NULL;
            }
            else if(temp->next != NULL)
            {
                temp->next->prev = temp->prev;
            }

            if(current == temp)
                current = head;

            free(temp);

            printf("Song Deleted Successfully!\n");
            return;
        }

        temp = temp->next;
    }

    printf("Song Not Found!\n");
}

// Count Songs
void countSongs()
{
    printf("Total Songs = %d\n", getCount());
}

// Current Song
void showCurrentSong()
{
    if(current == NULL)
    {
        printf("Playlist Empty!\n");
        return;
    }

    printf("Currently Playing: %s\n", current->title);
}

// Play Next Song
void playNextSong()
{
    if(current == NULL)
    {
        printf("Playlist Empty!\n");
        return;
    }

    if(current->next == NULL)
    {
        printf("Already at Last Song!\n");
        return;
    }

    current = current->next;

    printf("Now Playing: %s\n", current->title);
}

// Play Previous Song
void playPreviousSong()
{
    if(current == NULL)
    {
        printf("Playlist Empty!\n");
        return;
    }

    if(current->prev == NULL)
    {
        printf("Already at First Song!\n");
        return;
    }

    current = current->prev;

    printf("Now Playing: %s\n", current->title);
}


//Shuffle Playlist
void shufflePlaylist()
{
    int count = getCount();

    if(count <= 1)
    {
        printf("Not enough songs to shuffle!\n");
        return;
    }

    struct Song *songs[count];
    struct Song *temp = head;

    int i = 0;

    while(temp != NULL)
    {
        songs[i++] = temp;
        temp = temp->next;
    }

    srand(time(NULL));

    for(i = count - 1; i > 0; i--)
    {
        int j = rand() % (i + 1);

        char tempTitle[100];

        strcpy(tempTitle, songs[i]->title);
        strcpy(songs[i]->title, songs[j]->title);
        strcpy(songs[j]->title, tempTitle);
    } printf("Playlist Shuffled Successfully!\n");
}


//Save Playlist to File
void savePlaylistToFile()
{
    FILE *fp;

    fp = fopen("playlist.txt", "w");

    if(fp == NULL)
    {
        printf("Unable to Create File!\n");
        return;
    }

    struct Song *temp = head;

    while(temp != NULL)
    {
        fprintf(fp, "%s\n", temp->title);
        temp = temp->next;
    }

    fclose(fp);

    printf("Playlist Saved Successfully in playlist.txt\n");
}


int main()
{
    int choice;

    while(1)
    {
        printf("\n====== MUSIC MANAGEMENT SYSTEM ======\n");
        printf("1. Insert Song at Beginning\n");
        printf("2. Insert Song at End\n");
        printf("3. Insert Song at Nth Position\n");
        printf("4. Delete Song\n");
        printf("5. Search Song\n");
        printf("6. Display Playlist\n");
        printf("7. Play Next Song\n");
        printf("8. Play Previous Song\n");
        printf("9. Count Total Songs\n");
        printf("10. Show Current Song\n");
        printf("11. Shuffle Playlist\n");
        printf("12. Save Playlist To File\n");
        printf("13. Exit\n");

        printf("Enter Choice: ");
        scanf("%d", &choice);


        switch(choice)
        {
            case 1:
                insertAtBeginning();
                break;

            case 2:
                insertAtEnd();
                break;

            case 3:
                insertAtPosition();
                break;

            case 4:
                deleteSong();
                break;

            case 5:
                searchSong();
                break;
            case 6:
                displayPlaylist();
                break;

            case 7:
                playNextSong();
                break;

            case 8:
                playPreviousSong();
                break;

            case 9:
                countSongs();
                break;

            case 10:
                showCurrentSong();
                break;

            case 11:
                shufflePlaylist();
                break;

            case 12:
                 savePlaylistToFile();
                break;

            case 13:
                printf("Thank You!\n");
                exit(0);

            default:
                printf("Invalid Choice!\n");
        }
    }

    return 0;
}