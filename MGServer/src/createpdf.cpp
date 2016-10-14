#include "createpdf.h"
#include <QFile>
#include <QDebug>
#include <QTextCursor>

CreatePdf::CreatePdf()
 : QObject()
// , m_doc()
 , m_printer(QPrinter::PrinterResolution)
 , m_cRank()
{
}

void CreatePdf::retriveGymnastList()
{
    m_cRank.createLists();
}

void CreatePdf::Print()
{
    retriveGymnastList();
    // 1st update the scores
    m_cRank.updateAllroundScores();

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

    if (! m_printer.newPage()) {
        qWarning("failed in flushing page to disk, disk full?");
    }

    m_cRank.updateSingleScores(ApparatusList::AMParallelBars);
    PrintMenCityTrophy(false);
    if (! m_printer.newPage()) {
        qWarning("failed in flushing page to disk, disk full?");
    }

    m_cRank.updateSingleScores(ApparatusList::AWFloor);
    PrintWomenCityTrophy(false);

//    m_doc.setHtml(m_textStream.readAll());
//    m_doc.setPageSize(m_printer.pageRect().size()); // This is necessary if you want to hide the page number

    m_painter.end();
//    m_doc.print(&m_printer);
}

void CreatePdf::PrintMenAllround(bool p_bHFImages)
{
    QTextDocument doc;
    QTextCursor cur(&doc);

    if (QFile::exists("../MGServer/pdf/OUT_MenAllround.html"))
        QFile::remove("../MGServer/pdf/OUT_MenAllround.html");
    QFile fileOut("../MGServer/pdf/OUT_MenAllround.html");
    if(!fileOut.open(QIODevice::ReadWrite)) {
        qDebug() << "Unable to open file " << fileOut.errorString();
    }
    QTextStream out(&fileOut);

    PrintHeader(p_bHFImages, out);


    //    QWebView web;
//    web.setHtml(strLocalText);
//    web.print(&printer);

//    cur.movePosition(QTextCursor::Start);
//    cur.insertText("Ciao!");

    PrintMenTableTitle(out);

    PrintMenTableBody(out);

    PrintFooter(p_bHFImages, out);

    // Read the output files and import it as html document
    fileOut.close();
    QFile fileIn("../MGServer/pdf/OUT_MenAllround.html");
    if(!fileIn.open(QIODevice::ReadOnly)) {
        qDebug() << "Unable to open file " << fileIn.errorString();
    }
    QTextStream strReadOutCompleteFile(&fileIn);
    cur.insertHtml(strReadOutCompleteFile.readAll());
    fileIn.close();

    //    QWebView web;
//    web.setHtml(strLocalText);
//    web.print(&printer);

//    cur.movePosition(QTextCursor::Start);
//    cur.insertText("Ciao!");

    doc.drawContents(&m_painter);
}

void CreatePdf::PrintWomenAllround(bool p_bHFImages)
{
    QTextDocument doc;
    QTextCursor cur(&doc);

    if (QFile::exists("../MGServer/pdf/OUT_WomenAllround.html"))
        QFile::remove("../MGServer/pdf/OUT_WomenAllround.html");
    QFile fileOut("../MGServer/pdf/OUT_WomenAllround.html");
    if(!fileOut.open(QIODevice::ReadWrite)) {
        qDebug() << "Unable to open file " << fileOut.errorString();
    }
    QTextStream out(&fileOut);

    PrintHeader(p_bHFImages, out);

    PrintWomenTableTitle(out);

    PrintWomenTableBody(out);

    PrintFooter(p_bHFImages, out);

    // Read the output files and import it as html document
    fileOut.close();
    QFile fileIn("../MGServer/pdf/OUT_WomenAllround.html");
    if(!fileIn.open(QIODevice::ReadOnly)) {
        qDebug() << "Unable to open file " << fileIn.errorString();
    }
    QTextStream strReadOutCompleteFile(&fileIn);
    cur.insertHtml(strReadOutCompleteFile.readAll());
    fileIn.close();

    doc.drawContents(&m_painter);
}

