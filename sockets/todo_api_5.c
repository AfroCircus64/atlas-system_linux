#include "todo_api.h"

#define PORT 8080

todo_t *todo_list = NULL;
int next_id = 0;

/**
 * add_todo - Adds a new todo to the list.
 * @title: The title of the todo.
 * @description: The description of the todo.
 *
 * Return: The created todo.
 */
todo_t *add_todo(const char *title, const char *description)
{
    todo_t *new_todo = malloc(sizeof(todo_t));
    if (!new_todo)
        return NULL;

    new_todo->id = next_id++;
    strncpy(new_todo->title, title, sizeof(new_todo->title) - 1);
    strncpy(new_todo->description, description, sizeof(new_todo->description) - 1);
    new_todo->next = todo_list;
    todo_list = new_todo;

    return new_todo;
}

/**
 * get_todos_json - Converts the list of todos to a JSON string.
 *
 * Return: A JSON string representing the list of todos.
 */
char *get_todos_json(void)
{
    char *json = malloc(BUFFER_SIZE);
    if (!json)
        return NULL;

    strcpy(json, "[");
    todo_t *current = todo_list;
    while (current)
    {
        char todo_json[BUFFER_SIZE];
        snprintf(todo_json, sizeof(todo_json),
                 "{\"id\":%d,\"title\":\"%s\",\"description\":\"%s\"}",
                 current->id, current->title, current->description);
        strcat(json, todo_json);
        if (current->next)
            strcat(json, ",");
        current = current->next;
    }
    strcat(json, "]");
    return json;
}

/**
 * handle_client - Handles the client connection.
 * @client_socket: The client socket file descriptor.
 */
void handle_client(int client_socket)
{
    char buffer[BUFFER_SIZE];
    char client_ip[INET_ADDRSTRLEN];
    struct sockaddr_in client_addr;
    socklen_t client_addr_len = sizeof(client_addr);

    /* Get client IP address */
    getpeername(client_socket, (struct sockaddr *)&client_addr, &client_addr_len);
    inet_ntop(AF_INET, &client_addr.sin_addr, client_ip, INET_ADDRSTRLEN);
    printf("Client connected: %s\n", client_ip);

    /* Read the HTTP request */
    if (read_http_request(client_socket, buffer) < 0)
    {
        close(client_socket);
        return;
    }

    /* Print the full HTTP request */
    printf("Raw request: \"%s\"\n", buffer);

    /* Parse the first line of the HTTP request */
    char method[16], path[256], version[16];

    if (sscanf(buffer, "%s %s %s", method, path, version) != 3)
    {
        fprintf(stderr, "Failed to parse HTTP request line\n");
        close(client_socket);
        return;
    }

    if (strcmp(method, "GET") == 0 && strcmp(path, "/todos") == 0)
    {
        /* Retrieve the list of todos */
        char *todos_json = get_todos_json();
        if (!todos_json)
        {
            const char *response = "HTTP/1.1 500 Internal Server Error\r\n\r\n";
            send_http_response(client_socket, response);
            close(client_socket);
            return;
        }

        /* Send 200 OK response with the list of todos */
        char response[BUFFER_SIZE];
        snprintf(response, sizeof(response),
                 "HTTP/1.1 200 OK\r\n"
                 "Content-Type: application/json\r\n\r\n"
                 "%s", todos_json);
        send_http_response(client_socket, response);
        free(todos_json);
    }
    else
    {
        /* Send 404 Not Found response */
        const char *response = "HTTP/1.1 404 Not Found\r\n\r\n";
        send_http_response(client_socket, response);
    }

    /* Close the connection */
    close(client_socket);
}

/**
 * main - Entry point.
 *
 * Return: int Exit status of the program.
 */
int main(void)
{
    int server_fd = create_socket(PORT);

    if (server_fd < 0)
    {
        exit(EXIT_FAILURE);
    }

    printf("Server listening on port %d\n", PORT);

    while (1)
    {
        int client_socket = accept(server_fd, NULL, NULL);

        if (client_socket < 0)
        {
            perror("accept");
            close(server_fd);
            exit(EXIT_FAILURE);
        }
        handle_client(client_socket);
    }

    close(server_fd);
    return (0);
}
