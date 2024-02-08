#include "model.h"
#include "mainwindow.h"

modell::modell(QObject *parent) : QSqlQueryModel(parent)
{

}

Qt::ItemFlags modell::flags(const QModelIndex &index) const
{
    if(!index.isValid())
        return Qt::NoItemFlags;
    return flag;
}

QMimeData *modell::mimeData(const QModelIndexList &indexes) const
{
    qDebug() << "mimeData FUNCTION";
    if(indexes.isEmpty())
        return nullptr;
    if(!indexes.at(0).isValid())
        return nullptr;

    if (firstMimeType == "text/plain" && secondMimeType == "application/x-qabstractitemmodeldatalist")
    {
        QString result;

        int topSelectionRange = indexes.at(0).row();
        int leftSelectionRange = indexes.at(0).column();
        //int rowCountSelectionRange = 0;
        //int columnCountSelectionRange = 0;
        for (int i = 0; i < indexes.count(); ++i) {
            // item отсутствует?
            if (!indexes.at(i).isValid())
                return nullptr;

            int c = indexes.at(i).column() - leftSelectionRange;
            int r = indexes.at(i).row() - topSelectionRange;

            if (c > 0 && (c < 0 || indexes.at(i).row() == topSelectionRange))
                result += columnDelimiter;
            if (r > 0 && indexes.at(i).column() == leftSelectionRange)
                result += rowDelimiter;
            result += quotes +
                    indexes.at(i).data(Qt::DisplayRole).toString() +
                    quotes;
        }

        result += rowDelimiter;
        qDebug() << result;

        // создаем mimeData, которая будет использоваться для drop
        QMimeData *mimeData = new QMimeData;
        // создаем mimeDataForLocal для записи типа и mimeData для внутренних переносов
        QMimeData *mimeDataForLocal = QSqlQueryModel::mimeData(indexes);
        // записываем типы с данными для drop в mimeData
        mimeData->setData(secondMimeType, mimeDataForLocal->data(secondMimeType));
        mimeData->setData(firstMimeType, result.toUtf8());
        return mimeData;
    }

    return nullptr;
}

bool modell::dropMimeData(const QMimeData *data, Qt::DropAction action, int row, int column, const QModelIndex &parent)
{
    qDebug() << "dropMimeData FUNCTION";
    if(data == nullptr)
        return false;

    QByteArray dataforsecond = data->data(secondMimeType);
    QMimeData *forsecond = new  QMimeData;
    forsecond->setData(secondMimeType, dataforsecond);
    forsecond->setText(dataforsecond);

    if(data->hasFormat("application/x-qabstractitemmodeldatalist"))
    {
        return QSqlQueryModel::dropMimeData(forsecond, action, row, column, parent);
    }

    if (data->hasFormat("text/plain"))
    {
        QStringList strings;
        strings = data->text().split(rowDelimiter);

        for (int rowSelected = 0; rowSelected < strings.count(); ++rowSelected)
        {
            if ((row + rowSelected) >= rowCount(parent))
                insertRow(rowCount(parent));
            QStringList tokens = strings[rowSelected].split(columnDelimiter);
            for (int columnSelected = 0; columnSelected < tokens.count(); columnSelected++)
            {
                QString token = tokens[columnSelected];
                token.remove(quotes);
                if (token.isEmpty())
                    continue;

                setData(index(row + rowSelected, columnSelected, parent), token, Qt::EditRole);
            }
        }
        return true;
    }

    return false;
}

void modell::fetchMore(const QModelIndex &parent)
{
    if(parent.isValid())
        return;
    rowsToShow += qMin(FETCH_STEP, QSqlQueryModel::rowCount(parent) - rowsToShow);
    emit layoutChanged(); // обновление модели (+ пересчет строк методом rowCount)
}


bool modell::canFetchMore(const QModelIndex &parent) const
{
    if(parent.isValid())
        return false;
    qDebug() << "Can fetch more";
    return (rowsToShow < QSqlQueryModel::rowCount(parent));
}

QVariant modell::data(const QModelIndex &index, int role) const
{
    if(!index.isValid() || index.row() + 1 > rowsToShow)
        return QVariant();
    if(role == Qt::ToolTipRole)
        return QSqlQueryModel::data(index, Qt::DisplayRole);
    return QSqlQueryModel::data(index, role);
}
