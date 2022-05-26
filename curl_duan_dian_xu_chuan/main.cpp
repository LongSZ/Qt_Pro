#include "curlduandianxuchuan.h"

#include <QApplication>

#include <stdio.h>
#include <curl.h>
#include <stdlib.h>
#include <easy.h>;

//这个函数为CURLOPT_HEADERFUNCTION参数构造，从http头部获取文件size
size_t getcontentlengthfunc(void *ptr, size_t size, size_t nmemb, void *stream) {
    /* _snscanf() is Win32 specific */
    long len = 0;
    int r = sscanf((const char *const)ptr, "Content-Length: %ld\n", &len);
    if (r) {                        // Microsoft: we don't read the specs
        *((long *) stream) = len;
    }
    return size * nmemb;
}

// 保存下载文件
size_t wirtefunc(void *ptr, size_t size, size_t nmemb, void *stream) {
    cout << "size = " << size << endl;
    return fwrite(ptr, size, nmemb, (FILE *)stream);
}

// 读取上传文件
size_t readfunc(void *ptr, size_t size, size_t nmemb, void *stream) {
    FILE *fp = (FILE *)stream;
    if (ferror(fp)) {
        return CURL_READFUNC_ABORT;
    }
    size_t n = fread(ptr, size, nmemb, fp) * size;
    return n;
}
 
// 下载 或者上传文件函数
int download(CURL *curlhandle, const char *remotepath, const char *localpath, long timeout, long tries) {
    //得到本地文件大小
    struct stat file_info;
    curl_off_t local_file_len = -1;
    int use_resume = 0;
    if (stat(localpath, &file_info) == 0) {
        local_file_len =  file_info.st_size;
        use_resume  = 1;
        cout << "use_resume = " << use_resume << endl;
    }
    
    //采用追加方式打开文件，便于实现文件断点续传工作
    FILE *fp = fopen(localpath, "ab+"); 
    if (fp == NULL) {
        perror(NULL);
        return 0;
    }

    //curl_easy_setopt(curlhandle, CURLOPT_UPLOAD, 1L);
    curl_easy_setopt(curlhandle, CURLOPT_URL, remotepath);
    curl_easy_setopt(curlhandle, CURLOPT_CONNECTTIMEOUT, timeout);  // 设置连接超时，单位秒
    //设置http 头部处理函数
    long filesize = 0 ;
    curl_easy_setopt(curlhandle, CURLOPT_HEADERFUNCTION, getcontentlengthfunc);
    curl_easy_setopt(curlhandle, CURLOPT_HEADERDATA, &filesize);
    // 设置文件续传的位置给libcurl
    curl_easy_setopt(curlhandle, CURLOPT_RESUME_FROM_LARGE, use_resume ? local_file_len : 0);
    curl_easy_setopt(curlhandle, CURLOPT_WRITEDATA, fp);
    curl_easy_setopt(curlhandle, CURLOPT_WRITEFUNCTION, wirtefunc);

    //curl_easy_setopt(curlhandle, CURLOPT_READFUNCTION, readfunc);
    //curl_easy_setopt(curlhandle, CURLOPT_READDATA, fp);
    curl_easy_setopt(curlhandle, CURLOPT_NOPROGRESS, 1L);
    curl_easy_setopt(curlhandle, CURLOPT_VERBOSE, 1L);

    CURLcode res = curl_easy_perform(curlhandle);
    fclose(fp);
    if (res == CURLE_OK) {
        return 1;
    }
    else {
        fprintf(stderr, "%s\n", curl_easy_strerror(res));
        return 0;
    }
}

void test() {
    curl_global_init(CURL_GLOBAL_ALL);
    CURL *curlhandle = curl_easy_init();
    //download(curlhandle , "http://10.238.4.157/GitHubDesktopSetup.exe", "GitHubDesktopSetup.exe", 1, 1);
    download(curlhandle , "http://10.238.4.157/cn_windows_10_enterprise_ltsc_2019_x64_dvd_9c09ff24.iso", "win10.iso", 1, 3);
    curl_easy_cleanup(curlhandle);
    curl_global_cleanup();
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    CurlDuanDianXuChuan w;
//    w.show();
    test();
    return a.exec();
}
