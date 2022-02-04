#include <iostream>
#include "mongoose.h"
#include "Params.h"
#include "APIv1.h"
#include "HomvHandler.h"
Params params =  Params();
APIv1 apIv1 = APIv1();
HomvHandler *homvHandler;

static void fn(struct mg_connection *c, int ev, void *ev_data, void *fn_data) {
    if (ev == MG_EV_ACCEPT && fn_data != NULL) {
        /*struct mg_tls_opts opts = {
                //.ca = "ca.pem",         // Uncomment to enable two-way SSL
                .cert = "server.pem",     // Certificate PEM file
                .certkey = "server.pem",  // This pem conains both cert and key
        };*/
        struct mg_tls_opts opts;
        opts.cert = "server.pem";
        opts.certkey = "server.pem";
        mg_tls_init(c, &opts);

    } else if (ev == MG_EV_HTTP_MSG) {
        struct mg_http_message *hm = (struct mg_http_message *) ev_data;
        std::string method = std::string(hm->method.ptr, hm->method.len);

        if (mg_http_match_uri(hm, "/apiv1/conf")) {
            if (method == "GET") {
                mg_http_reply(c, 200, "Content-Type: application/json;\r\n", "%s", apIv1.getConfig().c_str());

            } else if (method == "PUT") {
                apIv1.putConfig(hm->body.ptr);
                mg_printf(c, "HTTP/1.1 200 OK\r\nContent-Length: 0\r\n\r\n");
            } else {
                mg_http_reply(c, 405, "", "%s", "Method Not Allowed \n");  // Serve REST
            }
        } else if (mg_http_match_uri(hm, "/apiv1/update")) {
            if (method == "GET") {
                mg_http_reply(c, 200, "", "{\"result\": \"%.*s\"}\n", (int) hm->uri.len,
                              hm->uri.ptr);
            }
        } else if (mg_http_match_uri(hm, "/apiv1/apply")) {
            if (method == "POST") {
               homvHandler->rerun();
                mg_printf(c, "HTTP/1.1 200 OK\r\nContent-Length: 0\r\n\r\n");
            } else {
                mg_http_reply(c, 405, "", "%s", "Method Not Allowed \n");  // Serve REST
            }
        } else {
            struct mg_http_serve_opts opts = {.root_dir = params.getWebPath().c_str()};
            mg_http_serve_dir(c, (mg_http_message *) ev_data, &opts);
        }
    }
    (void) fn_data;
}


int main(int argc, char *argv[]) {
    homvHandler= new HomvHandler(argc, argv);
    struct mg_mgr mgr;                            // Event manager
    mg_log_set("2");                              // Set to 3 to enable debug
    mg_mgr_init(&mgr);                            // Initialise event manager
    std::cout << "Attempt to start server at ip: " <<  params.getHttpAddr() << std::endl;
    mg_http_listen(&mgr, params.getHttpAddr().c_str(), fn, NULL);  // Create HTTP listener
    //mg_http_listen(&mgr, params->getHttpsAddr().c_str(), fn, (void *) 1);  // HTTPS listener
    std::cout << "Server run" << std::endl;
    for (;;) mg_mgr_poll(&mgr, 1000);                    // Infinite event loop
    mg_mgr_free(&mgr);
    return 0;
}

