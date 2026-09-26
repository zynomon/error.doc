#include <QApplication>
#include <QButtonGroup>
#include <QMainWindow>
#include <QSplitter>
#include <QTreeWidget>
#include <QStackedWidget>
#include <QTextBrowser>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QGridLayout>
#include <QFileDialog>
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
#include <QCompleter>
#include <QStringListModel>
#include <QLineEdit>
#include <QRegularExpression>
#include <QFuture>
#include <QFutureWatcher>
#include <QProgressBar>
#include <QMouseEvent>
#include <QStyle>
#include <QLineEdit>
#include <QPushButton>
#include <tan>

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

    QColor paletteColor(int digit) const {
        static const QColor def[10] = {
            QColor("#000000"), QColor("#ffffff"), QColor("#ffff00"), QColor("#0000ff"),
            QColor("#ff00ff"), QColor("#00ff00"), QColor("#ff0000"), QColor("#333333"),
            QColor("#cccccc"), QColor("#008080")
        };
        return m_settings.value(QString("palette/%1").arg(digit),
                                def[qBound(0, digit, 9)].name()).value<QColor>();
    }
    void setPaletteColor(int digit, const QColor &c) {
        m_settings.setValue(QString("palette/%1").arg(digit), c.name());
        emit settingsChanged();
    }

    void reset() {
        m_settings.clear();
        emit settingsChanged();
    }

signals:
    void settingsChanged();

private:
    Settings() : m_settings("error.os", "doc") {}
    QSettings m_settings;
};
class ManpageLoaderWorker : public QObject {
    Q_OBJECT

public slots:
    void loadManpages() {
        QProcess process;
        process.start("man", QStringList() << "-k" << ".");
        QString output;
        if (process.waitForFinished(-1) && process.exitCode() == 0) {
            output = QString::fromUtf8(process.readAllStandardOutput());
        }
        emit manpagesLoaded(output);
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
        if (icon.isNull()) {
            return QString("<span style='display: inline-block; width: 16px; height: 16px; background-color: #666; border-radius: 3px; text-align: center; color: white; font-size: 10px; line-height: 16px;'>?</span>");
        }

        QPixmap pixmap = icon.pixmap(16, 16);
        if (pixmap.isNull()) {
            return QString("<span style='display: inline-block; width: 16px; height: 16px; background-color: #666; border-radius: 3px;'> </span>");
        }

        QByteArray bytes;
        QBuffer buffer(&bytes);
        buffer.open(QIODevice::WriteOnly);
        if (!pixmap.save(&buffer, "PNG")) {
            return QString("<span>[%1]</span>").arg(iconName);
        }

        return QString("<img src='data:image/png;base64,%1' alt='%2' style='vertical-align: middle; width: 16px; height: 16px;'>")
            .arg(QString::fromLatin1(bytes.toBase64()))
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
struct Highlight {
    QString url;
    QString color;
    QString argStart;
    QString argEnd;
    int     offset = -1;
};
class HighlightStore : public QObject {
    Q_OBJECT
public:
    explicit HighlightStore(QObject *parent = nullptr) : QObject(parent) { load(); }

    void add(const Highlight &h) {
        m_items.append(h);
        save();
        emit changed(h.url);
    }

    QList<Highlight> forUrl(const QString &url) const {
        QList<Highlight> out;
        for (const Highlight &h : m_items)
            if (h.url == url) out.append(h);
        return out;
    }

signals:
    void changed(const QString &url);

private:
    QList<Highlight> m_items;

    static QString escapePipes(const QString &s) {
        QString r = s;
        r.replace('|', QChar(0x2502));
        return r;
    }
    static QString unescapePipes(const QString &s) {
        QString r = s;
        r.replace(QChar(0x2502), '|');
        return r;
    }

    QString filePath() const {
        return QStandardPaths::writableLocation(QStandardPaths::AppDataLocation)
        + "/highlights.txt";
    }

    void load() {
        QFile f(filePath());
        if (!f.open(QIODevice::ReadOnly | QIODevice::Text))
            return;
        const QString text = QString::fromUtf8(f.readAll());
        f.close();

        static const QRegularExpression rec(
            QStringLiteral(R"(:\[1\|([^|]*)\|1\]\[2\|(\d\d)\|2\]\[3\|([^|]*)\|3\]\[4\|([^|]*)\|4\](?:\[5\|(-?\d+)\|5\])?)"));

        auto it = rec.globalMatch(text);
        while (it.hasNext()) {
            const QRegularExpressionMatch m = it.next();
            Highlight h;
            h.url      = unescapePipes(m.captured(1));
            h.color    = m.captured(2);
            h.argStart = unescapePipes(m.captured(3));
            h.argEnd   = unescapePipes(m.captured(4));
            h.offset   = m.captured(5).isEmpty() ? -1 : m.captured(5).toInt();
            if (!h.url.isEmpty() && !h.argStart.isEmpty() && !h.argEnd.isEmpty())
                m_items.append(h);
        }
    }

    void save() {
        QString out;
        for (const Highlight &h : m_items) {
            out += QStringLiteral(":[1|%1|1][2|%2|2][3|%3|3][4|%4|4][5|%5|5]\n")
            .arg(escapePipes(h.url), h.color,
                 escapePipes(h.argStart), escapePipes(h.argEnd),
                 QString::number(h.offset));
        }
        QDir().mkpath(QFileInfo(filePath()).absolutePath());
        QFile f(filePath());
        if (!f.open(QIODevice::WriteOnly | QIODevice::Truncate | QIODevice::Text))
            return;
        f.write(out.toUtf8());
    }
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
        setMinimumWidth(420);

        auto *root = new QVBoxLayout(this);

        auto buildRow = [this, root](const QString &label, bool isBg,
                                     QVector<QToolButton*> &out) {
            auto *group = new QButtonGroup(this);   // one group per row
            group->setExclusive(true);

            auto *row = new QHBoxLayout();
            row->addWidget(new QLabel(label, this));
            for (int i = 0; i < 10; ++i) {
                auto *b = new QToolButton(this);
                b->setCheckable(true);
                b->setFixedSize(28, 28);
                b->setToolTip(QString::number(i));
                group->addButton(b);
                connect(b, &QToolButton::clicked, this, [this, i, isBg]() {
                    if (isBg) m_bg = i; else m_fg = i;
                    updatePreview();
                });
                row->addWidget(b);
                out.append(b);
            }
            row->addStretch();
            root->addLayout(row);
        };

        buildRow(QStringLiteral("Background:"), true,  m_bgButtons);
        buildRow(QStringLiteral("Foreground:"), false, m_fgButtons);

        m_preview = new QLabel(QStringLiteral("The quick brown fox jumps over the lazy dog."), this);
        m_preview->setMargin(8);
        m_preview->setAlignment(Qt::AlignCenter);

        auto *buttons = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);
        root->addWidget(m_preview);
        root->addWidget(buttons);

        connect(buttons, &QDialogButtonBox::accepted, this, &QDialog::accept);
        connect(buttons, &QDialogButtonBox::rejected, this, &QDialog::reject);

        m_bgButtons[m_bg]->setChecked(true);
        m_fgButtons[m_fg]->setChecked(true);
        updatePreview();
    }

