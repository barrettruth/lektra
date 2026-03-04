#include "RecentFilesPicker.hpp"

#include <QFileInfo>

RecentFilesPicker::RecentFilesPicker(QWidget *parent) : Picker(parent)
{
    setColumns({{.header = "Name", .stretch = 2}, {.header = "Path", .stretch = 0}});
}

QList<Picker::Item>
RecentFilesPicker::collectItems()
{
    QList<Item> items;
    items.reserve(m_recentFiles.size());
    for (const auto &path : m_recentFiles)
    {
        QFileInfo fi(path);
        items.push_back({
            .columns = {fi.fileName(), fi.absolutePath()},
            .data    = path,
        });
    }
    return items;
}

void
RecentFilesPicker::onItemAccepted(const Item &item)
{
    emit fileRequested(item.data.toString());
}
