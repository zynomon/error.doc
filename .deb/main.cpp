#include <QApplication>
#include <QMainWindow>
#include <QSplitter>
#include <QTreeWidget>
#include <QStackedWidget>
#include <QTextBrowser>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QGridLayout>
#include <QTabWidget>
#include <QBuffer>
#include <QPushButton>
#include <QToolButton>
#include <QMenu>
#include <QLabel>
#include <QFrame>
#include <QLineEdit>
#include <QProcess>
#include <QSettings>
#include <QFile>
#include <QDir>
#include <QDirIterator>
#include <QStandardPaths>
#include <QMessageBox>
#include <QCheckBox>
#include <QKeySequenceEdit>
#include <QSlider>
#include <QComboBox>
#include <QTextToSpeech>
#include <QColorDialog>
#include <QTextCharFormat>
#include <QTextCursor>
#include <QRegularExpression>
#include <QDateTime>
#include <QRandomGenerator>
#include <QFileIconProvider>
#include <QFileInfo>
#include <QDesktopServices>
#include <QUrl>
#include <QTextEdit>
#include <QScrollArea>
#include <QPainter>
#include <QIcon>
#include <QShortcut>
#include <QKeySequence>
#include <QGroupBox>
#include <QToolBar>
#include <QThread>
#include <QListWidget>
#include <QDialog>
#include <QDialogButtonBox>
#include <QTabBar>
#include <QTimer>
#include <QtConcurrent/QtConcurrent>
#include <QCompleter>
#include <QStringListModel>
#include <QLineEdit>
#include <QRegularExpression>
#include <QFuture>
#include <QFutureWatcher>
#include <QProgressBar>
#include <QStyle>
#include <QLineEdit>
#include <QPushButton>

static const QRegularExpression TITLE_REGEX("<title>([^<]+)</title>");
static const QRegularExpression MANPAGE_REGEX("^([^\\s]+)\\s+\\(([0-9]+)\\)\\s+-\\s+(.+)$");
static const QRegularExpression HEADER_REGEX("^([A-Z][A-Z\\s]+)$");
static const QRegularExpression MANPAGE_NAME_REGEX("^(.+)\\s+\\((\\d+)\\)$");
static const QRegularExpression FILE_TAG_REGEX("<file\\s+url=\"([^\"]+)\"\\s*/?>");
static const QRegularExpression ICON_TAG_REGEX("<icon\\s+name=\"([^\"]+)\"\\s*/?>");
static const QRegularExpression PAGE_ICON_TAG_REGEX("<page\\s+icon=\"([^\"]+)\"\\s*/?>");
static const QRegularExpression BASH_TAG_REGEX("<bash>([\\s\\S]*?)</bash>");


class Settings : public QObject {
    Q_OBJECT

public:
    static Settings& instance() {
        static Settings inst;
        return inst;
    }

    Settings(const Settings&) = delete;
    Settings& operator=(const Settings&) = delete;

    QString shortcutOptions() const {
        return m_settings.value("shortcuts/options", "Ctrl+O").toString();
    }
    QString shortcutNewTab() const {
        return m_settings.value("shortcuts/newTab", "Ctrl+T").toString();
    }
    QString shortcutCloseTab() const {
        return m_settings.value("shortcuts/closeTab", "Ctrl+W").toString();
    }
    QString shortcutFind() const {
        return m_settings.value("shortcuts/find", "Ctrl+F").toString();
    }
    QString shortcutSpeak() const {
        return m_settings.value("shortcuts/speak", "Ctrl+Shift+S").toString();
    }
    QString shortcutStopSpeech() const {
        return m_settings.value("shortcuts/stopSpeech", "Ctrl+Shift+X").toString();
    }
    QString shortcutBookmarks() const {
        return m_settings.value("shortcuts/bookmarks", "Ctrl+B").toString();
    }
    QString shortcutRefresh() const {
        return m_settings.value("shortcuts/refresh", "F5").toString();
    }

    bool showTabAlways() const {
        return m_settings.value("ui/showTabAlways", false).toBool();
    }

    QString terminal() const {
        return m_settings.value("system/terminal", "konsole").toString();
    }

    QString ttsEngine() const {
        return m_settings.value("tts/engine", "").toString();
    }
    double ttsRate() const {
        return m_settings.value("tts/rate", 0.5).toDouble();
    }
    double ttsPitch() const {
        return m_settings.value("tts/pitch", 1.0).toDouble();
    }
    double ttsVolume() const {
        return m_settings.value("tts/volume", 1.0).toDouble();
    }
    QString ttsVoice() const {
        return m_settings.value("tts/voice", "").toString();
    }

    void setShortcutOptions(const QString &v) {
        m_settings.setValue("shortcuts/options", v);
        emit settingsChanged();
    }
    void setShortcutNewTab(const QString &v) {
        m_settings.setValue("shortcuts/newTab", v);
        emit settingsChanged();
    }
    void setShortcutCloseTab(const QString &v) {
        m_settings.setValue("shortcuts/closeTab", v);
        emit settingsChanged();
    }
    void setShortcutFind(const QString &v) {
        m_settings.setValue("shortcuts/find", v);
        emit settingsChanged();
    }
    void setShortcutSpeak(const QString &v) {
        m_settings.setValue("shortcuts/speak", v);
        emit settingsChanged();
    }
    void setShortcutStopSpeech(const QString &v) {
        m_settings.setValue("shortcuts/stopSpeech", v);
        emit settingsChanged();
    }
    void setShortcutBookmarks(const QString &v) {
        m_settings.setValue("shortcuts/bookmarks", v);
        emit settingsChanged();
    }
    void setShortcutRefresh(const QString &v) {
        m_settings.setValue("shortcuts/refresh", v);
        emit settingsChanged();
    }

    void setShowTabAlways(bool v) {
        m_settings.setValue("ui/showTabAlways", v);
        emit settingsChanged();
    }

    void setTerminal(const QString &v) {
        m_settings.setValue("system/terminal", v);
        emit settingsChanged();
    }

    void setTtsEngine(const QString &v) {
        m_settings.setValue("tts/engine", v);
        emit settingsChanged();
    }
    void setTtsRate(double v) {
        m_settings.setValue("tts/rate", v);
        emit settingsChanged();
    }
    void setTtsPitch(double v) {
        m_settings.setValue("tts/pitch", v);
        emit settingsChanged();
    }
    void setTtsVolume(double v) {
        m_settings.setValue("tts/volume", v);
        emit settingsChanged();
    }
    void setTtsVoice(const QString &v) {
        m_settings.setValue("tts/voice", v);
        emit settingsChanged();
    }

    void reset() {
        m_settings.clear();
        emit settingsChanged();
    }

signals:
    void settingsChanged();

private:
    Settings() : m_settings("error.os", "error_doc") {}
    QSettings m_settings;
};

class ManpageLoaderWorker : public QObject {
    Q_OBJECT

public:
    explicit ManpageLoaderWorker(QObject *parent = nullptr) : QObject(parent) {}

public slots:
    void loadManpages() {
        QProcess *process = new QProcess(this);

        connect(process, &QProcess::finished, this, [this, process](int exitCode) {
            if (exitCode == 0) {
                QString output = process->readAllStandardOutput();
                emit manpagesLoaded(output);
            } else {
                emit manpagesLoaded("");
            }
            process->deleteLater();
        });

        connect(process, &QProcess::errorOccurred, this, [this, process](QProcess::ProcessError error) {
            qWarning() << "Manpage process error:" << error;
            emit manpagesLoaded("");
            process->deleteLater();
        });

        process->start("man", QStringList() << "-k" << ".");
    }

signals:
    void manpagesLoaded(const QString &output);
};

class NotFoundPage {
public:
    static QString generate(const QString &path) {
        return QString(
                   "<html><head><title>404 - Page Not Found</title></head>"
                   "<body style='font-family: sans-serif; text-align: center; padding: 50px;'>"
                   "<h1 style='color: #c0392b;'>404</h1>"
                   "<h2>Page Not Found</h2>"
                   "<p>The requested page <code>%1</code> could not be found.</p>"
                   "<p><a href=':/'>Return to Welcome</a></p>"
                   "<hr><small>error.doc Documentation Viewer</small>"
                   "</body></html>"
                   ).arg(path.toHtmlEscaped());
    }
};


class CustomTagProcessor {
public:
    static QString processHtml(const QString &html, QObject *parent = nullptr) {
        QString result = html;

        QRegularExpressionMatchIterator fileIt = FILE_TAG_REGEX.globalMatch(result);
        while (fileIt.hasNext()) {
            QRegularExpressionMatch match = fileIt.next();
            QString fileUrl = match.captured(1);
            QString replacement = generateFileWidget(fileUrl, parent);
            result.replace(match.captured(0), replacement);
        }

        QRegularExpressionMatchIterator iconIt = ICON_TAG_REGEX.globalMatch(result);
        while (iconIt.hasNext()) {
            QRegularExpressionMatch match = iconIt.next();
            QString iconName = match.captured(1);
            QString replacement = generateIconTag(iconName);
            result.replace(match.captured(0), replacement);
        }

        QRegularExpressionMatchIterator pageIt = PAGE_ICON_TAG_REGEX.globalMatch(result);
        while (pageIt.hasNext()) {
            QRegularExpressionMatch match = pageIt.next();
            QString iconName = match.captured(1);
            QString replacement = generatePageIconTag(iconName);
            result.replace(match.captured(0), replacement);
        }

        QRegularExpressionMatchIterator bashIt = BASH_TAG_REGEX.globalMatch(result);
        while (bashIt.hasNext()) {
            QRegularExpressionMatch match = bashIt.next();
            QString bashCode = match.captured(1);
            QString replacement = generateBashWidget(bashCode, parent);
            result.replace(match.captured(0), replacement);
        }

        return result;
    }

private:
    static QString generateFileWidget(const QString &filePath, QObject *parent) {
        QFileInfo info(filePath);
        QFileIconProvider iconProvider;
        QIcon icon = iconProvider.icon(info);

        return QString(
                   "<div style='border: 1px solid #ccc; padding: 10px; margin: 10px 0; border-radius: 5px;'>"
                   "<table><tr>"
                   "<td><img src='data:image/png;base64,%1' width='32' height='32'></td>"
                   "<td style='padding-left: 10px;'>"
                   "<b>%2</b><br>"
                   "<small>%3</small><br>"
                   "<small>%4 | %5</small><br>"
                   "<a href='file://%6'>Open File</a>"
                   "</td>"
                   "</tr></table>"
                   "</div>"
                   ).arg(iconToBase64(icon))
            .arg(info.fileName().toHtmlEscaped())
            .arg(filePath.toHtmlEscaped())
            .arg(info.suffix().toUpper())
            .arg(formatSize(info.size()))
            .arg(filePath);
    }

    static QString generateIconTag(const QString &iconName) {
        QIcon icon = QIcon::fromTheme(iconName);
        if (icon.isNull()) icon = QIcon::fromTheme("image-missing");

        return QString("<img src='data:image/png;base64,%1' alt='%2' style='vertical-align: middle;'>")
            .arg(iconToBase64(icon))
            .arg(iconName);
    }

    static QString generatePageIconTag(const QString &iconName) {
        return QString("<span data-page-icon='%1'></span>").arg(iconName);
    }

    static QString generateBashWidget(const QString &code, QObject *parent) {
        QString escapedCode = code.toHtmlEscaped();
        return QString(
                   "<div style='background: #2d2d2d; color: #f8f8f8; padding: 10px; margin: 10px 0; border-radius: 5px; font-family: monospace;'>"
                   "<pre>%1</pre>"
                   "<button onclick='runBashCode(this)' data-code='%2' style='margin-top: 5px;'>▶ Run in Terminal</button>"
                   "</div>"
                   ).arg(escapedCode)
            .arg(code.toHtmlEscaped());
    }

    static QString iconToBase64(const QIcon &icon) {
        QPixmap pixmap = icon.pixmap(32, 32);
        QByteArray bytes;
        QBuffer buffer(&bytes);
        buffer.open(QIODevice::WriteOnly);
        pixmap.save(&buffer, "PNG");
        return bytes.toBase64();
    }

    static QString formatSize(qint64 bytes) {
        if (bytes < 1024) return QString::number(bytes) + " B";
        if (bytes < 1024 * 1024) return QString::number(bytes / 1024) + " KB";
        return QString::number(bytes / (1024 * 1024)) + " MB";
    }
};


