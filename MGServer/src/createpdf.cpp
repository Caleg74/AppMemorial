#include "createpdf.h"
#include <QFile>
#include <QDebug>
#include <QTextCursor>

CreatePdf::CreatePdf()
 : QObject()
// , m_doc()
 , m_printer(QPrinter::PrinterResolution)
{

}

void CreatePdf::Print()
{
    //-------
//    QPrinter printer;
//    printer.setOutputFormat(QPrinter::PdfFormat);
//    printer.setOutputFileName("/foobar/nonwritable.pdf");
//    QPainter painter;
//    if (! painter.begin(&printer)) { // failed to open file
//        qWarning("failed to open file, is it writable?");
//        return 1;
//    }
//    painter.drawText(10, 10, "Test");
//    if (! printer.newPage()) {
//        qWarning("failed in flushing page to disk, disk full?");
//        return 1;
//    }
//    painter.drawText(10, 10, "Test 2");
//    painter.end();
    //-----------

    QString strFileName = "../MGServer/pdf/MemorialGander2016.pdf";
    m_printer.setOutputFormat(QPrinter::PdfFormat);
    m_printer.setPaperSize(QPrinter::A4);
    m_printer.setOutputFileName(strFileName);

    if (! m_painter.begin(&m_printer)) { // failed to open file
        qWarning("failed to open file, is it writable?");
        return;
    }

   PrintMenAllround(false);

    if (! m_printer.newPage()) {
        qWarning("failed in flushing page to disk, disk full?");
    }

    PrintWomenAllround(false);

//    PrintWomenAllround(false);
//    m_printer.newPage();

//    PrintMenCitycup(false);
//    m_printer.newPage();

//    PrintWomenCitycup(false);

//    m_doc.setHtml(m_textStream.readAll());
//    m_doc.setPageSize(m_printer.pageRect().size()); // This is necessary if you want to hide the page number

    m_painter.end();
//    m_doc.print(&m_printer);
}

void CreatePdf::PrintMenAllround(bool p_bHFImages)
{
    QTextDocument doc;
    QFile file("../MGServer/pdf/TestHtmlMen.html");
    if(!file.open(QIODevice::ReadOnly)) {
        qDebug() << "Unable to open file " << file.errorString();
    }
    QTextStream strLocalText(&file);

//    QWebView web;
//    web.setHtml(strLocalText);
//    web.print(&printer);

    QTextCursor cur(&doc);
//    cur.movePosition(QTextCursor::Start);
//    cur.insertText("Ciao!");
    cur.insertHtml(strLocalText.readAll());

    doc.drawContents(&m_painter);
    file.close();
}

void CreatePdf::PrintWomenAllround(bool p_bHFImages)
{
    QTextDocument doc;
    QFile file("../MGServer/pdf/TestHtmlWomen.html");
    if(!file.open(QIODevice::ReadOnly)) {
        qDebug() << "Unable to open file " << file.errorString();
    }
    QTextStream strLocalText(&file);

    QTextCursor cur(&doc);
//    cur.movePosition(QTextCursor::Start);
//    cur.insertText("Ciao!");
    cur.insertHtml(strLocalText.readAll());


    doc.drawContents(&m_painter);

    file.close();
}

void CreatePdf::PrintMenCitycup(bool p_bHFImages)
{

}


void CreatePdf::PrintWomenCitycup(bool p_bHFImages)
{

}
