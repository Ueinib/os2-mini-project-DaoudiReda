//exercice 1

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>

#define FOOTBALL_PLAYERS 8
#define SM_PLAYERS 4
#define NFS_PLAYERS 4

void* football_player(void* arg)
{
    int id = *(int*)arg;

    printf("[Football] Player %d is waiting to play\n", id);

    sleep(rand() % 3 + 1);

    printf("[Football] Player %d is done playing\n", id);

    free(arg);
    return NULL;
}

void* supermario_player(void* arg)
{
    int id = *(int*)arg;

    printf("[SuperMario] Player %d is waiting to play\n", id);

    sleep(rand() % 3 + 1);

    printf("[SuperMario] Player %d is done playing\n", id);

    free(arg);
    return NULL;
}

void* nfs_player(void* arg)
{
    int id = *(int*)arg;

    printf("[NFS] Player %d is waiting to play\n", id);

    sleep(rand() % 3 + 1);

    printf("[NFS] Player %d is done playing\n", id);

    free(arg);
    return NULL;
}

int main()
{
    srand(time(NULL));

    pthread_t football[FOOTBALL_PLAYERS];
    pthread_t sm[SM_PLAYERS];
    pthread_t nfs[NFS_PLAYERS];

    int i;

    // Create Football threads
    for(i = 0; i < FOOTBALL_PLAYERS; i++)
    {
        int* id = malloc(sizeof(int));
        *id = i;

        pthread_create(&football[i], NULL, football_player, id);
    }

    // Create Super Mario threads
    for(i = 0; i < SM_PLAYERS; i++)
    {
        int* id = malloc(sizeof(int));
        *id = i;

        pthread_create(&sm[i], NULL, supermario_player, id);
    }

    // Create NFS threads
    for(i = 0; i < NFS_PLAYERS; i++)
    {
        int* id = malloc(sizeof(int));
        *id = i;

        pthread_create(&nfs[i], NULL, nfs_player, id);
    }

    // Join Football threads
    for(i = 0; i < FOOTBALL_PLAYERS; i++)
    {
        pthread_join(football[i], NULL);
    }

    // Join Super Mario threads
    for(i = 0; i < SM_PLAYERS; i++)
    {
        pthread_join(sm[i], NULL);
    }

    // Join NFS threads
    for(i = 0; i < NFS_PLAYERS; i++)
    {
        pthread_join(nfs[i], NULL);
    }

    return 0;
}

