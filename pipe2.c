#include <stdlib.h>     /* exit() */
#include <unistd.h>     /* fork() and getpid() */
#include <stdio.h>      /* printf() */
#include <string.h>
#include <sys/wait.h>   /* wait */
#include <errno.h>      /* errno */
#include <unistd.h>     /* sleep() */

#define MSGSIZE 5

int main(int argc, char **argv) {
        //char inbuf[MSGSIZE]; //buffer
        int arrInt[MSGSIZE];
        int fd[2]; //pipe
        //create pipe
        if (pipe(fd) < 0) {
            exit(1); //error
        }
        int produsen, konsumen, i, j;
        printf("Masukkan jumlah fork produsen\n");
        scanf("%d", &produsen);
        printf("Masukkan jumlah fork konsumen\n");
        scanf("%d", &konsumen);

        int pid;
        int pidWait, status;
        printf("mulai \n");
        switch (pid = fork()) {
        case 0:         /* fork returns 0 ke proses anak */
            for(i = 0; i < produsen; i++){
                fork();
            }
            
            // tulis data ke pipe
            srand(getpid());
            for(i = 0; i < MSGSIZE; i++){
                arrInt[i] = rand()%(20+1-0)+0;
                printf("Produsen %d menulis %d\n", getpid(), arrInt[i]);
                sleep(1);
            }
            close(fd[0]);
            write(fd[1], arrInt, sizeof(arrInt));
            break;

        default:        /* fork returns pid ke proses ortu */
            for(j = 0; j < konsumen; j++){
                fork();
            }
            int jumlah = 0;
            // baca yang ditulis child dari pipe
            close(fd[1]);
            read(fd[0], arrInt, sizeof(arrInt));
            for(j = 0; j < MSGSIZE; j++){
                printf("Konsumen %d mengambil %d\n", getpid(), arrInt[j]);
                jumlah = jumlah+arrInt[j];
                sleep(1);
            }
            printf("jumlah : %d\n", jumlah);

            break;

        case -1:        /* error */
            perror("fork");
            exit(1);
        }

        
        //printf("selesai\n");
        exit(0);
}
