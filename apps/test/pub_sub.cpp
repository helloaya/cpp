#include "pub_sub.h"
#include <zmq.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>


int do_pub() {
	//  Prepare our context and publisher
    void *context = zmq_ctx_new ();
    void *publisher = zmq_socket (context, ZMQ_PUB);
    int rc = zmq_bind (publisher, "tcp://*:5555");

    //  Initialize random number generator
    srandom ((unsigned) time (NULL));
    while (1) {
        //  Get values that will fool the boss
        int zipcode, temperature, relhumidity;
        zipcode     = rand () % 100000;
        temperature = rand () % 215 - 80;
        relhumidity = rand () % 50 + 10;

        //  Send message to all subscribers
        char update [20];
        sprintf (update, "%05d %d %d", zipcode, temperature, relhumidity);
        printf ("sending..\n");
        zmq_send (publisher, update, strlen(update), 0);
        printf ("done...waiting...\n");
        sleep (5);
    }
    zmq_close (publisher);
    zmq_ctx_destroy (context);
    return 0;
}

int do_sub () {
	//  Socket to talk to server
    printf ("Collecting updates from weather server…\n");
    void *context = zmq_ctx_new ();
    void *subscriber = zmq_socket (context, ZMQ_SUB);
    int rc = zmq_connect (subscriber, "tcp://35.185.158.58:5555");

    //  Subscribe to zipcode, default is NYC, 10001
    char *filter = "demo";
    rc = zmq_setsockopt (subscriber, ZMQ_SUBSCRIBE,
                         filter, strlen (filter));

    //  Process 100 updates
    int update_nbr;
    long total_temp = 0;
    for (update_nbr = 0; update_nbr < 100; update_nbr++) {
        char string[20] = {0,};

        zmq_recv (subscriber, string, 20, 0);

        int zipcode, temperature, relhumidity;
        sscanf (string, "%d %d %d",
            &zipcode, &temperature, &relhumidity);
        total_temp += temperature;
        free (string);
    }
    printf ("Average temperature for zipcode '%s' was %dF\n",
        filter, (int) (total_temp / update_nbr));

    zmq_close (subscriber);
    zmq_ctx_destroy (context);
    return 0;
}
