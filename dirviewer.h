#ifndef DIRVIEWER_H
#define DIRVIEWER_H

#include <QCheckBox>
#include <QFileSystemModel>
#include <QLineEdit>
#include <QSortFilterProxyModel>
#include <QTreeView>
#include <QWidget>

class DirViewer  : public QWidget
{
    Q_OBJECT
public:
    DirViewer();
private slots:
    void on_filter_textChanged(const QString &arg1);
    void on_sensitive_stateChanged();
private:

    QLineEdit* m_filter;
    QTreeView* m_tree;
    QFileSystemModel* m_model;
    QCheckBox* m_register_sensitivity;
    QSortFilterProxyModel* m_proxy_model;

    const QString m_currentUserHomeDirPath = QDir::cleanPath(QDir::home().path());

    void setupTree();
    void setupFileSystemModel();
    void setupProxyModel();
    void setupRIToTree(const QModelIndex &rootIndex);
};

#endif // DIRVIEWER_H
