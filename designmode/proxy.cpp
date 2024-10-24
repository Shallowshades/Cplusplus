#include <iostream>
#include <memory>
#include <algorithm>

using namespace std;

/*
抽象主题（Subject）：定义了真实对象和代理对象的共同接口。
真实主题（Real Subject）：实现了抽象主题接口，代表实际的业务逻辑。
代理（Proxy）：持有对真实主题的引用，并实现了抽象主题接口。代理可以在访问真实主题之前或之后添加额外的功能。
*/

class WebAddr {
public:
    virtual void visit() = 0; //执行访问网站的动作，子类中重新实现
    virtual ~WebAddr() {} //做父类时析构函数应该为虚函数
};

//某购物网站
class WebAddr_Shopping :public WebAddr {
public:
    virtual void visit() {
        //......访问该购物网站，可能涉及到复杂的网络通信
        cout << "访问WebAddr_Shopping购物网站!" << endl;
    }
};

//某视频网站
class WebAddr_Video :public WebAddr {
public:
    virtual void visit() {
        //......访问该视频网站，可能涉及到复杂的网络通信
        cout << "访问WebAddr_Video视频网站!" << endl;
    }
};

//网站代理类
class WebAddrProxy :public WebAddr {
public:
    //构造函数，引入的目的是传递进来要访问的具体网站
    WebAddrProxy(WebAddr* pwebaddr) :mp_webaddr(pwebaddr) {}
public:
    virtual void visit() {
        //在这里进行访问的合法性检查、日志记录或者流量限制......
        mp_webaddr->visit();
        //在这里可以进行针对返回数据的过滤......
    }
private:
    // TODO: 类内尽量使用弱指针
    WebAddr* mp_webaddr; //代表要访问的具体网站
};

//专门针对某购物网站WebAddr_Shopping的代理
class WebAddr_Shopping_Proxy :public WebAddr {
public:
    virtual void visit() {
        //在这里进行访问的合法性检查、日志记录或者流量限制......
        WebAddr_Shopping* p_webaddr = new WebAddr_Shopping();
        p_webaddr->visit();
        //在这里可以进行针对返回数据的过滤......

        //释放资源
        delete p_webaddr;
    }
};

int main() {
    shared_ptr<WebAddr> wba1 = make_shared<WebAddr_Shopping>();
    shared_ptr<WebAddr> wba2 = make_shared<WebAddr_Video>();
    //WebAddr* wba1 = new WebAddr_Shopping();
    //WebAddr* wba2 = new WebAddr_Video();

    unique_ptr<WebAddrProxy> wbaproxy1 = make_unique<WebAddrProxy>(wba1.get());
    wbaproxy1->visit(); //通过代理去访问WebAddr_Shopping购物网站

    //WebAddrProxy* wbaproxy2 = new WebAddrProxy(wba2.get());
    unique_ptr<WebAddrProxy> wbaproxy2 = make_unique<WebAddrProxy>(wba2.get());
    wbaproxy2->visit(); //通过代理去访问WebAddr_Video视频网站

    //WebAddr_Shopping_Proxy* wbasproxy = new WebAddr_Shopping_Proxy();
    unique_ptr<WebAddr_Shopping_Proxy> wbasproxy = make_unique<WebAddr_Shopping_Proxy>();
    wbasproxy->visit(); //访问的实际是某购物网站

    //资源释放
    //delete wba1;
    //delete wba2;
    //delete wbaproxy1;
    //delete wbaproxy2;
    //资源释放
    //delete wbasproxy;

    return 0;
}
