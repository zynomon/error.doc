#include <QApplication>
#include <QMainWindow>
#include <QTabWidget>
#include <QWebEngineView>
#include <QWebEnginePage>
#include <QUrl>
#include <QProcess>
#include <QVBoxLayout>
#include <QGroupBox>
#include <QTextEdit>
#include <QPushButton>
#include <QMessageBox>
#include <QSettings>
#include <QLabel>
#include <QIcon>
#include <QPixmap>
#include <QPainter>
#include <QTimer>
#include <QLinearGradient>
#include <QRadialGradient>


QPixmap makeRadialFadedIcon(const QIcon &baseIcon, const QSize &size) {
    QPixmap pixmap(size);
    pixmap.fill(Qt::transparent);

    QPainter painter(&pixmap);
    painter.setRenderHint(QPainter::Antialiasing);
    baseIcon.paint(&painter, QRect(QPoint(0,0), size));

    QRadialGradient fade(size.width()/2, size.height()/2, size.width()/2);
    fade.setColorAt(0.0, QColor(255,255,255,120));
    fade.setColorAt(1.0, QColor(255,255,255,0));

    painter.setCompositionMode(QPainter::CompositionMode_DestinationIn);
    painter.fillRect(pixmap.rect(), fade);
    painter.end();
    return pixmap;
}


class TabSettings : public QWidget {
    Q_OBJECT
public:
    TabSettings(QWidget *parent = nullptr) : QWidget(parent) {
        QVBoxLayout *layout = new QVBoxLayout(this);


        QGroupBox *cssGroup = new QGroupBox(tr("Custom CSS for Websites"), this);
        QVBoxLayout *cssLayout = new QVBoxLayout(cssGroup);
        m_cssEdit = new QTextEdit(this);
        m_cssEdit->setPlaceholderText(tr("Enter CSS rules here..."));
        cssLayout->addWidget(m_cssEdit);
        layout->addWidget(cssGroup);


        QGroupBox *qssGroup = new QGroupBox(tr("Qt Style Sheet (QSS)"), this);
        QVBoxLayout *qssLayout = new QVBoxLayout(qssGroup);
        m_qssEdit = new QTextEdit(this);
        m_qssEdit->setPlaceholderText(tr("QSS code will appear here when you click Dark..."));
        qssLayout->addWidget(m_qssEdit);
        layout->addWidget(qssGroup);


        QPushButton *darkBtn = new QPushButton(tr("Apply Dark Theme"), this);
        layout->addWidget(darkBtn);


        QPushButton *docBtn = new QPushButton(tr("Open Documentation Tab"), this);
        layout->addWidget(docBtn);


        QPushButton *resetBtn = new QPushButton(tr("Reset All Settings"), this);
        layout->addWidget(resetBtn);

        layout->addStretch();
        setLayout(layout);

        connect(darkBtn, &QPushButton::clicked, this, &TabSettings::applyDarkTheme);
        connect(docBtn, &QPushButton::clicked, this, &TabSettings::openDocumentationRequested);
        connect(resetBtn, &QPushButton::clicked, this, &TabSettings::resetSettings);
    }

    void loadSettings() {
        QSettings settings("error.os", "error_doc");
        QString qss = settings.value("qss", "").toString();
        QString css = settings.value("css", "").toString();
        if (!qss.isEmpty()) {
            qApp->setStyleSheet(qss);
            m_qssEdit->setPlainText(qss);
        }
        if (!css.isEmpty()) {
            m_cssEdit->setPlainText(css);
        }
    }

signals:
    void openDocumentationRequested();

private slots:
    void resetSettings() {
        QSettings settings("error.os", "error_doc");
        settings.clear();
        QMessageBox::information(this, tr("Reset"), tr("All settings have been reset."));
        m_cssEdit->clear();
        m_qssEdit->clear();
    }

    void applyDarkTheme() {

        QString darkQss = R"(
            QWidget {
                background-color: #2b2b2b;
                color: #f0f0f0;
            }
            QGroupBox {
                border: 1px solid #444;
                margin-top: 6px;
            }
            QGroupBox::title {
                subcontrol-origin: margin;
                subcontrol-position: top left;
                padding: 0 3px;
                color: #f0f0f0;
            }
            QPushButton {
                background-color: #444;
                color: #f0f0f0;
                border: 1px solid #666;
                padding: 5px;
            }
            QPushButton:hover {
                background-color: #555;
            }
            QTextEdit {
                background-color: #1e1e1e;
                color: #f0f0f0;
                border: 1px solid #555;
            }
        )";


