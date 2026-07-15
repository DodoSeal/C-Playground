#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>

// Allow 32kb
char buffer[32768] = "";

void write_file(char *ptr, char *url) {
    char *file_name = strrchr(url, '/') + 1;
    char file_path[512] = "httpFileDownloader/out/";

    strcat(file_path, file_name);

    FILE *file;
    file = fopen(file_path, "w");

    fprintf(file, "%s", ptr);
    fclose(file);

    printf("\nSuccessfully Downloaded file: \"%s\"\nFile Path: \"%s\"\n", file_name, file_path);
};

size_t writer(char *ptr, size_t size, size_t nmemb, void *userdata) {
    size_t total_size = size * nmemb;
    strncat(buffer, ptr, total_size);

    return total_size;
};

/**
 * @param url MUST link to a file
 */
int make_http_request(char *url) {
    CURL *curl;
    CURLcode result = curl_global_init(CURL_GLOBAL_ALL);
    if (result != CURLE_OK) {
        return (int)result;
    };

    curl = curl_easy_init();
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writer);
        
        result = curl_easy_perform(curl);
        if (result != CURLE_OK) {
            printf("\n\nCURL ERROR: %s", curl_easy_strerror(result));
        };

        curl_easy_cleanup(curl);
    };

    curl_global_cleanup();
    write_file(buffer, url);
    
    return (int)result;
};

int main() {
    char user_input[256];

    system("clear");
    printf("\nWelcome to the C File Downloader!");
    printf("\n- Make sure entered file URL links to a file!");
    printf("\n- (ex. https://example.com/index.html)");
    printf("\n\nEnter a URL: ");

    if (fgets(user_input, sizeof(user_input), stdin) != NULL) {
        user_input[strcspn(user_input, "\n \r")] = 0;

        make_http_request(user_input);
    };

    return 0;
};