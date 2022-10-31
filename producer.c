
#include "shareContent.c"
//generating a random string
static char *rand_string(char* str,size_t size)
{

    const char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJK.?";
    if (size) {
        --size;
        for (size_t n = 0; n < size; n++) {
            int key = rand() % (int) (sizeof charset - 1);
            str[n] = charset[key];
        }
        str[size] = '\0';
    }
    return str;
}


int main(int argc, char* argv[])
{
    
    struct sharedContent* shms = getSharedContent();

    char s[MES_SIZE];
    int messageCount = atoi(argv[1]);
    int in = shms->in;

    for(int j = 0 ; j < messageCount; j++)
    {
        rand_string(s,MES_SIZE);
        //full > 0? minus full to 1 : wait;
        sem_wait(&(shms->full));
        size_t len = strlen(s);
        memcpy(shms->sharedMem[in], s, len + 1);
        printf("added %s\n",shms->sharedMem[in]);
        in = (in + 1)%2;
        shms->in = in;
        // signal the empty
        sem_post(&(shms->empty));
        sem_post(&(shms->mutex)); 
    }
    return 0;
}
