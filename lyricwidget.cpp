#include "lyricwidget.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QDir>
#include <QSettings>
#include <QCoreApplication>

LyricWidget::LyricWidget(QWidget *parent) : QWidget(parent),
    settings(QCoreApplication::organizationName(), QCoreApplication::applicationName())
{
    resize(800,120);

    setAttribute(Qt::WA_TranslucentBackground, true);
    setWindowFlags(Qt::WindowStaysOnTopHint);
    setWindowFlags(Qt::FramelessWindowHint);
    setWindowFlags(Qt::X11BypassWindowManagerHint);

    QVBoxLayout *vbox = new QVBoxLayout;
    vbox->setSpacing(0);

    QHBoxLayout *hbox = new QHBoxLayout;
    hbox->addStretch();

    pushButton_set = new QPushButton;
    pushButton_set->setFixedSize(24,24);
    pushButton_set->setIcon(QIcon(":/icon/set.svg"));
    pushButton_set->setFocusPolicy(Qt::NoFocus);
    pushButton_set->setFlat(true);
    pushButton_set->setCursor(Qt::PointingHandCursor);
    hbox->addWidget(pushButton_set);

    pushButton_close = new QPushButton;
    pushButton_close->setFixedSize(24,24);
    pushButton_close->setIcon(QIcon(":/icon/close.svg"));
    pushButton_close->setFocusPolicy(Qt::NoFocus);
    pushButton_close->setFlat(true);
    pushButton_close->setCursor(Qt::PointingHandCursor);
    hbox->addWidget(pushButton_close);

    vbox->addLayout(hbox);

    label_lyric = new QLabel("Hello，酷狗！");
    label_lyric->setAlignment(Qt::AlignCenter);
    QFont font;
    font.setPointSize(30);
    label_lyric->setFont(font);
    vbox->addWidget(label_lyric);

    setLayout(vbox);

    pushButton_set->hide();
    pushButton_close->hide();
}

void LyricWidget::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        isMouseLeftButtonPressed = true;
        m_point = event->pos();
    }
}

void LyricWidget::mouseMoveEvent(QMouseEvent *event)
{
    if(isMouseLeftButtonPressed){
        setCursor(Qt::ClosedHandCursor);
        move(event->pos() - m_point + pos());
    }
}

void LyricWidget::mouseReleaseEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
    isMouseLeftButtonPressed = false;
    setCursor(Qt::ArrowCursor);
    //writeSettings(QDir::currentPath() + "/config.ini", "config", "LyricX", QString::number(x()));
    //writeSettings(QDir::currentPath() + "/config.ini", "config", "LyricY", QString::number(y()));
    settings.setValue("LyricX", x());
    settings.setValue("LyricY", y());
}

void LyricWidget::enterEvent(QEvent *event)
{
    Q_UNUSED(event);
    setStyleSheet("background-color: rgba(255,255,255,30);");
    pushButton_close->setVisible(true);
    pushButton_set->setVisible(true);
}

void LyricWidget::leaveEvent(QEvent *event)
{
    Q_UNUSED(event);
    setStyleSheet("");
    pushButton_close->setVisible(false);
    pushButton_set->setVisible(false);
}