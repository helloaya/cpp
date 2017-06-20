#include <zmq.h>
#include <unistd.h>
#include <string.h>
#include "req_response.h"
#include "pub_sub.h"




int main(int n, char** args) {
	if (3 != n) {
		printf ("invalid args\n");
		return -1;
	}

    /// 测试req-rep模式
    if (!strcmp (args[1], "reqrep")) {
        if (!strcmp (args[2], "client")) {
            return do_client ();
        }

        if (!strcmp (args[2], "server")) {
            return do_server ();
        }
    }

    /// 测试pub subscriber模式
    if (!strcmp (args[1], "pubsub")) {
        if (!strcmp (args[2], "pub")) {
            return do_pub ();
        }

        if (!strcmp (args[2], "sub")) {
            return do_sub ();
        }
    }
	

	printf ("invalid args\n");
	return -1;
}
