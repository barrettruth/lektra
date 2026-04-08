#include "ColorDialog.hpp"

#include <QHBoxLayout>
#include <QPushButton>

ColorDialog::ColorDialog(const std::vector<QColor> colors, QWidget *parent)
    : m_colors(colors), QDialog(parent)
{
    initUI();
}

void
ColorDialog::initUI()
{
    setWindowTitle(tr("Color Dialog"));
    setFixedSize(200, 150);
    setModal(true);

    m_layout                 = new QVBoxLayout();
    QGridLayout *colorLayout = new QGridLayout();

    int idx            = 0;
    size_t color_count = m_colors.size();
    int nrows
        = std::min(3, static_cast<int>((color_count + 2)
                                       / 3)); // Calculate number of rows needed
    int ncols = std::min(
        3, static_cast<int>(color_count)); // Calculate number of columns needed

    for (int i = 0; i < nrows; ++i)
    {
        for (int j = 0; j < ncols; ++j)
        {
            const QColor &c          = m_colors[idx++];
            QPushButton *colorButton = new QPushButton(this);
            colorButton->setStyleSheet(QString(R"(
            QPushButton { background: rgb(%1, %2, %3); }
            QPushButton:focus { outline: 3px solid black; }
        )")
                                           .arg(c.red())
                                           .arg(c.green())
                                           .arg(c.blue()));
            connect(colorButton, &QPushButton::clicked, this,
                    [this, c]() { m_selected_color = c; });
            colorLayout->addWidget(colorButton, i, j);
        }
    }

    m_layout->addLayout(colorLayout);

    QPushButton *ok_btn     = new QPushButton(tr("OK"), this);
    QPushButton *cancel_btn = new QPushButton(tr("Cancel"), this);

    connect(ok_btn, &QPushButton::clicked, this, [this]()
    {
        emit colorSelected(m_selected_color);
        accept();
    });

    connect(cancel_btn, &QPushButton::clicked, this, [this]() { reject(); });

    m_layout->addWidget(ok_btn);
    m_layout->addWidget(cancel_btn);
    this->setLayout(m_layout);
}
