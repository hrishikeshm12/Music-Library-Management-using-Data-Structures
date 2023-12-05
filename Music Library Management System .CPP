
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include<time.h>
#include <ctype.h>
#include <math.h>
#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

#define MAX_SONG_POOL 120
#define MAX_STRING_SIZE 75

#ifdef __unix__
# include <unistd.h>
#elif defined _WIN32
# include <windows.h>
#define sleep(x) Sleep(1000 * (x))
#endif

// Data Structure for an individual song

typedef struct Song *songptr;
typedef struct Song
{
    char title[MAX_STRING_SIZE];
    char album[MAX_STRING_SIZE];
    char uri[MAX_STRING_SIZE];
    char id[MAX_STRING_SIZE];
    short int year;
    double duration;
} Song;

songptr song_pool[MAX_SONG_POOL];
int pool_insert_index = 0;

typedef struct PlaylistNode *node_ptr;
typedef struct PlaylistNode
{
    songptr song;
    node_ptr prev_song;
    node_ptr next_song;
} PlaylistNode;

node_ptr header_node = NULL, now_playing = NULL;

//Function to check if the song pool is empty
bool is_pool_empty()
{
    return song_pool[0] == NULL;
}

//Function to check if playlist exists
bool does_playlist_exist()
{
    return !(header_node == NULL);
}

void play_next_song()
{
    if (does_playlist_exist() && now_playing != NULL)
    {
        if (now_playing->next_song != NULL)
            now_playing = now_playing->next_song;
        else
            printf("REACHED END OF PLAYLIST");
    }
    else
    {
        printf("NO SONG ADDED TO PLAYLIST");
    }
}

void play_prev_song()
{
    if (does_playlist_exist() && now_playing != NULL)
    {
        if (now_playing->prev_song != NULL)
            now_playing = now_playing->prev_song;
        else
            printf("REACHED START OF PLAYLIST");
    }
    else
    {
        printf("NO SONG ADDED TO PLAYLIST");
    }
}

void show_song_details()
{
    if (now_playing == NULL || now_playing->song == NULL)
    {
        printf("                       CREATE A PLAYLIST FIRST\n");
    }
    else
    {
        printf("\n----------------------------------------------------------------------\n");
        printf("                          DETAILED OVERVIEW\n");
        printf("----------------------------------------------------------------------\n");
        printf("\t   TITLE    |   %s\n", now_playing->song->title);
        printf("\t   ALBUM    |   %s\n", now_playing->song->album);
        printf("\t   YEAR     |   %d\n", now_playing->song->year);
        printf("\t  DURATION  |   %0.2lf minutes\n", now_playing->song->duration);
        printf("\tSPOTIFY URI |   %s\n", now_playing->song->uri);
        printf("    Paste the above URI in your browser to play the song on Spotify\n");
        printf("----------------------------------------------------------------------\n");
    }
    char leave[MAX_STRING_SIZE];
    printf("<<<<< Enter any input to return to MAIN MENU\n");
    if (scanf("%s", leave))
    {
        system("cls");
        return;
    }
}

void main_menu()
{
    printf("\n----------------------------------------------------------------------\n");
    printf("                              MAIN MENU\n");
    printf("----------------------------------------------------------------------\n");

    if (now_playing == NULL || now_playing->song == NULL)
    {
        printf("                          NO TRACK SELECTED\n");
    }
    else
    {
        printf("    NOW    |   %s\n", now_playing->song->title);
        printf("  PLAYING  |   %0.2lf minutes\n", now_playing->song->duration);
    }
    printf("----------------------------------------------------------------------\n");
    printf("   #   |  Action   \n");
    printf("----------------------------------------------------------------------\n");
    printf("   1   |  Create a new song\n");
    printf("   2   |  Display all available songs\n");
    if (does_playlist_exist())
        printf("   3   |  Delete playlist\n");
    else
        printf("   3   |  Create a new playlist\n");
    printf("   4   |  Add a song to the playlist\n");
    printf("   5   |  Show playlist\n");
    printf("   6   |  Play previous track\n");
    printf("   7   |  Play next track\n");
    if (now_playing != NULL && now_playing->song != NULL)
        printf("   8   |  Show more information about the song playing\n");
    printf("   9   |  Search a song \n");
    printf("   10  |  Create a binary tree of songs  \n");
    printf("  -1   |  Exit music player\n");
    printf("----------------------------------------------------------------------\n");
    printf("                        Enter your choice below\n");
}

