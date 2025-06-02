#include <stdio.h>
#include <signal.h>
#include <pthread.h>
#include <unistd.h>

int signal_flag = 0;

void sig_handler(int signum)
{
    signal_flag = 1;
    printf("Signal %d received\n", signum);
}

void *my_thread(void *arg)
{
    while (1)
    {
        printf("my_thread is online\n");

        if (signal_flag)
        {
            printf("Signal received in thread\n");
            signal_flag = 0;
            break;
        }
        else
        {
            printf("no signal received\n");
            sleep(1);
        }
        
    }

    return NULL;
}

int main(void)
{
    pthread_t thread_id = 0;

    signal(SIGUSR1, sig_handler);

    int ret = pthread_create(&thread_id, NULL, my_thread, NULL);
    if (ret != 0)
    {
        printf("pthread_create error\n");
        return -1;
    }

    printf("Hello, World in parent thread!\n");

    printf("wait for signal send!\n");

    sleep(6);

    printf("Sending SIGUSR1 to thread\n");

    pthread_kill(thread_id, SIGUSR1); // 向线程发送SIGUSR1信号

    pthread_join(thread_id, NULL);
    printf("see you thread!\n");

    return 0;
}