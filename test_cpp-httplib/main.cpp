#include <QCoreApplication>

#include <iostream>
using namespace std;

#include "httplib.h"
using namespace httplib;

void http_callback(const Request& req, Response& resp) {
    cout << "req.version                \t:" << req.version << endl;
    cout << "req.target                 \t:" << req.target << endl;
    cout << "req.remote_port            \t:" << req.remote_port << endl;
    cout << "req.remote_addr            \t:" << req.remote_addr << endl;
    cout << "req.redirect_count_        \t:" << req.redirect_count_ << endl;
    cout << "req.path                   \t:" << req.path << endl;
    cout << "req.method                 \t:" << req.method << endl;
    cout << "req.content_length_        \t:" << req.content_length_ << endl;
    cout << "req.body                   \t:" << req.body << endl;
    cout << "req.authorization_count_   \t:" << req.authorization_count_ << endl << endl;
    
    cout << "resp.version               \t:" << resp.version << endl;
    cout << "resp.status                \t:" << resp.status << endl;
    cout << "resp.reason                \t:" << resp.reason << endl;
    cout << "resp.location              \t:" << resp.location << endl;
    cout << "resp.content_length_       \t:" << resp.content_length_ << endl;
    cout << "resp.body                  \t:" << resp.body << endl << endl;
    
    std::string body = "<html>linux so easy</html>";
    resp.set_content(body.c_str(), body.size(), "text/html");
    
    cout << "req.version                \t:" << req.version << endl;
    cout << "req.target                 \t:" << req.target << endl;
    cout << "req.remote_port            \t:" << req.remote_port << endl;
    cout << "req.remote_addr            \t:" << req.remote_addr << endl;
    cout << "req.redirect_count_        \t:" << req.redirect_count_ << endl;
    cout << "req.path                   \t:" << req.path << endl;
    cout << "req.method                 \t:" << req.method << endl;
    cout << "req.content_length_        \t:" << req.content_length_ << endl;
    cout << "req.body                   \t:" << req.body << endl;
    cout << "req.authorization_count_   \t:" << req.authorization_count_ << endl << endl;
    
    cout << "resp.version               \t:" << resp.version << endl;
    cout << "resp.status                \t:" << resp.status << endl;
    cout << "resp.reason                \t:" << resp.reason << endl;
    cout << "resp.location              \t:" << resp.location << endl;
    cout << "resp.content_length_       \t:" << resp.content_length_ << endl;
    cout << "resp.body                  \t:" << resp.body << endl << endl;
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    
    Server svr;
    svr.Get("/aaa", http_callback);
    svr.listen("0.0.0.0", 19998);
    
    return a.exec();
}
