#include <python.h>
#include "AllWindow/StockMarket.h"
#include <QApplication>
#pragma comment(lib, "user32.lib")

int main(int argc, char *argv[])
{
    /*Py_SetPythonHome((wchar_t *)(L"./env"));
    Py_Initialize();
    if (!Py_IsInitialized())
    {
        return -1;
    }*/
    QApplication a(argc, argv);
    StockMarket w;
    w.show();
    return a.exec();
    // 以下为测试代码
}
