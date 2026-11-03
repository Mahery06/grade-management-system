#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>
#include "head file/student.h"

// 用于接收返回数据的回调函数
static size_t WriteCallback(char *contents, size_t size, size_t nmemb, void *userdata) {
    (void)userdata;
    size_t realsize = size * nmemb;
    printf("%.*s", (int)realsize, contents); // 直接打印返回内容
    return realsize;
}

void tailored_report(Student stu[], int n) {
    char p[1500] = "";

    for (int i = 0; i < n; i++) {
        snprintf(p + strlen(p), sizeof(p) - strlen(p), "%s %g\\n", stu[i].name, stu[i].score);
    }

    CURL *curl;
    CURLcode resp;
    struct curl_slist *headers = NULL;

    curl = curl_easy_init();
    if (curl == NULL) {
        printf("curl init failed!\n");
        return;
    }

    curl_easy_setopt(curl, CURLOPT_URL, "https://api.deepseek.com/chat/completions");

    // 2. 设置请求头
    headers = curl_slist_append(headers, "Content-Type: application/json");
    char w[300] = "Authorization: Bearer ";
    char *key = getenv("api_key");
    if (key == NULL) {
        printf("The environment variable api_key is not set, so the report cannot be generated.\n");
        curl_easy_cleanup(curl);
        return;
    }
    strncat(w, key, sizeof(w) - strlen(w) - 1);
    headers = curl_slist_append(headers, w);
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

    // 3. 设置 POST 请求体（JSON 数据）
    char mes[1700] = "{\"model\": \"deepseek-flash\", \"messages\": [{\"role\": \"user\", \"content\": \"帮我按照每一位同学对应的高三数学分数(在对应后方,满分100),给每一个同学指定规划。结构为:学生姓名,具体规划内容。";
    char *rear = strcat(p, "\"}]}");
    const char *json_payload = strcat(mes, rear);
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, json_payload);

    // 4. 设置接收响应的回调函数
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);

    // 执行请求
    resp = curl_easy_perform(curl);
    if (resp != CURLE_OK) {
        fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(resp));
    }

    // 清理资源
    curl_slist_free_all(headers);
    curl_easy_cleanup(curl);
}
