#include "observer.h"

Observer::Observer()
{
    massivBridge.resize(3);
    massivBridge[0] = new BarChart();
    massivBridge[1] = new PieChart();
    massivBridge[2] = new TableAdapter();
}

QWidget* Observer::updateData(QList<DataFile>& data, unsigned int index)
{
    if (index < (unsigned int) massivBridge.size())
        return massivBridge[index]->updateData(data);
    else
        return nullptr;
}

Observer::~Observer()
{
    for (int i = 0; i < massivBridge.size(); i++)
    {
        delete massivBridge[i];
    }

}
