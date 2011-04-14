#ifndef THESAURUSMODEL_H
#define THESAURUSMODEL_H

#include <accountbaseplugin/accountbase_exporter.h>

#include <QAbstractTableModel>

namespace AccountDB {
namespace Internal {
class ThesaurusModelPrivate;
}

class ACCOUNTBASE_EXPORT ThesaurusModel : public QAbstractTableModel
{
public:
    ThesaurusModel(QObject *parent);
    ~ThesaurusModel();

    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
//    bool hasChildren(const QModelIndex &parent = QModelIndex()) const;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);

    QVariant headerData(int section, Qt::Orientation orientation,
                                int role = Qt::DisplayRole) const;
//    bool setHeaderData(int section, Qt::Orientation orientation, const QVariant &value,
//                               int role = Qt::EditRole);

    bool insertRows(int row, int count, const QModelIndex &parent = QModelIndex());
    bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex());

    bool insertRow(int arow, const QModelIndex &aparent = QModelIndex())        { return insertRows(arow, 1, aparent); }
    bool insertColumn(int acolumn, const QModelIndex &aparent = QModelIndex())  { return insertColumns(acolumn, 1, aparent); }
    bool removeRow(int arow, const QModelIndex &aparent = QModelIndex())        { return removeRows(arow, 1, aparent); }
    bool removeColumn(int acolumn, const QModelIndex &aparent = QModelIndex())  { return removeColumns(acolumn, 1, aparent); }
    bool submit();
    void setFilter(const QString & filter);
    bool select();
    bool isDirty() const;

private:
    Internal::ThesaurusModelPrivate *d;
};

}  // End namespace AccountDB


#endif // THESAURUSMODEL_H
