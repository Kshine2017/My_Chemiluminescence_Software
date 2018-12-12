/**
  *  @brief    选择标题栏
  *  @file     mycheckmessagebox.h
  *  @author   谢飞
  *  @version  1.0(版本号)
  *  @date     2017-10-22
  */
#ifndef MYCHECKMESSAGEBOX_H
#define MYCHECKMESSAGEBOX_H

#include <QDialog>
#include <QGridLayout>
#include <QLabel>
#include <QToolButton>
#include <QPushButton>

class myCheckmessageBox : public QDialog
{
    Q_OBJECT
public:

    /**
     * @brief 自定义枚举类型 选择框的类型
     */
    enum MY_MESSAGE_TYPE{
         MY_MESSAGE_NOICON = 0,  /**< 无 */
         MY_CALIBRATION,         /**< 校准/质控选择框*/
    };

    /**
     * @brief 构造函数
     * @param type [in] 消息类型
     * @param strTitle [in]标题
     * @param strInfo [in] 消息内容
     * @param parent [in] 父类窗口
     * @param flags [in] 窗口标志
     */
    explicit myCheckmessageBox(MY_MESSAGE_TYPE type, const QString &strTitle, const QString &strInfo,QWidget *parent = 0,
                     Qt::WindowFlags flags = Qt::CustomizeWindowHint | Qt::WindowTitleHint);
    /**
     * @brief 设置显示内容
     * @param strInfo [in] 信息内容
     */
    void setTextInfo(const QString &strInfo);

    /**
     * @brief 这是一个重载函数
     * @see CMYMessageBox::setTextInfo
     * @param strTitle [in] 标题
     * @param strInfo [in] 信息内容
     */
    void setTextInfo(const QString &strTitle, const QString &strInfo);

    /**
     * @brief 这是一个重载函数
     * @see CMYMessageBox::setTextInfo
     * @param type[in] 消息的类型
     * @param strTitle [in] 标题
     * @param strInfo [in] 信息内容
     */
    void setTextInfo(MY_MESSAGE_TYPE type, const QString &strTitle, const QString &strInfo);

private:
    /**
     * @brief 初始化
     * @param strInfo [in] 信息内容
     */
    void initialize(const QString &strInfo);

    /**
     * @brief 布局
     */
    void alignment();

private:
    QLabel *m_pLabelIcon;  /**< 提示信息类型图标 */
    QLabel *m_pLabelInfo;  /**< 提示信息 */
    QPushButton *m_oneBtn; /**< 是（确定）按扭 */
    QPushButton *m_twoBtn;  /**< 否（取消）按扭 */
    MY_MESSAGE_TYPE m_eMYType; /**< 自定义类型  */

signals:

public slots:
};

#endif // MYCHECKMESSAGEBOX_H