class FindBar : public QWidget {
    Q_OBJECT

public:
    explicit FindBar(QTextBrowser *browser, QWidget *parent = nullptr)
        : QWidget(parent), m_browser(browser)
    {
        setVisible(false);

        auto *layout = new QHBoxLayout(this);
        layout->setContentsMargins(5, 5, 5, 5);

        m_findEdit = new QLineEdit(this);
        m_findEdit->setPlaceholderText("Find...");

        m_nextBtn = new QPushButton("Next", this);
        m_prevBtn = new QPushButton("Previous", this);
        m_closeBtn = new QPushButton("×", this);
        m_closeBtn->setFixedSize(30, 25);

        layout->addWidget(new QLabel("Find:"));
        layout->addWidget(m_findEdit);
        layout->addWidget(m_nextBtn);
        layout->addWidget(m_prevBtn);
        layout->addStretch();
        layout->addWidget(m_closeBtn);

        connect(m_findEdit, &QLineEdit::textChanged, this, &FindBar::findText);
        connect(m_nextBtn, &QPushButton::clicked, [this]() { findNext(); });
        connect(m_prevBtn, &QPushButton::clicked, [this]() { findPrevious(); });
        connect(m_closeBtn, &QPushButton::clicked, [this]() { hide(); });

        auto *shortcut = new QShortcut(QKeySequence("Ctrl+F"), this);
        connect(shortcut, &QShortcut::activated, [this]() {
            show();
            m_findEdit->setFocus();
            m_findEdit->selectAll();
        });

        auto *escapeShortcut = new QShortcut(QKeySequence("Esc"), this);
        connect(escapeShortcut, &QShortcut::activated, [this]() {
            hide();
            m_browser->setFocus();
        });
    }

    void setBrowser(QTextBrowser *browser) {
        m_browser = browser;
    }

private slots:
    void findText() {
        if (!m_browser) return;
        QString text = m_findEdit->text();
        if (!text.isEmpty()) {
            bool found = m_browser->find(text);
            if (!found) {
                QTextCursor cursor = m_browser->textCursor();
                cursor.movePosition(QTextCursor::Start);
                m_browser->setTextCursor(cursor);
                m_browser->find(text);
            }
        }
    }

    void findNext() {
        if (m_browser && !m_findEdit->text().isEmpty()) {
            m_browser->find(m_findEdit->text());
        }
    }

    void findPrevious() {
        if (m_browser && !m_findEdit->text().isEmpty()) {
            m_browser->find(m_findEdit->text(), QTextDocument::FindBackward);
        }
    }

private:
    QTextBrowser *m_browser;
    QLineEdit *m_findEdit;
    QPushButton *m_nextBtn, *m_prevBtn, *m_closeBtn;
};


class DocumentUrl : public QObject {
    Q_OBJECT

public:
    enum Scheme { Root, Err, Man, Doc };

    explicit DocumentUrl(const QString &url = ":/", QObject *parent = nullptr)
        : QObject(parent), m_url(url) { parse(); }

    void setUrl(const QString &url) {
        if (m_url == url) return;
        m_url = url;
        parse();
        emit urlChanged(m_url);
    }

    QString url() const { return m_url; }
    Scheme scheme() const { return m_scheme; }
    QString path() const { return m_path; }
    QStringList pathParts() const { return m_pathParts; }

    bool isRoot() const { return m_scheme == Root; }
    bool isErr() const { return m_scheme == Err; }
    bool isMan() const { return m_scheme == Man; }
    bool isDoc() const { return m_scheme == Doc; }

signals:
    void urlChanged(const QString &url);

private:
    void parse() {
        if (m_url == ":/") {
            m_scheme = Root;
            m_path = "";
            m_pathParts.clear();
            return;
        }

        if (m_url.startsWith(":/err/")) {
            m_scheme = Err;
            m_path = m_url.mid(6);
        } else if (m_url.startsWith(":/man/")) {
            m_scheme = Man;
            m_path = m_url.mid(6);
        } else if (m_url.startsWith(":/doc/")) {
            m_scheme = Doc;
            m_path = m_url.mid(6);
        } else {
            m_scheme = Root;
            m_path = "";
        }

        m_pathParts = m_path.split('/', Qt::SkipEmptyParts);
    }

    QString m_url;
    Scheme m_scheme;
    QString m_path;
    QStringList m_pathParts;
};


struct Bookmark {
    QString id, title, url;
    QDateTime created;
};


class BookmarkStore : public QObject {
    Q_OBJECT

public:
    explicit BookmarkStore(QObject *parent = nullptr) : QObject(parent) { load(); }

    void add(const Bookmark &bm) {
        m_bookmarks.append(bm);
        save();
        emit changed();
    }

    void remove(const QString &id) {
        m_bookmarks.erase(std::remove_if(m_bookmarks.begin(), m_bookmarks.end(),
                                         [&id](const Bookmark &b) { return b.id == id; }), m_bookmarks.end());
        save();
        emit changed();
    }

    QList<Bookmark> all() const { return m_bookmarks; }

signals:
    void changed();

private:
    QList<Bookmark> m_bookmarks;

    void load() {
        QString path = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
        QDir().mkpath(path);
        QSettings settings(path + "/bookmarks.ini", QSettings::IniFormat);

        int size = settings.beginReadArray("bookmarks");
        for (int i = 0; i < size; ++i) {
            settings.setArrayIndex(i);
            Bookmark bm;
            bm.id = settings.value("id").toString();
            bm.title = settings.value("title").toString();
            bm.url = settings.value("url").toString();
            bm.created = settings.value("created").toDateTime();
            m_bookmarks.append(bm);
        }
        settings.endArray();
    }

    void save() {
        QString path = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
        QSettings settings(path + "/bookmarks.ini", QSettings::IniFormat);

        settings.beginWriteArray("bookmarks");
        for (int i = 0; i < m_bookmarks.size(); ++i) {
            settings.setArrayIndex(i);
            const Bookmark &bm = m_bookmarks[i];
            settings.setValue("id", bm.id);
            settings.setValue("title", bm.title);
            settings.setValue("url", bm.url);
            settings.setValue("created", bm.created);
        }
        settings.endArray();
    }
};


class HighlightDialog : public QDialog {
    Q_OBJECT

public:
    explicit HighlightDialog(QWidget *parent = nullptr) : QDialog(parent) {
        setWindowTitle("Highlight Text");
        setMinimumWidth(400);

        auto *layout = new QVBoxLayout(this);

        auto *fgLayout = new QHBoxLayout();
        m_fgBtn = new QPushButton("FG Color", this);
        m_fgEdit = new QLineEdit("#000000", this);
        m_fgEdit->setMaxLength(7);
        fgLayout->addWidget(new QLabel("Foreground:", this));
        fgLayout->addWidget(m_fgBtn);
        fgLayout->addWidget(m_fgEdit);

        auto *bgLayout = new QHBoxLayout();
        m_bgBtn = new QPushButton("BG Color", this);
        m_bgEdit = new QLineEdit("#ffff00", this);
        m_bgEdit->setMaxLength(7);
        bgLayout->addWidget(new QLabel("Background:", this));
        bgLayout->addWidget(m_bgBtn);
        bgLayout->addWidget(m_bgEdit);

        auto *buttons = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);

        layout->addLayout(fgLayout);
        layout->addLayout(bgLayout);
        layout->addWidget(buttons);

        connect(m_fgBtn, &QPushButton::clicked, this, &HighlightDialog::pickFgColor);
        connect(m_bgBtn, &QPushButton::clicked, this, &HighlightDialog::pickBgColor);
        connect(m_fgEdit, &QLineEdit::textChanged, this, &HighlightDialog::updateFgPreview);
        connect(m_bgEdit, &QLineEdit::textChanged, this, &HighlightDialog::updateBgPreview);
        connect(buttons, &QDialogButtonBox::accepted, this, &QDialog::accept);
        connect(buttons, &QDialogButtonBox::rejected, this, &QDialog::reject);

        updateFgPreview();
        updateBgPreview();
    }

    QColor fgColor() const { return QColor(m_fgEdit->text()); }
    QColor bgColor() const { return QColor(m_bgEdit->text()); }

private slots:
    void pickFgColor() {
        QColor color = QColorDialog::getColor(fgColor(), this);
        if (color.isValid()) {
            m_fgEdit->setText(color.name());
        }
    }

    void pickBgColor() {
        QColor color = QColorDialog::getColor(bgColor(), this);
        if (color.isValid()) {
            m_bgEdit->setText(color.name());
        }
    }

    void updateFgPreview() {
        QString style = QString("background-color: %1; color: white;").arg(m_fgEdit->text());
        m_fgBtn->setStyleSheet(style);
    }

    void updateBgPreview() {
        QString style = QString("background-color: %1; color: black;").arg(m_bgEdit->text());
        m_bgBtn->setStyleSheet(style);
    }

private:
    QPushButton *m_fgBtn, *m_bgBtn;
    QLineEdit *m_fgEdit, *m_bgEdit;
};


class BookmarkDialog : public QDialog {
    Q_OBJECT

public:
    BookmarkDialog(BookmarkStore *store, const QString &currentUrl, const QString &currentTitle, QWidget *parent = nullptr)
        : QDialog(parent), m_store(store), m_currentUrl(currentUrl), m_currentTitle(currentTitle)
    {
        setWindowTitle("Bookmarks");
        setMinimumSize(500, 400);

        auto *layout = new QVBoxLayout(this);

        m_search = new QLineEdit(this);
        m_search->setPlaceholderText("Search bookmarks...");

        auto *actionLayout = new QHBoxLayout();
        auto *addCurrentBtn = new QPushButton(QIcon::fromTheme("bookmark-new"), "Add Current Page", this);
        actionLayout->addWidget(addCurrentBtn);

        m_list = new QListWidget(this);

        auto *buttons = new QDialogButtonBox(QDialogButtonBox::Close, this);

        layout->addWidget(m_search);
        layout->addLayout(actionLayout);
        layout->addWidget(new QLabel("Your Bookmarks:", this));
        layout->addWidget(m_list);
        layout->addWidget(buttons);

        connect(addCurrentBtn, &QPushButton::clicked, this, &BookmarkDialog::addCurrent);
        connect(m_search, &QLineEdit::textChanged, this, &BookmarkDialog::filterBookmarks);
        connect(m_list, &QListWidget::itemDoubleClicked, this, &BookmarkDialog::openBookmark);
        connect(buttons, &QDialogButtonBox::rejected, this, &QDialog::accept);
        connect(m_store, &BookmarkStore::changed, this, &BookmarkDialog::refreshList);

        refreshList();
    }

signals:
    void navigateTo(const QString &url);

private slots:
    void addCurrent() {
        Bookmark bm;
        bm.id = QDateTime::currentDateTime().toString(Qt::ISODate) + "_" +
                QString::number(QRandomGenerator::global()->generate());
        bm.title = m_currentTitle;
        bm.url = m_currentUrl;
        bm.created = QDateTime::currentDateTime();
        m_store->add(bm);
        QMessageBox::information(this, "Bookmark", "Bookmark added");
    }

    void filterBookmarks() {
        QString filter = m_search->text().toLower();
        for (int i = 0; i < m_list->count(); ++i) {
            QListWidgetItem *item = m_list->item(i);
            bool matches = item->text().toLower().contains(filter);
            item->setHidden(!matches);
        }
    }

    void openBookmark(QListWidgetItem *item) {
        QString url = item->data(Qt::UserRole).toString();
        emit navigateTo(url);
        accept();
    }

    void refreshList() {
        m_list->clear();
        for (const Bookmark &bm : m_store->all()) {
            auto *item = new QListWidgetItem(bm.title, m_list);
            item->setData(Qt::UserRole, bm.url);
            item->setToolTip(bm.url);
        }
    }

private:
    BookmarkStore *m_store;
    QString m_currentUrl, m_currentTitle;
    QLineEdit *m_search;
    QListWidget *m_list;
};

class ContentEngine : public QWidget {
    Q_OBJECT

public:
    explicit ContentEngine(QWidget *parent = nullptr) : QWidget(parent) {}
    virtual ~ContentEngine() = default;

    virtual void load(const DocumentUrl &url) = 0;
    virtual QString selectedText() const = 0;
    virtual QString allText() const = 0;
    virtual void find() = 0;
    virtual void highlightSelection(const QColor &fg, const QColor &bg) = 0;
    virtual void speakSelected() = 0;

signals:
    void titleChanged(const QString &title);
    void navigationRequested(const QString &url);
    void iconChanged(const QString &iconName);
};

