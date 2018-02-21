#ifndef SERVER_H
#define SERVER_H

#include <libwebsockets.h>

typedef struct server_client_t {
	struct lws *socket;
	struct server_client_t *next;
} client_t;

client_t *client_insert(client_t **head, struct lws *socket);
void client_remove(client_t **head, struct lws *socket);
#define client_foreach(HEAD, CLIENT) for(client_t *CLIENT = HEAD; CLIENT; CLIENT = CLIENT->next)

typedef enum {
	server_type_text = LWS_WRITE_TEXT,
	server_type_binary = LWS_WRITE_BINARY
} server_data_type_t;

typedef struct server_t {
	struct lws_context *context;
	size_t buffer_size;
	unsigned char *send_buffer_with_padding;
	unsigned char *send_buffer;
	void *user;

	int port;
	struct server_client_t *clients;

	void (*on_connect)(struct server_t *server, struct lws *wsi);
	void (*on_message)(struct server_t *server, struct lws *wsi, void *in, size_t len);
	void (*on_close)(struct server_t *server, struct lws *wsi);
	int (*on_http_req)(struct server_t *server, struct lws *wsi, char *request);
} server_t;

server_t *server_create(int port, size_t buffer_size);
void server_destroy(server_t *self);
char *server_get_host_address(server_t *self);
char *server_get_client_address(server_t *self, struct lws *wsi);
void server_update(server_t *self);
void server_send(server_t *self, struct lws *socket, void *data, size_t size, server_data_type_t type);
void server_broadcast(server_t *self, void *data, size_t size, server_data_type_t type);

#endif
