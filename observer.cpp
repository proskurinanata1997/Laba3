#include "observer.h"

Observer::Observer()
{
    massivBridge.resize(3);
    massivBridge[0] = new BarBridge();
    massivBridge[1] = new PieBridge();
    massivBridge[2] = new TableBridge();
}

QWidget* Observer::UpdateData(QList<DataFile>& data, int index)
{
    QWidget *result;
    for (int i = 0; i < massivBridge.size(); i++)
    {
        if (i==index)
        {
            result = massivBridge[i]->UpdateData(data);
        }
    else massivBridge[i]->UpdateData(data);
    }
    return result;
}

Observer::~Observer()
{
    for (int i = 0; i < massivBridge.size(); i++)
    {
        delete massivBridge[i];
    }
}