class WelcomeEngine : public ContentEngine {
    Q_OBJECT

public:
    explicit WelcomeEngine(QWidget *parent = nullptr) : ContentEngine(parent) {
        auto *layout = new QVBoxLayout(this);
        layout->setAlignment(Qt::AlignCenter);

        auto *iconLabel = new QLabel(this);
        iconLabel->setPixmap(QIcon::fromTheme("error.doc", QIcon::fromTheme("help-browser")).pixmap(128, 128));
        iconLabel->setAlignment(Qt::AlignCenter);

        auto *titleLabel = new QLabel("<h1>error.doc</h1>", this);
        titleLabel->setAlignment(Qt::AlignCenter);

        auto *infoLabel = new QLabel(
            "<p>Documentation viewer for error.os</p>"
            "<p>Select an item from the tree to begin.</p>"
            "<p><b>Tips:</b><br>"
            "• Ctrl+F to search in err/ and man/ pages<br>"
            "• Bookmark any page with the bookmark button</p>",
            this
            );
        infoLabel->setAlignment(Qt::AlignCenter);
        infoLabel->setWordWrap(true);

        layout->addWidget(iconLabel);
        layout->addWidget(titleLabel);
        layout->addWidget(infoLabel);
        layout->addStretch();
    }

    void load(const DocumentUrl &) override {
        emit titleChanged("Welcome");
    }

    QString selectedText() const override { return ""; }
    QString allText() const override { return ""; }
    void find() override {}
    void highlightSelection(const QColor &, const QColor &) override {}
    void speakSelected() override {}
};



class ErrorDocEngine : public ContentEngine {
    Q_OBJECT

public:
    explicit ErrorDocEngine(QWidget *parent = nullptr) : ContentEngine(parent) {
        auto *layout = new QVBoxLayout(this);
        layout->setContentsMargins(0, 0, 0, 0);

        m_browser = new QTextBrowser(this);
        m_browser->setOpenLinks(false);
        m_browser->setContextMenuPolicy(Qt::CustomContextMenu);

        m_findBar = new FindBar(m_browser, this);
        m_findBar->hide();

        layout->addWidget(m_browser);
        layout->addWidget(m_findBar);

        connect(m_browser, &QTextBrowser::anchorClicked, this, &ErrorDocEngine::onLinkClicked);
        connect(m_browser, &QTextBrowser::customContextMenuRequested, this, &ErrorDocEngine::showContextMenu);
    }

protected:
 QVariant loadResource(int type, const QUrl &url) {
        if (url.scheme() == "icon") {
            QIcon icon = QIcon::fromTheme(url.path());
            if (!icon.isNull()) {
                return icon.pixmap(icon.availableSizes().isEmpty() ? QSize(16,16) : icon.availableSizes().first());
            }
        }
        return QVariant();
    }

    void load(const DocumentUrl &url) override {
        if (!url.isErr()) return;

        QString path = url.path();
        if (path.startsWith("/")) path = path.mid(1);

        QString qrcPath = ":/" + path;
        if (!path.endsWith(".html")) {
            qrcPath = ":/" + path + ".html";
        }

        QFile file(qrcPath);
        if (file.open(QIODevice::ReadOnly)) {
            QString html = QString::fromUtf8(file.readAll());

            QRegularExpressionMatch pageMatch = PAGE_ICON_TAG_REGEX.match(html);
            if (pageMatch.hasMatch()) {
                emit pageIconFound(pageMatch.captured(1));
                html.remove(PAGE_ICON_TAG_REGEX);
            }

            html.replace(ICON_TAG_REGEX, "<img src=\"icon://\\1\">");

            QRegularExpressionMatchIterator fileIt = FILE_TAG_REGEX.globalMatch(html);
            while (fileIt.hasNext()) {
                QRegularExpressionMatch match = fileIt.next();
                QString filePath = match.captured(1);

                QFileInfo info(filePath);
                QFileIconProvider provider;
                QIcon icon = provider.icon(info);
                QSize iconSize = icon.availableSizes().isEmpty() ? QSize(16,16) : icon.availableSizes().first();
                QPixmap pixmap = icon.pixmap(iconSize);
                QByteArray bytes;
                QBuffer buffer(&bytes);
                buffer.open(QIODevice::WriteOnly);
                pixmap.save(&buffer, "PNG");
                QString iconBase64 = QString::fromLatin1(bytes.toBase64());

                QString replacement = QString(
                                          "<a href='file://%1'><img src='data:image/png;base64,%2'> %3</a>"
                                          ).arg(filePath, iconBase64, info.fileName());

                html.replace(match.captured(0), replacement);
            }

            QRegularExpressionMatchIterator bashIt = BASH_TAG_REGEX.globalMatch(html);
            while (bashIt.hasNext()) {
                QRegularExpressionMatch match = bashIt.next();
                QString code = match.captured(1);
                QString replacement = QString(
                                          "<pre>%1</pre>"
                                          "<a href='bash://%2'>[run]</a>"
                                          ).arg(code.toHtmlEscaped(), code);
                html.replace(match.captured(0), replacement);
            }

            m_browser->setHtml(html);
            emit titleChanged(extractTitle(html));
        } else {
            m_browser->setHtml(NotFoundPage::generate(path));
            emit titleChanged("Not Found");
        }

        m_findBar->hide();
    }

    QString selectedText() const override { return m_browser->textCursor().selectedText(); }
    QString allText() const override { return m_browser->toPlainText(); }
    void find() override {
        m_findBar->show();
        m_findBar->setFocus();
    }

    void highlightSelection(const QColor &fg, const QColor &bg) override {
        QTextCursor cursor = m_browser->textCursor();
        if (cursor.hasSelection()) {
            QTextCharFormat fmt;
            fmt.setForeground(fg);
            fmt.setBackground(bg);
            cursor.mergeCharFormat(fmt);
        }
    }

    void speakSelected() override {
        QString text = selectedText();
        if (!text.isEmpty()) {
            emit speakText(text);
        }
    }

signals:
    void speakText(const QString &text);
    void requestHighlight();
    void pageIconFound(const QString &iconName);

private slots:
    void onLinkClicked(const QUrl &link) {
        if (link.scheme() == "bash") {
            QString code = QUrl::fromPercentEncoding(link.path().toUtf8());
            QString terminal = Settings::instance().terminal();
            QProcess::startDetached(terminal, QStringList() << "-e" << "bash" << "-c" << code);
        } else if (link.scheme() == "file") {
            QDesktopServices::openUrl(link);
        } else if (link.toString().startsWith(":/")) {
            emit navigationRequested(link.toString());
        }
    }

    void showContextMenu(const QPoint &pos) {
        QMenu menu;
        if (m_browser->textCursor().hasSelection()) {
            menu.addAction(QIcon::fromTheme("edit-copy"), "Copy", m_browser, &QTextBrowser::copy);
            menu.addSeparator();
            menu.addAction(QIcon::fromTheme("speak"), "Speak Selection", [this]() { speakSelected(); });
            menu.addAction(QIcon::fromTheme("format-text-color"), "Highlight", [this]() {
                emit requestHighlight();
            });
        }
        menu.exec(m_browser->mapToGlobal(pos));
    }

private:
    QString extractTitle(const QString &html) {
        QRegularExpressionMatch match = TITLE_REGEX.match(html);
        return match.hasMatch() ? match.captured(1) : "Documentation";
    }

    QTextBrowser *m_browser;
    FindBar *m_findBar;
};

class ManpageEngine : public ContentEngine {
    Q_OBJECT

public:
    explicit ManpageEngine(QWidget *parent = nullptr) : ContentEngine(parent) {
        auto *mainLayout = new QVBoxLayout(this);
        mainLayout->setContentsMargins(0, 0, 0, 0);
        mainLayout->setSpacing(0);

        auto *splitterLayout = new QHBoxLayout();

        auto *infoWidget = new QWidget(this);
        auto *infoLayout = new QVBoxLayout(infoWidget);

        m_iconLabel = new QLabel(this);
        m_iconLabel->setAlignment(Qt::AlignCenter);
        m_iconLabel->setFixedSize(100, 100);

        m_titleLabel = new QLabel(this);
        QFont titleFont = m_titleLabel->font();
        titleFont.setPointSize(titleFont.pointSize() + 2);
        titleFont.setBold(true);
        m_titleLabel->setFont(titleFont);
        m_titleLabel->setAlignment(Qt::AlignCenter);
        m_titleLabel->setWordWrap(true);

        m_dateLabel = new QLabel(this);
        m_dateLabel->setAlignment(Qt::AlignCenter);

        m_pathLabel = new QLabel(this);
        m_pathLabel->setAlignment(Qt::AlignCenter);
        m_pathLabel->setWordWrap(true);

        m_descLabel = new QLabel(this);
        m_descLabel->setAlignment(Qt::AlignTop | Qt::AlignLeft);
        m_descLabel->setWordWrap(true);

        infoLayout->addWidget(m_iconLabel);
        infoLayout->addWidget(m_titleLabel);
        infoLayout->addWidget(m_dateLabel);
        infoLayout->addWidget(m_pathLabel);
        infoLayout->addWidget(m_descLabel);
        infoLayout->addStretch();

        infoWidget->setMaximumWidth(250);

        auto *browserWidget = new QWidget(this);
        auto *browserLayout = new QVBoxLayout(browserWidget);
        browserLayout->setContentsMargins(0, 0, 0, 0);

        m_browser = new QTextBrowser(this);
        m_browser->setFont(QFont("Monospace"));
        m_browser->setContextMenuPolicy(Qt::CustomContextMenu);

        m_findBar = new FindBar(m_browser, this);
        m_findBar->hide();

        browserLayout->addWidget(m_browser);
        browserLayout->addWidget(m_findBar);

        auto *splitter = new QSplitter(Qt::Horizontal, this);
        splitter->addWidget(infoWidget);
        splitter->addWidget(browserWidget);
        splitter->setStretchFactor(0, 0);
        splitter->setStretchFactor(1, 1);

        splitterLayout->addWidget(splitter);
        mainLayout->addLayout(splitterLayout);

        connect(m_browser, &QTextBrowser::customContextMenuRequested, this, &ManpageEngine::showContextMenu);
    }

    void load(const DocumentUrl &url) override {
        if (!url.isMan()) return;

        QStringList parts = url.pathParts();
        if (parts.size() < 2) {
            m_browser->setPlainText("Invalid manpage URL");
            return;
        }

        QString section = parts[0];
        QString name = parts[1];

        loadManpage(name, section);
        m_findBar->hide();
    }
    QString selectedText() const override { return m_browser->textCursor().selectedText(); }
    QString allText() const override { return m_browser->toPlainText(); }
    void find() override {
        m_findBar->show();
        m_findBar->setFocus();
    }

    void highlightSelection(const QColor &fg, const QColor &bg) override {
        QTextCursor cursor = m_browser->textCursor();
        if (cursor.hasSelection()) {
            QTextCharFormat fmt;
            fmt.setForeground(fg);
            fmt.setBackground(bg);
            cursor.mergeCharFormat(fmt);
        }
    }