        QString darkCss = R"(
            body {
                background-color: #121212;
                color: #e0e0e0;
            }
            a {
                color: #bb86fc;
            }
            header, footer {
                background-color: #1f1f1f;
            }
        )";


        qApp->setStyleSheet(darkQss);
        m_qssEdit->setPlainText(darkQss);


        m_cssEdit->setPlainText(darkCss);


        QSettings settings("error.os", "error_doc");
        settings.setValue("qss", darkQss);
        settings.setValue("css", darkCss);
    }

private:
    QTextEdit *m_cssEdit;
    QTextEdit *m_qssEdit;
};



class TabDocumentation : public QWidget {
    Q_OBJECT
public:
    TabDocumentation(QWidget *parent = nullptr) : QWidget(parent) {
        QVBoxLayout *layout = new QVBoxLayout(this);
        layout->setContentsMargins(0,0,0,0);
        layout->setSpacing(0);

        m_view = new QWebEngineView(this);

        class RestrictedPage : public QWebEnginePage {
        public:
            explicit RestrictedPage(QObject *parent = nullptr) : QWebEnginePage(parent) {}
        protected:
            bool acceptNavigationRequest(const QUrl &url, NavigationType, bool) override {
                const QString allowedPrefix = QStringLiteral("https://zynomon.github.io/error.doc");
                const QString target = url.toString();
                if (target.startsWith(allowedPrefix)) return true;
                QProcess::startDetached("xdg-open", QStringList() << target);
                return false;
            }
        };

        m_view->setPage(new RestrictedPage(m_view));
        m_view->load(QUrl(QStringLiteral("https://zynomon.github.io/error.doc")));

        layout->addWidget(m_view);
        setLayout(layout);
    }

protected:
    void showEvent(QShowEvent *event) override {
        QWidget::showEvent(event);
        if (!m_noticeShown) {
            m_noticeShown = true;
            showNoticePopup();
        }
    }

private:
    QWebEngineView *m_view;
    bool m_noticeShown = false;

    void showNoticePopup() {
        QWidget *popup = new QWidget(this);
        popup->setAttribute(Qt::WA_DeleteOnClose);
        popup->setStyleSheet(
            "background-color:#333;"
            "color:white;"
            "border:1px solid #555;"
            "padding:10px;"
            );

        QHBoxLayout *layout = new QHBoxLayout(popup);
        layout->setContentsMargins(12, 12, 12, 12);
        layout->setSpacing(10);

        QLabel *iconLabel = new QLabel(popup);
        iconLabel->setPixmap(QIcon::fromTheme("dialog-information").pixmap(32, 32));

        QLabel *label = new QLabel("This documentation viewer uses the Internet to fetch data.", popup);
        label->setStyleSheet("font-size: 12pt; font-weight: bold;");
        label->setWordWrap(true);


        QPushButton *closeBtn = new QPushButton("×", popup);
        closeBtn->setFixedSize(36, 36);
        closeBtn->setStyleSheet(
            "color:white;"
            "border:none;"
            "font-weight:bold;"
            "font-size: 18pt;"
            "background:transparent;"
            );

        layout->addWidget(iconLabel);
        layout->addWidget(label);
        layout->addStretch();
        layout->addWidget(closeBtn);


        popup->resize(520, 120);

        // Position: centered horizontally, near top, lets get set ready
        int x = (this->width() - popup->width()) / 2;
        int y = 40;
        popup->move(x, y);

        popup->show();

        // Auto-close after 2s unless hovered
        QTimer *timer = new QTimer(popup);
        timer->setSingleShot(true);
        timer->start(2000);
        connect(timer, &QTimer::timeout, popup, &QWidget::close);

        connect(closeBtn, &QPushButton::clicked, popup, &QWidget::close);


        popup->installEventFilter(this);
        m_popupTimer = timer;
        m_popupWidget = popup;
    }

    bool eventFilter(QObject *obj, QEvent *event) override {
        if (obj == m_popupWidget && m_popupTimer) {
            if (event->type() == QEvent::Enter) {
                m_popupTimer->stop();
            } else if (event->type() == QEvent::Leave) {
                m_popupTimer->start(2000);
            }
        }
        return QWidget::eventFilter(obj, event);
    }

    QTimer *m_popupTimer = nullptr;
    QWidget *m_popupWidget = nullptr;
};