    QColor fgColor() const { return slot(m_fg); }
    QColor bgColor() const { return slot(m_bg); }

    // Palette: digit 0-9 -> color. Digits are what get saved to disk.
    static QColor slot(int d) {
        return Settings::instance().paletteColor(d);
    }

    static int toDigit(const QColor &c) {
        for (int i = 0; i < 10; ++i)
            if (slot(i) == c)
                return i;
        return 0;
    }

private:
    void updatePreview() {
        for (int i = 0; i < 10; ++i) {
            const QString css = QStringLiteral(
                                    "QToolButton{background:%1;border:1px solid #888;}"
                                    "QToolButton:checked{border:3px solid #000;}")
                                    .arg(slot(i).name());
            m_bgButtons[i]->setStyleSheet(css);
            m_fgButtons[i]->setStyleSheet(css);
        }
        m_preview->setStyleSheet(QStringLiteral(
                                     "background:%1;color:%2;border:1px solid #888;font-weight:bold;")
                                     .arg(slot(m_bg).name(), slot(m_fg).name()));
    }

    int m_bg = 2;   // yellow background
    int m_fg = 0;   // black text
    QVector<QToolButton*> m_bgButtons;
    QVector<QToolButton*> m_fgButtons;
    QLabel *m_preview = nullptr;
};

class HighlightApplier {
public:
    // Re-apply saved highlights to a freshly loaded page.
    static void apply(QTextBrowser *browser, const QList<Highlight> &items) {
        if (!browser || items.isEmpty())
            return;

        const QString plain = browser->toPlainText();

        for (const Highlight &h : items) {
            if (h.color.size() != 2)
                continue;
            const int bg = h.color[0].digitValue();
            const int fg = h.color[1].digitValue();
            if (bg < 0 || fg < 0)
                continue;

            // 1. Start: trust the saved offset if the text still matches there,
            //    otherwise search for the start anchor.
            int p = -1;
            if (h.offset >= 0 && plain.mid(h.offset, h.argStart.size()) == h.argStart)
                p = h.offset;
            else
                p = plain.indexOf(h.argStart);
            if (p < 0)
                continue;

            // 2. End: the end anchor must END at or after the end of the start
            //    anchor. This also covers short selections (argStart == argEnd).
            const int minEnd = p + h.argStart.size();
            int q = plain.indexOf(h.argEnd, p);
            while (q >= 0 && q + h.argEnd.size() < minEnd)
                q = plain.indexOf(h.argEnd, q + 1);
            if (q < 0)
                continue;

            const int e = q + h.argEnd.size();

            QTextCursor c(browser->document());
            c.setPosition(p);
            c.setPosition(e, QTextCursor::KeepAnchor);

            QTextCharFormat fmt;
            fmt.setBackground(HighlightDialog::slot(bg));
            fmt.setForeground(HighlightDialog::slot(fg));
            fmt.setFontWeight(QFont::Bold);
            c.mergeCharFormat(fmt);
        }
    }

    // Save the browser's current selection as a highlight record.
    static void record(QTextBrowser *browser, HighlightStore *store,
                       const QString &url, const QColor &fg, const QColor &bg) {
        if (!browser || !store || url.isEmpty())
            return;

        const QTextCursor cur = browser->textCursor();
        if (!cur.hasSelection())
            return;

        const int s = cur.selectionStart();
        const int e = cur.selectionEnd();
        const QString plain = browser->toPlainText();
        if (s < 0 || e <= s || e > plain.size())
            return;

        const QString sel = plain.mid(s, e - s);

        Highlight h;
        h.url      = url;
        h.color    = QString::number(HighlightDialog::toDigit(bg))
                  + QString::number(HighlightDialog::toDigit(fg));
        h.argStart = sel.left(32);
        h.argEnd   = sel.right(32);
        h.offset   = s;
        store->add(h);
    }
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

        applySettings();  // Apply settings before each speak
        m_speech->say(text);
    }

    void stop() {
        if (m_speech) {
            m_speech->stop();
        }
    }

    void applySettings() {
        if (!m_speech) return;

        auto &s = Settings::instance();

        m_speech->setRate(s.ttsRate());

        m_speech->setPitch(s.ttsPitch());

        m_speech->setVolume(s.ttsVolume());

        QString engine = s.ttsEngine();
        if (!engine.isEmpty() && m_speech->engine() != engine) {
            m_speech->setEngine(engine);
        }

        QString voiceName = s.ttsVoice();
        if (!voiceName.isEmpty() && voiceName != "Default") {
            QList<QVoice> voices = m_speech->availableVoices();
            for (const QVoice &voice : voices) {
                if (voice.name() == voiceName) {
                    m_speech->setVoice(voice);
                    break;
                }
            }
        }
    }

    QTextToSpeech* speech() { return m_speech; }

