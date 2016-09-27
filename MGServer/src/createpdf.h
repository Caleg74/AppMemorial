#ifndef CREATEPDF_H
#define CREATEPDF_H

#include <QTextDocument>
#include <QPrinter>
#include <QTextStream>
#include <QPainter>

class CreatePdf : public QObject
{
    Q_OBJECT
public:
    CreatePdf();

public slots:
    void Print();

private:

    /** Creates a pdf for the Men's allround ranking.
     * @param p_bHFImages true=with Header/Footer sponsor images
     */
    void PrintMenAllround(bool p_bHFImages);

    /** Creates a pdf for the Women's allround ranking.
     * @param p_bHFImages true=with Header/Footer sponsor images
     */
    void PrintWomenAllround(bool p_bHFImages);

    /** Creates a pdf for the Men's citycup ranking.
     * @param p_bHFImages true=with Header/Footer sponsor images
     */
    void PrintMenCitycup(bool p_bHFImages);

    /** Creates a pdf for the Women's citycup ranking.
     * @param p_bHFImages true=with Header/Footer sponsor images
     */
    void PrintWomenCitycup(bool p_bHFImages);

//    QTextDocument m_doc;
    QTextStream m_textStream;

    QPainter m_painter;

    QPrinter m_printer;
};

#endif // CREATEPDF_H