    void speakSelected() override {
        QString text = selectedText();
        if (!text.isEmpty()) {
            emit speakText(text);
        }
    }

signals:
    void speakText(const QString &text);
    void requestHighlight();

private slots:
    void showContextMenu(const QPoint &pos) {
        QMenu menu;
        if (m_browser->textCursor().hasSelection()) {
            menu.addAction(QIcon::fromTheme("edit-copy"), "Copy", m_browser, &QTextBrowser::copy);
            menu.addSeparator();
            menu.addAction(QIcon::fromTheme("speak"), "Speak Selection", [this]() { speakSelected(); });
            menu.addAction(QIcon::fromTheme("format-text-color"), "Highlight", [this]() {
                emit requestHighlight();
            });
        }
        menu.exec(m_browser->mapToGlobal(pos));
    }

private:
    void loadManpage(const QString &name, const QString &section) {
        QIcon icon = QIcon::fromTheme(name);
        if (icon.isNull()) icon = QIcon::fromTheme("text-x-generic");
        m_iconLabel->setPixmap(icon.pixmap(100, 100));
        emit iconChanged(name);

        m_titleLabel->setText(QString("<b>%1(%2)</b>").arg(name).arg(section));

        m_pathLabel->setText("Loading...");
        m_dateLabel->setText("");

        QProcess *whichProcess = new QProcess(this);
        connect(whichProcess, &QProcess::finished, this, [this, whichProcess, name, section](int exitCode) {
            if (exitCode == 0) {
                QString path = whichProcess->readAllStandardOutput().trimmed();
                if (!path.isEmpty()) {
                    QFileInfo info(path);
                    m_pathLabel->setText(path);
                    m_dateLabel->setText(info.lastModified().toString("yyyy-MM-dd"));
                } else {
                    m_pathLabel->setText("System command");
                    m_dateLabel->setText("");
                }
            } else {
                m_pathLabel->setText("System command");
                m_dateLabel->setText("");
            }
            whichProcess->deleteLater();
        });
        whichProcess->start("which", QStringList() << name);

        QProcess *process = new QProcess(this);
        connect(process, QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished),
                this, [this, process, name, section](int exitCode, QProcess::ExitStatus) {
                    if (exitCode == 0) {
                        QString content = process->readAllStandardOutput();
                        m_browser->setHtml(formatManpage(content));

                        QString desc = extractDescription(content);
                        m_descLabel->setText(desc);

                        emit titleChanged(QString("%1(%2)").arg(name).arg(section));
                    } else {
                        m_browser->setPlainText("Failed to load manpage");
                    }
                    process->deleteLater();
                });
        process->start("man", QStringList() << section << name);
    }

    QString formatManpage(const QString &raw) {
        QStringList lines = raw.split('\n');
        QString html = "<html><head><style>pre { margin: 0; } h2 { margin-top: 20px; }</style></head><body>";

        for (const QString &line : std::as_const(lines)) {
            QString trimmed = line.trimmed();
            if (!trimmed.isEmpty() && HEADER_REGEX.match(trimmed).hasMatch()) {
                html += QString("<h2>%1</h2>").arg(trimmed);
            } else {
                html += QString("<pre>%1</pre>").arg(line.toHtmlEscaped());
            }
        }

        html += "</body></html>";
        return html;
    }

    QString extractDescription(const QString &content) {
        QStringList lines = content.split('\n');
        bool inName = false;
        QString desc;

        for (const QString &line : std::as_const(lines)) {
            QString trimmed = line.trimmed();
            if (trimmed == "NAME") {
                inName = true;
                continue;
            }
            if (inName) {
                if (trimmed.isEmpty()) continue;
                if (trimmed.startsWith("SYNOPSIS") || trimmed.startsWith("DESCRIPTION")) {
                    break;
                }
                desc += line + "\n";
                if (desc.length() > 200) break;
            }
        }

        return desc.trimmed();
    }

    QLabel *m_iconLabel, *m_titleLabel, *m_dateLabel, *m_pathLabel, *m_descLabel;
    QTextBrowser *m_browser;
    FindBar *m_findBar;
};


class SettingsPage : public QScrollArea {
    Q_OBJECT

public:
    explicit SettingsPage(QWidget *parent = nullptr) : QScrollArea(parent) {
        setWidgetResizable(true);
        setFrameShape(QFrame::NoFrame);

        auto *content = new QWidget();
        auto *layout = new QVBoxLayout(content);
        layout->setSpacing(20);

        auto *shortcutGroup = new QGroupBox("Keyboard Shortcuts", this);
        auto *shortcutLayout = new QFormLayout(shortcutGroup);

        m_optionsShortcut = new QKeySequenceEdit(this);
        shortcutLayout->addRow("Options Menu:", m_optionsShortcut);

        m_newTabShortcut = new QKeySequenceEdit(this);
        shortcutLayout->addRow("New Tab:", m_newTabShortcut);

        m_closeTabShortcut = new QKeySequenceEdit(this);
        shortcutLayout->addRow("Close Tab:", m_closeTabShortcut);

        m_findShortcut = new QKeySequenceEdit(this);
        shortcutLayout->addRow("Find in Page:", m_findShortcut);

        m_speakShortcut = new QKeySequenceEdit(this);
        shortcutLayout->addRow("Speak Selection:", m_speakShortcut);

        m_stopSpeechShortcut = new QKeySequenceEdit(this);
        shortcutLayout->addRow("Stop Speech:", m_stopSpeechShortcut);

        m_bookmarksShortcut = new QKeySequenceEdit(this);
        shortcutLayout->addRow("Show Bookmarks:", m_bookmarksShortcut);

        m_refreshShortcut = new QKeySequenceEdit(this);
        shortcutLayout->addRow("Refresh:", m_refreshShortcut);

        auto *uiGroup = new QGroupBox("User Interface", this);
        auto *uiLayout = new QFormLayout(uiGroup);

        m_showTabAlways = new QCheckBox("Always show tab bar (even with single tab)", this);
        uiLayout->addRow(m_showTabAlways);

        auto *termGroup = new QGroupBox("Terminal", this);
        auto *termLayout = new QFormLayout(termGroup);

        m_terminal = new QComboBox(this);
        m_terminal->addItems(QStringList() << "konsole" << "xterm" << "gnome-terminal" << "xfce4-terminal" << "kitty" << "alacritty");
        m_terminal->setEditable(true);
        m_terminal->setInsertPolicy(QComboBox::NoInsert);
        termLayout->addRow("Terminal Emulator:", m_terminal);

        auto *ttsGroup = new QGroupBox("Text-to-Speech", this);
        auto *ttsLayout = new QFormLayout(ttsGroup);

        m_ttsEngine = new QComboBox(this);
        m_ttsEngine->addItem("Default");
        m_ttsEngine->addItems(QTextToSpeech::availableEngines());
        ttsLayout->addRow("Engine:", m_ttsEngine);

        m_ttsRate = new QSlider(Qt::Horizontal, this);
        m_ttsRate->setRange(-10, 10);
        m_ttsRate->setTickPosition(QSlider::TicksBelow);
        m_ttsRate->setTickInterval(2);
        m_ttsRateLabel = new QLabel(this);
        auto *rateLayout = new QHBoxLayout();
        rateLayout->addWidget(m_ttsRate);
        rateLayout->addWidget(m_ttsRateLabel);
        ttsLayout->addRow("Rate:", rateLayout);

        m_ttsPitch = new QSlider(Qt::Horizontal, this);
        m_ttsPitch->setRange(-10, 10);
        m_ttsPitch->setTickPosition(QSlider::TicksBelow);
        m_ttsPitch->setTickInterval(2);
        m_ttsPitchLabel = new QLabel(this);
        auto *pitchLayout = new QHBoxLayout();
        pitchLayout->addWidget(m_ttsPitch);
        pitchLayout->addWidget(m_ttsPitchLabel);
        ttsLayout->addRow("Pitch:", pitchLayout);

        m_ttsVolume = new QSlider(Qt::Horizontal, this);
        m_ttsVolume->setRange(0, 100);
        m_ttsVolume->setTickPosition(QSlider::TicksBelow);
        m_ttsVolume->setTickInterval(10);
        m_ttsVolumeLabel = new QLabel(this);
        auto *volumeLayout = new QHBoxLayout();
        volumeLayout->addWidget(m_ttsVolume);
        volumeLayout->addWidget(m_ttsVolumeLabel);
        ttsLayout->addRow("Volume:", volumeLayout);

        m_ttsVoice = new QComboBox(this);
        ttsLayout->addRow("Voice:", m_ttsVoice);

        auto *btnLayout = new QHBoxLayout();
        auto *saveBtn = new QPushButton(QIcon::fromTheme("document-save"), "Save Settings", this);
        auto *resetBtn = new QPushButton(QIcon::fromTheme("edit-clear"), "Reset All", this);
        auto *cancelBtn = new QPushButton(QIcon::fromTheme("window-close"), "Cancel", this);

        btnLayout->addWidget(saveBtn);
        btnLayout->addWidget(resetBtn);
        btnLayout->addWidget(cancelBtn);
        btnLayout->addStretch();

        layout->addWidget(shortcutGroup);
        layout->addWidget(uiGroup);
        layout->addWidget(termGroup);
        layout->addWidget(ttsGroup);
        layout->addLayout(btnLayout);
        layout->addStretch();

        setWidget(content);

        connect(saveBtn, &QPushButton::clicked, this, &SettingsPage::saveSettings);
        connect(resetBtn, &QPushButton::clicked, this, &SettingsPage::resetSettings);
        connect(cancelBtn, &QPushButton::clicked, this, &SettingsPage::cancel);

        connect(m_ttsRate, &QSlider::valueChanged, this, &SettingsPage::updateRateLabel);
        connect(m_ttsPitch, &QSlider::valueChanged, this, &SettingsPage::updatePitchLabel);
        connect(m_ttsVolume, &QSlider::valueChanged, this, &SettingsPage::updateVolumeLabel);

        connect(m_ttsEngine, QOverload<int>::of(&QComboBox::currentIndexChanged),
                this, &SettingsPage::onEngineChanged);

        loadSettings();

        QTimer::singleShot(100, this, &SettingsPage::populateVoices);
    }

    ~SettingsPage() {
        if (m_testSpeech) {
            m_testSpeech->stop();
            delete m_testSpeech;
        }
    }

signals:
    void settingsChanged();

private slots:
    void saveSettings() {
        auto &s = Settings::instance();

        s.setShortcutOptions(m_optionsShortcut->keySequence().toString());
        s.setShortcutNewTab(m_newTabShortcut->keySequence().toString());
        s.setShortcutCloseTab(m_closeTabShortcut->keySequence().toString());
        s.setShortcutFind(m_findShortcut->keySequence().toString());
        s.setShortcutSpeak(m_speakShortcut->keySequence().toString());
        s.setShortcutStopSpeech(m_stopSpeechShortcut->keySequence().toString());
        s.setShortcutBookmarks(m_bookmarksShortcut->keySequence().toString());
        s.setShortcutRefresh(m_refreshShortcut->keySequence().toString());

        s.setShowTabAlways(m_showTabAlways->isChecked());

        s.setTerminal(m_terminal->currentText());

        QString engine = m_ttsEngine->currentText();
        if (engine == "Default") engine = "";
        s.setTtsEngine(engine);
        s.setTtsRate(m_ttsRate->value() / 10.0);
        s.setTtsPitch(m_ttsPitch->value() / 10.0);
        s.setTtsVolume(m_ttsVolume->value() / 100.0);
        s.setTtsVoice(m_ttsVoice->currentText());

        emit settingsChanged();

        QMessageBox::information(this, "Settings", "Settings saved successfully.\nSome changes may require restart.");
    }

    void resetSettings() {
        int result = QMessageBox::question(this, "Reset Settings",
                                           "Reset all settings to defaults? This cannot be undone.",
                                           QMessageBox::Yes | QMessageBox::No);
        if (result == QMessageBox::Yes) {
            Settings::instance().reset();
            loadSettings();
            emit settingsChanged();
            QMessageBox::information(this, "Settings", "Settings reset to defaults.");
        }
    }

    void cancel() {
        loadSettings();
        QMessageBox::information(this, "Settings", "Changes discarded.");
    }

    void updateRateLabel(int value) {
        double rate = value / 10.0;
        m_ttsRateLabel->setText(QString("%1").arg(rate, 0, 'f', 1));
    }

    void updatePitchLabel(int value) {
        double pitch = value / 10.0;
        m_ttsPitchLabel->setText(QString("%1").arg(pitch, 0, 'f', 1));
    }

    void updateVolumeLabel(int value) {
        m_ttsVolumeLabel->setText(QString("%1%").arg(value));
    }

    void onEngineChanged(int index) {
        Q_UNUSED(index)
        populateVoices();
        testCurrentVoice();
    }

    void onVoiceChanged(int index) {
        Q_UNUSED(index)
        if (m_testSpeech) {
            m_testSpeech->stop();
            m_testSpeech->say("This is a test of the selected voice.");
        }
    }