private:
    TTSManager() : m_speech(nullptr) {
        connect(&Settings::instance(), &Settings::settingsChanged,
                this, &TTSManager::applySettings);
    }

    QTextToSpeech *m_speech;
};
class ErrorDocEngine : public ContentEngine {
    Q_OBJECT

public:
    explicit ErrorDocEngine(HighlightStore *store, QWidget *parent = nullptr)
        : ContentEngine(parent), m_store(store) {
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

    void load(const DocumentUrl &url) override {
        if (!url.isErr()) return;
        m_currentUrl = url.url();
        m_bashCommands.clear();
        m_bashCounter = 0;

        QString path = url.path();
        if (path.startsWith("/")) path = path.mid(1);

        QString qrcPath = ":/" + path;
        if (!path.endsWith(".html")) {
            qrcPath = ":/" + path + ".html";
        }

        QFile file(qrcPath);
        if (file.open(QIODevice::ReadOnly)) {
            QString html = QString::fromUtf8(file.readAll());

            html.remove(PAGE_ICON_TAG_REGEX);

            html.replace(ICON_TAG_REGEX, "<img src=\"icon://\\1\">");

            QRegularExpressionMatchIterator fileIt = FILE_TAG_REGEX.globalMatch(html);
            while (fileIt.hasNext()) {
                QRegularExpressionMatch match = fileIt.next();
                QString filePath = match.captured(1);

                if (filePath.startsWith("~/")) {
                    filePath = QDir::homePath() + filePath.mid(1);
                } else if (filePath == "~") {
                    filePath = QDir::homePath();
                }

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
                                          "<a href='file://%1' class='file-link'>"
                                          "<img src='data:image/png;base64,%2' style='vertical-align: middle; margin-right: 5px;'>"
                                          "%3"
                                          "</a>"
                                          ).arg(filePath, iconBase64, info.fileName());

                html.replace(match.captured(0), replacement);
            }

            QRegularExpressionMatchIterator bashIt = BASH_TAG_REGEX.globalMatch(html);
            while (bashIt.hasNext()) {
                QRegularExpressionMatch match = bashIt.next();
                QString code = match.captured(1);
                QString id = QString::number(m_bashCounter++);
                m_bashCommands.insert(id, code);
                QString replacement = QString(
                                          "<div class='bash-widget'>"
                                          "<pre class='bash-code'>%1</pre>"
                                          "<a href='bash://%2' class='bash-button'>▶ Run in Terminal</a>"
                                          "</div>"
                                          ).arg(code.toHtmlEscaped(), id);
                html.replace(match.captured(0), replacement);
            }

            QString fullHtml =
                "<style>"
                "pre, code { "
                "    background-color: #1e1e1e; "
                "    color: #d4d4d4; "
                "    border: 1px solid #3c3c3c; "
                "    border-radius: 4px; "
                "    padding: 2px 6px; "
                "    font-family: 'Consolas', 'Monaco', 'Courier New', monospace; "
                "    font-size: 13px; "
                "}"
                "pre { "
                "    background-color: #1e1e1e; "
                "    padding: 12px; "
                "    overflow-x: auto; "
                "    margin: 10px 0; "
                "    border-left: 4px solid #007acc; "
                "}"
                "code { "
                "    background-color: #2d2d2d; "
                "}"
                ".bash-widget { "
                "    background-color: #1e1e1e; "
                "    color: #d4d4d4; "
                "    padding: 0; "
                "    margin: 10px 0; "
                "    border-radius: 6px; "
                "    border: 1px solid #3c3c3c; "
                "    overflow: hidden; "
                "}"
                ".bash-code { "
                "    background-color: #1e1e1e; "
                "    color: #d4d4d4; "
                "    border: none; "
                "    margin: 0; "
                "    padding: 12px; "
                "    border-radius: 0; "
                "    border-left: 4px solid #007acc; "
                "}"
                ".bash-button { "
                "    display: inline-block; "
                "    background-color: #007acc; "
                "    color: white; "
                "    padding: 6px 12px; "
                "    text-decoration: none; "
                "    border-radius: 4px; "
                "    font-size: 12px; "
                "    margin: 8px 12px 12px 12px; "
                "    font-weight: 500; "
                "}"
                ".bash-button:hover { "
                "    background-color: #005f9e; "
                "}"
                ".file-link { "
                "    display: inline-block; "
                "    padding: 6px 10px; "
                "    text-decoration: none; "
                "    border: 1px solid #3c3c3c; "
                "    border-radius: 4px; "
                "    background-color: #2d2d2d; "
                "    color: #d4d4d4; "
                "    margin: 5px 5px 5px 0; "
                "    font-size: 12px; "
                "}"
                ".file-link:hover { "
                "    background-color: #3c3c3c; "
                "    border-color: #007acc; "
                "}"
                "</style>" + html;

            QUrl baseUrl;
            if (qrcPath.startsWith(":/")) {
                baseUrl = QUrl("qrc:/" + qrcPath.mid(1));
                baseUrl = baseUrl.adjusted(QUrl::RemoveFilename);
            } else {
                baseUrl = QUrl::fromLocalFile(qrcPath).adjusted(QUrl::RemoveFilename);
            }

            m_browser->setHtml(fullHtml);
            m_browser->document()->setBaseUrl(baseUrl);

            emit titleChanged(extractTitle(html));
        } else {
            m_browser->setHtml(NotFoundPage::generate(path));
            emit titleChanged("Not Found");
        }

        m_findBar->hide();

        if (m_store)
            HighlightApplier::apply(m_browser, m_store->forUrl(m_currentUrl));
    }
    QString selectedText() const override { return m_browser->textCursor().selectedText(); }
    QString allText() const override { return m_browser->toPlainText(); }
    void find() override {
        m_findBar->show();
        m_findBar->setFocus();
    }

