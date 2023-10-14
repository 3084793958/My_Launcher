#include<QApplication>
#include<QWidget>
#include"setting_control.h"
#include<QDBusMessage>
#include<QDBusConnection>
using namespace std;
int main(int argc,char* argv[])
{
    QApplication app(argc,argv);
    QString path=QDir::temp().absoluteFilePath("My_Launcher");
    QLockFile lockFile(path);
    bool isLock=lockFile.isLocked();
    if (!lockFile.tryLock(100))
    {
        QDBusMessage message=QDBusMessage::createSignal("/my/launcher","com.my.launcher","send_to_show");
        message<<"Show";
        QDBusConnection::sessionBus().send(message);
        return 1;
    }
    app.setApplicationName("My_Launcher");
    QWidget *app_main=new Setting_Control;
    app_main->hide();
    return app.exec();
}