void CreatePdf::PrintMenCityTrophy(bool p_bHFImages)
{
    QTextDocument doc;
    QTextCursor cur(&doc);

    if (QFile::exists("../MGServer/pdf/OUT_MenCityTrophy.html"))
        QFile::remove("../MGServer/pdf/OUT_MenCityTrophy.html");
    QFile fileOut("../MGServer/pdf/OUT_MenCityTrophy.html");
    if(!fileOut.open(QIODevice::ReadWrite)) {
        qDebug() << "Unable to open file " << fileOut.errorString();
    }
    QTextStream out(&fileOut);

    PrintHeader(p_bHFImages, out);

    PrintSingleMApparatusTableTitle(out);

    PrintSingleMApparatusTableBody(out);

    PrintFooter(p_bHFImages, out);

    // Read the output files and import it as html document
    fileOut.close();
    QFile fileIn("../MGServer/pdf/OUT_MenCityTrophy.html");
    if(!fileIn.open(QIODevice::ReadOnly)) {
        qDebug() << "Unable to open file " << fileIn.errorString();
    }
    QTextStream strReadOutCompleteFile(&fileIn);
    cur.insertHtml(strReadOutCompleteFile.readAll());
    fileIn.close();

    doc.drawContents(&m_painter);
}


void CreatePdf::PrintWomenCityTrophy(bool p_bHFImages)
{
    QTextDocument doc;
    QTextCursor cur(&doc);

    if (QFile::exists("../MGServer/pdf/OUT_WomenCityTrophy.html"))
        QFile::remove("../MGServer/pdf/OUT_WomenCityTrophy.html");
    QFile fileOut("../MGServer/pdf/OUT_WomenCityTrophy.html");
    if(!fileOut.open(QIODevice::ReadWrite)) {
        qDebug() << "Unable to open file " << fileOut.errorString();
    }
    QTextStream out(&fileOut);

    PrintHeader(p_bHFImages, out);

    PrintSingleWApparatusTableTitle(out);

    PrintSingleWApparatusTableBody(out);

    PrintFooter(p_bHFImages, out);

    // Read the output files and import it as html document
    fileOut.close();
    QFile fileIn("../MGServer/pdf/OUT_WomenCityTrophy.html");
    if(!fileIn.open(QIODevice::ReadOnly)) {
        qDebug() << "Unable to open file " << fileIn.errorString();
    }
    QTextStream strReadOutCompleteFile(&fileIn);
    cur.insertHtml(strReadOutCompleteFile.readAll());
    fileIn.close();

    doc.drawContents(&m_painter);
}

void CreatePdf::PrintHeader(bool p_bHFImages, QTextStream& out)
{
    // Add header
    QString fileName;
    if (p_bHFImages)
        fileName = "../MGServer/pdf/IN_NoHeader.html"; // GCA modify it
    else
        fileName = "../MGServer/pdf/IN_NoHeader.html";

    QFile fileIn(fileName);
    if(!fileIn.open(QIODevice::ReadOnly)) {
        qDebug() << "Unable to open file " << fileIn.errorString();
    }
    QTextStream strHeader(&fileIn);
    out << strHeader.readAll(); // copy to output file
    fileIn.close();
}

void CreatePdf::PrintFooter(bool p_bHFImages, QTextStream& out)
{
    QString fileName;
    if (p_bHFImages)
        fileName = "../MGServer/pdf/IN_NoFooter.html"; // GCA modify it
    else
        fileName = "../MGServer/pdf/IN_NoFooter.html";

    QFile fileIn(fileName);
    if(!fileIn.open(QIODevice::ReadOnly)) {
        qDebug() << "Unable to open file " << fileIn.errorString();
    }
    QTextStream strFooter(&fileIn);
    out << strFooter.readAll();
    fileIn.close();
}

void CreatePdf::PrintMenTableTitle(QTextStream& out)
{
    QFile fileIn("../MGServer/pdf/IN_MenTableTitle.html");
    if(!fileIn.open(QIODevice::ReadOnly)) {
        qDebug() << "Unable to open file " << fileIn.errorString();
    }
    QTextStream strTableTitle(&fileIn);
    out << strTableTitle.readAll(); // copy to output file
    fileIn.close();
}

