#ifndef CREATEPDF_H
#define CREATEPDF_H

#include <QTextDocument>

class CreatePdf : public QObject
{
    Q_OBJECT
public:
    CreatePdf();

public slots:
    void Print();

private:

    QTextDocument m_doc;
};

#endif // CREATEPDF_H