void show_all_songs_raw()
{
    for (int i = 0; i < MAX_SONG_POOL && song_pool[i] != NULL; i++)
        printf("%-1d %-3s %-3s %-3d %0.2lfmin\n", (i + 1), song_pool[i]->title, song_pool[i]->album, song_pool[i]->year, song_pool[i]->duration);
}

void show_playlist()
{
    if (does_playlist_exist())
    {
        printf("\n----------------------------------------------------------------------\n");
        printf("                          YOUR PLAYLIST\n");
        printf("----------------------------------------------------------------------\n");
        printf(" Title                                            | Duration\n");
        printf("----------------------------------------------------------------------\n");
        node_ptr current = header_node;
        while (current != NULL && current->song != NULL)
        {
            node_ptr next = current->next_song;
            printf(" %-48.48s | %2.2lf min\n", current->song->title, current->song->duration);
            current = next;
        }

        printf("----------------------------------------------------------------------");
    }
    else
    {
        printf("\nYou haven't created a playlist yet.\n");
    }
}

void pagewise_song_display(int step)
{
    printf("\n----------------------------------------------------------------------\n");
    printf("                             SONGS LIST\n");
    printf("----------------------------------------------------------------------\n");
    printf("   #   |  Title                                            | Duration\n");
    printf("----------------------------------------------------------------------\n");
    for (int i = step - 10; i < step && song_pool[i] != NULL; i++)
    {
        printf("  %2d   |  %-48.48s | %2.2lf min\n", (i + 1), song_pool[i]->title, song_pool[i]->duration);
    }
    printf("----------------------------------------------------------------------\n");
    printf("[Enter -2 to go to prev page] | Page %d | [Enter -1 to go to next page]\n", ((int)step / 10));
    printf("----------------------------------------------------------------------\n");
    printf(" <<<< Enter 0 to go back to main menu.\n");

    printf("----------------------------------------------------------------------\n");
    printf("                        Enter your choice below\n");
}

int song_selector()
{
    int song_number = -1;
    int step = 10;
    while (song_number < 0 || song_number > pool_insert_index)
    {
        pagewise_song_display(step);
        char input[MAX_STRING_SIZE];
        scanf("%s", input);

        if (!sscanf(input, "%d", &song_number))
        {
            system("cls");
            printf("You seem to have entered an invalid input.\nReturning to main menu.");
            return 0;
        }

        if (song_number == -2)
        {
            if (step > 10)
            {
                step -= 10;
                system("cls");
            }
            else
            {
                system("cls");
                printf("\nThis itself is the first page");
            }
        }
        else if (song_number == -1)
        {
            if (step < ceil(pool_insert_index / 10.0) * 10)
            {
                step += 10;
                system("cls");
            }
            else
            {
                system("cls");
                printf("\nThis is the last page");
            }
        }
        else if (song_number < -2 || song_number > pool_insert_index)
        {
            system("cls");
            printf("\nENTER A VALID CHOICE\n");
        }
    }

    return song_number;
}

Song *createSong(const char *title, const char *album, const short int year, const double duration, const char *uri, const char *id)
{
    Song *temp = (struct Song*)malloc(sizeof(Song));
    strcpy(temp->title, title);
    strcpy(temp->album, album);
    strcpy(temp->uri, uri);
    strcpy(temp->id, id);
    temp->year = year;
    temp->duration = duration;
    pool_insert_index++;
    return temp;
}

//Allocates memory for a new playlist and prompts user to add a song to it
void create_playlist()
{
    int song_number = 0, i = 0;

    node_ptr temp = (node_ptr)malloc(sizeof(PlaylistNode));
    printf("\nPick the song you want to add to your new playlist\n");
    song_number = song_selector();
    if (song_number > 0 && song_number <= 100)
    {
        temp->song = song_pool[song_number - 1];
        temp->prev_song = NULL;
        temp->next_song = NULL;
        header_node = temp;
        now_playing = temp;

        system("cls");
        printf("---\n%s has been added to your new playlist.\n---", song_pool[song_number - 1]->title);
    }
    else if (song_number == 0)
    {
        system("cls");
    }
    else
    {
        printf("\nThere was a problem while handling your request, try again.\n");
    }
}