void CreatePdf::PrintMenTableBody(QTextStream& out)
{
    QList<AthleteData>* pMenList = m_cRank.getAllroundMenList();

    for (int i=0; i<pMenList->size(); i++)
    {
        out << "\t<tr>" << endl;
        out << "\t  <th rowspan=\"2\" valign=\"middle\">"
            << pMenList->at(i).getRank()
            <<"</th> <!-- Rank -->" << endl;
        out << "\t  <th rowspan=\"2\" valign=\"middle\" align=\"left\" width=\"150\">"
            << pMenList->at(i).getNameFull()
            << "(" << pMenList->at(i).getNationShort() << ")"
            << "</th>" << endl;
        out << "\t  <th align=\"center\">"
            << pMenList->at(i).getFinalScore(ApparatusList::AGTotalScore)
            <<"</th> <!-- Total -->" << endl;
        out << "\t  <td align=\"center\">"
            << pMenList->at(i).getFinalScore(ApparatusList::AMFloor)
            <<"</td> <!-- Floor -->" << endl;
        out << "\t  <td align=\"center\">"
            << pMenList->at(i).getFinalScore(ApparatusList::AMPommelHores)
            <<"</td> <!-- Pommel Horse-->" << endl;
        out << "\t  <td align=\"center\">"
            << pMenList->at(i).getFinalScore(ApparatusList::AMRings)
            <<"</td> <!-- Rings-->" << endl;
        out << "\t  <td align=\"center\">"
            << pMenList->at(i).getFinalScore(ApparatusList::AMVault)
            <<"</td> <!-- Vault-->" << endl;
        out << "\t  <td align=\"center\">"
            << pMenList->at(i).getFinalScore(ApparatusList::AMParallelBars)
            <<"</td> <!-- Parallel Bars-->" << endl;
        out << "\t  <td align=\"center\">"
            << pMenList->at(i).getFinalScore(ApparatusList::AMHorizontalBar)
            <<"</td> <!-- Horizonatl Bar-->" << endl;
        out << "\t</tr>" << endl;

        out << "\t<tr>" << endl;
        out << "\t  <td align=\"center\"><small>("
            << pMenList->at(i).getStartScore(ApparatusList::AGTotalScore)
            <<")</small></td> <!-- Total -->" << endl;
        out << "\t  <td align=\"center\"><small>("
            << pMenList->at(i).getStartScore(ApparatusList::AMFloor)
            <<")</small></td>  <!-- Floor -->" << endl;
        out << "\t  <td align=\"center\"><small>("
            << pMenList->at(i).getStartScore(ApparatusList::AMPommelHores)
            <<")</small></td>  <!-- Pommel Horse-->" << endl;
        out << "\t  <td align=\"center\"><small>("
            << pMenList->at(i).getStartScore(ApparatusList::AMRings)
            <<")</small></td>  <!-- Rings-->" << endl;
        out << "\t  <td align=\"center\"><small>("
            << pMenList->at(i).getStartScore(ApparatusList::AMVault)
            <<")</small></td>  <!-- Vault-->" << endl;
        out << "\t  <td align=\"center\"><small>("
            << pMenList->at(i).getStartScore(ApparatusList::AMParallelBars)
            <<")</small></td>  <!-- Parallel Bars-->" << endl;
        out << "\t  <td align=\"center\"><small>("
            << pMenList->at(i).getStartScore(ApparatusList::AMHorizontalBar)
            <<")</small></td>  <!-- Horizonatl Bar-->" << endl;
        out << "\t</tr>" << endl;
    }
}

void CreatePdf::PrintWomenTableTitle(QTextStream& out)
{
    QFile fileIn("../MGServer/pdf/IN_WomenTableTitle.html");
    if(!fileIn.open(QIODevice::ReadOnly)) {
        qDebug() << "Unable to open file " << fileIn.errorString();
    }
    QTextStream strTableTitle(&fileIn);
    out << strTableTitle.readAll(); // copy to output file
    fileIn.close();
}

void CreatePdf::PrintWomenTableBody(QTextStream& out)
{
    QList<AthleteData>* pWomenList = m_cRank.getAllroundWomenList();

    for (int i=0; i<pWomenList->size(); i++)
    {
        out << "\t<tr>" << endl;
        out << "\t  <th rowspan=\"2\" valign=\"middle\">"
            << pWomenList->at(i).getRank()
            <<"</th> <!-- Rank -->" << endl;
        out << "\t  <th rowspan=\"2\" valign=\"middle\" align=\"left\" width=\"150\">"
            << pWomenList->at(i).getNameFull()
            << "(" << pWomenList->at(i).getNationShort() << ")"
            << "</th>" << endl;
        out << "\t  <th align=\"center\">"
            << pWomenList->at(i).getFinalScore(ApparatusList::AGTotalScore)
            <<"</th> <!-- Total -->" << endl;
        out << "\t  <td align=\"center\">"
            << pWomenList->at(i).getFinalScore(ApparatusList::AWVault)
            <<"</td> <!-- Vault -->" << endl;
        out << "\t  <td align=\"center\">"
            << pWomenList->at(i).getFinalScore(ApparatusList::AWUnevenBars)
            <<"</td> <!-- Uneven Bars-->" << endl;
        out << "\t  <td align=\"center\">"
            << pWomenList->at(i).getFinalScore(ApparatusList::AWBalanceBeam)
            <<"</td> <!-- Balance Beam-->" << endl;
        out << "\t  <td align=\"center\">"
            << pWomenList->at(i).getFinalScore(ApparatusList::AWFloor)
            <<"</td> <!-- Floor-->" << endl;
        out << "\t</tr>" << endl;

        out << "\t<tr>" << endl;
        out << "\t  <td align=\"center\"><small>("
            << pWomenList->at(i).getStartScore(ApparatusList::AGTotalScore)
            <<")</small></td> <!-- Total -->" << endl;
        out << "\t  <td align=\"center\"><small>("
            << pWomenList->at(i).getStartScore(ApparatusList::AWVault)
            <<")</small></td>  <!-- Vault -->" << endl;
        out << "\t  <td align=\"center\"><small>("
            << pWomenList->at(i).getStartScore(ApparatusList::AWUnevenBars)
            <<")</small></td>  <!-- Uneven Bars-->" << endl;
        out << "\t  <td align=\"center\"><small>("
            << pWomenList->at(i).getStartScore(ApparatusList::AWBalanceBeam)
            <<")</small></td>  <!-- Balance Beam-->" << endl;
        out << "\t  <td align=\"center\"><small>("
            << pWomenList->at(i).getStartScore(ApparatusList::AWFloor)
            <<")</small></td>  <!-- Floor-->" << endl;

        out << "\t</tr>" << endl;
    }
}

