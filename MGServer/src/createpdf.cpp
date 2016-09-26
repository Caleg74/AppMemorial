#include "createpdf.h"
#include <QPrinter>
#include <QTextStream>
#include <QFile>
#include <QDebug>

CreatePdf::CreatePdf()
 : QObject()
 , m_doc()
{

}

void CreatePdf::Print()
{
    QString strFileName = "../MGServer/pdf/MemorialGander2016.pdf";
    QPrinter printer(QPrinter::PrinterResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setPaperSize(QPrinter::A4);
    printer.setOutputFileName(strFileName);

    QTextDocument doc;
    QFile file("../MGServer/pdf/TestHtml.html");
    if(!file.open(QIODevice::ReadOnly)) {
        qDebug() << "Unable to open file " << file.errorString();
    }
    QTextStream in(&file);

    m_doc.setHtml(in.readAll());
    m_doc.setPageSize(printer.pageRect().size()); // This is necessary if you want to hide the page number
    m_doc.print(&printer);
}