//Prompts user to pick a song from the pool and add it to the existing playlist
void add_to_playlist()
{
    int song_number = 0;
    int step = 10;
    printf("\nPick the song you want to add\n");
    song_number = song_selector();
    if (song_number > 0 && song_number <= pool_insert_index)
    {
        node_ptr new_node = (node_ptr)malloc(sizeof(PlaylistNode));
        node_ptr last = header_node;
        new_node->song = song_pool[song_number - 1];
        new_node->next_song = NULL;

        /* 4. If the Linked List is empty, then make the new
          node as head */
        if (header_node == NULL)
        {
            new_node->prev_song = NULL;
            header_node = new_node;
            now_playing = new_node;
        }
        else
        {
            //Traverse till the last node
            while (last->next_song != NULL)
                last = last->next_song;

            last->next_song = new_node;
            new_node->prev_song = last;
        }
        system("cls");
        printf("%s has been added to your playlist.\n", song_pool[song_number - 1]->title);
    }
    else if (song_number == 0)
    {
        system("cls");
    }
    else
    {
        printf("\nThere was a problem while handling your request.\n");
    }
}

/** CSV Parser that maps a data set of upto songs onto the song pool
    Songs must be present in the root directory at rawdata.csv
*/
void readFromCSV()
{
    FILE *file = fopen("rawdata.csv", "r");
    char line[1000];
    int i = 0;

    if (file == NULL)
    {
        perror("******\nUnable to load songs from data source");
        printf("Please check if rawdata.csv exists at the root directory of the application.\n");
        printf("You can still enter songs manually.\n******\n");
        printf("Error Message");
    }
    else
    {
        char songtitle[MAX_STRING_SIZE];
        char releaseDate[MAX_STRING_SIZE];
        int durationms;
        double duration = 0.0;
        char id[MAX_STRING_SIZE];
        char album[MAX_STRING_SIZE];
        char uri[MAX_STRING_SIZE];
        int year;
        while (fgets(line, sizeof(line), file) && pool_insert_index < MAX_SONG_POOL)
        {
            char *token;
            token = strtok(line, ","); //tokenizes current line with delimiter ',' and returns the first substring
            if (token == NULL)
                continue;
            strcpy(songtitle, token);
            token = strtok(NULL, ","); // get the next token
            strncpy(releaseDate, token + 1, 4);
            sscanf(releaseDate, "%d", &year);
            token = strtok(NULL, ",");
            char temp[MAX_STRING_SIZE];
            strncpy(temp, token + 1, 6);
            sscanf(temp, "%d", &durationms);
            duration = durationms / 60000.0;
            token = strtok(NULL, ","); // get the next token
            strcpy(id, token);
            token = strtok(NULL, ","); // get the next token
            strcpy(album, token);
            token = strtok(NULL, ","); // get the next token
            strcpy(uri, token);
            token = strtok(NULL, ","); // get the next token
            //printf("Song read : %s  %s\n",songname,durationm);
            if (i == 0)
            {
                i++;
                continue;
            }
            song_pool[i - 1] = createSong(songtitle, album, year, duration, uri, id);
            i++;
        }
    }

    //printf("%d Songs added.\n\n", i);
    fclose(file);
}

//Function that allows the user to create a song of their own
void user_song_input()
{
    int add_another = 1;
    char songname[MAX_STRING_SIZE];
    int year;
    int durationms;
    char id[MAX_STRING_SIZE];
    char album[MAX_STRING_SIZE];
    char uri[MAX_STRING_SIZE] = "spotify:track:";
    double duration = 0.0;

    while (add_another && pool_insert_index < MAX_SONG_POOL)
    {
        system("cls");
        printf("\nEnter the details of the song you want to create.\n[ Don't give spaces between each word, use _ instead\n");

        printf("Title: ");
        scanf("%s", songname);
        printf("Album Name: ");
        scanf("%s", album);
        printf("Year of release: ");
        if (!(scanf("%d", &year)))
        {
            printf("INVALID INPUT ENTERED\n");
            sleep(1);
            break;
        }
        printf("Duration(in s): ");
        if (!(scanf("%d", &durationms)))
        {
            printf("INVALID INPUT ENTERED\n");
            sleep(1);
            break;
        }
        duration = durationms / 60;
        printf("Song ID: ");
        scanf("%s", id);
        strcat(uri, id);
        song_pool[pool_insert_index] = createSong(songname, album, year, duration, uri, id);
        printf("\nThe song %s has been created.\n\n", songname);
        printf("\nDo you want to create another song?\n(Enter 1 for yes and 0 for no) : ");
        scanf("%d", &add_another);
    }
    system("cls");
}

