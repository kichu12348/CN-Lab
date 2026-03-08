#include <stdio.h>
#include <stdlib.h>

int main()
{
    int capacity;   // bucket size
    int out_rate;   // leak rate
    int bucket = 0; // current packets in bucket
    int incoming;   // packets arriving per second
    int seconds;

    printf("Enter bucket capacity: ");
    scanf("%d", &capacity);

    printf("Enter output rate (packets/sec): ");
    scanf("%d", &out_rate);

    printf("Enter number of seconds to simulate: ");
    scanf("%d", &seconds);

    for (int i = 1; i <= seconds; i++)
    {
        printf("\nSecond %d\n", i);

        printf("Enter incoming packets: ");
        scanf("%d", &incoming);

        // Add incoming packets
        if (bucket + incoming <= capacity)
        {
            bucket += incoming;
            printf("All %d packets added to bucket.\n", incoming);
        }
        else
        {
            int accepted = capacity - bucket;
            bucket = capacity;
            printf("%d packets added, %d packets dropped (overflow).\n",
                   accepted, incoming - accepted);
        }

        // Leak packets
        if (bucket >= out_rate)
        {
            bucket -= out_rate;
            printf("%d packets sent.\n", out_rate);
        }
        else
        {
            printf("%d packets sent.\n", bucket);
            bucket = 0;
        }

        printf("Packets remaining in bucket: %d\n", bucket);
    }

    return 0;
}