    void highlightSelection(const QColor &fg, const QColor &bg) override {
        QTextCursor cursor = m_browser->textCursor();
        if (!cursor.hasSelection())
            return;

        QTextCharFormat fmt;
        fmt.setForeground(fg);
        fmt.setBackground(bg);
        cursor.mergeCharFormat(fmt);

        HighlightApplier::record(m_browser, m_store, m_currentUrl, fg, bg);
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
    void onLinkClicked(const QUrl &link) {
        if (link.scheme() == "bash") {
            QString code = m_bashCommands.value(link.host());
            if (!code.isEmpty())
                TAN::tanrun(code.toStdString());

        } else if (link.toString().startsWith(":/")) {
            emit navigationRequested(link.toString());
        } else if (link.scheme() == "file") {
            QDesktopServices::openUrl(link);
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
    HighlightStore *m_store = nullptr;
    QString m_currentUrl;
    QHash<QString, QString> m_bashCommands;
    int m_bashCounter = 0;
};
class ManpageEngine : public ContentEngine {
    Q_OBJECT

public:
    explicit ManpageEngine(HighlightStore *store, QWidget *parent = nullptr)
        : ContentEngine(parent), m_store(store) {
        auto *mainLayout = new QVBoxLayout(this);
        mainLayout->setContentsMargins(0, 0, 0, 0);
        mainLayout->setSpacing(0);

        auto *splitterLayout = new QHBoxLayout();

        auto *browserWidget = new QWidget(this);
        auto *browserLayout = new QVBoxLayout(browserWidget);
        browserLayout->setContentsMargins(0, 0, 0, 0);

        m_browser = new QTextBrowser(this);
        m_browser->setContextMenuPolicy(Qt::CustomContextMenu);

        m_findBar = new FindBar(m_browser, this);
        m_findBar->hide();

        browserLayout->addWidget(m_browser);
        browserLayout->addWidget(m_findBar);

        auto *infoWidget = new QWidget(this);
        auto *infoLayout = new QVBoxLayout(infoWidget);
        infoLayout->setAlignment(Qt::AlignTop | Qt::AlignLeft);

        m_iconLabel = new QLabel(this);
        m_iconLabel->setAlignment(Qt::AlignCenter);
        m_iconLabel->setFixedSize(128, 128);
        m_iconLabel->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

        infoLayout->addStretch();
        infoLayout->addWidget(m_iconLabel, 0, Qt::AlignCenter);
        infoLayout->addSpacing(10);

        m_titleLabel = new QLabel(this);
        QFont titleFont = m_titleLabel->font();
        titleFont.setPointSize(titleFont.pointSize() + 2);
        titleFont.setBold(true);
        m_titleLabel->setFont(titleFont);
        m_titleLabel->setAlignment(Qt::AlignLeft);
        m_titleLabel->setWordWrap(true);

        m_dateLabel = new QLabel(this);
        m_dateLabel->setAlignment(Qt::AlignLeft);

        m_pathLabel = new QLabel(this);
        m_pathLabel->setAlignment(Qt::AlignLeft);
        m_pathLabel->setWordWrap(true);

        m_descLabel = new QLabel(this);
        m_descLabel->setAlignment(Qt::AlignLeft | Qt::AlignTop);
        m_descLabel->setWordWrap(true);

        QFrame *separator = new QFrame(this);
        separator->setFrameShape(QFrame::HLine);
        separator->setFrameShadow(QFrame::Sunken);

        infoLayout->addWidget(m_titleLabel);
        infoLayout->addWidget(m_dateLabel);
        infoLayout->addWidget(m_pathLabel);
        infoLayout->addWidget(separator);
        infoLayout->addWidget(m_descLabel);
        infoLayout->addStretch();

        infoWidget->setMaximumWidth(300);
        infoWidget->setMinimumWidth(250);

        auto *splitter = new QSplitter(Qt::Horizontal, this);
        splitter->addWidget(browserWidget);
        splitter->addWidget(infoWidget);
        splitter->setStretchFactor(0, 1);
        splitter->setStretchFactor(1, 0);

        splitterLayout->addWidget(splitter);
        mainLayout->addLayout(splitterLayout);

        connect(m_browser, &QTextBrowser::customContextMenuRequested, this, &ManpageEngine::showContextMenu);
    }

    void load(const DocumentUrl &url) override {
        if (!url.isMan()) return;
        m_currentUrl = url.url();

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
        if (!cursor.hasSelection())
            return;

        QTextCharFormat fmt;
        fmt.setForeground(fg);
        fmt.setBackground(bg);
        cursor.mergeCharFormat(fmt);

        HighlightApplier::record(m_browser, m_store, m_currentUrl, fg, bg);
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
        m_iconLabel->setPixmap(icon.pixmap(128, 128));
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
                        if (m_store)
                            HighlightApplier::apply(m_browser, m_store->forUrl(m_currentUrl));

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

        if (!lines.isEmpty()) {
            lines.removeFirst();
        }

        QString html = "<html><body>";

        for (const QString &line : std::as_const(lines)) {
            QString trimmed = line.trimmed();
            if (!trimmed.isEmpty() && HEADER_REGEX.match(trimmed).hasMatch()) {
                QString headerText = trimmed;
                QStringList words = headerText.split(' ', Qt::SkipEmptyParts);
                QStringList capitalizedWords;
                for (const QString &word : words) {
                    if (!word.isEmpty()) {
                        QString capWord = word.toLower();
                        capWord[0] = capWord[0].toUpper();
                        capitalizedWords.append(capWord);
                    }
                }
                QString formattedHeader = capitalizedWords.join(' ');
                html += QString("<h1>%1</h1><hr>").arg(formattedHeader);
            } else {
                html += line.toHtmlEscaped() + "<br>";
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
                desc += line + " ";
                if (desc.length() > 200) break;
            }
        }

        return desc.trimmed();
    }

    QLabel *m_iconLabel, *m_titleLabel, *m_dateLabel, *m_pathLabel, *m_descLabel;
    QTextBrowser *m_browser;
    FindBar *m_findBar;
    HighlightStore *m_store = nullptr;
    QString m_currentUrl;
};

class SettingsPage : public QScrollArea {
    Q_OBJECT

public:
    explicit SettingsPage(QWidget *parent = nullptr) : QScrollArea(parent), m_skipVoiceTest(true) {
        setWidgetResizable(true);
        setFrameShape(QFrame::NoFrame);

        auto *content = new QWidget();
        auto *layout = new QVBoxLayout(content);
        layout->setSpacing(20);

        m_ttsWarningWidget = new QWidget(this);
        m_ttsWarningWidget->setObjectName("ttsWarning");
        m_ttsWarningWidget->setStyleSheet(
            "QWidget#ttsWarning { background-color: #fff3cd; border: 1px solid #ffeeba; border-radius: 6px; }");
        auto *warnLayout = new QHBoxLayout(m_ttsWarningWidget);
        auto *warnIcon = new QLabel(this);
        warnIcon->setPixmap(QIcon::fromTheme("dialog-warning").pixmap(24, 24));
        warnIcon->setFixedSize(28, 28);
        m_ttsWarningLabel = new QLabel(this);
        m_ttsWarningLabel->setWordWrap(true);
        m_ttsWarningLabel->setStyleSheet("color: #856404;");
        m_ttsWarningLabel->setText("No text-to-speech backend was found on this system. Speech features will not work until a backend is installed.");
        m_ttsInstallBtn = new QPushButton(QIcon::fromTheme("system-software-install"), "Install Backends...", this);
        warnLayout->addWidget(warnIcon);
        warnLayout->addWidget(m_ttsWarningLabel, 1);
        warnLayout->addWidget(m_ttsInstallBtn);
        m_ttsWarningWidget->hide();
        layout->addWidget(m_ttsWarningWidget);

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

        auto *testGroup = new QGroupBox("Test Text-to-Speech", this);
        auto *testLayout = new QHBoxLayout(testGroup);

        m_testTextEdit = new QLineEdit(this);
        m_testTextEdit->setPlaceholderText("Enter text to test...");
        m_testTextEdit->setText("This is a test of the selected voice.");

        m_testSpeakBtn = new QPushButton(QIcon::fromTheme("media-playback-start"), "Test", this);

        testLayout->addWidget(m_testTextEdit);
        testLayout->addWidget(m_testSpeakBtn);

        auto *btnLayout = new QHBoxLayout();
        auto *saveBtn = new QPushButton(QIcon::fromTheme("document-save"), "Save Settings", this);
        auto *resetBtn = new QPushButton(QIcon::fromTheme("edit-clear"), "Reset All", this);
        auto *cancelBtn = new QPushButton(QIcon::fromTheme("window-close"), "Cancel", this);

        btnLayout->addWidget(saveBtn);
        btnLayout->addWidget(resetBtn);
        btnLayout->addWidget(cancelBtn);
        btnLayout->addStretch();

        auto *paletteGroup = new QGroupBox("Highlight Palette", this);
        auto *paletteGrid = new QGridLayout(paletteGroup);
        m_paletteButtons.resize(10);
        for (int i = 0; i < 10; ++i) {
            auto *lbl = new QLabel(QString::number(i), paletteGroup);
            auto *btn = new QPushButton(paletteGroup);
            btn->setFixedSize(40, 26);
            btn->setToolTip(QString("Highlight color slot %1").arg(i));
            connect(btn, &QPushButton::clicked, this, [this, i]() {
                QColor c = QColorDialog::getColor(
                    Settings::instance().paletteColor(i), this,
                    QString("Palette slot %1").arg(i));
                if (c.isValid()) {
                    Settings::instance().setPaletteColor(i, c);
                    refreshPaletteButtons();
                }
            });
            m_paletteButtons[i] = btn;
            paletteGrid->addWidget(lbl, i, 0);
            paletteGrid->addWidget(btn, i, 1);
        }
        layout->addWidget(paletteGroup);

        layout->addWidget(shortcutGroup);
        layout->addWidget(uiGroup);
        layout->addWidget(ttsGroup);
        layout->addWidget(testGroup);
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

        connect(m_testSpeakBtn, &QPushButton::clicked, this, &SettingsPage::testSpeak);
        connect(m_testTextEdit, &QLineEdit::returnPressed, this, &SettingsPage::testSpeak);

        connect(m_ttsInstallBtn, &QPushButton::clicked, this, &SettingsPage::runTtsInstallScript);

        loadSettings();
        QTimer::singleShot(100, this, &SettingsPage::populateVoices);
        QTimer::singleShot(300, this, &SettingsPage::checkTtsBackends);
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
    void refreshPaletteButtons() {
        for (int i = 0; i < m_paletteButtons.size(); ++i) {
            QColor c = Settings::instance().paletteColor(i);
            m_paletteButtons[i]->setStyleSheet(QString(
                                                   "QPushButton { background: %1; border: 1px solid #666; }"
                                                   "QPushButton:hover { border: 1px solid #000; }").arg(c.name()));
        }
    }

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

        QString engine = m_ttsEngine->currentText();
        if (engine == "Default") engine = "";
        s.setTtsEngine(engine);
        s.setTtsRate(m_ttsRate->value() / 10.0);
        s.setTtsPitch(m_ttsPitch->value() / 10.0);
        s.setTtsVolume(m_ttsVolume->value() / 100.0);
        s.setTtsVoice(m_ttsVoice->currentText());

        TTSManager::instance().applySettings();

        emit settingsChanged();
        QMessageBox::information(this, "Settings", "Settings saved successfully.");
    }

    void resetSettings() {
        int result = QMessageBox::question(this, "Reset Settings",
                                           "Reset all settings to defaults? This cannot be undone.",
                                           QMessageBox::Yes | QMessageBox::No);
        if (result == QMessageBox::Yes) {
            Settings::instance().reset();
            loadSettings();
            TTSManager::instance().applySettings();
            emit settingsChanged();
            QMessageBox::information(this, "Settings", "Settings reset to defaults.");
        }
    }

    void cancel() {
        loadSettings();
        QMessageBox::information(this, "Settings", "Changes discarded.");
    }

    void updateRateLabel(int value) {
        m_ttsRateLabel->setText(QString("%1").arg(value / 10.0, 0, 'f', 1));
    }

    void updatePitchLabel(int value) {
        m_ttsPitchLabel->setText(QString("%1").arg(value / 10.0, 0, 'f', 1));
    }

    void updateVolumeLabel(int value) {
        m_ttsVolumeLabel->setText(QString("%1%").arg(value));
    }

    void testSpeak() {
        QString text = m_testTextEdit->text();
        if (text.isEmpty()) {
            QMessageBox::information(this, "Test", "Please enter text to test.");
            return;
        }

        QTextToSpeech *testSpeech = new QTextToSpeech(this);

        QString engine = m_ttsEngine->currentText();
        if (engine != "Default" && !engine.isEmpty()) {
            testSpeech->setEngine(engine);
        }

        if (testSpeech->state() == QTextToSpeech::Error) {
            QMessageBox::warning(this, "Text-to-Speech Error",
                                 "No working text-to-speech backend was found.\n\n"
                                 "Would you like to install espeak-ng and related backends now?",
                                 QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes
                ? runTtsInstallScript()
                : (void)0;
            testSpeech->deleteLater();
            return;
        }

        testSpeech->setRate(m_ttsRate->value() / 10.0);
        testSpeech->setPitch(m_ttsPitch->value() / 10.0);
        testSpeech->setVolume(m_ttsVolume->value() / 100.0);

        QString voiceName = m_ttsVoice->currentText();
        if (!voiceName.isEmpty() && voiceName != "Default") {
            const QList<QVoice> voices = testSpeech->availableVoices();
            for (const QVoice &voice : voices) {
                if (voice.name() == voiceName) {
                    testSpeech->setVoice(voice);
                    break;
                }
            }
        }

        connect(testSpeech, &QTextToSpeech::stateChanged, this, [testSpeech](QTextToSpeech::State state) {
            if (state == QTextToSpeech::Ready || state == QTextToSpeech::Error) {
                testSpeech->deleteLater();
            }
        });

        testSpeech->say(text);
    }

    void onEngineChanged(int index) {
        Q_UNUSED(index)
        m_skipVoiceTest = true;
        populateVoices();
    }

    void onVoiceChanged(int index) {
        Q_UNUSED(index)
        if (m_skipVoiceTest) {
            m_skipVoiceTest = false;
            return;
        }
    }

    void populateVoices() {
        m_ttsVoice->clear();

        if (!m_testSpeech) {
            m_testSpeech = new QTextToSpeech(this);
        }

        QString engine = m_ttsEngine->currentText();
        if (engine == "Default") engine = "";

        if (m_testSpeech->engine() != engine) {
            m_testSpeech->setEngine(engine);
        }

        const QList<QVoice> voices = m_testSpeech->availableVoices();
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

        QString engine = s.ttsEngine();
        if (engine.isEmpty()) engine = "Default";
        int idx = m_ttsEngine->findText(engine);
        if (idx >= 0) m_ttsEngine->setCurrentIndex(idx);

        m_ttsRate->setValue(s.ttsRate() * 10);
        m_ttsPitch->setValue(s.ttsPitch() * 10);
        m_ttsVolume->setValue(s.ttsVolume() * 100);

        updateRateLabel(m_ttsRate->value());
        updatePitchLabel(m_ttsPitch->value());
        updateVolumeLabel(m_ttsVolume->value());

        refreshPaletteButtons();
        QTimer::singleShot(200, this, &SettingsPage::populateVoices);
    }

    void checkTtsBackends() {
        bool hasBackend = !QTextToSpeech::availableEngines().isEmpty();

        if (!hasBackend) {
            const QStringList candidates = { "espeak-ng", "espeak", "speech-dispatcher", "spd-say" };
            for (const QString &bin : candidates) {
                if (!QStandardPaths::findExecutable(bin).isEmpty()) {
                    hasBackend = true;
                    break;
                }
            }
        }

        m_ttsWarningWidget->setVisible(!hasBackend);

        if (!hasBackend) {
            int answer = QMessageBox::question(
                this, "Text-to-Speech Backend Missing",
                "No text-to-speech backend was found on this system.\n\n"
                "Would you like to install espeak-ng and related backends now?\n"
                "This will open a terminal and run apt as root.",
                QMessageBox::Yes | QMessageBox::No);

            if (answer == QMessageBox::Yes) {
                runTtsInstallScript();
            }
        }
    }

    void runTtsInstallScript() {
        const QString cmd =
            "apt-get update && apt-get install -y espeak-ng espeak-ng-data "
            "speech-dispatcher libspeechd2 speech-dispatcher-espeak-ng";

        if (!TAN::tanrunsu(cmd.toStdString())) {
            QMessageBox::warning(this, "Launch Failed",
                                 "Could not launch a terminal to run the install command.");
        }
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
    QVector<QPushButton*> m_paletteButtons;

    QComboBox *m_ttsEngine;
    QSlider *m_ttsRate;
    QSlider *m_ttsPitch;
    QSlider *m_ttsVolume;
    QLabel *m_ttsRateLabel;
    QLabel *m_ttsPitchLabel;
    QLabel *m_ttsVolumeLabel;
    QComboBox *m_ttsVoice;

    QWidget *m_ttsWarningWidget;
    QLabel *m_ttsWarningLabel;
    QPushButton *m_ttsInstallBtn;

    QLineEdit *m_testTextEdit;
    QPushButton *m_testSpeakBtn;

    QTextToSpeech *m_testSpeech = nullptr;
    bool m_skipVoiceTest;
};
class BookmarksPage : public QWidget {
    Q_OBJECT

public:
    BookmarksPage(BookmarkStore *store, QWidget *parent = nullptr)
        : QWidget(parent), m_store(store)
    {
        auto *layout = new QVBoxLayout(this);

        auto *toolbar = new QHBoxLayout();
        auto *deleteBtn = new QPushButton(QIcon::fromTheme("edit-clear"), "Delete Selected", this);
        auto *deleteAllBtn = new QPushButton(QIcon::fromTheme("edit-delete"), "Delete All", this);

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
            "<p><b>Version:</b> 2.0</p>"
            "<h3>About</h3>"
            "This documentation takes a time on startup is the main disatvantage except that using this is easy make sure to have installed \"man\""
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


class ContentArea : public QStackedWidget {
    Q_OBJECT

public:
    ContentArea(BookmarkStore *store, HighlightStore *highlightStore, QWidget *parent = nullptr)
        : QStackedWidget(parent), m_store(store), m_highlightStore(highlightStore)
    {
        m_welcomeEngine = new WelcomeEngine(this);
        m_errEngine = new ErrorDocEngine(m_highlightStore, this);
        m_manEngine = new ManpageEngine(m_highlightStore, this);
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
        if (url.startsWith(":/err/")) return "documentation";
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
    HighlightStore *m_highlightStore = nullptr;
    DocumentUrl *m_currentUrl;
    WelcomeEngine *m_welcomeEngine;
    ErrorDocEngine *m_errEngine;
    ManpageEngine *m_manEngine;
    DocEngine *m_docEngine;
};


class TabContent : public QWidget {
    Q_OBJECT

public:
    TabContent(BookmarkStore *store, HighlightStore *highlightStore, QWidget *parent = nullptr)
        : QWidget(parent)
    {
        auto *layout = new QVBoxLayout(this);
        layout->setContentsMargins(0, 0, 0, 0);

        m_contentArea = new ContentArea(store, highlightStore, this);
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
        loadingItem->setText(0, "Loading manpages");
        manItem->setExpanded(true);

        auto *thread = new QThread(this);
        auto *worker = new ManpageLoaderWorker();
        worker->moveToThread(thread);

        connect(thread, &QThread::started, worker, &ManpageLoaderWorker::loadManpages);
        connect(worker, &ManpageLoaderWorker::manpagesLoaded, this,
                [this, manItem, loadingItem](const QString &output) {
                    if (!output.isEmpty()) {
                        parseManpages(output, manItem);
                    }
                    delete loadingItem;
                    emit manpagesLoaded();
                });
        connect(worker, &ManpageLoaderWorker::manpagesLoaded, thread, &QThread::quit);
        connect(thread, &QThread::finished, worker, &QObject::deleteLater);
        connect(thread, &QThread::finished, thread, &QObject::deleteLater);

        emit manpagesProgress(QStringLiteral("Loading manpages"));
        thread->start();
    }

signals:
    void navigationRequested(const QString &url);
    void navigationRequestedNewTab(const QString &url);
    void bookmarkRequested(const QString &url, const QString &title);
    void manpagesLoaded();
    void manpagesProgress(const QString &text);

private slots:
    void onItemActivated(QTreeWidgetItem *item) {
        if (!item) return;

        bool hasChildren = (item->childCount() > 0);

        if (hasChildren) {
            // This is a folder/section - just expand/collapse, don't navigate
            item->setExpanded(!item->isExpanded());
            return;
        }

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
        scanQrcDirectoryRecursive(":/", errItem);

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
        QDirIterator it(path, QDirIterator::NoIteratorFlags);
        QMap<QString, QTreeWidgetItem*> dirs;

        QStringList htmlFiles;
        QStringList subdirs;

        while (it.hasNext()) {
            QString file = it.next();
            QFileInfo info(file);

            if (info.isDir()) {
                if (info.fileName().startsWith(".")) continue;
                subdirs << file;
            } else if (info.fileName().endsWith(".html")) {
                htmlFiles << file;
            }
        }

        if (htmlFiles.isEmpty() && subdirs.isEmpty()) {
            return;
        }

        for (const QString &dir : subdirs) {
            QFileInfo info(dir);
            QTreeWidgetItem *dirItem = new QTreeWidgetItem(parent);
            QString folderName = info.fileName();
            dirItem->setText(0, folderName);

            QIcon icon = QIcon::fromTheme(folderName);
            if (icon.isNull()) {
                icon = QIcon::fromTheme("folder");
            }
            dirItem->setIcon(0, icon);

            dirItem->setData(0, Qt::UserRole, QString());
            scanQrcDirectoryRecursive(dir, dirItem);

            if (dirItem->childCount() == 0) {
                delete dirItem;
            }
        }

        for (const QString &file : htmlFiles) {
            QFileInfo info(file);
            auto *item = new QTreeWidgetItem(parent);
            QString displayName = info.baseName();
            item->setText(0, displayName);

            QIcon icon = QIcon::fromTheme("documentation");
            QFile f(file);
            if (f.open(QIODevice::ReadOnly | QIODevice::Text)) {
                const QByteArray head = f.read(1024);
                const QRegularExpressionMatch m =
                    PAGE_ICON_TAG_REGEX.match(QString::fromUtf8(head));
                if (m.hasMatch()) {
                    QIcon themed = QIcon::fromTheme(m.captured(1));
                    if (!themed.isNull())
                        icon = themed;
                }
            }
            item->setIcon(0, icon);

            QString urlPath = file;
            // Remove the ":/" prefix
            if (urlPath.startsWith(":/")) {
                urlPath = urlPath.mid(2);
            }
            if (urlPath.endsWith(".html")) {
                urlPath.chop(5);
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
class LoadingSplash : public QDialog {
    Q_OBJECT

public:
    explicit LoadingSplash(QWidget *parent = nullptr)
        : QDialog(parent, Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint)
    {
        setAttribute(Qt::WA_TranslucentBackground);
        setFixedSize(300, 180);

        auto *layout = new QVBoxLayout(this);
        layout->setAlignment(Qt::AlignCenter);

        auto *iconLabel = new QLabel(this);
        iconLabel->setPixmap(QIcon::fromTheme("error.doc", QIcon::fromTheme("help-browser")).pixmap(64, 64));
        iconLabel->setAlignment(Qt::AlignCenter);

        m_label = new QLabel(this);
        m_label->setAlignment(Qt::AlignCenter);

        layout->addWidget(iconLabel);
        layout->addWidget(m_label);

        connect(&m_dotTimer, &QTimer::timeout, this, &LoadingSplash::advanceDots);
        m_dotTimer.start(1000);
    }

    void setBaseText(const QString &text) {
        m_baseText = text;
        m_dotCount = 3;
        m_dotDirection = -1;
        updateLabel();
    }

protected:
    void mousePressEvent(QMouseEvent *event) override {
        if (event->button() == Qt::LeftButton) {
            m_dragPos = event->globalPosition().toPoint() - frameGeometry().topLeft();
            event->accept();
        }
    }

    void mouseMoveEvent(QMouseEvent *event) override {
        if (event->buttons() & Qt::LeftButton) {
            move(event->globalPosition().toPoint() - m_dragPos);
            event->accept();
        }
    }

private slots:
    void advanceDots() {
        m_dotCount += m_dotDirection;
        if (m_dotCount >= 3) {
            m_dotCount = 3;
            m_dotDirection = -1;
        } else if (m_dotCount <= 1) {
            m_dotCount = 1;
            m_dotDirection = 1;
        }
        updateLabel();
    }

private:
    void updateLabel() {
        m_label->setText(m_baseText + QString(".").repeated(m_dotCount));
    }

    QLabel *m_label;
    QString m_baseText;
    int m_dotCount = 3;
    int m_dotDirection = -1;
    QTimer m_dotTimer;
    QPoint m_dragPos;
};

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow() {
        setWindowTitle("error.doc");
        resize(1200, 800);

        m_splash = new LoadingSplash(nullptr);
        m_splash->setBaseText("Loading");

        m_splash->show();
        QApplication::processEvents();

        m_bookmarkStore = new BookmarkStore(this);
        m_highlightStore = new HighlightStore(this);
        m_ttsManager = &TTSManager::instance();

        m_recentUrls.clear();
        m_recentTitles.clear();
        m_recentIcons.clear();

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
        connect(m_navTree, &NavigationTree::manpagesProgress,
                this, [this](const QString &text) {
                    if (m_splash)
                        m_splash->setBaseText(text);
                });
        connect(m_navTree, &NavigationTree::manpagesLoaded,
                this, [this]() {
                    setWindowIcon(QIcon::fromTheme("error.doc",
                                                   QIcon::fromTheme("help-browser")));
                    show();
                    if (m_splash) {
                        m_splash->accept();
                        m_splash->deleteLater();
                        m_splash = nullptr;
                    }
                });

        connect(m_bookmarkStore, &BookmarkStore::changed, this, &MainWindow::onBookmarksChanged);
        connect(&Settings::instance(), &Settings::settingsChanged,
                this, &MainWindow::reloadShortcuts);

        m_splash->setBaseText(QStringLiteral("Loading Doc components"));
        m_navTree->initializeManpages();
    }
private slots:
    void navigateCurrentTab(const QString &url) {
        if (TabContent *tab = currentTab()) {
            QString currentUrl = tab->contentArea()->currentUrl()->url();
            QString currentTitle = tab->contentArea()->currentEngine()->windowTitle();
            QIcon currentIcon = m_tabWidget->tabIcon(m_tabWidget->currentIndex());

            if (!currentUrl.isEmpty() && currentUrl != ":/") {
                addToRecent(currentUrl, currentTitle, currentIcon);
            }

            tab->contentArea()->navigate(url);
            updateUrlBar(url);
            m_navTree->setCurrentUrl(url);
            updateBackButton();
        }
    }

    void addNewTab(const QString &url = ":/") {
        auto *tab = new TabContent(m_bookmarkStore, m_highlightStore, this);

        QString title;
        QTreeWidgetItemIterator it(m_navTree);
        while (*it) {
            QTreeWidgetItem *item = *it;
            if (item->data(0, Qt::UserRole).toString() == url) {
                title = item->text(0);
                break;
            }
            ++it;
        }

        if (title.isEmpty()) {
            title = url.mid(url.lastIndexOf('/') + 1);
            if (title.isEmpty() || url == ":/") {
                title = "Welcome";
            }
        }

        int index = m_tabWidget->addTab(tab, title);
        m_tabWidget->setCurrentIndex(index);

        QIcon initialIcon;
        it = QTreeWidgetItemIterator(m_navTree);
        while (*it) {
            QTreeWidgetItem *item = *it;
            if (item->data(0, Qt::UserRole).toString() == url) {
                initialIcon = item->icon(0);
                break;
            }
            ++it;
        }

        if (!initialIcon.isNull()) {
            m_tabWidget->setTabIcon(index, initialIcon);
        }

        connect(tab->contentArea(), &ContentArea::urlChanged, this, [this, index](const QString &url) {
            if (m_tabWidget->currentIndex() == index) {
                updateUrlBar(url);
                m_navTree->setCurrentUrl(url);
                updateBackButton();
            }
            updateTabFromUrl(index, url);
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
                m_recentUrls.clear();
                m_recentTitles.clear();
                m_recentIcons.clear();
                updateBackButton();
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
                updateBackButton();

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

    void navigateBack() {
        if (!m_recentUrls.isEmpty()) {
            QString url = m_recentUrls.takeFirst();
            QString title = m_recentTitles.takeFirst();
            QIcon icon = m_recentIcons.takeFirst();

            if (TabContent *tab = currentTab()) {
                tab->contentArea()->navigate(url);
                updateUrlBar(url);
                m_navTree->setCurrentUrl(url);
                updateBackButton();
            }
        }
    }

    void addToRecent(const QString &url, const QString &title, const QIcon &icon) {
        int index = m_recentUrls.indexOf(url);
        if (index != -1) {
            m_recentUrls.removeAt(index);
            m_recentTitles.removeAt(index);
            if (index < m_recentIcons.size()) m_recentIcons.removeAt(index);
        }

        m_recentUrls.prepend(url);
        m_recentTitles.prepend(title);
        m_recentIcons.prepend(icon);

        while (m_recentUrls.size() > 3) {
            m_recentUrls.removeLast();
            m_recentTitles.removeLast();
            if (m_recentIcons.size() > 3) m_recentIcons.removeLast();
        }
    }

    void updateBackButton() {
        if (!m_backBtn) return;

        m_backMenu->clear();

        if (!m_recentUrls.isEmpty()) {
            for (int i = 0; i < m_recentUrls.size(); ++i) {
                QAction *action = new QAction(m_recentIcons.value(i), m_recentTitles.value(i), m_backMenu);
                action->setData(m_recentUrls[i]);
                m_backMenu->addAction(action);
            }
            m_backMenu->addSeparator();
            QAction *clearAction = m_backMenu->addAction(QIcon::fromTheme("edit-clear"), "Clear History");
            connect(clearAction, &QAction::triggered, [this]() {
                m_recentUrls.clear();
                m_recentTitles.clear();
                m_recentIcons.clear();
                updateBackButton();
            });
        } else {
            QAction *action = m_backMenu->addAction("No recent pages");
            action->setEnabled(false);
        }

        connect(m_backMenu, &QMenu::triggered, this, [this](QAction *action) {
            QString url = action->data().toString();
            if (!url.isEmpty()) {
                navigateCurrentTab(url);
            }
        });

        m_backBtn->setEnabled(!m_recentUrls.isEmpty());

        if (!m_recentUrls.isEmpty()) {
            QString tooltip =  "Long press for more options";
            m_backBtn->setToolTip(tooltip);
        } else {
            m_backBtn->setToolTip("Back");
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
            QString url = tab->contentArea()->currentUrl()->url();
            QString title = url.mid(url.lastIndexOf('/') + 1);

            BookmarkDialog dlg(m_bookmarkStore, url, title, this);
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
        for (QShortcut *shortcut : std::as_const(m_shortcuts)) {
            delete shortcut;
        }
        m_shortcuts.clear();
        setupShortcuts();
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

        m_backBtn = new QToolButton(this);
        m_backBtn->setIcon(QIcon::fromTheme("go-previous"));
        m_backBtn->setToolTip("Back (long press for history)");
        m_backBtn->setPopupMode(QToolButton::MenuButtonPopup);

        m_backMenu = new QMenu(this);
        m_backBtn->setMenu(m_backMenu);

        connect(m_backBtn, &QToolButton::clicked, this, &MainWindow::navigateBack);

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

        m_toolbar->addWidget(m_backBtn);
        m_toolbar->addWidget(m_urlBar);
        m_toolbar->addWidget(refreshBtn);
        m_toolbar->addWidget(newTabBtn);
        m_toolbar->addWidget(m_highlightBtn);
        m_toolbar->addWidget(speakBtn);
        m_toolbar->addWidget(findBtn);
        m_toolbar->addWidget(stopBtn);
        m_toolbar->addWidget(bookmarkBtn);
    }

    void setupUrlCompleter() {
        if (!m_urlBar) return;

        m_completer = new QCompleter(this);
        m_urlBar->setCompleter(m_completer);

        QStringListModel *model = new QStringListModel(this);
        m_completer->setModel(model);
        m_completer->setCaseSensitivity(Qt::CaseInsensitive);
        m_completer->setFilterMode(Qt::MatchContains);

        updateCompleterModel();
    }

    void updateCompleterModel() {
        if (!m_completer || !m_navTree) return;

        QStringList allUrls;
        QTreeWidgetItemIterator it(m_navTree);
        while (*it) {
            QTreeWidgetItem *item = *it;
            QString url = item->data(0, Qt::UserRole).toString();
            if (!url.isEmpty()) {
                allUrls << url;
            }
            ++it;
        }
        allUrls.removeDuplicates();

        QAbstractItemModel *currentModel = m_completer->model();
        if (!currentModel) {
            QStringListModel *newModel = new QStringListModel(this);
            m_completer->setModel(newModel);
            currentModel = newModel;
        }

        if (auto *model = qobject_cast<QStringListModel*>(currentModel)) {
            model->setStringList(allUrls);
        }

        if (m_urlBar) {
            m_completer->setCompletionPrefix(m_urlBar->text());
        }
    }

    void setupShortcuts() {
        auto &settings = Settings::instance();

        QShortcut *optionsShortcut = new QShortcut(QKeySequence(settings.shortcutOptions()), this);
        connect(optionsShortcut, &QShortcut::activated, this, &MainWindow::toggleOptionsMenu);
        m_shortcuts.append(optionsShortcut);

        QShortcut *newTabShortcut = new QShortcut(QKeySequence(settings.shortcutNewTab()), this);
        connect(newTabShortcut, &QShortcut::activated, [this]() { addNewTab(); });
        m_shortcuts.append(newTabShortcut);

        QShortcut *closeTabShortcut = new QShortcut(QKeySequence(settings.shortcutCloseTab()), this);
        connect(closeTabShortcut, &QShortcut::activated, [this]() {
            if (m_tabWidget->count() > 0) closeTab(m_tabWidget->currentIndex());
        });
        m_shortcuts.append(closeTabShortcut);

        QShortcut *findShortcut = new QShortcut(QKeySequence(settings.shortcutFind()), this);
        connect(findShortcut, &QShortcut::activated, this, &MainWindow::findInPage);
        m_shortcuts.append(findShortcut);

        QShortcut *speakShortcut = new QShortcut(QKeySequence(settings.shortcutSpeak()), this);
        connect(speakShortcut, &QShortcut::activated, this, &MainWindow::speakText);
        m_shortcuts.append(speakShortcut);

        QShortcut *stopShortcut = new QShortcut(QKeySequence(settings.shortcutStopSpeech()), this);
        connect(stopShortcut, &QShortcut::activated, this, &MainWindow::stopSpeech);
        m_shortcuts.append(stopShortcut);

        QShortcut *bookmarksShortcut = new QShortcut(QKeySequence(settings.shortcutBookmarks()), this);
        connect(bookmarksShortcut, &QShortcut::activated, this, &MainWindow::showBookmarks);
        m_shortcuts.append(bookmarksShortcut);

        QShortcut *refreshShortcut = new QShortcut(QKeySequence(settings.shortcutRefresh()), this);
        connect(refreshShortcut, &QShortcut::activated, this, &MainWindow::refresh);
        m_shortcuts.append(refreshShortcut);
    }

    void updateTabBarVisibility() {
        if (!m_tabWidget) return;
        bool showAlways = Settings::instance().showTabAlways();
        m_tabWidget->tabBar()->setVisible(showAlways || m_tabWidget->count() > 1);
    }

    void updateTabFromUrl(int index, const QString &url) {
        if (!m_tabWidget) return;
        QTreeWidgetItemIterator it(m_navTree);
        while (*it) {
            QTreeWidgetItem *item = *it;
            if (item->data(0, Qt::UserRole).toString() == url) {
                QString title = item->text(0);
                if (title.isEmpty()) title = "New Tab";
                m_tabWidget->setTabText(index, title);
                QIcon icon = item->icon(0);
                if (!icon.isNull()) {
                    m_tabWidget->setTabIcon(index, icon);
                }
                break;
            }
            ++it;
        }
    }

    void updateUrlBar(const QString &url) {
        if (m_urlBar) {
            m_urlBar->setText(url);
            updateCompleterModel();
        }
    }

    TabContent* currentTab() {
        return qobject_cast<TabContent*>(m_tabWidget->currentWidget());
    }

    BookmarkStore *m_bookmarkStore = nullptr;
    HighlightStore *m_highlightStore = nullptr;
    NavigationTree *m_navTree = nullptr;
    QTabWidget *m_tabWidget = nullptr;
    QToolBar *m_toolbar = nullptr;
    QLineEdit *m_urlBar = nullptr;
    QLineEdit *m_treeSearchEdit = nullptr;
    QToolButton *m_highlightBtn = nullptr;
    QToolButton *m_backBtn = nullptr;
    QMenu *m_backMenu = nullptr;
    TTSManager *m_ttsManager = nullptr;
    LoadingSplash *m_splash = nullptr;
    QCompleter *m_completer = nullptr;
    QList<QShortcut*> m_shortcuts;

    QStringList m_recentUrls;
    QStringList m_recentTitles;
    QList<QIcon> m_recentIcons;
};
int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    QApplication::setApplicationName("doc");
    QApplication::setOrganizationName("error.os");

    MainWindow window;

    return app.exec();
}

#include "main.moc"
