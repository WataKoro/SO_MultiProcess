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
        
        int input, i, j;
        printf("Masukkan jumlah fork\n");
        scanf("%d", &input);
        int pid[input];
        printf("mulai \n");
        for(int j=0;j<input;j++){
                switch (pid[i] = fork()) {
                case 0:         /*  proses anak */
                        printf("Proses %d anak \n", j);
                        //isi data di memory map
                        shared[0] = rand()%(100+1-0)+0;
                        shared[1] = rand()%(100+1-0)+0;
                        shared[2] = rand()%(100+1-0)+0;
                        break;
                default:        /*  ortu */
                        printf("Proses %d ortu\n", j);
                        int pidWait,status,jumlah=0;
                        /* wait sampai child selesai */
                        while (pidWait = wait(&status)) {   
                                if (pidWait == pid[i])  /* child sukses selesai*/
                                        //cetak isi memory map
                                        for (int i = 0; i<MSGSIZE; i++) {
                                                printf("ini parent, proses %d child menulis: %d \n", j, shared[i]);
                                                jumlah = jumlah + shared[i];
                                        }
                                break; //keluar dari loop wait
                                
                                if ((pidWait == -1) && (errno != EINTR)) {
                                        /* ada error*/
                                        perror("waitpid");
                                        exit(1);
                                }
                        }
                        printf ("jumlah = %d\n", jumlah);
                break;
                case -1:        /* error */
                        perror("fork");
                        exit(1);
                }
        }
        printf("selesai\n");
        exit(0);
}