    void populateVoices() {
        m_ttsVoice->clear();

        if (!m_testSpeech) {
            m_testSpeech = new QTextToSpeech(this);
            connect(m_testSpeech, &QTextToSpeech::stateChanged, this, &SettingsPage::onSpeechStateChanged);
        }

        QString engine = m_ttsEngine->currentText();
        if (engine == "Default") engine = "";

        if (m_testSpeech->engine() != engine) {
            m_testSpeech->setEngine(engine);
        }

        QList<QVoice> voices = m_testSpeech->availableVoices();
        for (const QVoice &voice : std::as_const(voices)) {
            m_ttsVoice->addItem(voice.name(), voice.name());
        }

        if (m_ttsVoice->count() == 0) {
            m_ttsVoice->addItem("Default");
        }

        disconnect(m_ttsVoice, QOverload<int>::of(&QComboBox::currentIndexChanged),
                   this, &SettingsPage::onVoiceChanged);

        QString savedVoice = Settings::instance().ttsVoice();
        int idx = m_ttsVoice->findText(savedVoice);
        if (idx >= 0) {
            m_ttsVoice->setCurrentIndex(idx);
        }

        connect(m_ttsVoice, QOverload<int>::of(&QComboBox::currentIndexChanged),
                this, &SettingsPage::onVoiceChanged);
    }

    void testCurrentVoice() {
        if (m_testSpeech && m_ttsVoice->currentIndex() >= 0) {
            QString voiceName = m_ttsVoice->currentText();
            if (voiceName != "Default") {
                QList<QVoice> voices = m_testSpeech->availableVoices();
                for (const QVoice &voice : voices) {
                    if (voice.name() == voiceName) {
                        m_testSpeech->setVoice(voice);
                        break;
                    }
                }
            }
        }
    }

    void onSpeechStateChanged(QTextToSpeech::State state) {

        if (state == QTextToSpeech::Ready) {
        }
    }

    void loadSettings() {
        auto &s = Settings::instance();

        m_optionsShortcut->setKeySequence(QKeySequence(s.shortcutOptions()));
        m_newTabShortcut->setKeySequence(QKeySequence(s.shortcutNewTab()));
        m_closeTabShortcut->setKeySequence(QKeySequence(s.shortcutCloseTab()));
        m_findShortcut->setKeySequence(QKeySequence(s.shortcutFind()));
        m_speakShortcut->setKeySequence(QKeySequence(s.shortcutSpeak()));
        m_stopSpeechShortcut->setKeySequence(QKeySequence(s.shortcutStopSpeech()));
        m_bookmarksShortcut->setKeySequence(QKeySequence(s.shortcutBookmarks()));
        m_refreshShortcut->setKeySequence(QKeySequence(s.shortcutRefresh()));

        m_showTabAlways->setChecked(s.showTabAlways());

        int idx = m_terminal->findText(s.terminal());
        if (idx >= 0) m_terminal->setCurrentIndex(idx);
        else m_terminal->setEditText(s.terminal());

        QString engine = s.ttsEngine();
        if (engine.isEmpty()) engine = "Default";
        idx = m_ttsEngine->findText(engine);
        if (idx >= 0) m_ttsEngine->setCurrentIndex(idx);

        m_ttsRate->setValue(s.ttsRate() * 10);
        m_ttsPitch->setValue(s.ttsPitch() * 10);
        m_ttsVolume->setValue(s.ttsVolume() * 100);

        updateRateLabel(m_ttsRate->value());
        updatePitchLabel(m_ttsPitch->value());
        updateVolumeLabel(m_ttsVolume->value());

        QTimer::singleShot(200, this, &SettingsPage::populateVoices);
    }

private:
    QKeySequenceEdit *m_optionsShortcut;
    QKeySequenceEdit *m_newTabShortcut;
    QKeySequenceEdit *m_closeTabShortcut;
    QKeySequenceEdit *m_findShortcut;
    QKeySequenceEdit *m_speakShortcut;
    QKeySequenceEdit *m_stopSpeechShortcut;
    QKeySequenceEdit *m_bookmarksShortcut;
    QKeySequenceEdit *m_refreshShortcut;

    QCheckBox *m_showTabAlways;

    QComboBox *m_terminal;

    QComboBox *m_ttsEngine;
    QSlider *m_ttsRate;
    QSlider *m_ttsPitch;
    QSlider *m_ttsVolume;
    QLabel *m_ttsRateLabel;
    QLabel *m_ttsPitchLabel;
    QLabel *m_ttsVolumeLabel;
    QComboBox *m_ttsVoice;

    QTextToSpeech *m_testSpeech = nullptr;
};

class BookmarksPage : public QWidget {
    Q_OBJECT

public:
    BookmarksPage(BookmarkStore *store, QWidget *parent = nullptr)
        : QWidget(parent), m_store(store)
    {
        auto *layout = new QVBoxLayout(this);

        auto *toolbar = new QHBoxLayout();
        auto *deleteBtn = new QPushButton(QIcon::fromTheme("edit-delete"), "Delete Selected", this);
        auto *deleteAllBtn = new QPushButton(QIcon::fromTheme("edit-clear"), "Delete All", this);

        toolbar->addWidget(deleteBtn);
        toolbar->addWidget(deleteAllBtn);
        toolbar->addStretch();

        m_list = new QListWidget(this);
        m_list->setContextMenuPolicy(Qt::CustomContextMenu);
        m_list->setSelectionMode(QAbstractItemView::ExtendedSelection);

        layout->addLayout(toolbar);
        layout->addWidget(m_list);

        connect(deleteBtn, &QPushButton::clicked, this, &BookmarksPage::deleteSelected);
        connect(deleteAllBtn, &QPushButton::clicked, this, &BookmarksPage::deleteAll);
        connect(m_list, &QListWidget::itemDoubleClicked, this, &BookmarksPage::openBookmark);
        connect(m_list, &QListWidget::customContextMenuRequested, this, &BookmarksPage::showContextMenu);
        connect(m_store, &BookmarkStore::changed, this, &BookmarksPage::refreshList);

        refreshList();
    }

signals:
    void navigateTo(const QString &url);

private slots:
    void deleteSelected() {
        QList<QListWidgetItem*> selected = m_list->selectedItems();
        if (selected.isEmpty()) {
            QMessageBox::information(this, "Delete", "No bookmarks selected");
            return;
        }

        int result = QMessageBox::question(this, "Delete Bookmarks",
                                           QString("Delete %1 selected bookmark(s)?").arg(selected.size()),
                                           QMessageBox::Yes | QMessageBox::No);
        if (result == QMessageBox::Yes) {
            for (QListWidgetItem *item : selected) {
                QString id = item->data(Qt::UserRole + 1).toString();
                m_store->remove(id);
            }
        }
    }

    void deleteAll() {
        if (m_list->count() == 0) {
            QMessageBox::information(this, "Delete All", "No bookmarks to delete");
            return;
        }

        int result = QMessageBox::question(this, "Delete All Bookmarks",
                                           "Delete all bookmarks? This cannot be undone.",
                                           QMessageBox::Yes | QMessageBox::No);
        if (result == QMessageBox::Yes) {
            for (const Bookmark &bm : m_store->all()) {
                m_store->remove(bm.id);
            }
        }
    }

    void showContextMenu(const QPoint &pos) {
        QListWidgetItem *item = m_list->itemAt(pos);
        if (!item) return;

        QMenu menu;
        menu.addAction(QIcon::fromTheme("document-open"), "Open", [this, item]() {
            openBookmark(item);
        });
        menu.addSeparator();
        menu.addAction(QIcon::fromTheme("edit-delete"), "Delete", [this, item]() {
            QString id = item->data(Qt::UserRole + 1).toString();
            m_store->remove(id);
        });
        menu.exec(m_list->mapToGlobal(pos));
    }

    void openBookmark(QListWidgetItem *item) {
        QString url = item->data(Qt::UserRole).toString();
        emit navigateTo(url);
    }

    void refreshList() {
        m_list->clear();
        for (const Bookmark &bm : m_store->all()) {
            auto *item = new QListWidgetItem(bm.title, m_list);
            item->setIcon(QIcon::fromTheme("bookmarks"));
            item->setData(Qt::UserRole, bm.url);
            item->setData(Qt::UserRole + 1, bm.id);
            item->setToolTip(bm.url + "\nCreated: " + bm.created.toString());
        }
    }

private:
    BookmarkStore *m_store;
    QListWidget *m_list;
};

class InfoPage : public QWidget {
    Q_OBJECT

public:
    explicit InfoPage(QWidget *parent = nullptr) : QWidget(parent) {
        auto *layout = new QVBoxLayout(this);

        auto *titleLabel = new QLabel("<h1>error.doc</h1>", this);
        titleLabel->setAlignment(Qt::AlignCenter);

        auto *infoLabel = new QLabel(
            "<p><b>Version:</b> 1.0</p>"
            "<h3>About</h3>"
            "<p>Documentation viewer for error.os with custom URL system.</p>"
            "<h3>Here are some  features, if you dont know.</h3>"
            "<ul>"
            "<li>Custom URL scheme (:/err/, :/man/, :/doc/)</li>"
            "<li>Threaded manpage loading with safety</li>"
            "<li>Split manpage view with info panel</li>"
            "<li>Text highlighting with color picker</li>"
            "<li>Find bar (Ctrl+F) for err/ and man/ pages</li>"
            "<li>Custom HTML tags: &lt;file&gt;, &lt;icon&gt;, &lt;page&gt;, &lt;bash&gt;</li>"
            "<li>Bookmark management with delete context menu</li>"
            "<li>Tab system with auto-hide tab bar</li>"
            "<li>Recent 3 URLs for forward navigation</li>"
            "</ul>",
            this
            );

        layout->addWidget(titleLabel);
        layout->addWidget(infoLabel);
        layout->addStretch();
    }
};


class DocEngine : public ContentEngine {
    Q_OBJECT

public:
    DocEngine(BookmarkStore *store, QWidget *parent = nullptr)
        : ContentEngine(parent), m_store(store)
    {
        m_stack = new QStackedWidget(this);

        m_settingsPage = new SettingsPage(this);
        m_bookmarksPage = new BookmarksPage(store, this);
        m_infoPage = new InfoPage(this);

        m_stack->addWidget(m_settingsPage);
        m_stack->addWidget(m_bookmarksPage);
        m_stack->addWidget(m_infoPage);

        auto *layout = new QVBoxLayout(this);
        layout->setContentsMargins(0, 0, 0, 0);
        layout->addWidget(m_stack);

        connect(m_settingsPage, &SettingsPage::settingsChanged,
                this, &DocEngine::settingsChanged);
        connect(m_bookmarksPage, &BookmarksPage::navigateTo,
                this, &DocEngine::navigationRequested);
    }

    void load(const DocumentUrl &url) override {
        if (!url.isDoc()) return;

        QString page = url.path();

        if (page == "settings") {
            m_stack->setCurrentWidget(m_settingsPage);
            emit titleChanged("Settings");
        } else if (page == "bookmarks") {
            m_stack->setCurrentWidget(m_bookmarksPage);
            emit titleChanged("Bookmarks");
        } else if (page == "info") {
            m_stack->setCurrentWidget(m_infoPage);
            emit titleChanged("Info");
        }
    }

    QString selectedText() const override { return ""; }
    QString allText() const override { return ""; }
    void find() override {}
    void highlightSelection(const QColor &, const QColor &) override {}
    void speakSelected() override {}

signals:
    void settingsChanged();

private:
    BookmarkStore *m_store;
    QStackedWidget *m_stack;
    SettingsPage *m_settingsPage;
    BookmarksPage *m_bookmarksPage;
    InfoPage *m_infoPage;
};


class TTSManager : public QObject {
    Q_OBJECT

public:
    static TTSManager& instance() {
        static TTSManager inst;
        return inst;
    }

    void speak(const QString &text) {
        if (!m_speech) {
            m_speech = new QTextToSpeech(this);
        }

        auto &s = Settings::instance();
        m_speech->setRate(s.ttsRate());
        m_speech->setPitch(s.ttsPitch());
        m_speech->setVolume(s.ttsVolume());

        m_speech->say(text);
    }

    void stop() {
        if (m_speech) {
            m_speech->stop();
        }
    }

private:
    TTSManager() : m_speech(nullptr) {}
    QTextToSpeech *m_speech;
};

