#include "dirviewer.h"
#include <QFileIconProvider>
#include <QGridLayout>
#include <QLabel>
#include <QCheckBox>

DirViewer::DirViewer()
{
    setupFileSystemModel();
    setupProxyModel();
    setupTree();

    m_filter = new QLineEdit();
    m_register_sensitivity=nullptr;
    m_register_sensitivity = new QCheckBox();
    m_register_sensitivity->setText("Чуствительность регистра");

    connect(m_filter, SIGNAL(textChanged(const QString &)), this, SLOT(on_filter_textChanged(const QString &)));
    connect(m_register_sensitivity, SIGNAL(stateChanged(int)), this, SLOT(on_sensitive_stateChanged()));

    //set widgets into layout
    QGridLayout* mainLayout = new QGridLayout;
    mainLayout->addWidget(m_filter,                     0, 0, 1, 3);
    mainLayout->addWidget(m_register_sensitivity,       1, 0, 1, 1);
    mainLayout->addWidget(m_tree,                       2, 0, 1, 3);
    setLayout(mainLayout);
    setWindowTitle("DirViewer");
}

void DirViewer::setupFileSystemModel()
{
    m_model = new QFileSystemModel;
    m_model->setRootPath("");
    m_model->setFilter(QDir::Dirs | QDir::Hidden | QDir::Files | QDir::NoDotAndDotDot);
    m_model->iconProvider()->setOptions(QFileIconProvider::DontUseCustomDirectoryIcons);
}

void DirViewer::setupProxyModel()
{
    m_proxy_model = new QSortFilterProxyModel(this);
    m_proxy_model->setSourceModel(m_model);
    m_proxy_model->setFilterKeyColumn(0);
    m_proxy_model->setRecursiveFilteringEnabled(true);
}

void DirViewer::setupTree()
{

    m_tree = new QTreeView();
    m_tree->setModel(m_proxy_model);

    const QModelIndex rootIndexNoProxy = m_model->index(m_currentUserHomeDirPath);
    const QModelIndex rootIndex = m_proxy_model->mapFromSource(rootIndexNoProxy);
    setupRIToTree(rootIndex);


    // Demonstrating look and feel features
    m_tree->setAnimated(false);
    m_tree->setIndentation(20);
    m_tree->setSortingEnabled(true);
    m_tree->setColumnWidth(0, m_tree->width() / 3);
}

void DirViewer::setupRIToTree(const QModelIndex& rootIndex){
    if (rootIndex.isValid()) {
        m_tree->setRootIndex(rootIndex);
        m_tree->expand(rootIndex);
    }
}

void DirViewer::on_filter_textChanged(const QString &text)
{        
    Qt::CaseSensitivity caseSensitive = (m_register_sensitivity->isChecked()) ? Qt::CaseSensitive : Qt::CaseInsensitive;
    QRegExp::PatternSyntax syntex = QRegExp::PatternSyntax(QRegExp::RegExp);
    QRegExp regExp(text, caseSensitive, syntex);
    m_proxy_model->setFilterRegExp(regExp);

    if (text.isEmpty()){
        const QModelIndex rootIndexNoProxy = m_model->index(m_currentUserHomeDirPath);
        const QModelIndex rootIndex = m_proxy_model->mapFromSource(rootIndexNoProxy);
        setupRIToTree(rootIndex);
    }

    //поиск
    //m_tree->keyboardSearch(text);
    //Фильтрация по имени
    //m_model->setNameFilters(QStringList()<< text);
}

void DirViewer::on_sensitive_stateChanged()
{
   // qDebug() << state;
    m_filter->setText("");
}

