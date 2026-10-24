#include <stdio.h>
#include <string.h>

struct Message
{
    char text[100];
};

int main()
{
    struct Message msg;

    printf("Enter message: ");
    gets(msg.text);

    printf("\nProducer: Message sent: %s\n", msg.text);
    printf("Consumer: Message received: %s\n", msg.text);

    return 0;
}