class ContentArea : public QStackedWidget {
    Q_OBJECT

public:
    ContentArea(BookmarkStore *store, QWidget *parent = nullptr)
        : QStackedWidget(parent), m_store(store)
    {
        m_welcomeEngine = new WelcomeEngine(this);
        m_errEngine = new ErrorDocEngine(this);
        m_manEngine = new ManpageEngine(this);
        m_docEngine = new DocEngine(store, this);

        addWidget(m_welcomeEngine);
        addWidget(m_errEngine);
        addWidget(m_manEngine);
        addWidget(m_docEngine);

        m_currentUrl = new DocumentUrl(":/", this);

        connect(m_errEngine, &ErrorDocEngine::navigationRequested,
                this, &ContentArea::navigateRequested);
        connect(m_errEngine, &ErrorDocEngine::speakText,
                &TTSManager::instance(), &TTSManager::speak);
        connect(m_errEngine, &ErrorDocEngine::requestHighlight,
                this, &ContentArea::highlightRequested);

        connect(m_manEngine, &ManpageEngine::navigationRequested,
                this, &ContentArea::navigateRequested);
        connect(m_manEngine, &ManpageEngine::speakText,
                &TTSManager::instance(), &TTSManager::speak);
        connect(m_manEngine, &ManpageEngine::requestHighlight,
                this, &ContentArea::highlightRequested);
        connect(m_manEngine, &ManpageEngine::iconChanged,
                this, &ContentArea::iconChanged);

        connect(m_docEngine, &DocEngine::navigationRequested,
                this, &ContentArea::navigateRequested);
        connect(m_docEngine, &DocEngine::settingsChanged,
                this, &ContentArea::settingsChanged);
    }

    void navigate(const QString &url) {
        QString oldUrl = m_currentUrl->url();
        m_currentUrl->setUrl(url);

        ContentEngine *engine = nullptr;

        if (m_currentUrl->isRoot()) {
            engine = m_welcomeEngine;
        } else if (m_currentUrl->isErr()) {
            engine = m_errEngine;
        } else if (m_currentUrl->isMan()) {
            engine = m_manEngine;
        } else if (m_currentUrl->isDoc()) {
            engine = m_docEngine;
        }

        if (engine) {
            setCurrentWidget(engine);
            engine->load(*m_currentUrl);

            emit urlChanged(url);
            emit titleChanged(engine->windowTitle());
            emit engineChanged(engine);

            if (oldUrl != url && !oldUrl.isEmpty() && oldUrl != ":/") {
                emit backwardHistoryAdded(oldUrl, getTitleForUrl(oldUrl), getIconForUrl(oldUrl));
            }
        }
    }

    DocumentUrl* currentUrl() const { return m_currentUrl; }

    ContentEngine* currentEngine() const {
        return qobject_cast<ContentEngine*>(currentWidget());
    }

    void highlightCurrentSelection() {
        ContentEngine *engine = currentEngine();
        if (!engine) return;

        if (engine->selectedText().isEmpty()) {
            QMessageBox::information(this, "Highlight", "Please select text first");
            return;
        }

        HighlightDialog dlg(parentWidget());
        if (dlg.exec() == QDialog::Accepted) {
            engine->highlightSelection(dlg.fgColor(), dlg.bgColor());
        }
    }

    void findInCurrentPage() {
        ContentEngine *engine = currentEngine();
        if (engine && (m_currentUrl->isErr() || m_currentUrl->isMan())) {
            engine->find();
        }
    }

signals:
    void navigateRequested(const QString &url);
    void settingsChanged();
    void engineChanged(ContentEngine *engine);
    void urlChanged(const QString &url);
    void titleChanged(const QString &title);
    void highlightRequested();
    void iconChanged(const QString &iconName);
    void backwardHistoryAdded(const QString &url, const QString &title, const QString &icon);

private:
    QString getTitleForUrl(const QString &url) {
        if (url == ":/") return "Welcome";
        if (url.startsWith(":/err/")) {
            QString path = url.mid(6);
            if (path.contains('/')) return path.section('/', -1);
            return path;
        }
        if (url.startsWith(":/man/")) {
            QString path = url.mid(6);
            return path.section('/', -1);
        }
        if (url.startsWith(":/doc/")) {
            QString page = url.mid(6);
            if (page == "settings") return "Settings";
            if (page == "bookmarks") return "Bookmarks";
            if (page == "info") return "About";
            return page.isEmpty() ? "Documentation" : page;
        }
        return "Document";
    }

    QString getIconForUrl(const QString &url) {
        if (url == ":/") return "help-browser";
        if (url.startsWith(":/err/")) return "text-html";
        if (url.startsWith(":/man/")) return "utilities-terminal";
        if (url.startsWith(":/doc/")) {
            QString page = url.mid(6);
            if (page == "settings") return "preferences-system";
            if (page == "bookmarks") return "bookmarks";
            if (page == "info") return "help-about";
        }
        return "";
    }

    BookmarkStore *m_store;
    DocumentUrl *m_currentUrl;
    WelcomeEngine *m_welcomeEngine;
    ErrorDocEngine *m_errEngine;
    ManpageEngine *m_manEngine;
    DocEngine *m_docEngine;
};


class TabContent : public QWidget {
    Q_OBJECT

public:
    TabContent(BookmarkStore *store, QWidget *parent = nullptr)
        : QWidget(parent)
    {
        auto *layout = new QVBoxLayout(this);
        layout->setContentsMargins(0, 0, 0, 0);

        m_contentArea = new ContentArea(store, this);
        layout->addWidget(m_contentArea);
    }

    ContentArea* contentArea() { return m_contentArea; }

private:
    ContentArea *m_contentArea;
};
class NavigationTree : public QTreeWidget {
    Q_OBJECT

public:
    explicit NavigationTree(QWidget *parent = nullptr)
        : QTreeWidget(parent), m_manpagesInitialized(false)
    {
        setHeaderHidden(true);
        setContextMenuPolicy(Qt::CustomContextMenu);

        buildTree();

        connect(this, &QTreeWidget::itemActivated, this, &NavigationTree::onItemActivated);
        connect(this, &QTreeWidget::customContextMenuRequested, this, &NavigationTree::showContextMenu);

        m_searchEdit = new QLineEdit(this);
        m_searchEdit->setPlaceholderText("Search...");
        m_searchEdit->setClearButtonEnabled(true);
        setStyleSheet("QTreeWidget { padding-top: 30px; }");

        QTimer::singleShot(100, this, &NavigationTree::initializeManpages);
        connect(m_searchEdit, &QLineEdit::textChanged, this, &NavigationTree::filterTree);
    }

    void setSearchBar(QLineEdit *searchBar) {
        delete m_searchEdit;
        m_searchEdit = searchBar;
        m_searchEdit->setPlaceholderText("Search tree...");
        connect(m_searchEdit, &QLineEdit::textChanged, this, &NavigationTree::filterTree);
    }

    void setCurrentUrl(const QString &url) {
        if (m_currentUrl == url) return;
        m_currentUrl = url;
        findAndSelectItem(url);
    }

    void recursiveSearch(const QString &text) {
        filterTree(text);
    }

    void updatePageIcon(const QString &url, const QString &iconName) {
        QTreeWidgetItemIterator it(this);
        while (*it) {
            QTreeWidgetItem *item = *it;
            if (item->data(0, Qt::UserRole).toString() == url) {
                QIcon icon = QIcon::fromTheme(iconName);
                if (!icon.isNull()) {
                    item->setIcon(0, icon);
                }
                break;
            }
            ++it;
        }
    }

    void initializeManpages() {
        if (m_manpagesInitialized) return;
        m_manpagesInitialized = true;

        QTreeWidgetItem *manItem = nullptr;
        for (int i = 0; i < topLevelItemCount(); ++i) {
            if (topLevelItem(i)->data(0, Qt::UserRole).toString() == ":/man/") {
                manItem = topLevelItem(i);
                break;
            }
        }
        if (!manItem) return;

        auto *loadingItem = new QTreeWidgetItem(manItem);
        loadingItem->setText(0, "Loading manpages...");
        manItem->setExpanded(true);

        auto *worker = new ManpageLoaderWorker(this);
        connect(worker, &ManpageLoaderWorker::manpagesLoaded, this,
                [this, manItem, loadingItem, worker](const QString &output) {
                    if (!output.isEmpty()) {
                        parseManpages(output, manItem);
                    }
                    delete loadingItem;
                    worker->deleteLater();
                });

        worker->loadManpages();
    }

signals:
    void navigationRequested(const QString &url);
    void navigationRequestedNewTab(const QString &url);
    void bookmarkRequested(const QString &url, const QString &title);

private slots:
    void onItemActivated(QTreeWidgetItem *item) {
        if (!item) return;
        QString url = item->data(0, Qt::UserRole).toString();
        if (!url.isEmpty() && url != ":/" && url != ":/err/" && url != ":/man/" && url != ":/doc/") {
            emit navigationRequested(url);
        }
    }

    void showContextMenu(const QPoint &pos) {
        QTreeWidgetItem *item = itemAt(pos);
        if (!item) return;
        QString url = item->data(0, Qt::UserRole).toString();
        if (url.isEmpty()) return;
        if (url.startsWith(":/err/") || url.startsWith(":/man/")) {
            QMenu menu(this);
            menu.addAction(QIcon::fromTheme("bookmark-new"), "Bookmark", [this, item, url]() {
                emit bookmarkRequested(url, item->text(0));
            });
            menu.addAction(QIcon::fromTheme("tab-new"), "Open in New Tab", [this, url]() {
                emit navigationRequestedNewTab(url);
            });
            menu.exec(mapToGlobal(pos));
        }
    }

    void filterTree(const QString &text) {
        if (text.isEmpty()) {
            QTreeWidgetItemIterator it(this);
            while (*it) {
                (*it)->setHidden(false);
                ++it;
            }
            return;
        }
        QTreeWidgetItemIterator it(this);
        while (*it) {
            QTreeWidgetItem *item = *it;
            bool matches = item->text(0).contains(text, Qt::CaseInsensitive);
            item->setHidden(!matches);
            if (matches) {
                QTreeWidgetItem *parent = item->parent();
                while (parent) {
                    parent->setHidden(false);
                    parent->setExpanded(true);
                    parent = parent->parent();
                }
            }
            ++it;
        }
    }

private:
    struct SectionInfo {
        QString name;
        QString iconName;
    };

    SectionInfo getSectionInfo(const QString &section) {
        static QHash<QString, SectionInfo> sectionMap = {
            {"1", {"User Commands", "utilities-terminal"}},
            {"2", {"System Calls", "system-run"}},
            {"3", {"Library Functions", "applications-development"}},
            {"4", {"Devices", "drive-harddisk"}},
            {"5", {"File Formats", "text-x-generic"}},
            {"6", {"Games", "applications-games"}},
            {"7", {"Miscellaneous", "applications-other"}},
            {"8", {"System Administration", "system-users"}},
            {"9", {"Kernel", "applications-system"}}
        };

        if (sectionMap.contains(section)) {
            return sectionMap[section];
        }
        return {"General", "folder"};
    }

    void buildTree() {
        auto *errItem = new QTreeWidgetItem(this);
        errItem->setText(0, "err/");
        errItem->setIcon(0, QIcon::fromTheme("internet-web-browser"));
        errItem->setData(0, Qt::UserRole, ":/err/");
        scanQrcDirectoryRecursive(":/docs", errItem);
        scanQrcDirectoryRecursive(":/err", errItem);

        auto *manItem = new QTreeWidgetItem(this);
        manItem->setText(0, "man/");
        manItem->setIcon(0, QIcon::fromTheme("utilities-terminal"));
        manItem->setData(0, Qt::UserRole, ":/man/");

        auto *docItem = new QTreeWidgetItem(this);
        docItem->setText(0, "doc/");
        docItem->setIcon(0, QIcon::fromTheme("error.doc", QIcon::fromTheme("help-browser")));
        docItem->setData(0, Qt::UserRole, ":/doc/");

        auto *infoItem = new QTreeWidgetItem(docItem);
        infoItem->setText(0, "info");
        infoItem->setIcon(0, QIcon::fromTheme("help-about"));
        infoItem->setData(0, Qt::UserRole, ":/doc/info");

        auto *settingsItem = new QTreeWidgetItem(docItem);
        settingsItem->setText(0, "settings");
        settingsItem->setIcon(0, QIcon::fromTheme("preferences-system"));
        settingsItem->setData(0, Qt::UserRole, ":/doc/settings");

        auto *bookmarksItem = new QTreeWidgetItem(docItem);
        bookmarksItem->setText(0, "bookmarks");
        bookmarksItem->setIcon(0, QIcon::fromTheme("bookmarks"));
        bookmarksItem->setData(0, Qt::UserRole, ":/doc/bookmarks");
    }