class TabManpage : public QWidget {
    Q_OBJECT
public:
    TabManpage(QWidget *parent = nullptr) : QWidget(parent) {
        QVBoxLayout *layout = new QVBoxLayout(this);

        QLabel *bgLabel = new QLabel(this);
        bgLabel->setPixmap(makeRadialFadedIcon(QIcon::fromTheme("system-help"), QSize(512,512)));
        bgLabel->setAlignment(Qt::AlignTop | Qt::AlignRight);
        bgLabel->setStyleSheet("opacity:0.25;");
        layout->addWidget(bgLabel, 0, Qt::AlignTop | Qt::AlignRight);

        QLabel *iconLabel = new QLabel(this);
        iconLabel->setPixmap(QIcon::fromTheme("system-help").pixmap(96,96));
        iconLabel->setAlignment(Qt::AlignCenter);
        layout->addWidget(iconLabel);

        QLabel *textLabel = new QLabel(tr("Manpage coming soon..."), this);
        textLabel->setAlignment(Qt::AlignCenter);
        textLabel->setStyleSheet("font-size: 18pt; font-weight: bold;");
        layout->addWidget(textLabel);

        layout->addStretch();
        setLayout(layout);
    }
};


class TabBookmarks : public QWidget {
    Q_OBJECT
public:
    TabBookmarks(QWidget *parent = nullptr) : QWidget(parent) {
        QVBoxLayout *layout = new QVBoxLayout(this);

        QLabel *bgLabel = new QLabel(this);
        bgLabel->setPixmap(makeRadialFadedIcon(QIcon::fromTheme("bookmarks"), QSize(512, 512)));
        bgLabel->setAlignment(Qt::AlignBottom | Qt::AlignLeft);
        bgLabel->setStyleSheet("opacity:0.25;");
        layout->addWidget(bgLabel, 0, Qt::AlignBottom | Qt::AlignLeft);

        QLabel *iconLabel = new QLabel(this);
        iconLabel->setPixmap(QIcon::fromTheme("bookreader").pixmap(96,96));
        iconLabel->setAlignment(Qt::AlignCenter);
        layout->addWidget(iconLabel);

        QLabel *textLabel = new QLabel(tr("Bookmarks coming soon..."), this);
        textLabel->setAlignment(Qt::AlignCenter);
        textLabel->setStyleSheet("font-size: 18pt; font-weight: bold;");
        layout->addWidget(textLabel);

        layout->addStretch();
        setLayout(layout);
    }
};



class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr) : QMainWindow(parent) {
        m_tabs = new QTabWidget(this);
        m_tabs->setTabPosition(QTabWidget::West);
        m_tabs->setIconSize(QSize(48, 48));
        m_tabs->setDocumentMode(true);

        m_settingsTab   = new TabSettings();
        m_docTab        = new TabDocumentation();
        m_manpageTab    = new TabManpage();
        m_bookmarksTab  = new TabBookmarks();


        m_tabs->addTab(m_settingsTab,  QIcon::fromTheme("dcc_nav_commoninfo"), QString());
        m_tabs->setTabToolTip(0, tr("Settings: configure CSS/QSS themes and preferences"));

        m_tabs->addTab(m_docTab,       QIcon::fromTheme("abrowser"), QString());
        m_tabs->setTabToolTip(1, tr("Documentation: view error.doc web documentation connects to website called https://zynomon.github.io/error.doc/"));

        m_tabs->addTab(m_manpageTab,   QIcon::fromTheme("system-help"), QString());
        m_tabs->setTabToolTip(2, tr("Manpage: manual pages coming soon the version you are using was made in half hour"));

        m_tabs->addTab(m_bookmarksTab, QIcon::fromTheme("bookreader"), QString());
        m_tabs->setTabToolTip(3, tr("Bookmarks: saved references coming soon  same for the bookmark its coming soon.."));

        m_settingsTab->loadSettings();

        setCentralWidget(m_tabs);


        setWindowIcon(QIcon::fromTheme("error.doc"));

        setWindowTitle(tr("Error Documentaion"));
        resize(1024, 768);
    }

private:
    QTabWidget   *m_tabs = nullptr;
    TabSettings  *m_settingsTab = nullptr;
    TabDocumentation *m_docTab = nullptr;
    TabManpage   *m_manpageTab = nullptr;
    TabBookmarks *m_bookmarksTab = nullptr;
};

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    MainWindow window;
    window.show();
    return app.exec();
}

#include "main.moc"
