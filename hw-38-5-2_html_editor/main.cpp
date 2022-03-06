#include "mainwindow.h"

#include <QApplication>
#include <QHBoxLayout>

#include <QWebEngineView>
#include <QPlainTextEdit>
#include <QSizePolicy>
#include <QDesktopWidget>
#include <iostream>
#include <fstream>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QWidget window;
    QHBoxLayout placement(&window);
    auto view = new QWebEngineView;
    view->load(QUrl::fromLocalFile("C:\\Users\\burma\\Desktop\\C++\\HW\\HW-38 advanced Qt\\hw-38.5.2 html editor Qt\\hw-38-5-2_html_editor\\test.html"));
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
        if (!firstLoad){
            file.open("C:\\Users\\burma\\Desktop\\C++\\HW\\HW-38 advanced Qt\\hw-38.5.2 html editor Qt\\hw-38-5-2_html_editor\\test.html");
            file << editor->toPlainText().toStdString();
            file.close();
            view->reload();
        } else {
            firstLoad=false;
        }
    });

    QDesktopWidget *desc = QApplication::desktop();
    window.resize(desc->width(), desc->height());
    window.show();

    return a.exec();

    delete editor;
    delete desc;
    delete view;

}

#include <main.moc>