    void scanQrcDirectoryRecursive(const QString &path, QTreeWidgetItem *parent) {
        QDirIterator it(path, QDirIterator::Subdirectories);
        QMap<QString, QTreeWidgetItem*> dirs;

        while (it.hasNext()) {
            QString file = it.next();
            QFileInfo info(file);

            if (info.isDir()) continue;
            if (!info.fileName().endsWith(".html")) continue;

            QString relativePath = file.mid(QString(":/").length());
            QString dirPath = QFileInfo(file).path().mid(QString(":/").length());

            QTreeWidgetItem *parentItem = parent;

            if (!dirPath.isEmpty() && dirPath != "." && dirPath != "/") {
                QStringList dirs_parts = dirPath.split('/', Qt::SkipEmptyParts);
                QString currentPath = "";

                for (const QString &dir : std::as_const(dirs_parts)) {
                    currentPath += (currentPath.isEmpty() ? "" : "/") + dir;

                    if (!dirs.contains(currentPath)) {
                        auto *dirItem = new QTreeWidgetItem(parentItem);
                        dirItem->setText(0, dir);
                        dirItem->setIcon(0, QIcon::fromTheme("folder"));
                        dirItem->setData(0, Qt::UserRole, QString());
                        dirs[currentPath] = dirItem;
                        parentItem = dirItem;
                    } else {
                        parentItem = dirs[currentPath];
                    }
                }
            }

            auto *item = new QTreeWidgetItem(parentItem);
            QString displayName = info.baseName();
            item->setText(0, displayName);
            item->setIcon(0, QIcon::fromTheme("text-html"));

            QString urlPath = relativePath;
            if (urlPath.endsWith(".html")) {
                urlPath.chop(5);
            }
            if (urlPath.startsWith("/")) {
                urlPath = urlPath.mid(1);
            }
            item->setData(0, Qt::UserRole, ":/err/" + urlPath);
        }
    }

    void parseManpages(const QString &output, QTreeWidgetItem *parent) {
        QStringList lines = output.split('\n', Qt::SkipEmptyParts);
        QHash<QString, QTreeWidgetItem*> sections;

        for (const QString &line : std::as_const(lines)) {
            QRegularExpressionMatch match = MANPAGE_REGEX.match(line);
            if (!match.hasMatch()) continue;

            QString name = match.captured(1);
            QString section = match.captured(2);

            SectionInfo info = getSectionInfo(section);

            QTreeWidgetItem *secItem = sections.value(info.name);
            if (!secItem) {
                secItem = new QTreeWidgetItem(parent);
                secItem->setText(0, info.name);
                secItem->setIcon(0, QIcon::fromTheme(info.iconName));
                secItem->setData(0, Qt::UserRole, QString());
                sections.insert(info.name, secItem);
            }

            auto *item = new QTreeWidgetItem(secItem);
            item->setText(0, name);
            item->setData(0, Qt::UserRole, QString(":/man/%1/%2").arg(section).arg(name));

            QIcon icon = QIcon::fromTheme(name);
            if (icon.isNull()) icon = QIcon::fromTheme("text-x-generic");
            item->setIcon(0, icon);
        }
    }

    void findAndSelectItem(const QString &url) {
        clearSelection();
        QTreeWidgetItemIterator it(this);
        while (*it) {
            QTreeWidgetItem *item = *it;
            if (item->data(0, Qt::UserRole).toString() == url) {
                setCurrentItem(item);
                QTreeWidgetItem *parent = item->parent();
                while (parent) {
                    parent->setExpanded(true);
                    parent = parent->parent();
                }
                break;
            }
            ++it;
        }
    }

