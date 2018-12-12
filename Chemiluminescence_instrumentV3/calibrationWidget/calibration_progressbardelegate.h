#ifndef CALIBRATION_PROGRESSBARDELEGATE_H
#define CALIBRATION_PROGRESSBARDELEGATE_H

#include <QStyledItemDelegate>
#include <QProgressBar>
#include <QStyleOptionProgressBar>
#include <QApplication>
class calibration_ProgressBarDelegate:public QStyledItemDelegate
{
    Q_OBJECT

public:

    explicit calibration_ProgressBarDelegate(QObject *parent = 0);

private:
    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex  &index) const;
    void setEditorData(QWidget *editor, const QModelIndex &index) const;
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;
    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    void paint(QPainter *painter, const QStyleOptionViewItem &option,
                           const QModelIndex &index) const;
protected:


};


#endif // CALIBRATION_PROGRESSBARDELEGATE_H
