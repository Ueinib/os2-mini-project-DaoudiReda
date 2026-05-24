#include <stdio.h>

#include <stdlib.h>

#include <pthread.h>

#include <unistd.h>

#include <time.h>

#include <semaphore.h>

#define FOOTBALL_PLAYERS 8

#define SM_PLAYERS 4

#define NFS_PLAYERS 4

sem_t mutex;

sem_t console;

sem_t football_slots;

sem_t sm_slots;

sem_t nfs_slots;

int football_count = 0;

int sm_count = 0;

int nfs_count = 0;

/* ================= FOOTBALL ================= */

void enter_F_game()

{

    sem_wait(&football_slots);

    sem_wait(&mutex);

    if (football_count == 0)

    {

        sem_wait(&console);

    }

    football_count++;

    printf("[Football] Entered | Current players = %d\n",

           football_count);

    sem_post(&mutex);

}

void quit_F_game()

{

    sem_wait(&mutex);

    football_count--;

    printf("[Football] Left | Current players = %d\n",

           football_count);

    if (football_count == 0)

    {

        sem_post(&console);

    }

    sem_post(&mutex);

    sem_post(&football_slots);

}

/* ================= SUPER MARIO ================= */

void enter_SM_game()

{

    sem_wait(&sm_slots);

    sem_wait(&mutex);

    if (sm_count == 0)

    {

        sem_wait(&console);

    }

    sm_count++;

    printf("[SuperMario] Entered | Current players = %d\n",

           sm_count);

    sem_post(&mutex);

}

void quit_SM_game()

{

    sem_wait(&mutex);

    sm_count--;

    printf("[SuperMario] Left | Current players = %d\n",

           sm_count);

    if (sm_count == 0)

    {

        sem_post(&console);

    }

    sem_post(&mutex);

    sem_post(&sm_slots);

}

/* ================= NFS ================= */

void enter_NFS_game()

{

    sem_wait(&nfs_slots);

    sem_wait(&mutex);

    if (nfs_count == 0)

    {

        sem_wait(&console);

    }

    nfs_count++;

    printf("[NFS] Entered | Current players = %d\n",

           nfs_count);

    sem_post(&mutex);

}

void quit_NFS_game()

{

    sem_wait(&mutex);

    nfs_count--;

    printf("[NFS] Left | Current players = %d\n",

           nfs_count);

    if (nfs_count == 0)

    {

        sem_post(&console);

    }

    sem_post(&mutex);

    sem_post(&nfs_slots);

}

/* ================= THREAD FUNCTIONS ================= */

void* football_player(void* arg)

{

    int id = *(int*)arg;

    printf("[Football] Player %d waiting\n", id);

    enter_F_game();

    printf("[Football] Player %d playing\n", id);

    sleep(rand() % 3 + 1);

    printf("[Football] Player %d finished\n", id);

    quit_F_game();

    free(arg);

    return NULL;

}

void* supermario_player(void* arg)

{

    int id = *(int*)arg;

    printf("[SuperMario] Player %d waiting\n", id);

    enter_SM_game();

    printf("[SuperMario] Player %d playing\n", id);

    sleep(rand() % 3 + 1);

    printf("[SuperMario] Player %d finished\n", id);

    quit_SM_game();

    free(arg);

    return NULL;

}

void* nfs_player(void* arg)

{

    int id = *(int*)arg;

    printf("[NFS] Player %d waiting\n", id);

    enter_NFS_game();

    printf("[NFS] Player %d playing\n", id);

    sleep(rand() % 3 + 1);

    printf("[NFS] Player %d finished\n", id);

    quit_NFS_game();

    free(arg);

    return NULL;

}

/* ================= MAIN ================= */

int main()

{

    srand(time(NULL));

    pthread_t football[FOOTBALL_PLAYERS];

    pthread_t sm[SM_PLAYERS];

    pthread_t nfs[NFS_PLAYERS];

    sem_init(&mutex, 0, 1);

    sem_init(&console, 0, 1);

    sem_init(&football_slots, 0, 4);

    sem_init(&sm_slots, 0, 2);

    sem_init(&nfs_slots, 0, 1);

    int i;

    /* Create Football threads */

    for(i = 0; i < FOOTBALL_PLAYERS; i++)

    {

        int* id = malloc(sizeof(int));

        *id = i;

        pthread_create(&football[i], NULL,

                       football_player, id);

    }

    /* Create Super Mario threads */

    for(i = 0; i < SM_PLAYERS; i++)

    {

        int* id = malloc(sizeof(int));

        *id = i;

        pthread_create(&sm[i], NULL,

                       supermario_player, id);

    }

    /* Create NFS threads */

    for(i = 0; i < NFS_PLAYERS; i++)

    {
int* id = malloc(sizeof(int));

        *id = i;

        pthread_create(&nfs[i], NULL,

                       nfs_player, id);

    }

    /* Join Football threads */

    for(i = 0; i < FOOTBALL_PLAYERS; i++)

    {

        pthread_join(football[i], NULL);

    }

    /* Join Super Mario threads */

    for(i = 0; i < SM_PLAYERS; i++)

    {

        pthread_join(sm[i], NULL);

    }

    /* Join NFS threads */

    for(i = 0; i < NFS_PLAYERS; i++)

    {

        pthread_join(nfs[i], NULL);

    }

    sem_destroy(&mutex);

    sem_destroy(&console);

    sem_destroy(&football_slots);

    sem_destroy(&sm_slots);

    sem_destroy(&nfs_slots);

    return 0;

}


