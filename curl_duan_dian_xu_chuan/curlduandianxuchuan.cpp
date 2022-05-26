#include "curlduandianxuchuan.h"
#include "ui_curlduandianxuchuan.h"

//constexpr auto USERAGENT = "User-Agent: Mozilla/5.0 (Windows NT 6.1; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/50.0.2661.87 Safari/537.36";
size_t write_func(void *ptr, size_t size, size_t nmemb, void *stream)
{
    return fwrite(ptr, size, nmemb, (FILE *)stream);
}

size_t read_func(void *ptr, size_t size, size_t nmemb, void *stream)
{
    return fread(ptr, size, nmemb, (FILE *)stream);
}

int progress_func(void *ptr, double ddtotal, double ddnow, double udtotal, double udnow)
{
    cout << "ddtotal = " << ddtotal << ", ddnow = " << ddnow << endl;
    /*
    （1）dynamic_cast<类型>（要转换的对象）：用于转换基类和派生类。
    （2）const_cast<类型>（要转换的对象） ：用于const和volatile的转换。
    （3）reinterpret_cast<类型>（要转换的对象）：用于两个对象之间没有任何关系时进行转换。
    （4）static_cast<类型>（要转换的对象）：这个是一般转换，不是上述三个转换时或者不知道用什么时就用这个。
    */
    CurlDuanDianXuChuan *curlDuanDianXuChuan = static_cast<CurlDuanDianXuChuan *>(ptr);
    curlDuanDianXuChuan->UpdateProgressBar(ddnow * 100 / ddtotal);

    return 0;
}

DownloadThread::DownloadThread()
{
    curlDuanDianXuChuan = NULL;
}

void DownloadThread::run()
{
    FILE *fp = fopen("./GitHubDesktopSetup.exe", "wb");
    if (fp == NULL) {
        cout << "open file failed" << endl;
        return;
    }
    curl_global_init(CURL_GLOBAL_ALL);
    CURL* curl = curl_easy_init();
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, "http://10.238.4.157/GitHubDesktopSetup.exe");
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_func);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
//        curl_easy_setopt(curl, CURLOPT_READFUNCTION, read_func);
        curl_easy_setopt(curl, CURLOPT_NOPROGRESS, false);
        curl_easy_setopt(curl, CURLOPT_PROGRESSFUNCTION, progress_func);
        curl_easy_setopt(curl, CURLOPT_PROGRESSDATA, curlDuanDianXuChuan);
//        curl_easy_setopt(curl, CURLOPT_USERAGENT, USERAGENT);
//        curl_easy_setopt(curl, CURLOPT_DNS_CACHE_TIMEOUT,0);
        
//        struct curl_slist *headers = NULL;
//        headers = curl_slist_append(headers, "Cache-Control:no-cache");
//        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        
        CURLcode res = curl_easy_perform(curl);
        if (res != CURLE_OK) {
            cout << "curl error" << endl;
        }
        //curl_slist_free_all(headers);
        curl_easy_cleanup(curl);
        fclose(fp);
    }
}

CurlDuanDianXuChuan *DownloadThread::getCurlDuanDianXuChuan() const
{
    return curlDuanDianXuChuan;
}

void DownloadThread::setCurlDuanDianXuChuan(CurlDuanDianXuChuan *value)
{
    curlDuanDianXuChuan = value;
}

CurlDuanDianXuChuan::CurlDuanDianXuChuan(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::CurlDuanDianXuChuan)
{
    ui->setupUi(this);
    DownloadThread *downloadThread = new DownloadThread();
    downloadThread-> setCurlDuanDianXuChuan(this);
    downloadThread->start();
    
    connect(this, SIGNAL(sigUpdateProgressBar(int)), this, SLOT(sltUpdateProgressBar(int)));
}

CurlDuanDianXuChuan::~CurlDuanDianXuChuan()
{
    delete ui;
}

void CurlDuanDianXuChuan::UpdateProgressBar(int value)
{
    emit sigUpdateProgressBar(value);
}

void CurlDuanDianXuChuan::on_pushButton_clicked()
{
    if (ui->pushButton->text() == "Stop") {
        ui->pushButton->setText("Start");
    }
    else {
        ui->pushButton->setText("Stop");
    }
}

void CurlDuanDianXuChuan::sltUpdateProgressBar(int value)
{
    ui->progressBar->setValue(value);
}
