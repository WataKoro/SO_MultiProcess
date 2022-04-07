#include <stdlib.h>     /* exit() */
#include <unistd.h>     /* fork() and getpid() */
#include <stdio.h>      /* printf() */
#include <string.h>

#define MSGSIZE 3

int main(int argc, char **argv) {
        char inbuf[MSGSIZE]; //buffer
        int fd[2]; //pipe
        //create pipe
        if (pipe(fd) < 0) {
            exit(1); //error
        }
        int input, j;
        printf("Masukkan jumlah fork\n");
        scanf("%d", &input);
        int pid[input];
        printf("mulai \n");
        for(j=0; j<input; j++){
            switch (pid[j] = fork()) {
            case 0:         /* fork returns 0 ke proses anak */
                printf("");
                // tulis data ke pipe
                srand(getpid());
                int arrIntChild[MSGSIZE] = {rand()%(100+1-0)+0 ,rand()%(100+1-0)+0,rand()%(100+1-0)+0};
                write(fd[1], arrIntChild, sizeof(arrIntChild));
                for (int i = 0; i<MSGSIZE; i++) {
                    printf("proses %d %d child menulis: %d \n", j, getpid(), arrIntChild[i]);
                }
                break;

            default:        /* fork returns pid ke proses ortu */
                printf("");
                int arrIntParent[MSGSIZE];
                int jumlah = 0;
                // baca yang ditulis child dari pipe
                read(fd[0], arrIntParent, sizeof(arrIntParent));
                for (int i = 0; i<MSGSIZE; i++) {
                    printf("proses %d %d parent membaca: %d \n", j, getpid(), arrIntParent[i]);
                    jumlah = jumlah + arrIntParent[i];
                }
                printf ("jumlah proses ke %d = %d\n", getpid(), jumlah);
                break;

            case -1:        /* error */
                perror("fork");
                exit(1);
            }
        }

        
        printf("selesai\n");
        exit(0);
}