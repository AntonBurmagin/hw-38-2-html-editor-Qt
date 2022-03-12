#include "mainwindow.h"

#include <QApplication>
#include <QHBoxLayout>

#include <QWebEngineView>
#include <QPlainTextEdit>
#include <QSizePolicy>
#include <QDesktopWidget>
#include <iostream>
#include <fstream>

#include <QDir>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QWidget window;
    QHBoxLayout placement(&window);
    auto view = new QWebEngineView;
    view->load(QUrl("http://mycpp.ru/cpp/scpp/cppd_virtual.htm"));
    auto editor = new QPlainTextEdit;
    bool firstLoad = true;
    view->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    editor->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    placement.addWidget(editor);
    placement.addWidget(view);

    QObject::connect(view, &QWebEngineView::loadFinished, [view, editor, &firstLoad](bool ok) {
            if (ok && firstLoad){
                view->page()->toHtml([editor](const QString &result){
                editor->setPlainText(result);
                });
            }
    });

    std::ofstream file;

    QObject::connect(editor, &QPlainTextEdit::textChanged, [view, editor, &file, &firstLoad]() {
        file.open("..\\google.html");
        file << editor->toPlainText().toStdString();
        file.close();
        if(firstLoad) {
            auto dir = QDir::currentPath();
            dir += "../../google.html";
            view->load(QUrl::fromLocalFile(dir));
            firstLoad=false;
        } else {
            view->reload();
        }
    });

    window.showMaximized();

    return a.exec();
    delete editor;
    delete view;

}

#include <main.moc>
