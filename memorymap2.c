#include <sys/mman.h>   /* mmap()  */
#include <stdlib.h>     /* exit() */
#include <unistd.h>     /* fork() and getpid() */
#include <stdio.h>      /* printf() */
#include <sys/wait.h>   /*wait*/
#include <errno.h>        /* errno */

#define MSGSIZE 3

int main(int argc, char **argv) {

        printf("mulai \n");

        int size = MSGSIZE * sizeof(int);
        //buat memory map
        void *addr = mmap(0, size, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
        printf("Mapped at %p\n", addr);
        int *shared = addr;
        
        int produsen, konsumen, i, j;
        printf("Masukkan jumlah fork produsen\n");
        scanf("%d", &produsen);
        printf("Masukkan jumlah fork konsumen\n");
        scanf("%d", &konsumen);
        int pid;

        printf("mulai \n");
        switch (pid = fork()) {
        case 0:         /*  proses anak */
                for(i = 0; i < produsen; i++){
                        fork();
                }

                //isi data di memory map
                srand(getpid());
                for(i = 0; i < MSGSIZE; i++){
                        shared[i] = rand()%(20+1-0)+0;
                        printf("Produsen %d menulis %d\n", getpid(), shared[i]);
                        sleep(1);
                }
                break;
        default:        /*  ortu */
                for(j = 0; j < konsumen; j++){
                        fork();
                }

                int jumlah = 0;
                for(j = 0; j < MSGSIZE; j++){
                        printf("Konsumen %d mengambil %d\n", getpid(), shared[j]);
                        jumlah = jumlah + shared[j];
                        sleep(1);
                }
                printf ("jumlah %d = %d\n", getpid(), jumlah);
        break;
        case -1:        /* error */
                perror("fork");
                exit(1);
        }

        //printf("selesai\n");
        exit(0);
}