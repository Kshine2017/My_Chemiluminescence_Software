#ifndef CALIBRATION_QCOMBOXDELEGATE_H
#define CALIBRATION_QCOMBOXDELEGATE_H

#include <QStyledItemDelegate>
#include <QComboBox>
#include <QStyleOptionComboBox>
class calibration_QComboxDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit calibration_QComboxDelegate(QObject *parent = 0);

private:
    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex  &index) const;
    void setEditorData(QWidget *editor, const QModelIndex &index) const;
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;
    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    void paint(QPainter *painter, const QStyleOptionViewItem &option,
                              const QModelIndex &index) const;
signals:

public slots:
};

#endif // CALIBRATION_QCOMBOXDELEGATE_H
