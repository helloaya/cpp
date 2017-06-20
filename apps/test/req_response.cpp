#include "req_response.h"
#include <zmq.h>
#include <unistd.h>
#include <string.h>


int do_client (){
	printf ("Connecting to hello world server…\n");
    void *context = zmq_ctx_new ();
    void *requester = zmq_socket (context, ZMQ_REQ);
    zmq_connect (requester, "tcp://35.185.158.58:5555");

    int request_nbr;
    for (request_nbr = 0; request_nbr != 1000; request_nbr++) {
        char buffer [10];
        printf ("Sending Hello %d…\n", request_nbr);
        zmq_send (requester, "Hello", 5, 0);
        
        zmq_recv (requester, buffer, 10, 0);
        printf ("Received World %d\n", request_nbr);

    }
    zmq_close (requester);
    zmq_ctx_destroy (context);
	return 0;
}

int do_server () {
	//  Socket to talk to clients
    void *context = zmq_ctx_new ();
    void *responder = zmq_socket (context, ZMQ_REP);
    int rc = zmq_bind (responder, "tcp://*:5555");
    while (1) {
        char buffer [10]={0,};
        printf ("Wait for resp\n");
        zmq_recv (responder, buffer, 10, 0);
        printf ("Received %s\n", buffer);
        zmq_send (responder, "World", 5, 0);
    }
	return 0;
}