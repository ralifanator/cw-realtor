#ifndef MODEL_H
#define MODEL_H

#include <QObject>
#include "QSqlQueryModel"
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRecord>

class modell : public QSqlQueryModel
{
    Q_OBJECT
public:
    explicit modell(QObject *parent = nullptr);

    Qt::ItemFlags flags(const QModelIndex &index) const override;
    QMimeData *mimeData(const QModelIndexList &indexes) const override;
    bool dropMimeData(const QMimeData *data, Qt::DropAction action, int row, int column, const QModelIndex &parent) override;

    QVariant data(const QModelIndex &index, int role) const override;
    void fetchMore(const QModelIndex &parent) override;
    bool canFetchMore(const QModelIndex &parent) const override;

public slots:


protected:
    Qt::ItemFlags flag = Qt::ItemIsSelectable | Qt::ItemIsEnabled | Qt::ItemIsDragEnabled;
    QString firstMimeType = "text/plain";
    QString secondMimeType = "application/x-qabstractitemmodeldatalist";
    QString columnDelimiter = ";";
    QString rowDelimiter = "\n";
    QString quotes = "\"";

    const int FETCH_STEP = 20;
    int rowsToShow = 0;


signals:


private:

};

#endif // MODEL_H
