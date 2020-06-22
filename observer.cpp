#include "observer.h"

Observer::Observer()
{
    massivBridge.resize(3);
    massivBridge[0] = new BarBridge();
    massivBridge[1] = new PieBridge();
    massivBridge[2] = new TableBridge();
}

QWidget* Observer::UpdateData(QList<DataFile>& data, unsigned int index)
{
    if (index < (unsigned int) massivBridge.size())
        return massivBridge[index]->UpdateData(data);
    else
        return nullptr;
}

Observer::~Observer()
{
    for (int i = 0; i < massivBridge.size(); i++)
    {
        delete massivBridge[i];}

    }