//Helper function to delete the playlist created and free all resources taken up by PlaylistNodes
bool delete_playlist()
{
    if (header_node != NULL)
    {
        node_ptr current = header_node;
        while (current != NULL)
        {
            node_ptr next = current->next_song;
            free(current);
            current = next;
        }
        header_node = NULL;
        now_playing = NULL;
        return true;
    }
    return false;
}

//Frees resources that had been dynamically allocated
void free_all_memory()
{
    delete_playlist();
    for (int i = 0; i < MAX_SONG_POOL && song_pool[i] != NULL; i++)
        free(song_pool[i]);
    printf("\n---END---");

    //Generate a 2 second delay
    sleep(2);
}

void search_song()
{
    char s_name[MAX_STRING_SIZE];
    printf("Enter the song to be searched : " );
    scanf("%s",&s_name);
    int flag=0;

    for(int i=0;i<MAX_SONG_POOL && song_pool[i]!=NULL;i++)
    {
        if(strcmp(s_name,song_pool[i]->title)==0)
        {
            printf("Song found !\n");
            printf(" Name: %-48.48s\n",song_pool[i]->title);
            printf(" Album: %2.2lf min\n",song_pool[i]->duration);
            printf(" year:%d\n",song_pool[i]->year);
            printf(" URI:%s\n",song_pool[i]->uri);
            printf("------------------------------------------\n\n");
            flag=1;
            break;
        }
    }
    if(flag==0)
    {
        printf("Song not found \n");
    }

}

//binary tree of songs

struct song_tree {
  struct song_tree *left,*right;
  char s_title[20],singer[20];

}*Root=NULL;

typedef struct song_tree s_tree;
int check(char[],char[]);
void insert(s_tree *);
void Search();
void view(s_tree *);

int check(char a[],char b[]){
     int i,j,c;
     for(i=0,j=0 ; a[i]!='\0'&&b[j]!='\0' ; i++,j++){
       if(a[i]>b[j]){
         c=1;
         break;
       }
        else if(b[j]>a[i]){
          c=-1;
          break;
        }
      else
         c=0;
     }
     if(c==1)
       return 1;
      else if(c==-1)
        return -1;
      else
        return 0;
}

void Search(){
  int flag=0;
  s_tree *ptr;
  ptr=Root;
  char w[10];
  printf("------------------------------------------------");
  printf("\nEnter song:");
  scanf("%s",w);
  while(ptr!=NULL && flag==0){
    if(check(w,ptr->s_title)>0)
       ptr=ptr->right;
    else if(check(w,ptr->s_title)<0)
          ptr=ptr->left;
    else if(check(w,ptr->s_title)==0){
       flag=1;
       printf("Singer:%s\n",ptr->singer);

    }

    }
    if(flag==0)
      printf("\nSong not found");
}

void insert(s_tree *temp){
  int flag=0;
  s_tree *ptr,*par;
  ptr=Root;

  if(Root==NULL)
     Root=temp;
  else{
     while(ptr!=NULL ){
       if(check(temp->s_title,ptr->s_title)>0){
         par=ptr;
         ptr=ptr->right;
       }

       else if(check(temp->s_title,ptr->s_title)<0)
     {
       par=ptr;
       ptr=ptr->left;
     }
       else if(check(temp->s_title,ptr->s_title)==0){
          flag=1;
            printf("\nSong exists!!");
          break;
       }

   }
       if(flag==0 && ptr==NULL){

         if(check(par->s_title,temp->s_title)==1)
            par->left=temp;
         else if(check(par->s_title,temp->s_title)==-1)
            par->right=temp;
       }

     }

}

