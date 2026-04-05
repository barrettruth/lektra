#pragma once

#include <QColor>
#include <QDialog>
#include <QSpinBox>
#include <QVBoxLayout>
#include <qboxlayout.h>

class ColorDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ColorDialog(QWidget *parent = nullptr);

    inline QColor selectedColor() const
    {
        return m_selected_color;
    }

signals:
    void colorSelected(const QColor &color);

private:
    void initUI();

private:
    QVBoxLayout *m_layout       = nullptr;
    QPushButton *m_okButton     = nullptr;
    QPushButton *m_cancelButton = nullptr;
    QColor m_selected_color;
};