void CreatePdf::PrintSingleMApparatusTableTitle(QTextStream& out)
{
    QFile fileIn("../MGServer/pdf/IN_MenCityTrophyTableTitle.html");
    if(!fileIn.open(QIODevice::ReadOnly)) {
        qDebug() << "Unable to open file " << fileIn.errorString();
    }
    QTextStream strTableTitle(&fileIn);
    out << strTableTitle.readAll(); // copy to output file
    fileIn.close();
}

void CreatePdf::PrintSingleMApparatusTableBody(QTextStream& out)
{
    QList<SingleMWData>* pMenList = m_cRank.getSingleMenList();

    for (int i=0; i<pMenList->size(); i++)
    {
        // Skip if final score is 0
        if (pMenList->at(i).getFinalScore() != "0.000")
        {
            out << "\t<tr>" << endl;
            out << "\t  <th rowspan=\"2\" valign=\"middle\">"
                << pMenList->at(i).getRank()
                <<"</th> <!-- Rank -->" << endl;
            out << "\t  <th rowspan=\"2\" valign=\"middle\" align=\"left\" width=\"180\">"
                << pMenList->at(i).getNameFull()
                << "(" << pMenList->at(i).getNation() << ")"
                << "</th>" << endl;
            out << "\t  <th align=\"center\">"
                << pMenList->at(i).getFinalScore()
                <<"</th> <!-- Single appparatus -->" << endl;
            out << "\t</tr>" << endl;

            out << "\t<tr>" << endl;
            out << "\t  <td align=\"center\"><small>("
                << pMenList->at(i).getStartScore()
                <<")</small></td> <!-- Single appparatus -->" << endl;
            out << "\t</tr>" << endl;
        }
    }
}

void CreatePdf::PrintSingleWApparatusTableTitle(QTextStream& out)
{
    QFile fileIn("../MGServer/pdf/IN_WomenCityTrophyTableTitle.html");
    if(!fileIn.open(QIODevice::ReadOnly)) {
        qDebug() << "Unable to open file " << fileIn.errorString();
    }
    QTextStream strTableTitle(&fileIn);
    out << strTableTitle.readAll(); // copy to output file
    fileIn.close();
}

void CreatePdf::PrintSingleWApparatusTableBody(QTextStream& out)
{
    QList<SingleMWData>* pWomenList = m_cRank.getSingleWomenList();

    for (int i=0; i<pWomenList->size(); i++)
    {
        // Skip if final score is 0
        if (pWomenList->at(i).getFinalScore() != "0.000")
        {
            out << "\t<tr>" << endl;
            out << "\t  <th rowspan=\"2\" valign=\"middle\">"
                << pWomenList->at(i).getRank()
                <<"</th> <!-- Rank -->" << endl;
            out << "\t  <th rowspan=\"2\" valign=\"middle\" align=\"left\" width=\"180\">"
                << pWomenList->at(i).getNameFull()
                << "(" << pWomenList->at(i).getNation() << ")"
                << "</th>" << endl;
            out << "\t  <th align=\"center\">"
                << pWomenList->at(i).getFinalScore()
                <<"</th> <!-- Single appparatus -->" << endl;
            out << "\t</tr>" << endl;

            out << "\t<tr>" << endl;
            out << "\t  <td align=\"center\" width=\"60\"><small>("
                << pWomenList->at(i).getStartScore()
                <<")</small></td> <!-- Single appparatus -->" << endl;
            out << "\t</tr>" << endl;
        }
    }
}
