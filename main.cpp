#include<QApplication>
#include<QWidget>
#include"setting_control.h"
using namespace std;
int main(int argc,char* argv[])
{
    QApplication app(argc,argv);
    app.setApplicationName("My_Launcher");
    QWidget *app_main=new Setting_Control;
    app_main->hide();
    return app.exec();
}