void view(s_tree *ptr){
  if(Root==NULL)
    printf("\nEmpty song tree\n");

  else if(ptr !=NULL){
   view(ptr->left);

   printf("\nSong:%s---------------->",ptr->s_title);
   printf("Singer:%s\n",ptr->singer);



   view(ptr->right);
  }

}

int main()
{
    int userChoice = 0;
    char *terminate = "X";
    int wrong_choice_count = 0;
    system("cls");
    readFromCSV();
    while (userChoice != -1)
    {
        switch (userChoice)
        {
        case 0:
        { //Show menu options
            main_menu();
            break;
        }
        case 1:
        {
            system("cls");
            if (pool_insert_index >= MAX_SONG_POOL)
            {
                printf("Cannot add more songs.\n");
            }

            user_song_input();
            break;
        }
        case 2:
        {
            system("cls");
            //show_all_songs();
            int user_song_selection = song_selector();
            system("clear");
            break;
        }
        case 3:
        {
            system("cls");
            if (does_playlist_exist())
            {
                printf("---");
                if (delete_playlist())
                    printf("\nThe playlist was successfully deleted.\n");
                else
                    printf("\nYou haven't created a playlist yet. Nothing to delete\n");

                printf("---");
            }
            else
                create_playlist();
            break;
        }
        case 4:
        {
            system("cls");
            add_to_playlist();
            break;
        }
        case 5:
        {
            system("cls");
            show_playlist();
            break;
        }
        case 6:
        {
            system("cls");
            play_prev_song();
            break;
        }
        case 7:
        {
            system("cls");
            play_next_song();
            break;
        }
        case 8:
        {
            system("cls");
            show_song_details();
            break;
        }
        case 9:
        {
            system("cls");
           clock_t t;
            t = clock();
            search_song();
            t = clock() - t;
            double time_taken = ((double)t)/CLOCKS_PER_SEC; // in seconds

            printf(" Linear search took %f seconds to execute \n", time_taken);
            break;
        }
        case 10:
            {
                 int ch;
              s_tree *temp;
              while(ch!=4){
                printf("\n1.Search\n2.Insert\n3.View\n4.Exit\nYour choice please..");
                scanf("%d",&ch);
                switch (ch)
                 {
                  case 1:
                      {

                        clock_t t;
                        t = clock();
                        Search();
                        t = clock() - t;
                        double time_taken = ((double)t)/CLOCKS_PER_SEC; // in seconds

                        printf("\nSearching in binary tree  took %f seconds to execute \n", time_taken);
                        printf("------------------------------------------------");
                          break;
                      }
                  case 2:
                      {
                          temp=(s_tree*)malloc(sizeof(s_tree));
                          temp->left=NULL;
                          temp->right=NULL;
                          printf("\nInsert song:");
                          scanf("%s",temp->s_title);
                          printf("Insert singer:");
                          scanf("%s",temp->singer);

                   insert(temp);
                  break;
                      }
                  case 3:
                      {
                          view(Root);
                          break;
                      }

                  case 4:
                      {
                          exit(0);
                      }
                }
              }
            }

        default:
        {
            if (wrong_choice_count == 3)
            {
                system("cls");
                printf("Please enter a valid option or the program will terminate.\n");
            }
            if (wrong_choice_count > 3)
            {
                system("cls");
                printf("Sorry you have exceeded the maximum number of retries, terminating..");
                free_all_memory();
                exit(1);
            }
            else
            {
                system("cls");
                printf("Please enter a valid option from the main menu below\n");
            }
            wrong_choice_count++;
            break;
        }
        }
        if (userChoice != 0)
        {
            main_menu();
        }

        char input[MAX_STRING_SIZE];
        scanf("%s", input);

        if (!sscanf(input, "%d", &userChoice))
        {
            system("cls");
            printf("----\nINVALID INPUT\n");
            userChoice = 0;
            wrong_choice_count++;
            if (wrong_choice_count > 3)
            {
                printf("Sorry you have exceeded the maximum number of retries, terminating..");
                free_all_memory();
                exit(1);
            }
            continue;
        }
    }
    free_all_memory();

    return 0;
