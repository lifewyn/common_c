#include <stdio.h>
#include <signal.h>
#include <pthread.h>
#include <unistd.h>
#include <stdatomic.h>
#include <string.h>

int signal_flag = 0;

void sig_handler(int signum)
{
    atomic_store(&signal_flag, 1); // 使用原子操作修改全局变量

    // 将信号编号转换为字符串
    char signum_str[10];
    memset(signum_str, '\0', sizeof(signum_str));
    snprintf(signum_str, sizeof(signum_str), "%d", signum);

    // 构造完整的输出消息
    char msg[50];
    memset(msg, '\0', sizeof(msg));
    snprintf(msg, sizeof(msg), "Signal %s received\n", signum_str);

    // 使用 write 将消息写入标准输出
    write(STDOUT_FILENO, msg, strlen(msg));
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