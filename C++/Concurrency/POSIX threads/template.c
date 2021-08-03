#include <pthread.h>
#include <stdio.h>

#define ANZAHL 100000 /* eventuell höher setzen */

int zaehler;  /* wird durch die Threads hochgezählt */
void *zaehl_thread(void *);
pthread_mutex_t zaehler_mutex = PTHREAD_MUTEX_INITIALIZER;

int main(void)
{
   pthread_t id1, id2;
   pthread_create(&id1, NULL, &zaehl_thread, NULL);
   pthread_create(&id2, NULL, &zaehl_thread, NULL);
   pthread_join(id1, NULL);
   pthread_join(id2, NULL);

   fprintf(stderr, "zaehler = %d\n", zaehler);
   return 0;
}

void *zaehl_thread(void *unbenutzt)
{
   int i, zahl;
   for (i = 0; i < ANZAHL; i++)
   {
      pthread_mutex_lock(&zaehler_mutex);
      zahl = zaehler;
      fprintf(stderr, "\r %7d", zahl+1);
      zaehler = zahl + 1;
      pthread_mutex_unlock(&zaehler_mutex);
   }
   fprintf(stderr, "........... Thread %d fertig (zaehler = %d)\n",
            (int)pthread_self(), zaehler);
   return NULL;
}
