#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>


#define OPENAI_URL "https://api.openai.com/v1/chat/completions"

struct string {
    char *ptr;
    size_t len;
};

void init_string(struct string *s) {
    s->len = 0;
    s->ptr = malloc(1);
    if (s->ptr == NULL) {
        fprintf(stderr, "Erro ao alocar memória.\n");
        exit(EXIT_FAILURE);
    }
    s->ptr[0] = '\0';
}

size_t write_callback(void *ptr, size_t size, size_t nmemb, struct string *s) {
    size_t new_len = s->len + size * nmemb;
    s->ptr = realloc(s->ptr, new_len + 1);
    if (s->ptr == NULL) {
        fprintf(stderr, "Erro ao realocar memória.\n");
        exit(EXIT_FAILURE);
    }
    memcpy(s->ptr + s->len, ptr, size * nmemb);
    s->ptr[new_len] = '\0';
    s->len = new_len;

    return size * nmemb;
}

int main(int argc, char *argv[]) {
    const char *OPENAI_API_KEY = getenv("OPENAI_API_KEY");

    if (!OPENAI_API_KEY) {
        fprintf(stderr, "Erro: variável de ambiente OPENAI_API_KEY não definida.\n");
        return 1;
    }

    if (argc < 2) {
        fprintf(stderr, "Uso: wa <mensagem>\n");
        return 1;
    }

    int total_len = 0;
    for (int i = 1; i < argc; ++i) total_len += strlen(argv[i]) + 1;

    char *text = malloc(total_len);
    if (!text) {
        fprintf(stderr, "Erro de alocação.\n");
        return 1;
    }
    text[0] = '\0';
    for (int i = 1; i < argc; ++i) {
        strcat(text, argv[i]);
        if (i < argc - 1) strcat(text, " ");
    }

    char json[4096];
    snprintf(json, sizeof(json),
        "{ \"model\": \"gpt-3.5-turbo\", \"messages\": [{\"role\": \"user\", \"content\": \"%s\"}] }",
        text
    );

    CURL *curl = curl_easy_init();
    struct curl_slist *headers = NULL;
    struct string response;

    if (curl) {
        init_string(&response);

        headers = curl_slist_append(headers, "Content-Type: application/json");
        char auth_header[256];
        snprintf(auth_header, sizeof(auth_header), "Authorization: Bearer %s", OPENAI_API_KEY);
        headers = curl_slist_append(headers, auth_header);

        curl_easy_setopt(curl, CURLOPT_URL, OPENAI_URL);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, json);
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

        CURLcode res = curl_easy_perform(curl);
        if (res != CURLE_OK) {
            fprintf(stderr, "Erro: %s\n", curl_easy_strerror(res));
        } else {
            // Procura pela resposta do ChatGPT
            char *start = strstr(response.ptr, "\"content\":\"");
            if (start) {
                start += strlen("\"content\":\"");
                char *end = strchr(start, '"');
                if (end) *end = '\0';
                printf("\nResposta do ChatGPT:\n%s\n", start);
            } else {
                printf("Resposta bruta:\n%s\n", response.ptr);
            }
        }

        curl_easy_cleanup(curl);
        curl_slist_free_all(headers);
        free(response.ptr);
    }

    free(text);
    return 0;
}
