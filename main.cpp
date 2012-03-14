#include <iostream>
#include <stdlib.h>
#include <pthread.h>
#include <string>
#include <sstream>

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
using namespace std;

typedef struct ct_sum{
    int sum;
    pthread_mutex_t lock;
} ct_sum;

typedef struct noct_sum{
    int sum;
} noct_sum;

void * add_one ( void * cnt ) {
    pthread_mutex_lock(&(((ct_sum*)cnt)->lock));
    for ( int i = 0; i < 50; i++ ) {
        (*(ct_sum*)cnt).sum+=i;
    }
    pthread_mutex_unlock(&(((ct_sum*)cnt)->lock));
    pthread_exit(NULL);
    return 0;
}

void * add_two ( void * cnt ) {
    pthread_mutex_lock(&(((ct_sum*)cnt)->lock));
    for ( int i = 0; i < 50; i++ ) {
        (*(ct_sum*)cnt).sum+=i;
    }
    pthread_mutex_unlock(&(((ct_sum*)cnt)->lock));
    pthread_exit(NULL);
    return 0;
}

void *add1(void * cnt){
    for ( int i = 0; i < 50; i++ ) {
        cout << "enter one" << endl;
        (*(ct_sum*)cnt).sum+=i;
    }
}
void *add2(void * cnt){
    for ( int i = 0; i < 50; i++ ) {
        cout << "enter two" << endl;
        (*(ct_sum*)cnt).sum+=i;
    }
}

string itos(long long i){
		stringstream s;
		s << i;
		return s.str();
}
//main function
int main()
{
    in_addr_t temp;
    temp = inet_addr("211.100.7.101");
    cout << temp << endl;
    
    /*
    pthread_t tid;
    tid = pthread_self();
    char s[64];
    sprintf(s,"%lu",tid);
    cout << s << " " << strlen(s);
    noct_sum cnt;
    cnt.sum = 0;
    pthread_t ptid1,ptid2;
    pthread_create(&ptid1,NULL,add1,&cnt);
    pthread_create(&ptid2,NULL,add2,&cnt);
    cout << cnt.sum;
    pthread_t ptid1,ptid2;
    int sum=0;
    ct_sum cnt;
    pthread_mutex_init(&(cnt.lock),NULL);
    cnt.sum=0;
    pthread_create(&ptid1,NULL,add_one,&cnt);
    pthread_create(&ptid2,NULL,add_two,&cnt);
    pthread_mutex_lock(&(cnt.lock));
    printf("sum %d\n",cnt.sum);
    pthread_mutex_unlock(&(cnt.lock));
    pthread_join(ptid1,NULL); //等待线程ptid1结束
    pthread_join(ptid2,NULL); //等待线程ptid2结束
    printf("sum %d\n",cnt.sum);
    pthread_mutex_destroy(&(cnt.lock));
    */
    return 0;
}