    bool m_manpagesInitialized;
    QString m_currentUrl;
    QLineEdit *m_searchEdit;
};

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow() {
        setWindowTitle("error.doc");
        setWindowIcon(QIcon::fromTheme("error.doc", QIcon::fromTheme("help-browser")));
        resize(1200, 800);
        
        QDialog *splash = new QDialog(nullptr, Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
        splash->setAttribute(Qt::WA_TranslucentBackground);
        splash->setFixedSize(200, 150);
        
        QVBoxLayout *splashLayout = new QVBoxLayout(splash);
        splashLayout->setAlignment(Qt::AlignCenter);
        
        QLabel *iconLabel = new QLabel(splash);
        iconLabel->setPixmap(QIcon::fromTheme("error.doc", QIcon::fromTheme("help-browser")).pixmap(64, 64));
        iconLabel->setAlignment(Qt::AlignCenter);
        
        QLabel *textLabel = new QLabel("Loading...", splash);
        textLabel->setAlignment(Qt::AlignCenter);
        
        splashLayout->addWidget(iconLabel);
        splashLayout->addWidget(textLabel);
        
        splash->show();
        QApplication::processEvents();
        
        m_bookmarkStore = new BookmarkStore(this);
        m_ttsManager = &TTSManager::instance();
        
        m_backwardUrls.clear();
        m_backwardTitles.clear();
        m_backwardIcons.clear();
        
        auto *centralWidget = new QWidget(this);
        auto *mainLayout = new QVBoxLayout(centralWidget);
        mainLayout->setContentsMargins(0, 0, 0, 0);
        mainLayout->setSpacing(0);
        
        createToolbar();
        mainLayout->addWidget(m_toolbar);
        
        setupUrlCompleter();
        
        auto *splitter = new QSplitter(Qt::Horizontal, this);
        
        auto *treeContainer = new QWidget(this);
        auto *treeLayout = new QVBoxLayout(treeContainer);
        treeLayout->setContentsMargins(0, 0, 0, 0);
        
        m_treeSearchEdit = new QLineEdit(this);
        m_treeSearchEdit->setPlaceholderText("Search tree...");
        m_treeSearchEdit->setClearButtonEnabled(true);
        
        m_navTree = new NavigationTree(this);
        m_navTree->setSearchBar(m_treeSearchEdit);
        
        treeLayout->addWidget(m_treeSearchEdit);
        treeLayout->addWidget(m_navTree);
        
        m_tabWidget = new QTabWidget(this);
        m_tabWidget->setTabsClosable(true);
        m_tabWidget->setMovable(true);
        m_tabWidget->tabBar()->setVisible(false);
        
        addNewTab(":/");
        
        connect(m_tabWidget, &QTabWidget::tabCloseRequested, this, &MainWindow::closeTab);
        connect(m_tabWidget, &QTabWidget::currentChanged, this, &MainWindow::onTabChanged);
        connect(m_treeSearchEdit, &QLineEdit::textChanged, m_navTree, &NavigationTree::recursiveSearch);
        
        splitter->addWidget(treeContainer);
        splitter->addWidget(m_tabWidget);
        splitter->setStretchFactor(0, 1);
        splitter->setStretchFactor(1, 4);
        
        mainLayout->addWidget(splitter);
        setCentralWidget(centralWidget);
        
        updateTabBarVisibility();
        setupShortcuts();
        
        connect(m_navTree, &NavigationTree::navigationRequested,
                this, &MainWindow::navigateCurrentTab);
        connect(m_navTree, &NavigationTree::bookmarkRequested,
                this, &MainWindow::addBookmark);
        
        connect(m_bookmarkStore, &BookmarkStore::changed, this, &MainWindow::onBookmarksChanged);
        
        connect(&Settings::instance(), &Settings::settingsChanged,
                this, &MainWindow::reloadShortcuts);
    
        QTimer::singleShot(500, [splash]() {
            splash->accept();
            splash->deleteLater();
        });
        
        m_navTree->initializeManpages();
        
        updateBackwardButton();
    }
private slots:
    void navigateCurrentTab(const QString &url) {
        if (TabContent *tab = currentTab()) {
            QString currentUrl = tab->contentArea()->currentUrl()->url();
            QString currentTitle = extractTitleFromUrl(currentUrl);
            QString currentIcon = getIconForUrl(currentUrl);

            if (!currentUrl.isEmpty() && currentUrl != ":/") {
                addToBackwardHistory(currentUrl, currentTitle, currentIcon);
            }

            tab->contentArea()->navigate(url);
            updateUrlBar(url);
            m_navTree->setCurrentUrl(url);
            updateBackwardButton();
        }
    }

    void addNewTab(const QString &url = ":/") {
        auto *tab = new TabContent(m_bookmarkStore, this);
        int index = m_tabWidget->addTab(tab, "New Tab");
        m_tabWidget->setCurrentIndex(index);
        m_tabWidget->setTabIcon(index, QIcon::fromTheme("error.doc", QIcon::fromTheme("help-browser")));

        connect(tab->contentArea(), &ContentArea::urlChanged, this, [this, index](const QString &url) {
            if (m_tabWidget->currentIndex() == index) {
                updateUrlBar(url);
                m_navTree->setCurrentUrl(url);
                updateBackwardButton();
            }
            updateTabTitle(index, url);
        });

        connect(tab->contentArea(), &ContentArea::titleChanged, this, [this, index](const QString &title) {
            if (m_tabWidget->currentIndex() == index) {
                setWindowTitle(QString("error.doc  %1").arg(title));
            }
            QString tabTitle = title.length() > 20 ? title.left(17) + "..." : title;
            if (tabTitle.isEmpty()) tabTitle = "New Tab";
            m_tabWidget->setTabText(index, tabTitle);
            m_tabWidget->setTabToolTip(index, title);
        });

        connect(tab->contentArea(), &ContentArea::iconChanged, this, [this, index](const QString &iconName) {
            if (m_tabWidget->currentIndex() == index) {
                QIcon icon = QIcon::fromTheme(iconName);
                if (!icon.isNull()) {
                    m_tabWidget->setTabIcon(index, icon);
                }
            }
        });

        connect(tab->contentArea(), &ContentArea::navigateRequested, this, &MainWindow::navigateCurrentTab);
        connect(tab->contentArea(), &ContentArea::highlightRequested, this, &MainWindow::highlightText);

        tab->contentArea()->navigate(url);
        updateTabBarVisibility();
    }

    void closeTab(int index) {
        if (m_tabWidget->count() <= 1) {
            if (TabContent *tab = currentTab()) {
                tab->contentArea()->navigate(":/");
                m_backwardUrls.clear();
                m_backwardTitles.clear();
                m_backwardIcons.clear();
                updateBackwardButton();
            }
        } else {
            QWidget *widget = m_tabWidget->widget(index);
            m_tabWidget->removeTab(index);
            widget->deleteLater();
        }
        updateTabBarVisibility();
    }

    void onTabChanged(int index) {
        if (index >= 0) {
            if (TabContent *tab = currentTab()) {
                QString url = tab->contentArea()->currentUrl()->url();
                updateUrlBar(url);
                m_navTree->setCurrentUrl(url);
                updateBackwardButton();

                ContentEngine *engine = tab->contentArea()->currentEngine();
                if (engine) {
                    setWindowTitle(QString("error.doc  %1").arg(engine->windowTitle()));
                }
            }
        }
        updateTabBarVisibility();
    }

    void onUrlEdited() {
        if (!m_urlBar) return;
        QString url = m_urlBar->text();
        if (!url.isEmpty()) {
            navigateCurrentTab(url);
        }
    }

    void navigateBackward() {
        if (!m_backwardUrls.isEmpty()) {
            QString url = m_backwardUrls.takeFirst();
            QString title = m_backwardTitles.takeFirst();
            QString icon = m_backwardIcons.takeFirst();

            if (TabContent *tab = currentTab()) {
                tab->contentArea()->navigate(url);
                updateUrlBar(url);
                m_navTree->setCurrentUrl(url);
                updateBackwardButton();
            }
        }
    }

    void addToBackwardHistory(const QString &url, const QString &title, const QString &icon = "") {
        int index = m_backwardUrls.indexOf(url);
        if (index != -1) {
            m_backwardUrls.removeAt(index);
            m_backwardTitles.removeAt(index);
            if (index < m_backwardIcons.size()) m_backwardIcons.removeAt(index);
        }

        m_backwardUrls.prepend(url);
        m_backwardTitles.prepend(title);
        m_backwardIcons.prepend(icon);

        while (m_backwardUrls.size() > 3) {
            m_backwardUrls.removeLast();
            m_backwardTitles.removeLast();
            if (m_backwardIcons.size() > 3) m_backwardIcons.removeLast();
        }
    }

    void updateBackwardButton() {
        if (!m_backwardBtn) return;

        m_backwardBtn->setEnabled(!m_backwardUrls.isEmpty());

        if (!m_backwardUrls.isEmpty()) {
            QString tooltip = "Back to:<br>";
            for (int i = 0; i < m_backwardUrls.size() && i < 3; i++) {
                tooltip += QString("• %1<br>").arg(m_backwardTitles.value(i, m_backwardUrls[i]));
            }
            m_backwardBtn->setToolTip(tooltip);
        } else {
            m_backwardBtn->setToolTip("Back");
        }
    }

    void refresh() {
        if (TabContent *tab = currentTab()) {
            navigateCurrentTab(tab->contentArea()->currentUrl()->url());
        }
    }

    void highlightText() {
        if (TabContent *tab = currentTab()) {
            tab->contentArea()->highlightCurrentSelection();
        }
    }

    void speakText() {
        if (TabContent *tab = currentTab()) {
            ContentEngine *engine = tab->contentArea()->currentEngine();
            if (engine) {
                engine->speakSelected();
            }
        }
    }

    void findInPage() {
        if (TabContent *tab = currentTab()) {
            tab->contentArea()->findInCurrentPage();
        }
    }

    void stopSpeech() {
        if (m_ttsManager) {
            m_ttsManager->stop();
        }
    }

    void showBookmarks() {
        if (TabContent *tab = currentTab()) {
            BookmarkDialog dlg(m_bookmarkStore,
                               tab->contentArea()->currentUrl()->url(),
                               windowTitle(), this);
            connect(&dlg, &BookmarkDialog::navigateTo, this, &MainWindow::navigateCurrentTab);
            dlg.exec();
        }
    }

    void addBookmark(const QString &url, const QString &title) {
        Bookmark bm;
        bm.id = QDateTime::currentDateTime().toString(Qt::ISODate) + "_" +
                QString::number(QRandomGenerator::global()->generate());
        bm.title = title;
        bm.url = url;
        bm.created = QDateTime::currentDateTime();
        m_bookmarkStore->add(bm);
        QMessageBox::information(this, "Bookmark", "Bookmark added");
    }

    void toggleOptionsMenu() {
        if (TabContent *tab = currentTab()) {
            DocumentUrl *url = tab->contentArea()->currentUrl();
            if (!url->isErr() && !url->isMan()) {
                QMessageBox::information(this, "Options",
                                         "Options menu only available for :/err/ and :/man/ pages");
                return;
            }
            QMessageBox::information(this, "Options", "Options menu not implemented yet");
        }
    }

    void reloadShortcuts() {
        for (QShortcut *shortcut : m_shortcuts) {
            delete shortcut;
        }
        m_shortcuts.clear();

        setupShortcuts();
    }

    void setupUrlCompleter() {
        if (!m_urlBar) {
            qWarning() << "Cannot setup completer: URL bar is null";
            return;
        }

        m_completer = new QCompleter(this);
        m_urlBar->setCompleter(m_completer);

        QStringListModel *model = new QStringListModel(this);
        m_completer->setModel(model);
        m_completer->setCaseSensitivity(Qt::CaseInsensitive);
        m_completer->setFilterMode(Qt::MatchContains);

        updateCompleterModel();
    }

    void updateCompleterModel() {
        if (!m_completer) return;

        QStringList displayList;
        for (int i = 0; i < m_backwardUrls.size(); ++i) {
            displayList << QString("%1 - %2").arg(m_backwardTitles.value(i, "Unknown"), m_backwardUrls[i]);
        }

        QAbstractItemModel *currentModel = m_completer->model();
        if (!currentModel) {
            QStringListModel *newModel = new QStringListModel(this);
            m_completer->setModel(newModel);
            currentModel = newModel;
        }

        if (auto *model = qobject_cast<QStringListModel*>(currentModel)) {
            model->setStringList(displayList);
        }

        if (m_urlBar) {
            m_completer->setCompletionPrefix(m_urlBar->text());
        }
    }

    void setupShortcuts() {
        auto &settings = Settings::instance();

        QString optionsKey = settings.shortcutOptions();
        QShortcut *optionsShortcut = new QShortcut(QKeySequence(optionsKey), this);
        connect(optionsShortcut, &QShortcut::activated, this, &MainWindow::toggleOptionsMenu);
        m_shortcuts.append(optionsShortcut);

        QString newTabKey = settings.shortcutNewTab();
        QShortcut *newTabShortcut = new QShortcut(QKeySequence(newTabKey), this);
        connect(newTabShortcut, &QShortcut::activated, [this]() { addNewTab(); });
        m_shortcuts.append(newTabShortcut);

        QString closeTabKey = settings.shortcutCloseTab();
        QShortcut *closeTabShortcut = new QShortcut(QKeySequence(closeTabKey), this);
        connect(closeTabShortcut, &QShortcut::activated, [this]() {
            if (m_tabWidget->count() > 0) {
                closeTab(m_tabWidget->currentIndex());
            }
        });
        m_shortcuts.append(closeTabShortcut);

        QString findKey = settings.shortcutFind();
        QShortcut *findShortcut = new QShortcut(QKeySequence(findKey), this);
        connect(findShortcut, &QShortcut::activated, this, &MainWindow::findInPage);
        m_shortcuts.append(findShortcut);

        QString speakKey = settings.shortcutSpeak();
        QShortcut *speakShortcut = new QShortcut(QKeySequence(speakKey), this);
        connect(speakShortcut, &QShortcut::activated, this, &MainWindow::speakText);
        m_shortcuts.append(speakShortcut);

        QString stopKey = settings.shortcutStopSpeech();
        QShortcut *stopShortcut = new QShortcut(QKeySequence(stopKey), this);
        connect(stopShortcut, &QShortcut::activated, this, &MainWindow::stopSpeech);
        m_shortcuts.append(stopShortcut);

        QString bookmarksKey = settings.shortcutBookmarks();
        QShortcut *bookmarksShortcut = new QShortcut(QKeySequence(bookmarksKey), this);
        connect(bookmarksShortcut, &QShortcut::activated, this, &MainWindow::showBookmarks);
        m_shortcuts.append(bookmarksShortcut);

        QString refreshKey = settings.shortcutRefresh();
        QShortcut *refreshShortcut = new QShortcut(QKeySequence(refreshKey), this);
        connect(refreshShortcut, &QShortcut::activated, this, &MainWindow::refresh);
        m_shortcuts.append(refreshShortcut);
    }

    void updateTabBarVisibility() {
        if (!m_tabWidget) return;
        bool showAlways = Settings::instance().showTabAlways();
        m_tabWidget->tabBar()->setVisible(showAlways || m_tabWidget->count() > 1);
    }

    void updateTabTitle(int index, const QString &url) {
        if (!m_tabWidget) return;

        QString title = extractTitleFromUrl(url);
        if (title.isEmpty() || title == "Documentation") {
            title = "New Tab";
        }
        m_tabWidget->setTabText(index, title);

        QString iconName = getIconForUrl(url);
        if (!iconName.isEmpty()) {
            QIcon icon = QIcon::fromTheme(iconName);
            if (!icon.isNull()) {
                m_tabWidget->setTabIcon(index, icon);
            }
        }
    }

    void onBookmarksChanged() {
        if (!m_tabWidget) return;

        for (int i = 0; i < m_tabWidget->count(); ++i) {
            if (auto *tab = qobject_cast<TabContent*>(m_tabWidget->widget(i))) {
                if (tab->contentArea()->currentUrl()->isDoc() &&
                    tab->contentArea()->currentUrl()->path() == "bookmarks") {
                    tab->contentArea()->navigate(tab->contentArea()->currentUrl()->url());
                }
            }
        }
    }

private:
    void createToolbar() {
        m_toolbar = new QToolBar(this);
        m_toolbar->setMovable(false);

        m_backwardBtn = new QToolButton(this);
        m_backwardBtn->setIcon(QIcon::fromTheme("go-previous"));
        m_backwardBtn->setToolTip("Back");
        m_backwardBtn->setEnabled(false);
        connect(m_backwardBtn, &QToolButton::clicked, this, &MainWindow::navigateBackward);

        m_urlBar = new QLineEdit(this);
        m_urlBar->setPlaceholderText("Enter URL (:/err/, :/man/, :/doc/)");
        connect(m_urlBar, &QLineEdit::returnPressed, this, &MainWindow::onUrlEdited);

        auto *refreshBtn = new QToolButton(this);
        refreshBtn->setIcon(QIcon::fromTheme("view-refresh"));
        refreshBtn->setToolTip("Refresh");
        connect(refreshBtn, &QToolButton::clicked, this, &MainWindow::refresh);

        auto *newTabBtn = new QToolButton(this);
        newTabBtn->setIcon(QIcon::fromTheme("tab-new"));
        newTabBtn->setToolTip("New Tab");
        connect(newTabBtn, &QToolButton::clicked, [this]() { addNewTab(); });

        m_highlightBtn = new QToolButton(this);
        m_highlightBtn->setIcon(QIcon::fromTheme("format-text-color"));
        m_highlightBtn->setToolTip("Highlight Text");
        connect(m_highlightBtn, &QToolButton::clicked, this, &MainWindow::highlightText);

        auto *speakBtn = new QToolButton(this);
        speakBtn->setIcon(QIcon::fromTheme("media-playback-start"));
        speakBtn->setToolTip("Speak Selected Text");
        connect(speakBtn, &QToolButton::clicked, this, &MainWindow::speakText);

        auto *findBtn = new QToolButton(this);
        findBtn->setIcon(QIcon::fromTheme("edit-find"));
        findBtn->setToolTip("Find");
        connect(findBtn, &QToolButton::clicked, this, &MainWindow::findInPage);

        auto *stopBtn = new QToolButton(this);
        stopBtn->setIcon(QIcon::fromTheme("media-playback-stop"));
        stopBtn->setToolTip("Stop Speaking");
        connect(stopBtn, &QToolButton::clicked, this, &MainWindow::stopSpeech);

        auto *bookmarkBtn = new QToolButton(this);
        bookmarkBtn->setIcon(QIcon::fromTheme("bookmark-new"));
        bookmarkBtn->setToolTip("Bookmarks");
        connect(bookmarkBtn, &QToolButton::clicked, this, &MainWindow::showBookmarks);

        m_toolbar->addWidget(m_backwardBtn);
        m_toolbar->addWidget(m_urlBar);
        m_toolbar->addWidget(refreshBtn);
        m_toolbar->addWidget(newTabBtn);
        m_toolbar->addWidget(m_highlightBtn);
        m_toolbar->addWidget(speakBtn);
        m_toolbar->addWidget(findBtn);
        m_toolbar->addWidget(stopBtn);
        m_toolbar->addWidget(bookmarkBtn);
    }

    void updateUrlBar(const QString &url) {
        if (m_urlBar) {
            m_urlBar->setText(url);
            updateCompleterModel();
        }
    }

    QString extractTitleFromUrl(const QString &url) {
        if (url == ":/") return "Welcome";
        if (url.startsWith(":/err/")) {
            QString path = url.mid(6);
            if (path.contains('/')) return path.section('/', -1);
            return path;
        }
        if (url.startsWith(":/man/")) {
            QString path = url.mid(6);
            return path.section('/', -1);
        }
        if (url.startsWith(":/doc/")) {
            QString page = url.mid(6);
            return page.isEmpty() ? "Documentation" : page;
        }
        return "";
    }

    QString getIconForUrl(const QString &url) {
        if (url == ":/") return "help-browser";
        if (url.startsWith(":/err/")) return "text-html";
        if (url.startsWith(":/man/")) return "utilities-terminal";
        if (url.startsWith(":/doc/")) {
            QString page = url.mid(6);
            if (page == "settings") return "preferences-system";
            if (page == "bookmarks") return "bookmarks";
            if (page == "info") return "help-about";
        }
        return "";
    }

    TabContent* currentTab() {
        return qobject_cast<TabContent*>(m_tabWidget->currentWidget());
    }

    BookmarkStore *m_bookmarkStore = nullptr;
    NavigationTree *m_navTree = nullptr;
    QTabWidget *m_tabWidget = nullptr;
    QToolBar *m_toolbar = nullptr;
    QLineEdit *m_urlBar = nullptr;
    QLineEdit *m_treeSearchEdit = nullptr;
    QToolButton *m_highlightBtn = nullptr;
    QToolButton *m_backwardBtn = nullptr;
    TTSManager *m_ttsManager = nullptr;
    QCompleter *m_completer = nullptr;
    QList<QShortcut*> m_shortcuts;

    QStringList m_backwardUrls;
    QStringList m_backwardTitles;
    QStringList m_backwardIcons;
};

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    QApplication::setApplicationName("error_doc");
    QApplication::setOrganizationName("error.os");

    MainWindow window;
    window.show();

    return app.exec();
}

#include "main.moc"
